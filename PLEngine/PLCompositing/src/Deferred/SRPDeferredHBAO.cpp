/*********************************************************\
 *  File: SRPDeferredHBAO.cpp                            *
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
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/ShaderProgram.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Texture/TextureManager.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include "PLCompositing/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Deferred/SRPDeferredHBAO.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPDeferredHBAO)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
uint32 SRPDeferredHBAO::GetNumberOfDirections() const
{
	return m_nNumberOfDirections;
}

void SRPDeferredHBAO::SetNumberOfDirections(uint32 nValue)
{
	if (m_nNumberOfDirections != nValue) {
		m_nNumberOfDirections = nValue;

		// Destroy the random normals texture because it is now out-of-date
		if (m_pRandomNormalsTexture) {
			delete m_pRandomNormalsTexture;
			m_pRandomNormalsTexture = NULL;
		}
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredHBAO::SRPDeferredHBAO() :
	NumberOfSteps(this),
	NumberOfDirections(this),
	AORadius(this),
	AngleBias(this),
	Attenuation(this),
	RandomUVScale(this),
	Flags(this),
	m_nNumberOfDirections(8),
	m_pRandomNormalsTexture(NULL)
{
	// Init shader handler data
	MemoryManager::Set(m_bFragmentShader, 0, sizeof(m_bFragmentShader));
}

/**
*  @brief
*    Destructor
*/
SRPDeferredHBAO::~SRPDeferredHBAO()
{
	// Destroy all used shaders
	DestroyShaders();

	// Destroy the random normals texture
	if (m_pRandomNormalsTexture)
		delete m_pRandomNormalsTexture;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the fragment shader
*/
Shader *SRPDeferredHBAO::GetFragmentShader(Renderer &cRenderer, bool bUseNormal)
{
	// Get/construct the shader
	ShaderHandler &cShaderHandler = m_cFragmentShader[bUseNormal];
	Shader *pShader = cShaderHandler.GetResource();
	if (!pShader && !m_bFragmentShader[bUseNormal]) {
		const static String ShaderFilename = "Fragment/SRPDeferredHBAO.cg";

		// Get defines string and a readable shader name (we MUST choose a new name!)
		String sDefines, sName = ShaderFilename + '_';
		if (bUseNormal) {
			sDefines += "#define USE_NORMAL\n";
			sName    += "[UseNormal]";
		}
		if (!sDefines.GetLength())
			sName += "[NoDefines]";

		{ // Load the shader
			#include "SRPDeferredHBAO_Cg.h"
			static uint32 nNumOfBytes = Wrapper::GetStringLength(pszDeferredHBAO_Cg_FS) + 1; // +1 for the terminating NULL (\0) to be 'correct'
			File cFile((uint8*)pszDeferredHBAO_Cg_FS, nNumOfBytes, false, ".cg");
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
void SRPDeferredHBAO::DestroyShaders()
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
void SRPDeferredHBAO::DrawAO(FullscreenQuad &cFullscreenQuad, TextureBufferRectangle &cNormalDepthTextureBuffer)
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

		// Get the width and height of the texture buffer
		const float fWidth  = (float)cNormalDepthTextureBuffer.GetSize().x;
		const float fHeight = (float)cNormalDepthTextureBuffer.GetSize().y;

		{ // Set fragment shader parameters
			// g_NumSteps
			static const String g_NumSteps = "g_NumSteps";
			pFragmentShaderProgram->SetParameter1i(g_NumSteps, NumberOfSteps);

			// g_NumDir
			static const String g_NumDir = "g_NumDir";
			pFragmentShaderProgram->SetParameter1i(g_NumDir, m_nNumberOfDirections);

			{ // Radius
				// Calculate the radius to use
				const float fRadius = SceneScale * AORadius;

				// g_R
				static const String g_R = "g_R";
				pFragmentShaderProgram->SetParameter1f(g_R, fRadius);

				// g_inv_R
				static const String g_inv_R = "g_inv_R";
				pFragmentShaderProgram->SetParameter1f(g_inv_R, 1.0f/fRadius);

				// g_sqr_R
				static const String g_sqr_R = "g_sqr_R";
				pFragmentShaderProgram->SetParameter1f(g_sqr_R, fRadius*fRadius);
			}

			{ // Angle bias and contrast
				// Calculate the angle in radians
				const float fAngle = float(AngleBias * Math::DegToRad);

				// g_AngleBias
				static const String g_AngleBias = "g_AngleBias";
				pFragmentShaderProgram->SetParameter1f(g_AngleBias, fAngle);

				// g_TanAngleBias
				static const String g_TanAngleBias = "g_TanAngleBias";
				pFragmentShaderProgram->SetParameter1f(g_TanAngleBias, Math::Tan(fAngle));

				// g_Contrast
				static const String g_Contrast = "g_Contrast";
				const float fContrast = Contrast / (1.0f - Math::Sin(fAngle));
				pFragmentShaderProgram->SetParameter1f(g_Contrast, fContrast);
			}

			// g_Attenuation
			static const String g_Attenuation = "g_Attenuation";
			pFragmentShaderProgram->SetParameter1f(g_Attenuation, Attenuation);

			{ // Focal length
				// Calculate the focal length
				const float fFovY         = float((SNCamera::GetCamera() ? SNCamera::GetCamera()->GetFOV() : 45.0f) * Math::DegToRad);
				const float fFocalLengthY = 1.0f / Math::Tan(fFovY * 0.5f);
				const float fFocalLengthX = fFocalLengthY * ((fHeight * (SNCamera::GetCamera() ? SNCamera::GetCamera()->GetAspect() : 1.0f)) / fWidth);

				// g_FocalLen
				static const String g_FocalLen = "g_FocalLen";
				pFragmentShaderProgram->SetParameter2f(g_FocalLen, fFocalLengthX, fFocalLengthY);

				// g_InvFocalLen
				static const String g_InvFocalLen = "g_InvFocalLen";
				pFragmentShaderProgram->SetParameter2f(g_InvFocalLen, 1.0f/fFocalLengthX, 1.0f/fFocalLengthY);
			}

			// g_Resolution
			static const String g_Resolution = "g_Resolution";
			pFragmentShaderProgram->SetParameter2f(g_Resolution, fWidth, fHeight);

			// g_InvResolution
			static const String g_InvResolution = "g_InvResolution";
			pFragmentShaderProgram->SetParameter2f(g_InvResolution, 1.0f/fWidth, 1.0f/fHeight);

			// RandomUVScale
			static const String sRandomUVScale = "RandomUVScale";
			pFragmentShaderProgram->SetParameter2fv(sRandomUVScale, RandomUVScale.Get());
		}

		{ // Set the "RandomNormalsTexture" fragment shader parameter
			// Create texture if required
			if (!m_pRandomNormalsTexture) {
				const uint32 nWidth  = 64;
				const uint32 nHeight = 64;

				// Create the image
				Image cImage;
				ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
				pImageBuffer->CreateImage(DataFloat, ColorRGBA, Vector3i(nWidth, nHeight, 1));

				// Create the texture data
				float *pfData = (float*)pImageBuffer->GetData();
				for (int i=0; i<64*64*4; i+=4) {
					const float fAngle = float(2.0f*Math::Pi*Math::GetRandFloat()/(float)m_nNumberOfDirections);
					pfData[i  ] = Math::Cos(fAngle);
					pfData[i+1] = Math::Sin(fAngle);
					pfData[i+2] = Math::GetRandFloat();
					pfData[i+3] = 0.0f;
				}

				// Create the texture
				m_pRandomNormalsTexture = cRenderer.CreateTextureBuffer2D(cImage, TextureBuffer::Unknown, 0);
			}

			{ // Set texture
				static const String sRandomNormalsTexture = "RandomNormalsTexture";
				const int nStage = pFragmentShaderProgram->SetParameterTextureBuffer(sRandomNormalsTexture, m_pRandomNormalsTexture);
				if (nStage >= 0) {
					cRenderer.SetSamplerState(nStage, Sampler::AddressU, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nStage, Sampler::AddressV, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
					cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
					cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
				}
			}
		}

		// Draw the fullscreen quad
		cFullscreenQuad.Draw(Vector2i::One);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
