/*********************************************************\
 *  File: PerlinNoiseTileable.h                          *
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


#ifndef __PLMATH_PERLINNOISETILEABLE_H__
#define __PLMATH_PERLINNOISETILEABLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/PerlinNoise.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class containing tileable Perlin noise functions
*/
class PerlinNoiseTileable : public PerlinNoise {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		static inline float Noise2(float fX, float fY);
		static inline float Noise3(float fX, float fY, float fZ);
		static PLMATH_API float TileableNoise1(float fX, float fW);
		static PLMATH_API float TileableNoise2(float fX, float fY, float fW, float fH);
		static PLMATH_API float TileableNoise3(float fX, float fY, float fZ, float fW, float fH, float fD);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/PerlinNoiseTileable.inl"


#endif // __PLMATH_PERLINNOISETILEABLE_H__
