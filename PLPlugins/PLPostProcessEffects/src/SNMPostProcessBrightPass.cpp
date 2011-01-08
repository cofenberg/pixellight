/*********************************************************\
 *  File: SNMPostProcessBrightPass.cpp                   *
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
#include <PLRenderer/Material/Parameter.h>
#include <PLCompositing/Shaders/PostProcessing/PostProcessManager.h>
#include "PLPostProcessEffects/SNMPostProcessBrightPass.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessBrightPass)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessBrightPass::SNMPostProcessBrightPass(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	Luminance(this),
	MiddleGray(this),
	WhiteCutoff(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/BrightPass.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessBrightPass::~SNMPostProcessBrightPass()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessBrightPass::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	// Luminance
	Parameter *pParameter = GetParameter("Luminance", 0);
	if (pParameter)
		pParameter->SetValue1f(Luminance.Get());

	// MiddleGray
	pParameter = GetParameter("MiddleGray", 0);
	if (pParameter)
		pParameter->SetValue1f(MiddleGray.Get());

	// WhiteCutoff
	pParameter = GetParameter("WhiteCutoff", 0);
	if (pParameter)
		pParameter->SetValue1f(WhiteCutoff.Get());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
