/*********************************************************\
 *  File: PLDynVarVector4TreeItem.cpp                    *
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
#include <PLMath/Vector4.h>
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector4TreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


PLDynVarVector4TreeItem::PLDynVarVector4TreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, PLDynVarTreeItemTypes::Vector4, parent)
{
	RemoveFlags(1,  Qt::ItemIsEditable);
	if (m_dynVar && m_dynVar->GetTypeID() == PLCore::Type<PLMath::Vector4>::TypeID) {
		new Vector4XValueTreeItem(this, this);
		new Vector4YValueTreeItem(this, this);
		new Vector4ZValueTreeItem(this, this);
		new Vector4WValueTreeItem(this, this);
	}
}

QVariant PLDynVarVector4TreeItem::data(const int column, const int role)
{
	UpdateData();
	return PLDynVarStringTreeItem::data(column, role);
}

void PLDynVarVector4TreeItem::UpdateData()
{
	m_Vector4.FromString(m_dynVar->GetString());
}

void PLDynVarVector4TreeItem::UpdateDataToVar()
{
	m_dynVar->SetString(m_Vector4.ToString());
}

PLDynVarVector4TreeItem::Vector4ValueBaseTreeItem::Vector4ValueBaseTreeItem(const QString &name, QObject *parent, PLDynVarVector4TreeItem *parentItem) : TreeItemBase(2, parent),
	m_Name(name),
	m_parentItem(parentItem)
{
	SetFlags(1, Qt::ItemIsEditable);
}

QVariant PLDynVarVector4TreeItem::Vector4ValueBaseTreeItem::data(const int column, const int role)
{
	if (!m_parentItem->IsInStandardRole(role))
		return QVariant();

	if(m_parentItem == nullptr)
		return QVariant();

	if (column == 0) {
		return m_Name;
	} else if (column == 1) {
		return (double)GetVectorData(m_parentItem->m_Vector4);
	}

	return QVariant();
}

bool PLDynVarVector4TreeItem::Vector4ValueBaseTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::EditRole || column != 1)
		return false;

	float floatVal = value.value<float>();
	SetVectorData(m_parentItem->m_Vector4, floatVal);
	m_parentItem->UpdateDataToVar();
	return true;
}

PLDynVarVector4TreeItem::Vector4XValueTreeItem::Vector4XValueTreeItem(QObject *parent, PLDynVarVector4TreeItem *parentItem) : Vector4ValueBaseTreeItem("X", parent, parentItem)
{
}

float PLDynVarVector4TreeItem::Vector4XValueTreeItem::GetVectorData(const PLMath::Vector4 &vector)
{
	return vector.x;
}

void PLDynVarVector4TreeItem::Vector4XValueTreeItem::SetVectorData(PLMath::Vector4 &vector, float newValue)
{
	vector.SetX(newValue);
}

PLDynVarVector4TreeItem::Vector4YValueTreeItem::Vector4YValueTreeItem(QObject *parent, PLDynVarVector4TreeItem *parentItem) : Vector4ValueBaseTreeItem("Y", parent, parentItem)
{
}

float PLDynVarVector4TreeItem::Vector4YValueTreeItem::GetVectorData(const PLMath::Vector4 &vector)
{
	return vector.y;
}

void PLDynVarVector4TreeItem::Vector4YValueTreeItem::SetVectorData(PLMath::Vector4 &vector, float newValue)
{
	vector.SetY(newValue);
}

PLDynVarVector4TreeItem::Vector4ZValueTreeItem::Vector4ZValueTreeItem(QObject *parent, PLDynVarVector4TreeItem *parentItem) : Vector4ValueBaseTreeItem("Z", parent, parentItem)
{
}

float PLDynVarVector4TreeItem::Vector4ZValueTreeItem::GetVectorData(const PLMath::Vector4 &vector)
{
	return vector.z;
}

void PLDynVarVector4TreeItem::Vector4ZValueTreeItem::SetVectorData(PLMath::Vector4 &vector, float newValue)
{
	vector.SetZ(newValue);
}

PLDynVarVector4TreeItem::Vector4WValueTreeItem::Vector4WValueTreeItem(QObject *parent, PLDynVarVector4TreeItem *parentItem) : Vector4ValueBaseTreeItem("W", parent, parentItem)
{
}

float PLDynVarVector4TreeItem::Vector4WValueTreeItem::GetVectorData(const PLMath::Vector4 &vector)
{
	return vector.w;
}

void PLDynVarVector4TreeItem::Vector4WValueTreeItem::SetVectorData(PLMath::Vector4 &vector, float newValue)
{
	vector.SetW(newValue);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
