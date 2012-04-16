/*********************************************************\
 *  File: SPTessellation.h                               *
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


#ifndef __PLSAMPLE_55SURFACEPAINTER_H__
#define __PLSAMPLE_55_SURFACEPAINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/SurfacePainter.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class IndexBuffer;
	class VertexBuffer;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract tessellation surface painter
*/
class SPTessellation : public PLRenderer::SurfacePainter {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SPTessellation, "", PLRenderer::SurfacePainter, "Abstract tessellation surface painter")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		SPTessellation(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SPTessellation();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLRenderer::VertexBuffer *m_pVertexBuffer;				/**< Our renderer vertex buffer, can be a null pointer */
		PLRenderer::IndexBuffer  *m_pIndexBuffer;				/**< Our renderer index buffer, can be a null pointer */
		float					  m_fRotation;					/**< Current rotation of the triangle */
		float					  m_fTessellationLevelInner;	/**< Inner tessellation level */
		float					  m_fTessellationLevelOuter;	/**< Outer tessellation level */


};


#endif // __PLSAMPLE_55_SURFACEPAINTER_H__
