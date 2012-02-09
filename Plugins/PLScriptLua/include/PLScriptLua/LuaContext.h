/*********************************************************\
 *  File: LuaContext.h                                   *
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


#ifndef __PLSCRIPTLUA_LUACONTEXT_H__
#define __PLSCRIPTLUA_LUACONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Core/AbstractContext.h>
#include <PLCore/Container/FastPool.h>
#include "PLScriptLua/RTTIObjectPointer.h"
#include "PLScriptLua/RTTIObjectSlotPointer.h"
#include "PLScriptLua/RTTIObjectMethodPointer.h"
#include "PLScriptLua/RTTIObjectSignalPointer.h"
#include "PLScriptLua/RTTIObjectSignalMethodPointer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static Lua context
*/
class LuaContext : public PLCore::AbstractContext {


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Adds a context reference
		*
		*  @note
		*    - If this is the first reference, the internal Lua context is created automatically
		*/
		static void AddContextReference();

		/**
		*  @brief
		*    Releases a context reference
		*
		*  @note
		*    - If this is the last reference, the internal Lua context is destroyed automatically
		*/
		static void ReleaseContextReference();

		//[-------------------------------------------------------]
		//[ Lua user data types                                   ]
		//[-------------------------------------------------------]
		// RTTIObjectPointer
		static inline RTTIObjectPointer &GetRTTIObjectPointer(Script &cScript, PLCore::Object *pRTTIObject);
		static inline void ReleaseRTTIObjectPointer(RTTIObjectPointer &cInstance);
		// RTTIObjectSlotPointer
		static inline RTTIObjectSlotPointer &GetRTTIObjectSlotPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEventHandler *pDynEventHandler);
		static inline void ReleaseRTTIObjectSlotPointer(RTTIObjectSlotPointer &cInstance);
		// RTTIObjectMethodPointer
		static inline RTTIObjectMethodPointer &GetRTTIObjectMethodPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynFuncPtr pDynFunc);
		static inline void ReleaseRTTIObjectMethodPointer(RTTIObjectMethodPointer &cInstance);
		// RTTIObjectSignalPointer
		static inline RTTIObjectSignalPointer &GetRTTIObjectSignalPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEvent *pDynEvent);
		static inline void ReleaseRTTIObjectSignalPointer(RTTIObjectSignalPointer &cInstance);
		// RTTIObjectSignalMethodPointer
		static inline RTTIObjectSignalMethodPointer &GetRTTIObjectSignalMethodPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEvent *pDynEvent, RTTIObjectSignalMethodPointer::EMethod nMethod);
		static inline void ReleaseRTTIObjectSignalMethodPointer(RTTIObjectSignalMethodPointer &cInstance);


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static PLCore::uint32 m_nContexCounter;	/**< Lua context counter */

		// Lua user data types
		static PLCore::FastPool<RTTIObjectPointer>				m_lstRTTIObjectPointer;				/**< Fast pool for "RTTIObjectPointer"-instances */
		static PLCore::FastPool<RTTIObjectSlotPointer>			m_lstRTTIObjectSlotPointer;			/**< Fast pool for "RTTIObjectSlotPointer"-instances */
		static PLCore::FastPool<RTTIObjectMethodPointer>		m_lstRTTIObjectMethodPointer;		/**< Fast pool for "RTTIObjectMethodPointer"-instances */
		static PLCore::FastPool<RTTIObjectSignalPointer>		m_lstRTTIObjectSignalPointer;		/**< Fast pool for "RTTIObjectSignalPointer"-instances */
		static PLCore::FastPool<RTTIObjectSignalMethodPointer>	m_lstRTTIObjectSignalMethodPointer;	/**< Fast pool for "RTTIObjectSignalMethodPointer"-instances */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLScriptLua/LuaContext.inl"


#endif // __PLSCRIPTLUA_LUACONTEXT_H__
