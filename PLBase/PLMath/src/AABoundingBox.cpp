/*********************************************************\
 *  File: AABoundingBox.cpp                              *
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
#include "PLMath/AABoundingBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
AABoundingBox &AABoundingBox::operator =(const AABoundingBox &cSource)
{
	// Copy data
	vMin = cSource.vMin;
	vMax = cSource.vMax;

	// Return this
	return *this;
}

/**
*  @brief
*    Returns the 8 corner vertices
*/
void AABoundingBox::GetVertices(Vector3 vVertex[8]) const
{
	vVertex[0].SetXYZ(vMin.x, vMin.y, vMin.z);
	vVertex[1].SetXYZ(vMax.x, vMin.y, vMin.z);
	vVertex[2].SetXYZ(vMax.x, vMax.y, vMin.z);
	vVertex[3].SetXYZ(vMin.x, vMax.y, vMin.z);
	vVertex[4].SetXYZ(vMin.x, vMin.y, vMax.z);
	vVertex[5].SetXYZ(vMax.x, vMin.y, vMax.z);
	vVertex[6].SetXYZ(vMax.x, vMax.y, vMax.z);
	vVertex[7].SetXYZ(vMin.x, vMax.y, vMax.z);
}

/**
*  @brief
*    Returns one of the 8 corner vertices
*/
Vector3 AABoundingBox::GetVertex(uint32 nIndex) const
{
	switch (nIndex) {
		case 0:  return Vector3(vMin.x, vMin.y, vMin.z);
		case 1:  return Vector3(vMax.x, vMin.y, vMin.z);
		case 2:  return Vector3(vMax.x, vMax.y, vMin.z);
		case 3:  return Vector3(vMin.x, vMax.y, vMin.z);
		case 4:  return Vector3(vMin.x, vMin.y, vMax.z);
		case 5:  return Vector3(vMax.x, vMin.y, vMax.z);
		case 6:  return Vector3(vMax.x, vMax.y, vMax.z);
		case 7:  return Vector3(vMin.x, vMax.y, vMax.z);
		default: return Vector3::Zero; // Error!
	}
}

/**
*  @brief
*    Calculates the index of the nearest vertex in the AAB according to the normal vector of a clip plane
*/
uint32 AABoundingBox::GetNearestVertexIndex(const Vector3 &vClipPlaneNormal) const
{
	uint32 nIndex;

	// Get vertex index
	if (vClipPlaneNormal.x <= 0.0f)
		nIndex = (vClipPlaneNormal.y <= 0.0f) ? 0 : 3;
	else
		nIndex = (vClipPlaneNormal.y <= 0.0f) ? 1 : 2;
	return (vClipPlaneNormal.z <= 0.0f) ? nIndex : 4 + nIndex;
}

/**
*  @brief
*    Calculates the index of the furthest vertex in the AAB according to the normal vector of a clip plane
*/
uint32 AABoundingBox::GetFurthestVertexIndex(const Vector3 &vClipPlaneNormal) const
{
	uint32 nIndex;

	// Get vertex index
	if (vClipPlaneNormal.x > 0.0f)
		nIndex = (vClipPlaneNormal.y > 0.0f) ? 0 : 3;
	else
		nIndex = (vClipPlaneNormal.y > 0.0f) ? 1 : 2;
	return (vClipPlaneNormal.z > 0.0f) ? nIndex : 4 + nIndex;
}

/**
*  @brief
*    Ensures that the minimum is really the minimum and the maximum is really the maximum
*/
void AABoundingBox::ValidateMinMax()
{
	// x
	if (vMin.x > vMax.x) {
		// Swap
		const float fTemp = vMax.x;
		vMax.x = vMin.x;
		vMin.x = fTemp;
	}

	// y
	if (vMin.y > vMax.y) {
		// Swap
		const float fTemp = vMax.y;
		vMax.y = vMin.y;
		vMin.y = fTemp;
	}

	// z
	if (vMin.z > vMax.z) {
		// Swap
		const float fTemp = vMax.z;
		vMax.z = vMin.z;
		vMin.z = fTemp;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
