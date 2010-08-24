/*********************************************************\
 *  File: FontInfo.cpp                                   *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Gui/Resources/FontInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FontInfo::FontInfo() :
	m_sFilename(),
	m_sFamily(),
	m_nHeight(0),
	m_nWeight(WeightNormal),
	m_nStyle(StyleNormal)
{
}

/**
*  @brief
*    Constructor
*/
FontInfo::FontInfo(const String &sFilename, const String &sFamily, uint32 nHeight, EFontWeight nWeight, EFontStyle nStyle) :
	m_sFilename(sFilename),
	m_sFamily(sFamily),
	m_nHeight(nHeight),
	m_nWeight(nWeight),
	m_nStyle(nStyle)
{
}

/**
*  @brief
*    Copy constructor
*/
FontInfo::FontInfo(const FontInfo &cFontInfo) :
	m_sFamily(cFontInfo.m_sFamily),
	m_nHeight(cFontInfo.m_nHeight),
	m_nWeight(cFontInfo.m_nWeight),
	m_nStyle(cFontInfo.m_nStyle),
	m_sFilename(cFontInfo.m_sFilename)
{
}

/**
*  @brief
*    Destructor
*/
FontInfo::~FontInfo()
{
}

/**
*  @brief
*    Assignment operator
*/
FontInfo &FontInfo::operator =(const FontInfo &cFontInfo)
{
	// Copy font info
	m_sFamily	= cFontInfo.m_sFamily;
	m_nHeight	= cFontInfo.m_nHeight;
	m_nWeight	= cFontInfo.m_nWeight;
	m_nStyle	= cFontInfo.m_nStyle;
	m_sFilename	= cFontInfo.m_sFilename;

	// Return reference to this font
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
bool FontInfo::operator ==(const FontInfo &cFontInfo) const
{
	// Compare fonts
	return (m_sFamily	== cFontInfo.m_sFamily &&
			m_nHeight	== cFontInfo.m_nHeight &&
			m_nWeight	== cFontInfo.m_nWeight &&
			m_nStyle	== cFontInfo.m_nStyle  &&
			m_sFilename	== cFontInfo.m_sFilename );
}

/**
*  @brief
*    Get font file name
*/
String FontInfo::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Get font family
*/
String FontInfo::GetFamily() const
{
	// Return family name
	return m_sFamily;
}

/**
*  @brief
*    Get font height
*/
uint32 FontInfo::GetHeight() const
{
	// Return height
	return m_nHeight;
}

/**
*  @brief
*    Get font weight
*/
EFontWeight FontInfo::GetWeight() const
{
	// Return weight
	return m_nWeight;
}

/**
*  @brief
*    Get font style
*/
EFontStyle FontInfo::GetStyle() const
{
	// Return style
	return m_nStyle;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
