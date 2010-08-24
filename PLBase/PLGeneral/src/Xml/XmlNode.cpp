/*********************************************************\
 *  File: XmlNode.cpp                                    *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <tinyxml.h>
#include "PLGeneral/Xml/Xml.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
XmlNode::~XmlNode()
{
}

/**
*  @brief
*    The meaning of 'value' changes for the specific type of 'XmlNode'
*/
String XmlNode::GetValue() const
{
	return ((TiXmlNode*)m_pData)->Value();
}

/**
*  @brief
*    Changes the value of the node
*/
void XmlNode::SetValue(const String &sValue)
{
	((TiXmlNode*)m_pData)->SetValue(sValue);
}

/**
*  @brief
*    Delete all the children of this node
*/
void XmlNode::Clear()
{
	((TiXmlNode*)m_pData)->Clear();
}

/**
*  @brief
*    One step up the DOM
*/
XmlNode *XmlNode::GetParent()
{
	return GetPLNode(((TiXmlNode*)m_pData)->Parent());
}

const XmlNode *XmlNode::GetParent() const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->Parent());
}

/**
*  @brief
*    Returns the first child of this node
*/
XmlNode *XmlNode::GetFirstChild()
{
	return GetPLNode(((TiXmlNode*)m_pData)->FirstChild());
}

const XmlNode *XmlNode::GetFirstChild() const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->FirstChild());
}

/**
*  @brief
*    Returns the first child of this node with the matching 'value'
*/
XmlNode *XmlNode::GetFirstChild(const String &sValue)
{
	return GetPLNode(((TiXmlNode*)m_pData)->FirstChild(sValue));
}

const XmlNode *XmlNode::GetFirstChild(const String &sValue) const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->FirstChild(sValue));
}

/**
*  @brief
*    Returns the last child of this node
*/
XmlNode *XmlNode::GetLastChild()
{
	return GetPLNode(((TiXmlNode*)m_pData)->LastChild());
}

const XmlNode *XmlNode::GetLastChild() const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->LastChild());
}

/**
*  @brief
*    Returns the last child of this node with the matching 'value'
*/
XmlNode *XmlNode::GetLastChild(const String &sValue)
{
	return GetPLNode(((TiXmlNode*)m_pData)->LastChild(sValue));
}

const XmlNode *XmlNode::GetLastChild(const String &sValue) const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->LastChild(sValue));
}

/**
*  @brief
*    An alternate way to walk the children of a node
*/
XmlNode *XmlNode::IterateChildren(XmlNode *pPrevious)
{
	return pPrevious ? GetPLNode(((TiXmlNode*)m_pData)->IterateChildren((TiXmlNode*)pPrevious->m_pData)) : GetPLNode(((TiXmlNode*)m_pData)->IterateChildren(NULL));
}

const XmlNode *XmlNode::IterateChildren(const XmlNode *pPrevious) const
{
	return pPrevious ? (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->IterateChildren((TiXmlNode*)pPrevious->m_pData)) : (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->IterateChildren(NULL));
}

/**
*  @brief
*    This flavor of 'IterateChildren()' searches for children with a particular 'value'
*/
XmlNode *XmlNode::IterateChildren(const String &sValue, XmlNode *pPrevious)
{
	return pPrevious ? GetPLNode(((TiXmlNode*)m_pData)->IterateChildren(sValue, (TiXmlNode*)pPrevious->m_pData)) : GetPLNode(((TiXmlNode*)m_pData)->IterateChildren(sValue, NULL));
}

const XmlNode *XmlNode::IterateChildren(const String &sValue, const XmlNode *pPrevious) const
{
	return pPrevious ? (const XmlNode*)GetPLNode((void*)((TiXmlNode*)m_pData)->IterateChildren(sValue, (const TiXmlNode*)pPrevious->m_pData)) : (const XmlNode*)GetPLNode((void*)((TiXmlNode*)m_pData)->IterateChildren(sValue, NULL));
}

/**
*  @brief
*    Add a new node related to this (adds a child past the last child)
*/
XmlNode *XmlNode::InsertEndChild(const XmlNode &cAddThis)
{
	return GetPLNode(((TiXmlNode*)m_pData)->InsertEndChild((const TiXmlNode&)*((TiXmlNode*)cAddThis.m_pData)));
}

/**
*  @brief
*    Add a new node related to this (adds a child past the last child)
*/
XmlNode *XmlNode::LinkEndChild(XmlNode &cAddThis)
{
	return GetPLNode(((TiXmlNode*)m_pData)->LinkEndChild((TiXmlNode*)cAddThis.m_pData));
}

/**
*  @brief
*    Add a new node related to this (adds a child before the specified child)
*/
XmlNode *XmlNode::InsertBeforeChild(const XmlNode &cBeforeThis, const XmlNode &cAddThis)
{
	return GetPLNode(((TiXmlNode*)m_pData)->InsertBeforeChild((TiXmlNode*)cBeforeThis.m_pData, (const TiXmlNode&)*((TiXmlNode*)cAddThis.m_pData)));
}

/**
*  @brief
*    Add a new node related to this (adds a child after the specified child)
*/
XmlNode *XmlNode::InsertAfterChild(const XmlNode &cAfterThis, const XmlNode &cAddThis)
{
	return GetPLNode(((TiXmlNode*)m_pData)->InsertAfterChild((TiXmlNode*)cAfterThis.m_pData, (const TiXmlNode&)*((TiXmlNode*)cAddThis.m_pData)));
}

/**
*  @brief
*    Replace a child of this node
*/
XmlNode *XmlNode::ReplaceChild(XmlNode &cReplaceThis, const XmlNode &cWithThis)
{
	return GetPLNode(((TiXmlNode*)m_pData)->ReplaceChild((TiXmlNode*)cReplaceThis.m_pData, (const TiXmlNode&)*((TiXmlNode*)cWithThis.m_pData)));
}

/**
*  @brief
*    Delete a child of this node
*/
bool XmlNode::RemoveChild(XmlNode &cRemoveThis)
{
	return ((TiXmlNode*)m_pData)->RemoveChild((TiXmlNode*)cRemoveThis.m_pData);
}

/**
*  @brief
*    Navigate to a sibling node
*/
XmlNode *XmlNode::GetPreviousSibling()
{
	return GetPLNode(((TiXmlNode*)m_pData)->PreviousSibling());
}

const XmlNode *XmlNode::GetPreviousSibling() const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->PreviousSibling());
}

/**
*  @brief
*    Navigate to a sibling node with the given 'value'
*/
XmlNode *XmlNode::GetPreviousSibling(const String &sValue)
{
	return GetPLNode(((TiXmlNode*)m_pData)->PreviousSibling(sValue));
}

const XmlNode *XmlNode::GetPreviousSibling(const String &sValue) const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->PreviousSibling(sValue));
}

/**
*  @brief
*    Navigate to a sibling node
*/
XmlNode *XmlNode::GetNextSibling()
{
	return GetPLNode(((TiXmlNode*)m_pData)->NextSibling());
}

const XmlNode *XmlNode::GetNextSibling() const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->NextSibling());
}

/**
*  @brief
*    Navigate to a sibling node with the given 'value'
*/
XmlNode *XmlNode::GetNextSibling(const String &sValue)
{
	return GetPLNode(((TiXmlNode*)m_pData)->NextSibling(sValue));
}

const XmlNode *XmlNode::GetNextSibling(const String &sValue) const
{
	return (const XmlNode*)GetPLNode(((TiXmlNode*)m_pData)->NextSibling(sValue));
}

/**
*  @brief
*    Convenience function to get through elements
*/
XmlElement *XmlNode::GetNextSiblingElement()
{
	return (XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->NextSiblingElement());
}

const XmlElement *XmlNode::GetNextSiblingElement() const
{
	return (const XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->NextSiblingElement());
}

/**
*  @brief
*    Convenience function to get through elements
*/
XmlElement *XmlNode::GetNextSiblingElement(const String &sValue)
{
	return (XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->NextSiblingElement(sValue));
}

const XmlElement *XmlNode::GetNextSiblingElement(const String &sValue) const
{
	return (const XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->NextSiblingElement(sValue));
}

/**
*  @brief
*    Convenience function to get through elements
*/
XmlElement *XmlNode::GetFirstChildElement()
{
	return (XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->FirstChildElement());
}

const XmlElement *XmlNode::GetFirstChildElement() const
{
	return (const XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->FirstChildElement());
}

/**
*  @brief
*    Convenience function to get through elements
*/
XmlElement *XmlNode::GetFirstChildElement(const String &sValue)
{
	return (XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->FirstChildElement(sValue));
}

const XmlElement *XmlNode::GetFirstChildElement(const String &sValue) const
{
	return (const XmlElement*)GetPLNode(((TiXmlNode*)m_pData)->FirstChildElement(sValue));
}

/**
*  @brief
*    Query the type (as an enumerated value, above) of this node
*/
XmlNode::ENodeType XmlNode::GetType() const
{
	return (ENodeType)((TiXmlNode*)m_pData)->Type();
}

/**
*  @brief
*    Return a pointer to the document this node lives in
*/
XmlDocument *XmlNode::GetDocument()
{
	return (XmlDocument*)GetPLNode(((TiXmlNode*)m_pData)->GetDocument());
}

const XmlDocument *XmlNode::GetDocument() const
{
	return (const XmlDocument*)GetPLNode(((TiXmlNode*)m_pData)->GetDocument());
}

/**
*  @brief
*    Returns true if this node has no children
*/
bool XmlNode::NoChildren() const
{
	return ((TiXmlNode*)m_pData)->NoChildren();
}

/**
*  @brief
*    Cast functions
*/
XmlDocument *XmlNode::ToDocument()
{
	return (GetType() == Document) ? (XmlDocument*)this : NULL;
}

const XmlDocument *XmlNode::ToDocument() const
{
	return (GetType() == Document) ? (const XmlDocument*)this : NULL;
}

XmlElement *XmlNode::ToElement()
{
	return (GetType() == Element) ? (XmlElement*)this : NULL;
}

const XmlElement *XmlNode::ToElement() const
{
	return (GetType() == Element) ? (const XmlElement*)this : NULL;
}

XmlComment *XmlNode::ToComment()
{
	return (GetType() == Comment) ? (XmlComment*)this : NULL;
}

const XmlComment *XmlNode::ToComment() const
{
	return (GetType() == Comment) ? (const XmlComment*)this : NULL;
}

XmlUnknown *XmlNode::ToUnknown()
{
	return (GetType() == Unknown) ? (XmlUnknown*)this : NULL;
}

const XmlUnknown *XmlNode::ToUnknown() const
{
	return (GetType() == Unknown) ? (const XmlUnknown*)this : NULL;
}

XmlText *XmlNode::ToText()
{
	return (GetType() == Text) ? (XmlText*)this : NULL;
}

const XmlText *XmlNode::ToText() const
{
	return (GetType() == Text) ? (const XmlText*)this : NULL;
}

XmlDeclaration *XmlNode::ToDeclaration()
{
	return (GetType() == Declaration) ? (XmlDeclaration*)this : NULL;
}

const XmlDeclaration *XmlNode::ToDeclaration() const
{
	return (GetType() == Declaration) ? (const XmlDeclaration*)this : NULL;
}

/**
*  @brief
*    Create an exact duplicate of this node and return it
*/
XmlNode *XmlNode::Clone() const
{
	return GetPLNode(((TiXmlNode*)m_pData)->Clone());
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XmlNode::XmlNode(void *pData) :
	XmlBase(pData)
{
}

/**
*  @brief
*    Returns/creates the PL XML node
*/
XmlNode *XmlNode::GetPLNode(void *pNode)
{
	// Check parameter
	if (!pNode)
		return NULL;

	// Check wether this TinyXML node has already a PL XML node, if there's no
	// PL XML node, create one
	TiXmlNode *pTinyXMLNode = (TiXmlNode*)pNode;
	if (pTinyXMLNode->GetUserData())
		return (XmlNode*)pTinyXMLNode->GetUserData();
	else {
		XmlNode *pNewNode = NULL;
		switch (pTinyXMLNode->Type()) {
			case TiXmlNode::TINYXML_DECLARATION:	  pNewNode = new XmlDeclaration(pTinyXMLNode, 0); break;
			case TiXmlNode::TINYXML_TEXT:			  pNewNode = new XmlText       (pTinyXMLNode, 0); break;
			case TiXmlNode::TINYXML_COMMENT:		  pNewNode = new XmlComment    (pTinyXMLNode, 0); break;
			case TiXmlNode::TINYXML_ELEMENT:		  pNewNode = new XmlElement    (pTinyXMLNode, 0); break;
			case TiXmlNode::TINYXML_DOCUMENT:		  pNewNode = new XmlDocument   (pTinyXMLNode, 0); break;
			case TiXmlNode::TINYXML_UNKNOWN: default: pNewNode = new XmlUnknown    (pTinyXMLNode, 0); break;
		}

		// Return the created PL node
		return pNewNode;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
XmlNode::XmlNode(const XmlNode &cSource) :
	XmlBase(NULL)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
XmlNode &XmlNode::operator =(const XmlNode &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
