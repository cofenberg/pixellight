/*********************************************************\
 *  File: SPK_PLLineRenderer.h                           *
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


#ifndef __SPARK_PL_LINERENDERER_H__
#define __SPARK_PL_LINERENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <Extensions/Renderers/SPK_LineRendererInterface.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPI/SPK_PLRenderer.h"


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
*    A Renderer drawing particles as PixelLight lines
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
	//[ SPARK macro                                           ]
	//[-------------------------------------------------------]
	SPK_IMPLEMENT_REGISTERABLE(SPK_PLLineRenderer)


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates and registers a new SPK_PLLineRenderer
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fLength
		*    The length multiplier of this SPK_PLLineRenderer
		*  @param[in] fWidth
		*    The width of this SPK_PLLineRenderer in pixels
		*
		*  @return
		*    A new registered SPK_PLLineRenderer
		*/
		SPARK_PL_API static SPK_PLLineRenderer *Create(PLRenderer::Renderer &cRenderer, float fLength = 1.0f, float fWidth = 1.0f);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
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
		SPARK_PL_API SPK_PLLineRenderer(PLRenderer::Renderer &cRenderer, float fLength = 1.0f, float fWidth = 1.0f);

		/**
		*  @brief
		*    Destructor of SPK_PLLineRenderer
		*/
		SPARK_PL_API virtual ~SPK_PLLineRenderer();


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void render(const SPK::Group &group);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::BufferHandler functions           ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void createBuffers(const SPK::Group &group);
		SPARK_PL_API virtual void destroyBuffers(const SPK::Group &group);


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		static const std::string PLBufferName;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SPK_PLBuffer *m_pSPK_PLBuffer;	/**< Used SPK_PLBuffer instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_LINERENDERER_H__
