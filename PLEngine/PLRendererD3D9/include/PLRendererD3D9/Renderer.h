/*********************************************************\
 *  File: Renderer.h                                     *
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


#ifndef __PLRENDERERD3D9_RENDERER_H__
#define __PLRENDERERD3D9_RENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/Backend/RendererBackend.h>
#include "PLRendererD3D9/PLRendererD3D9.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FontManager;
class FixedFunctions;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Direct3D 9 renderer backend
*/
class Renderer : public PLRenderer::RendererBackend {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SurfaceWindow;
	friend class FixedFunctions;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Renderer, "PLRendererD3D9", PLRenderer::RendererBackend, "Direct3D 9 renderer backend")
		// Constructors
		pl_constructor_5(DefaultConstructor,	pl_enum_type(EMode),	PLGeneral::uint32,	PLGeneral::uint32,	PLGeneral::uint32,	PLGeneral::String,	"Constructor with renderer mode, Z buffer bits, stencil buffer bits, the number of multisample antialiasing samples per pixel and the default shader language as parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nMode
		*    Mode hint the renderer should run in, the renderer is not enforced to use this requested mode
		*  @param[in] nZBufferBits
		*     Z buffer bits (for example 24)
		*  @param[in] nStencilBits
		*    Stencil buffer bits (for example 8)
		*  @param[in] nMultisampleAntialiasingSamples
		*    Multisample antialiasing samples per pixel, <=1 means no antialiasing
		*  @param[in] sDefaultShaderLanguage
		*    The name of the default shader language of the renderer (for example "GLSL" or "Cg"), if the string
		*    is empty, the default is chosen by the renderer implementation, this information is just a hint
		*/
		Renderer(EMode nMode, PLGeneral::uint32 nZBufferBits, PLGeneral::uint32 nStencilBits, PLGeneral::uint32 nMultisampleAntialiasingSamples, PLGeneral::String sDefaultShaderLanguage);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Renderer();

		/**
		*  @brief
		*    Returns the instance of the IDirect3D9 object
		*
		*  @return
		*    Instance of the IDirect3D9 object
		*/
		LPDIRECT3D9 GetInstance() const;

		/**
		*  @brief
		*    Returns the Direct3D 9 renderer device
		*
		*  @return
		*    The Direct3D 9 renderer device
		*/
		LPDIRECT3DDEVICE9 GetDevice() const;

		/**
		*  @brief
		*    Chooses the image source and internal texture buffer formats depending on various input parameters
		*
		*  @param[in]  cImage
		*    Image to use
		*  @param[in]  nInternalFormat
		*    Desired internal texture buffer pixel format, if 'PLRenderer::TextureBuffer::Unknown' use the format of the given image
		*  @param[in]  nFlags
		*    Texture buffer flags (see PLRenderer::TextureBuffer::EFlags)
		*  @param[out] nImageFormat
		*    The chosen image format
		*  @param[out] bUsePreCompressedData
		*    'true' if the pre compressed image data should be used, else 'false'
		*
		*  @return
		*    The chosen internal format
		*/
		PLRenderer::TextureBuffer::EPixelFormat ChooseFormats(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat, PLGeneral::uint32 nFlags,
															  PLRenderer::TextureBuffer::EPixelFormat &nImageFormat, bool &bUsePreCompressedData) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initializes all wrappers
		*/
		void InitWrappers();

		/**
		*  @brief
		*    Setup the renderer capabilities
		*/
		void SetupCapabilities();

		/**
		*  @brief
		*    Enumerates all available display modes
		*
		*  @return
		*    'true' if all went fine and at least one display mode
		*    was found, else 'false'
		*/
		bool QueryDisplayModes();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		LPDIRECT3D9			  m_pD3D;						/**< Instance of the IDirect3D9 object*/
		HWND				  m_hWnd;						/**< Handle to top level window */
		LPDIRECT3DDEVICE9	  m_pDevice;					/**< Rendering device */
		FixedFunctions		 *m_pFixedFunctions;			/**< Fixed functions interface implementation, can be a null pointer */
		FontManager			 *m_pFontManager;				/**< D3D9 renderer font manager, always valid! */
		PLRenderer::Surface	 *m_pFirstSwapChainUserSurface;	/**< The surface window which uses the first swap chain */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Renderer functions         ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetAPI(PLGeneral::uint32 *pnVersion = nullptr) const;
		virtual PLGeneral::String GetVendor() const;
		virtual PLGeneral::String GetDefaultShaderLanguage() const;
		virtual PLRenderer::ShaderLanguage *GetShaderLanguage(const PLGeneral::String &sShaderLanguage = "");
		virtual PLRenderer::FixedFunctions *GetFixedFunctions() const;
		virtual PLRenderer::FontManager &GetFontManager() const;
		virtual void BackupDeviceObjects();
		virtual void RestoreDeviceObjects();
		virtual const PLMath::Vector2 &GetTexelToPixelOffset() const;

		//[-------------------------------------------------------]
		//[ Create surface/resource                               ]
		//[-------------------------------------------------------]
		virtual PLRenderer::SurfaceWindow *CreateSurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, PLGeneral::handle nWindow, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen = false);
		virtual PLRenderer::SurfaceTextureBuffer *CreateSurfaceTextureBuffer2D(const PLMath::Vector2i &vSize, PLRenderer::TextureBuffer::EPixelFormat nFormat, PLGeneral::uint32 nFlags = PLRenderer::SurfaceTextureBuffer::Depth | PLRenderer::SurfaceTextureBuffer::Stencil, PLGeneral::uint8 nMaxColorTargets = 1);
		virtual PLRenderer::SurfaceTextureBuffer *CreateSurfaceTextureBufferRectangle(const PLMath::Vector2i &vSize, PLRenderer::TextureBuffer::EPixelFormat nFormat, PLGeneral::uint32 nFlags = PLRenderer::SurfaceTextureBuffer::Depth | PLRenderer::SurfaceTextureBuffer::Stencil, PLGeneral::uint8 nMaxColorTargets = 1);
		virtual PLRenderer::SurfaceTextureBuffer *CreateSurfaceTextureBufferCube(PLGeneral::uint16 nSize, PLRenderer::TextureBuffer::EPixelFormat nFormat, PLGeneral::uint32 nFlags = PLRenderer::SurfaceTextureBuffer::Depth | PLRenderer::SurfaceTextureBuffer::Stencil);
		virtual PLRenderer::TextureBuffer1D *CreateTextureBuffer1D(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLGeneral::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::TextureBuffer2D *CreateTextureBuffer2D(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLGeneral::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::TextureBuffer *CreateTextureBufferRectangle(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLGeneral::uint32 nFlags = 0);
		virtual PLRenderer::TextureBuffer3D *CreateTextureBuffer3D(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLGeneral::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::TextureBufferCube *CreateTextureBufferCube(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLGeneral::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::IndexBuffer *CreateIndexBuffer();
		virtual PLRenderer::VertexBuffer *CreateVertexBuffer();
		virtual PLRenderer::OcclusionQuery *CreateOcclusionQuery();

		//[-------------------------------------------------------]
		//[ States                                                ]
		//[-------------------------------------------------------]
		virtual bool SetRenderState(PLRenderer::RenderState::Enum nState, PLGeneral::uint32 nValue);
		virtual bool SetSamplerState(PLGeneral::uint32 nStage, PLRenderer::Sampler::Enum nState, PLGeneral::uint32 nValue);

		//[-------------------------------------------------------]
		//[ Misc                                                  ]
		//[-------------------------------------------------------]
		virtual bool BeginScene();
		virtual bool EndScene();
		virtual bool SetViewport(const PLMath::Rectangle *pRectangle = nullptr, float fMinZ = 0.0f, float fMaxZ = 1.0f);
		virtual bool SetScissorRect(const PLMath::Rectangle *pRectangle = nullptr);
		virtual bool GetDepthBounds(float &fZMin, float &fZMax) const;
		virtual bool SetDepthBounds(float fZMin = 0.0f, float fZMax = 1.0f);
		virtual void GetColorMask(bool &bRed, bool &bGreen, bool &bBlue, bool &bAlpha) const;
		virtual bool SetColorMask(bool bRed = true, bool bGreen = true, bool bBlue = true, bool bAlpha = true);
		virtual bool Clear(PLGeneral::uint32 nFlags = PLRenderer::Clear::Color | PLRenderer::Clear::ZBuffer,
						   const PLGraphics::Color4 &cColor = PLGraphics::Color4::Black, float fZ = 1.0f, PLGeneral::uint32 nStencil = 0);

		//[-------------------------------------------------------]
		//[ Get/set current resources                             ]
		//[-------------------------------------------------------]
		virtual bool SetRenderTarget(PLRenderer::Surface *pSurface, PLGeneral::uint8 nFace = 0);
		virtual bool SetColorRenderTarget(PLRenderer::TextureBuffer *pTextureBuffer, PLGeneral::uint8 nColorIndex = 0, PLGeneral::uint8 nFace = 0);
		virtual bool MakeScreenshot(PLGraphics::Image &cImage);
		virtual bool SetTextureBuffer(int nStage = -1, PLRenderer::TextureBuffer *pTextureBuffer = nullptr);
		virtual bool SetIndexBuffer(PLRenderer::IndexBuffer *pIndexBuffer = nullptr);

		//[-------------------------------------------------------]
		//[ Draw                                                  ]
		//[-------------------------------------------------------]
		virtual bool DrawPrimitives(PLRenderer::Primitive::Enum nType, PLGeneral::uint32 nStartIndex, PLGeneral::uint32 nNumVertices);
		virtual bool DrawIndexedPrimitives(PLRenderer::Primitive::Enum nType, PLGeneral::uint32 nMinIndex, PLGeneral::uint32 nMaxIndex, PLGeneral::uint32 nStartIndex, PLGeneral::uint32 nNumVertices);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_RENDERER_H__
