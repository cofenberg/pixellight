/*********************************************************\
 *  File: PerlinNoise.h                                  *
 *      Perline noise tool functions
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


#ifndef __PLMATH_PERLINNOISE_H__
#define __PLMATH_PERLINNOISE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/PLMath.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
PLMATH_API void PLInitPerlin();

PLMATH_API float PLNoise1(float fX);
PLMATH_API float PLNoise2(float fX, float fY);
PLMATH_API float PLNoise3(float fX, float fY, float fZ);

PLMATH_API float PLTurbulence2(float fX, float fY, float fFreq);
PLMATH_API float PLTurbulence3(float fX, float fY, float fZ, float fFreq);

PLMATH_API float PLTileableNoise1(float fX, float fW);
PLMATH_API float PLTileableNoise2(float fX, float fY, float fW, float fH);
PLMATH_API float PLTileableNoise3(float fX, float fY, float fZ, float fW, float fH, float fD);

PLMATH_API float PLTileableTurbulence2(float fX, float fY, float fW, float fH, float fFreq);
PLMATH_API float PLTileableTurbulence3(float fX, float fY, float fZ, float fW, float fH, float fD, float fFreq);


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_PERLINNOISE_H__
