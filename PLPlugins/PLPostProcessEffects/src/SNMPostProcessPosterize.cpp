/*********************************************************\
 *  File: SNMPostProcessPosterize.cpp                    *
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
#include "PLPostProcessEffects/SNMPostProcessPosterize.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessPosterize)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessPosterize::SNMPostProcessPosterize(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	Gamma(this),
	Colors(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Posterize.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessPosterize::~SNMPostProcessPosterize()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessPosterize::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // Gamma
		Parameter *pParameter = GetParameter("Gamma");
		if (pParameter)
			pParameter->SetValue1f(Gamma.Get());
	}

	{ // Colors
		Parameter *pParameter = GetParameter("Colors");
		if (pParameter)
			pParameter->SetValue1f(Colors.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
