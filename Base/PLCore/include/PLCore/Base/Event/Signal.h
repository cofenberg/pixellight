/*********************************************************\
 *  File: Signal.h                                       *
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


#ifndef __PLCORE_SIGNAL_H__
#define __PLCORE_SIGNAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Event/Event.h"
#include "PLCore/Base/Event/EventDesc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Event of a class
*
*  @remarks
*    This class template represents signals (events that belong to objects).
*
*  @note
*    - Implementation of the observer design pattern (this class is the subject/observable, the source)
*/
template <typename DESC>
class Signal : public DESC::EventType {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static DESC	Desc;	/**< Event descriptor */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Signal() :
			DESC::EventType()
		{
			// Ensure that the compiler will actually create static instances
			Desc.Dummy();
		}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Signal()
		{
		}


	//[-------------------------------------------------------]
	//[ Public virtual DynEvent functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get event descriptor
		*
		*  @return
		*    Event descriptor
		*/
		virtual const EventDesc *GetDesc() const override
		{
			// Return descriptor
			return &Desc;
		}


};


// Static data instances
template<typename DESC>
DESC Signal<DESC>::Desc;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_SIGNAL_H__
