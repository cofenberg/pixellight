/*********************************************************\
 *  File: PerlinNoiseTurbulence.cpp                      *
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
#include "PLMath/PerlinNoiseTurbulence.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
float PerlinNoiseTurbulence::Turbulence2(float fX, float fY, float fFreq)
{
	float t = 0.0f;

	do {
		t += Noise2(fFreq*fX, fFreq*fY)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}

float PerlinNoiseTurbulence::Turbulence3(float fX, float fY, float fZ, float fFreq)
{
	float t = 0.0f;

	do {
		t += Noise3(fFreq*fX, fFreq*fY, fFreq*fZ)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}

float PerlinNoiseTurbulence::TileableTurbulence2(float fX, float fY, float fW, float fH, float fFreq)
{
	float t = 0.0f;

	do {
		t += TileableNoise2(fFreq*fX, fFreq*fY, fW*fFreq, fH*fFreq)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}

float PerlinNoiseTurbulence::TileableTurbulence3(float fX, float fY, float fZ, float fW, float fH, float fD, float fFreq)
{
	float t = 0.0f;

	do {
		t += TileableNoise3(fFreq*fX, fFreq*fY, fFreq*fZ, fW*fFreq, fH*fFreq, fD*fFreq)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
