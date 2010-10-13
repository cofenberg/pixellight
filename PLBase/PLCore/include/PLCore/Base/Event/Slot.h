/*********************************************************\
 *  File: Slot.h                                         *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_SLOT_H__
#define __PLCORE_SLOT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Event/EventHandler.h"
#include "PLCore/Base/Event/EventHandlerDesc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Event handler of a class
*
*  @remarks
*    This class template represents slots (event handlers that belong to objects).
*/
template <typename DESC>
class Slot : public DESC::EventHandlerType {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static DESC	Desc;	/**< Event handler descriptor */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pMemFunc
		*    Pointer to member function of a class
		*  @param[in] pObject
		*    Pointer to object to which the method belongs
		*/
		Slot(const typename DESC::MethType::MemFuncType &pMemFunc, typename DESC::ClassType *pObject) :
			DESC::EventHandlerType(pMemFunc, pObject)
		{
			Desc.Dummy();
		}

		/**
		*  @brief
		*    Destructor
		*/
		~Slot()
		{
		}


	//[-------------------------------------------------------]
	//[ Public virtual DynFunc functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get event handler descriptor
		*
		*  @return
		*    Event handler descriptor
		*/
		virtual const EventHandlerDesc *GetDesc() const {
			// Return descriptor
			return &Desc;
		}


};


// Static data instances
template<typename DESC>
DESC Slot<DESC>::Desc;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_SLOT_H__
