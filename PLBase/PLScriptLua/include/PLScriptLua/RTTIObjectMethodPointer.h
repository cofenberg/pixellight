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
#include "PLScriptLua/RTTIObjectPointer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class DynFunc;
}


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
		*    Calls the current Lua stack dynamic function
		*
		*  @param[in] cScript
		*    The owner script instance
		*  @param[in] cDynFunc
		*    Dynamic function to be called
		*
		*  @return
		*    Number of results on the Lua stack
		*/
		static int CallDynFunc(Script &cScript, PLCore::DynFunc &cDynFunc);


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
		*    Pointer to the RTTI object method to wrap, can be a null pointer
		*/
		RTTIObjectMethodPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynFunc *pDynFunc);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RTTIObjectMethodPointer();


	//[-------------------------------------------------------]
	//[ Protected virtual LuaUserData functions               ]
	//[-------------------------------------------------------]
	protected:
		virtual void CallMetamethod(lua_State *pLuaState);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::DynFunc *m_pDynFunc;	/**< Pointer to the RTTI object method to wrap, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_RTTIOBJECTMETHODPOINTER_H__
