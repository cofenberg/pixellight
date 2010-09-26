/*********************************************************\
 *  File: EffectPassLayer.cpp                            *
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
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Renderer/Program.h"
#include "PLRenderer/Renderer/ProgramUniform.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Texture/TextureHandler.h"
#include "PLRenderer/Material/Parameter.h"
#include "PLRenderer/Material/ParameterManager.h"
#include "PLRenderer/Effect/Effect.h"
#include "PLRenderer/Effect/EffectPass.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Effect/EffectTechnique.h"
#include "PLRenderer/Effect/EffectPassLayer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the layer owner
*/
EffectPass &EffectPassLayer::GetPass() const
{
	return *m_pFXPass;
}

/**
*  @brief
*    Makes the texture buffer of the texture handlers texture to the current renderer texture buffer
*/
bool EffectPassLayer::Bind(uint32 nStage, ParameterManager *pParameterManager) const
{
	// Get effect
	Effect &cEffect = m_pFXPass->GetTechnique().GetEffect();

	// Get renderer
	Renderer &cRenderer = cEffect.GetEffectManager().GetRendererContext().GetRenderer();

	// Bind texture
	if (!pParameterManager || !BindTexture(pParameterManager->GetParameter(m_sTexture), nStage))
		BindTexture(cEffect.GetParameterManager().GetParameter(m_sTexture), nStage);

	// Set sampler states
	for (uint32 i=0; i<Sampler::Number; i++)
		cRenderer.SetSamplerState(nStage, (Sampler::Enum)i, m_cSamplerStates.Get((Sampler::Enum)i));

	// Fixed functions
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		// Set texture stage states
		for (uint32 i=0; i<FixedFunctions::TextureStage::Number; i++)
			pFixedFunctions->SetTextureStageState(nStage, (FixedFunctions::TextureStage::Enum)i, m_cFixedFunctionsTextureStageStates.Get((FixedFunctions::TextureStage::Enum)i));
	}

	// Done
	return true;
}

/**
*  @brief
*    Returns the name of the used texture parameter
*/
String EffectPassLayer::GetTexture() const
{
	return m_sTexture;
}

/**
*  @brief
*    Sets the name of the used texture parameter
*/
void EffectPassLayer::SetTexture(const String &sTexture)
{
	m_sTexture = sTexture;
}

/**
*  @brief
*    Returns the sampler states
*/
SamplerStates &EffectPassLayer::GetSamplerStates()
{
	return m_cSamplerStates;
}

const SamplerStates &EffectPassLayer::GetSamplerStates() const
{
	return m_cSamplerStates;
}

/**
*  @brief
*    Returns the fixed functions texture stage states
*/
FixedFunctionsTextureStageStates &EffectPassLayer::GetFixedFunctionsTextureStageStates()
{
	return m_cFixedFunctionsTextureStageStates;
}

const FixedFunctionsTextureStageStates &EffectPassLayer::GetFixedFunctionsTextureStageStates() const
{
	return m_cFixedFunctionsTextureStageStates;
}

/**
*  @brief
*    Copy operator
*/
EffectPassLayer &EffectPassLayer::operator =(const EffectPassLayer &cSource)
{
	// Texture
	m_sTexture = cSource.m_sTexture;

	// Copy states
	m_cSamplerStates				    = cSource.m_cSamplerStates;
	m_cFixedFunctionsTextureStageStates = cSource.m_cFixedFunctionsTextureStageStates;

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
EffectPassLayer::EffectPassLayer(EffectPass &cFXPass) :
	m_pFXPass(&cFXPass)
{
}

/**
*  @brief
*    Destructor
*/
EffectPassLayer::~EffectPassLayer()
{
}

/**
*  @brief
*    Binds a texture
*/
bool EffectPassLayer::BindTexture(const Parameter *pParameter, uint32 nStage) const
{
	// Check parameter
	if (pParameter && pParameter->GetType() == Parameters::TextureBuffer) {
		// Get texture
		const TextureHandler *pTextureHandler = pParameter->GetValueTextureHandler();
		if (pTextureHandler) {
			const Texture *pTexture = pTextureHandler->GetTexture();
			bool bResult = true; // No error by default
			if (!pTexture) {
				// Use the default texture to avoid ugly graphics...
				pTexture = m_pFXPass->GetTechnique().GetEffect().GetEffectManager().GetRendererContext().GetTextureManager().GetStandard();
				if (!pTexture)
					return false; // Error! :(

				// Error!
				bResult = false;
			}
			TextureBuffer *pTextureBuffer = pTexture->GetTextureBuffer();
			if (pTextureBuffer) {
				{ // Set the GPU program uniform
					Program *pProgram = m_pFXPass->GetProgram();
					if (pProgram) {
						ProgramUniform *pProgramUniform = pProgram->GetUniform(pParameter->GetName());
						if (pProgramUniform && pProgramUniform->Set(pTextureBuffer) > -1) {
							// Done
							return bResult;
						}
					}
				}
				if (bResult)
					pTextureHandler->Bind(nStage);
				else {
					// Bind the fallback texture
					pTexture->Bind(nStage);

					// Fixed functions
					FixedFunctions *pFixedFunctions = pTextureBuffer->GetRenderer().GetFixedFunctions();
					if (pFixedFunctions) {
						// Set identity texture matrix
						pFixedFunctions->SetTransformState((FixedFunctions::Transform::Enum)(FixedFunctions::Transform::Texture0 + nStage), Matrix4x4::Identity);
					}
				}

				// Done
				return bResult;
			}
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
