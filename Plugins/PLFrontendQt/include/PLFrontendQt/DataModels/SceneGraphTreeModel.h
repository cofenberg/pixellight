/*********************************************************\
 *  File: SceneGraphTreeModel.h                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
		QModelIndex GetModelIndexForSceneNodeModifier(PLScene::SceneNodeModifier* nodeObj);
		void AddSceneNode(PLScene::SceneContainer *pContainer, PLScene::SceneNode *pSceneNode, int nPosition = -1);
		void AddSceneNodeModifier(PLScene::SceneNode *pParentNode, PLScene::SceneNodeModifier *pSceneNodeModifier, int nPosition = -1);

		
		
		bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);
		QMimeData *mimeData(const QModelIndexList &indexes) const;
		QStringList mimeTypes() const;
		Qt::DropActions supportedDropActions() const;

	//[-------------------------------------------------------]
	//[ Public virtual QAbstractItemModel functions           ]
	//[-------------------------------------------------------]
	public:
		virtual bool removeRows(int startRow, int count, const QModelIndex& parent = QModelIndex()) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bInMoveOperation;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_SCENEGRAPHTREEMODEL_H__
