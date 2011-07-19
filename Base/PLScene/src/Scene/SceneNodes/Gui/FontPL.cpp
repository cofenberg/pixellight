/*********************************************************\
 *  File: FontPL.cpp                                     *
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
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Resources/Font.h>
#include <PLRenderer/Renderer/Font.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/FontManager.h>
#include "PLScene/Scene/SceneNodes/Gui/GuiPL.h"
#include "PLScene/Scene/SceneNodes/Gui/FontPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGui;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FontPL::FontPL(Font &cFont) : FontImpl(cFont),
	m_pFont(&cFont)
{
}

/**
*  @brief
*    Destructor
*/
FontPL::~FontPL()
{
	// Do not destroy the renderer font, we might need it again...
}

/**
*  @brief
*    Returns the renderer font
*/
PLRenderer::Font *FontPL::GetRendererFont()
{
	// Get the renderer font
	PLRenderer::Font *pRendererFont = static_cast<PLRenderer::Font*>(m_cRendererFont.GetResource());

	// Is the renderer font already there?
	if (!pRendererFont) {
		// Get the PixelLight ingame GUI implementation
		GuiPL *pGuiPL = static_cast<GuiPL*>(m_pFont->GetGui()->GetImpl());
		if (pGuiPL) {
			// Get the renderer instance
			PLRenderer::Renderer *pRenderer = pGuiPL->GetRenderer();
			if (pRenderer) {
				pRendererFont = reinterpret_cast<PLRenderer::Font*>(pRenderer->GetFontManager().GetFontTexture(m_pFont->GetFilename(), m_pFont->GetHeight()));
				m_cRendererFont.SetResource(pRendererFont);
			}
		}
	}

	// Return the renderer font
	return pRendererFont;
}


//[-------------------------------------------------------]
//[ Public virtual FontImpl functions                     ]
//[-------------------------------------------------------]
bool FontPL::LoadFont(const String &sFamily, uint32 nHeight, uint32 nWeight, EFontStyle nStyle)
{
	// Not supported within the PixelLight ingame GUI

	// Error!
	return false;
}

bool FontPL::LoadFont(const String &sFilename, uint32 nHeight)
{
	// Do not destroy the renderer font, we might need it again...

	// Just set the font pointer to null, the font manager will do the rest
	m_cRendererFont.SetResource(nullptr);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
