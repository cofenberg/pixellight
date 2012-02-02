/*********************************************************\
 *  File: TreeSortAndFilterProxyModel.cpp                *
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
#include <QtCore/QStringList>
#include <PLCore/Container/List.h>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Module.h>
#include <PLCore/Base/ClassManager.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/TreeSortAndFilterProxyModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
TreeSortAndFilterProxyModel::TreeSortAndFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

void TreeSortAndFilterProxyModel::setFilterString(const QString &filters)
{
	setFilterWildcard(filters);
}

//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
bool TreeSortAndFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const 
{
	if (filterAcceptsRowItself(source_row, source_parent))
		return true;

// 		//accept if any of the parents is accepted on it's own merits
// 		QModelIndex parent = source_parent;
// 		while (parent.isValid()) {
// 			if (filterAcceptsRowItself(parent.row(), parent.parent()))
// 				return true;
// 			parent = parent.parent();
// 		}

	//accept if any of the children is accepted on it's own merits
	if (hasAcceptedChildren(source_row, source_parent)) {
		return true;
	}

	return false;
}

bool TreeSortAndFilterProxyModel::filterAcceptsRowItself(int source_row, const QModelIndex &source_parent) const
{
	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}
bool TreeSortAndFilterProxyModel::hasAcceptedChildren(int source_row, const QModelIndex &source_parent) const
{
	QModelIndex item = sourceModel()->index(source_row,0,source_parent);
	if (!item.isValid()) {
		return false;
	}

	//check if there are children
	int childCount = item.model()->rowCount(item);
	if (childCount == 0)
		return false;

	for (int i = 0; i < childCount; ++i) {
		if (filterAcceptsRowItself(i, item))
			return true;
		//recursive call
		if (hasAcceptedChildren(i, item))
			return true;
	}

	return false;
}

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
