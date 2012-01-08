/*********************************************************\
 *  File: SceneGraphTreeModel.cpp                        *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QBrush>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Object.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/TreeItemBase.h"
#include "PLFrontendQt/DataModels/SceneGraphNodeTreeItemBase.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


class SceneGraphHeaderTreeItem : public SceneGraphNodeTreeItemBase {


	public:
		SceneGraphHeaderTreeItem(QObject *parent = nullptr) : SceneGraphNodeTreeItemBase(parent)
		{
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column == 0)
				return "Node Name";

			return QVariant();
		}

		bool IsSceneNode() {
			return false;
		}

		bool IsSceneNodeModifier()
		{
			return false;
		}

		PLCore::Object *GetObject()
		{
			return nullptr;
		}


};

class SceneGraphNodeModifierTreeItem : public SceneGraphNodeTreeItemBase {


	public:
		SceneGraphNodeModifierTreeItem(PLScene::SceneNodeModifier *nodeObj, QObject *parent = nullptr) : SceneGraphNodeTreeItemBase(parent),
			m_nodeObj(nodeObj),
			m_nodeName(nodeObj ? QtStringAdapter::PLToQt(m_nodeObj->GetClass()->GetName().GetUTF8()) : "null modifier"),
			m_textColor(Qt::cyan)
		{
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column == 0) {
				if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
					return m_nodeName;
			}

			return QVariant();
		}

		bool IsSceneNode()
		{
			return false;
		}

		bool IsSceneNodeModifier()
		{
			return true;
		}

		PLCore::Object *GetObject()
		{
			return m_nodeObj;
		}


	private:
		PLScene::SceneNodeModifier *m_nodeObj;	// Can be a null pointer
		QString						m_nodeName;
		QBrush						m_textColor;


};

void CreateSceneGraphItemsFromContainer(PLScene::SceneContainer *pContainer, QObject *parent);

class SceneGraphNodeTreeItem : public SceneGraphNodeTreeItemBase {


	public:
		SceneGraphNodeTreeItem(PLScene::SceneNode *nodeObj, QObject *parent = nullptr) : SceneGraphNodeTreeItemBase(parent),
			m_nodeObj(nodeObj),
			EventHandlerOnDestroy(&SceneGraphNodeTreeItem::OnDestroy, this)
		{
			// Connect event handler
			m_nodeObj->SignalDestroy.Connect(EventHandlerOnDestroy);

			if (m_nodeObj->IsContainer()) {
				PLScene::SceneContainer *container = (PLScene::SceneContainer*)m_nodeObj;
				CreateSceneGraphItemsFromContainer(container, this);
			}

			for(PLCore::uint32 i=0; i<m_nodeObj->GetNumOfModifiers(); i++) {
				// Get the current scene node modifier
				PLScene::SceneNodeModifier *node = m_nodeObj->GetModifier("", i);

				// Add this scene node modifier as item, but only if it has no "Automatic"-flag set
				// -> "This scene node modifier was created automatically during runtime and should
				//     not be saved with the scene. Such scene nodes modifiers may also be hidden for
				//     instance within a scene editor."
				if (!(node->GetFlags() & PLScene::SceneNodeModifier::Automatic))
					new SceneGraphNodeModifierTreeItem(node, this);
			}

			GetIconFromSceneNode();
		}

		void GetIconFromSceneNode()
		{
			m_Icon = QPixmap::fromImage(GetQImage(m_nodeObj->GetClass()->GetProperties().Get("Icon")));
		}

		QImage GetQImage(const PLCore::String imageName)
		{
			PLGraphics::Image cImage;
			bool bRet = cImage.LoadByFilename(imageName);
			QImage img;

			if (bRet) {
				PLGraphics::ImageBuffer *buf = cImage.GetBuffer();

				if (buf->HasAnyData()) {
					const PLCore::uint8 *data = buf->GetData();
					QImage img1((const uchar*)data, buf->GetSize().width, buf->GetSize().height,QImage::Format_ARGB32);
					return img1.scaled(24,24, Qt::KeepAspectRatio, Qt::SmoothTransformation).rgbSwapped();
				}
			}
			return img;
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (role == Qt::DecorationRole)
				return m_Icon;

			if (role != Qt::DisplayRole)
				return QVariant();

			if (column == 0 && m_nodeObj)
				return QtStringAdapter::PLToQt(m_nodeObj->GetName().GetUTF8());

			return QVariant();
		}

		bool IsSceneNode()
		{
			return true;
		}

		bool IsSceneNodeModifier()
		{
			return false;
		}

		PLCore::Object *GetObject()
		{
			return m_nodeObj;
		}

	private:
		/**
		*  @brief
		*    Called when the scene node assigned with this item was destroyed
		*/
		void OnDestroy()
		{
			// Argh! Mayday! We lost our scene node!
			m_nodeObj = nullptr;

			// [TODO] Review this situation when the scene node get's killed, update the tree view. Maybe we don't need
			// to have an own event handler for each and every tree item and a single one for the whole tree is enough.
			// (maybe we just need to know that an item is now invalid due to removal, then rebuild the tree?)
		}

	private:
		PLScene::SceneNode	   *m_nodeObj;	// Can be a null pointer
		QPixmap				    m_Icon;
		PLCore::EventHandler<>  EventHandlerOnDestroy;


};

void CreateSceneGraphItemsFromContainer(PLScene::SceneContainer *pContainer, QObject *parent)
{
	for (PLCore::uint32 i=0; i<pContainer->GetNumOfElements(); i++) {
		// Get the current scene node
		PLScene::SceneNode *node = pContainer->GetByIndex(i);

		// Add this scene node as item, but only if it has no "Automatic"-flag set
		// -> "This scene node was created automatically during runtime and should
		//     not be saved with the scene. Such scene nodes may also be hidden for
		//     instance within a scene editor."
		if (!(node->GetFlags() & PLScene::SceneNode::Automatic))
			new SceneGraphNodeTreeItem(node, parent);
	}
}

SceneGraphTreeModel::SceneGraphTreeModel(QObject *parent) : TreeModelBase(new SceneGraphHeaderTreeItem, parent)
{
}

void SceneGraphTreeModel::SetStartNode(PLScene::SceneNode* nodeObj, bool hideStartNode)
{
	beginResetModel();
	const QObjectList &childs = GetRootItem()->children();
	qDeleteAll(childs.begin(), childs.end());

	if (nodeObj) {
		if (!hideStartNode || !nodeObj->IsContainer())
			new SceneGraphNodeTreeItem(nodeObj, GetRootItem());
		else
			CreateSceneGraphItemsFromContainer(static_cast<PLScene::SceneContainer*>(nodeObj), GetRootItem());
	}
	endResetModel();
}

PLScene::SceneNode *SceneGraphTreeModel::GetSceneNodeFromIndex(const QModelIndex &index)
{
	SceneGraphNodeTreeItemBase *treeItem = GetSceneTreeItemFromIndex(index);
	return (treeItem && treeItem->IsSceneNode() && treeItem->GetObject()) ? (PLScene::SceneNode*)treeItem->GetObject() : nullptr;
}

PLScene::SceneNodeModifier *SceneGraphTreeModel::GetSceneNodeModifierFromIndex(const QModelIndex &index)
{
	SceneGraphNodeTreeItemBase *treeItem = GetSceneTreeItemFromIndex(index);
	return (treeItem && treeItem->IsSceneNodeModifier() && treeItem->GetObject()) ? (PLScene::SceneNodeModifier*)treeItem->GetObject() : nullptr;
}

SceneGraphNodeTreeItemBase *SceneGraphTreeModel::GetSceneTreeItemFromIndex(const QModelIndex &index)
{
	return (!index.isValid() || index.model() != this) ? nullptr : (SceneGraphNodeTreeItemBase*)GetTreeItemFromIndex(index);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
