/*********************************************************\
 *  File: XmlTest.cpp                                    *
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
#include <PLCore/Xml/Xml.h>
#include <PLCore/File/File.h>
#include "PLTestBase/General/XmlTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *XmlTest::GetName() const
{
	return "XML";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void XmlTest::Test()
{
	// We start with the 'pszDemoStart' todo list. Process it. And
	// should hopefully end up with the todo list as illustrated.
	const char *pszDemoStart =
		"<?xml version=\"1.0\"  standalone='no' >\n"
		"<!-- Our to do list data -->"
		"<ToDo>\n"
		"<!-- Do I need a secure PDA? -->\n"
		"<Item priority=\"1\" distance='close'> Go to the <bold>Toy store!</bold></Item>"
		"<Item priority=\"2\" distance='none'> Do bills   </Item>"
		"<Item priority=\"2\" distance='far &amp; back'> Look for Evil Dinosaurs! </Item>"
		"</ToDo>";

	{
		// Write to a file and read it back, to check file I/O
		XmlDocument cDocument("demotest.xml");
		cDocument.Parse(pszDemoStart);
		if (cDocument.Error())
			Print("Error in %s: %s\n", cDocument.GetValue().GetASCII(), cDocument.GetErrorDesc().GetASCII());
		cDocument.Save();
	}

	XmlDocument cDocument("demotest.xml");
	if (!cDocument.Load())
		Print("Could not load test file 'demotest.xml'. Error='%s'.\n", cDocument.GetErrorDesc().GetASCII());

	Print("** Demo doc read from disk: ** \n\n");
	cDocument.Save(File::StandardOutput);

	// An example of changing existing attributes, and removing an element from the document
	XmlElement *pTodoElement = nullptr;
	XmlElement *pItemElement = nullptr;

	// Get the "ToDo" element
	XmlNode *pNode = static_cast<XmlNode*>(cDocument.GetFirstChild("ToDo"));
	if (pNode) {
		// It is a child of the document, and can be selected by name
		pTodoElement = pNode->ToElement();

		// Going to the toy store is now our second priority...
		// So set the "priority" attribute of the first item in the list.
		pNode = pTodoElement->GetFirstChildElement();	// This skips the "PDA" comment
		pItemElement = pNode->ToElement();
		pItemElement->SetAttribute("priority", 2);

		// Change the distance to "doing bills" from
		// "none" to "here". It's the next sibling element.
		pItemElement = static_cast<XmlElement*>(pItemElement->GetNextSiblingElement());
		pItemElement->SetAttribute("distance", "here");

		// Remove the "Look for Evil Dinosours!" item.
		// It is 1 more sibling away. We ask the parent to remove
		// a particular child.
		pItemElement = static_cast<XmlElement*>(pItemElement->GetNextSiblingElement());
		pTodoElement->RemoveChild(*pItemElement);

		pItemElement = nullptr;
	}

	// What follows is an example of created elements and text
	// nodes and adding them to the document

	// Add some meetings
	XmlElement *pItem = new XmlElement("Item");
	pItem->SetAttribute("priority", "1");
	pItem->SetAttribute("distance", "far");

	XmlText *pText = new XmlText("Talk to:");

	XmlElement *pMeeting1 = new XmlElement("Meeting");
	pMeeting1->SetAttribute("where", "School");

	XmlElement *pMeeting2 = new XmlElement("Meeting");
	pMeeting2->SetAttribute("where", "Lunch");

	XmlElement *pAttendee1 = new XmlElement("Attendee");
	pAttendee1->SetAttribute("name", "Marple");
	pAttendee1->SetAttribute("position", "teacher");

	XmlElement *pAttendee2 = new XmlElement("Attendee");
	pAttendee2->SetAttribute("name", "Voel");
	pAttendee2->SetAttribute("position", "counselor");

	// Assemble the nodes we've created
	pMeeting1->LinkEndChild(*pAttendee1);
	pMeeting1->LinkEndChild(*pAttendee2);

	pItem->LinkEndChild(*pText);
	pItem->LinkEndChild(*pMeeting1);
	pItem->LinkEndChild(*pMeeting2);

	// And add the node to the existing list after the first child
	if (pTodoElement) {
		pNode = pTodoElement->GetFirstChild("Item");
		pItemElement = pNode->ToElement();

		pTodoElement->InsertAfterChild(*pItemElement, *pItem);
		delete pItem;
	}

	Print("\n** Demo doc processed: ** \n\n");
	cDocument.Save(File::StandardOutput);
}
