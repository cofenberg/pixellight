/*********************************************************\
 *  File: SNMPostProcessToneMap.cpp                      *
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
#include "PLPostProcessEffects/SNMPostProcessToneMap.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessToneMap)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessToneMap::SNMPostProcessToneMap(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	ExposureLevel(this),
	GammaLevel(this),
	DeFogLevel(this),
	FogColor(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/ToneMap.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessToneMap::~SNMPostProcessToneMap()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessToneMap::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // ExposureLevel
		Parameter *pParameter = GetParameter("ExposureLevel");
		if (pParameter)
			pParameter->SetValue1f(ExposureLevel.Get());
	}

	{ // GammaLevel
		Parameter *pParameter = GetParameter("GammaLevel");
		if (pParameter)
			pParameter->SetValue1f(GammaLevel.Get());
	}

	{ // DeFogLevel
		Parameter *pParameter = GetParameter("DeFogLevel");
		if (pParameter)
			pParameter->SetValue1f(DeFogLevel.Get());
	}

	{ // FogColor
		Parameter *pParameter = GetParameter("FogColor");
		if (pParameter)
			pParameter->SetValue3fv(FogColor.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
