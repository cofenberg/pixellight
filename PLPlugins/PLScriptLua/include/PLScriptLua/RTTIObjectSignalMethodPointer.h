/*********************************************************\
 *  File: RTTIObjectSignalMethodPointer.h                *
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


#ifndef __PLSCRIPTLUA_RTTIOBJECTSIGNALMETHODPOINTER_H__
#define __PLSCRIPTLUA_RTTIOBJECTSIGNALMETHODPOINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScriptLua/RTTIObjectSignalPointer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class DynParams;
	class DynEventHandler;
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
*    RTTI object build in signal method pointer
*/
class RTTIObjectSignalMethodPointer : public RTTIObjectSignalPointer {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Build in method
		*/
		enum EMethod {
			MethodUnknown    = -1,	/**< Unknown method */
			MethodConnect    = 0,	/**< Connect method */
			MethodDisconnect = 1	/**< Disconnect method */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the build in method defined by a given string
		*
		*  @param[in] sMethod
		*    String to return the build in method from
		*
		*  @return
		*    The build in method defined by the given string
		*/
		static EMethod StringToMethod(const PLGeneral::String &sMethod);


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
		*  @param[in] pDynEvent
		*    Pointer to the RTTI object signal to wrap, can be a null pointer
		*  @param[in] nMethod
		*    Build in method
		*/
		RTTIObjectSignalMethodPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEvent *pDynEvent, EMethod nMethod);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RTTIObjectSignalMethodPointer();


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
		EMethod m_nMethod;	/**< Build in method */


	//[-------------------------------------------------------]
	//[ Private static event callback functions               ]
	//[-------------------------------------------------------]
	private:
		/*
		*  @brief
		*    Event callback function
		*
		*  @param[in] cDynParams
		*    Dynamic parameters
		*  @param[in] pUserData
		*    Pointer to optional user data, can be a null pointer
		*/
		static void EventCallback(PLCore::DynParams &cDynParams, void *pUserData);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns a RTTI slot from the Lua stack without removing it
		*
		*  @param[in] pLuaState
		*    Lua state
		*
		*  @return
		*    The valid RTTI slot, null pointer on error
		*
		*  @note
		*    - Performs also a signal/slot signature match
		*    - m_pDynEvent must be valid
		*/
		PLCore::DynEventHandler *GetSlotFromLuaStack(lua_State *pLuaState);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_RTTIOBJECTSIGNALMETHODPOINTER_H__
