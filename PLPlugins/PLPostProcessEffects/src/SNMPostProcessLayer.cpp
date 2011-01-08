/*********************************************************\
 *  File: SNMPostProcessLayer.cpp                        *
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
#include "PLPostProcessEffects/SNMPostProcessLayer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessLayer)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessLayer::SNMPostProcessLayer(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	LayerMap(this),
	Blend(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Layer.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessLayer::~SNMPostProcessLayer()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessLayer::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // LayerMap
		Parameter *pParameter = GetParameter("LayerMap");
		if (pParameter)
			pParameter->SetValueTexture(LayerMap.Get());
	}

	{ // Blend
		Parameter *pParameter = GetParameter("Blend");
		if (pParameter)
			pParameter->SetValue4fv(Blend.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
