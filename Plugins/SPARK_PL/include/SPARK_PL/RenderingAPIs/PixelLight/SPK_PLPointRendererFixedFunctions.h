/*********************************************************\
 *  File: SPK_PLPointRendererFixedFunctions.h            *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
