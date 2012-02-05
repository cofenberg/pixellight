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


#ifndef __PLSCRIPTNULL_SCRIPT_H__
#define __PLSCRIPTNULL_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Script/Script.h>
#include "PLScriptNull/PLScriptNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null script implementation
*/
class Script : public PLCore::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTNULL_RTTI_EXPORT, Script, "PLScriptNull", PLCore::Script, "Null script implementation")
		// Properties
		pl_properties
			pl_property("Language",	"Null")
			pl_property("Formats",	"")		// The null backend has no load and runnable scripts
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
		PLSCRIPTNULL_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTNULL_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Script functions               ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual bool IsGlobalFunction(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTNULL_API virtual bool AddGlobalFunction(const PLCore::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLCore::String &sNamespace = "") override;
		PLSCRIPTNULL_API virtual bool RemoveAllGlobalFunctions() override;

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual PLCore::String GetSourceCode() const override;
		PLSCRIPTNULL_API virtual bool SetSourceCode(const PLCore::String &sSourceCode) override;
		PLSCRIPTNULL_API virtual void GetAssociatedFilenames(PLCore::Array<PLCore::String> &lstFilenames) override;
		PLSCRIPTNULL_API virtual bool Execute(const PLCore::String &sSourceCode) override;

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual void GetGlobalVariables(PLCore::Array<PLCore::String> &lstGlobalVariables, const PLCore::String &sNamespace = "") override;
		PLSCRIPTNULL_API virtual bool IsGlobalVariable(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTNULL_API virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTNULL_API virtual PLCore::String GetGlobalVariable(const PLCore::String &sName, const PLCore::String &sNamespace = "") override;
		PLSCRIPTNULL_API virtual void SetGlobalVariable(const PLCore::String &sName, const PLCore::DynVar &cValue, const PLCore::String &sNamespace = "") override;

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual bool BeginCall(const PLCore::String &sFunctionName, const PLCore::String &sFunctionSignature, const PLCore::String &sNamespace = "") override;
		PLSCRIPTNULL_API virtual void PushArgument(bool bValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(float fValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(double fValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::int8 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::int16 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::int32 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::int64 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::uint8 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::uint16 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::uint32 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::uint64 nValue) override;
		PLSCRIPTNULL_API virtual void PushArgument(const PLCore::String &sString) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::Object *pObject) override;
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::Object &cObject) override;
		PLSCRIPTNULL_API virtual bool EndCall() override;
		PLSCRIPTNULL_API virtual bool GetReturn(bool nValue) override;
		PLSCRIPTNULL_API virtual float GetReturn(float nValue) override;
		PLSCRIPTNULL_API virtual double GetReturn(double nValue) override;
		PLSCRIPTNULL_API virtual PLCore::int8 GetReturn(PLCore::int8 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::int16 GetReturn(PLCore::int16 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::int32 GetReturn(PLCore::int32 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::int64 GetReturn(PLCore::int64 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::uint8 GetReturn(PLCore::uint8 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::uint16 GetReturn(PLCore::uint16 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::uint32 GetReturn(PLCore::uint32 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::uint64 GetReturn(PLCore::uint64 nValue) override;
		PLSCRIPTNULL_API virtual PLCore::String GetReturn(PLCore::String nValue) override;
		PLSCRIPTNULL_API virtual PLCore::Object *GetReturn(PLCore::Object *nValue) override;
		PLSCRIPTNULL_API virtual PLCore::Object &GetReturn(PLCore::Object &nValue) override;


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sSourceCode;	/**< Script source code */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptNull


#endif // __PLSCRIPTNULL_SCRIPT_H__
