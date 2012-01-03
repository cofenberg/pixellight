/*********************************************************\
 *  File: TextureBufferRectangle.cpp                     *
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
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/TextureBufferRectangle.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
TextureBufferRectangle::~TextureBufferRectangle()
{
	// Release the Direct3D 9 texture
	if (m_pD3D9Texture)
		m_pD3D9Texture->Release();

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nTextureBuffersNum--;
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nTextureBuffersMem -= GetTotalNumOfBytes();
}

/**
*  @brief
*    Returns the Direct3D 9 texture
*/
LPDIRECT3DTEXTURE9 TextureBufferRectangle::GetD3D9Texture() const
{
	return m_pD3D9Texture;
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
	m_pD3D9Texture(nullptr)
{
	// Get the concrete renderer implementation
	Renderer &cRendererD3D9 = static_cast<Renderer&>(cRenderer);

	// Update renderer statistics
	cRendererD3D9.GetWritableStatistics().nTextureBuffersNum++;

	// Choose the texture buffer pixel formats which should be used
	EPixelFormat nImageFormat;
	bool bUsePreCompressedData;
	m_nFormat = cRendererD3D9.ChooseFormats(cImage, nInternalFormat, nFlags, nImageFormat, bUsePreCompressedData);

	// Get the first image part
	const ImagePart *pImagePart = cImage.GetPart(0);
	if (pImagePart) {
		// Get the first image buffer
		const ImageBuffer *pImageBuffer = pImagePart->GetMipmap(0);
		if (pImageBuffer) {
			// Get API pixel format
			uint32 *pAPIPixelFormat = cRendererD3D9.GetAPIPixelFormat(m_nFormat);
			if (pAPIPixelFormat) {
				// Get Direct3D 9 device
				LPDIRECT3DDEVICE9 pDevice = static_cast<Renderer&>(cRenderer).GetDevice();
				if (pDevice) {
					D3DFORMAT nAPIFormat = static_cast<D3DFORMAT>(*pAPIPixelFormat);

					// Get the size
					m_vSize.x = pImageBuffer->GetSize().x;
					m_vSize.y = pImageBuffer->GetSize().y;

					// Is this texture buffer a render target?
					if (nFlags & RenderTarget) {
						// Create Direct3D 9 texture
						m_nNumOfMipmaps = 0;
						if (D3DXCreateTexture(pDevice, m_vSize.x, m_vSize.y, 1, D3DUSAGE_RENDERTARGET, nAPIFormat,
											  D3DPOOL_DEFAULT, &m_pD3D9Texture) != D3D_OK) {
							// Error!
							m_nFormat = Unknown;
							m_vSize   = Vector2i::Zero;
						}
					} else {
						// Use given mipmaps if there are any?
						bool   bMipmaps           = nFlags & Mipmaps;
						uint32 nNumOfImageMipmaps = pImagePart->GetNumOfMipmaps() - 1;
						if (bMipmaps && !nNumOfImageMipmaps) {
							// Calculate the number of mipmaps
							m_nNumOfMipmaps = static_cast<uint32>(Math::Log2(static_cast<float>(Math::Max(m_vSize.x, m_vSize.y))));
						} else {
							m_nNumOfMipmaps = nNumOfImageMipmaps;
						}

						// Create Direct3D 9 texture
						if (pDevice->CreateTexture(m_vSize.x, m_vSize.y, m_nNumOfMipmaps, 0, nAPIFormat, D3DPOOL_DEFAULT, &m_pD3D9Texture, nullptr) != D3D_OK) {
							// There was an error and compression was used, use no compression and try again
							bUsePreCompressedData = false;
							m_nFormat			  = nImageFormat;
							pAPIPixelFormat		  = cRendererD3D9.GetAPIPixelFormat(m_nFormat);
							if (pAPIPixelFormat) {
								nAPIFormat = static_cast<D3DFORMAT>(*pAPIPixelFormat);
								if (pDevice->CreateTexture(m_vSize.x, m_vSize.y, m_nNumOfMipmaps, 0, nAPIFormat, D3DPOOL_DEFAULT, &m_pD3D9Texture, nullptr) != D3D_OK) {
									// Error!
									m_nFormat		= Unknown;
									m_nNumOfMipmaps	= 0;
									m_vSize			= Vector2i::Zero;
								}
							} else {
								// Error!
								m_nFormat		= Unknown;
								m_nNumOfMipmaps	= 0;
								m_vSize			= Vector2i::Zero;
							}
						}

						// Upload the texture buffer
						Vector2i vSize;
						for (uint32 nLevel=0; nLevel<=nNumOfImageMipmaps; nLevel++) {
							// Get the mipmap image buffer
							const ImageBuffer *pMipmapImageBuffer = pImagePart->GetMipmap(nLevel);
							if (pMipmapImageBuffer) {
								// Get the size of this mipmap level
								vSize.x = pMipmapImageBuffer->GetSize().x;
								vSize.y = pMipmapImageBuffer->GetSize().y;

								// Get the surface
								LPDIRECT3DSURFACE9 pDestSurface = nullptr;
								m_pD3D9Texture->GetSurfaceLevel(nLevel, &pDestSurface);
								if (pDestSurface) {
									// Is the source data compressed?
									if (bUsePreCompressedData && pMipmapImageBuffer->HasCompressedData()) {
										// Compressed source data
										D3DFORMAT nSourceFormat;
										switch (pMipmapImageBuffer->GetCompression()) {
											case CompressionDXT1:
												nSourceFormat = D3DFMT_DXT1;
												break;

											// [TODO] Unsupported
											// case Image::DXTC_DXT2:
											//	nSourceFormat = D3DFMT_DXT2;
											//	break;

											case CompressionDXT3:
												nSourceFormat = D3DFMT_DXT3;
												break;

											// [TODO] Unsupported
											// case Image::DXTC_DXT4:
											//	nSourceFormat = D3DFMT_DXT4;
											//	break;

											case CompressionDXT5:
												nSourceFormat = D3DFMT_DXT5;
												break;

											case CompressionLATC1:
												nSourceFormat = static_cast<D3DFORMAT>('1ITA');
												break;

											case CompressionLATC2:
												nSourceFormat = static_cast<D3DFORMAT>('2ITA');
												break;

											// [TODO] Check Image::DXTC_RXGB
											default:
												nSourceFormat = D3DFMT_UNKNOWN;
												break;
										}
										if (nSourceFormat != D3DFMT_UNKNOWN) {
											RECT sSourceRect[] = { 0, 0, vSize.x, vSize.y };
											D3DXLoadSurfaceFromMemory(pDestSurface, nullptr, nullptr, static_cast<const uint8*>(pMipmapImageBuffer->GetCompressedData()), nSourceFormat,
																	  pMipmapImageBuffer->GetCompressedDataSize()/((vSize.y+3)/4), nullptr,
																	  sSourceRect, D3DX_FILTER_NONE, 0);
										}
									} else {
										// Uncompressed source data
										D3DFORMAT  nSourceFormat;
										uint8      nNumOfComponents = static_cast<uint8>(pMipmapImageBuffer->GetComponentsPerPixel());
										uint8     *pTempData        = const_cast<uint8*>(static_cast<const uint8*>(pMipmapImageBuffer->GetData()));
										switch (nNumOfComponents) {
											case 1:
												nSourceFormat = D3DFMT_L8;
												break;

											case 2:
												nSourceFormat = D3DFMT_A8L8;
												break;

											case 3:
											{
												// Quite stupid, but we really have to invert the color order...
												uint32 nSize = pMipmapImageBuffer->GetDataSize();
												nSourceFormat = D3DFMT_R8G8B8;
												pTempData = new uint8[nSize];
													  uint8 *pTempImageData = pTempData;
												const uint8 *pImageData     = static_cast<const uint8*>(pMipmapImageBuffer->GetData());
												const uint8 *pImageDataEnd  = static_cast<const uint8*>(pMipmapImageBuffer->GetData()) + nSize;
												while (pImageData<pImageDataEnd) {
													// Copy data and swap r/b
													pTempImageData[0] = pImageData[2];
													pTempImageData[1] = pImageData[1];
													pTempImageData[2] = pImageData[0];

													// Next pixel, please
													pTempImageData += 3;
													pImageData     += 3;
												}
												break;
											}

											case 4:
												nSourceFormat = D3DFMT_A8B8G8R8;
												break;

											default:
												nSourceFormat = D3DFMT_UNKNOWN;
												break;
										}
										if (nSourceFormat != D3DFMT_UNKNOWN) {
											RECT sSourceRect[] = { 0, 0, vSize.x, vSize.y };
											D3DXLoadSurfaceFromMemory(pDestSurface, nullptr, nullptr, pTempData, nSourceFormat,
																	  vSize.x*nNumOfComponents, nullptr, sSourceRect, D3DX_FILTER_NONE, 0);
										}
										if (pTempData != static_cast<const uint8*>(pMipmapImageBuffer->GetData()))
											delete [] pTempData;
									}

									// Release the surface
									pDestSurface->Release();
								}

								// Update the total number of bytes this texture buffer requires
								m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
							}
						}

						// Do we need to create mipmaps by hand?
						if (bMipmaps && !nNumOfImageMipmaps) {
							// Let the API create the mipmaps for us
							if (D3DXFilterTexture(m_pD3D9Texture, nullptr, D3DX_DEFAULT, D3DX_FILTER_LINEAR) != D3D_OK)
								PL_LOG(Error, "Failed to create rectangle texture buffer mipmap data")

							// Calculate the total number of bytes this texture buffer requires (note that we already have the base level!)
							for (uint32 nLevel=1; nLevel<=m_nNumOfMipmaps; nLevel++)
								m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
						} else {
							// We have to define all mipmap levels down to 1x1 otherwise the texture buffer is invalid when we try to use any min
							// filter that uses mipmaps. Direct3D 9 normally uses white color when invalid/incomplete texture buffer is enabled.
							if (bMipmaps && (vSize.x != 1 || vSize.y != 1))
								PL_LOG(Warning, String::Format("Lowest mipmap is %dx%d, but should be 1x1! As result, the texture buffer is probably NOT rendered correctly!", vSize.x, vSize.y))
						}
					}

					// Update renderer statistics
					cRendererD3D9.GetWritableStatistics().nTextureBuffersMem += GetTotalNumOfBytes();
				}
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
	m_pD3D9Texture(nullptr)
{
	// Get the concrete renderer implementation
	Renderer &cRendererD3D9 = static_cast<Renderer&>(cRenderer);

	// Update renderer statistics
	cRendererD3D9.GetWritableStatistics().nTextureBuffersNum++;

	// Check if there are renderer information
	LPDIRECT3DDEVICE9 pDevice = static_cast<Renderer&>(cRenderer).GetDevice();
	if (pDevice) {
		// Set data
		m_nFormat = nInternalFormat;
		m_vSize   = vSize;

		// Get API pixel format
		uint32 *pAPIPixelFormat = cRendererD3D9.GetAPIPixelFormat(m_nFormat);
		if (pAPIPixelFormat) {
			D3DFORMAT nAPIFormat = static_cast<D3DFORMAT>(*pAPIPixelFormat);

			// Create Direct3D 9 texture
			if (nFlags & RenderTarget) {
				m_nNumOfMipmaps = 0;
				if (D3DXCreateTexture(pDevice, m_vSize.x, m_vSize.y, 1, D3DUSAGE_RENDERTARGET, nAPIFormat,
									  D3DPOOL_DEFAULT, &m_pD3D9Texture) != D3D_OK) {
					// Error!
					m_nFormat = Unknown;
					m_vSize   = Vector2i::Zero;
				}
			} else {
				bool bMipmaps = m_nFlags & Mipmaps;
				if (D3DXCreateTexture(pDevice, m_vSize.x, m_vSize.y, bMipmaps ? D3DX_DEFAULT : 1, 0, nAPIFormat,
									  D3DPOOL_DEFAULT, &m_pD3D9Texture) == D3D_OK) {
					// Calculate the number of mipmaps
					m_nNumOfMipmaps = bMipmaps ? static_cast<uint32>(Math::Log2(static_cast<float>(Math::Max(m_vSize.x, m_vSize.y)))) : 0;
				} else {
					// Error!
					m_nFormat = Unknown;
					m_vSize   = Vector2i::Zero;
				}
			}

			// Calculate the total number of bytes this texture buffer requires
			for (uint32 nLevel=0; nLevel<=m_nNumOfMipmaps; nLevel++)
				m_nTotalNumOfBytes += GetNumOfBytes(nLevel);

			// Update renderer statistics
			cRendererD3D9.GetWritableStatistics().nTextureBuffersMem += GetTotalNumOfBytes();
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::TextureBuffer functions    ]
//[-------------------------------------------------------]
bool TextureBufferRectangle::Upload(uint32 nMipmap, EPixelFormat nFormat, const void *pData, uint8 nFace)
{
	// [TODO] At the moment, rectangle texture buffers don't support mipmaps, so nMipmap is always 0
	// Check parameters and Direct3D 9 texture
	if (nMipmap == 0 && nFormat != Unknown && pData && !nFace && m_pD3D9Texture) {
//	if (nMipmap <= m_nNumOfMipmaps && nFormat != Unknown && pData && !nFace && m_pD3D9Texture) {
		// Get API pixel format
		uint32 *pAPIPixelFormat = static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetAPIPixelFormat(nFormat);
		if (pAPIPixelFormat) {
			// Get the size of this mipmap level
			Vector2i vSize = GetSize();
//			Vector2i vSize = GetSize(nMipmap);

			// Get the surface
			LPDIRECT3DSURFACE9 pDestSurface = nullptr;
			if (m_pD3D9Texture->GetSurfaceLevel(nMipmap, &pDestSurface) == D3D_OK) {
				// Upload
				RECT sSourceRect[]  = { 0, 0, vSize.x, vSize.y };
				D3DXLoadSurfaceFromMemory(pDestSurface, nullptr, nullptr, pData, static_cast<D3DFORMAT>(*pAPIPixelFormat),
										  IsCompressedFormat() ? GetNumOfBytes(nMipmap)/((vSize.y+3)/4) : vSize.x*GetComponentsPerPixel(),
										  nullptr, sSourceRect, D3DX_FILTER_NONE, 0);

				// Release the surface
				pDestSurface->Release();

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

bool TextureBufferRectangle::Download(uint32 nMipmap, EPixelFormat nFormat, void *pData, uint8 nFace) const
{
	// Check parameters and Direct3D 9 texture
	if (nMipmap <= m_nNumOfMipmaps && nFormat != Unknown && pData && !nFace && m_pD3D9Texture) {
		// [TODO] Implement me
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::TextureBuffer functions   ]
//[-------------------------------------------------------]
bool TextureBufferRectangle::MakeCurrent(uint32 nStage)
{
	// Check if there are renderer information
	LPDIRECT3DDEVICE9 pDevice = static_cast<Renderer&>(GetRenderer()).GetDevice();
	if (pDevice) {
		if (GetRenderer().GetTextureBuffer(nStage) != this) {
			if (!GetRenderer().SetTextureBuffer(nStage, this))
				return true; // Done
		}

		// Set Direct3D 9 texture
		return (pDevice->SetTexture(nStage, m_pD3D9Texture) == D3D_OK);
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void TextureBufferRectangle::BackupDeviceData(uint8 **ppBackup)
{
/*	// [TODO] Backup data
	D3DLOCKED_BOX box;
	pDataTT = pDataT;
	uint64 nSizeT = vSize.x*vSize.y*GetComponentsPerPixel();
	if (m_pD3D9Texture->LockBox(i, &box, nullptr, 0) == D3D_OK) {
		MemoryManager::Copy(box.pBits, pDataTT, nSizeT);
		pDataTT += nSizeT;
		m_pD3D9Texture->UnlockBox(nDepth);
	}
*/
}

void TextureBufferRectangle::RestoreDeviceData(uint8 **ppBackup)
{
	// [TODO] Restore data
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9
