/*********************************************************\
 *  File: GraphPath.h                                    *
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


#ifndef __PLMATH_GRAPH_PATH_H__
#define __PLMATH_GRAPH_PATH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Resource.h>
#include "PLMath/Vector3.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Graph;
class GraphNode;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A path can be set of links to graph nodes or owning it's own private nodes
*/
class GraphPath : public PLCore::Resource<GraphPath> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Main                                                  ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Resource name to set
		*  @param[in] pManager
		*    Resource manager using this resource, can be NULL
		*/
		PLMATH_API GraphPath(const PLGeneral::String &sName, PLCore::ResourceManager<GraphPath> *pManager = NULL);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pOwnerGraph
		*    Owner graph, if NULL the path has it's own private nodes
		*
		*  @note
		*    - A path is linking to graph nodes if it's created from for instance
		*      Graph::FindShortestPath()
		*/
		PLMATH_API GraphPath(Graph *pOwnerGraph = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLMATH_API virtual ~GraphPath();

		/**
		*  @brief
		*    Returns the owner graph of the path
		*
		*  @return
		*    Owner graph of the path, NULL if the path is independent
		*/
		PLMATH_API Graph *GetOwnerGraph() const;

		//[-------------------------------------------------------]
		//[ Nodes                                                 ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of nodes
		*
		*  @return
		*    Number of path nodes
		*/
		PLMATH_API PLGeneral::uint32 GetNumOfNodes() const;

		/**
		*  @brief
		*    Adds a node
		*
		*  @param[in] cNode
		*    Node which should be added, if the path has no owner
		*    graph it will delete the node after it is no longer required.
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMATH_API bool AddNode(GraphNode &cNode);

		/**
		*  @brief
		*    Removes a node
		*
		*  @param[in] nNode
		*    ID of the node which should be removed
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMATH_API bool RemoveNode(PLGeneral::uint32 nNode = 0);

		/**
		*  @brief
		*    Returns a node
		*
		*  @param[in] nID
		*    ID of the node which should be returned
		*
		*  @return
		*    The path node, NULL if there was an error
		*/
		PLMATH_API const GraphNode *GetNode(PLGeneral::uint32 nID = 0) const;

		/**
		*  @brief
		*    Returns a node
		*
		*  @param[in] nID
		*    ID of the node which should be returned
		*
		*  @return
		*    The path node, NULL if there was an error
		*/
		PLMATH_API GraphNode *GetNode(PLGeneral::uint32 nID = 0);

		//[-------------------------------------------------------]
		//[ Tools                                                 ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the length of the path
		*
		*  @return
		*    Path length
		*/
		PLMATH_API float GetLength() const;

		/**
		*  @brief
		*    Returns whether the path is closed or not
		*
		*  @return
		*    'true' if the path is closed, else 'false'
		*
		*  @note
		*    - If a path is closed the first node is taken after the last one
		*/
		PLMATH_API bool IsClosed() const;

		/**
		*  @brief
		*    Sets if the path is closed or not
		*
		*  @param[in] bClosed
		*    Should the path be closed?
		*
		*  @see
		*    - IsClosed()
		*/
		PLMATH_API void SetClosed(bool bClosed = false);

		/**
		*  @brief
		*    Calculates the position at the given node index
		*
		*  @param[in] fNodeIndex
		*    Node index (0-<number of nodes>, automatically wrapped into that range)
		*  @param[in] bLinear
		*    Linear interpolation? Else a catmull rom curve is used.
		*
		*  @return
		*    The path position corresponding to the given node index
		*
		*  @remarks
		*    If the position isn't linear interpolated the first and last node are skipped.
		*    (only required for the curve progression)
		*    Therefore at node index 0 the position will be the position node 2.
		*/
		PLMATH_API Vector3 GetPosByNodeIndex(float fNodeIndex, bool bLinear = true) const;

		/**
		*  @brief
		*    Calculates the position by using percentage along the path
		*
		*  @param[in] fPercentageAlongPath
		*    Percentage along the path (0-1, automatically wrapped into that range)
		*  @param[in] bLinear
		*    Linear interpolation? Else a catmull rom curve is used.
		*
		*  @return
		*    The path position corresponding to the given percentage along the path
		*
		*  @remarks
		*    If the position isn't linear interpolated the first and last node are skipped.
		*    (only required for the curve progression)
		*    Therefore at node index 0 the position will be the position node 2.
		*/
		PLMATH_API Vector3 GetPosByPercentageAlongPath(float fPercentageAlongPath, bool bLinear = true) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Graph						 *m_pOwnerGraph;	/**< Owner graph, can be NULL */
		bool						  m_bClosed;		/**< Is the path closed? */
		PLGeneral::Array<GraphNode*>  m_lstNodes;		/**< Node list */


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Resource functions             ]
	//[-------------------------------------------------------]
	public:
		PLMATH_API virtual GraphPath &operator =(const GraphPath &cSource);


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLMATH_API virtual bool Unload();
		PLMATH_API virtual PLGeneral::String GetLoadableTypeName() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_GRAPH_PATH_H__
