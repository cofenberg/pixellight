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


#ifndef __PLRENDERERNULL_RENDERER_H__
#define __PLRENDERERNULL_RENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/Backend/RendererBackend.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererNull {


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
*    Null renderer backend
*/
class Renderer : public PLRenderer::RendererBackend {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SurfaceWindow;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Renderer, "PLRendererNull", PLRenderer::RendererBackend, "Null renderer backend")
		// Constructors
		pl_constructor_5(DefaultConstructor,	pl_enum_type(EMode),	PLCore::uint32,	PLCore::uint32,	PLCore::uint32,	PLCore::String,	"Constructor with renderer mode, Z buffer bits, stencil buffer bits, the number of multisample antialiasing samples per pixel and the default shader language as parameter",	"")
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
		Renderer(EMode nMode, PLCore::uint32 nZBufferBits, PLCore::uint32 nStencilBits, PLCore::uint32 nMultisampleAntialiasingSamples, PLCore::String sDefaultShaderLanguage);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Renderer();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Setup the renderer capabilities
		*/
		void SetupCapabilities();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FixedFunctions *m_pFixedFunctions;	/**< Fixed functions interface implementation, can be a null pointer */
		FontManager	   *m_pFontManager;		/**< Null renderer font manager, always valid! */
		PLCore::uint32	m_nViewPortX;
		PLCore::uint32	m_nViewPortY;
		PLCore::uint32	m_nViewPortWidth;
		PLCore::uint32	m_nViewPortHeight;
		float			m_fViewPortMinZ;
		float			m_fViewPortMaxZ;
		PLCore::uint32	m_nScissorRectX;
		PLCore::uint32	m_nScissorRectY;
		PLCore::uint32	m_nScissorRectWidth;
		PLCore::uint32	m_nScissorRectHeight;
		float			m_fDepthBoundsZMin;
		float			m_fDepthBoundsZMax;


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Renderer functions         ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::String GetAPI(PLCore::uint32 *pnVersion = nullptr) const;
		virtual PLCore::String GetVendor() const;
		virtual PLCore::String GetDefaultShaderLanguage() const;
		virtual PLRenderer::ShaderLanguage *GetShaderLanguage(const PLCore::String &sShaderLanguage = "");
		virtual PLRenderer::FixedFunctions *GetFixedFunctions() const;
		virtual PLRenderer::FontManager &GetFontManager() const;
		virtual void BackupDeviceObjects();
		virtual void RestoreDeviceObjects();

		//[-------------------------------------------------------]
		//[ Create surface/resource                               ]
		//[-------------------------------------------------------]
		virtual PLRenderer::SurfaceWindow *CreateSurfaceWindow(PLRenderer::SurfaceWindowHandler &cHandler, PLCore::handle nWindow, const PLRenderer::DisplayMode &sDisplayMode, bool bFullscreen = false);
		virtual PLRenderer::SurfaceTextureBuffer *CreateSurfaceTextureBuffer2D(const PLMath::Vector2i &vSize, PLRenderer::TextureBuffer::EPixelFormat nFormat, PLCore::uint32 nFlags = PLRenderer::SurfaceTextureBuffer::Depth | PLRenderer::SurfaceTextureBuffer::Stencil, PLCore::uint8 nMaxColorTargets = 1);
		virtual PLRenderer::SurfaceTextureBuffer *CreateSurfaceTextureBufferRectangle(const PLMath::Vector2i &vSize, PLRenderer::TextureBuffer::EPixelFormat nFormat, PLCore::uint32 nFlags = PLRenderer::SurfaceTextureBuffer::Depth | PLRenderer::SurfaceTextureBuffer::Stencil, PLCore::uint8 nMaxColorTargets = 1);
		virtual PLRenderer::SurfaceTextureBuffer *CreateSurfaceTextureBufferCube(PLCore::uint16 nSize, PLRenderer::TextureBuffer::EPixelFormat nFormat, PLCore::uint32 nFlags = PLRenderer::SurfaceTextureBuffer::Depth | PLRenderer::SurfaceTextureBuffer::Stencil);
		virtual PLRenderer::TextureBuffer1D *CreateTextureBuffer1D(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLCore::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::TextureBuffer2D *CreateTextureBuffer2D(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLCore::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::TextureBuffer *CreateTextureBufferRectangle(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLCore::uint32 nFlags = 0);
		virtual PLRenderer::TextureBuffer3D *CreateTextureBuffer3D(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLCore::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::TextureBufferCube *CreateTextureBufferCube(PLGraphics::Image &cImage, PLRenderer::TextureBuffer::EPixelFormat nInternalFormat = PLRenderer::TextureBuffer::Unknown, PLCore::uint32 nFlags = PLRenderer::TextureBuffer::Mipmaps);
		virtual PLRenderer::IndexBuffer *CreateIndexBuffer();
		virtual PLRenderer::VertexBuffer *CreateVertexBuffer();
		virtual PLRenderer::OcclusionQuery *CreateOcclusionQuery();

		//[-------------------------------------------------------]
		//[ States                                                ]
		//[-------------------------------------------------------]
		virtual bool SetRenderState(PLRenderer::RenderState::Enum nState, PLCore::uint32 nValue);
		virtual bool SetSamplerState(PLCore::uint32 nStage, PLRenderer::Sampler::Enum nState, PLCore::uint32 nValue);

		//[-------------------------------------------------------]
		//[ Misc                                                  ]
		//[-------------------------------------------------------]
		virtual bool BeginScene();
		virtual bool EndScene();
		virtual bool GetDepthBounds(float &fZMin, float &fZMax) const;
		virtual bool SetDepthBounds(float fZMin = 0.0f, float fZMax = 1.0f);
		virtual void GetColorMask(bool &bRed, bool &bGreen, bool &bBlue, bool &bAlpha) const;
		virtual bool SetColorMask(bool bRed = true, bool bGreen = true, bool bBlue = true, bool bAlpha = true);
		virtual bool Clear(PLCore::uint32 nFlags = PLRenderer::Clear::Color | PLRenderer::Clear::ZBuffer,
						   const PLGraphics::Color4 &cColor = PLGraphics::Color4::Black, float fZ = 1.0f, PLCore::uint32 nStencil = 0);

		//[-------------------------------------------------------]
		//[ Get/set current resources                             ]
		//[-------------------------------------------------------]
		virtual bool SetRenderTarget(PLRenderer::Surface *pSurface, PLCore::uint8 nFace = 0);
		virtual bool SetColorRenderTarget(PLRenderer::TextureBuffer *pTextureBuffer, PLCore::uint8 nColorIndex = 0, PLCore::uint8 nFace = 0);
		virtual bool MakeScreenshot(PLGraphics::Image &cImage);
		virtual bool SetTextureBuffer(int nStage = -1, PLRenderer::TextureBuffer *pTextureBuffer = nullptr);
		virtual bool SetIndexBuffer(PLRenderer::IndexBuffer *pIndexBuffer = nullptr);

		//[-------------------------------------------------------]
		//[ Draw                                                  ]
		//[-------------------------------------------------------]
		virtual bool DrawPrimitives(PLRenderer::Primitive::Enum nType, PLCore::uint32 nStartIndex, PLCore::uint32 nNumVertices);
		virtual bool DrawIndexedPrimitives(PLRenderer::Primitive::Enum nType, PLCore::uint32 nMinIndex, PLCore::uint32 nMaxIndex, PLCore::uint32 nStartIndex, PLCore::uint32 nNumVertices);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererNull


#endif // __PLRENDERERNULL_RENDERER_H__
