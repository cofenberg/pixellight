/*********************************************************\
 *  File: RTTIObjectPointer.h                            *
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


#ifndef __PLSCRIPTLUA_RTTIOBJECTPOINTER_H__
#define __PLSCRIPTLUA_RTTIOBJECTPOINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScriptLua/LuaUserData.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Object;
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
*    RTTI object pointer
*/
class RTTIObjectPointer : public LuaUserData {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Pushes an RTTI class instance onto the Lua stack
		*
		*  @param[in] cScript
		*    The owner script instance
		*  @param[in] pRTTIObject
		*    Pointer to the RTTI object to wrap, in case of a null pointer nil is pushed onto the Lua stack
		*
		*  @note
		*    - The destruction of the new RTTIObjectPointer instance is done by the Lua garbage collector
		*/
		static void LuaStackPush(Script &cScript, PLCore::Object *pRTTIObject);


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
		*  @param[in] nType
		*    The Lua user data type
		*/
		RTTIObjectPointer(Script &cScript, PLCore::Object *pRTTIObject, EType nType = TypeObjectPointer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RTTIObjectPointer();

		/**
		*  @brief
		*    Returns the pointer to the RTTI object to wrap
		*
		*  @return
		*    Pointer to the RTTI object to wrap, can be a null pointer
		*/
		PLCore::Object *GetObject() const;


	//[-------------------------------------------------------]
	//[ Protected virtual LuaUserData functions               ]
	//[-------------------------------------------------------]
	protected:
		virtual int IndexMetamethod(lua_State *pLuaState) override;
		virtual int NewIndexMetamethod(lua_State *pLuaState) override;
		virtual void CGMetamethod(lua_State *pLuaState) override;
		virtual void CallMetamethod(lua_State *pLuaState) override;
		virtual void ToStringMetamethod(lua_State *pLuaState) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the RTTI object assigned with this wrapper was destroyed
		*/
		void OnDestroy();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<>  m_cEventHandlerOnDestroy;	/**< "OnDestroy" event handler */
		PLCore::Object		   *m_pRTTIObject;				/**< Pointer to the RTTI object to wrap, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_RTTIOBJECTPOINTER_H__
