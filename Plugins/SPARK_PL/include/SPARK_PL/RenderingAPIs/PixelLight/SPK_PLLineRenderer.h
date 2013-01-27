/*********************************************************\
 *  File: SPK_PLLineRenderer.h                           *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __SPARK_PL_LINERENDERER_H__
#define __SPARK_PL_LINERENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <Extensions/Renderers/SPK_LineRendererInterface.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SPK_PLBuffer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    An abstract Renderer drawing particles as PixelLight lines
*
*  @remarks
*    The length of the lines is function of the Particle velocity and is defined in the universe space
*    while the width is fixed and defines in the screen space (in pixels).<br>
*    <br>
*    Below are the parameters of Particle that are used in this Renderer (others have no effects) :
*    <ul>
*    <li>SPK::PARAM_RED</li>
*    <li>SPK::PARAM_GREEN</li>
*    <li>SPK::PARAM_BLUE</li>
*    <li>SPK::PARAM_ALPHA (only if blending is enabled)</li>
*    </ul>
*
*  @note
*    - Basing on "SPK::GL::GLLineRenderer" (this includes most of the comments)
*/
class SPK_PLLineRenderer : public SPK_PLRenderer, public SPK::LineRendererInterface {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor of SPK_PLLineRenderer
		*/
		SPARK_PL_API virtual ~SPK_PLLineRenderer();


	//[-------------------------------------------------------]
	//[ Public virtual SPK::BufferHandler functions           ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void createBuffers(const SPK::Group &group) override;
		SPARK_PL_API virtual void destroyBuffers(const SPK::Group &group) override;


	//[-------------------------------------------------------]
	//[ Protected definitions                                 ]
	//[-------------------------------------------------------]
	protected:
		static const std::string PLBufferName;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor of SPK_PLLineRenderer
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fLength
		*    The length multiplier of this SPK_PLLineRenderer
		*  @param[in] fWidth
		*    The width of this SPK_PLLineRenderer in pixels
		*/
		SPK_PLLineRenderer(PLRenderer::Renderer &cRenderer, float fLength = 1.0f, float fWidth = 1.0f);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SPK_PLBuffer *m_pSPK_PLBuffer;	/**< Used SPK_PLBuffer instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_LINERENDERER_H__
