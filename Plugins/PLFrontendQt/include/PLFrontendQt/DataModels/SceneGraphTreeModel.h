/*********************************************************\
 *  File: SceneGraphTreeModel.h                          *
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


#ifndef __PLFRONTENDQT_SCENEGRAPHTREEMODEL_H__
#define __PLFRONTENDQT_SCENEGRAPHTREEMODEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DataModels/TreeModelBase.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SceneNode;
	class SceneNodeModifier;
	class SceneContainer;
}
namespace PLFrontendQt {
	namespace DataModels {
		class SceneGraphNodeTreeItemBase;
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
*    Scene graph tree model
*/
class PLFRONTENDQT_API SceneGraphTreeModel : public TreeModelBase {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		enum SceneGraphTreeModelRoles {
			ClassNameRole = Qt::UserRole+1,
			InternalObjectPointerRole
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit SceneGraphTreeModel(QObject *parent = nullptr);
		
		/**
		*  @brief
		*    Set the start scene node for this model
		*
		*  @param[in] nodeObj
		*    the start scene node
		* 
		*  @param[in] hideStartNode
		*    specifies if the start node be hidden
		*/
		void SetStartNode(PLScene::SceneNode *nodeObj, bool hideStartNode = false);
		PLScene::SceneNode *GetSceneNodeFromIndex(const QModelIndex &index);
		PLScene::SceneNodeModifier *GetSceneNodeModifierFromIndex(const QModelIndex &index);
		SceneGraphNodeTreeItemBase *GetSceneTreeItemFromIndex(const QModelIndex &index);
		QModelIndex GetModelIndexForSceneNode(PLScene::SceneNode* nodeObj);
		void AddSceneNode(PLScene::SceneContainer *pContainer, PLScene::SceneNode *pSceneNode, int cPosition = -1);
		void AddSceneNodeModifier(PLScene::SceneNode *pParentNode, PLScene::SceneNodeModifier *pSceneNodeModifier, int cPosition = -1);


	//[-------------------------------------------------------]
	//[ Public virtual QAbstractItemModel functions           ]
	//[-------------------------------------------------------]
	public:
		virtual bool removeRows(int startRow, int count, const QModelIndex& parent = QModelIndex()) override;
#ifdef WIN32		
		virtual QModelIndexList match(const QModelIndex &start, int role, const QVariant &value, int hits = 1, Qt::MatchFlags flags = Qt::MatchFlags(Qt::MatchStartsWith|Qt::MatchWrap)) const override;
#endif


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_SCENEGRAPHTREEMODEL_H__
