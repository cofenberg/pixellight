/*********************************************************\
 *  File: PLDynVarVector3TreeItem.cpp                    *
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
#include <PLMath/Vector3.h>
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector3TreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


PLDynVarVector3TreeItem::PLDynVarVector3TreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, parent)
{
	RemoveFlags(1,  Qt::ItemIsEditable);
	if (m_dynVar && m_dynVar->GetTypeID() == PLCore::Type<PLMath::Vector3>::TypeID) {
		new Vector3XValueTreeItem(this, this);
		new Vector3YValueTreeItem(this, this);
		new Vector3ZValueTreeItem(this, this);
	}
}

QVariant PLDynVarVector3TreeItem::data(const int column, const int role)
{
	UpdateData();
	return PLDynVarStringTreeItem::data(column, role);
}

void PLDynVarVector3TreeItem::UpdateData()
{
	m_Vector3.FromString(m_dynVar->GetString());
}

void PLDynVarVector3TreeItem::UpdateDataToVar()
{
	m_dynVar->SetString(m_Vector3.ToString());
}

PLDynVarVector3TreeItem::Vector3ValueBaseTreeItem::Vector3ValueBaseTreeItem(const QString &name, QObject *parent, PLDynVarVector3TreeItem *parentItem) : TreeItemBase(2, parent),
	m_Name(name),
	m_parentItem(parentItem)
{
	SetFlags(1, Qt::ItemIsEditable);
}

QVariant PLDynVarVector3TreeItem::Vector3ValueBaseTreeItem::data(const int column, const int role)
{
	if (!m_parentItem->IsInStandardRole(role))
		return QVariant();

	if(m_parentItem == nullptr)
		return QVariant();

	if (column == 0) {
		return m_Name;
	} else if (column == 1) {
		return (double)GetVectorData(m_parentItem->m_Vector3);
	}

	return QVariant();
}

bool PLDynVarVector3TreeItem::Vector3ValueBaseTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::EditRole || column != 1)
		return false;

	float floatVal = value.value<float>();
	SetVectorData(m_parentItem->m_Vector3, floatVal);
	m_parentItem->UpdateDataToVar();
	return true;
}

PLDynVarVector3TreeItem::Vector3XValueTreeItem::Vector3XValueTreeItem(QObject *parent, PLDynVarVector3TreeItem *parentItem) : Vector3ValueBaseTreeItem("X", parent, parentItem)
{
}

float PLDynVarVector3TreeItem::Vector3XValueTreeItem::GetVectorData(const PLMath::Vector3 &vector)
{
	return vector.x;
}

void PLDynVarVector3TreeItem::Vector3XValueTreeItem::SetVectorData(PLMath::Vector3 &vector, float newValue)
{
	vector.SetX(newValue);
}

PLDynVarVector3TreeItem::Vector3YValueTreeItem::Vector3YValueTreeItem(QObject *parent, PLDynVarVector3TreeItem *parentItem) : Vector3ValueBaseTreeItem("Y", parent, parentItem)
{
}

float PLDynVarVector3TreeItem::Vector3YValueTreeItem::GetVectorData(const PLMath::Vector3 &vector)
{
	return vector.y;
}

void PLDynVarVector3TreeItem::Vector3YValueTreeItem::SetVectorData(PLMath::Vector3 &vector, float newValue)
{
	vector.SetY(newValue);
}

PLDynVarVector3TreeItem::Vector3ZValueTreeItem::Vector3ZValueTreeItem(QObject *parent, PLDynVarVector3TreeItem *parentItem) : Vector3ValueBaseTreeItem("Z", parent, parentItem)
{
}

float PLDynVarVector3TreeItem::Vector3ZValueTreeItem::GetVectorData(const PLMath::Vector3 &vector)
{
	return vector.z;
}

void PLDynVarVector3TreeItem::Vector3ZValueTreeItem::SetVectorData(PLMath::Vector3 &vector, float newValue)
{
	vector.SetZ(newValue);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
