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
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLGraphics/Image/Image.h>
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/TextureBuffer3D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
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
TextureBuffer3D::~TextureBuffer3D()
{
	// Release the Direct3D 9 texture
	if (m_pD3D9Texture)
		m_pD3D9Texture->Release();

	// Update renderer statistics
	((PLRenderer::RendererBackend&)GetRenderer()).GetStatisticsT().nTextureBuffersNum--;
	((PLRenderer::RendererBackend&)GetRenderer()).GetStatisticsT().nTextureBuffersMem -= GetTotalNumOfBytes();
}

/**
*  @brief
*    Returns the Direct3D 9 texture
*/
LPDIRECT3DVOLUMETEXTURE9 TextureBuffer3D::GetD3D9Texture() const
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
TextureBuffer3D::TextureBuffer3D(PLRenderer::Renderer &cRenderer, Image &cImage, EPixelFormat nInternalFormat, uint32 nFlags) :
	PLRenderer::TextureBuffer3D(cRenderer, nFlags),
	m_pD3D9Texture(nullptr)
{
	// Get the concrete renderer implementation
	Renderer &cRendererD3D9 = (Renderer&)cRenderer;

	// Update renderer statistics
	cRendererD3D9.GetStatisticsT().nTextureBuffersNum++;

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
				LPDIRECT3DDEVICE9 pDevice = ((Renderer&)cRenderer).GetDevice();
				if (pDevice) {
					D3DFORMAT nAPIFormat = (D3DFORMAT)*pAPIPixelFormat;

					// Get the size
					m_vSize = pImageBuffer->GetSize();

					// Is this texture buffer a render target?
					if (nFlags & RenderTarget) {
						// Create Direct3D 9 texture
						m_nNumOfMipmaps = 0;
						if (D3DXCreateVolumeTexture(pDevice, m_vSize.x, m_vSize.y, m_vSize.z, 1, D3DUSAGE_RENDERTARGET, nAPIFormat,
													D3DPOOL_DEFAULT, &m_pD3D9Texture) != D3D_OK) {
							// Error!
							m_nFormat = Unknown;
							m_vSize   = Vector3i::Zero;
						}
					} else {
						// Use given mipmaps if there are any?
						bool   bMipmaps           = nFlags & Mipmaps;
						uint32 nNumOfImageMipmaps = pImagePart->GetNumOfMipmaps() - 1;
						if (bMipmaps && !nNumOfImageMipmaps) {
							// Calculate the number of mipmaps
							m_nNumOfMipmaps = (uint32)Math::Log2(float(Math::Max(m_vSize.x, m_vSize.y)));
						} else {
							m_nNumOfMipmaps = nNumOfImageMipmaps;
						}

						// Create Direct3D 9 texture - we have to use 'D3DPOOL_MANAGED' if we want to use 'D3DXFilterVolumeTexture()' later
						if (pDevice->CreateVolumeTexture(m_vSize.x, m_vSize.y, m_vSize.z, m_nNumOfMipmaps, 0, nAPIFormat,
														(bMipmaps && !nNumOfImageMipmaps) ? D3DPOOL_MANAGED : D3DPOOL_DEFAULT, &m_pD3D9Texture, nullptr) != D3D_OK) {
							// There was an error and compression was used, use no compression and try again
							bUsePreCompressedData = false;
							m_nFormat			  = nImageFormat;
							pAPIPixelFormat		  = cRendererD3D9.GetAPIPixelFormat(m_nFormat);
							if (pAPIPixelFormat) {
								nAPIFormat = (D3DFORMAT)*pAPIPixelFormat;
								if (pDevice->CreateVolumeTexture(m_vSize.x, m_vSize.y, m_vSize.z, m_nNumOfMipmaps, 0, nAPIFormat, D3DPOOL_DEFAULT, &m_pD3D9Texture, nullptr) != D3D_OK) {
									// Error!
									m_nFormat		= Unknown;
									m_nNumOfMipmaps	= 0;
									m_vSize			= Vector3i::Zero;
								}
							} else {
								// Error!
								m_nFormat		= Unknown;
								m_nNumOfMipmaps	= 0;
								m_vSize			= Vector3i::Zero;
							}
						}

						// Upload the texture buffer
						Vector3i vSize;
						for (uint32 nLevel=0; nLevel<=nNumOfImageMipmaps; nLevel++) {
							// Get the mipmap image buffer
							const ImageBuffer *pMipmapImageBuffer = pImagePart->GetMipmap(nLevel);
							if (pMipmapImageBuffer) {
								// Get the size of this mipmap level
								vSize = pMipmapImageBuffer->GetSize();

								// Get the volume
								LPDIRECT3DVOLUME9 pDestVolume = nullptr;
								m_pD3D9Texture->GetVolumeLevel(nLevel, &pDestVolume);
								if (pDestVolume) {
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
												nSourceFormat = (D3DFORMAT)'1ITA';
												break;

											case CompressionLATC2:
												nSourceFormat = (D3DFORMAT)'2ITA';
												break;

											// [TODO] Check Image::DXTC_RXGB
											default:
												nSourceFormat = D3DFMT_UNKNOWN;
												break;
										}
										if (nSourceFormat != D3DFMT_UNKNOWN) {
											D3DBOX sSourceBox[] = { 0, 0, vSize.x, vSize.y, 0, vSize.z };
											D3DXLoadVolumeFromMemory(pDestVolume, nullptr, nullptr, (uint8*)pMipmapImageBuffer->GetCompressedData(), nSourceFormat,
																	 pMipmapImageBuffer->GetCompressedDataSize()/((vSize.y+3)/4/vSize.z), pMipmapImageBuffer->GetCompressedDataSize()/vSize.z,
																	 nullptr, sSourceBox, D3DX_FILTER_NONE, 0);
										}
									} else {
										// Uncompressed source data
										D3DFORMAT  nSourceFormat;
										uint8      nNumOfComponents = (uint8)pMipmapImageBuffer->GetComponentsPerPixel();
										uint8     *pTempData        = (uint8*)pMipmapImageBuffer->GetData();
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
												const uint8 *pImageData     = (const uint8*)pMipmapImageBuffer->GetData();
												const uint8 *pImageDataEnd  = (const uint8*)pMipmapImageBuffer->GetData() + nSize;
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
											D3DBOX sSourceBox[] = { 0, 0, vSize.x, vSize.y, 0, vSize.z };
											uint32 nRowPitch = vSize.x*nNumOfComponents;
											D3DXLoadVolumeFromMemory(pDestVolume, nullptr, nullptr, pTempData, nSourceFormat,
																	 nRowPitch, nRowPitch*vSize.y, nullptr,
																	 sSourceBox, D3DX_FILTER_NONE, 0);
										}
										if (pTempData != (uint8*)pMipmapImageBuffer->GetData())
											delete [] pTempData;
									}

									// Release the volume
									pDestVolume->Release();
								}

								// Update the total number of bytes this texture buffer requires
								m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
							}
						}

						// Do we need to create mipmaps by hand?
						if (bMipmaps && !nNumOfImageMipmaps) {
							// Let the API create the mipmaps for us
							if (D3DXFilterVolumeTexture(m_pD3D9Texture, nullptr, D3DX_DEFAULT, D3DX_FILTER_LINEAR) != D3D_OK)
								PL_LOG(Error, "Failed to create 3D texture buffer mipmap data")

							// Calculate the total number of bytes this texture buffer requires (note that we already have the base level!)
							for (uint32 nLevel=1; nLevel<=m_nNumOfMipmaps; nLevel++)
								m_nTotalNumOfBytes += GetNumOfBytes(nLevel);
						} else {
							// We have to define all mipmap levels down to 1x1x1 otherwise the texture buffer is invalid when we try to use any min
							// filter that uses mipmaps. Direct3D 9 normally uses white color when invalid/incomplete texture buffer is enabled.
							if (bMipmaps && (vSize.x != 1 || vSize.y != 1 || vSize.z != 1))
								PL_LOG(Warning, String::Format("Lowest mipmap is %dx%dx%d, but should be 1x1! As result, the texture buffer is propably NOT rendered correctly!", vSize.x, vSize.y, vSize.z))
						}
					}

					// Update renderer statistics
					cRendererD3D9.GetStatisticsT().nTextureBuffersMem += GetTotalNumOfBytes();
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::TextureBuffer functions    ]
//[-------------------------------------------------------]
bool TextureBuffer3D::Upload(uint32 nMipmap, EPixelFormat nFormat, const void *pData, uint8 nFace)
{
	// Check parameters and Direct3D 9 texture
	if (nMipmap <= m_nNumOfMipmaps && nFormat != Unknown && pData && !nFace && m_pD3D9Texture) {
		// Get API pixel format
		uint32 *pAPIPixelFormat = ((PLRenderer::RendererBackend&)GetRenderer()).GetAPIPixelFormat(nFormat);
		if (pAPIPixelFormat) {
			// Get the size of this mipmap level
			Vector3i vSize = GetSize(nMipmap);

			// Get the volume
			LPDIRECT3DVOLUME9 pDestVolume = nullptr;
			m_pD3D9Texture->GetVolumeLevel(nMipmap, &pDestVolume);
			if (pDestVolume) {
				// Upload
				D3DBOX sSourceBox[] = { 0, 0, vSize.x, vSize.y, 0, vSize.z };
				D3DXLoadVolumeFromMemory(pDestVolume, nullptr, nullptr, pData, (D3DFORMAT)*pAPIPixelFormat,
										 IsCompressedFormat() ? GetNumOfBytes(nMipmap)/((vSize.y+3)/4)/vSize.z : vSize.x*GetComponentsPerPixel(),
										 IsCompressedFormat() ? GetNumOfBytes(nMipmap)/vSize.z				   : vSize.x*vSize.y*GetComponentsPerPixel(),
										 nullptr, sSourceBox, D3DX_FILTER_NONE, 0);

				// Release the volume
				pDestVolume->Release();

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

bool TextureBuffer3D::Download(uint32 nMipmap, EPixelFormat nFormat, void *pData, uint8 nFace)
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
bool TextureBuffer3D::MakeCurrent(uint32 nStage)
{
	// Check if there are renderer information
	LPDIRECT3DDEVICE9 pDevice = ((Renderer&)GetRenderer()).GetDevice();
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
void TextureBuffer3D::BackupDeviceData(uint8 **ppBackup)
{
	// [TODO] Backup data
}

void TextureBuffer3D::RestoreDeviceData(uint8 **ppBackup)
{
	// [TODO] Restore data
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9
