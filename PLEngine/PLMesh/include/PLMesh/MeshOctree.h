/*********************************************************\
 *  File: MeshOctree.h                                   *
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


#ifndef __PLMESH_MESHOCTREE_H__
#define __PLMESH_MESHOCTREE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Octree.h>
#include "PLMesh/PLMesh.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Bitset;
	template <class AType> class Array;
}
namespace PLGraphics {
	class Color4;
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
*    Mesh octree
*/
class MeshOctree : public PLMath::Octree {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMESH_API MeshOctree();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshOctree();

		/**
		*  @brief
		*    Builds the octree
		*
		*  @param[in]  cMeshLODLevel
		*    Owner mesh LOD level
		*  @param[in]  nNumOfGeometries
		*    Number of geometry indices
		*  @param[in]  nGeometries
		*    Geometry indices
		*  @param[out] plstOctreeIDList
		*    Will optionally store a list of octrees each geometry is in if not NULL
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMESH_API bool Build(MeshLODLevel &cMeshLODLevel, PLGeneral::uint32 nNumOfGeometries, const PLGeneral::uint32 nGeometries[],
							  PLGeneral::Array<PLGeneral::Array<PLGeneral::uint32>*> *plstOctreeIDList = NULL);

		/**
		*  @brief
		*    Draws the octree
		*
		*  @param[in] cColor
		*    Color to use
		*  @param[in] mWorldViewProjection
		*    World view projection matrix to use
		*  @param[in] fLineWidth
		*    Line width
		*/
		PLMESH_API void Draw(const PLGraphics::Color4 &cColor, const PLMath::Matrix4x4 &mWorldViewProjection, float fLineWidth = 1.0f) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		MeshLODLevel	  *m_pOwnerMeshLODLevel;	/**< Pointer to the owner, can be NULL */
		PLGeneral::uint32  m_nNumOfGeometries;		/**< Number of geometry indices */
		PLGeneral::uint32 *m_pnGeometries;			/**< Geometry indices, can be NULL */


	//[-------------------------------------------------------]
	//[ Private virtual PLMath::Octree functions              ]
	//[-------------------------------------------------------]
	private:
		virtual void CustomVisible(PLGeneral::Bitset *pBitset = NULL);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHOCTREE_H__
