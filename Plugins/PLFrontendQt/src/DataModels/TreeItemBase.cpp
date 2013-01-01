/*********************************************************\
 *  File: TreeItemBase.cpp                               *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
*    move an child within the child list
*/
void TreeItemBase::MoveChild(int nFromIndex, int nToIndex)
{
	m_cChildren.move(nFromIndex, nToIndex);
}

/**
*  @brief
*    Returns the index of the child
*/
int TreeItemBase::GetChildIndex(TreeItemBase* pChild) const
{
	if (!pChild)
		return -1;
	return m_cChildren.indexOf(pChild);
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

/**
*  @brief
*   Returns the position of this item
*/
QPair<int, int> TreeItemBase::position()
{
    if (const TreeItemBase *par = parent()) {
		// idx = row in the tree
        int idx = par->GetChildIndex(this);
        if (idx == -1)
            return QPair<int, int>(-1, -1);
		// return position (row, column), column is always 0 because there can only be one item per row
        return QPair<int, int>(idx , 0);
    }
    return QPair<int, int>(-1, -1);
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
