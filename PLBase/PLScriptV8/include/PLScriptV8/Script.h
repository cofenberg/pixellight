/*********************************************************\
 *  File: Script.h                                       *
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


#ifndef __PLSCRIPTV8_SCRIPT_H__
#define __PLSCRIPTV8_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4127) // "conditional expression is constant" (within "v8.h")
	#include <V8/v8.h>
PL_WARNING_POP
#include <PLScript/Script.h>
#include "PLScriptV8/PLScriptV8.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptV8 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    V8 (ECMA-262 compliant JavaScript engine, see http://code.google.com/p/v8/) script implementation
*/
class Script : public PLScript::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTV8_RTTI_EXPORT, Script, "PLScriptV8", PLScript::Script, "V8 (ECMA-262 compliant JavaScript engine, see http://code.google.com/p/v8/) script implementation")
		pl_properties
			pl_property("Language", "JavaScript")
			pl_property("Formats",  "js,JS")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLSCRIPTV8_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTV8_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLScript::Script functions             ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual bool AddGlobalFunction(const PLGeneral::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLGeneral::String &sNamespace = "");
		PLSCRIPTV8_API virtual bool RemoveAllGlobalFunctions();

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTV8_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual const PLGeneral::Array<PLGeneral::String> &GetGlobalVariables();
		PLSCRIPTV8_API virtual bool IsGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTV8_API virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLGeneral::String &sName);
		PLSCRIPTV8_API virtual PLGeneral::String GetGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTV8_API virtual void SetGlobalVariable(const PLGeneral::String &sName, const PLCore::DynVar &cValue);

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		PLSCRIPTV8_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTV8_API virtual void PushArgument(bool bValue);
		PLSCRIPTV8_API virtual void PushArgument(float fValue);
		PLSCRIPTV8_API virtual void PushArgument(double fValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::int8 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::int16 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::int32 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::int64 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::uint64 nValue);
		PLSCRIPTV8_API virtual void PushArgument(const PLGeneral::String &sString);
		PLSCRIPTV8_API virtual void PushArgument(PLCore::Object *pObject);
		PLSCRIPTV8_API virtual bool EndCall();
		PLSCRIPTV8_API virtual void GetReturn(bool *pbValue);
		PLSCRIPTV8_API virtual void GetReturn(float *pfValue);
		PLSCRIPTV8_API virtual void GetReturn(double *pfValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::int8 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::int16 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::int32 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::int64 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::uint8 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::uint16 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::uint32 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::uint64 *pnValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::String *psValue);
		PLSCRIPTV8_API virtual void GetReturn(PLCore::Object **ppObject);


	//[-------------------------------------------------------]
	//[ Private static V8 callback functions                  ]
	//[-------------------------------------------------------]
	private:
		/*
		*  @brief
		*    V8 function callback
		*
		*  @param[in] vV8Arguments
		*    V8 arguments
		*
		*  @return
		*    V8 function result
		*/
		static v8::Handle<v8::Value> V8FunctionCallback(const v8::Arguments &vV8Arguments);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    A global function
		*/
		struct GlobalFunction {
			PLGeneral::String  sFunction;	/**< Function name used inside the script to call the global function */
			PLCore::DynFunc   *pDynFunc;	/**< Dynamic function to be called, always valid, destroy when done */
			PLGeneral::String  sNamespace;	/**< Optional namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on) */
		};

		/**
		*  @brief
		*    V8 namespace
		*/
		class V8Namespace {
			public:
				v8::Local<v8::ObjectTemplate>						cV8ObjectTemplate;	/**< V8 object template representing this namespace */
				PLGeneral::HashMap<PLGeneral::String, V8Namespace > mapNamespaces;		/**< Map of nested namespaces */
				bool operator ==(const V8Namespace &cOther) { return false; }
		};


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
		Script(const Script &cSource);

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
		Script &operator =(const Script &cSource);

		/**
		*  @brief
		*    Clears the script
		*/
		void Clear();

		/**
		*  @brief
		*    Write a string into the log
		*
		*  @param[in] nLogLevel
		*    Log level
		*  @param[in] sText
		*    Text which should be written into the log
		*  @param[in] cTryCatch
		*    "v8::TryCatch" instance
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    The text is written to the log only if the current
		*    log level is greater or equal to the specified value.
		*    This method is an extension of "PLGeneral::Log::Output()"
		*    which also adds the name of the script to the given
		*    text and the "v8::TryCatch" line and expection.
		*/
		bool LogOutputTryCatch(PLGeneral::uint8 nLogLevel, const PLGeneral::String &sText, const v8::TryCatch &cTryCatch);

		/**
		*  @brief
		*    Adds a V8 function
		*
		*  @param[in] cV8Namespace
		*    Current V8 namespace
		*  @param[in] sFunction
		*    Name of the function
		*  @param[in] cV8Function
		*    V8 function to add
		*  @param[in] sNamespace
		*    Namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on)
		*/
		void AddV8Function(V8Namespace &cV8Namespace, const PLGeneral::String &sFunction, v8::Local<v8::ObjectTemplate> cV8Function, const PLGeneral::String &sNamespace) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String							 m_sSourceCode;			/**< Script source code */
		v8::Persistent<v8::Context>					 m_cV8Context;			/**< V8 context */
		PLGeneral::String							 m_sCurrentFunction;	/**< Name of the current function */
		v8::Persistent<v8::Value>					 m_cV8CurrentResult;	/**< Current V8 function */
		PLGeneral::Array<v8::Persistent<v8::Value> > m_lstV8Arguments;		/**< Current V8 arguments */
		PLGeneral::Array<GlobalFunction*>			 m_lstGlobalFunctions;	/**< List of global functions */
		PLGeneral::Array<PLGeneral::String>			 m_lstGlobalVariables;	/**< List of all global variables */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptV8


#endif // __PLSCRIPTV8_SCRIPT_H__
