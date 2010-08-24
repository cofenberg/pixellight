/*********************************************************\
 *  File: Renderer.h                                     *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDEREROPENGLES_RENDERER_H__
#define __PLRENDEREROPENGLES_RENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <EGL/egl.h>
#undef Yield 	// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef Success	// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef None	// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef Always	// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#undef PSize	// We undef this to avoid name conflicts with OS macros, why do they need to use macros?!
#include <GLES2/gl2.h>
#include <PLRenderer/Renderer/Backend/RendererBackend.h>
#ifdef LINUX
	#include <X11/Xutil.h>
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FontManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES renderer backend
*
*  @remarks
*    This implementation is basing upon the information found within the following documents:
*    - "OpenGL ES 2.0 API Quick Reference Card": "OpenGL-ES-2_0-Reference-card.pdf" (http://www.khronos.org/opengles/sdk/docs/reference_cards/OpenGL-ES-2_0-Reference-card.pdf)
*    - "OpenGLR ES Common Profile Specification Version 2.0.24 (Full Specification) (April 22, 2009)": "es_full_spec_2.0.24.pdf" (http://www.khronos.org/registry/gles/specs/2.0/es_full_spec_2.0.24.pdf)
*    - "The OpenGL ES Shading Language, Language Version: 1.00, Document Revision: 17, 12 May, 2009, Editor: Robert J. Simpson": "GLSL_ES_Specification_1.0.17.pdf": (http://www.khronos.org/registry/gles/specs/2.0/GLSL_ES_Specification_1.0.17.pdf)
*    - "OpenGL ES Common Profile Specification 2.0.24 (Difference Specification) (April 1, 2009) (Annotated)": "es_cm_spec_2.0.24.pdf" (http://www.khronos.org/registry/gles/specs/2.0/es_cm_spec_2.0.24.pdf)
*/
class Renderer : public PLRenderer::RendererBackend {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SurfaceWindow;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLGeneral::String ShaderLanguageGLSL;	/**< 'GLSL' string */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Renderer, "PLRendererOpenGLES", PLRenderer::RendererBackend, "OpenGL ES renderer backend")
		pl_constructor_5(DefaultConstructor, pl_enum_type(EMode), PLGeneral::uint32, PLGeneral::uint32, PLGeneral::uint32, PLGeneral::String, "Constructor with renderer mode, Z buffer bits, stencil buffer bits, the number of multisample antialiasing samples per pixel and the default shader language as parameter", "")
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
		*    Returns the used EGL display
		*
		*  @return
		*    The used EGL display
		*/
		EGLDisplay GetEGLDisplay() const;

		/**
		*  @brief
		*    Returns the used EGL config
		*
		*  @return
		*    The used EGL config
		*/
		EGLConfig GetEGLConfig() const;

		/**
		*  @brief
		*    Returns the used EGL context
		*
		*  @return
		*    The used EGL context
		*/
		EGLContext GetEGLContext() const;

		/**
		*  @brief
		*    Makes a given EGL surface to the currently used one
		*
		*  @param[in] hEGLSurface
		*    EGL surface to make to the current one, can be NULL, in this case an internal dummy surface is set
		*
		*  @return
		*    'EGL_TRUE' if all went fine, else 'EGL_FALSE'
		*/
		EGLBoolean MakeCurrent(EGLSurface hEGLSurface);

		/**
		*  @brief
		*    Returns a PL format as OpenGL ES format
		*
		*  @param[in] nFormat
		*    PL format to convert
		*
		*  @return
		*    The converted OpenGL ES format (like GL_LUMINANCE, GL_RGB etc.)
		*/
		PLGeneral::uint32 GetOpenGLESPixelFormat(PLRenderer::TextureBuffer::EPixelFormat nFormat) const;

		/**
		*  @brief
		*    Returns a PL data format as OpenGL ES data format
		*
		*  @param[in] nFormat
		*    PL data format to convert
		*
		*  @return
		*    The converted data format (like GL_UNSIGNED_UINT, GL_UNSIGNED_SHORT etc.)
		*/
		PLGeneral::uint32 GetOpenGLESDataFormat(PLRenderer::TextureBuffer::EPixelFormat nFormat) const;

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

		// [TODO] Clean this up!
		bool SetShaderProgramTextureBuffer(int nStage = -1, PLRenderer::TextureBuffer *pTextureBuffer = NULL);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Chooses a EGL config
		*
		*  @param[in] nMultisampleAntialiasingSamples
		*    Multisample antialiasing samples per pixel
		*
		*  @return
		*    The chosen EGL config, NULL on error
		*
		*  @note
		*    - Automatically tries to find fallback configs
		*/
		EGLConfig ChooseConfig(PLGeneral::uint32 nMultisampleAntialiasingSamples) const;

		/**
		*  @brief
		*    Shows some OpenGL ES information
		*/
		void ShowOpenGLESInformation();

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
		*    Sampler state filter mode helper function
		*
		*  @param[in] nStage
		*    Sampler stage
		*
		*  @return
		*    OpenGL ES sampler filter mode
		*/
		GLuint GetCombinedMinMipFilter(PLGeneral::uint32 nStage);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FontManager		   *m_pFontManager;	/**< OpenGL ES renderer font manager, always valid! */
		PLGeneral::uint32	m_nViewPortX;
		PLGeneral::uint32	m_nViewPortY;
		PLGeneral::uint32	m_nViewPortWidth;
		PLGeneral::uint32	m_nViewPortHeight;
		float				m_fViewPortMinZ;
		float				m_fViewPortMaxZ;
		PLGeneral::uint32	m_nScissorRectX;
		PLGeneral::uint32	m_nScissorRectY;
		PLGeneral::uint32	m_nScissorRectWidth;
		PLGeneral::uint32	m_nScissorRectHeight;
		float				m_fDepthBoundsZMin;
		float				m_fDepthBoundsZMax;
		PLGeneral::uint32	m_nVertexOffset;	/**< Current vertex offset */
		// EGL
		EGLDisplay			m_hDisplay;
		EGLConfig			m_hConfig;
		EGLContext			m_hContext;
		EGLNativeWindowType m_nDummyNativeWindow;
		EGLSurface			m_hDummySurface;
		// X11
		#ifdef LINUX
			::Display	   *m_pDisplay;
		#endif


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Renderer functions         ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetAPI(PLGeneral::uint32 *pnVersion = NULL) const;
		virtual PLGeneral::String GetVendor() const;
		virtual PLGeneral::String GetDefaultShaderLanguage() const;
		virtual PLRenderer::FixedFunctions *GetFixedFunctions() const;
		virtual PLRenderer::FontManager &GetFontManager() const;
		virtual bool IsShaderProgramProfileSupported(const PLGeneral::String &sProfile) const;

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
		virtual PLRenderer::ShaderProgram *CreateVertexShaderProgram(const void *pProgram, const PLGeneral::String &sProfile = "", const PLGeneral::String &sDefines = "", const PLGeneral::String &sEntry = "main", const char **ppszAttributes = NULL);
		virtual PLRenderer::ShaderProgram *CreateFragmentShaderProgram(const void *pProgram, const PLGeneral::String &sProfile = "", const PLGeneral::String &sDefines = "", const PLGeneral::String &sEntry = "main", const char **ppszAttributes = NULL);
		virtual PLRenderer::VertexShader *CreateVertexShader(const PLGeneral::String &sShaderLanguage = "");
		virtual PLRenderer::GeometryShader *CreateGeometryShader(const PLGeneral::String &sShaderLanguage = "");
		virtual PLRenderer::FragmentShader *CreateFragmentShader(const PLGeneral::String &sShaderLanguage = "");
		virtual PLRenderer::Program *CreateProgram(const PLGeneral::String &sShaderLanguage = "");
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
		virtual bool SetViewport(const PLMath::Rectangle *pRectangle = NULL, float fMinZ = 0.0f, float fMaxZ = 1.0f);
		virtual bool SetScissorRect(const PLMath::Rectangle *pRectangle = NULL);
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
		virtual bool SetTextureBuffer(int nStage = -1, PLRenderer::TextureBuffer *pTextureBuffer = NULL);
		virtual bool SetIndexBuffer(PLRenderer::IndexBuffer *pIndexBuffer = NULL);
		virtual bool SetVertexShaderProgram(PLRenderer::ShaderProgram *pVertexShaderProgram = NULL);
		virtual bool SetFragmentShaderProgram(PLRenderer::ShaderProgram *pFragmentShaderProgram = NULL);
		virtual bool SetProgram(PLRenderer::Program *pProgram = NULL);

		//[-------------------------------------------------------]
		//[ Draw                                                  ]
		//[-------------------------------------------------------]
		virtual bool DrawPrimitives(PLRenderer::Primitive::Enum nType, PLGeneral::uint32 nStartIndex, PLGeneral::uint32 nNumVertices);
		virtual bool DrawIndexedPrimitives(PLRenderer::Primitive::Enum nType, PLGeneral::uint32 nMinIndex, PLGeneral::uint32 nMaxIndex, PLGeneral::uint32 nStartIndex, PLGeneral::uint32 nNumVertices);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES


#endif // __PLRENDEREROPENGLES_RENDERER_H__
