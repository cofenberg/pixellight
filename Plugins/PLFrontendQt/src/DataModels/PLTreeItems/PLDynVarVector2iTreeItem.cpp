/*********************************************************\
 *  File: PLDynVarVector2iTreeItem.cpp                   *
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
#include <PLMath/Vector2i.h>
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector2iTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


PLDynVarVector2iTreeItem::PLDynVarVector2iTreeItem(PLCore::DynVar *dynVar, TreeItemBase *parent) : PLDynVarStringTreeItem(dynVar, PLDynVarTreeItemTypes::Vector2i, parent)
{
	RemoveFlags(1,  Qt::ItemIsEditable);
	if (m_dynVar && m_dynVar->GetTypeID() == PLCore::Type<PLMath::Vector2i>::TypeID) {
		new Vector2iXValueTreeItem(this, this);
		new Vector2iYValueTreeItem(this, this);
	}
}

QVariant PLDynVarVector2iTreeItem::data(const int column, const int role)
{
	UpdateData();
	return PLDynVarStringTreeItem::data(column, role);
}

void PLDynVarVector2iTreeItem::UpdateData()
{
	m_Vector2i.FromString(m_dynVar->GetString());
}

void PLDynVarVector2iTreeItem::UpdateDataToVar()
{
	m_dynVar->SetString(m_Vector2i.ToString());
}

PLDynVarVector2iTreeItem::Vector2iValueBaseTreeItem::Vector2iValueBaseTreeItem(const QString &name, TreeItemBase *parent, PLDynVarVector2iTreeItem *parentItem) : TreeItemBase(2, parent),
	m_Name(name),
	m_parentItem(parentItem)
{
	SetFlags(1, Qt::ItemIsEditable);
}

QVariant PLDynVarVector2iTreeItem::Vector2iValueBaseTreeItem::data(const int column, const int role)
{
	// Don't show tooltip for Vector sub Items in column 0
	if (!m_parentItem->IsInStandardRole(role) || (role == Qt::ToolTipRole && column == 0))
		return QVariant();

	if(m_parentItem == nullptr)
		return QVariant();

	if (column == 0) {
		return m_Name;
	} else if (column == 1) {
		return (double)GetVectorData(m_parentItem->m_Vector2i);
	}

	return QVariant();
}

bool PLDynVarVector2iTreeItem::Vector2iValueBaseTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::EditRole || column != 1)
		return false;

	int iloatVal = value.value<int>();
	SetVectorData(m_parentItem->m_Vector2i, iloatVal);
	m_parentItem->UpdateDataToVar();
	return true;
}

PLDynVarVector2iTreeItem::Vector2iXValueTreeItem::Vector2iXValueTreeItem(TreeItemBase* parent, PLFrontendQt::DataModels::PLDynVarVector2iTreeItem* parentItem) : Vector2iValueBaseTreeItem("X", parent, parentItem)
{
}

int PLDynVarVector2iTreeItem::Vector2iXValueTreeItem::GetVectorData(const PLMath::Vector2i &vector)
{
	return vector.x;
}

void PLDynVarVector2iTreeItem::Vector2iXValueTreeItem::SetVectorData(PLMath::Vector2i &vector, int newValue)
{
	vector.SetX(newValue);
}

PLDynVarVector2iTreeItem::Vector2iYValueTreeItem::Vector2iYValueTreeItem(TreeItemBase* parent, PLFrontendQt::DataModels::PLDynVarVector2iTreeItem* parentItem) : Vector2iValueBaseTreeItem("Y", parent, parentItem)
{
}

int PLDynVarVector2iTreeItem::Vector2iYValueTreeItem::GetVectorData(const PLMath::Vector2i& vector)
{
	return vector.y;
}

void PLDynVarVector2iTreeItem::Vector2iYValueTreeItem::SetVectorData(PLMath::Vector2i& vector, int newValue)
{
	vector.SetY(newValue);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
