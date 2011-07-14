/*********************************************************\
 *  File: RendererContext.h                              *
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


#ifndef __PLRENDERER_RENDERERCONTEXT_H__
#define __PLRENDERER_RENDERERCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include "PLRenderer/Renderer/Renderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class String;
}
namespace PLRenderer {
	class TextureManager;
	class EffectManager;
	class MaterialManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Renderer context
*/
class RendererContext {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class RendererBackend;


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<>	EventUpdate;	/**< Update event */


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates a renderer context instance
		*
		*  @param[in] sBackend
		*    Name of the renderer backend to use (for example 'PLRendererOpenGL::Renderer')
		*  @param[in] nMode
		*    Mode hint the renderer should run in, the renderer is not enforced to use this requested mode
		*  @param[in] nZBufferBits
		*     Z buffer bits (just a hint, for example 24)
		*  @param[in] nStencilBits
		*    Stencil buffer bits (just a hint, for example 8)
		*  @param[in] nMultisampleAntialiasingSamples
		*    Multisample antialiasing samples per pixel, <=1 means no antialiasing (just a hint)
		*  @param[in] sDefaultShaderLanguage
		*    The name of the default shader language of the renderer (for example "GLSL" or "Cg"), if the string
		*    is empty, the default is chosen by the renderer implementation, this information is just a hint
		*
		*  @return
		*    Creates a renderer context instance, a null pointer on error
		*/
		PLRENDERER_API static RendererContext *CreateInstance(const PLGeneral::String &sBackend, Renderer::EMode nMode = Renderer::ModeBoth, PLGeneral::uint32 nZBufferBits = 24, PLGeneral::uint32 nStencilBits = 8, PLGeneral::uint32 nMultisampleAntialiasingSamples = 0, const PLGeneral::String &sDefaultShaderLanguage = "");


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~RendererContext();

		/**
		*  @brief
		*    Returns the used renderer
		*
		*  @return
		*    Reference to the used renderer
		*/
		PLRENDERER_API Renderer &GetRenderer() const;

		/**
		*  @brief
		*    Returns the texture manager of this renderer context
		*
		*  @return
		*    Reference to the texture manager of this renderer context
		*/
		PLRENDERER_API TextureManager &GetTextureManager();

		/**
		*  @brief
		*    Returns the effect manager of this renderer context
		*
		*  @return
		*    Reference to the effect manager of this renderer context
		*/
		PLRENDERER_API EffectManager &GetEffectManager();

		/**
		*  @brief
		*    Returns the material manager of this renderer context
		*
		*  @return
		*    Reference to the material manager of this renderer context
		*/
		PLRENDERER_API MaterialManager &GetMaterialManager();

		/**
		*  @brief
		*    Updates the render context
		*
		*  @note
		*    - Should be called once per frame
		*    - Updates the effect manager
		*    - Emits the update event
		*    - Updates the renderer ("redraw")
		*    - Collects renderer context profiling information
		*/
		PLRENDERER_API void Update();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		PLRENDERER_API RendererContext(Renderer &cRenderer);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		RendererContext &operator =(const RendererContext &cSource);


	//[-------------------------------------------------------]
	//[ Privat data                                           ]
	//[-------------------------------------------------------]
	private:
		Renderer		*m_pRenderer;			/**< Used renderer, always valid! */
		TextureManager  *m_pTextureManager;		/**< The texture manager of this renderer context, a null pointer if not yet initialised */
		EffectManager   *m_pEffectManager;		/**< The effect manager of this renderer context, a null pointer if not yet initialised */
		MaterialManager *m_pMaterialManager;	/**< The material manager of this renderer context, a null pointer if not yet initialised */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_RENDERERCONTEXT_H__
