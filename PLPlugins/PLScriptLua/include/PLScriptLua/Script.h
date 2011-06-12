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
#include <PLCore/Script/Script.h>
#include "PLScriptLua/PLScriptLua.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class DynEvent;
	class DynEventHandler;
}
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
class Script : public PLCore::Script {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class RTTIObjectSignalMethodPointer;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTLUA_RTTI_EXPORT, Script, "PLScriptLua", PLCore::Script, "Lua (http://www.lua.org/) script implementation")
		// Properties
		pl_properties
			pl_property("Language",	"Lua")
			pl_property("Formats",	"lua,LUA")
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
		PLSCRIPTLUA_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTLUA_API virtual ~Script();

		/**
		*  @brief
		*    Returns the Lua state
		*
		*  @return
		*    Lua state, can be a null pointer
		*/
		PLSCRIPTLUA_API lua_State *GetLuaState() const;

		/**
		*  @brief
		*    Writes the current Lua stack content into the log
		*
		*  @note
		*    - For debugging
		*/
		PLSCRIPTLUA_API void LuaStackDump();


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Script functions               ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTLUA_API virtual bool AddGlobalFunction(const PLGeneral::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLGeneral::String &sNamespace = "");
		PLSCRIPTLUA_API virtual bool RemoveAllGlobalFunctions();

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		PLSCRIPTLUA_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTLUA_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		PLSCRIPTLUA_API virtual const PLGeneral::Array<PLGeneral::String> &GetGlobalVariables();
		PLSCRIPTLUA_API virtual bool IsGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTLUA_API virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLGeneral::String &sName);
		PLSCRIPTLUA_API virtual PLGeneral::String GetGlobalVariable(const PLGeneral::String &sName);
		PLSCRIPTLUA_API virtual void SetGlobalVariable(const PLGeneral::String &sName, const PLCore::DynVar &cValue);

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		PLSCRIPTLUA_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTLUA_API virtual void PushArgument(bool bValue);
		PLSCRIPTLUA_API virtual void PushArgument(float fValue);
		PLSCRIPTLUA_API virtual void PushArgument(double fValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::int8 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::int16 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::int32 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::int64 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(PLGeneral::uint64 nValue);
		PLSCRIPTLUA_API virtual void PushArgument(const PLGeneral::String &sString);
		PLSCRIPTLUA_API virtual void PushArgument(PLCore::Object *pObject);
		PLSCRIPTLUA_API virtual bool EndCall();
		PLSCRIPTLUA_API virtual bool GetReturn(bool nValue);
		PLSCRIPTLUA_API virtual float GetReturn(float nValue);
		PLSCRIPTLUA_API virtual double GetReturn(double nValue);
		PLSCRIPTLUA_API virtual PLGeneral::int8 GetReturn(PLGeneral::int8 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::int16 GetReturn(PLGeneral::int16 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::int32 GetReturn(PLGeneral::int32 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::int64 GetReturn(PLGeneral::int64 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::uint8 GetReturn(PLGeneral::uint8 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::uint16 GetReturn(PLGeneral::uint16 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::uint32 GetReturn(PLGeneral::uint32 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::uint64 GetReturn(PLGeneral::uint64 nValue);
		PLSCRIPTLUA_API virtual PLGeneral::String GetReturn(PLGeneral::String nValue);
		PLSCRIPTLUA_API virtual PLCore::Object *GetReturn(PLCore::Object *nValue);


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
		*    A global function
		*/
		struct GlobalFunction {
			Script			  *pScript;		/**< Pointer to the owner script instance, always valid! */
			PLGeneral::String  sFunction;	/**< Function name used inside the script to call the global function */
			PLCore::DynFunc   *pDynFunc;	/**< Dynamic function to be called, always valid, destroy when done */
			PLGeneral::String  sNamespace;	/**< Optional namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on) */
		};

		/**
		*  @brief
		*    The structure is used to connect script functions with RTTI signals
		*/
		struct EventUserData {
			PLCore::DynEventHandler *pDynEventHandler;		/**< The generic event handler, always valid! (delete the instance when no longer required) */
			Script					*pScript;				/**< The owner script instance, always valid! */
			int						 nLuaFunctionReference;	/**< The Lua-function or C-function to be called, never LUA_NOREF (use luaL_unref(<LuaState>, LUA_REGISTRYINDEX, <Reference>) when no longer required) */
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

		/**
		*  @brief
		*    Creates a nested Lua table
		*
		*  @param[in] pLuaState
		*    Lua state
		*  @param[in] sTableName
		*    Lua table name (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on)
		*
		*  @note
		*    - Creates all required subtables
		*    - Leaves the deepest table on the Lua stack
		*    - Already existing Lua tables are not overwritten
		*
		*  @return
		*    'true' if all went fine, else 'false' (error within the given Lua table name?)
		*/
		bool CreateNestedTable(lua_State *pLuaState, const PLGeneral::String &sTableName);

		//[-------------------------------------------------------]
		//[ Event and event handler stuff                         ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns event user data key
		*
		*  @param[in] pDynEvent
		*    Dynamic event, must be valid
		*  @param[in] pLuaPointer
		*    Lua pointer to the function, must be valid
		*
		*  @return
		*    Event user data key
		*/
		PLGeneral::String GetEventUserDataKey(PLCore::DynEvent *pDynEvent, const void *pLuaPointer) const;

		/**
		*  @brief
		*    Returns event user data
		*
		*  @param[in] pDynEvent
		*    Dynamic event, must be valid
		*  @param[in] pLuaPointer
		*    Lua pointer to the function, must be valid
		*
		*  @return
		*    Event user data, can be a null pointer
		*/
		EventUserData *GetEventUserData(PLCore::DynEvent *pDynEvent, const void *pLuaPointer) const;

		/**
		*  @brief
		*    Adds event user data
		*
		*  @param[in] pDynEvent
		*    Dynamic event, must be valid
		*  @param[in] pLuaPointer
		*    Lua pointer to the function, must be valid
		*  @param[in] pEventUserData
		*   Event user data to add, must be valid
		*
		*  @note
		*    - Do only call this method if the event user data is not yet added
		*/
		void AddEventUserData(PLCore::DynEvent *pDynEvent, const void *pLuaPointer, EventUserData *pEventUserData);

		/**
		*  @brief
		*    Destroys all registered event user data (a kind of "disconnect all slots at once")
		*/
		void DestroyEventUserData();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String									   m_sSourceCode;			/**< Script source code */
		lua_State											  *m_pLuaState;				/**< Lua state, can be a null pointer */
		PLGeneral::String									   m_sCurrentFunction;		/**< Name of the current function */
		bool												   m_bFunctionResult;		/**< Has the current function a result? */
		PLGeneral::uint32									   m_nCurrentArgument;		/**< Current argument, used during function call */
		PLGeneral::Array<GlobalFunction*>					   m_lstGlobalFunctions;	/**< List of global functions */
		PLGeneral::Array<PLGeneral::String>					   m_lstGlobalVariables;	/**< List of all global variables */
		PLGeneral::HashMap<PLGeneral::String, EventUserData*>  m_mapEventUserData;		/**< Map holding all event user data instances */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_SCRIPT_H__
