/*********************************************************\
 *  File: SRPDeferredHDAO.cpp                            *
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
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/TextureBufferRectangle.h>
#include "PLCompositing/Shaders/Deferred/SRPDeferredGBuffer.h"
#include "PLCompositing/Shaders/Deferred/SRPDeferredHDAO.h"


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
	Flags(this),
	m_pProgramGenerator(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
SRPDeferredHDAO::~SRPDeferredHDAO()
{
	// Destroy the program generator
	if (m_pProgramGenerator)
		delete m_pProgramGenerator;
}


//[-------------------------------------------------------]
//[ Protected virtual SRPDeferredSSAO functions           ]
//[-------------------------------------------------------]
void SRPDeferredHDAO::DrawAO(const String &sShaderLanguage, VertexBuffer &cVertexBuffer, TextureBufferRectangle &cNormalDepthTextureBuffer)
{
	// Get the renderer instance
	Renderer &cRenderer = cNormalDepthTextureBuffer.GetRenderer();

	// Create the program generator if there's currently no instance of it
	if (!m_pProgramGenerator || m_pProgramGenerator->GetShaderLanguage() != sShaderLanguage) {
		// If there's an previous instance of the program generator, destroy it first
		if (m_pProgramGenerator) {
			delete m_pProgramGenerator;
			m_pProgramGenerator = nullptr;
		}

		// Choose the shader source codes depending on the requested shader language
		if (sShaderLanguage == "GLSL") {
			#include "SRPDeferredHDAO_GLSL.h"
			m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDeferredHDAO_GLSL_VS, "130", sDeferredHDAO_GLSL_FS, "130");	// OpenGL 3.0 ("#version 130")
		} else if (sShaderLanguage == "Cg") {
			#include "SRPDeferredHDAO_Cg.h"
			m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDeferredHDAO_Cg_VS, "glslv", sDeferredHDAO_Cg_FS, "glslf");
		}
	}

	// If there's no program generator, we don't need to continue
	if (m_pProgramGenerator) {
		// Reset the program flags
		m_cProgramFlags.Reset();

		// Set program flags
		if (!(GetFlags() & NoNormals))
			PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMAL)

		// Get a program instance from the program generator using the given program flags
		ProgramGenerator::GeneratedProgram *pGeneratedProgram = m_pProgramGenerator->GetProgram(m_cProgramFlags);

		// Make our program to the current one
		if (pGeneratedProgram && cRenderer.SetProgram(pGeneratedProgram->pProgram)) {
			// Set pointers to uniforms & attributes of a generated program if they are not set yet
			GeneratedProgramUserData *pGeneratedProgramUserData = static_cast<GeneratedProgramUserData*>(pGeneratedProgram->pUserData);
			if (!pGeneratedProgramUserData) {
				pGeneratedProgram->pUserData = pGeneratedProgramUserData = new GeneratedProgramUserData;
				Program *pProgram = pGeneratedProgram->pProgram;
				// Vertex shader attributes
				static const String sVertexPosition = "VertexPosition";
				pGeneratedProgramUserData->pVertexPosition	= pProgram->GetAttribute(sVertexPosition);
				// Vertex shader uniforms
				static const String sTextureSize = "TextureSize";
				pGeneratedProgramUserData->pTextureSize		= pProgram->GetUniform(sTextureSize);
				// Fragment shader uniforms
				static const String sAORejectRadius = "AORejectRadius";
				pGeneratedProgramUserData->pAORejectRadius	= pProgram->GetUniform(sAORejectRadius);
				static const String sContrast = "Contrast";
				pGeneratedProgramUserData->pContrast		= pProgram->GetUniform(sContrast);
				static const String sAOAcceptRadius = "AOAcceptRadius";
				pGeneratedProgramUserData->pAOAcceptRadius	= pProgram->GetUniform(sAOAcceptRadius);
				static const String sNormalScale = "NormalScale";
				pGeneratedProgramUserData->pNormalScale		= pProgram->GetUniform(sNormalScale);
				static const String sAcceptAngle = "AcceptAngle";
				pGeneratedProgramUserData->pAcceptAngle		= pProgram->GetUniform(sAcceptAngle);
				static const String sNumRingGathers = "NumRingGathers";
				pGeneratedProgramUserData->pNumRingGathers	= pProgram->GetUniform(sNumRingGathers);
				static const String sNumRings = "NumRings";
				pGeneratedProgramUserData->pNumRings		= pProgram->GetUniform(sNumRings);
				static const String sResolution = "Resolution";
				pGeneratedProgramUserData->pResolution		= pProgram->GetUniform(sResolution);
				static const String sNormalDepthMap = "NormalDepthMap";
				pGeneratedProgramUserData->pNormalDepthMap	= pProgram->GetUniform(sNormalDepthMap);
			}

			// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
			if (pGeneratedProgramUserData->pVertexPosition)
				pGeneratedProgramUserData->pVertexPosition->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);

			// Set texture size
			if (pGeneratedProgramUserData->pTextureSize)
				pGeneratedProgramUserData->pTextureSize->Set(cNormalDepthTextureBuffer.GetSize());

			// Set the normal depth texture
			if (pGeneratedProgramUserData->pNormalDepthMap) {
				const int nTextureUnit = pGeneratedProgramUserData->pNormalDepthMap->Set(&cNormalDepthTextureBuffer);
				if (nTextureUnit >= 0) {
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// AORejectRadius
			if (pGeneratedProgramUserData->pAORejectRadius)
				pGeneratedProgramUserData->pAORejectRadius->Set(AORejectRadius);

			// Contrast
			if (pGeneratedProgramUserData->pContrast)
				pGeneratedProgramUserData->pContrast->Set(Contrast);

			// AOAcceptRadius
			if (pGeneratedProgramUserData->pAOAcceptRadius)
				pGeneratedProgramUserData->pAOAcceptRadius->Set(AOAcceptRadius);

			// NormalScale
			if (pGeneratedProgramUserData->pNormalScale)
				pGeneratedProgramUserData->pNormalScale->Set(NormalScale);

			// AcceptAngle
			if (pGeneratedProgramUserData->pAcceptAngle)
				pGeneratedProgramUserData->pAcceptAngle->Set(AcceptAngle);

			// NumRingGathers
			if (pGeneratedProgramUserData->pNumRingGathers) {
				uint32 nNumberOfRingGathers = NumberOfRingGathers;
				if (nNumberOfRingGathers < 1)
					nNumberOfRingGathers = 1;
				if (nNumberOfRingGathers > 20)
					nNumberOfRingGathers = 20;
				pGeneratedProgramUserData->pNumRingGathers->Set(static_cast<int>(nNumberOfRingGathers));
			}

			// NumRings
			if (pGeneratedProgramUserData->pNumRings) {
				uint32 nNumberOfRings = NumberOfRings;
				if (nNumberOfRings < 1)
					nNumberOfRings = 1;
				if (nNumberOfRings > 4)
					nNumberOfRings = 4;
				pGeneratedProgramUserData->pNumRings->Set(static_cast<int>(nNumberOfRings));
			}

			// Resolution
			if (pGeneratedProgramUserData->pResolution)
				pGeneratedProgramUserData->pResolution->Set(cNormalDepthTextureBuffer.GetSize());

			// Draw the fullscreen quad
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
