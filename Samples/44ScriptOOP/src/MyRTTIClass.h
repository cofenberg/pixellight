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
			pl_property("MyProperty",	"This is a property value")
		pl_properties_end
		// Attributes
		pl_attribute(Name,	PLCore::String,		"Bob",	ReadWrite,	GetSet,			"A name, emits MySignal after the name was changed",			"")
		pl_attribute(Level,	int,				1,		ReadWrite,	DirectValue,	"Level, automatically increased on get/set name and OnMyEvent",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_0(Return42,			pl_ret_type(int),					"Returns 42",							"")
		pl_method_1(IgnoreTheParameter,	pl_ret_type(void),			float,	"Ignores the provided parameter",		"")
		pl_method_0(SaySomethingWise,	pl_ret_type(void),					"Says something wise",					"")
		pl_method_0(GetSelf,			pl_ret_type(MyRTTIClass*),			"Returns a pointer to this instance",	"")
		// Signals
		pl_signal_1(MySignal,	PLCore::String,	"My signal, automatically emitted after the name was changed, message as first parameter",	"")
		// Slots
		pl_slot_1(OnMyEvent,	PLCore::String,	"My slot, message as first parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::String GetName();
		void SetName(const PLCore::String &sName);


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

		/**
		*  @brief
		*    Returns 42
		*
		*  @return
		*    42
		*/
		int Return42() const;

		/**
		*  @brief
		*    Ignores the provided parameter
		*
		*  @param[in] fValue
		*    Parameter to ignore
		*/
		void IgnoreTheParameter(float fValue) const;

		/**
		*  @brief
		*    Says something wise
		*/
		void SaySomethingWise() const;

		/**
		*  @brief
		*    Returns a pointer to this instance
		*
		*  @return
		*    A pointer to this instance, always valid!
		*/
		MyRTTIClass *GetSelf();

		/**
		*  @brief
		*    Called when my event was emitted
		*
		*  @param[in] sMessage
		*    Message
		*/
		void OnMyEvent(PLCore::String sMessage);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sName;


};


#endif // __PLSAMPLE_44_SCRIPTOOP_MYRTTICLASS_H__
