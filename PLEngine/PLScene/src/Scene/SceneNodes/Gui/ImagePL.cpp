/*********************************************************\
 *  File: ImagePL.cpp                                    *
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
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageEffects.h>
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Resources/Image.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include "PLScene/Scene/SceneNodes/Gui/GuiPL.h"
#include "PLScene/Scene/SceneNodes/Gui/ImagePL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLGui;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImagePL::ImagePL(PLGui::Image &cImage) : ImageImpl(cImage),
	m_pImage(&cImage),
	m_pTextureBuffer(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ImagePL::~ImagePL()
{
	// Clean up
	Unload();
}

/**
*  @brief
*    Unload image
*/
void ImagePL::Unload()
{
	// Destroy the renderer texture buffer
	if (m_pTextureBuffer) {
		delete m_pTextureBuffer;
		m_pTextureBuffer = nullptr;
	}
}

/**
*  @brief
*    Returns the texture buffer
*/
PLRenderer::TextureBuffer *ImagePL::GetTextureBuffer()
{
	return m_pTextureBuffer;
}


//[-------------------------------------------------------]
//[ Public virtual ImageImpl functions                    ]
//[-------------------------------------------------------]
bool ImagePL::Load(const String &sFilename)
{
	// Check parameter
	if (sFilename.GetLength()) {
		// Delete image
		Unload();

		// Get the PixelLight ingame GUI implementation
		GuiPL *pGuiPL = (GuiPL*)m_pImage->GetGui()->GetImpl();
		if (pGuiPL) {
			// Get the renderer instance
			PLRenderer::Renderer *pRenderer = pGuiPL->GetRenderer();
			if (pRenderer) {
				// Load the image
				PLGraphics::Image cImage;
				if (cImage.Load(sFilename)) {
					// Create rectancle texture buffer
					m_pTextureBuffer = pRenderer->CreateTextureBufferRectangle(cImage);
					if (m_pTextureBuffer) {
						m_sFilename   = sFilename;
						m_nColorDepth = 32;

						// Get width and height
						if (m_pTextureBuffer->GetType() == PLRenderer::Resource::TypeTextureBuffer2D)
							m_vSize = ((const PLRenderer::TextureBuffer2D*)m_pTextureBuffer)->GetSize();
						else
							m_vSize = ((const PLRenderer::TextureBufferRectangle*)m_pTextureBuffer)->GetSize();

						// Done
						return true;
					}
				}
			}
		}
	}

	// Error!
	m_sFilename		= "";
	m_vSize.x		= 0;
	m_vSize.y		= 0;
	m_nColorDepth	= 0;
	return false;
}

bool ImagePL::LoadWithColorKey(const String &sFilename, const Color3 &cColor)
{
	// Check parameter
	if (sFilename.GetLength()) {
		// Delete image
		Unload();

		// Get the PixelLight ingame GUI implementation
		GuiPL *pGuiPL = (GuiPL*)m_pImage->GetGui()->GetImpl();
		if (pGuiPL) {
			// Get the renderer instance
			PLRenderer::Renderer *pRenderer = pGuiPL->GetRenderer();
			if (pRenderer) {
				// Load the image
				PLGraphics::Image cImage;
				if (cImage.Load(sFilename)) {
					// Apply color key
					cImage.ApplyEffect(ImageEffects::ColorKey(cColor, 0.0f));

					// Create rectancle texture buffer
					m_pTextureBuffer = pRenderer->CreateTextureBufferRectangle(cImage);
					if (m_pTextureBuffer) {
						m_sFilename   = sFilename;
						m_nColorDepth = 32;

						// Get width and height
						if (m_pTextureBuffer->GetType() == PLRenderer::Resource::TypeTextureBuffer2D)
							m_vSize = ((const PLRenderer::TextureBuffer2D*)m_pTextureBuffer)->GetSize();
						else
							m_vSize = ((const PLRenderer::TextureBufferRectangle*)m_pTextureBuffer)->GetSize();

						// Done
						return true;
					}
				}
			}
		}
	}

	// Error!
	m_sFilename		= "";
	m_vSize.x		= 0;
	m_vSize.y		= 0;
	m_nColorDepth	= 0;
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
