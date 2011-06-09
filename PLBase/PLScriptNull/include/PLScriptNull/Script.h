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


#ifndef __PLSCRIPTNULL_SCRIPT_H__
#define __PLSCRIPTNULL_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScript/Script.h>
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
class Script : public PLScript::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTNULL_RTTI_EXPORT, Script, "PLScriptNull", PLScript::Script, "Null script implementation")
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
	//[ Public virtual PLScript::Script functions             ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual bool AddGlobalFunction(const PLGeneral::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLGeneral::String &sNamespace = "");
		PLSCRIPTNULL_API virtual bool RemoveAllGlobalFunctions();

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTNULL_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual const PLGeneral::Array<PLGeneral::String> &GetGlobalVariables();
		PLSCRIPTNULL_API virtual bool IsGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTNULL_API virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLGeneral::String &sName);
		PLSCRIPTNULL_API virtual PLGeneral::String GetGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTNULL_API virtual void SetGlobalVariable(const PLGeneral::String &sName, const PLCore::DynVar &cValue);

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		PLSCRIPTNULL_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTNULL_API virtual void PushArgument(bool bValue);
		PLSCRIPTNULL_API virtual void PushArgument(float fValue);
		PLSCRIPTNULL_API virtual void PushArgument(double fValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::int8 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::int16 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::int32 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::int64 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(PLGeneral::uint64 nValue);
		PLSCRIPTNULL_API virtual void PushArgument(const PLGeneral::String &sString);
		PLSCRIPTNULL_API virtual void PushArgument(PLCore::Object *pObject);
		PLSCRIPTNULL_API virtual bool EndCall();
		PLSCRIPTNULL_API virtual bool GetReturn(bool nValue);
		PLSCRIPTNULL_API virtual float GetReturn(float nValue);
		PLSCRIPTNULL_API virtual double GetReturn(double nValue);
		PLSCRIPTNULL_API virtual PLGeneral::int8 GetReturn(PLGeneral::int8 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::int16 GetReturn(PLGeneral::int16 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::int32 GetReturn(PLGeneral::int32 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::int64 GetReturn(PLGeneral::int64 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::uint8 GetReturn(PLGeneral::uint8 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::uint16 GetReturn(PLGeneral::uint16 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::uint32 GetReturn(PLGeneral::uint32 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::uint64 GetReturn(PLGeneral::uint64 nValue);
		PLSCRIPTNULL_API virtual PLGeneral::String GetReturn(PLGeneral::String nValue);
		PLSCRIPTNULL_API virtual PLCore::Object *GetReturn(PLCore::Object *nValue);


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
		PLGeneral::String					m_sSourceCode;			/**< Script source code */
		PLGeneral::Array<PLGeneral::String>	m_lstGlobalVariables;	/**< List of all global variables */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptNull


#endif // __PLSCRIPTNULL_SCRIPT_H__
