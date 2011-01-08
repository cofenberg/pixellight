/*********************************************************\
 *  File: TextureBuffer3D.cpp                            *
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
#include "PLRendererOpenGL/TextureBuffer3D.h"


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
TextureBuffer3D::~TextureBuffer3D()
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
uint32 TextureBuffer3D::GetOpenGLTexture() const
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
TextureBuffer3D::TextureBuffer3D(PLRenderer::Renderer &cRenderer, Image &cImage, EPixelFormat nInternalFormat, uint32 nFlags) :
	PLRenderer::TextureBuffer3D(cRenderer, nFlags),
	m_nOpenGLTexture(0)
{
	// Get the OpenGL renderer instance
	Renderer &cRendererOpenGL = (Renderer&)cRenderer;

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

				// Set the size
				m_vSize = pImageBuffer->GetSize();

				// Create OpenGL texture buffer
				glGenTextures(1, &m_nOpenGLTexture);
				glBindTexture(GL_TEXTURE_3D_EXT, m_nOpenGLTexture);

				// Upload the texture buffer
				m_nNumOfMipmaps = pImagePart->GetNumOfMipmaps() - 1;
				const bool bMipmaps = nFlags & Mipmaps;
				if (!m_nNumOfMipmaps && bMipmaps) {
					// Calculate the number of mipmaps
					m_nNumOfMipmaps = (uint32)Math::Log2(float(Math::Max(Math::Max(m_vSize.x, m_vSize.y), m_vSize.z)));

					// Try to build mipmaps automatically on the GPU
					if (cRendererOpenGL.IsGL_SGIS_generate_mipmap()) {
						glTexParameteri(GL_TEXTURE_3D_EXT, GL_GENERATE_MIPMAP_SGIS, true);

						// Upload the texture buffer
						if (bUsePreCompressedData)
							glCompressedTexImage3DARB(GL_TEXTURE_3D_EXT, 0, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z, 0, pImageBuffer->GetCompressedDataSize(), pImageBuffer->GetCompressedData());
						else 
							glTexImage3DEXT(GL_TEXTURE_3D_EXT, 0, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->GetData());

						// If compressed internal format, check whether all went fine
						if (bCompressedFormat) {
							GLint nCompressed;
							glGetTexLevelParameteriv(GL_TEXTURE_3D_EXT, 0, GL_TEXTURE_COMPRESSED_ARB, &nCompressed);
							if (!nCompressed) {
								// There was an error, use no compression
								m_nFormat = nImageFormat;
								pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
								if (pAPIPixelFormat)
									glTexImage3DEXT(GL_TEXTURE_3D_EXT, 0, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->GetData());
							}
						}
					} else {
						// [TODO] It looks like that gluBuild3DMipmaps() is NOT supported under Windows :(
						m_nNumOfMipmaps = 0;
						glTexImage3DEXT(GL_TEXTURE_3D_EXT, 0, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->GetData());

						// No pre compressed image data can be used
						// gluBuild3DMipmaps(GL_TEXTURE_3D_EXT, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z,
						//				  nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->GetData());

						// If compressed internal format, check whether all went fine
						// if (bCompressedFormat) {
						// 	GLint nCompressed;
						// 	glGetTexLevelParameteriv(GL_TEXTURE_3D_EXT, 0, GL_TEXTURE_COMPRESSED_ARB, &nCompressed);
						// 	if (!nCompressed) { // There was an error, use no compression
						// 		m_nFormat = nImageFormat;
						// 		pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
						// 		if (pAPIPixelFormat) {
						// 			gluBuild3DMipmaps(GL_TEXTURE_3D_EXT, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z,
						// 							  nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->GetData());
						// 		}
						// 	}
						// }
					}

					// Calculate the total number of bytes this texture buffer requires
					for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++)
						m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
				} else {
					// Ignore mipmaps?
					if (!bMipmaps)
						m_nNumOfMipmaps = 0; // Jep, we do not want to have any mipmaps for this texture buffer

					// Use given mipmaps
					Vector3i vSize;
					uint32 nLevel = 0;
					for (; nLevel<=m_nNumOfMipmaps; nLevel++) {
						// Get the mipmap image buffer
						const ImageBuffer *pMipmapImageBuffer = pImagePart->GetMipmap(nLevel);
						if (pMipmapImageBuffer) {
							// Get the size of this mipmap level
							vSize = pMipmapImageBuffer->GetSize();

							// Upload the texture buffer
							if (bUsePreCompressedData && pMipmapImageBuffer->HasCompressedData())
								glCompressedTexImage3DARB(GL_TEXTURE_3D_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, pMipmapImageBuffer->GetCompressedDataSize(), pMipmapImageBuffer->GetCompressedData());
							else
								glTexImage3DEXT(GL_TEXTURE_3D_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pMipmapImageBuffer->GetData());

							// If compressed internal format, check whether all went fine
							if (bCompressedFormat) {
								GLint nCompressed;
								glGetTexLevelParameteriv(GL_TEXTURE_3D_EXT, nLevel, GL_TEXTURE_COMPRESSED_ARB, &nCompressed);
								if (!nCompressed) {
									// There was an error, use no compression as fallback
									m_nFormat = nImageFormat;
									pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
									if (pAPIPixelFormat)
										glTexImage3DEXT(GL_TEXTURE_3D_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pMipmapImageBuffer->GetData());
								}
							}

							// Update the total number of bytes this texture buffer requires
							m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
						}
					}

					// We have to define all mipmap levels down to 1x1x1 otherwise the texture buffer is invalid when we try to use any min
					// filter that uses mipmaps. OpenGL "normally" uses white color when invalid/incomplete texture buffer is enabled.
					if (bMipmaps && (vSize.x != 1 || vSize.y != 1 || vSize.z != 1)) {
						// Write a warning into the log
						PL_LOG(Warning, String::Format("Lowest mipmap is %dx%dx%d, but should be 1x1x1! Missing mipmap levels will be white!", vSize.x, vSize.y, vSize.z))

						// If we don't define all mipmap levels down to 1x1x1 'mysterious' graphics bugs may occure were it is not
						// always easy to pinpoint the problem directly to the mipmaps. So, to avoid frustration during bug finding,
						// we just create the missing mipmap levels down to 1x1x1 with a white color - so it's possible to 'see' which texture
						// isn't correct without reading the log message from above. (for some people it appears to be hard to read logs *g*)
						char *pszBuffer = nullptr;
						do {
							// First at all, 'half' the current dimension
							if (vSize.x > 1)
								vSize.x /= 2;
							if (vSize.y > 1)
								vSize.y /= 2;
							if (vSize.z > 1)
								vSize.z /= 2;

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
							glTexImage3DEXT(GL_TEXTURE_3D_EXT, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pszBuffer);

							// Update the mipmap level counter
							nLevel++;
						} while (vSize.x != 1 || vSize.y != 1 || vSize.z != 1);

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


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::TextureBuffer functions    ]
//[-------------------------------------------------------]
bool TextureBuffer3D::Upload(uint32 nMipmap, EPixelFormat nFormat, const void *pData, uint8 nFace)
{
	// Check parameters
	if (nMipmap <= m_nNumOfMipmaps && nFormat != Unknown && pData && !nFace) {
		// Get the OpenGL renderer instance
		const Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

		// Get API pixel format
		const uint32 *pAPIPixelFormat = cRendererOpenGL.GetAPIPixelFormat(m_nFormat);
		if (pAPIPixelFormat) {
			// Get the size of this mipmap level
			const Vector3i vSize = GetSize(nMipmap);

			// Compressed format?
			if (IsCompressedFormat(nFormat)) {
				// Internal format MUST be the same as the given format
				if (m_nFormat != nFormat)
					return false; // Error!

				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_3D, m_nOpenGLTexture);

				// Get the number of bytes
				const uint32 nNumOfBytes = GetNumOfBytes(nMipmap);

				// Upload
				glCompressedTexImage3DARB(GL_TEXTURE_3D, nMipmap, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nNumOfBytes, pData);
			} else {
				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_3D, m_nOpenGLTexture);

				// Upload
				const uint32 nPixelFormat = cRendererOpenGL.GetOpenGLPixelFormat(nFormat);
				const uint32 nDataFormat   = cRendererOpenGL.GetOpenGLDataFormat(nFormat);
				glTexImage3DEXT(GL_TEXTURE_3D, nMipmap, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nPixelFormat, nDataFormat, pData);
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool TextureBuffer3D::Download(uint32 nMipmap, EPixelFormat nFormat, void *pData, uint8 nFace)
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
		glBindTexture(GL_TEXTURE_3D, m_nOpenGLTexture);

		// Download
		glGetCompressedTexImageARB(GL_TEXTURE_3D, nMipmap, pData);
	} else {
		// Bind this texture buffer
		glBindTexture(GL_TEXTURE_3D, m_nOpenGLTexture);

		// Get the OpenGL renderer instance
		const Renderer &cRendererOpenGL = (Renderer&)GetRenderer();

		// Download
		const uint32 nPixelFormat = cRendererOpenGL.GetOpenGLPixelFormat(nFormat);
		const uint32 nDataFormat  = cRendererOpenGL.GetOpenGLDataFormat(nFormat);
		glGetTexImage(GL_TEXTURE_3D, nMipmap, nPixelFormat, nDataFormat, pData);
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::TextureBuffer functions   ]
//[-------------------------------------------------------]
bool TextureBuffer3D::MakeCurrent(uint32 nStage)
{
	// Check if there are renderer information
	if (GetRenderer().GetTextureBuffer(nStage) != this) {
		if (!GetRenderer().SetTextureBuffer(nStage, this))
			return true; // Done
	}

	// Make this texture buffer to the renderers current one
	glEnable(GL_TEXTURE_3D_EXT);
	glBindTexture(GL_TEXTURE_3D_EXT, m_nOpenGLTexture);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void TextureBuffer3D::BackupDeviceData(uint8 **ppBackup)
{
	// Allocate memory
	const uint32 nTotalNumOfBytes = GetTotalNumOfBytes();
	if (nTotalNumOfBytes) {
		*ppBackup = new uint8[nTotalNumOfBytes];
		if (*ppBackup) {
			// Prepare for backup
			glEnable(GL_TEXTURE_3D_EXT);
			glBindTexture(GL_TEXTURE_3D_EXT, m_nOpenGLTexture);

			// Backup
			uint8 *pData = *ppBackup;
			if (IsCompressedFormat()) {
				// Loop through all mipmaps
				for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++) {
					// Get the data from the GPU
					glGetCompressedTexImageARB(GL_TEXTURE_3D, nLevel, pData);

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
					glGetTexImage(GL_TEXTURE_3D, nLevel, nPixelFormat, nDataFormat, pData);

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

void TextureBuffer3D::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup) {
		glGenTextures(1, &m_nOpenGLTexture);
		glBindTexture(GL_TEXTURE_3D_EXT, m_nOpenGLTexture);

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
				// Get the size of this mipmap level
				const Vector3i vSize = GetSize(nLevel);

				// Get the number of bytes
				const uint32 nNumOfBytes = GetNumOfBytes(nLevel);

				// Upload the texture buffer
				if (bCompressedFormat)
					glCompressedTexImage3DARB(GL_TEXTURE_3D, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nNumOfBytes, pData);
				else
					glTexImage3DEXT(GL_TEXTURE_3D, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nPixelFormat, nDataFormat, pData);

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
