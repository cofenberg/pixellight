/*********************************************************\
 *  File: PLDynVarTreeItemsFactory.cpp                   *
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
#include <PLMath/Vector3.h>
#include <PLMath/Vector3i.h>
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Color/Color4.h>
#include <PLCore/Base/TypeInfo/DynTypeInfo.h>
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarStringTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarFlagsTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector2TreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector3TreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector4TreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector2iTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector3iTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarNativNumericTypeTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarColorTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarEnumTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarTreeItemsFactory.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {
using namespace PLCore;


TreeItemBase *PLDynVarTreeItemsFactory::CreateDynVarTreeItem(PLCore::DynVar *dynVar, TreeItemBase *parent)
{
	if (dynVar == nullptr)
		return nullptr;
	
	// Check Flags and Enums before BaseType because Flags and Enums are internaly represented as int32
	if (dynVar->GetType().IsFlagType())
		return new PLDynVarFlagsTreeItem(dynVar, parent);
	else if(dynVar->GetType().IsEnumType())
		return new PLDynVarEnumTreeItem(dynVar, parent);
	else if (IsBaseType(*dynVar))
		return new PLDynVarNativNumericTypeTreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLMath::Vector2>::TypeID)
		return new PLDynVarVector2TreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLMath::Vector3>::TypeID)
		return new PLDynVarVector3TreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLMath::Vector4>::TypeID)
		return new PLDynVarVector4TreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLMath::Vector2i>::TypeID)
		return new PLDynVarVector2iTreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLMath::Vector3i>::TypeID)
		return new PLDynVarVector3iTreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLGraphics::Color3>::TypeID || dynVar->GetTypeID() == PLCore::Type<PLGraphics::Color4>::TypeID)
		return new PLDynVarColorTreeItem(dynVar, parent);
	else
		return new PLDynVarStringTreeItem(dynVar, PLFrontendQt::DataModels::PLDynVarTreeItemTypes::String, parent);

	return nullptr;
}

bool PLDynVarTreeItemsFactory::IsBaseType(const PLCore::DynVar &dynVar)
{
	int typeId = dynVar.GetTypeID();
	return (typeId == PLCore::TypeBool || typeId == PLCore::TypeFloat || typeId == PLCore::TypeDouble
			|| typeId == PLCore::TypeInt || typeId == PLCore::TypeInt32 || typeId == PLCore::TypeInt16 || typeId == PLCore::TypeInt64  || typeId == PLCore::TypeInt8
		   || typeId == PLCore::TypeUInt32 || typeId == PLCore::TypeUInt16 || typeId == PLCore::TypeUInt64  || typeId == PLCore::TypeUInt8);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
