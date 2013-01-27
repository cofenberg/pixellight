/*********************************************************\
 *  File: SceneRendererDataModel.cpp                     *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Module.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLFrontendQt/DataModels/HeaderTreeItem.h"
#include "PLFrontendQt/DataModels/ModelIndexMimeData.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererPassTreeItem.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererDataModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {
namespace DataModels {
namespace SceneRendererDataModel {


SceneRendererDataModel::SceneRendererDataModel(QObject *parent): TreeModelBase(new HeaderTreeItem),
	m_pSceneRenderer(nullptr)
{
	QStringList headerItems;
	headerItems << "Node Name" << "Value";

	HeaderTreeItem *header = static_cast<HeaderTreeItem*>(GetRootItem());
	header->setHeaderItems(headerItems);
}

SceneRenderer *SceneRendererDataModel::GetSceneRenderer() const
{
	return m_pSceneRenderer;
}

void SceneRendererDataModel::SetSceneRenderer(SceneRenderer *nodeObj)
{
	if (m_pSceneRenderer != nodeObj) {
		m_pSceneRenderer = nodeObj;

		beginResetModel();
		GetRootItem()->clearChildren();
		
		if (m_pSceneRenderer) {
			uint32 count = m_pSceneRenderer->GetNumOfElements();

			// Loop through all scene renderer passes
			for (uint32 nPass=0; nPass< count; nPass++) {
				// Get the current scene renderer pass
				SceneRendererPass *pSceneRendererPass = m_pSceneRenderer->GetByIndex(nPass);
				if (pSceneRendererPass)
					(new SceneRendererPassTreeItem(pSceneRendererPass, GetRootItem()));
			}
		}

		endResetModel();
	}
}

Qt::ItemFlags SceneRendererDataModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags itemFlags = TreeModelBase::flags(index);
	if(!index.isValid())
		itemFlags |= Qt::ItemIsDropEnabled;
	return itemFlags;
}

bool SceneRendererDataModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent)
{
	Q_UNUSED(column);

	if (action == Qt::IgnoreAction)
		return true;
	
	if (action != Qt::MoveAction)
		return false;

	if (!data->hasFormat("application/x-pixellight.scenerendererpasses.list") || row == -1)
		return false;

	if (const ModelIndexMimeData *mmd = qobject_cast<const ModelIndexMimeData*>(data))
	{
		foreach (QModelIndex idx, mmd->indexes()) {
			// check if the index is from this model
			if (idx.model() != this)
				continue;

			// We support only single selection so we move only one row at once
			if(!beginMoveRows(idx.parent(), idx.row(), idx.row(), parent, row))
				return false;

			int rowToMove = idx.row();
			// We have to decrement the target child index by one, when the item should be moved down the internal child list (child index gets greater).
			// Background:
			// We have a list with 4 items (indexes: 0, 1, 2 , 3). The user drags the item at index 1 and want it to be between the items at index 2 and 3 (-> item at index 2 moves to index 1 and the dragged item moves to index 2).
			// In this case the destinationRow param of this function has the value 3. From the View-class point of view the item should be positioned after the item at index 2 and so the destinationRow value is 3.
			// Because the View-class doesn't distinguishes between an copy or move operation when calling this function. So the view fills the destinationRow param with a value which is correct when doing an copy operation
			// But when the user drags e.g. the item at index 2 to be between index 0 and 1 then the destinationRow param value is correct for the internal move operation because the item at index 1 moves to index 2 and the dragged item moves to index 1 (moves upwards and not downwards)
			int rowTarget = row > rowToMove ? row -1 : row;

			TreeItemBase *parentItem = GetTreeItemFromIndex(idx.parent());
			
			this->m_pSceneRenderer->MoveElement(rowToMove, rowTarget);
			parentItem->MoveChild(rowToMove, rowTarget);

			endMoveRows();
		}

		return true;
	}
	return false;
}

QMimeData *SceneRendererDataModel::mimeData(const QModelIndexList &indexes) const
{
	return new ModelIndexMimeData(indexes, "application/x-pixellight.scenerendererpasses.list");
}

QStringList SceneRendererDataModel::mimeTypes() const
{
	QStringList types;
    types << "application/x-pixellight.scenerendererpasses.list";
    return types;
}

Qt::DropActions SceneRendererDataModel::supportedDropActions() const
{
	// We only support move actions
	return Qt::MoveAction;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt
