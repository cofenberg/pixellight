/*********************************************************\
 *  File: RTTIObjectMethodPointer.h                      *
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


#ifndef __PLSCRIPTLUA_RTTIOBJECTMETHODPOINTER_H__
#define __PLSCRIPTLUA_RTTIOBJECTMETHODPOINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Func/DynFunc.h>
#include "PLScriptLua/RTTIObjectPointer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    RTTI object method pointer
*/
class RTTIObjectMethodPointer : public RTTIObjectPointer {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the current Lua function parameters on the Lua stack as string
		*
		*  @param[in] cScript
		*    The owner script instance
		*  @param[in] cDynSignature
		*    Dynamic signature of the function to be called
		*  @param[in] bIsMethod
		*    'true' if the dynamic function is a method, 'false' if it's a global function
		*
		*  @return
		*    The current Lua function parameters on the Lua stack as string
		*/
		static PLGeneral::String GetLuaFunctionParametersAsString(Script &cScript, PLCore::DynSignature &cDynSignature, bool bIsMethod);

		/**
		*  @brief
		*    Calls the current Lua stack dynamic function
		*
		*  @param[in] cScript
		*    The owner script instance
		*  @param[in] cDynFunc
		*    Dynamic function to be called
		*  @param[in] bIsMethod
		*    'true' if the dynamic function is a method, 'false' if it's a global function
		*
		*  @return
		*    Number of results on the Lua stack
		*/
		static int CallDynFunc(Script &cScript, PLCore::DynFunc &cDynFunc, bool bIsMethod);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cScript
		*    The owner script instance
		*  @param[in] pRTTIObject
		*    Pointer to the RTTI object to wrap, can be a null pointer
		*  @param[in] pDynFunc
		*    Smart pointer to the RTTI object method to wrap, can be a null pointer
		*/
		RTTIObjectMethodPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynFuncPtr pDynFunc);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RTTIObjectMethodPointer();

		/**
		*  @brief
		*    Returns the pointer to the RTTI object method to wrap
		*
		*  @return
		*    Pointer to the RTTI object method to wrap, can be a null pointer
		*/
		PLCore::DynFuncPtr GetDynFuncPtr() const;


	//[-------------------------------------------------------]
	//[ Protected virtual LuaUserData functions               ]
	//[-------------------------------------------------------]
	protected:
		virtual int IndexMetamethod(lua_State *pLuaState);
		virtual int NewIndexMetamethod(lua_State *pLuaState);
		virtual void CallMetamethod(lua_State *pLuaState);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::DynFuncPtr m_pDynFunc;	/**< Smart pointer to the RTTI object method to wrap, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_RTTIOBJECTMETHODPOINTER_H__
