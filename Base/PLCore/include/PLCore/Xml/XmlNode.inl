/*********************************************************\
 *  File: XmlNode.inl                                    *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    The meaning of 'value' changes for the specific type of 'XmlNode'
*/
inline String XmlNode::GetValue() const
{
	return m_sValue;
}

/**
*  @brief
*    Changes the value of the node
*/
inline void XmlNode::SetValue(const String &sValue)
{
	m_sValue = sValue;
}

/**
*  @brief
*    One step up the DOM
*/
inline XmlNode *XmlNode::GetParent()
{
	return m_pParent;
}

inline const XmlNode *XmlNode::GetParent() const
{
	return m_pParent;
}

/**
*  @brief
*    Returns the first child of this node
*/
inline XmlNode *XmlNode::GetFirstChild()
{
	return m_pFirstChild;
}

inline const XmlNode *XmlNode::GetFirstChild() const
{
	return m_pFirstChild;
}

/**
*  @brief
*    Returns the last child of this node
*/
inline XmlNode *XmlNode::GetLastChild()
{
	return m_pLastChild;
}

inline const XmlNode *XmlNode::GetLastChild() const
{
	return m_pLastChild;
}

/**
*  @brief
*    An alternate way to walk the children of a node
*/
inline XmlNode *XmlNode::IterateChildren(XmlNode *pPrevious)
{
	return const_cast< XmlNode* >( (const_cast< const XmlNode* >(this))->IterateChildren( pPrevious ) );
}

inline const XmlNode *XmlNode::IterateChildren(const XmlNode *pPrevious) const
{
	return pPrevious ? pPrevious->GetNextSibling() : GetFirstChild();
}

/**
*  @brief
*    This flavor of 'IterateChildren()' searches for children with a particular 'value'
*/
inline XmlNode *XmlNode::IterateChildren(const String &sValue, XmlNode *pPrevious)
{
	return pPrevious ? pPrevious->GetNextSibling(sValue) : GetFirstChild(sValue);
}

inline const XmlNode *XmlNode::IterateChildren(const String &sValue, const XmlNode *pPrevious) const
{
	return pPrevious ? pPrevious->GetNextSibling(sValue) : GetFirstChild(sValue);
}

/**
*  @brief
*    Navigate to a sibling node
*/
inline XmlNode *XmlNode::GetPreviousSibling()
{
	return m_pPreviousSibling;
}

inline const XmlNode *XmlNode::GetPreviousSibling() const
{
	return m_pPreviousSibling;
}

/**
*  @brief
*    Navigate to a sibling node
*/
inline XmlNode *XmlNode::GetNextSibling()
{
	return m_pNextSibling;
}

inline const XmlNode *XmlNode::GetNextSibling() const
{
	return m_pNextSibling;
}

/**
*  @brief
*    Convenience function to get through elements
*/
inline XmlElement *XmlNode::GetNextSiblingElement()
{
	return const_cast< XmlElement* >( (const_cast< const XmlNode* >(this))->GetNextSiblingElement() );
}

/**
*  @brief
*    Convenience function to get through elements
*/
inline XmlElement *XmlNode::GetFirstChildElement()
{
	return const_cast< XmlElement* >( (const_cast< const XmlNode* >(this))->GetFirstChildElement() );
}

/**
*  @brief
*    Convenience function to get through elements
*/
inline XmlElement *XmlNode::GetFirstChildElement(const String &sValue)
{
	return const_cast< XmlElement* >( (const_cast< const XmlNode* >(this))->GetFirstChildElement( sValue ) );
}

/**
*  @brief
*    Query the type (as an enumerated value, above) of this node
*/
inline XmlNode::ENodeType XmlNode::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Return a pointer to the document this node lives in
*/
inline XmlDocument *XmlNode::GetDocument()
{
	return const_cast< XmlDocument* >( (const_cast< const XmlNode* >(this))->GetDocument() );
}

/**
*  @brief
*    Returns true if this node has no children
*/
inline bool XmlNode::NoChildren() const
{
	return !m_pFirstChild;
}

/**
*  @brief
*    Cast functions
*/
inline XmlDocument *XmlNode::ToDocument()
{
	return (m_nType == Document) ? reinterpret_cast<XmlDocument*>(this) : nullptr;
}

inline const XmlDocument *XmlNode::ToDocument() const
{
	return (m_nType == Document) ? reinterpret_cast<const XmlDocument*>(this) : nullptr;
}

inline XmlElement *XmlNode::ToElement()
{
	return (m_nType == Element) ? reinterpret_cast<XmlElement*>(this) : nullptr;
}

inline const XmlElement *XmlNode::ToElement() const
{
	return (m_nType == Element) ? reinterpret_cast<const XmlElement*>(this) : nullptr;
}

inline XmlComment *XmlNode::ToComment()
{
	return (m_nType == Comment) ? reinterpret_cast<XmlComment*>(this) : nullptr;
}

inline const XmlComment *XmlNode::ToComment() const
{
	return (m_nType == Comment) ? reinterpret_cast<const XmlComment*>(this) : nullptr;
}

inline XmlUnknown *XmlNode::ToUnknown()
{
	return (m_nType == Unknown) ? reinterpret_cast<XmlUnknown*>(this) : nullptr;
}

inline const XmlUnknown *XmlNode::ToUnknown() const
{
	return (m_nType == Unknown) ? reinterpret_cast<const XmlUnknown*>(this) : nullptr;
}

inline XmlText *XmlNode::ToText()
{
	return (m_nType == Text) ? reinterpret_cast<XmlText*>(this) : nullptr;
}

inline const XmlText *XmlNode::ToText() const
{
	return (m_nType == Text) ? reinterpret_cast<const XmlText*>(this) : nullptr;
}

inline XmlDeclaration *XmlNode::ToDeclaration()
{
	return (m_nType == Declaration) ? reinterpret_cast<XmlDeclaration*>(this) : nullptr;
}

inline const XmlDeclaration *XmlNode::ToDeclaration() const
{
	return (m_nType == Declaration) ? reinterpret_cast<const XmlDeclaration*>(this) : nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
