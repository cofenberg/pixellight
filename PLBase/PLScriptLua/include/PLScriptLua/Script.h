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


#ifndef __PLSCRIPTLUA_SCRIPT_H__
#define __PLSCRIPTLUA_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScript/Script.h>
#include "PLScriptLua/PLScriptLua.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
typedef struct lua_State lua_State;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Lua (http://www.lua.org/) script implementation
*/
class Script : public PLScript::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTLUA_RTTI_EXPORT, Script, "PLScriptLua", PLScript::Script, "Lua (http://www.lua.org/) script implementation")
		pl_properties
			pl_property("Language", "Lua")
			pl_property("Formats",  "lua,LUA")
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
		PLSCRIPTLUA_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTLUA_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLScript::Script functions             ]
	//[-------------------------------------------------------]
	public:
		PLSCRIPTLUA_API virtual bool AddDynamicFunction(const PLGeneral::String &sFunction, const PLCore::DynFunc &cDynFunc);
		PLSCRIPTLUA_API virtual bool RemoveAllDynamicFunctions();
		PLSCRIPTLUA_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTLUA_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);
		PLSCRIPTLUA_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTLUA_API virtual void PushArgument(int nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(float fValue);
		PLSCRIPTLUA_API virtual void PushArgument(double fValue);
		PLSCRIPTLUA_API virtual bool EndCall();
		PLSCRIPTLUA_API virtual void GetReturn(int &nValue);
		PLSCRIPTLUA_API virtual void GetReturn(PLGeneral::uint8 &nValue);
		PLSCRIPTLUA_API virtual void GetReturn(PLGeneral::uint16 &nValue);
		PLSCRIPTLUA_API virtual void GetReturn(PLGeneral::uint32 &nValue);
		PLSCRIPTLUA_API virtual void GetReturn(float &fValue);
		PLSCRIPTLUA_API virtual void GetReturn(double &fValue);


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
		*    Reports Lua errors
		*
		*  @note
		*    - Do only call this method if m_pLuaState is valid and there was in fact an error
		*/
		void ReportErrors();

		/**
		*  @brief
		*    Clears the script
		*/
		void Clear();


	//[-------------------------------------------------------]
	//[ Private static Lua callback functions                 ]
	//[-------------------------------------------------------]
	private:
		/*
		*  @brief
		*    Lua memory allocation
		*
		*  @param[in] pUserData
		*    User data
		*  @param[in] pPointer
		*    A pointer to the block being allocated/reallocated/freed
		*  @param[in] nOriginalBlockSize
		*    The original size of the block
		*  @param[in] nNewBlockSize
		*    The new size of the block
		*
		*  @return
		*    Pointer to the allocated memory, can be a null pointer
		*/
		static void *LuaMemoryAllocation(void *pUserData, void *pPointer, size_t nOriginalBlockSize, size_t nNewBlockSize);

		/*
		*  @brief
		*    Lua function callback
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*/
		static int LuaFunctionCallback(lua_State *pLuaState);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    A dynamic function
		*/
		struct DynamicFunction {
			PLGeneral::String  sFunction;	/**< Function name used inside the script to call the dynamic function */
			PLCore::DynFunc   *pDynFunc;	/**< Dynamic function to be called, always valid, destroy when done */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String					m_sSourceCode;			/**< Script source code */
		lua_State						   *m_pLuaState;			/**< Lua state, can be a null pointer */
		PLGeneral::String					m_sCurrentFunction;		/**< Name of the current function */
		bool								m_bFunctionResult;		/**< Has the current function a result? */
		PLGeneral::uint32					m_nCurrentArgument;		/**< Current argument, used during function call */
		PLGeneral::Array<DynamicFunction*>  m_lstDynamicFunctions;	/**< List of dynamic functions */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_SCRIPT_H__
