/*********************************************************\
 *  File: LuaContext.inl                                 *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptLua {


//[-------------------------------------------------------]
//[ Lua user data types                                   ]
//[-------------------------------------------------------]
// RTTIObjectPointer
inline RTTIObjectPointer &LuaContext::GetRTTIObjectPointer(Script &cScript, PLCore::Object *pRTTIObject)
{
	RTTIObjectPointer &cInstance = m_lstRTTIObjectPointer.Add();
	cInstance.InitializeInstance(cScript, pRTTIObject);
	return cInstance;
}

inline void LuaContext::ReleaseRTTIObjectPointer(RTTIObjectPointer &cInstance)
{
	// Remove the given instance (added to the list of free elements)
	m_lstRTTIObjectPointer.Remove(cInstance);
}

// RTTIObjectSlotPointer
inline RTTIObjectSlotPointer &LuaContext::GetRTTIObjectSlotPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEventHandler *pDynEventHandler)
{
	RTTIObjectSlotPointer &cInstance = m_lstRTTIObjectSlotPointer.Add();
	cInstance.InitializeInstance(cScript, pRTTIObject, pDynEventHandler);
	return cInstance;
}

inline void LuaContext::ReleaseRTTIObjectSlotPointer(RTTIObjectSlotPointer &cInstance)
{
	// Remove the given instance (added to the list of free elements)
	m_lstRTTIObjectSlotPointer.RemoveElement(cInstance);
}

// RTTIObjectMethodPointer
inline RTTIObjectMethodPointer &LuaContext::GetRTTIObjectMethodPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynFuncPtr pDynFunc)
{
	RTTIObjectMethodPointer &cInstance = m_lstRTTIObjectMethodPointer.Add();
	cInstance.InitializeInstance(cScript, pRTTIObject, pDynFunc);
	return cInstance;
}

inline void LuaContext::ReleaseRTTIObjectMethodPointer(RTTIObjectMethodPointer &cInstance)
{
	// Remove the given instance (added to the list of free elements)
	m_lstRTTIObjectMethodPointer.RemoveElement(cInstance);
}

// RTTIObjectSignalPointer
inline RTTIObjectSignalPointer &LuaContext::GetRTTIObjectSignalPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEvent *pDynEvent)
{
	RTTIObjectSignalPointer &cInstance = m_lstRTTIObjectSignalPointer.Add();
	cInstance.InitializeInstance(cScript, pRTTIObject, pDynEvent);
	return cInstance;
}

inline void LuaContext::ReleaseRTTIObjectSignalPointer(RTTIObjectSignalPointer &cInstance)
{
	// Remove the given instance (added to the list of free elements)
	m_lstRTTIObjectSignalPointer.Remove(cInstance);
}

// RTTIObjectSignalMethodPointer
inline RTTIObjectSignalMethodPointer &LuaContext::GetRTTIObjectSignalMethodPointer(Script &cScript, PLCore::Object *pRTTIObject, PLCore::DynEvent *pDynEvent, RTTIObjectSignalMethodPointer::EMethod nMethod)
{
	RTTIObjectSignalMethodPointer &cInstance = m_lstRTTIObjectSignalMethodPointer.Add();
	cInstance.InitializeInstance(cScript, pRTTIObject, pDynEvent, nMethod);
	return cInstance;
}

inline void LuaContext::ReleaseRTTIObjectSignalMethodPointer(RTTIObjectSignalMethodPointer &cInstance)
{
	// Remove the given instance (added to the list of free elements)
	m_lstRTTIObjectSignalMethodPointer.RemoveElement(cInstance);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptLua
