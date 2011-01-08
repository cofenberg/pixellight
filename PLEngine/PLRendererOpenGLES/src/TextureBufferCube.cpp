/*********************************************************\
 *  File: TextureBufferCube.cpp                          *
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
#include <PLGeneral/Log/Log.h>
#include <PLMath/Math.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/Renderer/Backend/RendererBackend.h>
#include "PLRendererOpenGLES/Renderer.h"
#include "PLRendererOpenGLES/TextureBufferCube.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
TextureBufferCube::~TextureBufferCube()
{
	// Delete the OpenGL ES texture
	glDeleteTextures(1, &m_nOpenGLESTexture);

	// Update renderer statistics
	((PLRenderer::RendererBackend&)GetRenderer()).GetStatisticsT().nTextureBuffersNum--;
	((PLRenderer::RendererBackend&)GetRenderer()).GetStatisticsT().nTextureBuffersMem -= GetTotalNumOfBytes();
}

/**
*  @brief
*    Returns the OpenGL ES object of the texture buffer
*/
GLuint TextureBufferCube::GetOpenGLESTexture() const
{
	return m_nOpenGLESTexture;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TextureBufferCube::TextureBufferCube(PLRenderer::Renderer &cRenderer, Image &cImage, EPixelFormat nInternalFormat, uint32 nFlags) :
	PLRenderer::TextureBufferCube(cRenderer, nFlags),
	m_nOpenGLESTexture(0)
{
	// Get the OpenGL ES renderer instance
	Renderer &cRendererOpenGLES = (Renderer&)cRenderer;

	// Update renderer statistics
	cRendererOpenGLES.GetStatisticsT().nTextureBuffersNum++;

	// Choose the texture buffer pixel formats which should be used
	EPixelFormat nImageFormat;
	bool bUsePreCompressedData;
	m_nFormat = cRendererOpenGLES.ChooseFormats(cImage, nInternalFormat, nFlags, nImageFormat, bUsePreCompressedData);

	// Get the first image part
	const ImagePart *pImagePart = cImage.GetPart(0);
	if (pImagePart) {
		// Get the first image buffer
		const ImageBuffer *pImageBuffer = pImagePart->GetMipmap(0);
		if (pImageBuffer) {
			// Get API pixel format
			uint32 *pAPIPixelFormat = cRendererOpenGLES.GetAPIPixelFormat(m_nFormat);
			if (pAPIPixelFormat) {
				// Is this a compressed texture buffer pixel format?
				const bool bCompressedFormat = IsCompressedFormat();

				// Get uncompressed image format information
				EPixelFormat nImageFormatUncompressed     = GetFormatFromImage(cImage, true);
				uint32		 nAPIImageFormatUncompressed  = cRendererOpenGLES.GetOpenGLESPixelFormat(nImageFormatUncompressed);
				uint32		 nImageDataFormatUncompressed = cRendererOpenGLES.GetOpenGLESDataFormat(nImageFormatUncompressed);

				// Set the size and number of mipmaps
				m_nSize		    = pImageBuffer->GetSize().x;
				m_nNumOfMipmaps = pImagePart->GetNumOfMipmaps() - 1;

				// Create OpenGL ES texture buffer
				glGenTextures(1, &m_nOpenGLESTexture);
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_nOpenGLESTexture);

				// Ignore mipmaps?
				const bool bMipmaps = (nFlags & Mipmaps);
				bool bAutomaticMipmaps = false;
				if (!bMipmaps)
					m_nNumOfMipmaps = 0; // Jep, we do not want to have any mipmaps for this texture buffer
				else {
					// Calculate the number of mipmaps if required
					if (!m_nNumOfMipmaps) {
						m_nNumOfMipmaps = (uint32)Math::Log2(float(m_nSize));
						bAutomaticMipmaps = true;
					}
				}

				// Upload the texture buffer
				for (uint8 nFace=0; nFace<6; nFace++) {
					// Get the current image
					ImagePart *pFaceImagePart = cImage.GetPartBySemantics(ImagePartCubeSidePosX + nFace);
					if (pFaceImagePart) {
						// Upload
						if (bAutomaticMipmaps) {
							// Get the first image buffer
							ImageBuffer *pFaceImageBuffer = pFaceImagePart->GetMipmap(0);
							if (pFaceImageBuffer) {
								// Upload the texture buffer
								if (bUsePreCompressedData && pFaceImageBuffer->HasCompressedData())
									glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, 0, *pAPIPixelFormat, m_nSize, m_nSize, 0, pFaceImageBuffer->GetCompressedDataSize(), pFaceImageBuffer->GetCompressedData());
								else
									glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, 0, *pAPIPixelFormat, m_nSize, m_nSize, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pFaceImageBuffer->GetData());

								// If compressed internal format, we would check whether all went fine - but OpenGL ES 2.0 provides no functionality for this :/

								// Let OpenGL ES create the mipmap chain for us
								glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

								// Update the total number of bytes this texture buffer requires
								for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++)
									m_nTotalNumOfBytes += GetNumOfBytes(nLevel)/6;
							}
						} else {
							// Use given mipmaps
							uint32 nSize = 0, nLevel = 0;
							for (; nLevel<=m_nNumOfMipmaps; nLevel++) {
								// Get the mipmap image buffer
								const ImageBuffer *pMipmapImageBuffer = pFaceImagePart->GetMipmap(nLevel);
								if (pMipmapImageBuffer) {
									// Get the size of this mipmap level
									nSize = pMipmapImageBuffer->GetSize().x;

									// Upload the texture buffer
									if (bUsePreCompressedData && pMipmapImageBuffer->HasCompressedData())
										glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, nLevel, *pAPIPixelFormat, nSize, nSize, 0, pMipmapImageBuffer->GetCompressedDataSize(), pMipmapImageBuffer->GetCompressedData());
									else
										glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, nLevel, *pAPIPixelFormat, nSize, nSize, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pMipmapImageBuffer->GetData());

									// If compressed internal format, we would check whether all went fine - but OpenGL ES 2.0 provides no functionality for this :/
								}

								// Update the total number of bytes this texture buffer requires
								m_nTotalNumOfBytes += GetNumOfBytes(nLevel)/6;
							}

							// We have to define all mipmap levels down to 1x1 otherwise the texture buffer is invalid when we try to use any min
							// filter that uses mipmaps. OpenGL "normally" uses white color when invalid/incomplete texture buffer is enabled.
							if (bMipmaps && nSize != 1) {
								// Write a warning into the log
								PL_LOG(Warning, String::Format("Lowest mipmap is %dx%d, but should be 1x1! Missing mipmap levels will be white!", nSize, nSize))

								// If we don't define all mipmap levels down to 1x1 'mysterious' graphics bugs may occure were it is not
								// always easy to pinpoint the problem directly to the mipmaps. So, to avoid frustration during bug finding,
								// we just create the missing mipmap levels down to 1x1 with a white color - so it's possible to 'see' which texture
								// isn't correct without reading the log message from above. (for some people it appears to be hard to read logs *g*)
								char *pszBuffer = nullptr;
								do {
									// First at all, 'half' the current dimension
									if (nSize > 1)
										nSize /= 2;

									// Update the total number of mipmap levels
									m_nNumOfMipmaps++;

									// Update the total number of bytes this texture buffer requires
									const uint32 nNumOfBytes = GetNumOfBytes(nLevel);
									m_nTotalNumOfBytes += nNumOfBytes;

									// Allocate memory for your white buffer and set it to "white" (we only do this once for the larges one)
									if (!pszBuffer) {
										pszBuffer = new char[nNumOfBytes];
										MemoryManager::Set(pszBuffer, 255, nNumOfBytes);
									}

									// Upload the texture buffer
									glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, nLevel, *pAPIPixelFormat, nSize, nSize, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pszBuffer);

									// Update the mipmap level counter
									nLevel++;
								} while (nSize != 1);

								// Cleanup your white buffer
								if (pszBuffer)
									delete [] pszBuffer;
							}
						}
					}
				}

				// Update renderer statistics
				cRendererOpenGLES.GetStatisticsT().nTextureBuffersMem += GetTotalNumOfBytes();
			}
		}
	}
}

/**
*  @brief
*    Constructor
*/
TextureBufferCube::TextureBufferCube(PLRenderer::Renderer &cRenderer, uint32 nSize, EPixelFormat nInternalFormat, uint32 nFlags) :
	PLRenderer::TextureBufferCube(cRenderer, nFlags),
	m_nOpenGLESTexture(0)
{
	// Get the OpenGL ES renderer instance
	Renderer &cRendererOpenGLES = (Renderer&)GetRenderer();

	// Update renderer statistics
	cRendererOpenGLES.GetStatisticsT().nTextureBuffersNum++;

	// Get pixel format
	m_nFormat = nInternalFormat;

	// Get API pixel format
	const uint32 *pAPIPixelFormat = cRendererOpenGLES.GetAPIPixelFormat(m_nFormat);
	if (pAPIPixelFormat) {
		// Set size
		m_nSize = nSize;

		// Get formats
		const uint32 nPixelFormat = cRendererOpenGLES.GetOpenGLESPixelFormat(m_nFormat);
		const uint32 nDataFormat  = cRendererOpenGLES.GetOpenGLESDataFormat(m_nFormat);

		// Create OpenGL ES texture buffer
		glGenTextures(1, &m_nOpenGLESTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_nOpenGLESTexture);

		// Create texture buffer
		for (uint8 nFace=0; nFace<6; nFace++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, 0, *pAPIPixelFormat, m_nSize, m_nSize, 0, nPixelFormat, nDataFormat, nullptr);

			// If compressed internal format, we would check whether all went fine - but OpenGL ES 2.0 provides no functionality for this :/
		}

		// Build mipmaps automatically on the GPU?
		if (m_nFlags & Mipmaps) {
			// Let OpenGL ES create the mipmap chain for us
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

			// Calculate the number of mipmaps
			m_nNumOfMipmaps = (uint32)Math::Log2(float(m_nSize));
		}

		// Get the total number of bytes this texture buffer requires
		m_nTotalNumOfBytes = GetNumOfBytes();

		// Update renderer statistics
		cRendererOpenGLES.GetStatisticsT().nTextureBuffersMem += GetTotalNumOfBytes();
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::TextureBuffer functions    ]
//[-------------------------------------------------------]
bool TextureBufferCube::Upload(uint32 nMipmap, EPixelFormat nFormat, const void *pData, uint8 nFace)
{
	// Check parameters
	if (nMipmap <= m_nNumOfMipmaps && nFormat != Unknown && pData && nFace <= 5) {
		// Get the OpenGL ES renderer instance
		const Renderer &cRendererOpenGLES = (Renderer&)GetRenderer();

		// Get API pixel format
		const uint32 *pAPIPixelFormat = cRendererOpenGLES.GetAPIPixelFormat(m_nFormat);
		if (pAPIPixelFormat) {
			// Get the size of this mipmap level
			const uint32 nSize = GetSize(nMipmap);

			// Compressed format?
			if (IsCompressedFormat(nFormat)) {
				// Internal format MUST be the same as the given format
				if (m_nFormat != nFormat)
					return false; // Error!

				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_nOpenGLESTexture);

				// Get the number of bytes
				const uint32 nNumOfBytes = GetNumOfBytes(nMipmap)/6;

				// Upload
				glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, nMipmap, *pAPIPixelFormat, nSize, nSize, 0, nNumOfBytes, pData);
			} else {
				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_nOpenGLESTexture);

				// Upload
				const uint32 nPixelFormat = cRendererOpenGLES.GetOpenGLESPixelFormat(nFormat);
				const uint32 nDataFormat  = cRendererOpenGLES.GetOpenGLESDataFormat(nFormat);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+nFace, nMipmap, *pAPIPixelFormat, nSize, nSize, 0, nPixelFormat, nDataFormat, pData);
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool TextureBufferCube::Download(uint32 nMipmap, EPixelFormat nFormat, void *pData, uint8 nFace)
{
	// Error, texture readback is not supported by OpenGL ES 2.0
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::TextureBuffer functions   ]
//[-------------------------------------------------------]
bool TextureBufferCube::MakeCurrent(uint32 nStage)
{
	// [TODO] Remove this method if possible
/*
	// Check if there are renderer information
	if (GetRenderer().GetTextureBuffer(nStage) != this) {
		if (!GetRenderer().SetTextureBuffer(nStage, this))
			return true; // Done
	}
*/
	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES
