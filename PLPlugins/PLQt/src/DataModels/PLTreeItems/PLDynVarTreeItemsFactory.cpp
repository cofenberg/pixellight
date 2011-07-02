/*********************************************************\
 *  File: PLDynVarTreeItemsFactory.cpp                   *
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
#include "PLQt/DataModels/PLTreeItems/PLDynVarStringTreeItem.h"
#include "PLQt/DataModels/PLTreeItems/PLDynVarFlagsTreeItem.h"
#include "PLQt/DataModels/PLTreeItems/PLDynVarVector3TreeItem.h"
#include "PLQt/DataModels/PLTreeItems/PLDynVarFloatTreeItem.h"
#include "PLQt/DataModels/PLTreeItems/PLDynVarColorTreeItem.h"
#include "PLQt/DataModels/PLTreeItems/PLDynVarTreeItemsFactory.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {
namespace DataModels {


TreeItemBase *PLDynVarTreeItemsFactory::CreateDynVarTreeItem(PLCore::DynVar *dynVar, QObject *parent)
{
	// [TODO] use here the typeid constant of the corresponding type instead the hardcoded number
	if (dynVar->GetType().IsFlagType())
		new PLDynVarFlagsTreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == 1001)
		new PLDynVarVector3TreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == PLCore::TypeFloat)
		new PLDynVarFloatTreeItem(dynVar, parent);
	else if (dynVar->GetTypeID() == 2001)
		new PLDynVarColorTreeItem(dynVar, parent);
	else
		new PLDynVarStringTreeItem(dynVar, parent);
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLQt
