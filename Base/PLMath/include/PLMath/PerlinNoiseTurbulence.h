/*********************************************************\
 *  File: PerlinNoiseTurbulence.h                        *
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


#ifndef __PLMATH_PERLINNOISETURBULENCE_H__
#define __PLMATH_PERLINNOISETURBULENCE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/PerlinNoiseTileable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class containing turbulence perlin noise functions
*/
class PerlinNoiseTurbulence : public PerlinNoiseTileable {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		static PLMATH_API float Turbulence2(float fX, float fY, float fFreq);
		static PLMATH_API float Turbulence3(float fX, float fY, float fZ, float fFreq);
		static PLMATH_API float TileableTurbulence2(float fX, float fY, float fW, float fH, float fFreq);
		static PLMATH_API float TileableTurbulence3(float fX, float fY, float fZ, float fW, float fH, float fD, float fFreq);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_PERLINNOISETURBULENCE_H__
