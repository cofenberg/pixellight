/*********************************************************\
 *  File: TreeItemBase.cpp                               *
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
#include "PLFrontendQt/DataModels/TreeItemBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


TreeItemBase::TreeItemBase(QObject *parent) : QObject(parent)
{
}

TreeItemBase::TreeItemBase(int columnCount, QObject *parent) : QObject(parent), m_columnCount(columnCount)
{
	setParent(parent);
	for (int i=0; i<columnCount; i++)
		m_flagsMap.insert(i, Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

int TreeItemBase::columnCount() const
{
	return m_columnCount;
}

int TreeItemBase::row() const
{
	return parent()->children().indexOf(const_cast<TreeItemBase*>(this));
}

Qt::ItemFlags TreeItemBase::flags(const int column) const
{
	return m_flagsMap.contains(column) ? m_flagsMap[column] : Qt::ItemIsEnabled;
}

void TreeItemBase::SetFlags(const int column, const Qt::ItemFlags flags)
{
	if (m_flagsMap.contains(column))
		m_flagsMap[column] |= flags;
	else
		m_flagsMap[column] = flags;
}

void TreeItemBase::RemoveFlags(const int column, const Qt::ItemFlags flags)
{
	if (m_flagsMap.contains(column))
		m_flagsMap[column] &= ~flags;
	else
		m_flagsMap[column] = Qt::NoItemFlags;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
