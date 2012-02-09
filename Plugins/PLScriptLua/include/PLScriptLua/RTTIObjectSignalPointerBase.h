/*********************************************************\
 *  File: RTTIObjectSignalPointerBase.h                  *
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


#ifndef __PLSCRIPTLUA_RTTIOBJECTSIGNALPOINTERBASE_H__
#define __PLSCRIPTLUA_RTTIOBJECTSIGNALPOINTERBASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScriptLua/RTTIObjectPointerBase.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class DynEvent;
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
*    RTTI object signal pointer base class
*/
class RTTIObjectSignalPointerBase : public RTTIObjectPointerBase {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RTTIObjectSignalPointerBase();

		/**
		*  @brief
		*    Returns the pointer to the RTTI object signal to wrap
		*
		*  @return
		*    Pointer to the RTTI object signal to wrap, can be a null pointer
		*/
		PLCore::DynEvent *GetDynEvent() const;


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
		RTTIObjectSignalPointerBase(EType nType = TypeObjectSignalPointer);

		/**
		*  @brief
		*    Initializes this instance
		*
		*  @param[in] cScript
		*    The owner script instance
		*  @param[in] pRTTIObject
		*    Pointer to the RTTI object to wrap, can be a null pointer
		*  @param[in] pDynEvent
		*    Pointer to the RTTI object signal to wrap, can be a null pointer
		*/
		void InitializeInstance(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEvent *pDynEvent);


	//[-------------------------------------------------------]
	//[ Protected virtual LuaUserData functions               ]
	//[-------------------------------------------------------]
	protected:
		virtual int IndexMetamethod(lua_State *pLuaState) override;
		virtual int NewIndexMetamethod(lua_State *pLuaState) override;
		virtual void CallMetamethod(lua_State *pLuaState) override;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::DynEvent *m_pDynEvent;	/**< Pointer to the RTTI object signal to wrap, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_RTTIOBJECTSIGNALPOINTERBASE_H__
