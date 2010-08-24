/*********************************************************\
 *  File: SNProjectiveSpotLight.cpp                      *
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
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SNProjectiveSpotLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNProjectiveSpotLight)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNProjectiveSpotLight::GetProjectedMaterial() const
{
	return m_sProjectedMaterial;
}

void SNProjectiveSpotLight::SetProjectedMaterial(const String &sValue)
{
	if (m_sProjectedMaterial != sValue) {
		m_sProjectedMaterial = sValue;
		m_bProjectedMaterial = false;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNProjectiveSpotLight::SNProjectiveSpotLight() :
	ProjectedMaterial(this),
	Flags(this),
	m_sProjectedMaterial("Data/Textures/PLLogo.dds"),
	m_bProjectedMaterial(false)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoCone);
}

/**
*  @brief
*    Destructor
*/
SNProjectiveSpotLight::~SNProjectiveSpotLight()
{
}

/**
*  @brief
*    Returns the handler of the projected material
*/
const MaterialHandler &SNProjectiveSpotLight::GetProjectedMaterialHandler()
{
	if (!m_bProjectedMaterial) {
		m_cProjectedMaterial.SetResource(GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(m_sProjectedMaterial));
		m_bProjectedMaterial = true;
	}
	return m_cProjectedMaterial;
}


//[-------------------------------------------------------]
//[ Public virtual SNLight functions                      ]
//[-------------------------------------------------------]
bool SNProjectiveSpotLight::IsProjectiveSpotLight() const
{
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
