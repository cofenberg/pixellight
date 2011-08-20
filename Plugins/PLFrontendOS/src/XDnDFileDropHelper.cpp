/*********************************************************\
 *  File: XDnDFileDropHelper.cpp                         *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendOS/XDnDFileDropHelper.h"
#include <PLCore/String/Tokenizer.h>
#include <PLCore/String/String.h>
#include <PLCore/Container/Array.h>
#include "PLFrontendOS/OSWindowLinux.h"
#include <string.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendOS {


XDnDFileDropHelper::XDnDFileDropHelper(OSWindowLinux *pOSWindowLinux)
	:	m_pOSWindowLinux(pOSWindowLinux),
		m_pDisplay(pOSWindowLinux->m_pDisplay),
		m_dropWindow(XLib::None),
		XdndEnter(XInternAtom(m_pDisplay, "XdndEnter", False)),
		XdndPosition(XInternAtom(m_pDisplay, "XdndPosition", False)),
		XdndStatus(XInternAtom(m_pDisplay, "XdndStatus", False)),
		XdndTypeList(XInternAtom(m_pDisplay, "XdndTypeList", False)),
		XdndActionCopy(XInternAtom(m_pDisplay, "XdndActionCopy", False)),
		XdndDrop(XInternAtom(m_pDisplay, "XdndDrop", False)),
		XdndFinished(XInternAtom(m_pDisplay, "XdndFinished", False)),
		XdndSelection(XInternAtom(m_pDisplay, "XdndSelection", False)),
		//This is a meta-format for data to be "pasted" in to.
		//Requesting this format acquires a list of possible
		//formats from the application which copied the data.
		XA_TARGETS(XInternAtom(m_pDisplay, "TARGETS", False)),
		m_XdndSourceWindow(XLib::None),
		m_ToBeRequestedType(XLib::None),
		m_XdndVersion(0)
{

}

void XDnDFileDropHelper::EnableDropForWindow()
{
	if (m_dropWindow != XLib::None)
		return;

	m_dropWindow = m_pOSWindowLinux->m_nNativeWindowHandle;
	//Announce XDND support
	Atom XdndAware = XInternAtom(m_pDisplay, "XdndAware", False);
	Atom version=5;
	XChangeProperty(m_pDisplay, m_dropWindow, XdndAware, XA_ATOM, 32, PropModeReplace, (unsigned char*)&version, 1);
}

bool XDnDFileDropHelper::HandleClientMessage(const XClientMessageEvent &clientMessage)
{
	if(clientMessage.message_type == XdndEnter)
	{
		HandleXdndEnter(clientMessage);
	}
	else if (clientMessage.message_type == XdndPosition)
	{
		HandleXdndPosition(clientMessage);
	}
	else if (clientMessage.message_type == XdndDrop)
	{
		HandleXdndDrop(clientMessage);
	}
	else
	{
		return false;
	}
	
	return true;
}

void XDnDFileDropHelper::HandleXdndEnter(const XClientMessageEvent &clientMessage)
{
	bool more_than_3 = clientMessage.data.l[1] & 1;
	Window source = clientMessage.data.l[0];

	m_XdndVersion = ( clientMessage.data.l[1] >> 24);

	//Query which conversions are available and pick the best

	if(more_than_3)
	{
		//Fetch the list of possible conversions
		PropertyData propertyData = ReadProperty(source , XdndTypeList);
		m_ToBeRequestedType = CheckForSupportedTargetTypFromProperty(propertyData);
		XFree(propertyData.data);
	}
	else
	{
		//Use the available list
		m_ToBeRequestedType = CheckForSupportedTargetTypFromAtoms(clientMessage.data.l[2], clientMessage.data.l[3], clientMessage.data.l[4]);
	}
}

void XDnDFileDropHelper::HandleXdndPosition(const XClientMessageEvent &clientMessage)
{
	
	Atom action = XdndActionCopy;
	if(m_XdndVersion >= 2)
		action = clientMessage.data.l[4];
	
	//Xdnd: reply with an XDND status message
	XClientMessageEvent m;
	memset(&m, 0, sizeof(m));
	m.type = ClientMessage;
	m.display = clientMessage.display;
	m.window = clientMessage.data.l[0];
	m.message_type = XdndStatus;
	m.format=32;
	m.data.l[0] = m_dropWindow;
	m.data.l[1] = (m_ToBeRequestedType != XLib::None);
	m.data.l[2] = m_pOSWindowLinux->GetWidth();
	m.data.l[3] = m_pOSWindowLinux->GetHeight();
	m.data.l[4] = XdndActionCopy; //We only accept copying anyway.

	XSendEvent(m_pDisplay,clientMessage.data.l[0], False, NoEventMask, (XEvent*)&m);
	XFlush(m_pDisplay);
}

void XDnDFileDropHelper::HandleXdndDrop(const XClientMessageEvent &clientMessage)
{
	if(m_ToBeRequestedType == XLib::None)
	{
		//It's sending anyway, despite instructions to the contrary.
		//So reply that we're not interested.
		XClientMessageEvent m;
		memset(&m, 0, sizeof(m));
		m.type = ClientMessage;
		m.display = clientMessage.display;
		m.window = clientMessage.data.l[0];
		m.message_type = XdndFinished;
		m.format=32;
		m.data.l[0] = m_dropWindow;
		m.data.l[1] = 0;
		m.data.l[2] = XLib::None; //Failed.
		XSendEvent(m_pDisplay, clientMessage.data.l[0], False, NoEventMask, (XEvent*)&m);
	}
	else
	{
		m_XdndSourceWindow = clientMessage.data.l[0];
		if(m_XdndVersion >= 1)
			XConvertSelection(m_pDisplay, XdndSelection, m_ToBeRequestedType, XdndSelection, m_dropWindow, clientMessage.data.l[2]);
		else
			XConvertSelection(m_pDisplay, XdndSelection, m_ToBeRequestedType, XdndSelection, m_dropWindow, CurrentTime);
	}
}

void XDnDFileDropHelper::HandleXdndSelection(const XSelectionEvent &selectionMessage)
{
	Atom target = selectionMessage.target;

	if(selectionMessage.property == XLib::None || selectionMessage.selection != XdndSelection)
	{
		// The selection can not be converted or isn't in the XdndSelection buffer -> ignore.
		return;
	}
	else 
	{
		// check if target is the requested one
		if(target == m_ToBeRequestedType)
		{
			PropertyData propertyData = ReadProperty(m_dropWindow, XdndSelection);
			
			//Reply OK.
			XClientMessageEvent m;
			memset(&m, 0, sizeof(m));
			m.type = ClientMessage;
			m.display = m_pDisplay;
			m.window = m_XdndSourceWindow;
			m.message_type = XdndFinished;
			m.format=32;
			m.data.l[0] = m_dropWindow;
			m.data.l[1] = 1;
			m.data.l[2] = XdndActionCopy; //We only ever copy.

			//Reply that all is well.
			XSendEvent(m_pDisplay, m_XdndSourceWindow, False, NoEventMask, (XEvent*)&m);

			XSync(m_pDisplay, False);
			
			String path (String::FromUTF8((char*)propertyData.data));
			
			XFree(propertyData.data);
			
			Tokenizer token;
			token.SetDelimiters("\n\r");
			token.SetSingleLineComment("");
			token.SetQuotes("");
			token.SetSingleChars("");
			
			token.Start(path);
			
			// Create the file list
			Array<String> lstFiles = token.GetTokens();
			
			// Inform the frontend
			m_pOSWindowLinux->OnDrop(lstFiles);
		}
	}
}

//[-------------------------------------------------------]
//[ Private helper functions                              ]
//[-------------------------------------------------------]
//This fetches all the data from a property
XDnDFileDropHelper::PropertyData XDnDFileDropHelper::ReadProperty(Window window, Atom property)
{
	Atom actual_type;
	int actual_format;
	unsigned long nitems;
	unsigned long bytes_after;
	unsigned char *ret=0;
	
	int read_bytes = 1024;	

	//Keep trying to read the property until there are no
	//bytes unread.
	do
	{
		if(ret != 0)
			XFree(ret);
		XGetWindowProperty(m_pDisplay, window, property, 0, read_bytes, False, AnyPropertyType,
							&actual_type, &actual_format, &nitems, &bytes_after, 
							&ret);

		read_bytes *= 2;
	}while(bytes_after != 0);
	
	PropertyData propertyData = {ret, actual_format, nitems, actual_type};

	return propertyData;
}

//Convert an atom name in to a String
String XDnDFileDropHelper::GetAtomName(Atom atom)
{
	if(atom == XLib::None)
		return "None";
	else
		return XGetAtomName(m_pDisplay, atom);
}

// This function takes a list of targets which can be converted to (atom_list, nitems)
// It returns the target which matches "text/uri-list" otherwise None
Atom XDnDFileDropHelper::CheckForSupportedTargetTypeFromAtomList(Atom* atom_list, int nitems)
{
	Atom to_be_requested = XLib::None;
	for(int i=0; i < nitems; i++)
	{
		String atom_name = GetAtomName(atom_list[i]);

		if (atom_name == "text/uri-list")
			to_be_requested = atom_list[i];
	}

	return to_be_requested;
}

// Finds the best target given up to three atoms provided (any can be None).
// Useful for part of the Xdnd protocol.
Atom XDnDFileDropHelper::CheckForSupportedTargetTypFromAtoms(Atom atom1, Atom atom2, Atom atom3)
{
	Atom atoms[3];
	int  count = 0;

	if(atom1 != XLib::None)
		atoms[count++] = atom1;

	if(atom2 != XLib::None)
		atoms[count++] = atom2;

	if(atom3 != XLib::None)
		atoms[count++] = atom3;

	return CheckForSupportedTargetTypeFromAtomList(atoms, count);
}

// Finds the best target given a local copy of a property.
Atom XDnDFileDropHelper::CheckForSupportedTargetTypFromProperty(PropertyData propertyData)
{
	//The list of targets is a list of atoms, so it should have type XA_ATOM
	//but it may have the type TARGETS instead.

	if((propertyData.type != XA_ATOM && propertyData.type != XA_TARGETS) || propertyData.format != 32)
	{ 
		//This would be really broken. Targets have to be an atom list
		//and applications should support this. Nevertheless, some
		//seem broken (MATLAB 7, for instance), so ask for STRING
		//next instead as the lowest common denominator

		return XA_STRING;
	}
	else
	{
		Atom *atom_list = (Atom*)propertyData.data;
		
		return CheckForSupportedTargetTypeFromAtomList(atom_list, propertyData.nitems);
	}
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
XDnDFileDropHelper::XDnDFileDropHelper(const XDnDFileDropHelper& other)
{

}

XDnDFileDropHelper& XDnDFileDropHelper::operator=(const XDnDFileDropHelper& other)
{
    return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
}
