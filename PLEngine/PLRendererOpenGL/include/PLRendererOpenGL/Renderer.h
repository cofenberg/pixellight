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


#ifndef __PLRENDEREROPENGL_RENDERER_H__
#define __PLRENDEREROPENGL_RENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/Backend/RendererBackend.h>
#include "PLRendererOpenGL/PLRendererOpenGL.h"
#include "PLRendererOpenGL/Misc/Extensions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Context;
class FontManager;
class FixedFunctions;
class ShaderLanguage;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL 1.1 + extensions renderer backend
*/
class Renderer : public PLRenderer::RendererBackend, public OpenGLExtensions {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FixedFunctions;
	friend class OpenGLRenderContext;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDEREROPENGL_RTTI_EXPORT, Renderer, "PLRendererOpenGL", PLRenderer::RendererBackend, "OpenGL 1.1 + extensions renderer backend")
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
		PLRENDEREROPENGL_API Renderer(EMode nMode, PLGeneral::uint32 nZBufferBits, PLGeneral::uint32 nStencilBits, PLGeneral::uint32 nMultisampleAntialiasingSamples, PLGeneral::String sDefaultShaderLanguage);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Renderer();

		/**
		*  @brief
		*    Returns the OpenGL render context
		*
		*  @return
		*    The OpenGL render context, NULL on error
		*/
		Context *GetContext() const;

		/**
		*  @brief
		*    Returns the used multisample antialiasing samples per pixel
		*
		*  @return
		*    The used multisample antialiasing samples per pixel
		*/
		PLGeneral::uint32 GetMultisampleAntialiasingSamples() const;

		/**
		*  @brief
		*    Returns a PL format as OpenGL format
		*
		*  @param[in] nFormat
		*    PL format to convert
		*
		*  @return
		*    The converted OpenGL format (like GL_LUMINANCE, GL_RGB etc.)
		*/
		PLGeneral::uint32 GetOpenGLPixelFormat(PLRenderer::TextureBuffer::EPixelFormat nFormat) const;

		/**
		*  @brief
		*    Returns a PL data format as OpenGL data format
		*
		*  @param[in] nFormat
		*    PL data format to convert
		*
		*  @return
		*    The converted data format (like GL_UNSIGNED_UINT, GL_UNSIGNED_SHORT etc.)
		*/
		PLGeneral::uint32 GetOpenGLDataFormat(PLRenderer::TextureBuffer::EPixelFormat nFormat) const;

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
		*    Creates a OpenGL render context instance
		*
		*  @return
		*    The created a OpenGL render context instance, NULL on error
		*
		*  @note
		*    - The new render context will be automatically set as the current active one
		*/
		Context *CreateContext();

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
		*    General OpenGL settings
		*/
		void GeneralSettings();

		/**
		*  @brief
		*    Sampler state filter mode helper function
		*
		*  @param[in] nStage
		*    Sampler stage
		*
		*  @return
		*    OpenGL sampler filter mode
		*/
		GLuint GetCombinedMinMipFilter(PLGeneral::uint32 nStage);

		/**
		*  @brief
		*    Enables/disables VSync
		*
		*  @param[in] bEnabled
		*    Use VSync?
		*/
		void SwapInterval(bool bEnabled);

		/**
		*  @brief
		*    Restores the device states
		*/
		void RestoreDeviceStates();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Context														*m_pContext;						/**< OpenGL render context, can be NULL (= renderer not initialized) */
		FixedFunctions												*m_pFixedFunctions;					/**< Fixed functions interface implementation, can be NULL */
		FontManager													*m_pFontManager;					/**< OpenGL renderer font manager, always valid! */
		bool														 m_bSceneRendering;					/**< Is the scene rendering currently active? (see BeginScene/EndScene) */
		bool														 m_bCurrentSwapInterval;			/**< Is swap interval currently enabled? */
		PLGeneral::uint32											 m_nMultisampleAntialiasingSamples;	/**< Multisample antialiasing samples per pixel */
		PLGeneral::String											 m_sDefaultShaderLanguage;			/**< Name of the default shader language to use */
		PLGeneral::List<const PLCore::Class*>						 m_lstShaderLanguages;				/**< List of available shader language classes */
		PLGeneral::HashMap<PLGeneral::String, const PLCore::Class*>  m_mapShaderLanguages;				/**< Map of available shader language classes "<Name> => <Class>" */
		PLGeneral::Array<ShaderLanguage*>							 m_lstShaderLanguageInstances;		/**< List of available shader language instances */
		PLGeneral::HashMap<PLGeneral::String, ShaderLanguage*>		 m_mapShaderLanguageInstances;		/**< Map of available shader language instances "<Name> => <Instance>" */

		/** OpenGL texture type at the certain texture stages */
		PLGeneral::uint32 *m_nTextureBufferTypes;

		PLRenderer::TextureBuffer **m_ppPrevTextureBuffer;	/**< The previous non NULL texture buffer */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Renderer functions         ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetAPI(PLGeneral::uint32 *pnVersion = NULL) const;
		virtual PLGeneral::String GetVendor() const;
		virtual PLGeneral::String GetDefaultShaderLanguage() const;
		virtual PLRenderer::ShaderLanguage *GetShaderLanguage(const PLGeneral::String &sShaderLanguage = "");
		virtual PLRenderer::FixedFunctions *GetFixedFunctions() const;
		virtual PLRenderer::FontManager &GetFontManager() const;
		virtual void BackupDeviceObjects();
		virtual void RestoreDeviceObjects();
		virtual void Update();

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

		// [TODO] Clean this up!
		PLRENDEREROPENGL_API bool SetShaderProgramTextureBuffer(int nStage = -1, PLRenderer::TextureBuffer *pTextureBuffer = NULL);

		virtual bool SetIndexBuffer(PLRenderer::IndexBuffer *pIndexBuffer = NULL);
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
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_RENDERER_H__
