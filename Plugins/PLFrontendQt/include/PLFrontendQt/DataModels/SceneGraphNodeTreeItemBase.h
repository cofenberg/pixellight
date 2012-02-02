/*********************************************************\
 *  File: SceneGraphNodeTreeItemBase.h                   *
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


#ifndef __PLFRONTENDQT_SCENEGRAPHNODETREEITEMBASE_H__
#define __PLFRONTENDQT_SCENEGRAPHNODETREEITEMBASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DataModels/TreeItemBase.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Object;
}
namespace PLFrontendQt {
	namespace DataModels {
		class SceneGraphTreeModel;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene graph node tree item base
*/
class PLFRONTENDQT_API SceneGraphNodeTreeItemBase : public TreeItemBase {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit SceneGraphNodeTreeItemBase(SceneGraphTreeModel &cModel, const QModelIndex &parentIdx, int rowNr, TreeItemBase *parent);
		virtual bool IsSceneNode() = 0;
		virtual bool IsSceneNodeModifier() = 0;
		virtual PLCore::Object *GetObject() = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SceneGraphTreeModel		&m_cModel;
// 		int						 m_cRow;
		QModelIndex				 m_cParentModelIndex;
		QModelIndex				 m_cModelIndex;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_SCENEGRAPHNODETREEITEMBASE_H__
