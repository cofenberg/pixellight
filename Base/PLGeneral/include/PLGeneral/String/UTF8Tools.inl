/*********************************************************\
 *  File: UTF8Tools.inl                                  *
 *      UTF8 tools inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether the given character is an octal digit
*/
inline bool UTF8Tools::IsOctalDigit(char nCharacter)
{
	return (nCharacter >= '0' && nCharacter <= '7');
}

/**
*  @brief
*    Returns whether the given character is a hex digit
*/
inline bool UTF8Tools::IsHexDigit(char nCharacter)
{
	return ((nCharacter >= '0' && nCharacter <= '9') ||
			(nCharacter >= 'A' && nCharacter <= 'F') ||
			(nCharacter >= 'a' && nCharacter <= 'f'));
}

/**
*  @brief
*    Returns whether the given character is the start of an UTF8 sequence or not
*/
inline bool UTF8Tools::IsSequenceStart(char nCharacter)
{
	return ((nCharacter & 0xC0) != 0x80);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
