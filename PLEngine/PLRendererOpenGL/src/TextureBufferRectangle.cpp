/*********************************************************\
 *  File: TextureBufferRectangle.cpp                     *
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
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/TextureBufferRectangle.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
TextureBufferRectangle::~TextureBufferRectangle()
{
	if (m_nOpenGLTexture)
		glDeleteTextures(1, &m_nOpenGLTexture);

	// Update renderer statistics
	((PLRenderer::RendererBackend&)GetRenderer()).GetStatisticsT().nTextureBuffersNum--;
	((PLRenderer::RendererBackend&)GetRenderer()).GetStatisticsT().nTextureBuffersMem -= GetTotalNumOfBytes();
}

/**
*  @brief
*    Returns the OpenGL resource ID of the texture buffer
*/
uint32 TextureBufferRectangle::GetOpenGLTexture() const
{
	return m_nOpenGLTexture;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TextureBufferRectangle::TextureBufferRectangle(PLRenderer::Renderer &cRenderer, Image &cImage, EPixelFormat nInternalFormat, uint32 nFlags) :
	PLRenderer::TextureBufferRectangle(cRenderer, nFlags),
	m_nOpenGLTexture(0)
{
	// Get the OpenGL renderer instance
	Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

	// Update renderer statistics
	cRendererOpenGL.GetStatisticsT().nTextureBuffersNum++;

	// Initialize sampler states
	MemoryManager::Set(m_nSamplerState, PLRenderer::Sampler::Unknown, sizeof(uint32)*PLRenderer::Sampler::Number);

	// Choose the texture buffer pixel formats which should be used
	EPixelFormat nImageFormat;
	bool bUsePreCompressedData;
	m_nFormat = cRendererOpenGL.ChooseFormats(cImage, nInternalFormat, nFlags, nImageFormat, bUsePreCompressedData);

	// Get the first image part
	const ImagePart *pImagePart = cImage.GetPart(0);
	if (pImagePart) {
		// Get the first image buffer
		const ImageBuffer *pImageBuffer = pImagePart->GetMipmap(0);
		if (pImageBuffer) {
			// Get API pixel format
			uint32 *pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
			if (pAPIPixelFormat) {
				// Is this a compressed texture buffer pixel format?
				const bool bCompressedFormat = IsCompressedFormat();

				// Get uncompressed image format information
				EPixelFormat nImageFormatUncompressed     = GetFormatFromImage(cImage, true);
				uint32		 nAPIImageFormatUncompressed  = cRendererOpenGL.GetOpenGLPixelFormat(nImageFormatUncompressed);
				uint32		 nImageDataFormatUncompressed = cRendererOpenGL.GetOpenGLDataFormat(nImageFormatUncompressed);

				// Get the size
				m_vSize.x = pImageBuffer->GetSize().x;
				m_vSize.y = pImageBuffer->GetSize().y;

				// Create OpenGL texture buffer
				glGenTextures(1, &m_nOpenGLTexture);
				glBindTexture(GL_TEXTURE_RECTANGLE_EXT, m_nOpenGLTexture);

				// Setup depth format stuff
				if (m_nFormat == D16 || m_nFormat == D24 || m_nFormat == D32) {
					// Enable shadow comparison
					glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

					// Shadow comparison should be true (ie not in shadow) if r<=texture buffer
					glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

					// THIS is really important, if we choose other filtering there may be a crash...
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				}

				// Upload the texture buffer
				m_nNumOfMipmaps = pImagePart->GetNumOfMipmaps() - 1;
				bool bMipmaps = nFlags & Mipmaps;


				// [TODO] Rectangle texture buffers with mipmaps possible?
				bMipmaps		= false;
				m_nNumOfMipmaps = 0;


				if (!m_nNumOfMipmaps && bMipmaps) {
					// Calculate the number of mipmaps
					m_nNumOfMipmaps = (uint32)Math::Log2(float(Math::Max(m_vSize.x, m_vSize.y)));

					// Build mipmaps automatically, no pre compressed image data can be used
					gluBuild2DMipmaps(GL_TEXTURE_RECTANGLE_EXT, *pAPIPixelFormat, m_vSize.x, m_vSize.y, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->GetData());

					// If compressed internal format, check whether all went fine
					if (bCompressedFormat) {
						GLint nCompressed;
						glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_EXT, 0, GL_TEXTURE_COMPRESSED_ARB, &nCompressed);
						if (!nCompressed) {
							// There was an error, use no compression
							m_nFormat = nImageFormat;
							pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
							if (pAPIPixelFormat)
								gluBuild2DMipmaps(GL_TEXTURE_RECTANGLE_EXT, *pAPIPixelFormat, m_vSize.x, m_vSize.y, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->GetData());
						}
					}

					// Calculate the total number of bytes this texture buffer requires
					for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++)
						m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
				} else {
					// Ignore mipmaps?
					if (!bMipmaps)
						m_nNumOfMipmaps = 0; // Jep, we do not want to have any mipmaps for this texture buffer

					// Use given mipmaps
					Vector2i vSize;
					uint32 nLevel = 0;
					for (; nLevel<m_nNumOfMipmaps+1; nLevel++) {
						// Get the mipmap image buffer
						const ImageBuffer *pMipmapImageBuffer = pImagePart->GetMipmap(nLevel);
						if (pMipmapImageBuffer) {
							// Get the size of this mipmap level
							vSize.x = pMipmapImageBuffer->GetSize().x;
							vSize.y = pMipmapImageBuffer->GetSize().y;

							// Upload the texture buffer
							if (bUsePreCompressedData && pMipmapImageBuffer->HasCompressedData())
								glCompressedTexImage2DARB(GL_TEXTURE_RECTANGLE_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, 0, pMipmapImageBuffer->GetCompressedDataSize(), pMipmapImageBuffer->GetCompressedData());
							else
								glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pMipmapImageBuffer->GetData());

							// If compressed internal format, check whether all went fine
							if (bCompressedFormat) {
								GLint nCompressed;
								glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_EXT, nLevel, GL_TEXTURE_COMPRESSED_ARB, &nCompressed);
								if (!nCompressed) {
									// There was an error, use no compression as fallback
									m_nFormat = nImageFormat;
									pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
									if (pAPIPixelFormat)
										glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pMipmapImageBuffer->GetData());
								}
							}
						}

						// Update the total number of bytes this texture buffer requires
						m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
					}

					// We have to define all mipmap levels down to 1x1 otherwise the texture buffer is invalid when we try to use any min
					// filter that uses mipmaps. OpenGL "normally" uses white color when invalid/incomplete texture buffer is enabled.
					if (bMipmaps && (vSize.x != 1 || vSize.y != 1)) {
						// Write a warning into the log
						PL_LOG(Warning, String::Format("Lowest mipmap is %dx%d, but should be 1x1! Missing mipmap levels will be white!", vSize.x, vSize.y))

						// If we don't define all mipmap levels down to 1x1 'mysterious' graphics bugs may occure were it is not
						// always easy to pinpoint the problem directly to the mipmaps. So, to avoid frustration during bug finding,
						// we just create the missing mipmap levels down to 1x1 with a white color - so it's possible to 'see' which texture
						// isn't correct without reading the log message from above. (for some people it appears to be hard to read logs *g*)
						char *pszBuffer = nullptr;
						do {
							// First at all, 'half' the current dimension
							if (vSize.x > 1)
								vSize.x /= 2;
							if (vSize.y > 1)
								vSize.y /= 2;

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
							glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pszBuffer);

							// Update the mipmap level counter
							nLevel++;
						} while (vSize.x != 1 || vSize.y != 1);

						// Cleanup your white buffer
						if (pszBuffer)
							delete [] pszBuffer;
					}
				}

				// Update renderer statistics
				cRendererOpenGL.GetStatisticsT().nTextureBuffersMem += GetTotalNumOfBytes();
			}
		}
	}
}

/**
*  @brief
*    Constructor
*/
TextureBufferRectangle::TextureBufferRectangle(PLRenderer::Renderer &cRenderer, const Vector2i &vSize, EPixelFormat nInternalFormat, uint32 nFlags) :
	PLRenderer::TextureBufferRectangle(cRenderer, nFlags),
	m_nOpenGLTexture(0)
{
	// Get the OpenGL renderer instance
	Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

	// Update renderer statistics
	cRendererOpenGL.GetStatisticsT().nTextureBuffersNum++;

	// Initialize sampler states
	MemoryManager::Set(m_nSamplerState, PLRenderer::Sampler::Unknown, sizeof(uint32)*PLRenderer::Sampler::Number);

	// Get pixel format
	m_nFormat = nInternalFormat;

	// Get API pixel format
	const uint32 *pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
	if (pAPIPixelFormat) {
		// Set size
		m_vSize = vSize;

		// Get format
		const uint32 nPixelFormat = cRendererOpenGL.GetOpenGLPixelFormat(m_nFormat);
		const uint32 nDataFormat  = cRendererOpenGL.GetOpenGLDataFormat(m_nFormat);

		// Create OpenGL texture buffer
		glGenTextures(1, &m_nOpenGLTexture);
		glBindTexture(GL_TEXTURE_RECTANGLE_EXT, m_nOpenGLTexture);

		// Setup depth format stuff
		if (m_nFormat == D16 || m_nFormat == D24 || m_nFormat == D32) {
			// Enable shadow comparison
			glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

			// Shadow comparison should be true (ie not in shadow) if r<=texture buffer
			glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

			// THIS is really important, if we choose other filtering there may be a crash...
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		// Build mipmaps automatically on the GPU? (not supported...)
	/*	if ((m_nFlags & Mipmaps) && cRendererOpenGL.IsGL_SGIS_generate_mipmap()) {
			// Calculate the number of mipmaps - it's not allowed to access this automatic mipmaps??
	//		m_nNumOfMipmaps = (uint32)Math::Log2(float(Math::Max(m_vSize.x, m_vSize.y)));

			// Enable automatic mipmap generation
			glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_GENERATE_MIPMAP_SGIS, true);
		}*/

		// Create texture buffer
		glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, *pAPIPixelFormat, m_vSize.x, m_vSize.y, 0, nPixelFormat, nDataFormat, nullptr);

		// If compressed internal format, check whether all went fine
		if (IsCompressedFormat()) {
			GLint nCompressed;
			glGetTexLevelParameteriv(GL_TEXTURE_RECTANGLE_EXT, 0, GL_TEXTURE_COMPRESSED_ARB, &nCompressed);
			if (!nCompressed) {
				// There was an error, use no compression
				m_nFormat = R8G8B8A8;
				pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
				if (pAPIPixelFormat)
					glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, 0, *pAPIPixelFormat,	m_vSize.x, m_vSize.y, 0, nPixelFormat, nDataFormat, nullptr);
			}
		}

		// Get the total number of bytes this texture buffer requires
		m_nTotalNumOfBytes = GetNumOfBytes();

		// Update renderer statistics
		cRendererOpenGL.GetStatisticsT().nTextureBuffersMem += GetTotalNumOfBytes();
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::TextureBuffer functions    ]
//[-------------------------------------------------------]
bool TextureBufferRectangle::Upload(uint32 nMipmap, EPixelFormat nFormat, const void *pData, uint8 nFace)
{
	// Check parameters
	if (nMipmap <= m_nNumOfMipmaps && nFormat != Unknown && pData && !nFace) {
		// Get the OpenGL renderer instance
		const Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

		// Get API pixel format
		uint32 *pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
		if (pAPIPixelFormat) {
			// [TODO] At the moment, rectangle texture buffers don't support mipmaps, so m_nNumOfMipmaps is always 0 :)
			// Get the size of this mipmap level
			const Vector2i vSize = GetSize();

			// Compressed format?
			if (IsCompressedFormat(nFormat)) {
				// Internal format MUST be the same as the given format
				if (m_nFormat != nFormat)
					return false; // Error!

				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_BINDING_RECTANGLE_ARB, m_nOpenGLTexture);

				// Get the number of bytes
				const uint32 nNumOfBytes = GetNumOfBytes(nMipmap);

				// Upload
				glCompressedTexImage2DARB(GL_TEXTURE_RECTANGLE_EXT, nMipmap, *pAPIPixelFormat, vSize.x, vSize.y, 0, nNumOfBytes, pData);
			} else {
				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_BINDING_RECTANGLE_ARB, m_nOpenGLTexture);

				// Upload
				const uint32 nPixelFormat = cRendererOpenGL.GetOpenGLPixelFormat(nFormat);
				const uint32 nDataFormat  = cRendererOpenGL.GetOpenGLDataFormat(nFormat);
				glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, nMipmap, *pAPIPixelFormat, vSize.x, vSize.y, 0, nPixelFormat, nDataFormat, pData);
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool TextureBufferRectangle::Download(uint32 nMipmap, EPixelFormat nFormat, void *pData, uint8 nFace)
{
	// Check parameters
	if (nMipmap > m_nNumOfMipmaps || nFormat == Unknown || !pData || nFace)
		return false; // Error!

	// Compressed format?
	if (IsCompressedFormat(nFormat)) {
		// Internal format MUST be the same as the given format
		if (m_nFormat != nFormat)
			return false; // Error!

		// Bind this texture buffer
		glBindTexture(GL_TEXTURE_BINDING_RECTANGLE_ARB, m_nOpenGLTexture);

		// Download
		glGetCompressedTexImageARB(GL_TEXTURE_RECTANGLE_EXT, nMipmap, pData);
	} else {
		// Bind this texture buffer
		glBindTexture(GL_TEXTURE_BINDING_RECTANGLE_ARB, m_nOpenGLTexture);

		// Get the OpenGL renderer instance
		const Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

		// Download
		const uint32 nPixelFormat = cRendererOpenGL.GetOpenGLPixelFormat(nFormat);
		const uint32 nDataFormat  = cRendererOpenGL.GetOpenGLDataFormat(nFormat);
		glGetTexImage(GL_TEXTURE_RECTANGLE_EXT, nMipmap, nPixelFormat, nDataFormat, pData);
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::TextureBuffer functions   ]
//[-------------------------------------------------------]
bool TextureBufferRectangle::MakeCurrent(uint32 nStage)
{
	// Check if there are renderer information
	if (GetRenderer().GetTextureBuffer(nStage) != this) {
		if (!GetRenderer().SetTextureBuffer(nStage, this))
			return true; // Done
	}

	// Make this texture buffer to the renderers current one
	glEnable(GL_TEXTURE_RECTANGLE_EXT);
	glBindTexture(GL_TEXTURE_RECTANGLE_EXT, m_nOpenGLTexture);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void TextureBufferRectangle::BackupDeviceData(uint8 **ppBackup)
{


	// [HACK] ?It looks like 'glGetTexImage(GL_TEXTURE_RECTANGLE_EXT' is not working with RGB, I tested it
	// on a NVIDIA and ATI card and both times we get the data slightly 'shifted'?
	if (m_nFormat == R8G8B8) {
		m_nFormat = R8G8B8A8;
		m_nTotalNumOfBytes = GetNumOfBytes(0);
	}


	// Allocate memory
	const uint32 nTotalNumOfBytes = GetTotalNumOfBytes();
	if (nTotalNumOfBytes) {
		*ppBackup = new uint8[nTotalNumOfBytes];
		if (*ppBackup) {
			// Prepare for backup
			glEnable(GL_TEXTURE_RECTANGLE_EXT);
			glBindTexture(GL_TEXTURE_RECTANGLE_EXT, m_nOpenGLTexture);

			// Backup
			uint8 *pData = *ppBackup;
			if (IsCompressedFormat()) {
				// Loop through all mipmaps
				for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++) {
					// Get the data from the GPU
					glGetCompressedTexImageARB(GL_TEXTURE_RECTANGLE_EXT, nLevel, pData);

					// Next level, please
					pData += GetNumOfBytes(nLevel);
				}
			} else {
				// Get the OpenGL renderer instance
				const Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

				// Get format information
				const uint32 nPixelFormat = cRendererOpenGL.GetOpenGLPixelFormat(m_nFormat);
				const uint32 nDataFormat  = cRendererOpenGL.GetOpenGLDataFormat(m_nFormat);

				// Loop through all mipmaps
				for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++) {
					// Get the data from the GPU
					glGetTexImage(GL_TEXTURE_RECTANGLE_EXT, nLevel, nPixelFormat, nDataFormat, pData);

					// Next level, please
					pData += GetNumOfBytes(nLevel);
				}
			}

			// Destroy this OpenGL texture buffer
			if (m_nOpenGLTexture) {
				glDeleteTextures(1, &m_nOpenGLTexture);
				m_nOpenGLTexture = 0;
			}
		}
	} else {
		*ppBackup = nullptr;
	}
}

void TextureBufferRectangle::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup) {
		glGenTextures(1, &m_nOpenGLTexture);
		glBindTexture(GL_TEXTURE_RECTANGLE_EXT, m_nOpenGLTexture);

		// Get the OpenGL renderer instance
		const Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

		// Get API pixel format
		const uint32 nPixelFormat = cRendererOpenGL.GetOpenGLPixelFormat(m_nFormat);
		const uint32 nDataFormat  = cRendererOpenGL.GetOpenGLDataFormat(m_nFormat);
		const uint32 *pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
		if (pAPIPixelFormat) {
			// Is this a compressed texture buffer pixel format?
			const bool bCompressedFormat = IsCompressedFormat();

			// Data pointer
			const uint8 *pData = *ppBackup;

			// Loop through all mipmaps
			for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++) {
				// [TODO] At the moment, rectangle texture buffers don't support mipmaps, so m_nNumOfMipmaps is always 0 :)
				// Get the size of this mipmap level
				const Vector2i vSize = GetSize();
	//			Vector2i nSize = GetSize(nLevel);

				// Get the number of bytes
				const uint32 nNumOfBytes = GetNumOfBytes(nLevel);

				// Upload the texture buffer
				if (bCompressedFormat)
					glCompressedTexImage2DARB(GL_TEXTURE_RECTANGLE_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, 0, nNumOfBytes, pData);
				else
					glTexImage2D(GL_TEXTURE_RECTANGLE_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, 0, nPixelFormat, nDataFormat, pData);

				// Next level, please
				pData += nNumOfBytes;
			}
		}

		// Delete memory
		delete [] *ppBackup;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
