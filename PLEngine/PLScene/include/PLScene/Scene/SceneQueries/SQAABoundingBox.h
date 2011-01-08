/*********************************************************\
 *  File: SQAABoundingBox.h                              *
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


#ifndef __PLSCENE_SCENEQUERY_AABOUNDINGBOX_H__
#define __PLSCENE_SCENEQUERY_AABOUNDINGBOX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/AABoundingBox.h>
#include "PLScene/Scene/SceneQuery.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SceneHierarchyNode;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Axis aligned bounding box intersection scene query class
*
*  @remarks
*    This axis aligned bounding box test scene query will enumerate all scene nodes intersecting the
*    given axis aligned bounding box. The intersection box will ALWAYS stay an axis aligned bounding box,
*    even if it's transformed into a rotated child scene container! Therefore, if there are such rotated
*    child scene containers, a new axis aligned bounding box in this container space is calculated
*    automatically. As result, even scene nodes which are not inside the 'original' intersection volume
*    may be within this transformed volume.
*/
class SQAABoundingBox : public SceneQuery {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SQAABoundingBox, "PLScene", PLScene::SceneQuery, "Axis aligned bounding box intersection scene query class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SQAABoundingBox();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SQAABoundingBox();

		/**
		*  @brief
		*    Returns the used axis aligned bounding box
		*
		*  @return
		*    The used axis aligned bounding box
		*/
		PLS_API PLMath::AABoundingBox &GetAABoundingBox();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Recursive part of PerformQuery()
		*
		*  @param[in] cHierarchyNode
		*    Current scene hierarchy node we work on
		*
		*  @return
		*    'true' to continue the query, 'false' if stop it right now
		*/
		bool PerformQueryRec(SceneHierarchyNode &cHierarchyNode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::AABoundingBox m_cAABoundingBox;	/**< Axis aligned bounding box used for the query */


	//[-------------------------------------------------------]
	//[ Public virtual SceneQuery functions                   ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool PerformQuery();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENEQUERY_AABOUNDINGBOX_H__
