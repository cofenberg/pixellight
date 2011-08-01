/*********************************************************\
 *  File: SceneGraphTreeModel.cpp                        *
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

		virtual QVariant data(const int column, const int role)
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

		virtual QVariant data(const int column, const int role)
		{
			if (column == 0) {
				if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
					return m_nodeName;
				// [TODO]
				//            else if (role == Qt::ForegroundRole)
				//                return m_textColor;
				//            else if (role == Qt::BackgroundRole)
				//                return QBrush(Qt::magenta);
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
		PLScene::SceneNodeModifier *m_nodeObj;
		QString						m_nodeName;
		QBrush						m_textColor;


};

class SceneGraphNodeTreeItem : public SceneGraphNodeTreeItemBase {


	public:
		SceneGraphNodeTreeItem(PLScene::SceneNode *nodeObj, QObject *parent = nullptr) : SceneGraphNodeTreeItemBase(parent),
			m_nodeObj(nodeObj)
		{
			if (m_nodeObj->IsContainer()) {
				PLScene::SceneContainer *container = (PLScene::SceneContainer*)m_nodeObj;
				for (PLCore::uint32 i=0; i<container->GetNumOfElements(); i++) {
					PLScene::SceneNode *node = container->GetByIndex(i);
					new SceneGraphNodeTreeItem(node, this);
				}
			}

			for(PLCore::uint32 i=0; i<m_nodeObj->GetNumOfModifiers(); i++) {
				PLScene::SceneNodeModifier *node = m_nodeObj->GetModifier("", i);
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
			bool bRet = cImage.Load(imageName);
			QImage img;

			if (bRet) {
				PLGraphics::ImageBuffer *buf = cImage.GetBuffer();
				if (buf->HasCompressedData())
					buf->Decompress();

				if (buf->HasData()) {
					const PLCore::uint8 *data = buf->GetData();
					QImage img1((const uchar*)data, buf->GetSize().width, buf->GetSize().height,QImage::Format_ARGB32);
					return img1.scaled(24,24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
				}
			}
			return img;
		}

		virtual QVariant data(const int column, const int role)
		{
			if (role == Qt::DecorationRole)
				return m_Icon;

			if (role != Qt::DisplayRole)
				return QVariant();

			if (column == 0)
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
		PLScene::SceneNode	*m_nodeObj;
		QPixmap				 m_Icon;


};

SceneGraphTreeModel::SceneGraphTreeModel(QObject *parent) : TreeModelBase(new SceneGraphHeaderTreeItem, parent)
{
}

void SceneGraphTreeModel::SetStartNode(PLScene::SceneNode *nodeObj)
{
	beginResetModel();
	const QObjectList &childs = GetRootItem()->children();
	qDeleteAll(childs.begin(), childs.end());

	// [TODO]
	//m_MeshObj = meshObj;

	if (nodeObj)
		new SceneGraphNodeTreeItem(nodeObj, GetRootItem());
	endResetModel();
}

PLScene::SceneNode *SceneGraphTreeModel::GetSceneNodeFromIndex(QModelIndex &index)
{
	SceneGraphNodeTreeItemBase *treeItem = GetSceneTreeItemFromIndex(index);
	return (treeItem && treeItem->IsSceneNode()) ? (PLScene::SceneNode*)treeItem->GetObject() : nullptr;
}

SceneGraphNodeTreeItemBase *SceneGraphTreeModel::GetSceneTreeItemFromIndex(QModelIndex &index)
{
	return (!index.isValid() || index.model() != this) ? nullptr : (SceneGraphNodeTreeItemBase*)GetTreeItemFromIndex(index);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
