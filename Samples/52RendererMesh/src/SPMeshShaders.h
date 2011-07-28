/*********************************************************\
 *  File: SPMeshShaders.h                                *
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


#ifndef __PLSAMPLE_52_SURFACEPAINTER_SHADERS_H__
#define __PLSAMPLE_52_SURFACEPAINTER_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPMesh.h"


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
*    Shaders based mesh surface painter
*/
class SPMeshShaders : public SPMesh {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SPMeshShaders, "", SPMesh, "Shaders based mesh surface painter")
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
		SPMeshShaders(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SPMeshShaders();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::VertexShader	*m_pVertexShader;	/**< Vertex shader, can be a null pointer */
		PLRenderer::FragmentShader	*m_pFragmentShader;	/**< Fragment shader, can be a null pointer */
		PLRenderer::Program			*m_pProgram;		/**< GPU program, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::SurfacePainter functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnPaint(PLRenderer::Surface &cSurface) override;


};


#endif // __PLSAMPLE_52_SURFACEPAINTER_SHADERS_H__
