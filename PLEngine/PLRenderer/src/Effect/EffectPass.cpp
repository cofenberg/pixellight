/*********************************************************\
 *  File: EffectPass.cpp                                 *
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
#include "PLRenderer/Renderer/ShaderProgram.h"
#include "PLRenderer/Shader/ShaderManager.h"
#include "PLRenderer/Material/Parameter.h"
#include "PLRenderer/Material/ParameterManager.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Effect/EffectTechnique.h"
#include "PLRenderer/Effect/EffectPassLayer.h"
#include "PLRenderer/Effect/EffectPass.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner effect technique
*/
EffectTechnique &EffectPass::GetTechnique() const
{
	return *m_pTechnique;
}

/**
*  @brief
*    Returns the pass name
*/
String EffectPass::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Sets the pass name
*/
void EffectPass::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Binds the pass
*/
bool EffectPass::Bind(ParameterManager *pParameterManager) const
{
	// Get renderer
	Renderer &cRenderer = m_pTechnique->GetEffect().GetEffectManager().GetRendererContext().GetRenderer();

	// Set render states
	for (uint32 i=0; i<RenderState::ScissorTestEnable; i++)
		cRenderer.SetRenderState((RenderState::Enum)i, m_cRenderStates.Get((RenderState::Enum)i));

	// Fixed functions
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		// Set render states
		for (uint32 i=0; i<FixedFunctions::RenderState::Number; i++)
			pFixedFunctions->SetRenderState((FixedFunctions::RenderState::Enum)i, m_cFixedFunctionsRenderStates.Get((FixedFunctions::RenderState::Enum)i));
		pFixedFunctions->SetColor(m_cColor);

		// Set material states
		for (uint32 i=0; i<FixedFunctions::MaterialState::Number; i++)
			pFixedFunctions->SetMaterialState((FixedFunctions::MaterialState::Enum)i, m_nMaterialState[i]);
	}

	{ // Bind shaders
		if (!m_pVertexShader || !BindShader(*m_pVertexShader, pParameterManager))
			cRenderer.SetVertexShaderProgram();
		if (!m_pFragmentShader || !BindShader(*m_pFragmentShader, pParameterManager))
			cRenderer.SetFragmentShaderProgram();
	}

	{ // Setup textures
		uint32 i;

		if (m_lstLayers.GetNumOfElements()) {
			for (i=0; i<m_lstLayers.GetNumOfElements(); i++)
				m_lstLayers[i]->Bind(i, pParameterManager);
		} else {
			// Fixed functions
			if (pFixedFunctions)
				pFixedFunctions->SetTransformState(FixedFunctions::Transform::Texture0, Matrix4x4::Identity);
			i = 0;
		}
		for (; i<(signed)cRenderer.GetCapabilities().nMaxTextureUnits; i++) {
			cRenderer.SetTextureBuffer(i);

			// Set sampler states
			for (uint32 nState=0; nState<Sampler::Number; nState++)
				cRenderer.SetSamplerState(i, (Sampler::Enum)nState, cRenderer.GetDefaultSamplerState((Sampler::Enum)nState));

			// Fixed functions
			if (pFixedFunctions) {
				pFixedFunctions->SetTransformState(FixedFunctions::Transform::Enum(FixedFunctions::Transform::Texture0 + i), Matrix4x4::Identity);

				// Set texture stage states
				for (uint32 nState=0; nState<FixedFunctions::TextureStage::Number; nState++)
					pFixedFunctions->SetTextureStageState(i, (FixedFunctions::TextureStage::Enum)nState, pFixedFunctions->GetDefaultTextureStageState((FixedFunctions::TextureStage::Enum)nState));
			}
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Unbinds the pass to the renderer
*/
bool EffectPass::Unbind()
{
	// Unbind shaders
	if (m_pVertexShader)
		m_pVertexShader->Unbind();
	if (m_pFragmentShader)
		m_pFragmentShader->Unbind();

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
EffectPass &EffectPass::operator =(const EffectPass &cSource)
{
	// Copy pass name
	m_sName = cSource.GetName();

	// Copy general color
	m_cColor = cSource.m_cColor;

	// Copy render states
	m_cRenderStates = cSource.m_cRenderStates;

	// Copy material states
	for (uint32 i=0; i<FixedFunctions::MaterialState::Number; i++)
		m_nMaterialState[i] = cSource.GetMaterialState((FixedFunctions::MaterialState::Enum)i);

	// Layers
	for (uint32 i=0; i<m_lstLayers.GetNumOfElements(); i++)
		delete m_lstLayers[i];
	m_lstLayers.Clear();
	for (uint32 i=0; i<cSource.GetNumOfLayers(); i++) {
		EffectPassLayer *pFXPassLayer = new EffectPassLayer(*this);
		*pFXPassLayer = *cSource.GetLayer(i);
		m_lstLayers.Add(pFXPassLayer);
	}

	// Vertex shader
	if (cSource.GetVertexShader()) {
		if (!m_pVertexShader)
			m_pVertexShader = new ShaderHandler();
		m_pVertexShader->SetResource(cSource.GetVertexShader()->GetResource());
	} else {
		if (m_pVertexShader) {
			delete m_pVertexShader;
			m_pVertexShader = NULL;
		}
	}

	// Fragment shader
	if (cSource.GetFragmentShader()) {
		if (!m_pFragmentShader)
			m_pFragmentShader = new ShaderHandler();
		m_pFragmentShader->SetResource(cSource.GetFragmentShader()->GetResource());
	} else {
		if (m_pFragmentShader) {
			delete m_pFragmentShader;
			m_pFragmentShader = NULL;
		}
	}

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ States                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the general color
*/
const Color4 &EffectPass::GetColor() const
{
	return m_cColor;
}

/**
*  @brief
*    Sets the general color
*/
void EffectPass::SetColor(const Color4 &cColor)
{
	m_cColor = cColor;
}

/**
*  @brief
*    Returns the render states
*/
RenderStates &EffectPass::GetRenderStates()
{
	return m_cRenderStates;
}

const RenderStates &EffectPass::GetRenderStates() const
{
	return m_cRenderStates;
}

/**
*  @brief
*    Returns the fixed functions render states
*/
FixedFunctionsRenderStates &EffectPass::GetFixedFunctionsRenderStates()
{
	return m_cFixedFunctionsRenderStates;
}

const FixedFunctionsRenderStates &EffectPass::GetFixedFunctionsRenderStates() const
{
	return m_cFixedFunctionsRenderStates;
}

/**
*  @brief
*    Resets all material states to default
*/
void EffectPass::ResetMaterialStates()
{
	// Get renderer
	Renderer &cRenderer = m_pTechnique->GetEffect().GetEffectManager().GetRendererContext().GetRenderer();

	// Get the default material state settings
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		for (uint32 i=0; i<FixedFunctions::MaterialState::Number; i++)
			m_nMaterialState[i] = pFixedFunctions->GetDefaultMaterialState((FixedFunctions::MaterialState::Enum)i);
	} else {
		for (uint32 i=0; i<FixedFunctions::MaterialState::Number; i++)
			m_nMaterialState[i] = 0;
	}
}

/**
*  @brief
*    Retrieves a material-state value
*/
uint32 EffectPass::GetMaterialState(FixedFunctions::MaterialState::Enum nState) const
{
	// Check if the state is a value renderer material state member
	return (nState < FixedFunctions::MaterialState::Number) ? m_nMaterialState[nState] : 0;
}

/**
*  @brief
*    Sets a single material-state parameter
*/
bool EffectPass::SetMaterialState(FixedFunctions::MaterialState::Enum nState, uint32 nValue)
{
	// Check if the state is a value renderer material state member
	if (nState >= FixedFunctions::MaterialState::Number)
		return false; // Error!

	// Set material state value
	m_nMaterialState[nState] = nValue;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Layers                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of texture layers
*/
uint32 EffectPass::GetNumOfLayers() const
{
	return m_lstLayers.GetNumOfElements();
}

/**
*  @brief
*    Adds a new layer
*/
EffectPassLayer *EffectPass::AddLayer()
{
	EffectPassLayer *ppFXPassLayer = new EffectPassLayer(*this);
	m_lstLayers.Add(ppFXPassLayer);
	return ppFXPassLayer;
}

/**
*  @brief
*    Returns a layer
*/
EffectPassLayer *EffectPass::GetLayer(uint32 nIndex) const
{
	return m_lstLayers[nIndex];
}

/**
*  @brief
*    Removes a layer
*/
bool EffectPass::RemoveLayer(uint32 nIndex)
{
	EffectPassLayer *pEffectPassLayer = m_lstLayers[nIndex];
	if (!pEffectPassLayer)
		return false; // Error!
	delete pEffectPassLayer;
	m_lstLayers.RemoveAtIndex(nIndex);

	// Done
	return true;
}

/**
*  @brief
*    Removes all layers
*/
void EffectPass::RemoveAllLayers()
{
	// Delete layers
	for (uint32 i=0; i<m_lstLayers.GetNumOfElements(); i++)
		delete m_lstLayers[i];
	m_lstLayers.Clear();
}


//[-------------------------------------------------------]
//[ Shaders                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads a vertex shader
*/
bool EffectPass::LoadVertexShader(const String &sFilename, const String &sProfile)
{
	// Check parameters
	if (sFilename.GetLength()) {
		// Destroy old shader
		if (!m_pVertexShader) {
			delete m_pVertexShader;
			m_pVertexShader = NULL;
		}

		// Load shader
		Shader *pShader = m_pTechnique->GetEffect().GetEffectManager().GetRendererContext().GetShaderManager().Load(sFilename, sFilename, sProfile);
		if (pShader) {
			m_pVertexShader = new ShaderHandler();
			m_pVertexShader->SetResource(pShader);

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Unloads the vertex shader
*/
void EffectPass::UnloadVertexShader()
{
	if (m_pVertexShader) {
		delete m_pVertexShader;
		m_pVertexShader = NULL;
	}
}

/**
*  @brief
*    Gets the vertex shader
*/
ShaderHandler *EffectPass::GetVertexShader() const
{
	return m_pVertexShader;
}

/**
*  @brief
*    Sets the vertex shader
*/
void EffectPass::SetVertexShader(Shader *pShader)
{
	if (!m_pVertexShader)
		m_pVertexShader = new ShaderHandler();
	m_pVertexShader->SetResource(pShader);
}

/**
*  @brief
*    Loads a fragment shader
*/
bool EffectPass::LoadFragmentShader(const String &sFilename, const String &sProfile)
{
	// Check parameters
	if (sFilename.GetLength()) {
		// Destroy old shader
		if (!m_pFragmentShader) {
			delete m_pFragmentShader;
			m_pFragmentShader = NULL;
		}

		// Load shader
		Shader *pShader = m_pTechnique->GetEffect().GetEffectManager().GetRendererContext().GetShaderManager().Load(sFilename + "+", sFilename + "+", sProfile);
		if (pShader) {
			m_pFragmentShader = new ShaderHandler();
			m_pFragmentShader->SetResource(pShader);

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Unloads the fragment shader
*/
void EffectPass::UnloadFragmentShader()
{
	if (m_pFragmentShader) {
		delete m_pFragmentShader;
		m_pFragmentShader = NULL;
	}
}

/**
*  @brief
*    Gets the fragment shader
*/
ShaderHandler *EffectPass::GetFragmentShader() const
{
	return m_pFragmentShader;
}

/**
*  @brief
*    Sets the fragment shader
*/
void EffectPass::SetFragmentShader(Shader *pShader)
{
	if (!m_pFragmentShader)
		m_pFragmentShader = new ShaderHandler();
	m_pFragmentShader->SetResource(pShader);
}

/**
*  @brief
*    Binds a shader
*/
bool EffectPass::BindShader(const ShaderHandler &cShaderHandler, ParameterManager *pParameterManager) const
{
	// Check parameter
	if (cShaderHandler.GetResource()) {
		// Get shader program
		ShaderProgram *pShaderProgram = cShaderHandler.GetResource()->GetShaderProgram();
		if (pShaderProgram) {
			// Bind shader
			cShaderHandler.Bind();

			// Set shader parameters
			if (pParameterManager) {
				// First, use the given parameter manager
				for (uint32 i=0; i<pParameterManager->GetNumOfParameters(); i++) {
					// Get parameter
					const Parameter *pParameter = pParameterManager->GetParameter(i);
					if (pParameter && pParameter->GetType() != Parameters::TextureBuffer) {
						// Is this a valid shader parameter?
						const String sName = pParameter->GetName();
						if (pShaderProgram->IsParameter(sName))
							pParameter->SetManagerParameterValue(*pShaderProgram, sName);
					}
				}

				// Use the effect parameters if not already set by the given parameter manager
				const uint32 nNumOfParameters = GetTechnique().GetEffect().GetParameterManager().GetNumOfParameters();
				for (uint32 i=0; i<nNumOfParameters; i++) {
					// Get parameter, ignore texture buffer parameters
					const Parameter *pParameter = GetTechnique().GetEffect().GetParameterManager().GetParameter(i);
					if (pParameter && pParameter->GetType() != Parameters::TextureBuffer) {
						// Already set by the given parameter manager?
						const String sName = pParameter->GetName();
						if (!pParameterManager->IsParameter(sName)) {
							// Is this a valid shader parameter?
							if (pShaderProgram->IsParameter(sName))
								pParameter->SetManagerParameterValue(*pShaderProgram, sName);
						}
					}
				}
			} else {
				const uint32 nNumOfParameters = GetTechnique().GetEffect().GetParameterManager().GetNumOfParameters();
				for (uint32 i=0; i<nNumOfParameters; i++) {
					// Get parameter
					const Parameter *pParameter = GetTechnique().GetEffect().GetParameterManager().GetParameter(i);
					if (pParameter && pParameter->GetType() != Parameters::TextureBuffer) {
						// Is this a valid shader parameter?
						const String sName = pParameter->GetName();
						if (pShaderProgram->IsParameter(sName))
							pParameter->SetManagerParameterValue(*pShaderProgram, sName);
					}
				}
			}

			// Done
			return true;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
EffectPass::EffectPass(EffectTechnique &cTechnique) :
	m_pTechnique(&cTechnique),
	m_sName("Pass"),
	m_cColor(Color4::White),
	m_pVertexShader(NULL),
	m_pFragmentShader(NULL)
{
	ResetMaterialStates();
}

/**
*  @brief
*    Destructor
*/
EffectPass::~EffectPass()
{
	// Remove all layers
	RemoveAllLayers();

	// Delete shaders
	if (m_pVertexShader)
		delete m_pVertexShader;
	if (m_pFragmentShader)
		delete m_pFragmentShader;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
