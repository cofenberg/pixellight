/*********************************************************\
 *  File: Script.h                                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
		PLSCRIPTANGELSCRIPT_API virtual bool IsGlobalFunction(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTANGELSCRIPT_API virtual bool AddGlobalFunction(const PLCore::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLCore::String &sNamespace = "") override;
		PLSCRIPTANGELSCRIPT_API virtual bool RemoveAllGlobalFunctions() override;

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		PLSCRIPTANGELSCRIPT_API virtual PLCore::String GetSourceCode() const override;
		PLSCRIPTANGELSCRIPT_API virtual bool SetSourceCode(const PLCore::String &sSourceCode) override;
		PLSCRIPTANGELSCRIPT_API virtual void GetAssociatedFilenames(PLCore::Array<PLCore::String> &lstFilenames) override;
		PLSCRIPTANGELSCRIPT_API virtual bool Execute(const PLCore::String &sSourceCode) override;

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTANGELSCRIPT_API virtual void GetGlobalVariables(PLCore::Array<PLCore::String> &lstGlobalVariables, const PLCore::String &sNamespace = "") override;
		PLSCRIPTANGELSCRIPT_API virtual bool IsGlobalVariable(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::String GetGlobalVariable(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTANGELSCRIPT_API virtual void SetGlobalVariable(const PLCore::String &sName, const PLCore::DynVar &cValue, const PLCore::String &sNamespace = "") override;

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		PLSCRIPTANGELSCRIPT_API virtual bool BeginCall(const PLCore::String &sFunctionName, const PLCore::String &sFunctionSignature, const PLCore::String &sNamespace = "") override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(bool bValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(float fValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(double fValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::int8 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::int16 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::int32 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::int64 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::uint8 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::uint16 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::uint32 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::uint64 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(const PLCore::String &sString) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::Object *pObject) override;
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLCore::Object &cObject) override;
		PLSCRIPTANGELSCRIPT_API virtual bool EndCall() override;
		PLSCRIPTANGELSCRIPT_API virtual bool GetReturn(bool nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual float GetReturn(float nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual double GetReturn(double nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::int8 GetReturn(PLCore::int8 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::int16 GetReturn(PLCore::int16 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::int32 GetReturn(PLCore::int32 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::int64 GetReturn(PLCore::int64 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::uint8 GetReturn(PLCore::uint8 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::uint16 GetReturn(PLCore::uint16 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::uint32 GetReturn(PLCore::uint32 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::uint64 GetReturn(PLCore::uint64 nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::String GetReturn(PLCore::String nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::Object *GetReturn(PLCore::Object *nValue) override;
		PLSCRIPTANGELSCRIPT_API virtual PLCore::Object &GetReturn(PLCore::Object &nValue) override;


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
		PLCore::String GetAngelScriptFunctionDeclaration(const PLCore::String &sFunctionName, const PLCore::String &sFunctionSignature, bool bCppToAngelScript) const;


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    A global function
		*/
		struct GlobalFunction {
			PLCore::String   sFunction;		/**< Function name used inside the script to call the global function */
			PLCore::DynFunc *pDynFunc;		/**< Dynamic function to be called, always valid, destroy when done */
			PLCore::String   sNamespace;	/**< Optional namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on) */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String					m_sSourceCode;			/**< Script source code */
		asIScriptEngine				   *m_pAngelScriptEngine;	/**< AngelScript engine instance, can be a null pointer, managed by AngelScriptContext */
		asIScriptModule				   *m_pAngelScriptModule;	/**< AngelScript module instance, can be a null pointer */
		asIScriptContext			   *m_pAngelScriptContext;	/**< AngelScript context instance, can be a null pointer */
		PLCore::uint32					m_nCurrentArgument;		/**< Current argument, used during function call */
		PLCore::Array<GlobalFunction*>  m_lstGlobalFunctions;	/**< List of global functions */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript


#endif // __PLSCRIPTANGELSCRIPT_SCRIPT_H__
