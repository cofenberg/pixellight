/*********************************************************\
 *  File: RTTIObjectSignalPointer.h                      *
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


#ifndef __PLSCRIPTLUA_RTTIOBJECTSIGNALPOINTER_H__
#define __PLSCRIPTLUA_RTTIOBJECTSIGNALPOINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScriptLua/RTTIObjectPointer.h"


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
*    RTTI object signal pointer
*/
class RTTIObjectSignalPointer : public RTTIObjectPointer {


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
		*    Pointer the the RTTI object to wrap, can be a null pointer
		*  @param[in] pDynEvent
		*    Pointer the the RTTI object signal to wrap, can be a null pointer
		*/
		RTTIObjectSignalPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEvent *pDynEvent);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RTTIObjectSignalPointer();


	//[-------------------------------------------------------]
	//[ Protected virtual LuaUserData functions               ]
	//[-------------------------------------------------------]
	protected:
		virtual void CallMetamethod(lua_State *pLuaState);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::DynEvent *m_pDynEvent;	/**< Pointer the the RTTI object signal to wrap, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


#endif // __PLSCRIPTLUA_RTTIOBJECTSIGNALPOINTER_H__
