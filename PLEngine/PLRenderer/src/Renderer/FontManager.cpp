/*********************************************************\
 *  File: FontManager.cpp                                *
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
#include <PLGeneral/Log/Log.h>
#include <PLGeneral/File/File.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLRenderer/Renderer/ResourceHandler.h"
#include "PLRenderer/Renderer/FontTexture.h"
#include "PLRenderer/Renderer/FontManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
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
	return (FontTexture*)m_pDefaultFontTextureHandler->GetResource();
}

/**
*  @brief
*    Sets the default texture font
*/
void FontManager::SetDefaultFontTexture(FontTexture *pFont)
{
	m_pDefaultFontTextureHandler->SetResource((Resource*)pFont);
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
		FontTexture *pFont = (FontTexture*)CreateFontTexture(sFilename, nSize, nResolution);
		if (pFont)
			m_lstFontTexture.Add(pFont);

		// Return the new font
		return pFont;
	} else {
		// Error!
		return NULL;
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
	Font *pFont = NULL;

	// Because absolute filenames can be accessed fastest by the file system, we first give
	// the file system an absolute filename which is hopefully the correct one... if
	// not, we must search the file which is quite slow...
	File cFile;
	Url cUrl(sFilename);
	if (cUrl.IsAbsolute()) {
		// The given filename is already absolute! :)
		cFile.Assign(sFilename);
	} else {
		// Loop through all base directories
		for (uint32 nBaseDir=0; nBaseDir<LoadableManager::GetInstance()->GetNumOfBaseDirs() && !cFile.IsFile(); nBaseDir++) {
			String sBaseDir = LoadableManager::GetInstance()->GetBaseDir(nBaseDir);

			// Construct absolute filename and check file
			String sAbsFilename = sBaseDir + sFilename;
			cFile.Assign(sAbsFilename);

			// Is this a correct file?
			if (!cFile.IsFile()) {
				// Try to open the file directly
				sAbsFilename = sBaseDir + sFilename;
				cFile.Assign(sAbsFilename);
			}
		}
	}

	// Try to open the file
	if (cFile.Open(File::FileRead)) {
		// Create the font
		pFont = CreateFontTexture(cFile, nSize, nResolution);
	} else {
		PL_LOG(Error, "Failed to open font file '" + sFilename + '\'');
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
	m_pRenderer(NULL),
	m_pDefaultFontTextureHandler(NULL)
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
