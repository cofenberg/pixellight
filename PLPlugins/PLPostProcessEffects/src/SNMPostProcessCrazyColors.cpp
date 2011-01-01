/*********************************************************\
 *  File: SNMPostProcessCrazyColors.cpp                  *
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
#include "PLPostProcessEffects/SNMPostProcessCrazyColors.h"


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
pl_implement_class(SNMPostProcessCrazyColors)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessCrazyColors::SNMPostProcessCrazyColors(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	SlotOnSceneNodeUpdate(this),
	ColorScaleX(this),
	ColorSpeedX(this),
	ColorOffsetX(this),
	ColorScaleY(this),
	ColorSpeedY(this),
	ColorOffsetY(this),
	Filename(this),
	m_fTimer(0.0f)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/CrazyColors.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessCrazyColors::~SNMPostProcessCrazyColors()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNodeModifier functions  ]
//[-------------------------------------------------------]
void SNMPostProcessCrazyColors::OnActivate(bool bActivate)
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
void SNMPostProcessCrazyColors::OnSceneNodeUpdate()
{
	m_fTimer += Timing::GetInstance()->GetTimeDifference();
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessCrazyColors::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // Timer
		Parameter *pParameter = GetParameter("Timer");
		if (pParameter)
			pParameter->SetValue1f(m_fTimer);
	}

	{ // ColorScaleX
		Parameter *pParameter = GetParameter("ColorScaleX");
		if (pParameter)
			pParameter->SetValue3fv(ColorScaleX.Get());
	}

	{ // ColorSpeedX
		Parameter *pParameter = GetParameter("ColorSpeedX");
		if (pParameter)
			pParameter->SetValue3fv(ColorSpeedX.Get());
	}

	{ // ColorOffsetX
		Parameter *pParameter = GetParameter("ColorOffsetX");
		if (pParameter)
			pParameter->SetValue3fv(ColorOffsetX.Get());
	}

	{ // ColorScaleY
		Parameter *pParameter = GetParameter("ColorScaleY");
		if (pParameter)
			pParameter->SetValue3fv(ColorScaleY.Get());
	}

	{ // ColorSpeedY
		Parameter *pParameter = GetParameter("ColorSpeedY");
		if (pParameter)
			pParameter->SetValue3fv(ColorSpeedY.Get());
	}

	{ // ColorOffsetY
		Parameter *pParameter = GetParameter("ColorOffsetX");
		if (pParameter)
			pParameter->SetValue3fv(ColorOffsetX.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
