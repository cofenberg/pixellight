/*********************************************************\
 *  File: SPK_PLPointRendererFixedFunctions.h            *
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


#ifndef __SPARK_PL_POINTRENDERER_FIXEDFUNCTIONS_H__
#define __SPARK_PL_POINTRENDERER_FIXEDFUNCTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/FixedFunctions.h>
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLPointRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A Renderer drawing drawing particles as PixelLight points using fixed functions
*
*  @note
*    - Basing on "SPK::GL::GLPointRenderer" (this includes most of the comments)
*/
class SPK_PLPointRendererFixedFunctions : public SPK_PLPointRenderer {


	//[-------------------------------------------------------]
	//[ SPARK macro                                           ]
	//[-------------------------------------------------------]
	SPK_IMPLEMENT_REGISTERABLE(SPK_PLPointRendererFixedFunctions)


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates and registers a new SPK_PLPointRendererFixedFunctions
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fSize
		*    The size of the points
		*
		*  @return
		*    A new registered SPK_PLPointRendererFixedFunctions
		*/
		SPARK_PL_API static SPK_PLPointRendererFixedFunctions *Create(PLRenderer::Renderer &cRenderer, float fSize = 1.0f);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/** 
		*  @brief
		*    Constructor of SPK_PLPointRendererFixedFunctions
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fSize
		*    The size of the points
		*/
		SPK_PLPointRendererFixedFunctions(PLRenderer::Renderer &cRenderer, float fSize = 1.0f);

		/**
		*  @brief
		*    Destructor of SPK_PLPointRendererFixedFunctions
		*/
		SPARK_PL_API virtual ~SPK_PLPointRendererFixedFunctions();

		/**
		*  @brief
		*    Gets the texture blending function of this SPK_PLQuadRendererFixedFunctions
		*
		*  @return
		*    The texture blending function of this SPK_PLQuadRendererFixedFunctions
		*/
		SPARK_PL_API PLRenderer::FixedFunctions::TextureEnvironment::Enum GetTextureBlending() const;

		/**
		*  @brief
		*    Sets the texture blending function of this SPK_PLQuadRendererFixedFunctions
		*
		*  @param[in] nTextureBlending
		*    The texture blending function of this SPK_PLQuadRendererFixedFunctions
		*
		*  @remarks
		*    The texture blending function is one of the PixelLight texture blending functions.
		*/
		SPARK_PL_API void SetTextureBlending(PLRenderer::FixedFunctions::TextureEnvironment::Enum nTextureBlending);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void render(const SPK::Group &group) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::FixedFunctions::TextureEnvironment::Enum  m_nTextureBlending;	/**< The texture blending function of this SPK_PLRenderer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_POINTRENDERER_FIXEDFUNCTIONS_H__
