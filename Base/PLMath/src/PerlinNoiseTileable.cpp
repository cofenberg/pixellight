/*********************************************************\
 *  File: PerlinNoiseTileable.cpp                        *
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
#include "PLMath/PerlinNoiseTileable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
float PerlinNoiseTileable::TileableNoise1(float fX, float fW)
{
	return static_cast<float>((Noise1(fX)*(fW-fX) + Noise1(fX-fW)*fX)/fW);
}

float PerlinNoiseTileable::TileableNoise2(float fX, float fY, float fW, float fH)
{
	return (Noise2(fX,    fY)   *(fW-fX)*(fH-fY) +
			Noise2(fX-fW, fY)   *    fX *(fH-fY) +
			Noise2(fX,    fY-fH)*(fW-fX)*    fY  +
			Noise2(fX-fW, fY-fH)*    fX *    fY)/(fW*fH);
}

float PerlinNoiseTileable::TileableNoise3(float fX, float fY, float fZ, float fW, float fH, float fD)
{
	return (Noise3(fX,    fY,    fZ)   *(fW-fX)*(fH-fY)*(fD-fZ) +
			Noise3(fX-fW, fY,    fZ)   *    fX *(fH-fY)*(fD-fZ) +
			Noise3(fX,    fY-fH, fZ)   *(fW-fX)*    fY *(fD-fZ) +
			Noise3(fX-fW, fY-fH, fZ)   *    fX *    fY *(fD-fZ) + 
			Noise3(fX,    fY,    fZ-fD)*(fW-fX)*(fH-fY)*    fZ  +
			Noise3(fX-fW, fY,    fZ-fD)*    fX *(fH-fY)*    fZ  +
			Noise3(fX,    fY-fH, fZ-fD)*(fW-fX)*    fY *    fZ  +
			Noise3(fX-fW, fY-fH, fZ-fD)*    fX *    fY *    fZ)/(fW*fH*fD);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
