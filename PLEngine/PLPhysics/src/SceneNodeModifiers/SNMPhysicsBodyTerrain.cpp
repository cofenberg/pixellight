/*********************************************************\
 *  File: SNMPhysicsBodyTerrain.cpp                      *
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
#include <PLScene/Scene/SceneNodes/Terrain/SNTerrain.h>
#include <PLScene/Scene/SceneNodes/Terrain/GMMSurface.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/World.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBodyTerrain.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsBodyTerrain)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
const Vector3 &SNMPhysicsBodyTerrain::GetScale() const
{
	return m_vScale;
}

void SNMPhysicsBodyTerrain::SetScale(const Vector3 &vValue)
{
	if (m_vScale != vValue) {
		m_vScale = vValue;
		RecreatePhysicsBody();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsBodyTerrain::SNMPhysicsBodyTerrain(SceneNode &cSceneNode) : SNMPhysicsBody(cSceneNode),
	Scale(this),
	m_vScale(1.0f, 1.0f, 1.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsBodyTerrain::~SNMPhysicsBodyTerrain()
{
}


//[-------------------------------------------------------]
//[ Private virtual SNMPhysicsBody functions              ]
//[-------------------------------------------------------]
void SNMPhysicsBodyTerrain::CreatePhysicsBody()
{
	if (m_pWorldContainer && m_pWorldContainer->GetWorld()) {
		// Get the gmm surface of the terrain scene node
		SNTerrain &cTerrainSceneNode = (SNTerrain&)GetSceneNode();
		const GMMSurface *pGMMSurface = cTerrainSceneNode.GetGMMSurface();
		if (pGMMSurface && pGMMSurface->GetHeightMap()) {
			// Create the PL physics body
			const AABoundingBox &cAABBox = cTerrainSceneNode.GetAABoundingBox();
			m_pBodyHandler->SetElement(m_pWorldContainer->GetWorld()->CreateBodyTerrain(pGMMSurface->GetHeightMapSize(),
																						pGMMSurface->GetHeightMapSize(),
																						pGMMSurface->GetHeightMap(),
																						cAABBox.vMin, cAABBox.vMax, m_vScale));

			// Call base implementation
			SNMPhysicsBody::CreatePhysicsBody();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
