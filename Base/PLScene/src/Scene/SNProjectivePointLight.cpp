/*********************************************************\
 *  File: SNProjectivePointLight.cpp                     *
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
#include <PLRenderer/RendererContext.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SNProjectivePointLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNProjectivePointLight)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNProjectivePointLight::GetProjectedMaterial() const
{
	return m_sProjectedMaterial;
}

void SNProjectivePointLight::SetProjectedMaterial(const String &sValue)
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
SNProjectivePointLight::SNProjectivePointLight() :
	ProjectedMaterial(this),
	Flags(this),
	m_sProjectedMaterial("Data/Textures/DefaultCubeMap.dds"),
	m_bProjectedMaterial(false)
{
}

/**
*  @brief
*    Destructor
*/
SNProjectivePointLight::~SNProjectivePointLight()
{
}

/**
*  @brief
*    Returns the handler of the projected material
*/
const MaterialHandler &SNProjectivePointLight::GetProjectedMaterialHandler()
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
bool SNProjectivePointLight::IsProjectivePointLight() const
{
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
