/*********************************************************\
 *  File: Font.cpp                                       *
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
#include "PLGui/Gui/Resources/Font.h"
#include "PLGui/Gui/Resources/FontInfo.h"
#include "PLGui/Gui/Gui.h"
#include "PLGui/Backend/FontImpl.h"


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
Font::Font(Gui &cGui) :
	m_pGui(&cGui),
	m_pFontImpl(NULL),
	m_sFamily(),
	m_nHeight(0),
	m_nWeight(WeightNormal),
	m_nStyle(StyleNormal),
	m_sFilename()
{
	// Load empty font
	Load("");
}

/**
*  @brief
*    Constructor
*/
Font::Font(Gui &cGui, const String &sFamily, uint32 nHeight, EFontWeight nWeight, EFontStyle nStyle) :
	m_pGui(&cGui),
	m_pFontImpl(NULL),
	m_sFamily(sFamily),
	m_nHeight(nHeight),
	m_nWeight(nWeight),
	m_nStyle(nStyle),
	m_sFilename()
{
	// Load font
	Load(sFamily, nHeight, nWeight, nStyle);
}

/**
*  @brief
*    Constructor
*/
Font::Font(Gui &cGui, const FontInfo &cFontInfo) :
	m_pGui(&cGui),
	m_pFontImpl(NULL),
	m_sFamily(cFontInfo.GetFamily()),
	m_nHeight(cFontInfo.GetHeight()),
	m_nWeight(cFontInfo.GetWeight()),
	m_nStyle(cFontInfo.GetStyle()),
	m_sFilename(cFontInfo.GetFilename())
{
	// Load font
	if (m_sFilename.GetLength() > 0) LoadFromFile(m_sFilename, m_nHeight);
	else							 Load(m_sFamily, m_nHeight, m_nWeight, m_nStyle);
}

/**
*  @brief
*    Copy constructor
*/
Font::Font(const Font &cFont) :
	m_pGui(cFont.m_pGui),
	m_pFontImpl(cFont.m_pFontImpl),
	m_sFamily(cFont.m_sFamily),
	m_nHeight(cFont.m_nHeight),
	m_nWeight(cFont.m_nWeight),
	m_nStyle(cFont.m_nStyle),
	m_sFilename(cFont.m_sFilename)
{
	// Increase reference count for font
	if (m_pFontImpl)
		m_pFontImpl->AddReference();
}

/**
*  @brief
*    Destructor
*/
Font::~Font()
{
	// Release font
	if (m_pFontImpl)
		m_pFontImpl->Release();
}

/**
*  @brief
*    Assignment operator
*/
Font &Font::operator =(const Font &cFont)
{
	// Release font
	if (m_pFontImpl) {
		m_pFontImpl->Release();
		m_pFontImpl = NULL;
	}

	// Copy font
	m_pFontImpl	= cFont.m_pFontImpl;
	m_sFamily	= cFont.m_sFamily;
	m_nHeight	= cFont.m_nHeight;
	m_nWeight	= cFont.m_nWeight;
	m_nStyle	= cFont.m_nStyle;
	m_sFilename	= cFont.m_sFilename;
	if (m_pFontImpl) {
		m_pFontImpl->AddReference();
	}

	// Return reference to this font
	return *this;
}

/**
*  @brief
*    Get owner GUI
*/
Gui *Font::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get implementation
*/
FontImpl *Font::GetImpl() const
{
	// Return font implementation
	return m_pFontImpl;
}

/**
*  @brief
*    Load font
*/
bool Font::Load(const String &sFamily, uint32 nHeight, EFontWeight nWeight, EFontStyle nStyle)
{
	// Release font
	if (m_pFontImpl) {
		m_pFontImpl->Release();
		m_pFontImpl = NULL;
	}

	// Save font data
	m_sFilename	= "";
	m_sFamily	= sFamily;
	m_nHeight	= nHeight;
	m_nWeight	= nWeight;
	m_nStyle	= nStyle;

	// Create font
	m_pFontImpl = m_pGui->CreateFontImpl(*this);
	m_pFontImpl->AddReference();

	// Load font
	return m_pFontImpl->LoadFont(sFamily, nHeight, nWeight, nStyle);
}

/**
*  @brief
*    Load font from file
*/
bool Font::LoadFromFile(const String &sFilename, uint32 nHeight)
{
	// Release font
	if (m_pFontImpl) {
		m_pFontImpl->Release();
		m_pFontImpl = NULL;
	}

	// Save font data
	m_sFilename	= sFilename;
	m_sFamily	= "";
	m_nHeight	= nHeight;
	m_nWeight	= WeightNormal;
	m_nStyle	= StyleNormal;

	// Create font
	m_pFontImpl = m_pGui->CreateFontImpl(*this);
	m_pFontImpl->AddReference();

	// Load font
	return m_pFontImpl->LoadFont(sFilename, nHeight);
}

/**
*  @brief
*    Get font information
*/
FontInfo Font::GetFontInfo() const
{
	// Return font info
	return FontInfo(m_sFilename, m_sFamily, m_nHeight, m_nWeight, m_nStyle);
}

/**
*  @brief
*    Get font file name
*/
String Font::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Get font family
*/
String Font::GetFamily() const
{
	// Return family name
	return m_sFamily;
}

/**
*  @brief
*    Set font family
*/
void Font::SetFamily(const String &sFamily)
{
	// Load changed font
	Load(sFamily, m_nHeight, m_nWeight, m_nStyle);
}

/**
*  @brief
*    Get font height
*/
uint32 Font::GetHeight() const
{
	// Return height
	return m_nHeight;
}

/**
*  @brief
*    Set font height
*/
void Font::SetHeight(uint32 nHeight)
{
	// Load changed font
	Load(m_sFamily, nHeight, m_nWeight, m_nStyle);
}

/**
*  @brief
*    Get font weight
*/
EFontWeight Font::GetWeight() const
{
	// Return weight
	return m_nWeight;
}

/**
*  @brief
*    Set font weight
*/
void Font::SetWeight(EFontWeight nWeight)
{
	// Load changed font
	Load(m_sFamily, m_nHeight, nWeight, m_nStyle);
}

/**
*  @brief
*    Get font style
*/
EFontStyle Font::GetStyle() const
{
	// Return style
	return m_nStyle;
}

/**
*  @brief
*    Set font style
*/
void Font::SetStyle(EFontStyle nStyle)
{
	// Load changed font
	Load(m_sFamily, m_nHeight, m_nWeight, nStyle);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
