/*********************************************************\
 *  File: SRPDeferredHDAO.cpp                            *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredHDAO.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDeferredHDAO)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredHDAO::SRPDeferredHDAO() :
	AORejectRadius(this),
	AOAcceptRadius(this),
	NormalScale(this),
	AcceptAngle(this),
	NumberOfRingGathers(this),
	NumberOfRings(this),
	Flags(this)
{
	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredHDAO::~SRPDeferredHDAO()
{
	// Destroy all used shaders
	DestroyShaders();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the fragment shader
*/
Shader *SRPDeferredHDAO::GetFragmentShader(Renderer &cRenderer, bool bUseNormal)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bUseNormal];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bUseNormal]) {
		const static String ShaderFilename = "Fragment/SRPDeferredHDAO.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bUseNormal) {
			sDefines += "#define USE_NORMAL\n";
			sName    += "[UseNormal]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			#include "SRPDeferredHDAO_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredHDAO_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredHDAO_Cg_FS, nNumOfBytes, false, ".cg");
			pShader = cRenderer.GetRendererContext().GetShaderManager().Load(sName, cFile, true, "glslf", sDefines); // We can't use for e.g. "arbfp1" because we're using loops heavily in here
		}
		cShaderHandler.SetResource(pShader);
		m_lstShaders.Add(new ShaderHandler())->SetResource(pShader);
		m_bFragmentShader[bUseNormal] = true;
	}

	// Return the shader
	return pShader;
}

/**
*  @brief
*    Destroys all currently used shaders
*/
void SRPDeferredHDAO::DestroyShaders()
{
	{
		Iterator<ShaderHandler*> cIterator = m_lstShaders.GetIterator();
		while (cIterator.HasNext()) {
			ShaderHandler *pShaderHandler = cIterator.Next();
			if (pShaderHandler->GetResource())
				delete pShaderHandler->GetResource();
			delete pShaderHandler;
		}
	}
	m_lstShaders.Clear();

	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}


//[-------------------------------------------------------]
//[ Protected virtual SRPDeferredSSAO functions           ]
//[-------------------------------------------------------]
void SRPDeferredHDAO::DrawAO(FullscreenQuad &cFullscreenQuad, TextureBufferRectangle &cNormalDepthTextureBuffer)
{
	// Get the renderer instance
	Renderer &cRenderer = cNormalDepthTextureBuffer.GetRenderer();

	// Get and set the fragment shader
	Shader *pFragmentShader = GetFragmentShader(cRenderer, !(GetFlags() & NoNormals));
	if (pFragmentShader && pFragmentShader->GetShaderProgram()) {
		// Get and set the fragment shader program
		ShaderProgram *pFragmentShaderProgram = pFragmentShader->GetShaderProgram();
		cRenderer.SetFragmentShaderProgram(pFragmentShaderProgram);

		{ // Set the texture buffer
			static const String sNormalDepthTexture = "NormalDepthTexture";
			const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sNormalDepthTexture, &cNormalDepthTextureBuffer);
			if (nStage >= 0) {
				cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Get the size of the texture buffer
		const Vector2i vSize = cNormalDepthTextureBuffer.GetSize();

		{ // Set fragment shader parameters
			{ // g_fHDAORejectRadius
				static const String g_fHDAORejectRadius = "g_fHDAORejectRadius";
				pFragmentShaderProgram->SetParameter1f(g_fHDAORejectRadius, AORejectRadius);
			}

			{ // Contrast
				static const String sContrast = "Contrast";
				pFragmentShaderProgram->SetParameter1f(sContrast, Contrast);
			}

			{ // g_fHDAOAcceptRadius
				static const String g_fHDAOAcceptRadius = "g_fHDAOAcceptRadius";
				pFragmentShaderProgram->SetParameter1f(g_fHDAOAcceptRadius, AOAcceptRadius);
			}

			// g_fNormalScale
			if (!(GetFlags() & NoNormals)) {
				static const String g_fNormalScale = "g_fNormalScale";
				pFragmentShaderProgram->SetParameter1f(g_fNormalScale, NormalScale);
			}

			{ // g_fAcceptAngle
				static const String g_fAcceptAngle = "g_fAcceptAngle";
				pFragmentShaderProgram->SetParameter1f(g_fAcceptAngle, AcceptAngle);
			}

			{ // iNumRingGathers
				uint32 nNumberOfRingGathers = NumberOfRingGathers;
				if (nNumberOfRingGathers < 1)
					nNumberOfRingGathers = 1;
				if (nNumberOfRingGathers > 20)
					nNumberOfRingGathers = 20;
				static const String iNumRingGathers = "iNumRingGathers";
				pFragmentShaderProgram->SetParameter1i(iNumRingGathers, nNumberOfRingGathers);
			}

			{ // iNumRings
				uint32 nNumberOfRings = NumberOfRings;
				if (nNumberOfRings < 1)
					nNumberOfRings = 1;
				if (nNumberOfRings > 4)
					nNumberOfRings = 4;
				static const String iNumRings = "iNumRings";
				pFragmentShaderProgram->SetParameter1i(iNumRings, nNumberOfRings);
			}

			// g_Resolution
			static const String g_Resolution = "g_Resolution";
			pFragmentShaderProgram->SetParameter2iv(g_Resolution, vSize);
		}

		// Draw the fullscreen quad
		cFullscreenQuad.Draw(vSize);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
