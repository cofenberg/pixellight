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


#ifndef __PLSCRIPTANGELSCRIPT_SCRIPT_H__
#define __PLSCRIPTANGELSCRIPT_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Script/Script.h>
#include "PLScriptAngelScript/PLScriptAngelScript.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class asIScriptModule;
class asIScriptEngine;
class asIScriptGeneric;
class asIScriptContext;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptAngelScript {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    AngelScript (http://www.angelcode.com/angelscript/) script implementation
*/
class Script : public PLCore::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTANGELSCRIPT_RTTI_EXPORT, Script, "PLScriptAngelScript", PLCore::Script, "AngelScript (http://www.angelcode.com/angelscript/) script implementation")
		// Properties
		pl_properties
			pl_property("Language",	"AngelScript")
			pl_property("Formats",	"as,AS")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLSCRIPTANGELSCRIPT_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTANGELSCRIPT_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Script functions               ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTANGELSCRIPT_API virtual bool IsGlobalFunction(const PLGeneral::String &sName);
		PLSCRIPTANGELSCRIPT_API virtual bool AddGlobalFunction(const PLGeneral::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLGeneral::String &sNamespace = "");
		PLSCRIPTANGELSCRIPT_API virtual bool RemoveAllGlobalFunctions();

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTANGELSCRIPT_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTANGELSCRIPT_API virtual const PLGeneral::Array<PLGeneral::String> &GetGlobalVariables();
		PLSCRIPTANGELSCRIPT_API virtual bool IsGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTANGELSCRIPT_API virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLGeneral::String &sName);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::String GetGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTANGELSCRIPT_API virtual void SetGlobalVariable(const PLGeneral::String &sName, const PLCore::DynVar &cValue);

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		PLSCRIPTANGELSCRIPT_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(bool bValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(float fValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(double fValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::int8 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::int16 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::int32 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::int64 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::uint64 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(const PLGeneral::String &sString);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::Object *pObject);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::Object &cObject);
		PLSCRIPTANGELSCRIPT_API virtual bool EndCall();
		PLSCRIPTANGELSCRIPT_API virtual bool GetReturn(bool nValue);
		PLSCRIPTANGELSCRIPT_API virtual float GetReturn(float nValue);
		PLSCRIPTANGELSCRIPT_API virtual double GetReturn(double nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::int8 GetReturn(PLGeneral::int8 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::int16 GetReturn(PLGeneral::int16 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::int32 GetReturn(PLGeneral::int32 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::int64 GetReturn(PLGeneral::int64 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::uint8 GetReturn(PLGeneral::uint8 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::uint16 GetReturn(PLGeneral::uint16 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::uint32 GetReturn(PLGeneral::uint32 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::uint64 GetReturn(PLGeneral::uint64 nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::String GetReturn(PLGeneral::String nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLCore::Object *GetReturn(PLCore::Object *nValue);
		PLSCRIPTANGELSCRIPT_API virtual PLCore::Object &GetReturn(PLCore::Object &nValue);


	//[-------------------------------------------------------]
	//[ Private static AngelScript callback functions         ]
	//[-------------------------------------------------------]
	private:
		/*
		*  @brief
		*    AngelScript function callback
		*
		*  @param[in] pAngelScriptGeneric
		*    AngelScript generic
		*/
		static void AngelScriptFunctionCallback(asIScriptGeneric *pAngelScriptGeneric);


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
		*    Gets a AngelScript function declaration
		*
		*  @param[in] sFunctionName
		*    Name of the function
		*  @param[in] sFunctionSignature
		*    Signature of the given dynamic parameters (e.g. "void(int,float)")
		*  @param[in] bCppToAngelScript
		*    Return a C++ to AngelScript function declaration
		*
		*  @return
		*    AngelScript function declaration (e.g. "void MyFunction(int,float)")
		*/
		PLGeneral::String GetAngelScriptFunctionDeclaration(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature, bool bCppToAngelScript) const;


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String					m_sSourceCode;			/**< Script source code */
		asIScriptEngine					   *m_pAngelScriptEngine;	/**< AngelScript engine instance, can be a null pointer, managed by AngelScriptContext */
		asIScriptModule					   *m_pAngelScriptModule;	/**< AngelScript module instance, can be a null pointer */
		asIScriptContext				   *m_pAngelScriptContext;	/**< AngelScript context instance, can be a null pointer */
		PLGeneral::uint32					m_nCurrentArgument;		/**< Current argument, used during function call */
		PLGeneral::Array<GlobalFunction*>   m_lstGlobalFunctions;	/**< List of global functions */
		PLGeneral::Array<PLGeneral::String> m_lstGlobalVariables;	/**< List of all global variables */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript


#endif // __PLSCRIPTANGELSCRIPT_SCRIPT_H__
