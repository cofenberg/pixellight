/*********************************************************\
 *  File: SNMPostProcessPixel.cpp                        *
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
#include "PLPostProcessEffects/SNMPostProcessPixel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessPixel)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessPixel::SNMPostProcessPixel(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	PixelSize(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Pixel.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessPixel::~SNMPostProcessPixel()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SNMPostProcess functions      ]
//[-------------------------------------------------------]
void SNMPostProcessPixel::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	// PixelSize
	// Update scale down parameters
	Parameter *pParameter = GetParameter("ScaleX", 0);
	if (pParameter)
		pParameter->SetValue1f(1.0f/PixelSize.Get().x);
	pParameter = GetParameter("ScaleY", 0);
	if (pParameter)
		pParameter->SetValue1f(1.0f/PixelSize.Get().y);

	// Update scale up parameters
	pParameter = GetParameter("ScaleX", 1);
	if (pParameter)
		pParameter->SetValue1f(PixelSize.Get().x);
	pParameter = GetParameter("ScaleY", 1);
	if (pParameter)
		pParameter->SetValue1f(PixelSize.Get().y);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
