/*********************************************************\
 *  File: PostProcess.cpp                                *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLScene/Compositing/PostProcessing/PostProcessManager.h"
#include "PLScene/Compositing/PostProcessing/PostProcess.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PostProcess::PostProcess(const String &sName, PostProcessManager &cManager) :
	Element<PostProcess>(sName, &cManager),
	m_bActive(true),
	m_pMaterialHandler(new MaterialHandler())
{
	// Load material
	if (sName.GetLength())
		m_pMaterialHandler->SetResource(cManager.GetRendererContext().GetMaterialManager().LoadResource(sName));
}

/**
*  @brief
*    Destructor
*/
PostProcess::~PostProcess()
{
	// Destroy material handler
	delete m_pMaterialHandler;
}

/**
*  @brief
*    Returns whether the post process is active or not
*/
bool PostProcess::IsActive() const
{
	return m_bActive;
}

/**
*  @brief
*    Sets whether the post process is active or not
*/
void PostProcess::SetActive(bool bActive)
{
	m_bActive = bActive;
}

/**
*  @brief
*    Returns the post process material
*/
Material *PostProcess::GetMaterial() const
{
	return m_pMaterialHandler->GetResource();
}

/**
*  @brief
*    Sets the post process material
*/
void PostProcess::SetMaterial(Material *pMaterial)
{
	m_pMaterialHandler->SetResource(pMaterial);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
