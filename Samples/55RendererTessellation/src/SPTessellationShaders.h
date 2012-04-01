/*********************************************************\
 *  File: SPTessellationShaders.h                        *
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


#ifndef __PLSAMPLE_55_SURFACEPAINTER_SHADERS_H__
#define __PLSAMPLE_55_SURFACEPAINTER_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPTessellation.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class VertexShader;
	class GeometryShader;
	class FragmentShader;
	class ProgramWrapper;
	class TessellationControlShader;
	class TessellationEvaluationShader;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Shaders based tessellation surface painter
*
*  @note
*    - The geometry shader is only passing thru data and it's purpose is to show how geometry shaders are used
*/
class SPTessellationShaders : public SPTessellation {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SPTessellationShaders, "", SPTessellation, "Shaders based tessellation surface painter")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLRenderer::Renderer&,	"Parameter constructor",	"")
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
		SPTessellationShaders(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SPTessellationShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::VertexShader				 *m_pVertexShader;					/**< Vertex shader, can be a null pointer */
		PLRenderer::TessellationControlShader	 *m_pTessellationControlShader;		/**< Tessellation control shader, can be a null pointer */
		PLRenderer::TessellationEvaluationShader *m_pTessellationEvaluationShader;	/**< Tessellation evaluation shader, can be a null pointer */
		PLRenderer::GeometryShader				 *m_pGeometryShader;				/**< Geometry shader, can be a null pointer */
		PLRenderer::FragmentShader				 *m_pFragmentShader;				/**< Fragment shader, can be a null pointer */
		PLRenderer::ProgramWrapper				 *m_pProgram;						/**< GPU program, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::SurfacePainter functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnPaint(PLRenderer::Surface &cSurface) override;


};


#endif // __PLSAMPLE_55_SURFACEPAINTER_SHADERS_H__
