/*********************************************************\
 *  File: Element.h                                      *
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


#ifndef __PLPHYSICS_ELEMENT_H__
#define __PLPHYSICS_ELEMENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Element.h>
#include "PLPhysics/PLPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class World;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics element base class
*/
class Element : public PLCore::Element<Element> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the world this element is in
		*
		*  @return
		*    The world this element is in
		*/
		PLPHYSICS_API World &GetWorld() const;

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~Element();


	//[-------------------------------------------------------]
	//[ Public virtual Element functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether or not this is a body
		*
		*  @return
		*    'true' if this is a body, else 'false'
		*/
		PLPHYSICS_API virtual bool IsBody() const = 0;

		/**
		*  @brief
		*    Returns whether or not this is a joint
		*
		*  @return
		*    'true' if this is a joint, else 'false'
		*/
		PLPHYSICS_API virtual bool IsJoint() const = 0;

		/**
		*  @brief
		*    Returns whether or not this is a sensor
		*
		*  @return
		*    'true' if this is a sensor, else 'false'
		*/
		PLPHYSICS_API virtual bool IsSensor() const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this element is in
		*/
		PLPHYSICS_API Element(World &cWorld);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_ELEMENT_H__
