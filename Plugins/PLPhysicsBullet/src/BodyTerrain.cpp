/*********************************************************\
 *  File: BodyTerrain.cpp                                *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix4x4.h>
#include "PLPhysicsBullet/BodyImpl.h"
#include "PLPhysicsBullet/World.h"
#include "PLPhysicsBullet/BodyTerrain.h"
#include <Bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLPhysicsBullet {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
BodyTerrain::~BodyTerrain()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyTerrain::BodyTerrain(PLPhysics::World &cWorld,  PLCore::uint32 nWidth, PLCore::uint32 nHeight,
					const float fTerrain[], const PLMath::Vector3 &vBoxMin, const PLMath::Vector3 &vBoxMax,
					const PLMath::Vector3 &vScale) :
	PLPhysics::BodyTerrain(cWorld, static_cast<World&>(cWorld).CreateBodyImpl()),
	m_nWidth(nWidth),
	m_nHeight(nHeight),
	m_pfTerrain(fTerrain),
	m_vBoxMin(vBoxMin),
	m_vBoxMax(vBoxMax),
	m_vScale(vScale)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Bullet physics world
	btDynamicsWorld *pBulletWorld = ((World&)cWorld).GetBulletWorld();
	if (pBulletWorld) {
		// [TODO] use correct values for min/max height (can they calculated from vBoxMin and vBoxMax?)
		//        and is the up axis always the y-axis?
		btCollisionShape* collisionShape = new btHeightfieldTerrainShape(m_nWidth, m_nHeight, const_cast<float*>(m_pfTerrain),
																		 0 /* scaling factor, ignored when using float values */,
																		 0/* <min height, float>*/,
																		 0/* <max height, float>*/,
																		 1 /* y-axis is up */,
																		 PHY_FLOAT /* Highfield values are float*/,
																		 false /*flip quatEdges*/
																		);
		
		// Initialize the Bullet physics body
		((BodyImpl&)GetBodyImpl()).InitializeBulletBody(*this, *collisionShape, true);
	}

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsBullet
