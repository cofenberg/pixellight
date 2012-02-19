/*********************************************************\
 *  File: LuaUserData.h                                  *
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


#ifndef __PLSCRIPTLUA_LUAUSERDATA_H__
#define __PLSCRIPTLUA_LUAUSERDATA_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScriptLua/PLScriptLua.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Script;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract Lua user data
*
*  @note
*    - "Lua 5.1 Reference Manual" -> "2.8 - Metatables" -> http://www.lua.org/manual/5.1/manual.html
*/
class LuaUserData {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Lua user data types
		*/
		enum EType {
			TypeObjectPointer             = 0,	/**< Object pointer */
			TypeObjectMethodPointer       = 1,	/**< Object method pointer */
			TypeObjectSignalPointer       = 2,	/**< Object signal pointer */
			TypeObjectSignalMethodPointer = 3,	/**< Object signal method pointer */
			TypeObjectSlotPointer         = 4	/**< Object slot pointer */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates the metatable for LuaUserData events
		*
		*  @param[in] pLuaState
		*    Lua state
		*/
		static void CreateMetatable(lua_State *pLuaState);

		/**
		*  @brief
		*    Destroys the metatable for LuaUserData events
		*
		*  @param[in] pLuaState
		*    Lua state
		*/
		static void DestroyMetatable(lua_State *pLuaState);

		/**
		*  @brief
		*    Returns user data from the Lua stack without removing it
		*
		*  @param[in] pLuaState
		*    Lua state
		*  @param[in] nIndex
		*    Lua stack index
		*
		*  @return
		*    The user data, null pointer on error
		*/
		static LuaUserData *GetUserDataFromLuaStack(lua_State *pLuaState, int nIndex);

		/**
		*  @brief
		*    Returns user data from the top of the Lua stack and removes it from the Lua stack
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    The user data, null pointer on error
		*/
		static LuaUserData *PopUserDataFromLuaStack(lua_State *pLuaState);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Return the Lua user data type
		*
		*  @return
		*    The Lua user data type
		*/
		EType GetType() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nType
		*    The Lua user data type
		*/
		LuaUserData(EType nType);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~LuaUserData();

		/**
		*  @brief
		*    Initializes this instance
		*
		*  @param[in] cScript
		*    The owner script instance
		*/
		void InitializeInstance(Script &cScript);

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
		LuaUserData &operator =(const LuaUserData &cSource);


	//[-------------------------------------------------------]
	//[ Protected virtual LuaUserData functions               ]
	//[-------------------------------------------------------]
	protected:
		/*
		*  @brief
		*    Lua __index metamethod callback (for table accesses)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "Programming in Lua " -> "13.4.1 - The __index Metamethod" -> http://www.lua.org/pil/13.4.1.html
		*/
		virtual int IndexMetamethod(lua_State *pLuaState) = 0;

		/*
		*  @brief
		*    Lua __newindex metamethod callback (for table updates)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "Programming in Lua " -> "13.4.1 - The __newindex Metamethod" -> http://www.lua.org/pil/13.4.2.html
		*/
		virtual int NewIndexMetamethod(lua_State *pLuaState) = 0;

		/*
		*  @brief
		*    Lua __gc metamethod callback (finalizer/destructor called by garbage collector)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @see
		*    - "Programming in Lua " -> "29 - Managing Resources" -> http://www.lua.org/pil/29.html
		*/
		virtual void CGMetamethod(lua_State *pLuaState) = 0;

		/*
		*  @brief
		*    Lua __call metamethod callback (called when Lua calls a value)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @see
		*    - "Lua 5.1 Reference Manual" -> "2.8 - Metatables" -> ""call": called when Lua calls a value" -> http://www.lua.org/manual/5.1/manual.html
		*/
		virtual void CallMetamethod(lua_State *pLuaState) = 0;

		/*
		*  @brief
		*    Lua __tostring metamethod callback (called when Lua tries to convert the user data into a string)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @see
		*    - "Lua 5.1 Reference Manual" -> "5.1 - Basic Functions" -> "If the metatable of e has a "__tostring" field, then tostring calls the corresponding value with e as argument, and uses the result of the call as its result." -> http://www.lua.org/manual/5.1/manual.html
		*/
		virtual void ToStringMetamethod(lua_State *pLuaState) = 0;

		/*
		*  @brief
		*    Lua __eq metamethod callback (called when Lua tries to check for equality)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @see
		*    - "2.8 - Metatables" -> ""eq": the == operation. The function getcomphandler defines how Lua chooses a metamethod for comparison operators. A metamethod only is selected when both objects being compared have the same type and the same metamethod for the selected operation." -> http://www.lua.org/manual/5.1/manual.html
		*/
		virtual int EqualityMetamethod(lua_State *pLuaState) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Script *m_pScript;	/**< The owner script instance, always valid! */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		EType m_nType;	/**< The Lua user data type */


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
		LuaUserData(const LuaUserData &cSource);


	//[-------------------------------------------------------]
	//[ Private static Lua callback functions                 ]
	//[-------------------------------------------------------]
	private:
		/*
		*  @brief
		*    Lua __index metamethod callback (for table accesses)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "Programming in Lua " -> "13.4.1 - The __index Metamethod" -> http://www.lua.org/pil/13.4.1.html
		*/
		static int LuaIndexMetamethodCallback(lua_State *pLuaState);

		/*
		*  @brief
		*    Lua __newindex metamethod callback (for table updates)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "Programming in Lua " -> "13.4.1 - The __newindex Metamethod" -> http://www.lua.org/pil/13.4.2.html
		*/
		static int LuaNewIndexMetamethodCallback(lua_State *pLuaState);

		/*
		*  @brief
		*    Lua __gc metamethod callback (finalizer/destructor called by garbage collector)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "Programming in Lua " -> "29 - Managing Resources" -> http://www.lua.org/pil/29.html
		*/
		static int LuaCGMetamethodCallback(lua_State *pLuaState);

		/*
		*  @brief
		*    Lua __call metamethod callback (called when Lua calls a value)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "Lua 5.1 Reference Manual" -> "2.8 - Metatables" -> ""call": called when Lua calls a value" -> http://www.lua.org/manual/5.1/manual.html
		*/
		static int LuaCallMetamethodCallback(lua_State *pLuaState);

		/*
		*  @brief
		*    Lua __tostring metamethod callback (called when Lua tries to convert the user data into a string)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "Lua 5.1 Reference Manual" -> "5.1 - Basic Functions" -> "If the metatable of e has a "__tostring" field, then tostring calls the corresponding value with e as argument, and uses the result of the call as its result." -> http://www.lua.org/manual/5.1/manual.html
		*/
		static int LuaToStringMetamethodCallback(lua_State *pLuaState);

		/*
		*  @brief
		*    Lua __eq metamethod callback (called when Lua tries to check for equality)
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    Number of parameters to return to Lua
		*
		*  @see
		*    - "2.8 - Metatables" -> ""eq": the == operation. The function getcomphandler defines how Lua chooses a metamethod for comparison operators. A metamethod only is selected when both objects being compared have the same type and the same metamethod for the selected operation." -> http://www.lua.org/manual/5.1/manual.html
		*/
		static int LuaEqualityMetamethodCallback(lua_State *pLuaState);


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static char LuaMetatable;	/**< The address of this static variable is used to identify the metatable of the user data */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_LUAUSERDATA_H__
