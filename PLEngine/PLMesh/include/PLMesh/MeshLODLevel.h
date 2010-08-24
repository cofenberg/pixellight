/*********************************************************\
 *  File: MeshLODLevel.h                                 *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLMESH_MESH_LODLEVEL_H__
#define __PLMESH_MESH_LODLEVEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include "PLMesh/Mesh.h"
#include "PLMesh/Geometry.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class IndexBuffer;
	class VertexBuffer;
}
namespace PLMesh {
	class MeshOctree;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh LOD level
*
*  @remark
*    A LOD level for a mesh can redifine one or more of the mesh's base data
*    Index data (indices into the vertex data)
*    Geometries (that structure the index data in different parts)
*/
class MeshLODLevel {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Main functions                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pMesh
		*    Pointer to the owner mesh, can be NULL
		*/
		PLMESH_API MeshLODLevel(Mesh *pMesh = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API ~MeshLODLevel();

		/**
		*  @brief
		*    Returns the mesh the LOD level belongs to
		*
		*  @return
		*    Pointer to the owner mesh, can be NULL
		*/
		PLMESH_API Mesh *GetMesh() const;

		/**
		*  @brief
		*    Sets the mesh the LOD level belongs to
		*
		*  @param[in] pMesh
		*    Pointer to the owner mesh, can be NULL
		*/
		PLMESH_API void SetMesh(Mesh *pMesh = NULL);

		/**
		*  @brief
		*    Returns the distance for using this LOD level
		*
		*  @return
		*    Distance for the LOD level
		*/
		PLMESH_API float GetLODDistance() const;

		/**
		*  @brief
		*    Sets the distance for using this LOD level
		*
		*  @param[in] fDistance
		*    Distance for the LOD level
		*/
		PLMESH_API void SetLODDistance(float fDistance = 0.0f);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLMESH_API MeshLODLevel &operator =(const MeshLODLevel &cSource);

		//[-------------------------------------------------------]
		//[ Index buffer functions                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Clears the index buffer for this LOD level
		*/
		PLMESH_API void ClearIndexBuffer();

		/**
		*  @brief
		*    Creates the index buffer for this LOD level
		*
		*  @note
		*    - If you don't want to overwrite the mesh's index buffer
		*      (if the LOD level only alters the vertex buffers or geometries),
		*      you don't have to call this function. In this case
		*      the meshes standard index buffer will be used.
		*/
		PLMESH_API void CreateIndexBuffer();

		/**
		*  @brief
		*    Returns the index buffer for this LOD level
		*
		*  @return
		*    The LOD level's index buffer, can be NULL
		*/
		PLMESH_API PLRenderer::IndexBuffer *GetIndexBuffer() const;

		//[-------------------------------------------------------]
		//[ Geometry functions                                    ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the total number of LOD level triangles
		*
		*  @return
		*    Total number of LOD level triangles
		*/
		PLMESH_API PLGeneral::uint32 GetNumOfTriangles() const;

		/**
		*  @brief
		*    Clears the geometries for this LOD level
		*/
		PLMESH_API void ClearGeometries();

		/**
		*  @brief
		*    Creates the geometries for this LOD level
		*
		*  @note
		*     - If you don't want to overwrite the mesh's geometries
		*       (if the LOD level only alters the index or vertex buffers),
		*       you don't have to call this function. In this case
		*       the meshes standard geometries will be used.
		*/
		PLMESH_API void CreateGeometries();

		/**
		*  @brief
		*    Gets the geometries of this LOD level
		*
		*  @return
		*    List of geometries, can be NULL
		*/
		PLMESH_API PLGeneral::Array<Geometry> *GetGeometries() const;

		//[-------------------------------------------------------]
		//[ Visibility functions                                  ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Creates the LOD level octree
		*
		*  @param[in]  nSubdivide
		*    Octree subdivide
		*  @param[in]  nMinGeometries
		*    Minimum number of geometries per octree
		*  @param[out] plstOctreeIDList
		*    Will optionally store a list of octrees each geometry is on, can be NULL
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - This function doesn't manipulate the geometries etc. Therefore an octree
		*      can only be efficient if there are different smaller geometries because
		*      the octree later checks which geometries are currently visible!
		*    - The tool function GenerateOctreeGeometries() will split up the geometries
		*      in octree friendly parts
		*/
		PLMESH_API bool CreateOctree(PLGeneral::uint32 nSubdivide = 1, PLGeneral::uint32 nMinGeometries = 10,
									 PLGeneral::Array<PLGeneral::Array<PLGeneral::uint32>*> *plstOctreeIDList = NULL);

		/**
		*  @brief
		*    Destroys the LOD level octree
		*/
		PLMESH_API void DestroyOctree();

		/**
		*  @brief
		*    Returns the LOD level octree
		*
		*  @return
		*    LOD level octree, NULL if there's no octree
		*
		*  @note
		*    - The octree is used for fast visibility and collision determination
		*/
		PLMESH_API MeshOctree *GetOctree() const;

		//[-------------------------------------------------------]
		//[ Tool functions                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Builds the connectivity information
		*
		*  @note
		*    - This function calls BuildTriangleList() and BuildEdgeList()
		*/
		PLMESH_API void BuildConnectivity();

		/**
		*  @brief
		*    Builds the current triangle list
		*
		*  @note
		*    - The triangle list must be updated after manipulating geometries!
		*/
		PLMESH_API void BuildTriangleList();

		/**
		*  @brief
		*    Gets the triangle list
		*
		*  @return
		*    Triangle list
		*
		*  @see
		*    - BuildTriangleList()
		*/
		PLMESH_API PLGeneral::Array<MeshTriangle> &GetTriangleList();

		/**
		*  @brief
		*    Builds the current edge list
		*
		*  @note
		*    - The edge list must be updated after manipulating geometries!
		*    - The triangle list must be build before the edge list can be constructed!
		*      (see BuildTriangleList())
		*/
		PLMESH_API void BuildEdgeList();

		/**
		*  @brief
		*    Gets the edge list
		*
		*  @return
		*    Edge list
		*
		*  @see
		*    - BuildEdgeList()
		*/
		PLMESH_API PLGeneral::Array<MeshEdge> &GetEdgeList();

		/**
		*  @brief
		*    Gets a triangle of a geometry
		*
		*  @param[in]  nGeometry
		*    Geometry ID
		*  @param[in]  nIndex
		*    Triangle index
		*  @param[out] nVertex1
		*    Will receive the first triangle vertex index
		*  @param[out] nVertex2
		*    Will receive the second triangle vertex index
		*  @param[out] nVertex3
		*    Will receive the third triangle vertex index
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - When requesting many triangle vertices you should lock the index buffer
		*      using GetIndexBuffer() for more performance by self!
		*    - GetTrianglePlaneList() is faster because it is using a precalculated triangle
		*      list
		*/
		PLMESH_API bool GetTriangle(PLGeneral::uint32 nGeometry, PLGeneral::uint32 nIndex,
									PLGeneral::uint32 &nVertex1, PLGeneral::uint32 &nVertex2, PLGeneral::uint32 &nVertex3) const;

		/**
		*  @brief
		*    Splits up geometries to geometries of single triangles
		*
		*  @param[in] bSingleGeometries
		*    One geometry per triangle? Recommended if octrees should be build but
		*    not good when preparing the mesh for optimize!
		*  @param[in] pSplit
		*    Optional index list of the geometries to split, if NULL all geometries will be split
		*  @param[in] nSplitNumber
		*    If pSplit ist't NULL this indicates the number of geometries to split
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If there was an octree it will be destroyed!
		*/
		PLMESH_API bool SplitGeometries(bool bSingleGeometries = false, PLGeneral::uint32 *pSplit = NULL, PLGeneral::uint32 nSplitNumber = 0);

		/**
		*  @brief
		*    Joins geometries with the same properties to one single geometry
		*
		*  @param[in] pJoin
		*    Optional index list of the geometries to join, if NULL all geometries will be joined
		*  @param[in] nJoinNumber
		*    If pJoin ist't NULL, this indicates the number of geometries to join
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If there was an octree it will be destroyed!
		*    - Geometries of the primitive type PLRenderer::Primitive::LineStrip,
		*      PLRenderer::Primitive::TriangleStrip and PLRenderer::Primitive::TriangleFan can't be joined!
		*/
		PLMESH_API bool JoinGeometries(PLGeneral::uint32 *pJoin = NULL, PLGeneral::uint32 nJoinNumber = 0);

		/**
		*  @brief
		*    Optimizes the geometries for an octree
		*
		*  @param[in] nSubdivide
		*    Octree subdivide
		*  @param[in] nMinGeometries
		*    Minimum number of geometries per octree
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If there was an octree it will be destroyed!
		*    - The octree itself can be created using CreateOctree()
		*    - Its recommended to use GenerateStrips() to optimize the new
		*      geometries!
		*    - This may take some time so don't do it during runtime!
		*/
		PLMESH_API bool GenerateOctreeGeometries(PLGeneral::uint32 nSubdivide = 1, PLGeneral::uint32 nMinGeometries = 10);

		/**
		*  @brief
		*    Optimizes the geometries using triangle strips
		*
		*  @param[in] nVertexCacheSize
		*    Sets the cache size which the stripfier uses to optimize the data.
		*    Controls the length of the generated individual strips.
		*    CacheSize should be 0 to disable the cache optimizer, 10 for a GeForce 256
		*    or a GeForce 2, 16 or 18 for a GeForce 3 or a GeForce 4.
		*    Play a bit with this setting to find the best value for your 3D card.
		*  @param[in] nMinStripLength
		*    Sets the minimum acceptable size for a strip, in triangles.
		*    All strips generated which are shorter than this will be thrown into
		*    one big, separate list.
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - This may take some time so don't do it during runtime!
		*    - Ensure that there are ONLY geometries of triangles, (PLRenderer::Primitive::TriangleList)
		*      else this function will not work! (see SplitGeometries())
		*/
		PLMESH_API bool GenerateStrips(PLGeneral::uint32 nVertexCacheSize = 18, PLGeneral::uint32 nMinStripLength = 3);

		/**
		*  @brief
		*    Calculates the LOD level bounding box
		*
		*  @param[in]  lstGeometries
		*    The LOD level geometries to use
		*  @param[in]  cVertexBuffer
		*    Vertex buffer to use
		*  @param[out] vMinPos
		*    Will receive the minimum bounding box position
		*  @param[out] vMaxPos
		*    Will receive the maximum bounding box position
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMESH_API bool CalculateBoundingBox(const PLGeneral::Array<const Geometry*> &lstGeometries, PLRenderer::VertexBuffer &cVertexBuffer, PLMath::Vector3 &vMinPos, PLMath::Vector3 &vMaxPos) const;

		/**
		*  @brief
		*    Calculates the LOD level bounding sphere
		*
		*  @param[in]  lstGeometries
		*    The LOD level geometries to use
		*  @param[in]  cVertexBuffer
		*    Vertex buffer to use
		*  @param[out] vPos
		*    Will receive the bounding sphere position
		*  @param[out] fRadius
		*    Will receive the bounding sphere radius
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMESH_API bool CalculateBoundingSphere(const PLGeneral::Array<const Geometry*> &lstGeometries, PLRenderer::VertexBuffer &cVertexBuffer, PLMath::Vector3 &vPos, float &fRadius) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Internal data
		Mesh *m_pMesh;	/**< Owner mesh, can be NULL */

		// LOD data
		float m_fDistance;	/**< LOD distance */

		// Overwritten data
		PLRenderer::IndexBuffer    *m_pIndexBuffer;		/**< Index buffer, can be NULL */
		PLGeneral::Array<Geometry> *m_plstGeometries;	/**< Geometries, can be NULL */

		// Visibility
		MeshOctree *m_pOctree;	/**< Octree for geometry visibility determination, can be NULL */

		// Precalculated data
		PLGeneral::Array<MeshTriangle> m_lstTriangles;	/**< List of triangles */
		PLGeneral::Array<MeshEdge>     m_lstEdges;		/**< List of edges */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESH_LODLEVEL_H__ 
