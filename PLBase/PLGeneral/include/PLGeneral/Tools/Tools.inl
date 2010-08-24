/*********************************************************\
 *  File: Tools.inl                                      *
 *      Tools inline implementation
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
*    float to uint32
*/
inline uint32 Tools::FloatToUInt32(float f)
{
	return *((uint32*)&f);
}

/**
*  @brief
*    uint32 to float
*/
inline float Tools::UInt32ToFloat(uint32 n)
{
	return *((float*)&n);
}

/**
*  @brief
*    Base64 encoder
*/
inline String Tools::GetBase64(const String &sString)
{
	String sBase64;
	uint32 nLength = sString.GetLength();
	const char *pszString = sString.GetASCII();
	for (uint32 i=0; i<sString.GetLength(); i+=3) {
		uint8 nByte0 = pszString[i];
		uint8 nByte1 = (i+1 < nLength) ? pszString[i+1] : 0;
		uint8 nByte2 = (i+2 < nLength) ? pszString[i+2] : 0;
		for (int j=0; j<4; j++) {
			uint8 nBlock = 0;
			switch (j) {
				case 0: nBlock = ((nByte0 & 252) >> 2); break;
				case 1: nBlock = ((nByte0 &   3) << 4) | ((nByte1 & 240) >> 4); break;
				case 2: nBlock = ((nByte1 &  15) << 2) | ((nByte2 & 128+64) >> 6); break;
				case 3: nBlock = ((nByte2 &  63)); break;
			}
			char cChar = 0;
			if (nBlock <= 25)						cChar = (char)('A' + nBlock);
			else if (nBlock >= 26 && nBlock <= 51)	cChar = (char)('a' + (nBlock - 26));
			else if (nBlock >= 52 && nBlock <= 61)	cChar = (char)('0' + (nBlock - 52));
			else if (nBlock == 62)					cChar = '+';
			else if (nBlock == 63)					cChar = '/';
			if ((j >= 2 && i+1 >= nLength) || (j == 3 && i+2 >= nLength)) cChar = '=';
			sBase64 += cChar;
		}
	}
	return sBase64;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
