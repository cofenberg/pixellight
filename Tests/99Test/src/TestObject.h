/*********************************************************\
 *  File: TestObject.h                                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLSAMPLE_TESTOBJECT_H__
#define __PLSAMPLE_TESTOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include <PLCore/Base/ClassReal.h>
#include <PLCore/Base/Var/Var.h>
#include <PLCore/Base/Var/Attribute.h>
#include <PLCore/Base/Func/Method.h>
#include <PLCore/Base/Func/Signature.h>
#include <PLCore/Base/Func/Constructor.h>
#include <PLCore/Base/Event/Signal.h>
#include <PLCore/Base/Event/Slot.h>
#include <PLCore/Base/Rtti.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test object
*/
class TestObject : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI                                                  ]
	//[-------------------------------------------------------]
	/* All RTTI members are public */
	public:
		/*****************************************************/
		/* Class                                             */
		/*****************************************************/

		/* Class type */
		typedef TestObject _Self;

		/* Class description */
		class _Class : public PLCore::ClassReal {
			public:
				/* Singleton */
				static _Class *Instance;
				static bool Shutdown;

				/* Get class instance */
				static _Class *GetInstance() {
					if (!Instance && !Shutdown) Instance = new _Class();
					return Instance;
				}

				/* Destroy class instance (and prevent recreation) */
				static void RemoveInstance() {
					/* Make sure that the object won't be recreated */
					Shutdown = true;

					/* Destroy instance */
					if (Instance) {
						delete Instance;
						Instance = nullptr;
					}
				}

				/* Constructor */
				_Class() : ClassReal(PLCore::ModuleID<int>::GetModuleID(), "TestObject", "RTTI test class", "", "PLCore::Object") {
				};

				/* Destructor */
				virtual ~_Class() {
				};
		};

		/* Creation and destruction guard */
		class _Guard {
			public:
				/* Constructor */
				_Guard() {
					_Class::GetInstance();
				}

				/* Destructor */
				~_Guard() {
					/* Make sure that class instance is removed on shutdown */
					_Class::RemoveInstance();
				}
		};

		/* Public virtual PLCore::Object function */
		virtual PLCore::Class *GetClass() const override;


		/*****************************************************/
		/* Constructor                                       */
		/*****************************************************/

		/* Constructor descriptor (contains metadata like name, description etc.) */
		class Create_Desc : public PLCore::ConstructorDesc {
			public:
				typedef _Self							ClassType;
				typedef PLCore::Params<Object*>			ParamType;
				typedef PLCore::FuncConstructor<_Self>	ConstType;
				typedef PLCore::Signature<Object*>		SigType;

			public:
				Create_Desc() : PLCore::ConstructorDesc(SigType::GetSignatureID(), "Create", "Main constructor", "") {
					// Register constructor
					Register(_Class::GetInstance());
				}
				~Create_Desc() {
				}

			private:
				virtual PLCore::DynFunc *GetConstructor() const override {
					return const_cast<PLCore::DynFunc*>(reinterpret_cast<const PLCore::DynFunc*>(&m_Constructor));
				}
				virtual PLCore::Object *Create(const PLCore::DynParams &cConstParams) override {
					if (cConstParams.GetSignature() == m_Constructor.GetSignature()) {
						m_Constructor.Call(cConstParams);
						return ((ParamType&)cConstParams).Return;
					} else return nullptr;
				}
				ConstType m_Constructor;
		};

		/* Constructor */
		class Create_Const : public PLCore::Constructor<Create_Desc> {
			public:
				Create_Const() {
				}
		};


		/*****************************************************/
		/* Attribute 'BoolValue'                             */
		/*****************************************************/

		/* Attribute descriptor (contains metadata like name, description etc.) */
		class BoolValue_Desc : public PLCore::VarDesc {
			public:
				BoolValue_Desc() : PLCore::VarDesc(PLCore::Type<bool>::TypeID, PLCore::Type<bool>::GetTypeName(), "_BoolValue", "Boolean value", "") {
					// Register attribute
					Register(_Class::GetInstance());
				}
				~BoolValue_Desc() {
				}
			private:
				virtual PLCore::String GetDefault() const override {
					return PLCore::Type<bool>::ConvertToString(false);
				}
				virtual PLCore::DynVar *GetAttribute(const Object &cObject) const override {
					return &((TestObject&)cObject).BoolValue;
				}
		};

		/* Attribute class */
		class BoolValue_Attr : public PLCore::Attribute<bool, PLCore::AccessReadWrite, PLCore::StorageDirectValue, BoolValue_Desc> {
			public:
				BoolValue_Attr(Object *pObject) : PLCore::Attribute<bool, PLCore::AccessReadWrite, PLCore::StorageDirectValue, BoolValue_Desc>(true, pObject) {
				}
		};

		/* Attribute itself */
		BoolValue_Attr BoolValue;


		/*****************************************************/
		/* Attribute 'IntValue'                              */
		/*****************************************************/

		/* Attribute descriptor (contains metadata like name, description etc.) */
		class IntValue_Desc : public PLCore::VarDesc {
			public:
				IntValue_Desc() : PLCore::VarDesc(PLCore::Type<int>::TypeID, PLCore::Type<int>::GetTypeName(), "_IntValue", "Integer value #1", "") {
					// Register attribute
					Register(_Class::GetInstance());
				}
				~IntValue_Desc() {
				}
			private:
				virtual PLCore::String GetDefault() const override {
					return PLCore::Type<int>::ConvertToString(0);
				}
				virtual PLCore::DynVar *GetAttribute(const Object &cObject) const override {
					return &((TestObject&)cObject).IntValue;
				}
		};

		/* Attribute class */
		class IntValue_Attr : public PLCore::Attribute<int, PLCore::AccessReadWrite, PLCore::StorageDirectValue, IntValue_Desc> {
			public:
				IntValue_Attr(Object *pObject) : PLCore::Attribute<int, PLCore::AccessReadWrite, PLCore::StorageDirectValue, IntValue_Desc>(200, pObject) {
				}
		};

		/* Attribute itself */
		IntValue_Attr IntValue;


		/*****************************************************/
		/* Attribute 'IntValue2'                             */
		/*****************************************************/

		/* Attribute descriptor (contains metadata like name, description etc.) */
		class IntValue2_Desc : public PLCore::VarDesc {
			public:
				IntValue2_Desc() : PLCore::VarDesc(PLCore::Type<int>::TypeID, PLCore::Type<int>::GetTypeName(), "_IntValue2", "Integer value #2", "") {
					// Register attribute
					Register(_Class::GetInstance());
				}
				~IntValue2_Desc() {
				}
			private:
				virtual PLCore::String GetDefault() const override {
					return PLCore::Type<int>::ConvertToString(0);
				}
				virtual PLCore::DynVar *GetAttribute(const Object &cObject) const override {
					return &((TestObject&)cObject).IntValue2;
				}
		};

		/* Attribute class */
		class IntValue2_Attr : public PLCore::Attribute<int, PLCore::AccessReadOnly, PLCore::StorageDirectValue, IntValue2_Desc> {
			public:
				IntValue2_Attr(Object *pObject) : PLCore::Attribute<int, PLCore::AccessReadOnly, PLCore::StorageDirectValue, IntValue2_Desc>(10, pObject) {
				}
		};

		/* Attribute itself */
		IntValue2_Attr IntValue2;


		/*****************************************************/
		/* Method 'Test'                                     */
		/*****************************************************/
		private:	/* RTTI class methods are private to avoid misuse */
		/* Method descriptor (contains metadata like name and signature) */
		class MethodTest_Desc : public PLCore::FuncDesc {
			public:
				typedef _Self									ClassType;
				typedef PLCore::Functor<void>					FuncType;
				typedef PLCore::Signature<void>					SigType;
				typedef PLCore::MethodSignature<_Self, void>	MethType;

			public:
				MethodTest_Desc() : PLCore::FuncDesc(SigType::GetSignatureID(), "Test", "Test method", "") {
					// Register method
					Register(_Class::GetInstance());
				}
				~MethodTest_Desc() {
				}
				virtual PLCore::DynFuncPtr GetMethod(Object &cObject) const override {
					return new MethodTest_Method(reinterpret_cast<_Self&>(cObject));
				}
		};

		/* Method class */
		class MethodTest_Method : public PLCore::Method<MethodTest_Desc> {
			public:
				MethodTest_Method() : PLCore::Method<MethodTest_Desc>(&_Self::Test, nullptr) { /* There are no automatic RTTI class method instances per RTTI class instance because there's no need for it and this safes RTTI class instance memory */ \
				}
				MethodTest_Method(_Self &cObject) : PLCore::Method<MethodTest_Desc>(&_Self::Test, &cObject) {
				}
		};

		/* Method itself */
		static MethodTest_Method MethodTest;
		public:

		/*****************************************************/
		/* Event 'Event0'                                    */
		/*****************************************************/

		/* Event descriptor (contains metadata like name and signature) */
		class Event0_Desc : public PLCore::EventDesc {
			public:
				typedef _Self					ClassType;
				typedef PLCore::Event<>			EventType;
				typedef PLCore::Signature<void>	SigType;

			public:
				Event0_Desc() : PLCore::EventDesc(SigType::GetSignatureID(), "Event0", "Event #0", "") {
					// Register method
					Register(_Class::GetInstance());
				}
				~Event0_Desc() {
				}
			private:
				virtual PLCore::DynEvent *GetSignal(const Object &cObject) const override {
					return &((TestObject&)cObject).Event0;
				}
		};

		/* Event class */
		class Event0_Event : public PLCore::Signal<Event0_Desc> {
			public:
				Event0_Event() : PLCore::Signal<Event0_Desc>() {
				}
		};

		/* Method itself */
		Event0_Event Event0;


		/*****************************************************/
		/* EventHandler 'EventHandler0'                      */
		/*****************************************************/

		/* Event handler descriptor (contains metadata like name and signature) */
		class EventHandler0_Desc : public PLCore::EventHandlerDesc {
			public:
				typedef _Self									ClassType;
				typedef PLCore::EventHandler<>					EventHandlerType;
				typedef PLCore::Signature<void>					SigType;
				typedef PLCore::MethodSignature<_Self, void>	MethType;

			public:
				EventHandler0_Desc() : PLCore::EventHandlerDesc(SigType::GetSignatureID(), "EventHandler0", "Event handler #0", "") {
					// Register event handler
					Register(_Class::GetInstance());
				}
				~EventHandler0_Desc() {
				}
			private:
				virtual PLCore::DynEventHandler *GetSlot(const Object &cObject) const override {
					return &((TestObject&)cObject).EventHandler0;
				}
		};

		/* Event handler class */
		class EventHandler0_EventHandler : public PLCore::Slot<EventHandler0_Desc> {
			public:
				EventHandler0_EventHandler(_Self *pObject) : PLCore::Slot<EventHandler0_Desc>(&_Self::Test, pObject) {
				}
		};

		/* Method itself */
		EventHandler0_EventHandler EventHandler0;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		TestObject();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TestObject();

		/**
		*  @brief
		*    Test function
		*/
		void Test();


};


#endif // __PLSAMPLE_TESTOBJECT_H__
