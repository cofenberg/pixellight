/*********************************************************\
 *  File: Rectangle.cpp                                  *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/Rectangle.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Calculates the screen-space bounding rectangle of the given array of points
*/
bool Rectangle::ScreenRectangle(const Array<Vector3> &lstPoints, bool bZCull, const Matrix4x4 &mMVP,
								uint32 nX, uint32 nY, uint32 nWidth, uint32 nHeight)
{
	// Convert it to window space
	const Vector3 *pPoint = &lstPoints[0];
	uint32 nZNear = 0, nZFar = 0;
	Vector3 vPoint;
	for (uint32 i=0; i<lstPoints.GetNumOfElements(); i++, pPoint++) {
		// Multiply with concatenated modelview/projection matrix
		vPoint = *pPoint;
		vPoint *= mMVP;

		// Convert to window coordinates
		// Map x, y and z to range 0-1
		vPoint.x =  vPoint.x*0.5f + 0.5f;
		vPoint.y = -vPoint.y*0.5f + 0.5f;
		vPoint.z =  vPoint.z*0.5f + 0.5f;
		// Map x,y to viewport
		vPoint.x = vPoint.x*nWidth  + nX;
		vPoint.y = vPoint.y*nHeight + nY;

		// Perform z cull?
		if (bZCull) {
			if (vPoint.z < -Math::Epsilon)
				nZFar++;
			else if (vPoint.z > (1+Math::Epsilon))
				nZNear++;
		}

		// Clamp x
		vPoint.x = Math::Max(static_cast<float>(nX),        vPoint.x);
		vPoint.x = Math::Min(static_cast<float>(nX+nWidth), vPoint.x);

		// Clamp y
		vPoint.y = Math::Max(static_cast<float>(nY),         vPoint.y);
		vPoint.y = Math::Min(static_cast<float>(nY+nHeight), vPoint.y);

		// Update min/max
		if (i) {
			if (vMin.x > vPoint.x)
				vMin.x = vPoint.x;
			if (vMin.y > vPoint.y)
				vMin.y = vPoint.y;
			if (vMax.x < vPoint.x)
				vMax.x = vPoint.x;
			if (vMax.y < vPoint.y)
				vMax.y = vPoint.y;
		} else {
			vMin.x = vMax.x = vPoint.x;
			vMin.y = vMax.y = vPoint.y;
		}
	}

	// Return z culling result
	if (nZFar == lstPoints.GetNumOfElements() || nZNear == lstPoints.GetNumOfElements())
		return false; // Z culled
	if (nZNear > 0 && nZNear < lstPoints.GetNumOfElements()) {
		vMin.x = static_cast<float>(nX);
		vMin.y = static_cast<float>(nY);
		vMax.x = static_cast<float>(nX + nWidth);
		vMax.y = static_cast<float>(nY + nHeight);
	}

	// Done
	return true;
}

/**
*  @brief
*    Calculates the screen-space bounding rectangle of the given array of points
*/
bool Rectangle::ScreenRectangle(const Array<Vector4> &lstPoints, bool bZCull, const Matrix4x4 &mMVP,
								uint32 nX, uint32 nY, uint32 nWidth, uint32 nHeight)
{
	// Convert it to window space
	Array<Vector4> lstP(lstPoints);
	const Vector4 *pPoint = &lstP[0];
	uint32 nZNear = 0, nZFar = 0;
	Vector4 vPoint;
	for (uint32 i=0; i<lstP.GetNumOfElements(); i++, pPoint++) {
		// Multiply with concatenated modelview/projection matrix
		vPoint = *pPoint;
		vPoint *= mMVP;
		vPoint.x /= vPoint.w;
		vPoint.y /= vPoint.w;
		vPoint.z /= vPoint.w;
		vPoint.w = 1.0f;

		// Convert to window coordinates
		// Map x, y and z to range 0-1
		vPoint.x =  vPoint.x*0.5f + 0.5f;
		vPoint.y = -vPoint.y*0.5f + 0.5f;
		vPoint.z =  vPoint.z*0.5f + 0.5f;
		// Map x,y to viewport
		vPoint.x = vPoint.x*nWidth  + nX;
		vPoint.y = vPoint.y*nHeight + nY;

		// Perform z cull?
		if (bZCull) {
			if (vPoint.z < -Math::Epsilon)
				nZFar++;
			else if (vPoint.z > (1+Math::Epsilon))
				nZNear++;
		}

		// Clamp x
		vPoint.x = Math::Max(static_cast<float>(nX),        vPoint.x);
		vPoint.x = Math::Min(static_cast<float>(nX+nWidth), vPoint.x);

		// Clamp y
		vPoint.y = Math::Max(static_cast<float>(nY),         vPoint.y);
		vPoint.y = Math::Min(static_cast<float>(nY+nHeight), vPoint.y);

		// Update min/max
		if (i) {
			if (vMin.x > vPoint.x)
				vMin.x = vPoint.x;
			if (vMin.y > vPoint.y)
				vMin.y = vPoint.y;
			if (vMax.x < vPoint.x)
				vMax.x = vPoint.x;
			if (vMax.y < vPoint.y)
				vMax.y = vPoint.y;
		} else {
			vMin.x = vMax.x = vPoint.x;
			vMin.y = vMax.y = vPoint.y;
		}
	}

	// Return z culling result
	if (nZFar == lstP.GetNumOfElements() || nZNear == lstP.GetNumOfElements())
		return false; // Z culled
	if (nZNear > 0 && nZNear < lstP.GetNumOfElements()) {
		vMin.x = static_cast<float>(nX);
		vMin.y = static_cast<float>(nY);
		vMax.x = static_cast<float>(nX + nWidth);
		vMax.y = static_cast<float>(nY + nHeight);
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
