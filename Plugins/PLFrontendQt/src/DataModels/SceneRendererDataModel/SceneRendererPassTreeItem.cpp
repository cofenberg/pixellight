/*********************************************************\
 *  File: SceneRendererPassTreeItem.cpp                  *
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
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/PLTreeItems/PLDynVarTreeItemsFactory.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererPassTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {
namespace DataModels {
namespace SceneRendererDataModel {


SceneRendererPassTreeItem::SceneRendererPassTreeItem(PLScene::SceneRendererPass *item, QObject *parent) : TreeItemBase(2, parent),
	m_pPass(item)
{
	if (m_pPass) {
		List<PLCore::DynVar*> list = m_pPass->GetAttributes();
		for (uint32 i=0; i<list.GetNumOfElements(); i++) {
			PLCore::DynVar *var = list[i];
			PLDynVarTreeItemsFactory::CreateDynVarTreeItem(var, this);
		}
	}
}

QVariant SceneRendererPassTreeItem::data(const int column, const int role)
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (column == 0)
		return QtStringAdapter::PLToQt(m_pPass->GetName().GetUTF8());

	return QVariant();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt
