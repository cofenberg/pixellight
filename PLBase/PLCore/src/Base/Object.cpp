/*********************************************************\
 *  File: Object.cpp                                     *
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
#include <PLGeneral/Xml/Xml.h>
#include "PLCore/Base/Var/VarDesc.h"
#include "PLCore/Base/Var/DynVar.h"
#include "PLCore/Base/Func/FuncDesc.h"
#include "PLCore/Base/Func/DynFunc.h"
#include "PLCore/Base/Event/EventDesc.h"
#include "PLCore/Base/Event/EventHandlerDesc.h"
#include "PLCore/Base/Event/DynEvent.h"
#include "PLCore/Base/Event/DynEventHandler.h"
#include "PLCore/Base/Tools/ParamsParser.h"
#include "PLCore/Base/Tools/ParamsParserXml.h"
#include "PLCore/Base/ClassManager.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Base/Object.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Rtti interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Object)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Object::Object()
{
}

/**
*  @brief
*    Destructor
*/
Object::~Object()
{
}

/**
*  @brief
*    Get class
*/
Class *Object::GetClass() const
{
	// Return class for PLCore::Object
	return _Class::GetSingleton();
}

/**
*  @brief
*    Check if object is instance of a given class
*/
bool Object::IsInstanceOf(const Class &cClass) const
{
	// Get class
	const Class *pClass = GetClass();
	if (pClass) {
		// Same class?
		if (pClass == &cClass) {
			return true;
		} else {
			// Check if class is derived from given class
			return pClass->IsDerivedFrom(cClass);
		}
	}

	// Class could not be found
	return false;
}

/**
*  @brief
*    Check if object is instance of a given class
*/
bool Object::IsInstanceOf(const String &sClass) const
{
	// Get class
	const Class *pClass = ClassManager::GetInstance()->GetClass(sClass);
	if (pClass) {
		// Check class
		return IsInstanceOf(*pClass);
	}

	// Class could not be found
	return false;
}

/**
*  @brief
*    Get attributes
*/
const List<DynVar*> Object::GetAttributes() const
{
	// Create attribute list
	List<DynVar*> lstAttributes;

	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor list
		const Container<VarDesc*> &lstDescriptors = pClass->GetAttributes();

		// Get all attributes for this instance and add them to the list
		for (uint32 i=0; i<lstDescriptors.GetNumOfElements(); i++) {
			lstAttributes.Add( lstDescriptors[i]->GetAttribute(this) );
		}
	}

	// Return attribute list
	return lstAttributes;
}

/**
*  @brief
*    Get attribute
*/
DynVar *Object::GetAttribute(const String &sName) const
{
	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor
		const VarDesc *pDescriptor = pClass->GetAttribute(sName);
		if (pDescriptor) {
			// Return attribute
			return pDescriptor->GetAttribute(this);
		}
	}

	// Could not find attribute
	return NULL;
}

/**
*  @brief
*    Get methods
*/
const List<DynFunc*> Object::GetMethods() const
{
	// Create method list
	List<DynFunc*> lstMethods;

	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor list
		const Container<FuncDesc*> &lstDescriptors = pClass->GetMethods();

		// Get all methods for this instance and add them to the list
		for (uint32 i=0; i<lstDescriptors.GetNumOfElements(); i++) {
			lstMethods.Add( lstDescriptors[i]->GetMethod(this) );
		}
	}

	// Return method list
	return lstMethods;
}

/**
*  @brief
*    Get method
*/
DynFunc *Object::GetMethod(const String &sName) const
{
	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor
		const FuncDesc *pDescriptor = pClass->GetMethod(sName);
		if (pDescriptor) {
			// Return method
			return pDescriptor->GetMethod(this);
		}
	}

	// Could not find method
	return NULL;
}

/**
*  @brief
*    Get signals
*/
const List<DynEvent*> Object::GetSignals() const
{
	// Create signal list
	List<DynEvent*> lstSignals;

	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor list
		const Container<EventDesc*> &lstDescriptors = pClass->GetSignals();

		// Get all signals for this instance and add them to the list
		for (uint32 i=0; i<lstDescriptors.GetNumOfElements(); i++) {
			lstSignals.Add( lstDescriptors[i]->GetSignal(this) );
		}
	}

	// Return signal list
	return lstSignals;
}

/**
*  @brief
*    Get signal
*/
DynEvent *Object::GetSignal(const String &sName) const
{
	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor
		const EventDesc *pDescriptor = pClass->GetSignal(sName);
		if (pDescriptor) {
			// Return signal
			return pDescriptor->GetSignal(this);
		}
	}

	// Could not find signal
	return NULL;
}

/**
*  @brief
*    Get slots
*/
const List<DynEventHandler*> Object::GetSlots() const
{
	// Create slot list
	List<DynEventHandler*> lstSlots;

	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor list
		const Container<EventHandlerDesc*> &lstDescriptors = pClass->GetSlots();

		// Get all slots for this instance and add them to the list
		for (uint32 i=0; i<lstDescriptors.GetNumOfElements(); i++) {
			lstSlots.Add( lstDescriptors[i]->GetSlot(this) );
		}
	}

	// Return slot list
	return lstSlots;
}

/**
*  @brief
*    Get slot
*/
DynEventHandler *Object::GetSlot(const String &sName) const
{
	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Get descriptor
		const EventHandlerDesc *pDescriptor = pClass->GetSlot(sName);
		if (pDescriptor) {
			// Return slot
			return pDescriptor->GetSlot(this);
		}
	}

	// Could not find slot
	return NULL;
}

/**
*  @brief
*    Set attribute value
*/
void Object::SetAttribute(const String &sName, const String &sValue)
{
	// Get attribute
	DynVar *pAttribute = GetAttribute(sName);
	if (pAttribute) {
		// Set value
		pAttribute->SetString(sValue);
	}
}

/**
*  @brief
*    Set attribute value
*/
void Object::SetAttribute(const String &sName, const DynVar *pVar)
{
	// Get attribute
	DynVar *pAttribute = GetAttribute(sName);
	if (pAttribute) {
		// Set value
		pAttribute->SetVar(pVar);
	}
}

/**
*  @brief
*    Set attribute to it's default value
*/
void Object::SetAttributeDefault(const String &sName)
{
	// Get attribute
	DynVar *pAttribute = GetAttribute(sName);
	if (pAttribute) {
		// Set default value
		pAttribute->SetDefault();
	}
}

/**
*  @brief
*    Call method
*/
void Object::CallMethod(const String &sName, DynParams &cParams)
{
	// Get method
	DynFunc *pMethod = GetMethod(sName);
	if (pMethod) {
		// Call method
		pMethod->Call(cParams);
	}
}

/**
*  @brief
*    Call method
*/
void Object::CallMethod(const String &sName, const DynParams &cParams)
{
	// Get method
	DynFunc *pMethod = GetMethod(sName);
	if (pMethod) {
		// Call method
		pMethod->Call(cParams);
	}
}

/**
*  @brief
*    Call method
*/
void Object::CallMethod(const String &sName, const String &sParams)
{
	// Get method
	DynFunc *pMethod = GetMethod(sName);
	if (pMethod) {
		// Call method
		pMethod->Call(sParams);
	}
}

/**
*  @brief
*    Call method
*/
void Object::CallMethod(const String &sName, const XmlElement &cElement)
{
	// Get method
	DynFunc *pMethod = GetMethod(sName);
	if (pMethod) {
		// Call method
		pMethod->Call(cElement);
	}
}

/**
*  @brief
*    Get attribute values as a string
*/
String Object::GetValues(EDefaultValue nDefaultValue) const
{
	// Init string
	String sVars;

	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Loop through attributes
		const Container<VarDesc*> &lstDescriptors = pClass->GetAttributes();
		Iterator<VarDesc*> cIterator = lstDescriptors.GetIterator();
		while (cIterator.HasNext()) {
			// Get attribute descriptor
			VarDesc *pVarDesc = cIterator.Next();
			if (pVarDesc) {
				// Get attribute
				DynVar *pVar = pVarDesc->GetAttribute(this);

				// Ignore variables with default values?
				if (nDefaultValue == WithDefault || !pVar->IsDefault()) {
					// Add attribute to string
					if (sVars.GetLength() > 0) sVars += " ";
					sVars += pVarDesc->GetName();
					sVars += "=\"";
					sVars += pVar->GetString();
					sVars += "\"";
				}
			}
		}
	}

	// Return string
	return sVars;
}

/**
*  @brief
*    Set attribute values as a string
*/
void Object::SetValues(const String &sVars)
{
	// Parse parameters
	ParamsParser cParams;
	cParams.ParseString(sVars);
	while (cParams.HasParam()) {
		// Set attribute
		SetAttribute(cParams.GetName(), cParams.GetValue());

		// Next parameter
		cParams.Next();
	}
}

/**
*  @brief
*    Get attribute values as XML
*/
void Object::GetValuesXml(XmlElement &cElement, EDefaultValue nDefaultValue) const
{
	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Loop through attributes
		const Container<VarDesc*> &lstDescriptors = pClass->GetAttributes();
		Iterator<VarDesc*> cIterator = lstDescriptors.GetIterator();
		while (cIterator.HasNext()) {
			// Get attribute descriptor
			VarDesc *pVarDesc = cIterator.Next();
			if (pVarDesc) {
				// Get attribute
				DynVar *pVar = pVarDesc->GetAttribute(this);

				// Ignore variables with default values?
				if (nDefaultValue == WithDefault || !pVar->IsDefault()) {
					// Add attribute to XML element
					cElement.SetAttribute(pVarDesc->GetName(), pVar->GetString());
				}
			}
		}
	}
}

/**
*  @brief
*    Set attribute values from XML
*/
void Object::SetValuesXml(const XmlElement &cElement)
{
	// Parse parameters
	ParamsParserXml cParams;
	cParams.ParseXml(cElement);
	while (cParams.HasParam()) {
		// Set attribute
		SetAttribute(cParams.GetName(), cParams.GetValue());

		// Next parameter
		cParams.Next();
	}
}

/**
*  @brief
*    Set all attributes to default
*/
void Object::SetDefaultValues()
{
	// Get class
	Class *pClass = GetClass();
	if (pClass) {
		// Loop through attributes
		const Container<VarDesc*> &lstDescriptors = pClass->GetAttributes();
		Iterator<VarDesc*> cIterator = lstDescriptors.GetIterator();
		while (cIterator.HasNext()) {
			// Get attribute descriptor
			VarDesc *pVarDesc = cIterator.Next();
			if (pVarDesc) {
				// Get attribute
				DynVar *pVar = pVarDesc->GetAttribute(this);

				// Set default value
				pVar->SetDefault();
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual Object functions                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get object as string
*/
String Object::ToString() const
{
	// Get attributes
	return GetValues(WithDefault);
}

/**
*  @brief
*    Set object from string
*/
void Object::FromString(const String &sString)
{
	// Set attributes
	SetValues(sString);
}

/**
*  @brief
*    Get object as XML
*/
XmlElement Object::ToXml() const
{
	// Create XML element
	XmlElement cElement(GetClass()->GetClassName());
	GetValuesXml(cElement, WithDefault);
	return cElement;
}

/**
*  @brief
*    Set object from XML
*/
void Object::FromXml(const XmlElement &cElement)
{
	// Check if XML element has the class name as it's name
	if (cElement.GetValue() == GetClass()->GetClassName()) {
		// Set attributes from XML
		SetValuesXml(cElement);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
