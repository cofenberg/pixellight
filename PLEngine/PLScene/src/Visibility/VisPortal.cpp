/*********************************************************\
 *  File: VisPortal.cpp                                  *
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
#include "PLScene/Scene/SNCellPortal.h"
#include "PLScene/Visibility/VisContainer.h"
#include "PLScene/Visibility/VisPortal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the target visibility container the portal links to
*/
VisContainer *VisPortal::GetTargetVisContainer() const
{
	// Is it possible to 'see through' this portal?
	const SceneNode *pSceneNode = GetSceneNode();
	if (!pSceneNode || !(pSceneNode->GetFlags() & SNCellPortal::NoSeeThrough))
		return m_pTargetCell;
	else
		return nullptr;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VisPortal::VisPortal() :
	EventHandlerDestroy(&VisPortal::NotifyDestroy, this),
	m_pTargetCell(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
VisPortal::~VisPortal()
{
	if (m_pTargetCell)
		delete m_pTargetCell;
}

/**
*  @brief
*    Called when the scene node assigned with this visibililty container was destroyed
*/
void VisPortal::NotifyDestroy()
{
	SceneNode *pSceneNode = GetSceneNode();
	if (pSceneNode && pSceneNode->IsPortal() && pSceneNode->IsInstanceOf("PLScene::SNCellPortal")) {
		// Get the parent visibility container
		const VisNode *pParent = GetParent();
		if (pParent && pParent->IsContainer()) {
			VisContainer *pParentVisContainer = (VisContainer*)pParent;

			// Unregister within the parent container
			VisPortal *pPortal = pParentVisContainer->m_mapPortals.Get(pSceneNode->GetName());
			if (pPortal) {
				pParentVisContainer->m_lstNodes.Remove(pPortal);
				delete pPortal;
				pParentVisContainer->m_mapPortals.Remove(pSceneNode->GetName());
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual VisNode functions                      ]
//[-------------------------------------------------------]
bool VisPortal::IsPortal() const
{
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
