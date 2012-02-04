/*********************************************************\
 *  File: SceneGraphNodeTreeItemBase.cpp                 *
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
#include "PLFrontendQt/DataModels/SceneGraphNodeTreeItemBase.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


SceneGraphNodeTreeItemBase::SceneGraphNodeTreeItemBase(PLFrontendQt::DataModels::SceneGraphTreeModel& cModel, PLFrontendQt::DataModels::TreeItemBase* parent) : TreeItemBase(1, parent), m_cModel(cModel)
{
}

QModelIndex SceneGraphNodeTreeItemBase::index()
{
	return m_cModel.GetIndexForTreeItem(this);
}

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt
