/*********************************************************\
 *  File: Vector2i.cpp                                   *
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
#include <PLGeneral/String/RegEx.h>
#include "PLMath/Vector2i.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const Vector2i Vector2i::Zero		  ( 0,  0);
const Vector2i Vector2i::One		  ( 1,  1);
const Vector2i Vector2i::NegativeOne  (-1, -1);
const Vector2i Vector2i::UnitX		  ( 1,  0);
const Vector2i Vector2i::UnitY		  ( 0,  1);
const Vector2i Vector2i::NegativeUnitX(-1,  0);
const Vector2i Vector2i::NegativeUnitY( 0, -1);


/**
*  @brief
*    To string
*/
String Vector2i::ToString() const
{
	return String::Format("%d %d", x, y);
}

/**
*  @brief
*    From string
*/
bool Vector2i::FromString(const String &sString)
{
	if (sString.GetLength()) {
		// Parse components
		uint32 nParsePos  = 0;
		uint32 nComponent = 0;
		static RegEx cRegEx("\\s*(\\S+)");
		while (nComponent < 2 && cRegEx.Match(sString, nParsePos)) {
			nV[nComponent++] = cRegEx.GetResult(0).GetInt();
			nParsePos = cRegEx.GetPosition();
		}

		// Set unused componts to 0
		while (nComponent < 2)
			nV[nComponent++] = 0;

		// Done
		return true;
	} else {
		// Error!
		x = y = 0;
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
