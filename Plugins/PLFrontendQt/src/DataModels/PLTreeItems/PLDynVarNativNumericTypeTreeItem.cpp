/*********************************************************\
 *  File: PLDynVarNativNumericTypeTreeItem.cpp           *
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
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarNativNumericTypeTreeItem.h"
#include <PLCore/PLCoreDefinitions.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


PLDynVarNativNumericTypeTreeItem::PLDynVarNativNumericTypeTreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, GetNumericTypeFromDynVar(dynVar), parent)
	, m_basisTypeId(dynVar ? dynVar->GetTypeID() : -1)
{
	if (m_basisTypeId == PLCore::TypeBool)
		SetFlags(1, Qt::ItemIsUserCheckable);
}

QVariant PLDynVarNativNumericTypeTreeItem::data(const int column, const int role)
{
 	if (column == 1 && m_basisTypeId == PLCore::TypeBool)
	{
		if(role == Qt::CheckStateRole)
			return m_dynVar->GetBool() ? Qt::Checked : Qt::Unchecked;
		else
			return QVariant(); 
	}
	
	return (IsInStandardRole(role) && column == 1) ? getBaseTypeData() : PLDynVarStringTreeItem::data(column, role);
}

bool PLDynVarNativNumericTypeTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role == Qt::CheckStateRole && column == 1 && m_basisTypeId == PLCore::TypeBool)
		return setBaseTypeData(value);
	
	if (role == Qt::EditRole && column == 1 && m_basisTypeId != PLCore::TypeBool)
		return setBaseTypeData(value);

	
// 	float floatVal = value.value<float>();
// 	m_dynVar->SetFloat(floatVal);
 	return false;
}

QVariant PLDynVarNativNumericTypeTreeItem::getBaseTypeData()
{
	switch(m_basisTypeId)
	{
		case PLCore::TypeBool:
			return m_dynVar->GetBool();
		case PLCore::TypeDouble:
			return m_dynVar->GetDouble();
		case PLCore::TypeFloat:
			return m_dynVar->GetFloat();
		case PLCore::TypeInt8:
			return (qint8)m_dynVar->GetInt8();
		case PLCore::TypeInt16:
			return (qint16)m_dynVar->GetInt16();
		case PLCore::TypeInt32:
		case PLCore::TypeInt:
			return (int)m_dynVar->GetInt32();
		case PLCore::TypeInt64:
			return (qint64)m_dynVar->GetInt64();
		case PLCore::TypeUInt8:
			return (quint8)m_dynVar->GetUInt8();
		case PLCore::TypeUInt16:
			return (quint16)m_dynVar->GetUInt16();
		case PLCore::TypeUInt32:
			return (unsigned int)m_dynVar->GetUInt32();
		case PLCore::TypeUInt64:
			return (quint64)m_dynVar->GetUInt64();
		default:
			return QVariant();
	}
}

bool PLDynVarNativNumericTypeTreeItem::setBaseTypeData(const QVariant& value)
{
	bool bRet = true;
	switch(m_basisTypeId)
	{
		case PLCore::TypeBool:
			m_dynVar->SetBool(value.value<bool>());
			break;
		case PLCore::TypeDouble:
			m_dynVar->SetDouble(value.value<double>());
			break;
		case PLCore::TypeFloat:
			m_dynVar->SetFloat(value.value<float>());
			break;
		case PLCore::TypeInt8:
			m_dynVar->SetInt8(value.value<PLCore::int8>());
			break;
		case PLCore::TypeInt16:
			m_dynVar->SetInt16(value.value<PLCore::int16>());
			break;
		case PLCore::TypeInt32:
		case PLCore::TypeInt:
			m_dynVar->SetInt32(value.value<int>());
			break;
		case PLCore::TypeInt64:
			m_dynVar->SetInt64(value.value<PLCore::int64>());
			break;
		case PLCore::TypeUInt8:
			m_dynVar->SetUInt8(value.value<PLCore::uint8>());
			break;
		case PLCore::TypeUInt16:
			m_dynVar->SetUInt16(value.value<PLCore::uint16>());
			break;
		case PLCore::TypeUInt32:
			m_dynVar->SetUInt32(value.value<unsigned int>());
			break;
		case PLCore::TypeUInt64:
			m_dynVar->SetUInt64(value.value<PLCore::uint64>());
			break;
		default:
			bRet = false;
			break;
	}
	return bRet;
}

PLDynVarTreeItemTypes::DynVarTreeItemTypes PLDynVarNativNumericTypeTreeItem::GetNumericTypeFromDynVar(const PLCore::DynVar* dynVar)
{
	int typeId = dynVar ? dynVar->GetTypeID() : -1;
	switch(typeId)
	{
		case PLCore::TypeBool:
			return PLDynVarTreeItemTypes::Bool;
		case PLCore::TypeDouble:
			return PLDynVarTreeItemTypes::Double;
		case PLCore::TypeFloat:
			return PLDynVarTreeItemTypes::Float;
		case PLCore::TypeInt8:
			return PLDynVarTreeItemTypes::Int8;
		case PLCore::TypeInt16:
			return PLDynVarTreeItemTypes::Int16;
		case PLCore::TypeInt32:
		case PLCore::TypeInt:
			return PLDynVarTreeItemTypes::Int32;
		case PLCore::TypeInt64:
			return PLDynVarTreeItemTypes::Int64;
		case PLCore::TypeUInt8:
			return PLDynVarTreeItemTypes::UInt8;
		case PLCore::TypeUInt16:
			return PLDynVarTreeItemTypes::UInt16;
		case PLCore::TypeUInt32:
			return PLDynVarTreeItemTypes::UInt32;
		case PLCore::TypeUInt64:
			return PLDynVarTreeItemTypes::UInt64;
		default:
			return PLDynVarTreeItemTypes::String;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
