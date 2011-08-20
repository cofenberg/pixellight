/*********************************************************\
 *  File: XDnDFileDropHelper.h                           *
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


#ifndef __XDNDFILEDROPHELPER_H__
#define __XDNDFILEDROPHELPER_H__
#pragma once

//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
	#ifdef None
		// ... we undef these to avoid name conflicts...
		namespace OSWindowLinuxInclude {
			enum {
				X11_None = None,
				X11_Always = Always,
				X11_Above = Above,
				X11_Success = Success
			};
		}

		#undef None
		#undef Always
		#undef Above
		#undef Success

		namespace XLib {
			enum {
				None = OSWindowLinuxInclude::X11_None,
				Always = OSWindowLinuxInclude::X11_Always,
				Above = OSWindowLinuxInclude::X11_Above,
				Success = OSWindowLinuxInclude::X11_Success
			};
		}
		// ... now that the namespace is name conflict free, go on with includes...
	#endif
#include <PLCore/String/String.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendOS {

//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class OSWindowLinux;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OS Linux XDnD Helper class
*
*  @note
*    - Implements a subset of the XDnD Protocol (http://www.newplanetsoftware.com/xdnd/)
*    - It can only receive dop events and only URIs can be dropped
*    - This code is based on the paste.cc code from http://www.edwardrosten.com/code/x11.html
*/
class XDnDFileDropHelper
{


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		 *  @brief
		 *    Holds the data of an property (Atom)
		 */
		struct PropertyData
		{
			unsigned char *data;
			unsigned long format, nitems;
			Atom type;
		};

	//[-------------------------------------------------------]
	//[ public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pOSWindowLinux
		*    The OSWindowLinux instance which should support Drop
		*/
		XDnDFileDropHelper(OSWindowLinux *pOSWindowLinux);
		
		/**
		 * @brief
		 *    Enables XDnD for an window
		 * @param[in] window
		 *    The window for which the XDnD support should be enabled
		 * @remarks
		 *    If an window is already set then this method does nothing
		 *    The give window is internaly used for sending messages to the drop source window
		 */
		void EnableDropForWindow();

		/**
		 * @brief
		 *    Handler for client messages
		 * @param[in] cClientMessage
		 *    The XClientMessageEvent structure which holds the information about the client message
		 * @return
		 *    true if the message was handled otherwise false
		 */
		bool HandleClientMessage(const XClientMessageEvent &clientMessage);

		/**
		 * @brief
		 *    Handler for the SelectionNotify message
		 * @param[in] cClientMessage
		 *    The XSelectionEvent structure which holds the information about the XSelectionEvent message
		 * @remarks
		 *    This handler reads the drop data from teh XdndSelection buffer (the data was converted into this buffer from the HandleXdndDrop handler)
		 *    It sends an XdndFinished event to the drop source to indicate if the drop was successfull or not
		 *    If the drop was successfull the Frontend is informed about the dropped file list
		 */
		void HandleXdndSelection(const XSelectionEvent &selectionMessage);


	//[-------------------------------------------------------]
	//[ Private helper functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		 *  @brief
		 *    Fetches all data from a property (Atom)
		 *  @param[in] window
		 *    The window from which the property data schould be fetched
		 *  @param[in] property
		 *    The property from which the data should be fetched
		 *  @return
		 *    The PropertyData struct with the data of the property (Atom)
		 */
		PropertyData ReadProperty(Window window, Atom property);

		/**
		 *  @brief
		 *    Convert an atom name in to a String
		 *  @param[in] atom
		 *    The atom for which the name should be returnd
		 */
		PLCore::String GetAtomName(Atom atom);

		/**
		 *  @brief
		 *    Checks if the drop source supports the "text/uri-list" drop target type
		 *  @param[in] atom_list
		 *    the list of supported targets from the drop source
		 *  @param[in] nitems
		 *    the numer of items in the atom_list
		 *  @return
		 *    The corresponding Atom when the drop source supports the "text/uri-list" otherwise None
		 */
		Atom CheckForSupportedTargetTypeFromAtomList(Atom* atom_list, int nitems);

		/**
		 *  @brief
		 *    Checks if the drop source supports the "text/uri-list" drop target type (from three Atoms)
		 *  @param[in] atom1
		 *    the first atom (can be None)
		 *  @param[in] atom2
		 *    the first atom (can be None)
		 *  @param[in] atom3
		 *    the first atom (can be None)
		 *  @return
		 *    The corresponding Atom when the drop source supports the "text/uri-list" otherwise None
		 * 
		 *  @remarks
		 *    The ClientMessage structure used by the XDndEnterEvent can deliver max three Atoms, this method is used to generate a atom list from this three Atoms
		 *    This method internal calls CheckForSupportedTargetTypeFromAtomList
		 */
		Atom CheckForSupportedTargetTypFromAtoms(Atom atom1, Atom atom2, Atom atom3);

		/**
		 *  @brief
		 *    Checks if the drop source supports the "text/uri-list" drop target type (from an Property)
		 *  @param[in] propertyData
		 *    the data of an property
		 *  @return
		 *    The corresponding Atom when the drop source supports the "text/uri-list" otherwise None
		 * 
		 *  @remarks
		 *    The ClientMessage structure used by the XDndEnterEvent can deliver max three Atoms.
		 *    When the drop source supports more than 3 drop targets than the complete list can be read from the XdndTypeList Atom
		 *    This method internal calls CheckForSupportedTargetTypeFromAtomList
		 */
		Atom CheckForSupportedTargetTypFromProperty(PropertyData propertyData);

	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		 * @brief
		 *    copy constructor
		 */
		XDnDFileDropHelper(const XDnDFileDropHelper& other);

		/**
		 * @brief
		 *    assignment operator
		 */
		XDnDFileDropHelper& operator=(const XDnDFileDropHelper& other);

		/**
		 * @brief
		 *    Handler for the XDnDEnter client message
		 * @param[in] cClientMessage
		 *    The XClientMessageEvent structure which holds the information about the XDndEnter message
		 * @remarks
		 *    This handler retreives the supported XDnD protocol version and if the drop source supports the "text/uri-list" target type. 
		 */
		void HandleXdndEnter(const XClientMessageEvent &clientMessage);

		/**
		 * @brief
		 *    Handler for the XDnDPosition client message
		 * @param[in] cClientMessage
		 *    The XClientMessageEvent structure which holds the information about the XDnDPosition message
		 * @remarks
		 *    This handler checks if the drop source supports the "text/uri-list" target type and sends a corresponding XdndStatus message to the drop source
		 */
		void HandleXdndPosition(const XClientMessageEvent &clientMessage);

		/**
		 * @brief
		 *    Handler for the XDnDDrop client message
		 * @param[in] cClientMessage
		 *    The XClientMessageEvent structure which holds the information about the XDnDDrop message
		 * @remarks
		 *    This handler reads the drop data from the drop source window via an XConvertSelection call (the actual read is done in the HandleXDndSelection handler)
		 *    If this message was sent from the drop source but the drop source doesn't support the "test/uri-list" target type then this handler sends an XdndFinished which indicates that the drop has failed
		 */
		void HandleXdndDrop(const XClientMessageEvent &clientMessage);


	//[-------------------------------------------------------]
	//[ Private Data                                          ]
	//[-------------------------------------------------------]
	private:
		OSWindowLinux	*m_pOSWindowLinux;		/**< Pointer tp an OSWindowLinux instance should be always valid */
		Display			*m_pDisplay;			/**< System display, considered to be always valid */
		Window 			 m_dropWindow;			/**< The window which has drop support */
		//Atoms for Xdnd
		Atom			 XdndEnter;				/**< The atom for the XDnD Enter client message */
		Atom			 XdndPosition;			/**< The atom for the XDnD Position client message */
		Atom			 XdndStatus;			/**< The atom for the XDnD Status client message */
		Atom			 XdndTypeList;			/**< The atom to receive the supported drop target types when the source supports mor the 3 types (limit of the XCLientMessageEvent structure) */
		Atom			 XdndActionCopy;		/**< The atom for the XDnD Action type used for XDnD version 0 or 1 */
		Atom			 XdndDrop;				/**< The atom for the XDnD Drop client message */
		Atom			 XdndFinished;			/**< The atom for the XDnD Finished client message */
		Atom			 XdndSelection;			/**< The atom for the XDnD Selection buffer */
		Atom			 XA_TARGETS;			/**< The atom for the meta-format for data to be "pasted" in to.
													 Requesting this format acquires a list of possible formats from the application which copied the data. */
		// Data about the source
		Window 			 m_XdndSourceWindow;	/**< The source window */
		Atom 			 m_ToBeRequestedType;	/**< The requested drop target type can be None when the check in XDndEnter failed*/
		int				 m_XdndVersion;			/**< The support XDnD protocol version of the drop source */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS


#endif // __XDNDFILEDROPHELPER_H__
