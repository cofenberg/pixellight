/*********************************************************\
 *  File: SPMultiViewShaders.h                           *
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


#ifndef __PLDEMORENDERERMULTIVIEW_SURFACEPAINTER_SHADERS_H__
#define __PLDEMORENDERERMULTIVIEW_SURFACEPAINTER_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPMultiView.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Program;
	class VertexShader;
	class FragmentShader;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Shaders based multi view surface painter
*/
class SPMultiViewShaders : public SPMultiView {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SPMultiViewShaders, "", SPMultiView, "Shaders based multi view surface painter")
		pl_constructor_1(ParameterConstructor, PLRenderer::Renderer&, "Parameter constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		SPMultiViewShaders(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SPMultiViewShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::VertexShader	*m_pVertexShader;	/**< Vertex shader, can be NULL */
		PLRenderer::FragmentShader	*m_pFragmentShader;	/**< Fragment shader, can be NULL */
		PLRenderer::Program			*m_pProgram;		/**< GPU program, can be NULL */


	//[-------------------------------------------------------]
	//[ Private virtual SPMultiView functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual void DrawScene(PLGeneral::uint32 nScene = 0);


};


#endif // __PLDEMORENDERERMULTIVIEW_SURFACEPAINTER_SHADERS_H__
