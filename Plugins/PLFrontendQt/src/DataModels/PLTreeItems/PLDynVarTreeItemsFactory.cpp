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
#include <PLGraphics/Color/Color3.h>
#include <PLCore/Base/TypeInfo/DynTypeInfo.h>
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarStringTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarFlagsTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarVector3TreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarFloatTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarColorTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarEnumTreeItem.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarTreeItemsFactory.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {
using namespace PLCore;


TreeItemBase *PLDynVarTreeItemsFactory::CreateDynVarTreeItem(PLCore::DynVar *dynVar, QObject *parent)
{
	if (dynVar->GetType().IsFlagType())
		new PLDynVarFlagsTreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLMath::Vector3>::TypeID)
		new PLDynVarVector3TreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::TypeFloat)
		new PLDynVarFloatTreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::Type<PLGraphics::Color3>::TypeID)
		new PLDynVarColorTreeItem(dynVar, parent);
	else if(dynVar->GetType().IsEnumType())
		new PLDynVarEnumTreeItem(dynVar, parent);
	else
		new PLDynVarStringTreeItem(dynVar, PLFrontendQt::DataModels::PLDynVarTreeItemTypes::String, parent);

	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
