/*********************************************************\
 *  File: BodyTerrain.h                                  *
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


#ifndef __PLPHYSICSBULLET_BODYTERRAIN_H__
#define __PLPHYSICSBULLET_BODYTERRAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/BodyTerrain.h>
#include "PLPhysicsBullet/PLPhysicsBullet.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsBullet {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bullet physics terrain body implementation
*/
class BodyTerrain : public PLPhysics::BodyTerrain {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICSBULLET_API virtual ~BodyTerrain();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this body is in
		*  @param[in] nWidth
		*    Terrain data width
		*  @param[in] nHeight
		*    Terrain data height
		*  @param[in] fTerrain
		*    Terrain data
		*  @param[in] vBoxMin
		*    Bounding box minimum
		*  @param[in] vBoxMax
		*    Bounding box maximum
		*  @param[in] vScale
		*    Scale
		*/
		BodyTerrain(PLPhysics::World &cWorld, PLCore::uint32 nWidth, PLCore::uint32 nHeight,
					const float fTerrain[], const PLMath::Vector3 &vBoxMin, const PLMath::Vector3 &vBoxMax,
					const PLMath::Vector3 &vScale);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Private data
		PLCore::uint32     m_nWidth;	/**< Terrain data width */
		PLCore::uint32     m_nHeight;	/**< Terrain data height */
		const float		  *m_pfTerrain;	/**< Terrain data (always valid, do NOT destroy the data itself, it's only shared) */
		PLMath::Vector3	   m_vBoxMin;	/**< Bounding box minimum */
		PLMath::Vector3	   m_vBoxMax;	/**< Bounding box maximum */
		PLMath::Vector3	   m_vScale;	/**< Scale */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsBullet


#endif // __PLPHYSICSBULLET_BODYTERRAIN_H__
