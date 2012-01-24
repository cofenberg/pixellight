/*********************************************************\
 *  File: TextureBuffer3D.cpp                            *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLRendererOpenGLES2/Renderer.h"
#include "PLRendererOpenGLES2/Extensions.h"
#include "PLRendererOpenGLES2/TextureBuffer3D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
TextureBuffer3D::~TextureBuffer3D()
{
	if (m_nOpenGLESTexture)
		glDeleteTextures(1, &m_nOpenGLESTexture);

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nTextureBuffersNum--;
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nTextureBuffersMem -= GetTotalNumOfBytes();
}

/**
*  @brief
*    Returns the OpenGL ES resource ID of the texture buffer
*/
uint32 TextureBuffer3D::GetOpenGLESTexture() const
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
TextureBuffer3D::TextureBuffer3D(PLRenderer::Renderer &cRenderer, Image &cImage, EPixelFormat nInternalFormat, uint32 nFlags) :
	PLRenderer::TextureBuffer3D(cRenderer, nFlags),
	m_nOpenGLESTexture(0)
{
	// Get the OpenGL ES renderer instance
	Renderer &cRendererOpenGLES = static_cast<Renderer&>(cRenderer);

	// Update renderer statistics
	cRendererOpenGLES.GetWritableStatistics().nTextureBuffersNum++;

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
			const uint32 *pAPIPixelFormat = cRendererOpenGLES.GetAPIPixelFormat(m_nFormat);
			if (pAPIPixelFormat) {
				// Get uncompressed image format information
				EPixelFormat nImageFormatUncompressed     = GetFormatFromImage(cImage, true);
				uint32		 nAPIImageFormatUncompressed  = cRendererOpenGLES.GetOpenGLESPixelFormat(nImageFormatUncompressed);
				uint32		 nImageDataFormatUncompressed = cRendererOpenGLES.GetOpenGLESDataFormat(nImageFormatUncompressed);

				// Set the size
				m_vSize = pImageBuffer->GetSize();

				// Create OpenGL ES texture buffer
				glGenTextures(1, &m_nOpenGLESTexture);
				glBindTexture(GL_TEXTURE_3D_OES, m_nOpenGLESTexture);

				// Upload the texture buffer
				m_nNumOfMipmaps = pImagePart->GetNumOfMipmaps() - 1;
				const bool bMipmaps = nFlags & Mipmaps;
				if (!m_nNumOfMipmaps && bMipmaps) {
					// Upload the texture buffer
					if (bUsePreCompressedData)
						glCompressedTexImage3DOES(GL_TEXTURE_3D_OES, 0, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z, 0, pImageBuffer->GetCompressedDataSize(), pImageBuffer->GetCompressedData());
					else 
						glTexImage3DOES(GL_TEXTURE_3D_OES, 0, *pAPIPixelFormat, m_vSize.x, m_vSize.y, m_vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pImageBuffer->HasAnyData() ? pImageBuffer->GetData() : nullptr);

					// If compressed internal format, we would check whether all went fine - but OpenGL ES 2.0 provides no functionality for this :/

					// Let OpenGL ES create the mipmap chain for us
					// -> Lookout! "OpenGL ES Common Profile Specification Version 2.0.25 (Full Specification) (November 2, 2010)" ->
					//    "3.7.11 Mipmap Generation" states:
					//    "If either the width or height of the level zero array are not a power or two, the error INVALID_OPERATION is generated."
					// -> On "LG P990 Optimus Speed" (Tegra 2, Android 2.3.4) there was no crash
					// -> "Asus Eee Pad Transformer" (Tegra 2, Android 3.2.1) crashed instead of returning an error
					// -> So we really have to check for this situation
					if (IsPowerOfTwo()) {
						// Let OpenGL ES create the mipmap chain for us
						glGenerateMipmap(GL_TEXTURE_3D_OES);

						// Calculate the number of mipmaps
						m_nNumOfMipmaps = static_cast<uint32>(Math::Log2(static_cast<float>(Math::Max(Math::Max(m_vSize.x, m_vSize.y), m_vSize.z))));

						// Update the total number of bytes this texture buffer requires
						for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++)
							m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
					} else {
						// Sorry, no automatic mipmap generation possible
						m_nNumOfMipmaps = 0;
						m_nTotalNumOfBytes += GetNumOfBytes();
					}
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
								glCompressedTexImage3DOES(GL_TEXTURE_3D_OES, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, pMipmapImageBuffer->GetCompressedDataSize(), pMipmapImageBuffer->GetCompressedData());
							else
								glTexImage3DOES(GL_TEXTURE_3D_OES, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pMipmapImageBuffer->HasAnyData() ? pMipmapImageBuffer->GetData() : nullptr);

							// If compressed internal format, we would check whether all went fine - but OpenGL ES 2.0 provides no functionality for this :/

							// Update the total number of bytes this texture buffer requires
							m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
						}
					}

					// We have to define all mipmap levels down to 1x1x1 otherwise the texture buffer is invalid when we try to use any min
					// filter that uses mipmaps. OpenGL ES "normally" uses white color when invalid/incomplete texture buffer is enabled.
					if (bMipmaps && (vSize.x != 1 || vSize.y != 1 || vSize.z != 1)) {
						// Write a warning into the log
						PL_LOG(Warning, String::Format("Lowest mipmap is %dx%dx%d, but should be 1x1x1! Missing mipmap levels will be white!", vSize.x, vSize.y, vSize.z))

						// If we don't define all mipmap levels down to 1x1x1 'mysterious' graphics bugs may occur were it is not
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
							glTexImage3DOES(GL_TEXTURE_3D_OES, nLevel, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nAPIImageFormatUncompressed, nImageDataFormatUncompressed, pszBuffer);

							// Update the mipmap level counter
							nLevel++;
						} while (vSize.x != 1 || vSize.y != 1 || vSize.z != 1);

						// Cleanup your white buffer
						if (pszBuffer)
							delete [] pszBuffer;
					}
				}

				// Update renderer statistics
				cRendererOpenGLES.GetWritableStatistics().nTextureBuffersMem += GetTotalNumOfBytes();
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
		// Get the OpenGL ES renderer instance
		const Renderer &cRendererOpenGLES = static_cast<Renderer&>(GetRenderer());

		// Get API pixel format
		const uint32 *pAPIPixelFormat = cRendererOpenGLES.GetAPIPixelFormat(m_nFormat);
		if (pAPIPixelFormat) {
			// Get the size of this mipmap level
			const Vector3i vSize = GetSize(nMipmap);

			// Compressed format?
			if (IsCompressedFormat(nFormat)) {
				// Internal format MUST be the same as the given format
				if (m_nFormat != nFormat)
					return false; // Error!

				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_3D_OES, m_nOpenGLESTexture);

				// Get the number of bytes
				const uint32 nNumOfBytes = GetNumOfBytes(nMipmap);

				// Upload
				glCompressedTexImage3DOES(GL_TEXTURE_3D_OES, nMipmap, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nNumOfBytes, pData);
			} else {
				// Bind this texture buffer
				glBindTexture(GL_TEXTURE_3D_OES, m_nOpenGLESTexture);

				// Upload
				const uint32 nPixelFormat = cRendererOpenGLES.GetOpenGLESPixelFormat(nFormat);
				const uint32 nDataFormat  = cRendererOpenGLES.GetOpenGLESDataFormat(nFormat);
				glTexImage3DOES(GL_TEXTURE_3D_OES, nMipmap, *pAPIPixelFormat, vSize.x, vSize.y, vSize.z, 0, nPixelFormat, nDataFormat, pData);
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool TextureBuffer3D::Download(uint32 nMipmap, EPixelFormat nFormat, void *pData, uint8 nFace) const
{
	// "GL_NV_get_tex_image"-extension available?
	if (static_cast<Renderer&>(GetRenderer()).GetContext().GetExtensions().IsGL_NV_get_tex_image()) {
		// Check parameters
		if (nMipmap > m_nNumOfMipmaps || nFormat == Unknown || !pData || nFace)
			return false; // Error!

		// Compressed format?
		if (IsCompressedFormat(nFormat)) {
			// Internal format MUST be the same as the given format
			if (m_nFormat != nFormat)
				return false; // Error!

			// Bind this texture buffer
			glBindTexture(GL_TEXTURE_3D_OES, m_nOpenGLESTexture);

			// Download
			glGetCompressedTexImageNV(GL_TEXTURE_3D_OES, nMipmap, pData);
		} else {
			// Bind this texture buffer
			glBindTexture(GL_TEXTURE_3D_OES, m_nOpenGLESTexture);

			// Get the OpenGL ES renderer instance
			const Renderer &cRendererOpenGLES = static_cast<Renderer&>(GetRenderer());

			// Download
			const uint32 nPixelFormat = cRendererOpenGLES.GetOpenGLESPixelFormat(nFormat);
			const uint32 nDataFormat  = cRendererOpenGLES.GetOpenGLESDataFormat(nFormat);
			glGetTexImageNV(GL_TEXTURE_3D_OES, nMipmap, nPixelFormat, nDataFormat, pData);
		}

		// Done
		return true;
	} else {
		// Error, texture read back is not supported by OpenGL ES 2.0
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::TextureBuffer functions   ]
//[-------------------------------------------------------]
bool TextureBuffer3D::MakeCurrent(uint32 nStage)
{
	// [TODO] Remove this method if possible
	/*
	// Check if there are renderer information
	if (GetRenderer().GetTextureBuffer(nStage) != this) {
		if (!GetRenderer().SetTextureBuffer(nStage, this))
			return true; // Done
	}

	// Make this texture buffer to the renderers current one
	glEnable(GL_TEXTURE_3D_OES);
	glBindTexture(GL_TEXTURE_3D_OES, m_nOpenGLESTexture);
*/
	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
