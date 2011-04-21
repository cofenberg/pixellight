/*********************************************************\
 *  File: SPK_PLPointRendererShaders.h                   *
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


#ifndef __SPARK_PL_POINTRENDERER_SHADERS_H__
#define __SPARK_PL_POINTRENDERER_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    A Renderer drawing drawing particles as PixelLight points using shaders
*
*  @note
*    - Basing on "SPK::GL::GLPointRenderer" (this includes most of the comments)
*/
class SPK_PLPointRendererShaders : public SPK_PLPointRenderer {


	//[-------------------------------------------------------]
	//[ SPARK macro                                           ]
	//[-------------------------------------------------------]
	SPK_IMPLEMENT_REGISTERABLE(SPK_PLPointRendererShaders)


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates and registers a new SPK_PLPointRendererShaders
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fSize
		*    The size of the points
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used
		*
		*  @return
		*    A new registered SPK_PLPointRendererShaders
		*/
		SPARK_PL_API static SPK_PLPointRendererShaders *Create(PLRenderer::Renderer &cRenderer, const PLGeneral::String &sShaderLanguage = "", float fSize = 1.0f);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/** 
		*  @brief
		*    Constructor of SPK_PLPointRendererShaders
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fSize
		*    The size of the points
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used
		*/
		SPK_PLPointRendererShaders(PLRenderer::Renderer &cRenderer, const PLGeneral::String &sShaderLanguage = "", float fSize = 1.0f);

		/**
		*  @brief
		*    Destructor of SPK_PLPointRendererShaders
		*/
		SPARK_PL_API virtual ~SPK_PLPointRendererShaders();


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void render(const SPK::Group &group);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sShaderLanguage;	/**< Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_POINTRENDERER_SHADERS_H__
