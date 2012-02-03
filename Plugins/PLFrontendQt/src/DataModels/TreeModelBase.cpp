/*********************************************************\
 *  File: TreeModelBase.cpp                              *
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
#include "PLFrontendQt/DataModels/TreeItemBase.h"
#include "PLFrontendQt/DataModels/TreeModelBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


TreeModelBase::TreeModelBase(TreeItemBase *rootItem, QObject *parent) : QAbstractItemModel(parent),
	m_rootItem(rootItem)
{
}

TreeModelBase::~TreeModelBase()
{
	delete m_rootItem;
}

QModelIndex TreeModelBase::index(int row, int column, const QModelIndex &parent) const
{
	// Check if row, column and parent represents an valid item in the model
	// if no return an invalid index
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	TreeItemBase *parentItem = GetTreeItemFromIndex(parent);

	// Get child item
	TreeItemBase *childItem = static_cast<TreeItemBase*>(parentItem->children()[row]);

	// Create an model index with row, column and childItem if child item exists
	// otherwise return an invalid model index
	return childItem ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex TreeModelBase::parent(const QModelIndex &index) const
{
	// Check if given index is valid
	if (!index.isValid())
		return QModelIndex();

	// Get child item from model index
	TreeItemBase *childItem = static_cast<TreeItemBase*>(index.internalPointer());

	// Get parent item from child item
	TreeItemBase *parentItem = static_cast<TreeItemBase*>(childItem->parent());

	// Check if parent item equals the root item
	if (parentItem == m_rootItem)
		return QModelIndex();

	// Create model index for the parent, column is always 0 because in a tree model only the first column can have childs or an parent
	return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModelBase::rowCount(const QModelIndex &parent) const
{
	// Return child count as row count
	return (parent.column() > 0) ? 0 : GetTreeItemFromIndex(parent)->children().count();
}

int TreeModelBase::columnCount(const QModelIndex &parent) const
{
	// Ask tree item for its column count
	return GetTreeItemFromIndex(parent)->columnCount();
}

QVariant TreeModelBase::data(const QModelIndex &index, int role) const
{
	// Return invalid QVariant when index not valid
	if (!index.isValid())
		return QVariant();

	// Get tree item from model index
	TreeItemBase *item = static_cast<TreeItemBase*>(index.internalPointer());

	int column = index.column();
	// Ask tree item for the data for the given column and role
	return item->data(column, role);
}

QVariant TreeModelBase::headerData(int section, Qt::Orientation orientation, int role) const
{
	// Call the default impl if the role is not the display role or the orientation is not horizontal
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return QAbstractItemModel::headerData(section, orientation, role);

	// Get data from the root item for the display role and column (section == column when orientation == horizontal)
	return m_rootItem->data(section, role);
}

Qt::ItemFlags TreeModelBase::flags(const QModelIndex &index) const
{
	// Check index and return only ItemIsEnabled as flag if not valid
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	// Get tree item from index
	TreeItemBase *item = static_cast<TreeItemBase*>(index.internalPointer());

	// Ask tree item for its flags for the given column
	return item->flags(index.column());
}

bool TreeModelBase::setData(const QModelIndex &index, const QVariant &value, int role)
{
	// Check if index is valid
	if (index.isValid()) {
		// Get tree item from index
		TreeItemBase *item = static_cast<TreeItemBase*>(index.internalPointer());
		if (item) {
			// Ask item to set data for the given role and value
			bool bRet = item->setData(index.column(), value, role);

			// Check if setting the data was successful and emit dataChanged signal to notify Views
			if (bRet)
				emit dataChanged(index, index);

			return bRet;
		}
	}
	return false;
}

/**
*  @brief
*    Returns the model index of the given item
*/
QModelIndex TreeModelBase::GetIndexForTreeItem(TreeItemBase *item) const
{
	if (item && item->parent()) {
        QPair<int, int> pos = item->position();
        return createIndex(pos.first, pos.second, item);
	}
    return QModelIndex();
}

TreeItemBase *TreeModelBase::GetTreeItemFromIndex(const QModelIndex &parent) const
{
	if (parent.isValid()) {
		// Get tree item from parent index as parent item
		return static_cast<TreeItemBase*>(parent.internalPointer());
	} else {
		// Parent index is not valid -> return root item as parent
		return m_rootItem;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
