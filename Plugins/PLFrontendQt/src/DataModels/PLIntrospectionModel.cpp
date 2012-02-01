/*********************************************************\
 *  File: PLIntrospectionModel.cpp                       *
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
#include <PLCore/PLCoreDefinitions.h>
#include <PLCore/Base/Var/DynVar.h>
#include <PLCore/Base/Func/DynFunc.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/TreeItemBase.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarTreeItemsFactory.h"
#include "PLFrontendQt/DataModels/PLIntrospectionModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


class AttributeInfoHeaderTreeItem : public TreeItemBase {


	public:
		AttributeInfoHeaderTreeItem(TreeItemBase *parent = nullptr) : TreeItemBase(2, parent)
		{
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (role == Qt::DisplayRole) {
				if (column == 0)
					return "Attribute";
				else if (column == 1)
					return "Value";
			}

			return QVariant();
		}


};


PLIntrospectionModel::PLIntrospectionModel(QObject *parent) : TreeModelBase(new AttributeInfoHeaderTreeItem, parent)
{
}

PLIntrospectionModel::PLIntrospectionModel(DataModels::TreeItemBase *rootItem, QObject *parent) : TreeModelBase(rootItem, parent)
{
}

void PLIntrospectionModel::SetObject(PLCore::Object *Obj)
{
	beginResetModel();
	GetRootItem()->clearChildren();

	if (Obj) {
		PLCore::List<PLCore::DynFuncPtr> funcs;
		Obj->GetMethods(funcs);

		PLCore::List<PLCore::DynVar*> list = Obj->GetAttributes();
		for (PLCore::uint32 i=0; i<list.GetNumOfElements(); i++) {
			PLCore::DynVar *var = list[i];
			PLDynVarTreeItemsFactory::CreateDynVarTreeItem(var, GetRootItem());
		}
	}

	endResetModel();
}

void PLIntrospectionModel::UpdateModel()
{
	dataChanged(this->index(0,1), this->index(GetRootItem()->children().count(), 1));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
