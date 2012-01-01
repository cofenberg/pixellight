/*********************************************************\
 *  File: PerlinNoiseTileable.inl                        *
 *      PerlinNoiseTileable inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
inline float PerlinNoiseTileable::Noise2(float fX, float fY)
{
	// This is just a wrapper - Call the original perlin noise function
	const double vec[2] = { fX, fY };
	return static_cast<float>(PerlinNoise::Noise2(vec));
}

inline float PerlinNoiseTileable::Noise3(float fX, float fY, float fZ)
{
	// This is just a wrapper - Call the original perlin noise function
	const double vec[3] = { fX, fY, fZ };
	return static_cast<float>(PerlinNoise::Noise3(vec));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
