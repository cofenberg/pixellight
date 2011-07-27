/*********************************************************\
 *  File: FontManager.cpp                                *
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
#include <PLCore/Log/Log.h>
#include <PLCore/File/File.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLRenderer/Renderer/ResourceHandler.h"
#include "PLRenderer/Renderer/FontTexture.h"
#include "PLRenderer/Renderer/FontManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner renderer
*/
Renderer &FontManager::GetRenderer() const
{
	return *m_pRenderer;
}

/**
*  @brief
*    Returns the default texture font
*/
FontTexture *FontManager::GetDefaultFontTexture() const
{
	return reinterpret_cast<FontTexture*>(m_pDefaultFontTextureHandler->GetResource());
}

/**
*  @brief
*    Sets the default texture font
*/
void FontManager::SetDefaultFontTexture(FontTexture *pFont)
{
	m_pDefaultFontTextureHandler->SetResource(pFont);
}

/**
*  @brief
*    Returns a texture font
*/
FontTexture *FontManager::GetFontTexture(const String &sFilename, uint32 nSize, uint32 nResolution)
{
	// Check the parameters
	if (sFilename.GetLength() && nSize) {
		Iterator<FontTexture*> cIterator = m_lstFontTexture.GetIterator();
		while (cIterator.HasNext()) {
			FontTexture *pFont = cIterator.Next();
			if (pFont->GetFilename() == sFilename && pFont->GetSize() == nSize && pFont->GetResolution() == nResolution)
				return pFont; // Return the found font
		}

		// Create a new font
		FontTexture *pFont = reinterpret_cast<FontTexture*>(CreateFontTexture(sFilename, nSize, nResolution));
		if (pFont)
			m_lstFontTexture.Add(pFont);

		// Return the new font
		return pFont;
	} else {
		// Error!
		return nullptr;
	}
}

/**
*  @brief
*    Clears all texture fonts
*/
void FontManager::ClearFontTexture()
{
	// Texture fonts unregister within the FontTexture destructor
	while (m_lstFontTexture.GetNumOfElements())
		delete m_lstFontTexture[0];
}


//[-------------------------------------------------------]
//[ Public virtual FontManager functions                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a texture font
*/
Font *FontManager::CreateFontTexture(const String &sFilename, uint32 nSize, uint32 nResolution)
{
	Font *pFont = nullptr;

	// Try to open the file
	File cFile;
	if (LoadableManager::GetInstance()->OpenFile(cFile, sFilename, false)) {
		// Create the font
		pFont = CreateFontTexture(cFile, nSize, nResolution);
	} else {
		PL_LOG(Error, "Failed to open font file '" + sFilename + '\'')
	}

	// Return the created font
	return pFont;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
FontManager::FontManager(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pDefaultFontTextureHandler(new ResourceHandler())
{
}

/**
*  @brief
*    Destructor
*/
FontManager::~FontManager()
{
	// Cleanup
	delete m_pDefaultFontTextureHandler;
	ClearFontTexture();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
FontManager::FontManager(const FontManager &cSource) :
	m_pRenderer(nullptr),
	m_pDefaultFontTextureHandler(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
FontManager &FontManager::operator =(const FontManager &cSource)
{
	// No implementation because the copy constructor is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
