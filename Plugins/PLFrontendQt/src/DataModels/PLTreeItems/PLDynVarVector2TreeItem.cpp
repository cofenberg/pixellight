/*********************************************************\
 *  File: PLDynVarVector2TreeItem.cpp                    *
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
#include <PLMath/Vector2.h>
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector2TreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


PLDynVarVector2TreeItem::PLDynVarVector2TreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, PLDynVarTreeItemTypes::Vector2, parent)
{
	RemoveFlags(1,  Qt::ItemIsEditable);
	if (m_dynVar && m_dynVar->GetTypeID() == PLCore::Type<PLMath::Vector2>::TypeID) {
		new Vector2XValueTreeItem(this, this);
		new Vector2YValueTreeItem(this, this);
	}
}

QVariant PLDynVarVector2TreeItem::data(const int column, const int role)
{
	UpdateData();
	return PLDynVarStringTreeItem::data(column, role);
}

void PLDynVarVector2TreeItem::UpdateData()
{
	m_Vector2.FromString(m_dynVar->GetString());
}

void PLDynVarVector2TreeItem::UpdateDataToVar()
{
	m_dynVar->SetString(m_Vector2.ToString());
}

PLDynVarVector2TreeItem::Vector2ValueBaseTreeItem::Vector2ValueBaseTreeItem(const QString &name, QObject *parent, PLDynVarVector2TreeItem *parentItem) : TreeItemBase(2, parent),
	m_Name(name),
	m_parentItem(parentItem)
{
	SetFlags(1, Qt::ItemIsEditable);
}

QVariant PLDynVarVector2TreeItem::Vector2ValueBaseTreeItem::data(const int column, const int role)
{
// Don't show tooltip for Vector sub Items in column 0
	if (!m_parentItem->IsInStandardRole(role) || (role == Qt::ToolTipRole && column == 0))
		return QVariant();

	if(m_parentItem == nullptr)
		return QVariant();

	if (column == 0) {
		return m_Name;
	} else if (column == 1) {
		return (double)GetVectorData(m_parentItem->m_Vector2);
	}

	return QVariant();
}

bool PLDynVarVector2TreeItem::Vector2ValueBaseTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::EditRole || column != 1)
		return false;

	float floatVal = value.value<float>();
	SetVectorData(m_parentItem->m_Vector2, floatVal);
	m_parentItem->UpdateDataToVar();
	return true;
}

PLDynVarVector2TreeItem::Vector2XValueTreeItem::Vector2XValueTreeItem(QObject *parent, PLDynVarVector2TreeItem *parentItem) : Vector2ValueBaseTreeItem("X", parent, parentItem)
{
}

float PLDynVarVector2TreeItem::Vector2XValueTreeItem::GetVectorData(const PLMath::Vector2 &vector)
{
	return vector.x;
}

void PLDynVarVector2TreeItem::Vector2XValueTreeItem::SetVectorData(PLMath::Vector2 &vector, float newValue)
{
	vector.SetX(newValue);
}

PLDynVarVector2TreeItem::Vector2YValueTreeItem::Vector2YValueTreeItem(QObject *parent, PLDynVarVector2TreeItem *parentItem) : Vector2ValueBaseTreeItem("Y", parent, parentItem)
{
}

float PLDynVarVector2TreeItem::Vector2YValueTreeItem::GetVectorData(const PLMath::Vector2 &vector)
{
	return vector.y;
}

void PLDynVarVector2TreeItem::Vector2YValueTreeItem::SetVectorData(PLMath::Vector2 &vector, float newValue)
{
	vector.SetY(newValue);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
