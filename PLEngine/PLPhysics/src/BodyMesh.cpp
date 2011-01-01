/*********************************************************\
 *  File: BodyMesh.cpp                                   *
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
#include "PLPhysics/BodyMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
BodyMesh::~BodyMesh()
{
}

/**
*  @brief
*    Returns the collision mesh
*/
String BodyMesh::GetMesh() const
{
	return m_sMesh;
}

/**
*  @brief
*    Returns the mesh scale
*/
const Vector3 &BodyMesh::GetMeshScale() const
{
	return m_vMeshScale;
}

/**
*  @brief
*    Returns whether the physics API is allowed to optimize the mesh or not (if supported)
*/
bool BodyMesh::GetOptimize() const
{
	return m_bOptimize;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyMesh::BodyMesh(World &cWorld, BodyImpl &cBodyImpl, const String &sMesh, const Vector3 &vMeshScale, bool bOptimize) :
	Body(cWorld, cBodyImpl),
	m_sMesh(sMesh),
	m_vMeshScale(vMeshScale),
	m_bOptimize(bOptimize)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
