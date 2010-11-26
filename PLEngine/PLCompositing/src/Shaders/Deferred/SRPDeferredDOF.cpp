/*********************************************************\
 *  File: SRPDeferredDOF.cpp                             *
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
#include <float.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLScene/Compositing/FullscreenQuad.h>
#include <PLScene/Compositing/General/SRPBegin.h>
#include "PLCompositing/Shaders/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Shaders/Deferred/SRPDeferredDOF.h"


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
pl_implement_class(SRPDeferredDOF)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPDeferredDOF::SRPDeferredDOF() :
	EventHandlerDirty(&SRPDeferredDOF::OnDirty, this),
	ShaderLanguage(this),
	EffectWeight(this),
	NearPlaneDepth(this),
	FocalPlaneDepth(this),
	FarPlaneDepth(this),
	BlurrinessCutoff(this),
	BlurPasses(this),
	BlurDownscale(this),
	Flags(this),
	m_bResultIndex(0),
	m_pVertexShader(NULL),
	m_pDepthBlurFragmentShader(NULL),
	m_pDepthBlurProgram(NULL),
	m_pDepthBlurPositionProgramAttribute(NULL),
	m_pDepthBlurTextureSizeProgramUniform(NULL),
	m_pDepthBlurDOFParamsProgramUniform(NULL),
	m_pDepthBlurRGBTextureProgramUniform(NULL),
	m_pDepthBlurNormalDepthTextureProgramUniform(NULL),
	m_pDownscaleFragmentShader(NULL),
	m_pDownscaleProgram(NULL),
	m_pDownscalePositionProgramAttribute(NULL),
	m_pDownscaleTextureSizeProgramUniform(NULL),
	m_pDownscaleTextureProgramUniform(NULL),
	m_pBlurFragmentShader(NULL),
	m_pBlurProgram(NULL),
	m_pBlurPositionProgramAttribute(NULL),
	m_pBlurTextureSizeProgramUniform(NULL),
	m_pBlurUVScaleProgramUniform(NULL),
	m_pBlurTextureProgramUniform(NULL),
	m_pResultFragmentShader(NULL),
	m_pResultProgram(NULL),
	m_pResultPositionProgramAttribute(NULL),
	m_pResultTextureSizeProgramUniform(NULL),
	m_pResultEffectWeightProgramUniform(NULL),
	m_pResultBlurDownscaleProgramUniform(NULL),
	m_pResultBlurTextureProgramUniform(NULL),
	m_pResultTextureProgramUniform(NULL),
	m_pDebugFragmentShader(NULL),
	m_pDebugProgram(NULL),
	m_pDebugPositionProgramAttribute(NULL),
	m_pDebugTextureSizeProgramUniform(NULL),
	m_pDebugTextureProgramUniform(NULL),
	m_nDebugType(0)
{
	// Init data
	m_pRenderTarget[0] = m_pRenderTarget[1] = NULL;
}

/**
*  @brief
*    Destructor
*/
SRPDeferredDOF::~SRPDeferredDOF()
{
	// Destroy the render targets
	for (int i=0; i<2; i++) {
		if (m_pRenderTarget[i])
			delete m_pRenderTarget[i];
	}

	// Destroy the depth blur stuff
	if (m_pDepthBlurProgram)
		delete m_pDepthBlurProgram;
	if (m_pDepthBlurFragmentShader)
		delete m_pDepthBlurFragmentShader;

	// Destroy the downscale stuff
	if (m_pDownscaleProgram)
		delete m_pDownscaleProgram;
	if (m_pDownscaleFragmentShader)
		delete m_pDownscaleFragmentShader;

	// Destroy the blur stuff
	if (m_pBlurProgram)
		delete m_pBlurProgram;
	if (m_pBlurFragmentShader)
		delete m_pBlurFragmentShader;

	// Destroy the result stuff
	if (m_pResultProgram)
		delete m_pResultProgram;
	if (m_pResultFragmentShader)
		delete m_pResultFragmentShader;

	// Destroy the debug stuff
	if (m_pDebugProgram)
		delete m_pDebugProgram;
	if (m_pDebugFragmentShader)
		delete m_pDebugFragmentShader;

	// Destroy the vertex shader
	if (m_pVertexShader)
		delete m_pVertexShader;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Calculates the depth blur
*/
void SRPDeferredDOF::CalculateDepthBlur(const String &sShaderLanguage, VertexBuffer &cVertexBuffer, TextureBufferRectangle &cRGBTexture,
										TextureBufferRectangle &cNormalDepthTexture, float fNearPlaneDepth, float fFocalPlaneDepth, float fFarPlaneDepth, float fBlurrinessCutoff)
{
	// Get the renderer instance
	Renderer &cRenderer = cRGBTexture.GetRenderer();

	// Create the shaders and programs right now?
	if (!m_pVertexShader || m_pVertexShader->GetShaderLanguage() != sShaderLanguage) {
		// If there's an previous instance of the program, destroy it first
		if (m_pDepthBlurProgram) {
			delete m_pDepthBlurProgram;
			m_pDepthBlurProgram = NULL;
		}
		if (m_pDepthBlurFragmentShader) {
			delete m_pDepthBlurFragmentShader;
			m_pDepthBlurFragmentShader = NULL;
		}
		if (m_pVertexShader) {
			delete m_pVertexShader;
			m_pVertexShader = NULL;
		}
		m_pDepthBlurPositionProgramAttribute			= NULL;
		m_pDepthBlurTextureSizeProgramUniform			= NULL;
		m_pDepthBlurDOFParamsProgramUniform				= NULL;
		m_pDepthBlurRGBTextureProgramUniform			= NULL;
		m_pDepthBlurNormalDepthTextureProgramUniform	= NULL;

		// Get the shader language instance
		PLRenderer::ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(sShaderLanguage);
		if (pShaderLanguage) {
			// Shader source code
			String sVertexShaderSourceCode;
			String sFragmentShaderSourceCode;
			if (sShaderLanguage == "GLSL") {
				#include "SRPDeferredDOF_GLSL.h"
				sVertexShaderSourceCode	  = sDeferredDOF_GLSL_VS;
				sFragmentShaderSourceCode = sDeferredDOF_GLSL_FS_DepthBlur;
			} else if (sShaderLanguage == "Cg") {
				#include "SRPDeferredDOF_Cg.h"
				sVertexShaderSourceCode	  = sDeferredDOF_Cg_VS;
				sFragmentShaderSourceCode = sDeferredDOF_Cg_FS_DepthBlur;
			}

			// Create a vertex shader instance
			m_pVertexShader = pShaderLanguage->CreateVertexShader();
			if (m_pVertexShader) {
				// Set the vertex shader source code
				m_pVertexShader->SetSourceCode(sVertexShaderSourceCode);
			}

			// Create a fragment shader instance
			m_pDepthBlurFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pDepthBlurFragmentShader) {
				// Set the fragment shader source code
				m_pDepthBlurFragmentShader->SetSourceCode(sFragmentShaderSourceCode);
			}

			// Create a program instance
			m_pDepthBlurProgram = pShaderLanguage->CreateProgram();
			if (m_pDepthBlurProgram) {
				// Assign the created vertex and fragment shaders to the program
				m_pDepthBlurProgram->SetVertexShader(m_pVertexShader);
				m_pDepthBlurProgram->SetFragmentShader(m_pDepthBlurFragmentShader);

				// Add our nark which will inform us as soon as the program gets dirty
				m_pDepthBlurProgram->EventDirty.Connect(&EventHandlerDirty);

				// Get attributes and uniforms
				OnDirty(m_pDepthBlurProgram);
			}
		}
	}

	// Make the depth blur GPU program to the currently used one
	if (cRenderer.SetProgram(m_pDepthBlurProgram)) {
		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		if (m_pDepthBlurPositionProgramAttribute)
			m_pDepthBlurPositionProgramAttribute->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);

		// Set the "TextureSize" fragment shader parameter
		if (m_pDepthBlurTextureSizeProgramUniform)
			m_pDepthBlurTextureSizeProgramUniform->Set(cRGBTexture.GetSize());

		// Set the "DOFParams" fragment shader parameter and ensure that all values are correct
		if (m_pDepthBlurDOFParamsProgramUniform) {
			// fFocalPlaneDepth - fNearPlaneDepth is not allowed to be 0!
			if (fNearPlaneDepth > fFocalPlaneDepth)
				fNearPlaneDepth = fFocalPlaneDepth;
			if (fFocalPlaneDepth - fNearPlaneDepth < FLT_MIN)
				fNearPlaneDepth -= FLT_MIN;

			// fFarPlaneDepth - fFocalPlaneDepth is not allowed to be 0!
			if (fFarPlaneDepth < fFocalPlaneDepth)
				fFarPlaneDepth = fFocalPlaneDepth;
			if (fFarPlaneDepth - fFocalPlaneDepth < FLT_MIN)
				fFarPlaneDepth += FLT_MIN;

			// Set parameters
			m_pDepthBlurDOFParamsProgramUniform->Set(fNearPlaneDepth, fFocalPlaneDepth, fFarPlaneDepth, fBlurrinessCutoff);
		}

		// Set the "RGBTexture" fragment shader parameter
		if (m_pDepthBlurRGBTextureProgramUniform) {
			const int nTextureUnit = m_pDepthBlurRGBTextureProgramUniform->Set(&cRGBTexture);
			if (nTextureUnit >= 0) {
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Set the "NormalDepthTexture" fragment shader parameter
		if (m_pDepthBlurNormalDepthTextureProgramUniform) {
			const int nTextureUnit = m_pDepthBlurNormalDepthTextureProgramUniform->Set(&cNormalDepthTexture);
			if (nTextureUnit >= 0) {
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Draw the fullscreen quad
		cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
	}
}

/**
*  @brief
*    Calculates the blur
*/
void SRPDeferredDOF::CalculateBlur(const String &sShaderLanguage, VertexBuffer &cVertexBuffer, TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, uint32 nBlurPasses, float fDownscale)
{
	// Get the internal texture format to use
	const TextureBuffer::EPixelFormat nInternalFormat = cOriginalTexture.GetFormat();

	// Get the renderer instance
	Renderer &cRenderer = cOriginalTexture.GetRenderer();

	{ // Create/update the two render targets
		// Get the size of the original HDR texture
		const Vector2i vRTSize = cOriginalTexture.GetSize()/fDownscale;
		if (vRTSize.x != 0 && vRTSize.y != 0) {
			for (int i=0; i<2; i++) {
				// Render target size change?
				if (m_pRenderTarget[i] && (m_pRenderTarget[i]->GetSize() != vRTSize || m_pRenderTarget[i]->GetFormat() != nInternalFormat)) {
					// Destroy the downscale render target
					if (m_pRenderTarget[i]) {
						delete m_pRenderTarget[i];
						m_pRenderTarget[i] = NULL;
					}
				}

				// Create the downscale render target right now?
				if (!m_pRenderTarget[i])
					m_pRenderTarget[i] = cRenderer.CreateSurfaceTextureBufferRectangle(vRTSize, nInternalFormat, SurfaceTextureBuffer::NoMultisampleAntialiasing);
			}
		}
	}

	// Create the shaders and programs right now?
	if (!m_pDownscaleFragmentShader || m_pDownscaleFragmentShader->GetShaderLanguage() != sShaderLanguage) {
		// If there's an previous instance of the program, destroy it first
		if (m_pDownscaleProgram) {
			delete m_pDownscaleProgram;
			m_pDownscaleProgram = NULL;
		}
		if (m_pDownscaleFragmentShader) {
			delete m_pDownscaleFragmentShader;
			m_pDownscaleFragmentShader = NULL;
		}
		if (m_pBlurProgram) {
			delete m_pBlurProgram;
			m_pBlurProgram = NULL;
		}
		if (m_pBlurFragmentShader) {
			delete m_pBlurFragmentShader;
			m_pBlurFragmentShader = NULL;
		}
		m_pDownscalePositionProgramAttribute	= NULL;
		m_pDownscaleTextureSizeProgramUniform	= NULL;
		m_pDownscaleTextureProgramUniform		= NULL;
		m_pBlurPositionProgramAttribute			= NULL;
		m_pBlurTextureSizeProgramUniform		= NULL;
		m_pBlurUVScaleProgramUniform			= NULL;
		m_pBlurTextureProgramUniform			= NULL;

		// Get the shader language instance
		PLRenderer::ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(sShaderLanguage);
		if (pShaderLanguage) {
			// Shader source code
			String sVertexShaderSourceCode;
			String sFragmentShaderSourceCode_Downscale;
			String sFragmentShaderSourceCode_Blur;
			if (sShaderLanguage == "GLSL") {
				#include "SRPDeferredDOF_GLSL.h"
				sVertexShaderSourceCode				= sDeferredDOF_GLSL_VS;
				sFragmentShaderSourceCode_Downscale	= sDeferredDOF_GLSL_FS_Downscale;
				sFragmentShaderSourceCode_Blur		= sDeferredDOF_GLSL_FS_Blur;
			} else if (sShaderLanguage == "Cg") {
				#include "SRPDeferredDOF_Cg.h"
				sVertexShaderSourceCode				= sDeferredDOF_Cg_VS;
				sFragmentShaderSourceCode_Downscale = sDeferredDOF_Cg_FS_Downscale;
				sFragmentShaderSourceCode_Blur		= sDeferredDOF_Cg_FS_Blur;
			}

			// Create a fragment shader instance
			m_pDownscaleFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pDownscaleFragmentShader) {
				// Set the fragment shader source code
				m_pDownscaleFragmentShader->SetSourceCode(sFragmentShaderSourceCode_Downscale);
			}
			m_pBlurFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pBlurFragmentShader) {
				// Set the fragment shader source code
				m_pBlurFragmentShader->SetSourceCode(sFragmentShaderSourceCode_Blur);
			}

			// Create a program instance
			m_pDownscaleProgram = pShaderLanguage->CreateProgram();
			if (m_pDownscaleProgram) {
				// Assign the created vertex and fragment shaders to the program
				m_pDownscaleProgram->SetVertexShader(m_pVertexShader);
				m_pDownscaleProgram->SetFragmentShader(m_pDownscaleFragmentShader);

				// Add our nark which will inform us as soon as the program gets dirty
				m_pDownscaleProgram->EventDirty.Connect(&EventHandlerDirty);

				// Get attributes and uniforms
				OnDirty(m_pDownscaleProgram);
			}
			m_pBlurProgram = pShaderLanguage->CreateProgram();
			if (m_pBlurProgram) {
				// Assign the created vertex and fragment shaders to the program
				m_pBlurProgram->SetVertexShader(m_pVertexShader);
				m_pBlurProgram->SetFragmentShader(m_pBlurFragmentShader);

				// Add our nark which will inform us as soon as the program gets dirty
				m_pBlurProgram->EventDirty.Connect(&EventHandlerDirty);

				// Get attributes and uniforms
				OnDirty(m_pBlurProgram);
			}
		}
	}

	// First step: Downscale -> Make the downscale GPU program to the currently used one
	if (cRenderer.SetProgram(m_pDownscaleProgram)) {
		// Make the render target 0 to the current render target
		cRenderer.SetRenderTarget(m_pRenderTarget[0]);
		m_bResultIndex = 0;

		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		if (m_pDownscalePositionProgramAttribute)
			m_pDownscalePositionProgramAttribute->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);

		// Set the "TextureSize" fragment shader parameter
		if (m_pDownscaleTextureSizeProgramUniform)
			m_pDownscaleTextureSizeProgramUniform->Set(cOriginalTexture.GetSize());

		// Set the "Texture" fragment shader parameter
		if (m_pDownscaleTextureProgramUniform) {
			const int nTextureUnit = m_pDownscaleTextureProgramUniform->Set(&cOriginalTexture);
			if (nTextureUnit >= 0) {
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Draw the fullscreen quad
		cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
	}

	// Second step: Gaussian convolution filter to glow - Make the bloom GPU program to the currently used one
	if (cRenderer.SetProgram(m_pBlurProgram)) {
		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		if (m_pBlurPositionProgramAttribute)
			m_pBlurPositionProgramAttribute->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);

		// Set the "TextureSize" fragment shader parameter - both render targets have the same size
		if (m_pBlurTextureSizeProgramUniform)
			m_pBlurTextureSizeProgramUniform->Set(m_pRenderTarget[0]->GetSize());

		// Horizontal and vertical blur
		for (uint32 i=0; i<nBlurPasses; i++) {
			// Make the render target 1 to the current render target
			cRenderer.SetRenderTarget(m_pRenderTarget[!m_bResultIndex]);

			// Set the "UVScale" fragment shader parameter
			if (m_pBlurUVScaleProgramUniform) {
				if (i%2 != 0)
					m_pBlurUVScaleProgramUniform->Set(0.0f, 1.0f);
				else
					m_pBlurUVScaleProgramUniform->Set(1.0f, 0.0f);
			}

			// Set the "Texture" fragment shader parameter
			if (m_pBlurTextureProgramUniform) {
				const int nTextureUnit = m_pBlurTextureProgramUniform->Set(m_pRenderTarget[m_bResultIndex]->GetTextureBuffer());
				if (nTextureUnit >= 0) {
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw the fullscreen quad
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);

			// The result is now within the other render target
			m_bResultIndex = !m_bResultIndex;
		}
	}
}

/**
*  @brief
*    Debugs data
*/
void SRPDeferredDOF::Debug(const String &sShaderLanguage, VertexBuffer &cVertexBuffer, TextureBufferRectangle &cTexture, uint32 nType)
{
	// Get the renderer instance
	Renderer &cRenderer = cTexture.GetRenderer();

	// Create the shaders and programs right now?
	if (!m_pDebugFragmentShader || m_pDebugFragmentShader->GetShaderLanguage() != sShaderLanguage || m_nDebugType != nType) {
		// If there's an previous instance of the program, destroy it first
		if (m_pDebugProgram) {
			delete m_pDebugProgram;
			m_pDebugProgram = NULL;
		}
		if (m_pDebugFragmentShader) {
			delete m_pDebugFragmentShader;
			m_pDebugFragmentShader = NULL;
		}
		m_pDebugPositionProgramAttribute	= NULL;
		m_pDebugTextureSizeProgramUniform	= NULL;
		m_pDebugTextureProgramUniform		= NULL;

		// Get the shader language instance
		PLRenderer::ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(sShaderLanguage);
		if (pShaderLanguage) {
			// Get the definition
			String sDefinition;
			switch (nType) {
				 case 0:
					 sDefinition = "#define FS_DEPTH_BLUR\\n";
					 break;

				 case 1:
					 sDefinition = "#define FS_BLUR\\n";
					 break;
			}

			// Shader source code
			String sVertexShaderSourceCode;
			String sFragmentShaderSourceCode;
			if (sShaderLanguage == "GLSL") {
				#include "SRPDeferredDOF_GLSL.h"
				sVertexShaderSourceCode	  = sDeferredDOF_GLSL_VS;
				sFragmentShaderSourceCode = sDefinition + sDeferredDOF_GLSL_FS_Debug;
			} else if (sShaderLanguage == "Cg") {
				#include "SRPDeferredDOF_Cg.h"
				sVertexShaderSourceCode	  = sDeferredDOF_Cg_VS;
				sFragmentShaderSourceCode = sDefinition + sDeferredDOF_Cg_FS_Debug;
			}

			// Create a fragment shader instance
			m_pDebugFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pDebugFragmentShader) {
				// Set the fragment shader source code
				m_pDebugFragmentShader->SetSourceCode(sFragmentShaderSourceCode);
			}

			// Create a program instance
			m_pDebugProgram = pShaderLanguage->CreateProgram();
			if (m_pDebugProgram) {
				// Assign the created vertex and fragment shaders to the program
				m_pDebugProgram->SetVertexShader(m_pVertexShader);
				m_pDebugProgram->SetFragmentShader(m_pDebugFragmentShader);

				// Add our nark which will inform us as soon as the program gets dirty
				m_pDebugProgram->EventDirty.Connect(&EventHandlerDirty);

				// Get attributes and uniforms
				OnDirty(m_pDebugProgram);

				// Backup the current debug type
				m_nDebugType = nType;
			}
		}
	}

	// Make the depth blur GPU program to the currently used one
	if (cRenderer.SetProgram(m_pDebugProgram)) {
		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		if (m_pDebugPositionProgramAttribute)
			m_pDebugPositionProgramAttribute->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);

		// Set the "TextureSize" fragment shader parameter
		if (m_pDebugTextureSizeProgramUniform)
			m_pDebugTextureSizeProgramUniform->Set(cTexture.GetSize());

		// Set the "Texture" fragment shader parameter
		if (m_pDebugTextureProgramUniform) {
			const int nTextureUnit = m_pDebugTextureProgramUniform->Set(&cTexture);
			if (nTextureUnit >= 0) {
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
			}
		}

		// Draw the fullscreen quad
		cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
	}
}

/**
*  @brief
*    Returns the rectangle texture buffer storing the blur
*/
TextureBuffer *SRPDeferredDOF::GetBlurTextureBuffer() const
{
	return m_pRenderTarget[m_bResultIndex] ? m_pRenderTarget[m_bResultIndex]->GetTextureBuffer() : NULL;
}

/**
*  @brief
*    Called when a program became dirty
*/
void SRPDeferredDOF::OnDirty(Program *pProgram)
{
	// Get attributes and uniforms
	if (pProgram == m_pDepthBlurProgram) {
		m_pDepthBlurPositionProgramAttribute		 = m_pDepthBlurProgram->GetAttribute("VertexPosition");
		m_pDepthBlurTextureSizeProgramUniform		 = m_pDepthBlurProgram->GetUniform("TextureSize");
		m_pDepthBlurDOFParamsProgramUniform			 = m_pDepthBlurProgram->GetUniform("DOFParams");
		m_pDepthBlurRGBTextureProgramUniform		 = m_pDepthBlurProgram->GetUniform("RGBTexture");
		m_pDepthBlurNormalDepthTextureProgramUniform = m_pDepthBlurProgram->GetUniform("NormalDepthTexture");
	} else if (pProgram == m_pDownscaleProgram) {
		m_pDownscalePositionProgramAttribute  = m_pDownscaleProgram->GetAttribute("VertexPosition");
		m_pDownscaleTextureSizeProgramUniform = m_pDownscaleProgram->GetUniform("TextureSize");
		m_pDownscaleTextureProgramUniform	  = m_pDownscaleProgram->GetUniform("Texture");
	} else if (pProgram == m_pBlurProgram) {
		m_pBlurPositionProgramAttribute  = m_pBlurProgram->GetAttribute("VertexPosition");
		m_pBlurTextureSizeProgramUniform = m_pBlurProgram->GetUniform("TextureSize");
		m_pBlurUVScaleProgramUniform	 = m_pBlurProgram->GetUniform("UVScale");
		m_pBlurTextureProgramUniform	 = m_pBlurProgram->GetUniform("Texture");
	} else if (pProgram == m_pResultProgram) {
		m_pResultPositionProgramAttribute    = m_pResultProgram->GetAttribute("VertexPosition");
		m_pResultTextureSizeProgramUniform   = m_pResultProgram->GetUniform("TextureSize");
		m_pResultEffectWeightProgramUniform	 = m_pResultProgram->GetUniform("EffectWeight");
		m_pResultBlurDownscaleProgramUniform = m_pResultProgram->GetUniform("BlurDownscale");
		m_pResultBlurTextureProgramUniform	 = m_pResultProgram->GetUniform("BlurTexture");
		m_pResultTextureProgramUniform		 = m_pResultProgram->GetUniform("Texture");
	} else if (pProgram == m_pDebugProgram) {
		m_pDebugPositionProgramAttribute  = m_pDebugProgram->GetAttribute("VertexPosition");
		m_pDebugTextureSizeProgramUniform = m_pDebugProgram->GetUniform("TextureSize");
		m_pDebugTextureProgramUniform	  = m_pDebugProgram->GetUniform("Texture");
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPDeferredDOF::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get DOF settings
	float fEffectWeight		= EffectWeight;
	float fNearPlaneDepth   = NearPlaneDepth;
	float fFocalPlaneDepth  = FocalPlaneDepth;
	float fFarPlaneDepth    = FarPlaneDepth;
	float fBlurrinessCutoff = BlurrinessCutoff;
	bool  bDOFActive        = true;

	// Get depth of field settings from the 'SNMPostProcessDepthOfField' modifier of the used camera?
	if (!(GetFlags() & IgnoreCameraSettings)) {
		bDOFActive = false;
		SNCamera *pCamera = SNCamera::GetCamera();
		if (pCamera) {
			SceneNodeModifier *pModifier = pCamera->GetModifier("PLScene::SNMPostProcessDepthOfField");
			if (pModifier && pModifier->IsActive()) {
				fEffectWeight = pModifier->GetAttribute("EffectWeight")->GetFloat();
				if (fEffectWeight > 0.0f) {
					fNearPlaneDepth   = pModifier->GetAttribute("NearBlurDepth")   ->GetFloat();
					fFocalPlaneDepth  = pModifier->GetAttribute("FocalPlaneDepth") ->GetFloat();
					fFarPlaneDepth    = pModifier->GetAttribute("FarBlurDepth")    ->GetFloat();
					fBlurrinessCutoff = pModifier->GetAttribute("BlurrinessCutoff")->GetFloat();
					bDOFActive        = true;
				}
			}
		}
	}

	// DOF active?
	if (bDOFActive) {
		// Get the instance of the "PLCompositing::SRPDeferredGBuffer" scene renderer pass
		SRPDeferredGBuffer *pSRPDeferredGBuffer = GetGBuffer();
		if (pSRPDeferredGBuffer) {
			// Get the normal/depth texture buffer to use
			TextureBufferRectangle *pNormalDepthTextureBuffer = pSRPDeferredGBuffer->GetRenderTargetTextureBuffer(1);
			if (pNormalDepthTextureBuffer) {
				// Get the fullscreen quad instance
				FullscreenQuad *pFullscreenQuad = pSRPDeferredGBuffer->GetFullscreenQuad();
				if (pFullscreenQuad) {
					// Get the vertex buffer of the fullscreen quad
					VertexBuffer *pVertexBuffer = pFullscreenQuad->GetVertexBuffer();
					if (pVertexBuffer) {
						// Get the "PLScene::SRPBegin" instance
						SRPBegin *pSRPBegin = (SRPBegin*)GetFirstInstanceOfSceneRendererPassClass("PLScene::SRPBegin");
						if (pSRPBegin) {
							// We need up-to-date front render target content, so swap the render targets
							pSRPBegin->SwapRenderTargets();

							// Get the front render target of SRPBegin, this holds the current content
							SurfaceTextureBuffer *pFrontSurfaceTextureBuffer = pSRPBegin->GetFrontRenderTarget();
							if (pFrontSurfaceTextureBuffer && pFrontSurfaceTextureBuffer->GetTextureBuffer()) {
								// Get the shader language to use
								String sShaderLanguage = ShaderLanguage;
								if (!sShaderLanguage.GetLength())
									sShaderLanguage = cRenderer.GetDefaultShaderLanguage();

								// Reset all render states to default
								cRenderer.GetRendererContext().GetEffectManager().Use();

								// Setup renderer
								const uint32 nFixedFillModeBackup = cRenderer.GetRenderState(RenderState::FixedFillMode);
								cRenderer.SetRenderState(RenderState::ScissorTestEnable, false);
								cRenderer.SetRenderState(RenderState::FixedFillMode,	 Fill::Solid);
								cRenderer.SetRenderState(RenderState::CullMode,			 Cull::None);
								cRenderer.SetRenderState(RenderState::ZEnable,			 false);
								cRenderer.SetRenderState(RenderState::ZWriteEnable,		 false);

								// Calculate the depth blur
								cRenderer.SetColorMask(false, false, false, true);
								CalculateDepthBlur(sShaderLanguage, *pVertexBuffer, (TextureBufferRectangle&)*pFrontSurfaceTextureBuffer->GetTextureBuffer(), *pNormalDepthTextureBuffer, fNearPlaneDepth, fFocalPlaneDepth, fFarPlaneDepth, fBlurrinessCutoff);
								cRenderer.SetColorMask();
								if (GetFlags() & DebugDepthBlur) {
									// Debug depth blur data
									pSRPBegin->SwapRenderTargets();
									pFrontSurfaceTextureBuffer = pSRPBegin->GetFrontRenderTarget();
									if (pFrontSurfaceTextureBuffer && pFrontSurfaceTextureBuffer->GetTextureBuffer())
										Debug(sShaderLanguage, *pVertexBuffer, (TextureBufferRectangle&)*pFrontSurfaceTextureBuffer->GetTextureBuffer(), 0);
								} else {
									// Calculate the blur texture buffer
									if (BlurDownscale < 1.0f)
										BlurDownscale = 1.0f;
									CalculateBlur(sShaderLanguage, *pVertexBuffer, (TextureBufferRectangle&)*pFrontSurfaceTextureBuffer->GetTextureBuffer(), 0.0f, BlurPasses, BlurDownscale);

									// We need up-to-date front render target content, so swap the render targets
									pSRPBegin->SwapRenderTargets();

									// Get blur texture buffer
									TextureBufferRectangle *pTextureBuffer = (TextureBufferRectangle*)GetBlurTextureBuffer();
									if (pTextureBuffer) {
										// Debug blur data?
										if (GetFlags() & DebugBlur) {
											Debug(sShaderLanguage, *pVertexBuffer, *pTextureBuffer, 1);
										} else {
											pFrontSurfaceTextureBuffer = pSRPBegin->GetFrontRenderTarget();
											if (pFrontSurfaceTextureBuffer && pFrontSurfaceTextureBuffer->GetTextureBuffer()) {
												// Create the shaders and programs right now?
												if (!m_pResultFragmentShader || m_pResultFragmentShader->GetShaderLanguage() != sShaderLanguage) {
													// If there's an previous instance of the program, destroy it first
													if (m_pResultProgram) {
														delete m_pResultProgram;
														m_pResultProgram = NULL;
													}
													if (m_pResultFragmentShader) {
														delete m_pResultFragmentShader;
														m_pResultFragmentShader = NULL;
													}
													m_pResultPositionProgramAttribute		= NULL;
													m_pResultTextureSizeProgramUniform		= NULL;
													m_pResultEffectWeightProgramUniform		= NULL;
													m_pResultBlurDownscaleProgramUniform	= NULL;
													m_pResultBlurTextureProgramUniform		= NULL;
													m_pResultTextureProgramUniform			= NULL;

													// Get the shader language instance
													PLRenderer::ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(sShaderLanguage);
													if (pShaderLanguage) {
														// Shader source code
														String sVertexShaderSourceCode;
														String sFragmentShaderSourceCode;
														if (sShaderLanguage == "GLSL") {
															#include "SRPDeferredDOF_GLSL.h"
															sVertexShaderSourceCode	  = sDeferredDOF_GLSL_VS;
															sFragmentShaderSourceCode = sDeferredDOF_GLSL_FS_Result;
														} else if (sShaderLanguage == "Cg") {
															#include "SRPDeferredDOF_Cg.h"
															sVertexShaderSourceCode	  = sDeferredDOF_Cg_VS;
															sFragmentShaderSourceCode = sDeferredDOF_Cg_FS_Result;
														}

														// Create a fragment shader instance
														m_pResultFragmentShader = pShaderLanguage->CreateFragmentShader();
														if (m_pResultFragmentShader) {
															// Set the fragment shader source code
															m_pResultFragmentShader->SetSourceCode(sFragmentShaderSourceCode);
														}

														// Create a program instance
														m_pResultProgram = pShaderLanguage->CreateProgram();
														if (m_pResultProgram) {
															// Assign the created vertex and fragment shaders to the program
															m_pResultProgram->SetVertexShader(m_pVertexShader);
															m_pResultProgram->SetFragmentShader(m_pResultFragmentShader);

															// Add our nark which will inform us as soon as the program gets dirty
															m_pResultProgram->EventDirty.Connect(&EventHandlerDirty);

															// Get attributes and uniforms
															OnDirty(m_pResultProgram);
														}
													}
												}

												// Make the result GPU program to the currently used one
												if (cRenderer.SetProgram(m_pResultProgram)) {
													// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
													if (m_pResultPositionProgramAttribute)
														m_pResultPositionProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);

													// Set the "TextureSize" fragment shader parameter
													if (m_pResultTextureSizeProgramUniform)
														m_pResultTextureSizeProgramUniform->Set(((TextureBufferRectangle*)pFrontSurfaceTextureBuffer->GetTextureBuffer())->GetSize());

													// Set the "EffectWeight" fragment shader parameter
													if (m_pResultEffectWeightProgramUniform)
														m_pResultEffectWeightProgramUniform->Set(fEffectWeight);

													// Set the "BlurDownscale" fragment shader parameter
													if (m_pResultBlurDownscaleProgramUniform)
														m_pResultBlurDownscaleProgramUniform->Set(BlurDownscale);

													// Set the "BlurTexture" fragment shader parameter
													if (m_pResultBlurTextureProgramUniform) {
														const int nTextureUnit = m_pResultBlurTextureProgramUniform->Set(pTextureBuffer);
														if (nTextureUnit >= 0) {
															cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
														}
													}

													// Set the "Texture" fragment shader parameter
													if (m_pResultTextureProgramUniform) {
														const int nTextureUnit = m_pResultTextureProgramUniform->Set(pFrontSurfaceTextureBuffer->GetTextureBuffer());
														if (nTextureUnit >= 0) {
															cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
															cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
														}
													}

													// Draw the fullscreen quad
													cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
												}
											}
										}
									}
								}

								// Restore fixed fill mode render state
								cRenderer.SetRenderState(RenderState::FixedFillMode, nFixedFillModeBackup);
							}
						}
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
