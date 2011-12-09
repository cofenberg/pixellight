/*********************************************************\
 *  File: Vector3i.cpp                                   *
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
#include <PLCore/String/RegEx.h>
#include "PLMath/Vector2i.h"
#include "PLMath/Vector3i.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const Vector3i Vector3i::Zero		  ( 0,  0,  0);
const Vector3i Vector3i::One		  ( 1,  1,  1);
const Vector3i Vector3i::NegativeOne  (-1, -1, -1);
const Vector3i Vector3i::UnitX		  ( 1,  0,  0);
const Vector3i Vector3i::UnitY		  ( 0,  1,  0);
const Vector3i Vector3i::UnitZ		  ( 0,  0,  1);
const Vector3i Vector3i::NegativeUnitX(-1,  0,  0);
const Vector3i Vector3i::NegativeUnitY( 0, -1,  0);
const Vector3i Vector3i::NegativeUnitZ( 0,  0, -1);


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Vector3i::Vector3i(const Vector2i &vVector, int nZ) :
	x(vVector.x),
	y(vVector.y),
	z(nZ)
{
}

/**
*  @brief
*    Set X, Y and Z component
*/
void Vector3i::SetXYZ(const Vector2i &vXY, int nZ)
{
	x = vXY.x;
	y = vXY.y;
	z = nZ;
}

/**
*  @brief
*    To string
*/
String Vector3i::ToString() const
{
	return String::Format("%d %d %d", x, y, z);
}

/**
*  @brief
*    From string
*/
bool Vector3i::FromString(const String &sString)
{
	if (sString.GetLength()) {
		// Parse components
		uint32 nParsePos  = 0;
		uint32 nComponent = 0;
		static RegEx cRegEx("\\s*(\\S+)");
		while (nComponent < 3 && cRegEx.Match(sString, nParsePos)) {
			nV[nComponent++] = cRegEx.GetResult(0).GetInt();
			nParsePos = cRegEx.GetPosition();
		}

		// Set unused components to 0
		while (nComponent < 3)
			nV[nComponent++] = 0;

		// Done
		return true;
	} else {
		// Error!
		x = y = z = 0;
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
