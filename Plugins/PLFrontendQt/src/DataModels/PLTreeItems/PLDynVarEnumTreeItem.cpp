/*********************************************************\
 *  File: PLDynVarEnumTreeItem.cpp                       *
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
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarEnumTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {
namespace DataModels {


PLDynVarEnumTreeItem::PLDynVarEnumTreeItem(PLCore::DynVar *dynVar, TreeItemBase *parent) : PLDynVarStringTreeItem(dynVar, PLDynVarTreeItemTypes::Enum, parent)
{
	PLCore::DynTypeInfo &typeInfo = m_dynVar->GetType();

	if (typeInfo.IsEnumType()) {
		const List<String> &enumList = typeInfo.GetEnumValues();

		// Assumption that the order in the list equals to the bit which the flag represents
		for (uint32 i=0; i<enumList.GetNumOfElements(); i++) {
			QString str(QtStringAdapter::PLToQt(enumList[i]));
			QString sValue(QtStringAdapter::PLToQt(typeInfo.GetEnumValue(enumList[i])));
			m_enumValues.insert(str, sValue);
		}
	}
}

QVariant PLDynVarEnumTreeItem::data(const int column, const int role)
{
	if (column == 1 && role == PLDynVarTreeItemTypes::DynVarEnumValues)
		return m_enumValues;
	
	return PLDynVarStringTreeItem::data(column, role);
}

void PLDynVarEnumTreeItem::UpdateData()
{
	//m_flagValues = m_dynVar->GetUInt32();
}

void PLDynVarEnumTreeItem::UpdateDataToVar()
{
	//m_dynVar->SetUInt32(m_flagValues);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
