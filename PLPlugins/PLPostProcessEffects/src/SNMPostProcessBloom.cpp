/*********************************************************\
 *  File: SNMPostProcessBloom.cpp                        *
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
#include "PLPostProcessEffects/SNMPostProcessBloom.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessBloom)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessBloom::SNMPostProcessBloom(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	Luminance(this),
	MiddleGray(this),
	WhiteCutoff(this),
	BloomScale(this),
	Strength(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Bloom.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessBloom::~SNMPostProcessBloom()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessBloom::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // Strength
		// Update scale down parameters
		Parameter *pParameter = GetParameter("ScaleX", 0);
		if (pParameter)
			pParameter->SetValue1f(1.0f/Strength.Get().x);
		pParameter = GetParameter( "ScaleY", 0);
		if (pParameter)
			pParameter->SetValue1f(1.0f/Strength.Get().y);

		// Update scale up parameters
		pParameter = GetParameter("ScaleX", 6);
		if (pParameter)
			pParameter->SetValue1f(Strength.Get().x);
		pParameter = GetParameter("ScaleY", 6);
		if (pParameter)
			pParameter->SetValue1f(Strength.Get().y);
	}

	{ // Luminance
		Array<Parameter*> lstParameters;
		if (GetParameters("Luminance", lstParameters)) {
			Iterator<Parameter*> cIterator = lstParameters.GetIterator();
			while (cIterator.HasNext())
				cIterator.Next()->SetValue1f(Luminance.Get());
		}
	}

	{ // MiddleGray
		Array<Parameter*> lstParameters;
		if (GetParameters("MiddleGray", lstParameters)) {
			Iterator<Parameter*> cIterator = lstParameters.GetIterator();
			while (cIterator.HasNext())
				cIterator.Next()->SetValue1f(MiddleGray.Get());
		}
	}

	{ // WhiteCutoff
		Array<Parameter*> lstParameters;
		if (GetParameters("WhiteCutoff", lstParameters)) {
			Iterator<Parameter*> cIterator = lstParameters.GetIterator();
			while (cIterator.HasNext())
				cIterator.Next()->SetValue1f(WhiteCutoff.Get());
		}
	}

	{ // BloomScale
		Array<Parameter*> lstParameters;
		if (GetParameters("BloomScale", lstParameters)) {
			Iterator<Parameter*> cIterator = lstParameters.GetIterator();
			while (cIterator.HasNext())
				cIterator.Next()->SetValue1f(BloomScale.Get());
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
