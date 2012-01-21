/*********************************************************\
 *  File: PLDynVarFlagsTreeItem.cpp                      *
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
#include <PLCore/Base/Var/DynVar.h>
#include <PLCore/Base/TypeInfo/DynTypeInfo.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarFlagsTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {
namespace DataModels {


PLDynVarFlagsTreeItem::PLDynVarFlagsTreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, PLDynVarTreeItemTypes::Flags, parent)
{
	RemoveFlags(1, Qt::ItemIsEditable);

	PLCore::DynTypeInfo &typeInfo = m_dynVar->GetType();

	if (typeInfo.IsFlagType()) {
		const List<String> &enumList = typeInfo.GetEnumValues();

		// Assumption that the order in the list equals to the bit which the flag represents
		for (uint32 i=0; i<enumList.GetNumOfElements(); i++) {
			QString str(QtStringAdapter::PLToQt(enumList[i]));
			new FlagValueTreeItem(this, str, 1<<i, this);
		}
	}
}

QVariant PLDynVarFlagsTreeItem::data(const int column, const int role)
{
	UpdateData();
	return PLDynVarStringTreeItem::data(column, role);
}

void PLDynVarFlagsTreeItem::UpdateData()
{
	m_flagValues = m_dynVar->GetUInt32();
}

void PLDynVarFlagsTreeItem::UpdateDataToVar()
{
	m_dynVar->SetUInt32(m_flagValues);
}

PLDynVarFlagsTreeItem::FlagValueTreeItem::FlagValueTreeItem(QObject *parent, QString flagName, uint32 flagValue, PLDynVarFlagsTreeItem *parentItem) : TreeItemBase(2, parent),
	m_flagValue(flagValue),
	m_flagName(flagName),
	m_parentItem(parentItem)
{
	SetFlags(1, Qt::ItemIsUserCheckable);
}

QVariant PLDynVarFlagsTreeItem::FlagValueTreeItem::data(const int column, const int role)
{
	if (m_parentItem == nullptr)
		return QVariant();

	if (column == 0 && m_parentItem->IsInStandardRole(role))
		return m_flagName;
	else if (column == 1 && role == Qt::CheckStateRole)
		return (m_parentItem->m_flagValues & m_flagValue) == m_flagValue ? Qt::Checked : Qt::Unchecked;
	else if (column == 1 && role == Qt::ToolTipRole)
		return (m_parentItem->m_flagValues & m_flagValue) == m_flagValue;
	return QVariant();
}

bool PLDynVarFlagsTreeItem::FlagValueTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::CheckStateRole || column != 1)
		return false;

	bool boolVal = value.value<bool>();

	if (boolVal)
		m_parentItem->m_flagValues |= m_flagValue;
	else
		m_parentItem->m_flagValues &= ~m_flagValue;

	m_parentItem->UpdateDataToVar();
	return true;
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
