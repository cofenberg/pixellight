/*********************************************************\
 *  File: XmlElement.h                                   *
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


#ifndef __PLGENERAL_XML_ELEMENT_H__
#define __PLGENERAL_XML_ELEMENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Xml/XmlNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class XmlAttribute;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    The XML element is a container class
*
*  @remarks
*    An element has a value, the element name, and can contain other elements, text,
*    comments, and unknowns. Elements also contain an arbitrary number of attributes.
*/
class XmlElement : public XmlNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XmlNode;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sValue
		*    Value of this element (value = element tag name)
		*/
		PLGENERAL_API XmlElement(const String &sValue);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLGENERAL_API XmlElement(const XmlElement &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~XmlElement();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLGENERAL_API XmlElement &operator =(const XmlElement &cSource);

		/**
		*  @brief
		*    Given an attribute name, 'GetAttribute()' returns the value
		*    for the attribute of that name, or empty string if none exists
		*
		*  @param[in] sName
		*    Attribute name
		*
		*  @return
		*    Attribute value, empty on error
		*/
		PLGENERAL_API String GetAttribute(const String &sName) const;

		/**
		*  @brief
		*    Given an attribute name, 'GetAttribute()' returns the value
		*    for the attribute of that name, or empty string if none exists
		*
		*  @param[in]  sName
		*    Attribute name
		*  @param[out] pnValue
		*    If not NULL, this variable will receive the integer value - if the attribute
		*    value can be converted into an integer, if not, this variable is not touched
		*
		*  @return
		*    Attribute value, empty on error
		*
		*  @remarks
		*    If the attribute exists and can be converted to an integer,
		*    the integer value will be put in the return 'pnValue', if 'pnValue'
		*    is not NULL.
		*/
		PLGENERAL_API String GetAttribute(const String &sName, int *pnValue) const;

		/**
		*  @brief
		*    Given an attribute name, 'GetAttribute()' returns the value
		*    for the attribute of that name, or empty string if none exists
		*
		*  @param[in]  sName
		*    Attribute name
		*  @param[out] pdValue
		*    If not NULL, this variable will receive the double value - if the attribute
		*    value can be converted into a double, if not, this variable is not touched
		*
		*  @return
		*    Attribute value, empty on error
		*
		*  @remarks
		*    If the attribute exists and can be converted to an double,
		*    the double value will be put in the return 'pdValue', if 'pdValue'
		*    is not NULL.
		*/
		PLGENERAL_API String GetAttribute(const String &sName, double *pdValue) const;

		/**
		*  @brief
		*    Examines the attribute
		*
		*  @param[in]  sName
		*    Attribute name
		*  @param[out] pnValue
		*    If not NULL, this variable will receive the integer value - if the attribute
		*    value can be converted into an integer, if not, this variable is not touched
		*
		*  @return
		*    'Success' if all went fine, 'WrongType' if value is not an integer and
		*    'NoAttribute' if the attribute does not exist
		*
		*  @note
		*     - This function is an alternative to the 'GetAttribute()' function with richer
		*       error checking.
		*/
		PLGENERAL_API EQueryResult QueryIntAttribute(const String &sName, int *pnValue) const;

		/**
		*  @brief
		*    Examines the attribute
		*
		*  @param[in]  sName
		*    Attribute name
		*  @param[out] pfValue
		*    If not NULL, this variable will receive the float value - if the attribute
		*    value can be converted into a float, if not, this variable is not touched
		*
		*  @return
		*    'Success' if all went fine, 'WrongType' if value is not a float and
		*    'NoAttribute' if the attribute does not exist
		*
		*  @see
		*    - QueryIntAttribute()
		*/
		PLGENERAL_API EQueryResult QueryFloatAttribute(const String &sName, float *pfValue) const;

		/**
		*  @brief
		*    Examines the attribute
		*
		*  @param[in]  sName
		*    Attribute name
		*  @param[out] pdValue
		*    If not NULL, this variable will receive the double value - if the attribute
		*    value can be converted into a double, if not, this variable is not touched
		*
		*  @return
		*    'Success' if all went fine, 'WrongType' if value is not a double and
		*    'NoAttribute' if the attribute does not exist
		*
		*  @see
		*    - QueryIntAttribute()
		*/
		PLGENERAL_API EQueryResult QueryDoubleAttribute(const String &sName, double *pdValue) const;

		/**
		*  @brief
		*    Sets an attribute of name to a given value
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] sValue
		*    Attribute value
		*
		*  @remarks
		*    The attribute will be created if it does not exist, or changed if it does.
		*/
		PLGENERAL_API void SetAttribute(const String &sName, const String &sValue);

		/**
		*  @brief
		*    Sets an attribute of name to a given value
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] nValue
		*    Attribute value
		*
		*  @remarks
		*    The attribute will be created if it does not exist, or changed if it does.
		*/
		PLGENERAL_API void SetAttribute(const String &sName, int nValue);

		/**
		*  @brief
		*    Sets an attribute of name to a given value
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] dValue
		*    Attribute value
		*
		*  @remarks
		*    The attribute will be created if it does not exist, or changed if it does.
		*/
		PLGENERAL_API void SetDoubleAttribute(const String &sName, double dValue);

		/**
		*  @brief
		*    Deletes an attribute with the given name
		*
		*  @param[in] sName
		*    Name of the attribute to remove
		*/
		PLGENERAL_API void RemoveAttribute(const String &sName);

		/**
		*  @brief
		*    Access the first attribute in this element
		*
		*  @return
		*    The first attribute, NULL if there's no first attribute
		*/
		PLGENERAL_API XmlAttribute *GetFirstAttribute();
		PLGENERAL_API const XmlAttribute *GetFirstAttribute() const;

		/**
		*  @brief
		*    Access the last attribute in this element
		*
		*  @return
		*    The last attribute, NULL if there's no last attribute
		*/
		PLGENERAL_API XmlAttribute *GetLastAttribute();
		PLGENERAL_API const XmlAttribute *GetLastAttribute() const;


	//[-------------------------------------------------------]
	//[ Public virtual XmlBase functions                      ]
	//[-------------------------------------------------------]
	public:
		PLGENERAL_API virtual bool Save(File &cFile, uint32 nDepth = 0);
		PLGENERAL_API virtual String ToString(uint32 nDepth = 0);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pNode
		*    Internal node pointer (always valid!)
		*  @param[in] nDummy
		*    Dummy parameter
		*/
		XmlElement(void *pNode, int nDummy);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_XML_ELEMENT_H__
