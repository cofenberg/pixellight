/*********************************************************\
 *  File: SNMPostProcessOldFilm.cpp                      *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLCompositing/Shaders/PostProcessing/PostProcessManager.h>
#include "PLPostProcessEffects/SNMPostProcessOldFilm.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
using namespace PLScene;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessOldFilm)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessOldFilm::SNMPostProcessOldFilm(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	SlotOnSceneNodeUpdate(this),
	Filename(this),
	m_fScratchPos(0.0f)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/OldFilm.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessOldFilm::~SNMPostProcessOldFilm()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNodeModifier functions  ]
//[-------------------------------------------------------]
void SNMPostProcessOldFilm::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&SlotOnSceneNodeUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&SlotOnSceneNodeUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMPostProcessOldFilm::OnSceneNodeUpdate()
{
	// Update the movement parameter
	m_fScratchPos += Timing::GetInstance()->GetTimeDifference()*0.5f;
	if (m_fScratchPos > 1.0f)
		m_fScratchPos -= 1.0f;
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessOldFilm::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	// ScratchPos
	Parameter *pParameter = GetParameter("ScratchPos");
	if (pParameter)
		pParameter->SetValue1f(m_fScratchPos);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
