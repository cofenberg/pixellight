/*********************************************************\
 *  File: TreeSortAndFilterProxyModel.cpp                *
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
