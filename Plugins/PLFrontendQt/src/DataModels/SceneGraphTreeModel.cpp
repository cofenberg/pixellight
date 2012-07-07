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
#include <QtCore/QDebug>
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
#include "PLFrontendQt/DataModels/HeaderTreeItem.h"
#include "PLFrontendQt/DataModels/SceneGraphNodeTreeItemBase.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DataModels/Helper.h"
#include "PLFrontendQt/DataModels/ModelIndexMimeData.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


class SceneGraphNodeModifierTreeItem : public SceneGraphNodeTreeItemBase {


	public:
		SceneGraphNodeModifierTreeItem(SceneGraphTreeModel &cModel, PLScene::SceneNodeModifier *nodeObj, TreeItemBase *parent = nullptr) : SceneGraphNodeTreeItemBase(cModel, parent),
			m_nodeObj(nodeObj),
			m_nodeName(nodeObj ? QtStringAdapter::PLToQt(m_nodeObj->GetClass()->GetName()) : "null modifier"),
			m_nodeClassName(nodeObj ? QtStringAdapter::PLToQt(m_nodeObj->GetClass()->GetClassName()) : "null class"),
			m_textColor(Qt::cyan),
			EventHandlerOnDestroyed(&SceneGraphNodeModifierTreeItem::OnDestroyed, this)
		{
			// Connect event handler
			m_nodeObj->SignalDestroyed.Connect(EventHandlerOnDestroyed);
		}
		
		virtual ~SceneGraphNodeModifierTreeItem()
		{
			if(m_nodeObj)
				m_nodeObj->SignalDestroyed.Disconnect(EventHandlerOnDestroyed);
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column == 0) {
				if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
					return m_nodeName;
				else if(role == SceneGraphTreeModel::ClassNameRole) {
					return m_nodeClassName;
				}
				else if(role == SceneGraphTreeModel::InternalObjectPointerRole) {
					return VPtr<PLScene::SceneNodeModifier>::asQVariant(m_nodeObj);
				}
			}

			return QVariant();
		}

		bool IsSceneNode()
		{
			return false;
		}
		
		bool IsSceneContainer()
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
		/**
		*  @brief
		*    Called when the scene node modifier assigned with this item was destroyed
		*/
		void OnDestroyed()
		{
			// Argh! Mayday! We lost our scene node modifier!
			m_nodeObj = nullptr;

			const QModelIndex cIndex = index();
			m_cModel.removeRow(cIndex.row(), cIndex.parent());
		}

	private:
		PLScene::SceneNodeModifier	*m_nodeObj;	// Can be a null pointer
		QString						 m_nodeName;
		QString						 m_nodeClassName;
		QBrush						 m_textColor;
		PLCore::EventHandler<>		 EventHandlerOnDestroyed;


};

void CreateSceneGraphItemsFromContainer(PLFrontendQt::DataModels::SceneGraphTreeModel& cModel, PLScene::SceneContainer* pContainer, TreeItemBase* parent);

class SceneGraphNodeTreeItem : public SceneGraphNodeTreeItemBase {


	public:
		SceneGraphNodeTreeItem(SceneGraphTreeModel &cModel, PLScene::SceneNode *nodeObj, TreeItemBase *parent = nullptr) : SceneGraphNodeTreeItemBase(cModel, parent),
			m_nodeObj(nodeObj),
			EventHandlerOnDestroy(&SceneGraphNodeTreeItem::OnDestroy, this)
		{
			// Connect event handler
			m_nodeObj->SignalDestroy.Connect(EventHandlerOnDestroy);
			
			SetFlags(0, Qt::ItemIsDragEnabled);
			
			PLCore::String sName(nodeObj->GetName());

			if (m_nodeObj->IsContainer()) {
				PLScene::SceneContainer *container = (PLScene::SceneContainer*)m_nodeObj;
				SetFlags(0, Qt::ItemIsDropEnabled);
				CreateSceneGraphItemsFromContainer(cModel, container, this);
			}

			for(PLCore::uint32 i=0; i<m_nodeObj->GetNumOfModifiers(); i++) {
				// Get the current scene node modifier
				PLScene::SceneNodeModifier *node = m_nodeObj->GetModifier("", i);

				// Add this scene node modifier as item, but only if it has no "Automatic"-flag set
				// -> "This scene node modifier was created automatically during runtime and should
				//     not be saved with the scene. Such scene nodes modifiers may also be hidden for
				//     instance within a scene editor."
				if ((node->GetFlags() & PLScene::SceneNodeModifier::Automatic))
					continue;
				
				AddChild(new SceneGraphNodeModifierTreeItem(cModel, node, this));
			}

			GetIconFromSceneNode();
		}
		
		virtual ~SceneGraphNodeTreeItem()
		{
			if(m_nodeObj)
				m_nodeObj->SignalDestroy.Disconnect(EventHandlerOnDestroy);
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
			
			if (m_nodeObj == nullptr)
				return QVariant();

			if (column == 0 && role == Qt::DisplayRole)
				return QtStringAdapter::PLToQt(m_nodeObj->GetName());
			else if(column == 0 && role == SceneGraphTreeModel::ClassNameRole) {
				return QtStringAdapter::PLToQt(m_nodeObj->GetClass()->GetClassName());
			}else if(role == SceneGraphTreeModel::InternalObjectPointerRole) {
				return VPtr<PLScene::SceneNode>::asQVariant(m_nodeObj);
			}

			return QVariant();
		}

		bool IsSceneNode()
		{
			return true;
		}
		
		bool IsSceneContainer()
		{
			if (m_nodeObj)
				return m_nodeObj->IsContainer();
			return false;
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
			qDebug()<<"SceneNode destroyed!!";
			// Argh! Mayday! We lost our scene node!
			m_nodeObj = nullptr;
			const QModelIndex cIndex = index();
			m_cModel.removeRow(cIndex.row(), cIndex.parent());
		}

	private:
		PLScene::SceneNode	   *m_nodeObj;	// Can be a null pointer
		QPixmap				    m_Icon;
		PLCore::EventHandler<>  EventHandlerOnDestroy;


};

void CreateSceneGraphItemsFromContainer(PLFrontendQt::DataModels::SceneGraphTreeModel& cModel, PLScene::SceneContainer* pContainer, PLFrontendQt::DataModels::TreeItemBase* parent)
{
	for (PLCore::uint32 i=0; i<pContainer->GetNumOfElements(); ++i) {
		// Get the current scene node
		PLScene::SceneNode *node = pContainer->GetByIndex(i);

		// Add this scene node as item, but only if it has no "Automatic"-flag set
		// -> "This scene node was created automatically during runtime and should
		//     not be saved with the scene. Such scene nodes may also be hidden for
		//     instance within a scene editor."
		if ((node->GetFlags() & PLScene::SceneNode::Automatic))
			continue;
		
		parent->AddChild(new SceneGraphNodeTreeItem(cModel, node, parent));
	}
}

SceneGraphTreeModel::SceneGraphTreeModel(QObject *parent) : TreeModelBase(new HeaderTreeItem, parent), m_bInMoveOperation(false)
{
	QStringList headerItems;
	headerItems << "Node Name";

	HeaderTreeItem *header = static_cast<HeaderTreeItem*>(GetRootItem());
	header->setHeaderItems(headerItems);
}

void SceneGraphTreeModel::SetStartNode(PLScene::SceneNode* nodeObj, bool hideStartNode)
{
	beginResetModel();
	TreeItemBase *pRootItem = GetRootItem();
	pRootItem->clearChildren();

	if (nodeObj) {
		if (!hideStartNode || !nodeObj->IsContainer()) {
			pRootItem->AddChild(new SceneGraphNodeTreeItem(*this,nodeObj));
			QModelIndex tt = index(0,0);
			QString str;
			if (tt.isValid())
				str = tt.data().toString();
		}
		else
			CreateSceneGraphItemsFromContainer(*this, static_cast<PLScene::SceneContainer*>(nodeObj), pRootItem);
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

QModelIndex SceneGraphTreeModel::GetModelIndexForSceneNode(PLScene::SceneNode *nodeObj)
{
	if(nodeObj) {
		// Search through the complete model data to find the SceneNode
		// The memory address is used for comparison. Which can be retrieved via the ItemDataRole InternalObjectPointerRole 
		// The search stops when the first item with the same memory address was found.
		QModelIndexList items = this->match(index(0,0), SceneGraphTreeModel::InternalObjectPointerRole, VPtr<PLScene::SceneNode>::asQVariant(nodeObj), 1, Qt::MatchRecursive);
		// return the model index if we found something
		if(items.count() == 1)
			return items[0];
	}
	
	return QModelIndex();
}

QModelIndex SceneGraphTreeModel::GetModelIndexForSceneNodeModifier(PLScene::SceneNodeModifier *nodeObj)
{
	if(nodeObj) {
		// Search through the complete model data to find the SceneNodeModifier
		// The memory address is used for comparison. Which can be retrieved via the ItemDataRole InternalObjectPointerRole 
		// The search stops when the first item with the same memory address was found.
		QModelIndexList items = this->match(index(0,0), SceneGraphTreeModel::InternalObjectPointerRole, VPtr<PLScene::SceneNodeModifier>::asQVariant(nodeObj), 1, Qt::MatchRecursive);
		// return the model index if we found something
		if(items.count() == 1)
			return items[0];
	}
	
	return QModelIndex();
}

void SceneGraphTreeModel::AddSceneNode(PLScene::SceneContainer* pContainer, PLScene::SceneNode* pSceneNode, int nPosition)
{
	QModelIndex parentIdx = GetModelIndexForSceneNode(pContainer);
	// [TODO] handling items to the root SceneContainer (pContainer == nullptr)
	if (!parentIdx.isValid())
		return;
	
	SceneGraphNodeTreeItemBase *treeItem = GetSceneTreeItemFromIndex(parentIdx);
	
	int rowNumber = nPosition == -1 ?  treeItem->children().count() : nPosition;

	beginInsertRows(parentIdx, rowNumber, rowNumber);
	
	TreeItemBase *pChild = new SceneGraphNodeTreeItem(*this, pSceneNode);
	if(nPosition == -1)
		treeItem->AddChild(pChild);
	else
		treeItem->InsertChild(pChild, nPosition);
	
	endInsertRows();
}

void SceneGraphTreeModel::AddSceneNodeModifier(PLScene::SceneNode* pParentNode, PLScene::SceneNodeModifier* pSceneNodeModifier, int nPosition)
{
	QModelIndex parentIdx = GetModelIndexForSceneNode(pParentNode);
	if (!parentIdx.isValid())
		return;
	
	SceneGraphNodeTreeItemBase *treeItem = GetSceneTreeItemFromIndex(parentIdx);
	
	int rowNumber = nPosition == -1 ?  treeItem->children().count() : nPosition;

	beginInsertRows(parentIdx, rowNumber, rowNumber);
	
	TreeItemBase *pChild = new SceneGraphNodeModifierTreeItem(*this, pSceneNodeModifier);
	
	if(nPosition == -1)
		treeItem->AddChild(pChild);
	else
		treeItem->InsertChild(pChild, nPosition);
	
	endInsertRows();
}

bool SceneGraphTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int destinationRow, int column, const QModelIndex &parent)
{
	Q_UNUSED(column);
	
	if (action == Qt::IgnoreAction)
		return true;
	
	if (action != Qt::MoveAction)
		return false;
	
	if (!data->hasFormat("application/x-pixellight.scenenode.list"))
		return false;
	
	if (const ModelIndexMimeData *mmd = qobject_cast<const ModelIndexMimeData*>(data))
	{
		foreach (QModelIndex idx, mmd->indexes()) {
			// check if the index is from this model
			if (idx.model() != this)
				continue;

			SceneGraphNodeTreeItemBase *parentItem = GetSceneTreeItemFromIndex(parent);
			SceneGraphNodeTreeItemBase *item = GetSceneTreeItemFromIndex(idx);
			
			PLScene::SceneContainer *pSceneContainer = static_cast<PLScene::SceneContainer*>(parentItem->GetObject());
			PLScene::SceneNode *pSceneNode = static_cast<PLScene::SceneNode*>(item->GetObject());
			
			if (parent != idx.parent())
			{
				// We do a move operation to an different parent
				int rowTarget = destinationRow;
				int childCount =  parentItem->children().count();
				
				if (rowTarget >= childCount || rowTarget == -1)
				{
					// The item should be moved after the last item in the child list (this is also done when destinationRow = -1 => it's up to the model where to put the item)
					// Set rowTarget to childCount because we move the item after the last item in the child list and from the model/view point of view the new row is lasChildRowNumber + 1
					rowTarget = childCount;
				}
				
				// We support only single selection so we move only one row at once
				if(!beginMoveRows(idx.parent(), idx.row(), idx.row(), parent, rowTarget))
					return false;
				
				// Set that we are in a move operation see comment in removeRows() why
				m_bInMoveOperation = true;
				
				// Do the move in the underlaying data structure
				pSceneNode->SetContainer(*pSceneContainer);
				
				if (rowTarget >= childCount)
				{
					// when rowTarget equals childCount then we Append the child tree item (the child gets automatically removed from the old parent child list)
					parentItem->AddChild(item);
				}
				else
				{
					// Otherwise we insert the item at the specified location
					int nodeIdx = pSceneContainer->GetIndex(*pSceneNode);
					
					// We have to move the underlaying data item also to the new location, because SceneNode::SetContainer appends the item to the end of the new container
					if(nodeIdx != rowTarget)
						pSceneContainer->MoveElement(nodeIdx, rowTarget);
					
					// Insert the tree item to the new parent at the specified location (the child gets automatically removed from the old parent child list)
					parentItem->InsertChild(item, rowTarget);
				}
			}
			else
			{
				// We do a move operation within the same parent
				int rowToMove = idx.row();
				int rowTarget = destinationRow;
				int targetIdx = destinationRow;
				int childCount =  parentItem->children().count();
				
				if (rowTarget == -1)
				{
					// It is up to the model where the item should be placed
					// For this model the item gets placed om the end of the list.
					// Set the target index to childcount -1 otherwise the index is out of range 
					targetIdx = childCount - 1;
					// But set rowTarget to childcount because we move the item after the last item in the child list and from the model/view point of view the new row is lasChildRowNumber + 1
					rowTarget = childCount;
				}
				else if (targetIdx >= childCount) {
					// The item should be moved after the last item in the child list
					// Set the target index to childcount -1 otherwise the index is out of range 
					targetIdx = childCount - 1;
				}
				else if (rowTarget > rowToMove)
				{
					// We have to decrement the target child index by one, when the item should be moved down the internal child list (child index gets greater).
					// Background:
					// We have a list with 4 items (indexes: 0, 1, 2 , 3). The user drags the item at index 1 and want it to be between the items at index 2 and 3 (-> item at index 2 moves to index 1 and the dragged item moves to index 2).
					// In this case the destinationRow param of this function has the value 3. From the View-class point of view the item should be positioned after the item at index 2 and so the destinationRow value is 3.
					// Because the View-class doesn't distinguishes between an copy or move operation when calling this function. So the view fills the destinationRow param with a value which is correct when doing an copy operation
					// But when the user drags e.g. the item at index 2 to be between index 0 and 1 then the destinationRow param value is correct for the internal move operation because the item at index 1 moves to index 2 and the dragged item moves to index 1 (moves upwards and not downwards)
					targetIdx -= 1;
				}

				// [HACK][TODO] Currently, there's a different tree view item drag'n'drop behavior on Linux and Windows
				// -> Linux: If an item is marked to not allow drop onto it, the mouse cursor gets "X" and dropping is impossible (as expected in the first place)
				// -> Windows: If an item is marked to not allow drop onto it, the dropped item is inserted in top of or below the
				//             item we dropped our item onto. When debugging into Qt in order to understand the drag'n'drop behavior,
				//             the explanation for this behavior can be found within
				//             "QAbstractItemView::DropIndicatorPosition QAbstractItemViewPrivate::position(const QPoint &pos, const QRect &rect, const QModelIndex &index) const"
				//             When just looking at this Qt source code, it appears that this has nothing to do with the Windows operation
				//             system at all. No OS features are used. Interesting that the behavior under Linux is that different. Maybe
				//             we should also debug the drag'n'drop procedure under Linux to be able to find the one part were it starts to differ.
				//             I assume that there are some other relevant parts before "QAbstractItemViewPrivate::position()" is even called.
				// -> When searching for this issue in the Internet, it appears that there are also other people which have noticed the same thing
				// -> For now we have the following hack under Windows, if we don't do this, items will disappear regularly when doing drag'n'drop making is unusable :/
				#ifdef WIN32
					// Set that we are in a move operation see comment in removeRows() why
					m_bInMoveOperation = true;
				#endif

				// Check if we move the item to the same location within the child list
				// rowToMove equals the current list index of the item
				if (rowToMove == targetIdx)
					return false;

				// We support only single selection so we move only one row at once
				if(!beginMoveRows(idx.parent(), idx.row(), idx.row(), parent, rowTarget))
					return false;
				
				// Set that we are in a move operation see comment in removeRows() why
				m_bInMoveOperation = true;

				// Do the actual moving in the underlaying data structure
				pSceneContainer->MoveElement(rowToMove, targetIdx);
				// And move the child tree item to the new position. See the comment in removeRows() why we do this here
				parentItem->MoveChild(rowToMove, targetIdx);
			}
			
			endMoveRows();
			return true;
		}
	}
	return false;
}

QMimeData *SceneGraphTreeModel::mimeData(const QModelIndexList &indexes) const
{
	return new ModelIndexMimeData(indexes, "application/x-pixellight.scenenode.list");
}

QStringList SceneGraphTreeModel::mimeTypes() const
{
	QStringList types;
    types << "application/x-pixellight.scenenode.list";
    return types;
}

Qt::DropActions SceneGraphTreeModel::supportedDropActions() const
{
	// We only support move actions
	return Qt::MoveAction;
}

//[-------------------------------------------------------]
//[ Public virtual QAbstractItemModel functions           ]
//[-------------------------------------------------------]
bool SceneGraphTreeModel::removeRows(int startRow, int count, const QModelIndex& parent)
{
	// Check if we are currently in a move operation
	// Background:
	// When a view does an drag and drop move operation the view calls dropMimeData after this call the view calls removeRows and insertRows.
	// Normally dropMimeData should only be used to insert/move data in the underlaying data structure of the model.
	// But we doesn't do it that way we move also the tree item to the new location, because otherwise we had to destroy the old tree item (and all it's child items) and create a new one for the new location. So we must cancel the removeRows call when a move operation is done via drag and drop
	if (m_bInMoveOperation) {
		m_bInMoveOperation = false;
		return false;
	}
	

	if (!parent.isValid())
		return false;

	beginRemoveRows(parent, startRow, startRow+count-1);
	
	QModelIndex childIdx = index(startRow, 0, parent);
	// All tree items are created on the heap so calling delete is save
	SceneGraphNodeTreeItemBase* childItem = GetSceneTreeItemFromIndex(childIdx);
	SceneGraphNodeTreeItemBase* parentItem = GetSceneTreeItemFromIndex(parent);
	
	parentItem->RemoveChild(childItem);
	
	endRemoveRows();
	
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
