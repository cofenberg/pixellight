/*********************************************************\
 *  File: BodyConvexHull.cpp                             *
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
#include "PLPhysics/BodyConvexHull.h"


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
BodyConvexHull::~BodyConvexHull()
{
}

/**
*  @brief
*    Returns the collision mesh
*/
String BodyConvexHull::GetMesh() const
{
	return m_sMesh;
}

/**
*  @brief
*    Returns the mesh scale
*/
const Vector3 &BodyConvexHull::GetMeshScale() const
{
	return m_vMeshScale;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyConvexHull::BodyConvexHull(World &cWorld, BodyImpl &cBodyImpl, const String &sMesh, const Vector3 &vMeshScale) :
	Body(cWorld, cBodyImpl),
	m_sMesh(sMesh),
	m_vMeshScale(vMeshScale)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
