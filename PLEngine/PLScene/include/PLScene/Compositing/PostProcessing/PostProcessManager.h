/*********************************************************\
 *  File: PostProcessManager.h                           *
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


#ifndef __PLSCENE_COMPOSITING_POSTPROCESSING_POSTPROCESSMANAGER_H__
#define __PLSCENE_COMPOSITING_POSTPROCESSING_POSTPROCESSMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/ElementManager.h>
#include <PLCore/Tools/Loadable.h>
#include <PLRenderer/Renderer/TextureBuffer.h>
#include "PLScene/Compositing/PostProcessing/PostProcess.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class RendererContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a manager for the post process element
*/
class PostProcessManager : public PLGeneral::ElementManager<PostProcess>, public PLCore::Loadable {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRendererContext
		*    Renderer context to use
		*/
		PLS_API PostProcessManager(PLRenderer::RendererContext &cRendererContext);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~PostProcessManager();

		/**
		*  @brief
		*    Returns the used renderer context
		*
		*  @return
		*    The used renderer context
		*/
		PLS_API PLRenderer::RendererContext &GetRendererContext() const;

		/**
		*  @brief
		*    Returns the texture format
		*
		*  @return
		*    The texture format
		*
		*  @note
		*    - The default texture format is PLRenderer::TextureBuffer::R8G8B8A8, but some effects like
		*      tone map need PLRenderer::TextureBuffer::R16G16B16A16F for high dynamic range rendering
		*    - Supported texture formats: PLRenderer::TextureBuffer::R8G8B8, PLRenderer::TextureBuffer::R8G8B8A8,
		*      PLRenderer::TextureBuffer::R16G16B16A16F, PLRenderer::TextureBuffer::R32G32B32A32F
		*/
		PLS_API PLRenderer::TextureBuffer::EPixelFormat GetTextureFormat() const;

		/**
		*  @brief
		*    Sets the texture format
		*
		*  @param[in] nFormat
		*    The texture format
		*
		*  @see
		*    - GetTextureFormat
		*/
		PLS_API void SetTextureFormat(PLRenderer::TextureBuffer::EPixelFormat nFormat = PLRenderer::TextureBuffer::R8G8B8A8);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::RendererContext				*m_pRendererContext;	/**< The used renderer context (always valid!) */
		PLRenderer::TextureBuffer::EPixelFormat  m_nTextureFormat;		/**< Texture buffer format */


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool Unload();
		PLS_API virtual PLGeneral::String GetLoadableTypeName() const;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::Loadable functions            ]
	//[-------------------------------------------------------]
	private:
		virtual bool CallLoadable(PLGeneral::File &cFile, PLCore::Loader &cLoader, const PLGeneral::String &sMethod, const PLGeneral::String &sParams);


	//[-------------------------------------------------------]
	//[ Private virtual PLGeneral::ElementManager functions   ]
	//[-------------------------------------------------------]
	private:
		virtual PostProcess *CreateElement(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_COMPOSITING_POSTPROCESSING_POSTPROCESSMANAGER_H__
