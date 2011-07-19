/*********************************************************\
 *  File: SNMPostProcessDiagonalBlur.cpp                 *
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
#include "PLPostProcessEffects/SNMPostProcessDiagonalBlur.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessDiagonalBlur)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessDiagonalBlur::SNMPostProcessDiagonalBlur(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	ColorScale(this),
	PixelKernel0(this),
	PixelKernel1(this),
	PixelKernel2(this),
	PixelKernel3(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/DiagonalBlur.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessDiagonalBlur::~SNMPostProcessDiagonalBlur()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessDiagonalBlur::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // ColorScale
		Parameter *pParameter = GetParameter("ColorScale");
		if (pParameter)
			pParameter->SetValue1f(ColorScale.Get());
	}

	{ // PixelKernel[0]
		Parameter *pParameter = GetParameter("PixelKernel[0]");
		if (pParameter)
			pParameter->SetValue2fv(PixelKernel0.Get());
	}

	{ // PixelKernel[1]
		Parameter *pParameter = GetParameter("PixelKernel[1]");
		if (pParameter)
			pParameter->SetValue2fv(PixelKernel1.Get());
	}

	{ // PixelKernel[2]
		Parameter *pParameter = GetParameter("PixelKernel[2]");
		if (pParameter)
			pParameter->SetValue2fv(PixelKernel2.Get());
	}

	{ // PixelKernel[3]
		Parameter *pParameter = GetParameter("PixelKernel[3]");
		if (pParameter)
			pParameter->SetValue2fv(PixelKernel3.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
