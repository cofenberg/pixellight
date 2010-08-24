/*********************************************************\
 *  File: SNBitmap.cpp                                   *
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
#include <PLGeneral/File/Url.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodes/SNBitmap.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNBitmap)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNBitmap::GetMaterial() const
{
	return m_sMaterial;
}

void SNBitmap::SetMaterial(const String &sValue)
{
	if (m_sMaterial != sValue) {
		m_sMaterial = sValue;
		m_bMaterial = false;
	}
}

const Color4 &SNBitmap::GetColor() const
{
	return m_cColor;
}

void SNBitmap::SetColor(const Color4 &cValue)
{
	m_cColor = cValue;
}

const Vector2 &SNBitmap::GetTexelStart() const
{
	return m_vTexelStart;
}

void SNBitmap::SetTexelStart(const Vector2 &vValue)
{
	m_vTexelStart = vValue;
}

const Vector2 &SNBitmap::GetTexelEnd() const
{
	return m_vTexelEnd;
}

void SNBitmap::SetTexelEnd(const Vector2 &vValue)
{
	m_vTexelEnd = vValue;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the handler of the material
*/
const MaterialHandler &SNBitmap::GetMaterialHandler()
{
	if (!m_bMaterial) {
		// Load material
		PLRenderer::Material *pMaterial = GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(m_sMaterial);
		m_cMaterial.SetResource(pMaterial);

		// Check whether this is a material or an effect, if not, we need to set a nice default billboard effect
		if (pMaterial) {
			const String sExtension = Url(pMaterial->GetName()).GetExtension();
			if (sExtension != "mat" && sExtension != "plfx") {
				// Set the billboard default effect
				PLRenderer::Material *pDefaultMaterial = GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(Material.GetDefault());
				if (pDefaultMaterial)
					pMaterial->SetEffect(pDefaultMaterial->GetEffect());
			}
		}
		m_bMaterial = true;
	}
	return m_cMaterial;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNBitmap::SNBitmap() :
	Material(this),
	Color(this),
	TexelStart(this),
	TexelEnd(this),
	Flags(this),
	m_sMaterial("Data/Effects/DefaultBitmap.plfx"),
	m_bMaterial(false),
	m_cColor(1.0f, 1.0f, 1.0f, 1.0f),
	m_vTexelEnd(1.0f, 1.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNBitmap::~SNBitmap()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
