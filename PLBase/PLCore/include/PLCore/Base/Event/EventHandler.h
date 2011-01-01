/*********************************************************\
 *  File: EventHandler.h                                 *
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


#ifndef __PLCORE_EVENTHANDLER_H__
#define __PLCORE_EVENTHANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Func/Functor.h"
#include "PLCore/Base/Event/DynEventHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
class Event;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Generic event handler class
*/
template <typename T0 = NullType, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType, typename T10 = NullType, typename T11 = NullType, typename T12 = NullType, typename T13 = NullType, typename T14 = NullType, typename T15 = NullType>
class EventHandler : public DynEventHandler {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Event<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>;


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		typedef Functor<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>		TypeFunctor;
		typedef Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>	TypeSignature;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		EventHandler() :
			m_cFunctor()
		{
		}

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFunctor
		*    Functor containing an event handler function
		*/
		EventHandler(const TypeFunctor &cFunctor) :
			m_cFunctor(cFunctor)
		{
		}

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pFunc
		*    Pointer to a static function
		*/
		EventHandler(const typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FuncType &pFunc) :
			m_cFunctor(pFunc)
		{
		}

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pMemFunc
		*    Pointer to a member function of a class
		*  @param[in] pObject
		*    Pointer to an instance of that class
		*/
        template <class CLASS>
		EventHandler(const typename MethodSignature<CLASS, void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::MemFuncType &pMemFunc, CLASS *pObject) :
			m_cFunctor(pMemFunc, pObject)
		{
		}

		/**
		*  @brief
		*    Destructor
		*/
		~EventHandler()
		{
		}


	//[-------------------------------------------------------]
	//[ Public virtual DynEventHandler functions              ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetSignature() const {
			return TypeSignature::GetSignatureID();
		}


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		TypeFunctor m_cFunctor;		/**< Functor containing the event handler */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_EVENTHANDLER_H__
