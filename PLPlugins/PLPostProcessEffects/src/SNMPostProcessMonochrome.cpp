/*********************************************************\
 *  File: SNMPostProcessMonochrome.cpp                   *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLScene/Compositing/PostProcessing/PostProcessManager.h>
#include "PLPostProcessEffects/SNMPostProcessMonochrome.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessMonochrome)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessMonochrome::SNMPostProcessMonochrome(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	LuminanceConvert(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Monochrome.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessMonochrome::~SNMPostProcessMonochrome()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SNMPostProcess functions      ]
//[-------------------------------------------------------]
void SNMPostProcessMonochrome::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	// LuminanceConvert
	Parameter *pParameter = GetParameter("LuminanceConvert");
	if (pParameter)
		pParameter->SetValue3fv(LuminanceConvert.Get());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
