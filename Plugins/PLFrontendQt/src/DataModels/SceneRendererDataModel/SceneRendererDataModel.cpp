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
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Module.h>
#include <PLScene/Compositing/SceneRenderer.h>
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererHeaderTreeItem.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererPassTreeItem.h"
#include "PLFrontendQt/DataModels/SceneRendererDataModel/SceneRendererDataModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {
namespace DataModels {
namespace SceneRendererDataModel {


SceneRendererDataModel::SceneRendererDataModel(QObject *parent): TreeModelBase(new SceneRendererHeaderTreeItem, parent),
	m_pSceneRenderer(nullptr)
{
}

SceneRenderer *SceneRendererDataModel::GetSceneRenderer() const
{
	return m_pSceneRenderer;
}

void SceneRendererDataModel::SetSceneRenderer(SceneRenderer *nodeObj)
{
	if (m_pSceneRenderer != nodeObj) {
		m_pSceneRenderer = nodeObj;

		beginResetModel();
		const QObjectList &childs = GetRootItem()->children();
		qDeleteAll(childs.begin(), childs.end());

		if (m_pSceneRenderer) {
			uint32 count = m_pSceneRenderer->GetNumOfElements();

			// Loop through all scene renderer passes
			for (uint32 nPass=0; nPass< count; nPass++) {
				// Get the current scene renderer pass
				SceneRendererPass *pSceneRendererPass = m_pSceneRenderer->GetByIndex(nPass);
				if (pSceneRendererPass)
					new SceneRendererPassTreeItem(pSceneRendererPass, GetRootItem());
			}
		}

		endResetModel();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt
