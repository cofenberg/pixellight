/*********************************************************\
 *  File: BodyCylinder.h                                 *
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


#ifndef __PLPHYSICS_BODYCYLINDER_H__
#define __PLPHYSICS_BODYCYLINDER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/Body.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PL physics cylinder body
*/
class BodyCylinder : public Body {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~BodyCylinder();

		/**
		*  @brief
		*    Returns the cylinder radius at the base
		*
		*  @return
		*    The cylinder radius at the base
		*/
		PLPHYSICS_API float GetRadius() const;

		/**
		*  @brief
		*    Returns the cylinder height along the x local axis from base to top
		*
		*  @return
		*    The cylinder height along the x local axis from base to top
		*/
		PLPHYSICS_API float GetHeight() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this body is in
		*  @param[in] cBodyImpl
		*    Reference to the physics API specific body implementation
		*  @param[in] fRadius
		*    Cylinder radius at the base
		*  @param[in] fHeight
		*    Cylinder height along the x local axis from base to top
		*/
		PLPHYSICS_API BodyCylinder(World &cWorld, BodyImpl &cBodyImpl, float fRadius, float fHeight);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		float m_fRadius;	/**< Cylinder radius at the base */
		float m_fHeight;	/**< Cylinder height along the x local axis from base to top */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_BODYCYLINDER_H__
