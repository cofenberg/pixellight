/*********************************************************\
 *  File: SceneRendererDataModel.cpp                     *
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
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererDataModelMimeData.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {
namespace SceneRendererDataModel {


SceneRendererDataModelMimeData::SceneRendererDataModelMimeData(const QModelIndexList & indexes): indexes_(indexes)
{
}
const QModelIndexList & SceneRendererDataModelMimeData::indexes() const
{
	return indexes_;
}

bool SceneRendererDataModelMimeData::hasFormat ( const QString & mimeType ) const
{
	if (mimeType == "application/x-pixellight.scenerendererpasses.list")
		return true;
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt
