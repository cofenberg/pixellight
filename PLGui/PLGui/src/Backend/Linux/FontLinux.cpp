/*********************************************************\
 *  File: FontLinux.cpp                                  *
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
#include "PLGui/PLGuiLinux.h"
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/Resources/Font.h"
#include "PLGui/Backend/Linux/GuiLinux.h"
#include "PLGui/Backend/Linux/FontLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FontLinux::FontLinux(Font &cFont) : FontImpl(cFont),
	m_pDisplay(((GuiLinux*)cFont.GetGui()->GetImpl())->GetDisplay()),
	m_pXFont(nullptr),
	m_nHeight(0)
{
}

/**
*  @brief
*    Destructor
*/
FontLinux::~FontLinux()
{
	// Release font
	if (m_pXFont) XFreeFont(m_pDisplay, m_pXFont);
}

/**
*  @brief
*    Get X font
*/
XFontStruct *FontLinux::GetXFont() const
{
	// Return font
	return m_pXFont;
}

/**
*  @brief
*    Get font height
*/
uint32 FontLinux::GetHeight() const
{
	// Return font height
	return m_nHeight;
}


//[-------------------------------------------------------]
//[ Public virtual FontImpl functions                     ]
//[-------------------------------------------------------]
bool FontLinux::LoadFont(const String &sFamily, uint32 nHeight, uint32 nWeight, EFontStyle nStyle)
{
	// Release font
	if (m_pXFont) {
		XFreeFont(m_pDisplay, m_pXFont);
		m_pXFont = nullptr;
	}

	// Load font
	if (sFamily.GetLength()) {
		// Font options
		String sFoundry		= "*";
		String sWeight		= (nWeight >= WeightBold ? "bold" : "medium");
		String sSlant		= (nStyle == StyleItalics ? "i" : "r");
		String sWidth		= "normal";
		String sStyle		= "*";
		String sPixelSize	= String() + (int)nHeight;
		String sPointSize	= "*";

		// Compose font name
		String sFontName =	"-" + sFoundry + 
							"-" + sFamily +
							"-" + sWeight +
							"-" + sSlant +
							"-" + sWidth +
							"-" + sStyle +
							"-" + sPixelSize +
							"-" + sPointSize +
							"-*-*-*-*-*-*";

		// Load font
		m_pXFont = XLoadQueryFont(m_pDisplay, sFontName.GetASCII());

		// [DEBUG] Error
		if (!m_pXFont) {
//			printf("Could not load font '%s'\n", sFontName.GetASCII());
		}
	}

	// Check returned font
	bool bSuccess = true;
	if (!m_pXFont) {

		// Load default font
		m_pXFont = XLoadQueryFont(m_pDisplay, "fixed");
		bSuccess = false;
	}

	// Save height
//	m_nHeight = m_pXFont->ascent + m_pXFont->descent - 1;
	m_nHeight = m_pXFont->ascent - 1;

	// Done
	return bSuccess;
}

bool FontLinux::LoadFont(const String &sFilename, uint32 nHeight)
{
	// [TODO]
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
