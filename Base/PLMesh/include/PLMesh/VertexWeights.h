/*********************************************************\
 *  File: VertexWeights.h                                *
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


#ifndef __PLMESH_VERTEXWEIGHTS_H__
#define __PLMESH_VERTEXWEIGHTS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Array.h>
#include "PLMesh/PLMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Vertex weights class for managing a list of weights per vertex
*
*  @note
*    - A vertex can have multiple weights
*/
class VertexWeights {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMESH_API VertexWeights();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API ~VertexWeights();

		/**
		*  @brief
		*    Get the vertex weight indices array
		*
		*  @return
		*    Vertex weight indices array
		*
		*  @note
		*    - This array holds the vertex weight indices per vertex
		*      (see Mesh::GetVertexWeights())
		*/
		PLMESH_API PLCore::Array<PLCore::uint32> &GetWeights();
		PLMESH_API const PLCore::Array<PLCore::uint32> &GetWeights() const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This vertex weights
		*/
		PLMESH_API VertexWeights &operator =(const VertexWeights &cSource);

		/**
		*  @brief
		*    Compares two vertex weights
		*
		*  @param[in] cVertexWeights
		*    Vertex weights to compare with
		*
		*  @return
		*    'true' if both vertex weights are equal, else 'false'
		*/
		PLMESH_API bool operator ==(const VertexWeights &cVertexWeights) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Array<PLCore::uint32> m_lstWeights;	/**< Vertex weights */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_VERTEXWEIGHTS_H__
