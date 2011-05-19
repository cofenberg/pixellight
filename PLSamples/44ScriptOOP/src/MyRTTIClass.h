/*********************************************************\
 *  File: MyRTTIClass.h                                  *
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


#ifndef __PLSAMPLE_44_SCRIPTOOP_MYRTTICLASS_H__
#define __PLSAMPLE_44_SCRIPTOOP_MYRTTICLASS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sample RTTI class, don't take it to serious
*/
class MyRTTIClass : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MyRTTIClass, "", PLCore::Object, "Sample RTTI class, don't take it to serious")
		// Properties
		pl_properties
			pl_property("MyProperty", "This is a property value")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		// Methods
		pl_method_0(Return42,			int,			"Returns 42",						"")
		pl_method_1(IgnoreTheParameter,	void, float,	"Ignores the provided parameter",	"")
		pl_method_0(SaySomethingWise,	void,			"Says something wise",				"")
		// Signals
		pl_signal_1(MySignal, PLGeneral::String, "My signal, automatically emitted after the name was changed", "")
		// Slots
		pl_slot_0(OnMyEvent, "My slot", "")
		// Attributes
		pl_attribute(Name,	PLGeneral::String,	"Bob",	ReadWrite,	GetSet,			"A name, emits MySignal after the name was changed",			"")
		pl_attribute(Level,	int,				1,		ReadWrite,	DirectValue,	"Level, automatically increased on get/set name and OnMyEvent",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		int Return42();
		void IgnoreTheParameter(float fValue);
		void SaySomethingWise();


	//[-------------------------------------------------------]
	//[ Public RTTI slot methods                              ]
	//[-------------------------------------------------------]
	public:
		void OnMyEvent();


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLGeneral::String GetName();
		void SetName(const PLGeneral::String &sName);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		MyRTTIClass();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MyRTTIClass();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sName;


};


#endif // __PLSAMPLE_44_SCRIPTOOP_MYRTTICLASS_H__
