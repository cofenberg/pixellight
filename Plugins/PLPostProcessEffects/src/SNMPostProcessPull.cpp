/*********************************************************\
 *  File: SNMPostProcessPull.cpp                         *
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
#include "PLPostProcessEffects/SNMPostProcessPull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessPull)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessPull::SNMPostProcessPull(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	WarpPoint(this),
	WarpScale(this),
	WarpDimension(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Pull.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessPull::~SNMPostProcessPull()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessPull::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // WarpPoint
		Parameter *pParameter = GetParameter("WarpPoint");
		if (pParameter)
			pParameter->SetValue2fv(WarpPoint.Get());
	}

	{ // WarpScale
		Parameter *pParameter = GetParameter("WarpScale");
		if (pParameter)
			pParameter->SetValue1f(WarpScale.Get());
	}

	{ // WarpDimension
		Parameter *pParameter = GetParameter("WarpDimension");
		if (pParameter)
			pParameter->SetValue1f(WarpDimension.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
