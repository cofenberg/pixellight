/*********************************************************\
 *  File: PLDynVarFloatTreeItem.cpp                      *
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
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarFloatTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


PLDynVarFloatTreeItem::PLDynVarFloatTreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, PLDynVarTreeItemTypes::Float, parent)
{
}

QVariant PLDynVarFloatTreeItem::data(const int column, const int role)
{
	return (IsInStandardRole(role) && column == 1) ? (double)m_dynVar->GetFloat() : PLDynVarStringTreeItem::data(column, role);
}

bool PLDynVarFloatTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::EditRole || column != 1)
		return false;

	float floatVal = value.value<float>();
	m_dynVar->SetFloat(floatVal);
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
