/*********************************************************\
 *  File: GMMSurface.h                                   *
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


#ifndef __PLNATURE_SCENENODE_GMMSURFACE_H__
#define __PLNATURE_SCENENODE_GMMSURFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Quadtree.h>
#include "PLNature/PLNature.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Texture;
	class Renderer;
	class VertexBuffer;
	class TextureHandler;
	class MaterialHandler;
}
namespace PLNature {
	class GMMSurfacePatch;
	class GMMSurfaceLevel;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLNature {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Geometrically MipMapping surface
*
*  @remarks
*    This surface takes a hight map and displays it with an optimal level of detail
*    using height variance and distance to camera.
*
*  @note
*    - For optimal frustum culling a quadtree is used
*    - The standard usage of this surface type is a terrain
*    - Similar to the ROAM surface but this technique is quite better for modern hardware
*/
class GMMSurface {


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    GMM surface vertex
		*/
		struct Vertex {
			float x, y, z;	/**< Position */
			float u, v;		/**< Texture coordinate */
		};


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
		PLNATURE_API GMMSurface(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		PLNATURE_API ~GMMSurface();

		/**
		*  @brief
		*    Creates the GMM surface
		*
		*  @param[in] nHeightMapSize
		*    Height map size
		*  @param[in] fHeightMap
		*    Reference to the height map
		*  @param[in] nPatchSize
		*    Patch size
		*  @param[in] nGeoMipMaps
		*    Number of geometrically mip maps, -1 = automatic
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The reference to the height map is used directly, short the reference must
		*      be valid as long as the GMM surface is used!!
		*    - The GMM takes place in the single patches of the surface further they
		*      are used for frustum culling and each patch could have another material
		*/
		PLNATURE_API bool Create(PLCore::uint32 nHeightMapSize, float fHeightMap[], PLCore::uint32 nPatchSize = 16, int nGeoMipMaps = -1);

		/**
		*  @brief
		*    Kills the GMM surface
		*/
		PLNATURE_API void Destroy();

		/**
		*  @brief
		*    Returns the viewer position
		*
		*  @return
		*    Viewer position
		*/
		PLNATURE_API const PLMath::Vector3 &GetViewerPos() const;

		/**
		*  @brief
		*    Sets the viewer position
		*
		*  @param[in] vPos
		*    Viewer position
		*/
		PLNATURE_API void SetViewerPos(const PLMath::Vector3 &vPos);

		/**
		*  @brief
		*    Returns the size of the height map
		*
		*  @return
		*    The size of the height map
		*/
		PLNATURE_API PLCore::uint32 GetHeightMapSize() const;

		/**
		*  @brief
		*    Returns a pointer to the height map
		*
		*  @return
		*    Pointer to the height map, can be a null pointer
		*/
		PLNATURE_API const float *GetHeightMap() const;

		/**
		*  @brief
		*    Returns the number of surface vertices
		*
		*  @return
		*    Number of surface vertices
		*/
		PLNATURE_API PLCore::uint32 GetVertices() const;

		/**
		*  @brief
		*    Returns a pointer to a surface vertex
		*
		*  @param[in] nID
		*    ID of the vertex
		*
		*  @return
		*    Pointer to a surface vertex, a null pointer if there was an error
		*/
		PLNATURE_API Vertex *GetVertex(PLCore::uint32 nID = 0) const;

		/**
		*  @brief
		*    Returns the height of a height map coordinate
		*
		*  @param[in] nX
		*    Height map x coordinate
		*  @param[in] nY
		*    Height map y coordinate
		*
		*  @return
		*    The height of a height map coordinate
		*/
		PLNATURE_API float GetHeight(PLCore::uint32 nX, PLCore::uint32 nY) const;

		/**
		*  @brief
		*    Sets the height of a height map coordinate
		*
		*  @param[in] nX
		*    Height map x coordinate
		*  @param[in] nY
		*    Height map y coordinate
		*  @param[in] fHeight
		*    New height at the coordinate
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If a height value in the height map is manipulated the patch using this
		*      coordinate must be recalculated during the next GMM surface update
		*/
		PLNATURE_API bool SetHeight(PLCore::uint32 nX, PLCore::uint32 nY, float fHeight = 0);

		/**
		*  @brief
		*    Returns the size of a patch
		*
		*  @return
		*    Size of a patch
		*/
		PLNATURE_API PLCore::uint32 GetPatchSize() const;

		/**
		*  @brief
		*    Returns the number of patches per column/row
		*
		*  @return
		*    Number of patches per column/row
		*/
		PLNATURE_API PLCore::uint32 GetXYPatches() const;

		/**
		*  @brief
		*    Returns the total number of patches in the GMM surface
		*
		*  @return
		*    The total number of patches in the GMM surface
		*/
		PLNATURE_API PLCore::uint32 GetPatches() const;

		/**
		*  @brief
		*    Returns a pointer to the patch with the given ID
		*
		*  @param[in] nID
		*    ID of the patch which should be returned
		*
		*  @return
		*    A pointer to the patch with the given ID, a null pointer if there was an error
		*/
		PLNATURE_API GMMSurfacePatch *GetPatch(PLCore::uint32 nID) const;

		/**
		*  @brief
		*    Returns the number of geometrically mip maps
		*
		*  @return
		*    Number of geometrically mip maps
		*/
		PLNATURE_API PLCore::uint32 GetGeoMipMaps() const;

		/**
		*  @brief
		*    Sets the neighbour GMM surfaces
		*
		*  @param[in] pLeft
		*    The left neighbour GMM surface
		*  @param[in] pTop
		*    The top neighbour GMM surface
		*  @param[in] pRight
		*    The right neighbour GMM surface
		*  @param[in] pBottom
		*    The bottom neighbour GMM surface
		*/
		PLNATURE_API void SetNeighbours(GMMSurface *pLeft = nullptr, GMMSurface *pTop = nullptr, GMMSurface *pRight = nullptr, GMMSurface *pBottom = nullptr);

		/**
		*  @brief
		*    Returns the surface material handler
		*
		*  @return
		*    Surface material handler
		*/
		PLNATURE_API PLRenderer::MaterialHandler &GetMaterialHandler();

		/**
		*  @brief
		*    Returns the GMM surface quadtree
		*
		*  @return
		*    GMM surface quadtree
		*/
		PLNATURE_API PLMath::Quadtree &GetQuadtree();

		/**
		*  @brief
		*    Updates the GMM surface
		*
		*  @note
		*    - Must be done before the GMM surface is drawn!! (updates detail etc.)
		*/
		PLNATURE_API void Update();

		/**
		*  @brief
		*    Draws the GMM surface
		*
		*  @note
		*    - The GMM surface must be updated before it's drawn! (updates detail etc.)
		*/
		PLNATURE_API void Draw() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws a patch
		*
		*  @param[in] cPatch
		*    Patch to draw
		*/
		void DrawPatch(GMMSurfacePatch &cPatch) const;

		/**
		*  @brief
		*    Initializes the GMM surface
		*/
		void Init();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Side
		*/
		enum ESide {
			Right,	/**< Right side */
			Top,	/**< Top side */
			Left,	/**< Left side */
			Bottom	/**< Bottom side */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// General
		PLRenderer::Renderer		 *m_pRenderer;			/**< Used renderer (always valid!) */
		PLMath::Vector3				  m_vViewerPos;			/**< Viewer position */
		GMMSurface					 *m_pNeighbour[4];		/**< Neighbour GMM surfaces, can be a null pointer */
		PLCore::uint32				  m_nVertices;			/**< Number of surface vertices */
		PLRenderer::VertexBuffer	 *m_pVertexBuffer;		/**< Vertex buffer, can be a null pointer */
		Vertex						 *m_pVertex;			/**< Surface vertices, can be a null pointer */
		PLRenderer::MaterialHandler	 *m_pMaterialHandler;	/**< Surface material (always valid!) */

		// Height map
		PLCore::uint32 	 m_nHeightMapSize;	/**< Height map size */
		float			*m_pfHeightMap;		/**< Height map data, can be a null pointer */

		// Patches
		PLCore::uint32	  m_nPatchSize,	/**< Patch size */
						  m_nXYPatches,	/**< Patches per column / row */
						  m_nPatches;	/**< Total number of patches */
		GMMSurfacePatch **m_ppPatches;	/**< The patches, can be a null pointer */

		// Levels
		PLCore::uint32      m_nGeoMipMaps;	/**< Number of geometrically mip maps */
		GMMSurfaceLevel   **m_ppLevels;		/**< Levels, can be a null pointer */

		// Quadtree
		PLMath::Quadtree m_cQuadtree;	/**< Quadtree for frustum culling */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLNature


#endif // __PLNATURE_SCENENODE_GMMSURFACE_H__
