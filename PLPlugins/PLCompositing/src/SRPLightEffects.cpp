/*********************************************************\
 *  File: SRPLightEffects.cpp                            *
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
#include <PLRenderer/Material/MaterialManager.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLCompositing/SRPLightEffects.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPLightEffects)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SRPLightEffects::GetCoronaMaterial() const
{
	return m_sCoronaMaterial;
}

void SRPLightEffects::SetCoronaMaterial(const String &sValue)
{
	if (m_sCoronaMaterial != sValue) {
		m_sCoronaMaterial = sValue;
		m_bCoronaMaterial = false;
	}
}

String SRPLightEffects::GetFlareMaterial() const
{
	return m_sFlareMaterial;
}

void SRPLightEffects::SetFlareMaterial(const String &sValue)
{
	if (m_sFlareMaterial != sValue) {
		m_sFlareMaterial = sValue;
		m_bFlareMaterial = false;
	}
}

String SRPLightEffects::GetBlendMaterial() const
{
	return m_sBlendMaterial;
}

void SRPLightEffects::SetBlendMaterial(const String &sValue)
{
	if (m_sBlendMaterial != sValue) {
		m_sBlendMaterial = sValue;
		m_bBlendMaterial = false;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the handler of the corona material
*/
const MaterialHandler &SRPLightEffects::GetCoronaMaterialHandler()
{
	if (!m_bCoronaMaterial) {
		m_cCoronaMaterial.SetResource(GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(m_sCoronaMaterial));
		m_bCoronaMaterial = true;
	}
	return m_cCoronaMaterial;
}

/**
*  @brief
*    Returns the handler of the flare material
*/
const MaterialHandler &SRPLightEffects::GetFlareMaterialHandler()
{
	if (!m_bFlareMaterial) {
		m_cFlareMaterial.SetResource(GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(m_sFlareMaterial));
		m_bFlareMaterial = true;
	}
	return m_cFlareMaterial;
}

/**
*  @brief
*    Returns the handler of the blend material
*/
const MaterialHandler &SRPLightEffects::GetBlendMaterialHandler()
{
	if (!m_bBlendMaterial) {
		m_cBlendMaterial.SetResource(GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(m_sBlendMaterial));
		m_bBlendMaterial = true;
	}
	return m_cBlendMaterial;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPLightEffects::SRPLightEffects() :
	CoronaMaterial(this),
	FlareMaterial(this),
	BlendMaterial(this),
	Flags(this),
	m_bCoronaMaterial(false),
	m_sCoronaMaterial("Data/Effects/DefaultCorona.plfx"),
	m_bFlareMaterial(false),
	m_sFlareMaterial("Data/Effects/DefaultFlare.plfx"),
	m_bBlendMaterial(false),
	m_sBlendMaterial("Data/Effects/DefaultBlend.plfx")
{
}

/**
*  @brief
*    Destructor
*/
SRPLightEffects::~SRPLightEffects()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
