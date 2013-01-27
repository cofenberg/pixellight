/*********************************************************\
 *  File: MyRTTIClass.h                                  *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
