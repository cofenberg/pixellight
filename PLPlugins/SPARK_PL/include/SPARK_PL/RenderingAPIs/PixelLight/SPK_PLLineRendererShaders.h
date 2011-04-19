/*********************************************************\
 *  File: SPK_PLLineRendererShaders.h                    *
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


#ifndef __SPARK_PL_LINERENDERER_SHADERS_H__
#define __SPARK_PL_LINERENDERER_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A Renderer drawing particles as PixelLight lines using shaders
*
*  @note
*    - Basing on "SPK::GL::GLLineRenderer" (this includes most of the comments)
*/
class SPK_PLLineRendererShaders : public SPK_PLLineRenderer {


	//[-------------------------------------------------------]
	//[ SPARK macro                                           ]
	//[-------------------------------------------------------]
	SPK_IMPLEMENT_REGISTERABLE(SPK_PLLineRendererShaders)


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates and registers a new SPK_PLLineRendererShaders
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fLength
		*    The length multiplier of this SPK_PLLineRendererShaders
		*  @param[in] fWidth
		*    The width of this SPK_PLLineRendererShaders in pixels
		*
		*  @return
		*    A new registered SPK_PLLineRendererShaders
		*/
		SPARK_PL_API static SPK_PLLineRendererShaders *Create(PLRenderer::Renderer &cRenderer, float fLength = 1.0f, float fWidth = 1.0f);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor of SPK_PLLineRendererShaders
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fLength
		*    The length multiplier of this SPK_PLLineRendererShaders
		*  @param[in] fWidth
		*    The width of this SPK_PLLineRendererShaders in pixels
		*/
		SPK_PLLineRendererShaders(PLRenderer::Renderer &cRenderer, float fLength = 1.0f, float fWidth = 1.0f);

		/**
		*  @brief
		*    Destructor of SPK_PLLineRendererShaders
		*/
		SPARK_PL_API virtual ~SPK_PLLineRendererShaders();


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void render(const SPK::Group &group);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_LINERENDERER_SHADERS_H__
