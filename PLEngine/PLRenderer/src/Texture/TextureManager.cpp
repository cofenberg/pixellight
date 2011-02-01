/*********************************************************\
 *  File: TextureManager.cpp                             *
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
#include <PLGeneral/Tools/Profiling.h>
#include <PLGeneral/Log/Log.h>
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/ResourceHandler.h"
#include "PLRenderer/Texture/Creator/TextureCreator.h"
#include "PLRenderer/Texture/Texture.h"
#include "PLRenderer/Texture/TextureManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String TextureManager::Default = "Data/Textures/Default.dds";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner renderer context of this manager
*/
RendererContext &TextureManager::GetRendererContext() const
{
	return *m_pRendererContext;
}

/**
*  @brief
*    Returns the texture quality
*/
float TextureManager::GetTextureQuality() const
{
	return m_fTextureQuality;
}

/**
*  @brief
*    Sets the texture quality
*/
void TextureManager::SetTextureQuality(float fQuality)
{
	m_fTextureQuality = fQuality;

	// Ensure the value is inside the specified range
	if (m_fTextureQuality < 0.0f)
		m_fTextureQuality = 0.0f;
	else if (m_fTextureQuality > 1.0f)
		m_fTextureQuality = 1.0f;
}

/**
*  @brief
*    Returns whether the next lower valid texture size should be taken or the higher one
*/
bool TextureManager::GetTextureFit() const
{
	return m_bTextureFitLower;
}

/**
*  @brief
*    Sets whether the next lower valid texture size should be taken or the higher one
*/
void TextureManager::SetTextureFit(bool bLower)
{
	m_bTextureFitLower = bLower;
}

/**
*  @brief
*    Returns whether or not the usage of texture mipmaps is allowed
*/
bool TextureManager::AreTextureMipmapsAllowed() const
{
	return m_bTextureMipmapsAllowed;
}

/**
*  @brief
*    Sets whether or not the usage of Ttxture mipmaps is allowed
*/
void TextureManager::SetTextureMipmapsAllowed(bool bAllowed)
{
	m_bTextureMipmapsAllowed = bAllowed;
}

/**
*  @brief
*    Returns whether or not the usage of texture compression is allowed
*/
bool TextureManager::IsTextureCompressionAllowed() const
{
	return m_bTextureCompressionAllowed;
}

/**
*  @brief
*    Sets whether or not the usage of texture compression is allowed
*/
void TextureManager::SetTextureCompressionAllowed(bool bAllowed)
{
	m_bTextureCompressionAllowed = bAllowed;
}

/**
*  @brief
*    Reloads all textures
*/
bool TextureManager::ReloadTextures()
{
	bool bResult = true; // No error by default

	// Reload every texture
	for (uint32 i=0; i<m_lstResources.GetNumOfElements(); i++) {
		Texture *pTexture = m_lstResources[i];
		if (!pTexture->Load(pTexture->GetName()))
			bResult = false; // Error!
	}

	// Done
	return bResult;
}

/**
*  @brief
*    Creates a new texture
*/
Texture *TextureManager::CreateTexture(const String &sName, TextureBuffer &cTextureBuffer)
{
	// Create
	Texture *pTexture = new Texture(*this, sName);

	// Create the renderer texture resource
	pTexture->m_pTextureBufferHandler = new ResourceHandler();
	cTextureBuffer.AddHandler(*pTexture->m_pTextureBufferHandler);
	pTexture->m_bShareTextureBuffer = true;

	// Done
	return pTexture;
}

/**
*  @brief
*    Creates a texture resource using a texture creator
*/
Texture *TextureManager::CreateTexture(const String &sName, const String &sParameters)
{
	// To keep things as fast as possible we store a pointer to the base class
	// (no hash map operation + quite efficent internal string comparison)
	static const Class *pBaseClass = ClassManager::GetInstance()->GetClass("PLRenderer::TextureCreator");

	// Create the texture creator
	if (pBaseClass) {
		const Class *pClass = ClassManager::GetInstance()->GetClass(sName);
		if (pClass && pClass->IsDerivedFrom(*pBaseClass)) {
			TextureCreator *pTC = static_cast<TextureCreator*>(pClass->Create());
			if (pTC) {
				// Set parameters
				if (sParameters.GetLength())
					pTC->SetValues(sParameters);

				// Create the texture
				Texture *pTexture = pTC->Create(*this, nullptr);

				// Destroy the texture creator
				delete pTC;

				// Return the created texture
				return pTexture;
			}
		}
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TextureManager::TextureManager(RendererContext &cRendererContext) :
	m_pRendererContext(&cRendererContext),
	m_fTextureQuality(1.0f),
	m_bTextureFitLower(true),
	m_bTextureMipmapsAllowed(true),
	m_bTextureCompressionAllowed(true)
{
	PL_LOG(Debug, "Create texture manager")

	// Set manager name
	SetManagerName("Texture manager");

	// Unload unused resources, please
	SetUnloadUnused(true);

	// Load the standard texture
	Texture *pTexture = LoadResource(Default);
	if (pTexture) {
		pTexture->SetProtected(true);
		SetStandard(pTexture);
	}
}

/**
*  @brief
*    Destructor
*/
TextureManager::~TextureManager()
{
	PL_LOG(Debug, "Destroy texture manager")

	// Clear all textures
	Clear();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager functions     ]
//[-------------------------------------------------------]
Texture *TextureManager::CreateResource(const String &sName)
{
	return new Texture(*this, sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
