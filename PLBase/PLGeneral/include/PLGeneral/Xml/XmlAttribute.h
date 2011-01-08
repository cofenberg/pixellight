/*********************************************************\
 *  File: XmlAttribute.h                                 *
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


#ifndef __PLGENERAL_XML_ATTRIBUTE_H__
#define __PLGENERAL_XML_ATTRIBUTE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Xml/XmlBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class XmlDocument;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    XML element attribute
*
*  @remarks
*    An attribute is a name-value pair. Elements have an arbitrary
*    number of attributes, each with a unique name.
*/
class XmlAttribute : public XmlBase {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XmlElement;
	friend class XmlAttributeSet;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLGENERAL_API XmlAttribute();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~XmlAttribute();

		/**
		*  @brief
		*    Return the name of this attribute
		*
		*  @return
		*    Name of this attribute
		*/
		PLGENERAL_API String GetName() const;

		/**
		*  @brief
		*    Set the name of this attribute
		*
		*  @param[in] sName
		*    Name of this attribute to set
		*/
		PLGENERAL_API void SetName(const String &sName);

		/**
		*  @brief
		*    Return the value of this attribute
		*
		*  @return
		*    Value of this attribute
		*/
		PLGENERAL_API String GetValue() const;

		/**
		*  @brief
		*    Return the value of this attribute, converted to an integer
		*
		*  @return
		*    Value of this attribute, converted to an integer
		*/
		PLGENERAL_API int GetIntValue() const;

		/**
		*  @brief
		*    Return the value of this attribute, converted to a double
		*
		*  @return
		*    Value of this attribute, converted to a double
		*/
		PLGENERAL_API double GetDoubleValue() const;

		/**
		*  @brief
		*    Examines the value string
		*
		*  @param[out] nValue
		*    Will receive the integer value if all went fine, if not, this variable is not touched
		*
		*  @return
		*    If the attribute value is not an integer, it returns 'WrongType'. Returns
		*    'Success' on success.
		*
		*  @remarks
		*    It is an alternative to the 'GetIntValue()'-function with richer error checking.
		*    If the value is an integer, it is stored in 'value' and the call returns
		*    'Success'. If it is not an integer, it returns 'WrongType'.
		*    A specialized but useful call. Note that for success it returns 'Success',
		*    which is the opposite of almost all other parser calls.
		*/
		PLGENERAL_API EQueryResult QueryIntValue(int &nValue) const;

		/**
		*  @brief
		*    Examines the value string
		*
		*  @param[out] dValue
		*    Will receive the double value if all went fine, if not, this variable is not touched
		*
		*  @return
		*    If the attribute value is not an integer, it returns 'WrongType'. Returns
		*    'Success' on success.
		*
		*  @see
		*    - QueryIntValue()
		*/
		PLGENERAL_API EQueryResult QueryDoubleValue(double &dValue) const;

		/**
		*  @brief
		*    Set the value
		*
		*  @param[in] sValue
		*    Attribute value to set
		*/
		PLGENERAL_API void SetValue(const String &sValue);

		/**
		*  @brief
		*    Set the value from an integer
		*
		*  @param[in] nValue
		*    Attribute integer value to set
		*/
		PLGENERAL_API void SetIntValue(int nValue);

		/**
		*  @brief
		*    Set the value from a double
		*
		*  @param[in] dValue
		*    Attribute double value to set
		*/
		PLGENERAL_API void SetDoubleValue(double dValue);

		/**
		*  @brief
		*    Get the next sibling attribute in the DOM
		*
		*  @return
		*    The next sibling attribute in the DOM, a null pointer at end
		*/
		PLGENERAL_API XmlAttribute *GetNext();
		PLGENERAL_API const XmlAttribute *GetNext() const;

		/**
		*  @brief
		*    Get the previous sibling attribute in the DOM
		*
		*  @return
		*    The previous sibling attribute in the DOM, a null pointer at beginning
		*/
		PLGENERAL_API XmlAttribute *GetPrevious();
		PLGENERAL_API const XmlAttribute *GetPrevious() const;

		/**
		*  @brief
		*    Compare functions
		*
		*  @param[in] cOther
		*    Other attribute to compare with
		*
		*  @return
		*    'true' if the condition is fulfilled, else 'false'
		*/
		PLGENERAL_API bool operator ==(const XmlAttribute &cOther) const;
		PLGENERAL_API bool operator <(const XmlAttribute &cOther) const;
		PLGENERAL_API bool operator >(const XmlAttribute &cOther) const;


	//[-------------------------------------------------------]
	//[ Public virtual XmlBase functions                      ]
	//[-------------------------------------------------------]
	public:
		PLGENERAL_API virtual bool Save(File &cFile, uint32 nDepth = 0);
		PLGENERAL_API virtual String ToString(uint32 nDepth = 0) const;
		PLGENERAL_API const char *Parse(const char *pszData, XmlParsingData *pData = nullptr, EEncoding nEncoding = EncodingUnknown);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		XmlAttribute(const XmlAttribute &cSource);

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
		XmlAttribute &operator =(const XmlAttribute &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		XmlDocument  *m_pDocument;			/**< A pointer back to a document, for error reporting, can be a null pointer */
		String		  m_sName;				/**< Name */
		String		  m_sValue;				/**< Value */
		XmlAttribute *m_pPreviousAttribute;	/**< Previous attribute, can be a null pointer */
		XmlAttribute *m_pNextAttribute;		/**< Next attribute, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_XML_ATTRIBUTE_H__
