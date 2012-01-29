/*********************************************************\
 *  File: PLDynVarVector3iTreeItem.cpp                   *
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
#include <PLMath/Vector3i.h>
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector3iTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


PLDynVarVector3iTreeItem::PLDynVarVector3iTreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, PLDynVarTreeItemTypes::Vector3i, parent)
{
	RemoveFlags(1,  Qt::ItemIsEditable);
	if (m_dynVar && m_dynVar->GetTypeID() == PLCore::Type<PLMath::Vector3i>::TypeID) {
		new Vector3iXValueTreeItem(this, this);
		new Vector3iYValueTreeItem(this, this);
		new Vector3iZValueTreeItem(this, this);
	}
}

QVariant PLDynVarVector3iTreeItem::data(const int column, const int role)
{
	UpdateData();
	return PLDynVarStringTreeItem::data(column, role);
}

void PLDynVarVector3iTreeItem::UpdateData()
{
	m_Vector3i.FromString(m_dynVar->GetString());
}

void PLDynVarVector3iTreeItem::UpdateDataToVar()
{
	m_dynVar->SetString(m_Vector3i.ToString());
}

PLDynVarVector3iTreeItem::Vector3iValueBaseTreeItem::Vector3iValueBaseTreeItem(const QString &name, QObject *parent, PLDynVarVector3iTreeItem *parentItem) : TreeItemBase(2, parent),
	m_Name(name),
	m_parentItem(parentItem)
{
	SetFlags(1, Qt::ItemIsEditable);
}

QVariant PLDynVarVector3iTreeItem::Vector3iValueBaseTreeItem::data(const int column, const int role)
{
	// Don't show tooltip for Vector sub Items in column 0
	if (!m_parentItem->IsInStandardRole(role) || (role == Qt::ToolTipRole && column == 0))
		return QVariant();

	if(m_parentItem == nullptr)
		return QVariant();

	if (column == 0) {
		return m_Name;
	} else if (column == 1) {
		return (double)GetVectorData(m_parentItem->m_Vector3i);
	}

	return QVariant();
}

bool PLDynVarVector3iTreeItem::Vector3iValueBaseTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::EditRole || column != 1)
		return false;

	float floatVal = value.value<float>();
	SetVectorData(m_parentItem->m_Vector3i, floatVal);
	m_parentItem->UpdateDataToVar();
	return true;
}

PLDynVarVector3iTreeItem::Vector3iXValueTreeItem::Vector3iXValueTreeItem(QObject *parent, PLDynVarVector3iTreeItem *parentItem) : Vector3iValueBaseTreeItem("X", parent, parentItem)
{
}

int PLDynVarVector3iTreeItem::Vector3iXValueTreeItem::GetVectorData(const PLMath::Vector3i &vector)
{
	return vector.x;
}

void PLDynVarVector3iTreeItem::Vector3iXValueTreeItem::SetVectorData(PLMath::Vector3i &vector, int newValue)
{
	vector.SetX(newValue);
}

PLDynVarVector3iTreeItem::Vector3iYValueTreeItem::Vector3iYValueTreeItem(QObject *parent, PLDynVarVector3iTreeItem *parentItem) : Vector3iValueBaseTreeItem("Y", parent, parentItem)
{
}

int PLDynVarVector3iTreeItem::Vector3iYValueTreeItem::GetVectorData(const PLMath::Vector3i &vector)
{
	return vector.y;
}

void PLDynVarVector3iTreeItem::Vector3iYValueTreeItem::SetVectorData(PLMath::Vector3i &vector, int newValue)
{
	vector.SetY(newValue);
}

PLDynVarVector3iTreeItem::Vector3iZValueTreeItem::Vector3iZValueTreeItem(QObject *parent, PLDynVarVector3iTreeItem *parentItem) : Vector3iValueBaseTreeItem("Z", parent, parentItem)
{
}

int PLDynVarVector3iTreeItem::Vector3iZValueTreeItem::GetVectorData(const PLMath::Vector3i &vector)
{
	return vector.z;
}

void PLDynVarVector3iTreeItem::Vector3iZValueTreeItem::SetVectorData(PLMath::Vector3i &vector, int newValue)
{
	vector.SetZ(newValue);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
