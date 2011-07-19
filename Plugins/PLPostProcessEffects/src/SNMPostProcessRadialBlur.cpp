/*********************************************************\
 *  File: SNMPostProcessRadialBlur.cpp                   *
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
#include "PLPostProcessEffects/SNMPostProcessRadialBlur.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessRadialBlur)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessRadialBlur::SNMPostProcessRadialBlur(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	WarpPoint(this),
	BlurStart(this),
	BlurWidth(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/RadialBlur.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessRadialBlur::~SNMPostProcessRadialBlur()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessRadialBlur::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // WarpPoint
		Parameter *pParameter = GetParameter("WarpPoint");
		if (pParameter)
			pParameter->SetValue2fv(WarpPoint.Get());
	}

	{ // BlurStart
		Parameter *pParameter = GetParameter("BlurStart");
		if (pParameter)
			pParameter->SetValue1f(BlurStart.Get());
	}

	{ // BlurWidth
		Parameter *pParameter = GetParameter("BlurWidth");
		if (pParameter)
			pParameter->SetValue1f(BlurWidth.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
