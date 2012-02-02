/*********************************************************\
 *  File: TreeItemBase.cpp                               *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


TreeItemBase::TreeItemBase(TreeItemBase *parent) : m_columnCount(0), m_pParent(parent)
{
	if (m_pParent)
		m_pParent->AddChild(this);
}

TreeItemBase::TreeItemBase(int columnCount, TreeItemBase *parent) : m_columnCount(columnCount), m_pParent(parent)
{
	if (m_pParent)
		m_pParent->AddChild(this);
	
	for (int i=0; i<columnCount; i++)
		m_flagsMap.insert(i, Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

TreeItemBase::~TreeItemBase()
{
	if (m_pParent)
		m_pParent->RemoveChild(this, false);
	clearChildren();
}

int TreeItemBase::columnCount() const
{
	return m_columnCount;
}

int TreeItemBase::row() const
{
	// [TODO] add a member var to hold this information, which gets updated when the items got moved within the model
	return parent()->children().indexOf(const_cast<TreeItemBase*>(this));
}

Qt::ItemFlags TreeItemBase::flags(const int column) const
{
	return m_flagsMap.contains(column) ? m_flagsMap[column] : Qt::ItemIsEnabled;
}

/**
*  @brief
*    Adds an child to this tree node
*/
void TreeItemBase::AddChild(TreeItemBase* pChild)
{
	if(!pChild || m_cChildren.contains(pChild))
		return;
	pChild->ChangeParent(this, true);
	m_cChildren.append(pChild);
}

/**
*  @brief
*    Insert an child to this tree node
*/
void TreeItemBase::InsertChild(TreeItemBase* pChild, int nPosition)
{
	if(!pChild || m_cChildren.contains(pChild))
		return;
	if (nPosition < 0)
		nPosition = 0;
	if (nPosition > m_cChildren.size())
		nPosition = m_cChildren.size();
	
	pChild->ChangeParent(this, true);
	m_cChildren.insert(nPosition, pChild);
}

/**
*  @brief
*    Remove an child from this tree node
*/
void TreeItemBase::RemoveChild(TreeItemBase* pChild, bool bDestroy)
{
	int cIdx = m_cChildren.indexOf(pChild);
	if (cIdx < 0)
		return;
	m_cChildren.removeAt(cIdx);
	if(bDestroy)
		delete pChild;
}

/**
*  @brief
*   Returns a list of child objects.
*/
const QList<TreeItemBase*>& TreeItemBase::children() const
{
	return m_cChildren;
}

/**
*  @brief
*   Removes all child items from the internal list
*/
void TreeItemBase::clearChildren()
{
	if (m_cChildren.count() == 0)
		return;

	while(!m_cChildren.isEmpty())
	{
		TreeItemBase *child = m_cChildren.takeFirst();
		child->m_pParent = nullptr;
		delete child;
	}
}

/**
*  @brief
*   Returns the parent item of this item
*/
TreeItemBase* TreeItemBase::parent() const
{
	return m_pParent;
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

void TreeItemBase::SetColumnCount(const int columnCount)
{
	m_columnCount = columnCount;
}

void TreeItemBase::ChangeParent(PLFrontendQt::DataModels::TreeItemBase* pNewParent, bool bNoAdd)
{
	if (m_pParent == pNewParent)
		return;
	
	if (m_pParent)
		m_pParent->RemoveChild(this, false);
	m_pParent = pNewParent;
	if(m_pParent && !bNoAdd)
		m_pParent->AddChild(this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
