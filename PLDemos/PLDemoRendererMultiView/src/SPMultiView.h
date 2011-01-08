/*********************************************************\
 *  File: SPMultiView.h                                  *
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


#ifndef __PLDEMORENDERERMULTIVIEW_SURFACEPAINTER_H__
#define __PLDEMORENDERERMULTIVIEW_SURFACEPAINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/SurfacePainter.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMesh {
	class MeshHandler;
	class MeshManager;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract multi view surface painter
*/
class SPMultiView : public PLRenderer::SurfacePainter {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SPMultiView, "", PLRenderer::SurfacePainter, "Abstract multi view surface painter")
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
		SPMultiView(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SPMultiView();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		float				 m_fRotation;			/**< Current rotation of the teapot */
		PLMesh::MeshManager *m_pMeshManager;		/**< Mesh manager (always valid!) */
		PLMesh::MeshHandler *m_pMeshHandlerSphere;	/**< Mesh handler holding your sphere (always valid!) */
		PLMesh::MeshHandler *m_pMeshHandlerTorus;	/**< Mesh handler holding your torus (always valid!) */
		PLMesh::MeshHandler *m_pMeshHandlerCube;	/**< Mesh handler holding your cube (always valid!) */


	//[-------------------------------------------------------]
	//[ Private virtual SPMultiView functions                 ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws a scene
		*
		*  @param[in] nScene
		*    Scene to draw
		*/
		virtual void DrawScene(PLGeneral::uint32 nScene = 0) = 0;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::SurfacePainter functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnPaint(PLRenderer::Surface &cSurface);


};


#endif // __PLDEMORENDERERMULTIVIEW_SURFACEPAINTER_H__
