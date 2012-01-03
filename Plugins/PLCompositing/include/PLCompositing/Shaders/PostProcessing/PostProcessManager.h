/*********************************************************\
 *  File: PostProcessManager.h                           *
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


#ifndef __PLCOMPOSITING_POSTPROCESSING_POSTPROCESSMANAGER_H__
#define __PLCOMPOSITING_POSTPROCESSING_POSTPROCESSMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Loadable.h>
#include <PLCore/Container/ElementManager.h>
#include <PLRenderer/Renderer/TextureBuffer.h>
#include "PLCompositing/Shaders/PostProcessing/PostProcess.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class RendererContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a manager for the post process element
*/
class PostProcessManager : public PLCore::ElementManager<PostProcess>, public PLCore::Loadable {


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
		PLCOM_API PostProcessManager(PLRenderer::RendererContext &cRendererContext);

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~PostProcessManager();

		/**
		*  @brief
		*    Returns the used renderer context
		*
		*  @return
		*    The used renderer context
		*/
		PLCOM_API PLRenderer::RendererContext &GetRendererContext() const;

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
		PLCOM_API PLRenderer::TextureBuffer::EPixelFormat GetTextureFormat() const;

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
		PLCOM_API void SetTextureFormat(PLRenderer::TextureBuffer::EPixelFormat nFormat = PLRenderer::TextureBuffer::R8G8B8A8);


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
		PLCOM_API virtual bool Unload() override;
		PLCOM_API virtual PLCore::String GetLoadableTypeName() const override;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::Loadable functions            ]
	//[-------------------------------------------------------]
	private:
		virtual bool CallLoadable(PLCore::File &cFile, PLCore::Loader &cLoader, const PLCore::String &sMethod, const PLCore::String &sParams) override;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ElementManager functions      ]
	//[-------------------------------------------------------]
	private:
		virtual PostProcess *CreateElement(const PLCore::String &sName) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_POSTPROCESSING_POSTPROCESSMANAGER_H__
