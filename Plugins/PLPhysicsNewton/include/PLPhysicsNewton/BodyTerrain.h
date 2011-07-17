/*********************************************************\
 *  File: BodyTerrain.h                                  *
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


#ifndef __PLPHYSICSNEWTON_BODYTERRAIN_H__
#define __PLPHYSICSNEWTON_BODYTERRAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/BodyTerrain.h>
#include "PLPhysicsNewton/PLPhysicsNewton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Newton physics terrain body implementation
*
*  @note
*    - The implementation is basing on the Newton SDK heigh field collision sample
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
		PLPHYSICSNEWTON_API virtual ~BodyTerrain();


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
		BodyTerrain(PLPhysics::World &cWorld, PLGeneral::uint32 nWidth, PLGeneral::uint32 nHeight,
					const float fTerrain[], const PLMath::Vector3 &vBoxMin, const PLMath::Vector3 &vBoxMax,
					const PLMath::Vector3 &vScale);

		/**
		*  @brief
		*    Calculate the intersection of a ray and a triangle
		*/
		dFloat RayCastTriangle(const PLMath::Vector3 &p0, const PLMath::Vector3 &dp, const PLMath::Vector3 &origin, const PLMath::Vector3 &e1, const PLMath::Vector3 &e2);

		/**
		*  @brief
		*    Calculate the intersection point of a line segment and the two triangles making a the cell of a heigh map terrain
		*/
		dFloat RayCastCell(int xIndex0, int zIndex0, const PLMath::Vector3 &p0, const PLMath::Vector3 &dp, PLMath::Vector3 &normalOut);

		/**
		*  @brief
		*    Calculate the bounding box surrounding a line segment
		*/
		void CalculateMinExtend2d(const PLMath::Vector3 &p0, const PLMath::Vector3 &p1, PLMath::Vector3 &boxP0, PLMath::Vector3 &boxP1);

		/**
		*  @brief
		*    Calculate the bounding box surrounding a line segment
		*/
		void CalculateMinExtend3d(const PLMath::Vector3 &p0, const PLMath::Vector3 &p1, PLMath::Vector3 &boxP0, PLMath::Vector3 &boxP1);

		/**
		*  @brief
		*    Clip a line segment against a box
		*/
		bool ClipRay2d(PLMath::Vector3 &p0, PLMath::Vector3 &p1, const PLMath::Vector3 &boxP0, const PLMath::Vector3 &boxP1);


	//[-------------------------------------------------------]
	//[ Private Newton callback functions                     ]
	//[-------------------------------------------------------]
	private:
		static void MeshCollisionCollideCallback(Newton::NewtonUserMeshCollisionCollideDesc *pCollideDescData);
		static dFloat UserMeshCollisionRayHitCallback(Newton::NewtonUserMeshCollisionRayHitDesc *pRayDescData);


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static const int MaxCollidingFaces = 256; /**< Maximum number of colliding faces */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Private data
		PLGeneral::uint32  m_nWidth;	/**< Terrain data width */
		PLGeneral::uint32  m_nHeight;	/**< Terrain data height */
		const float		  *m_pfTerrain;	/**< Terrain data (always valid, do NOT destroy the data itself, it's only shared) */
		PLMath::Vector3	   m_vBoxMin;	/**< Bounding box minimum */
		PLMath::Vector3	   m_vBoxMax;	/**< Bounding box maximum */
		PLMath::Vector3	   m_vScale;	/**< Scale */

		int				m_nAttribute[MaxCollidingFaces];
		int				m_nFaceIndices[MaxCollidingFaces];
		int				m_nIndexArray[MaxCollidingFaces * 3];
		PLMath::Vector3	m_vCollisionVertex[MaxCollidingFaces * 2];


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_BODYTERRAIN_H__
