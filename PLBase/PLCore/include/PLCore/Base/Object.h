/*********************************************************\
 *  File: Object.h                                       *
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


#ifndef __PLCORE_OBJECT_H__
#define __PLCORE_OBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Xml/XmlElement.h>
#include <PLGeneral/Container/List.h>
#include "PLCore/PLCoreDefinitions.h"
#include "PLCore/Base/Object.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Base/Rtti.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Class;
	class DynVar;
	class DynFunc;
	class DynEvent;
	class DynEventHandler;
	class DynConstructor;
	class DynParams;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Internal Object base class
*/
class ObjectBase {
};


/**
*  @brief
*    Object base class
*/
class Object : public ObjectBase {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class_internal(Object, "PLCore", "", "Object base class")
		pl_properties
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API Object();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Object();

		//[-------------------------------------------------------]
		//[ Class and members                                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Get class
		*
		*  @return
		*    Class of the object ( should never be NULL, unless something is *terribly* wrong ;-) )
		*/
		PLCORE_API virtual Class *GetClass() const;

		/**
		*  @brief
		*    Check if object is instance of a given class
		*
		*  @param[in] cClass
		*    Class
		*
		*  @return
		*    'true' if the object is an instance of the class or one of it's derived classes, else 'false'
		*/
		PLCORE_API bool IsInstanceOf(const Class &cClass) const;

		/**
		*  @brief
		*    Check if object is instance of a given class
		*
		*  @param[in] sClass
		*    Class name (with namespace)
		*
		*  @return
		*    'true' if the object is an instance of the class or one of it's derived classes, else 'false'
		*/
		PLCORE_API bool IsInstanceOf(const PLGeneral::String &sClass) const;

		/**
		*  @brief
		*    Get attributes
		*
		*  @return
		*    List of attributes
		*
		*  @remarks
		*    Use this function with caution, as the list is assembled and copied each time the function is called!
		*    In general it is recommended to use GetClass()->GetAttributes() to obtain a list of attribute descriptors
		*    and then call GetAttribute() from the descriptor to get access to the actual attribute
		*/
		PLCORE_API const PLGeneral::List<DynVar*> GetAttributes() const;

		/**
		*  @brief
		*    Get attribute
		*
		*  @param[in] sName
		*    Attribute name
		*
		*  @return
		*    Attribute (can be NULL, if no attribute with that name could be found)
		*/
		PLCORE_API DynVar *GetAttribute(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get methods
		*
		*  @return
		*    List of methods
		*
		*  @remarks
		*    Use this function with caution, as the list is assembled and copied each time the function is called!
		*    In general it is recommended to use GetClass()->GetMethods() to obtain a list of method descriptors
		*    and then call GetMethod() from the descriptor to get access to the actual method
		*/
		PLCORE_API const PLGeneral::List<DynFunc*> GetMethods() const;

		/**
		*  @brief
		*    Get method
		*
		*  @param[in] sName
		*    Method name
		*
		*  @return
		*    Method (can be NULL, if no method with that name could be found)
		*/
		PLCORE_API DynFunc *GetMethod(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get signals
		*
		*  @return
		*    List of signals
		*
		*  @remarks
		*    Use this function with caution, as the list is assembled and copied each time the function is called!
		*    In general it is recommended to use GetClass()->GetSignals() to obtain a list of signal descriptors
		*    and then call GetSignal() from the descriptor to get access to the actual signal
		*/
		PLCORE_API const PLGeneral::List<DynEvent*> GetSignals() const;

		/**
		*  @brief
		*    Get signal
		*
		*  @param[in] sName
		*    Signal name
		*
		*  @return
		*    Signal (can be NULL, if no signal with that name could be found)
		*/
		PLCORE_API DynEvent *GetSignal(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get slots
		*
		*  @return
		*    List of slots
		*
		*  @remarks
		*    Use this function with caution, as the list is assembled and copied each time the function is called!
		*    In general it is recommended to use GetClass()->GetSlots() to obtain a list of slot descriptors
		*    and then call GetSlot() from the descriptor to get access to the actual slot
		*/
		PLCORE_API const PLGeneral::List<DynEventHandler*> GetSlots() const;

		/**
		*  @brief
		*    Get slot
		*
		*  @param[in] sName
		*    Slot name
		*
		*  @return
		*    Slot (can be NULL, if no slot with that name could be found)
		*/
		PLCORE_API DynEventHandler *GetSlot(const PLGeneral::String &sName) const;

		//[-------------------------------------------------------]
		//[ Direct access functions                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Set attribute value
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] sValue
		*    Attribute value
		*/
		PLCORE_API void SetAttribute(const PLGeneral::String &sName, const PLGeneral::String &sValue);

		/**
		*  @brief
		*    Set attribute value
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] pVar
		*    Attribute value
		*/
		PLCORE_API void SetAttribute(const PLGeneral::String &sName, const DynVar *pVar);

		/**
		*  @brief
		*    Set attribute to it's default value
		*
		*  @param[in] sName
		*    Attribute name
		*/
		PLCORE_API void SetAttributeDefault(const PLGeneral::String &sName);

		/**
		*  @brief
		*    Call method
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cParams
		*    Parameters
		*/
		PLCORE_API void CallMethod(const PLGeneral::String &sName, DynParams &cParams);

		/**
		*  @brief
		*    Call method
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cParams
		*    Parameters
		*/
		PLCORE_API void CallMethod(const PLGeneral::String &sName, const DynParams &cParams);

		/**
		*  @brief
		*    Call method
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] sParams
		*    Parameters as string
		*/
		PLCORE_API void CallMethod(const PLGeneral::String &sName, const PLGeneral::String &sParams);

		/**
		*  @brief
		*    Call method
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cElement
		*    Parameters as XML
		*/
		PLCORE_API void CallMethod(const PLGeneral::String &sName, const PLGeneral::XmlElement &cElement);

		//[-------------------------------------------------------]
		//[ Object state functions                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Get attribute values as a string
		*
		*  @param[in] nDefaultValue
		*    'WithDefault' to retrieve all attributes, 'NoDefault' to only retrieve attributes that are not set to default
		*
		*  @return
		*    String containing attributes and values
		*
		*  @remarks
		*    The returned string contains the attributes and their values.
		*    Example: "Name='Test' IntValue='10'"
		*/
		PLCORE_API PLGeneral::String GetValues(EDefaultValue nDefaultValue = NoDefault) const;

		/**
		*  @brief
		*    Set attribute values as a string
		*
		*  @param[in] sString
		*    String containing attributes and values
		*/
		PLCORE_API void SetValues(const PLGeneral::String &sVars);

		/**
		*  @brief
		*    Get attribute values as XML
		*
		*  @param[out] cElement
		*    XML element
		*  @param[in] nDefaultValue
		*    'WithDefault' to retrieve all attributes, 'NoDefault' to only retrieve attributes that are not set to default
		*
		*  @remarks
		*    The attributes and their values are added as XML-attributes to the given XML-element
		*/
		PLCORE_API void GetValuesXml(PLGeneral::XmlElement &cElement, EDefaultValue nDefaultValue = NoDefault) const;

		/**
		*  @brief
		*    Set attribute values from XML
		*
		*  @param[out] cElement
		*    XML element
		*
		*  @remarks
		*    The attributes and their values are read from the XML-attributes of the given XML-element
		*/
		PLCORE_API void SetValuesXml(const PLGeneral::XmlElement &cElement);

		/**
		*  @brief
		*    Set all attributes to default
		*/
		PLCORE_API void SetDefaultValues();


	//[-------------------------------------------------------]
	//[ Public virtual Object functions                       ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get object as string
		*
		*  @return
		*    String representation of object
		*/
		PLCORE_API virtual PLGeneral::String ToString() const;

		/**
		*  @brief
		*    Set object from string
		*
		*  @param[in] sString
		*    String representation of object
		*/
		PLCORE_API virtual void FromString(const PLGeneral::String &sString);

		/**
		*  @brief
		*    Get object as XML
		*
		*  @return
		*    XML representation of object
		*/
		PLCORE_API virtual PLGeneral::XmlElement ToXml() const;

		/**
		*  @brief
		*    Set object from XML
		*
		*  @param[in] cElement
		*    XML representation of object
		*/
		PLCORE_API virtual void FromXml(const PLGeneral::XmlElement &cElement);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_OBJECT_H__
