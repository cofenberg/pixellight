/*********************************************************\
 *  File: SNMPostProcessSepia2.cpp                       *
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
#include <PLRenderer/Material/Parameter.h>
#include <PLCompositing/Shaders/PostProcessing/PostProcessManager.h>
#include "PLPostProcessEffects/SNMPostProcessSepia2.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessSepia2)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessSepia2::SNMPostProcessSepia2(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	TintColor0(this),
	TintColor1(this),
	TintColor2(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Sepia2.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessSepia2::~SNMPostProcessSepia2()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessSepia2::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // TintColor[0]
		Parameter *pParameter = GetParameter("TintColor[0]");
		if (pParameter)
			pParameter->SetValue4fv(TintColor0.Get());
	}

	{ // TintColor[1]
		Parameter *pParameter = GetParameter("TintColor[1]");
		if (pParameter)
			pParameter->SetValue4fv(TintColor1.Get());
	}

	{ // TintColor[2]
		Parameter *pParameter = GetParameter("TintColor[2]");
		if (pParameter)
			pParameter->SetValue4fv(TintColor2.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
