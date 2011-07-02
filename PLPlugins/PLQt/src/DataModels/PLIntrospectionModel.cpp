/*********************************************************\
 *  File: PLIntrospectionModel.cpp                       *
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
#include <PLCore/PLCoreDefinitions.h>
#include <PLCore/Base/Var/DynVar.h>
#include <PLCore/Base/Func/DynFunc.h>
#include "PLQt/QtStringAdapter.h"
#include "PLQt/DataModels/TreeItemBase.h"
#include "PLQt/DataModels/PLTreeItems/PLDynVarTreeItemsFactory.h"
#include "PLQt/DataModels/PLIntrospectionModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {
namespace DataModels {


class AttributeInfoHeaderTreeItem : public TreeItemBase {


	public:
		AttributeInfoHeaderTreeItem(QObject *parent = nullptr) : TreeItemBase(2, parent)
		{
		}

		virtual QVariant data(const int column, const int role)
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


PLIntrospectionModel::PLIntrospectionModel(QObject *parent) : TreeModelBase(new AttributeInfoHeaderTreeItem(parent), parent)
{
}

PLIntrospectionModel::PLIntrospectionModel(DataModels::TreeItemBase *rootItem, QObject *parent) : TreeModelBase(rootItem, parent)
{
}

void PLIntrospectionModel::SetObject(PLCore::Object *Obj)
{
	beginResetModel();
	const QObjectList &childs = GetRootItem()->children();
	qDeleteAll(childs.begin(), childs.end());

	if (Obj) {
		PLGeneral::List<PLCore::DynFuncPtr> funcs;
		Obj->GetMethods(funcs);

		PLGeneral::List<PLCore::DynVar*> list = Obj->GetAttributes();
		for (PLGeneral::uint32 i=0; i<list.GetNumOfElements(); i++) {
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
} // PLQt
