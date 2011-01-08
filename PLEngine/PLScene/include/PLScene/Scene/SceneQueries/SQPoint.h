/*********************************************************\
 *  File: SQPoint.h                                      *
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


#ifndef __PLSCENE_SCENEQUERY_POINT_H__
#define __PLSCENE_SCENEQUERY_POINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
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
*    Point intersection scene query class
*
*  @remarks
*    This point test scene query will enumerate all scene nodes intersecting the
*    given point.
*/
class SQPoint : public SceneQuery {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SQPoint, "PLScene", PLScene::SceneQuery, "Point intersection scene query class")
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
		PLS_API SQPoint();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SQPoint();

		/**
		*  @brief
		*    Returns the used point
		*
		*  @return
		*    The used point
		*/
		PLS_API PLMath::Vector3 &GetPoint();


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
		PLMath::Vector3 m_vPoint;	/**< Point used for the query */


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


#endif // __PLSCENE_SCENEQUERY_POINT_H__
