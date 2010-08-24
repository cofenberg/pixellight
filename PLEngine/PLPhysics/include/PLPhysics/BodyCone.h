/*********************************************************\
 *  File: BodyCone.h                                     *
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


#ifndef __PLPHYSICS_BODYCONE_H__
#define __PLPHYSICS_BODYCONE_H__
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
*    Abstract PL physics cone body
*
*  @note
*    - The cone height must equal of larger than the sum of the cap radius. If this is not
*      the case the height will be clamped the 2 * radius.
*/
class BodyCone : public Body {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~BodyCone();

		/**
		*  @brief
		*    Returns the cone radius at the base
		*
		*  @return
		*    The cone radius at the base
		*/
		PLPHYSICS_API float GetRadius() const;

		/**
		*  @brief
		*    Returns the cone height along the x local axis from base to top
		*
		*  @return
		*    The cone height along the x local axis from base to top
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
		*    Cone radius at the base
		*  @param[in] fHeight
		*    Cone height along the x local axis from base to top
		*/
		PLPHYSICS_API BodyCone(World &cWorld, BodyImpl &cBodyImpl, float fRadius, float fHeight);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		float m_fRadius;	/**< Cone radius at the base */
		float m_fHeight;	/**< Cone height along the x local axis from base to top */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_BODYCONE_H__
