/*********************************************************\
 *  File: TestObject.h                                   *
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


#ifndef __PLSAMPLE_TESTOBJECT_H__
#define __PLSAMPLE_TESTOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include <PLCore/Base/Class.h>
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
		class _Class : public PLCore::Class {
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
				_Class() : Class(PLCore::ModuleID<int>::GetModuleID(), "TestObject", "RTTI test class", "", "PLCore::Object") {
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
		virtual PLCore::Class *GetClass() const;


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
				virtual PLCore::DynFunc *GetConstructor() {
					return &m_Constructor;
				}
				virtual PLCore::Object *Create(PLCore::DynParams &cParams) {
					if (cParams.GetSignature() == m_Constructor.GetSignature()) {
						m_Constructor.Call(cParams);
						return ((ParamType&)cParams).Return;
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
				virtual PLCore::DynVar *GetAttribute(const Object *pObject) {
					return &((TestObject*)pObject)->BoolValue;
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
				virtual PLCore::DynVar *GetAttribute(const Object *pObject) {
					return &((TestObject*)pObject)->IntValue;
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
				virtual PLCore::DynVar *GetAttribute(const Object *pObject) {
					return &((TestObject*)pObject)->IntValue2;
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
			private:
				virtual PLCore::DynFunc *GetMethod(const Object *pObject) {
					return &((TestObject*)pObject)->MethodTest;
				}
		};

		/* Method class */
		class MethodTest_Method : public PLCore::Method<MethodTest_Desc> {
			public:
				MethodTest_Method(_Self *pObject) : PLCore::Method<MethodTest_Desc>(&_Self::Test, pObject) {
				}
		};

		/* Method itself */
		MethodTest_Method MethodTest;


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
				virtual PLCore::DynEvent *GetEvent(const Object *pObject) {
					return &((TestObject*)pObject)->Event0;
				}
		};

		/* Event class */
		class Event0_Event : public PLCore::Signal<Event0_Desc> {
			public:
				Event0_Event(_Self *pObject) : PLCore::Signal<Event0_Desc>(pObject) {
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
				virtual PLCore::DynEventHandler *GetEventHandler(const Object *pObject) {
					return &((TestObject*)pObject)->EventHandler0;
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
