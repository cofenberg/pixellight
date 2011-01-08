/*********************************************************\
 *  File: SPSampleTeapot.h                               *
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


#ifndef __PLSAMPLETEAPOT_SURFACEPAINTER_H__
#define __PLSAMPLETEAPOT_SURFACEPAINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/SurfacePainter.h>
#include "PLPlugin/PLPlugin.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMesh {
	class MeshHandler;
	class MeshManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This surface painter is called when the window content should be drawn
*/
class SPSampleTeapot : public PLRenderer::SurfacePainter {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPLUGIN_RTTI_EXPORT, SPSampleTeapot, "", PLRenderer::SurfacePainter, "This surface painter is called when the window content should be drawn")
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
		SPSampleTeapot(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SPSampleTeapot();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float				 m_fRotation;		/**< Current rotation of the teapot */
		PLMesh::MeshManager *m_pMeshManager;	/**< Mesh manager (always valid!) */
		PLMesh::MeshHandler *m_pMeshHandler;	/**< Mesh handler holding your teapot (always valid!) */


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::SurfacePainter functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnPaint(PLRenderer::Surface &cSurface);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin


#endif // __PLSAMPLETEAPOT_SURFACEPAINTER_H__
