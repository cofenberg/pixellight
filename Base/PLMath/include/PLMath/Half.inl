/*********************************************************\
 *  File: Half.inl                                       *
 *      Half inline implementation
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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether or not the given half value is zero
*/
inline bool Half::IsZero(PLCore::uint16 nHalf)
{
	return ((nHalf & 0x7fff) == 0);
}

/**
*  @brief
*    Returns whether or not the given half value is negative
*/
inline bool Half::IsNegative(PLCore::uint16 nHalf)
{
	return ((nHalf & 0x8000) != 0);
}

/**
*  @brief
*    Returns whether or not the given half value is not a number (NAN)
*/
inline bool Half::IsNotANumber(PLCore::uint16 nHalf)
{
	const PLCore::uint16 nExponent = ((nHalf >> 10) & 0x001f);
	const PLCore::uint16 nMantissa = (nHalf & 0x3ff);
	return (nExponent == 31 && nMantissa != 0);
}

/**
*  @brief
*    Returns whether or not the given half value is finite
*/
inline bool Half::IsFinite(PLCore::uint16 nHalf)
{
	const PLCore::uint16 nExponent = ((nHalf >> 10) & 0x001f);
	return (nExponent < 31);
}

/**
*  @brief
*    Returns whether or not the given half value is infinity
*/
inline bool Half::IsInfinity(PLCore::uint16 nHalf)
{
	const PLCore::uint16 nExponent = ((nHalf >> 10) & 0x001f);
	const PLCore::uint16 nMantissa = (nHalf & 0x3ff);
	return (nExponent == 31 && nMantissa == 0);
}

/**
*  @brief
*    Returns whether or not the given half value is normalized
*/
inline bool Half::IsNormalized(PLCore::uint16 nHalf)
{
	const PLCore::uint16 nExponent = ((nHalf >> 10) & 0x001f);
	return (nExponent > 0 && nExponent < 31);
}

/**
*  @brief
*    Returns whether or not the given half value is de-normalized
*/
inline bool Half::IsDenormalized(PLCore::uint16 nHalf)
{
	const PLCore::uint16 nExponent = ((nHalf >> 10) & 0x001f);
	const PLCore::uint16 nMantissa = (nHalf & 0x3ff);
	return (nExponent == 0 && nMantissa != 0);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
