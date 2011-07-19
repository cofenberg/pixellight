/*********************************************************\
 *  File: SPK_PLLineTrailRendererShaders.cpp             *
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
#include <PLCore/Tools/Tools.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
	#include <Core/SPK_ArrayBuffer.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineTrailRendererShaders.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
using namespace PLRenderer;
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates and registers a new SPK_PLLineTrailRendererShaders
*/
SPK_PLLineTrailRendererShaders *SPK_PLLineTrailRendererShaders::Create(PLRenderer::Renderer &cRenderer, const String &sShaderLanguage)
{
	SPK_PLLineTrailRendererShaders *pSPK_PLLineTrailRendererShaders = new SPK_PLLineTrailRendererShaders(cRenderer, sShaderLanguage);
	registerObject(pSPK_PLLineTrailRendererShaders);
	return pSPK_PLLineTrailRendererShaders;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLLineTrailRendererShaders::SPK_PLLineTrailRendererShaders(PLRenderer::Renderer &cRenderer, const String &sShaderLanguage) : SPK_PLLineTrailRenderer(cRenderer),
	m_pEventHandlerDirty(new PLCore::EventHandler<PLRenderer::Program*>(&SPK_PLLineTrailRendererShaders::OnDirty, this)),
	m_sShaderLanguage(sShaderLanguage),
	m_pVertexShader(nullptr),
	m_pFragmentShader(nullptr),
	m_pProgram(nullptr),
	m_pPositionProgramAttribute(nullptr),
	m_pColorProgramAttribute(nullptr),
	m_pObjectSpaceToClipSpaceMatrixProgramUniform(nullptr)
{
	// Get the shader language to use
	if (!m_sShaderLanguage.GetLength())
		m_sShaderLanguage = cRenderer.GetDefaultShaderLanguage();

	// Create the GPU program right now?
	if (!m_pProgram || m_pProgram->GetShaderLanguage() != m_sShaderLanguage) {
		// If there's an previous instance of the program, destroy it first
		if (m_pProgram) {
			delete m_pProgram;
			m_pProgram = nullptr;
		}
		if (m_pFragmentShader) {
			delete m_pFragmentShader;
			m_pFragmentShader = nullptr;
		}
		if (m_pVertexShader) {
			delete m_pVertexShader;
			m_pVertexShader = nullptr;
		}
		m_pPositionProgramAttribute						= nullptr;
		m_pColorProgramAttribute						= nullptr;
		m_pObjectSpaceToClipSpaceMatrixProgramUniform	= nullptr;

		// Get the shader language instance
		PLRenderer::ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(m_sShaderLanguage);
		if (pShaderLanguage) {
			// Shader source code
			String sVertexShaderSourceCode;
			String sFragmentShaderSourceCode;
			if (m_sShaderLanguage == "GLSL") {
				#include "SPK_PLLineRendererShaders_GLSL.h"
				if (cRenderer.GetAPI() == "OpenGL ES 2.0") {
					// Get shader source codes
					sVertexShaderSourceCode   = "#version 100\n" + sSPK_PLLineRendererShaders_GLSL_VS;
					sFragmentShaderSourceCode = "#version 100\n" + sSPK_PLLineRendererShaders_GLSL_FS;
				} else {
					// Remove precision qualifiers so that we're able to use 110 (OpenGL 2.0 shaders) instead of 130 (OpenGL 3.0 shaders,
					// with this version we can keep the precision qualifiers) so that this shader requirements are as low as possible
					sVertexShaderSourceCode   = "#version 110\n" + Shader::RemovePrecisionQualifiersFromGLSL(sSPK_PLLineRendererShaders_GLSL_VS);
					sFragmentShaderSourceCode = "#version 110\n" + Shader::RemovePrecisionQualifiersFromGLSL(sSPK_PLLineRendererShaders_GLSL_FS);
				}
			} else if (m_sShaderLanguage == "Cg") {
				#include "SPK_PLLineRendererShaders_Cg.h"
				sVertexShaderSourceCode   = sSPK_PLLineRendererShaders_Cg_VS;
				sFragmentShaderSourceCode = sSPK_PLLineRendererShaders_Cg_FS;
			}

			// Create a vertex shader instance
			m_pVertexShader = pShaderLanguage->CreateVertexShader();
			if (m_pVertexShader) {
				// Set the vertex shader source code
				m_pVertexShader->SetSourceCode(sVertexShaderSourceCode, "arbvp1");
			}

			// Create a fragment shader instance
			m_pFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pFragmentShader) {
				// Set the fragment shader source code
				m_pFragmentShader->SetSourceCode(sFragmentShaderSourceCode, "arbfp1");
			}

			// Create a program instance
			m_pProgram = pShaderLanguage->CreateProgram();
			if (m_pProgram) {
				// Assign the created vertex and fragment shaders to the program
				m_pProgram->SetVertexShader(m_pVertexShader);
				m_pProgram->SetFragmentShader(m_pFragmentShader);

				// Add our nark which will inform us as soon as the program gets dirty
				m_pProgram->EventDirty.Connect(*m_pEventHandlerDirty);

				// Get attributes and uniforms
				OnDirty(m_pProgram);
			}
		}
	}
}

/**
*  @brief
*    Destructor of SPK_PLLineTrailRendererShaders
*/
SPK_PLLineTrailRendererShaders::~SPK_PLLineTrailRendererShaders()
{
	// Destroy shaders
	if (m_pProgram)
		delete m_pProgram;
	if (m_pFragmentShader)
		delete m_pFragmentShader;
	if (m_pVertexShader)
		delete m_pVertexShader;

	// Destroy the event handler
	delete m_pEventHandlerDirty;
}


//[-------------------------------------------------------]
//[ Public virtual SPK::Renderer functions                ]
//[-------------------------------------------------------]
void SPK_PLLineTrailRendererShaders::render(const SPK::Group &group)
{	
	// Is there a valid m_pSPK_PLBuffer instance?
	if (prepareBuffers(group) && m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
		// Update buffers
		for (size_t i=0; i<group.getNbParticles(); i++) {
			const SPK::Particle &cParticle = group.getParticle(i);
			float fAge = cParticle.getAge();
			float fOldAge = *m_pfValueIterator;

			if ((fAge == 0.0f) || (fAge < *m_pfValueIterator)) {
				// If the particle is new, buffers for it are reinitialized
				Init(cParticle, 0.0f);
			} else {
				if (fAge - *(m_pfValueIterator + 1) >= m_fDuration/(m_nNumOfSamples - 1)) {
					// Shifts the data by one
					memmove(m_pfVertexIterator + 6, m_pfVertexIterator + 3, (m_nNumOfSamples - 1)*3*sizeof(float));
					memmove(m_pfColorIterator + 8,  m_pfColorIterator + 4,  ((m_nNumOfSamples - 1) << 2)*sizeof(float));
					memmove(m_pfValueIterator + 1,  m_pfValueIterator,      (m_nNumOfSamples - 1)*sizeof(float));

					// Post degenerated vertex copy
					memcpy(m_pfVertexIterator + (m_nNumOfSamples + 1)*3, m_pfVertexIterator + m_nNumOfSamples*3, 3*sizeof(float));
				}

				// Updates the current sample
				const SPK::Vector3D &pos = cParticle.position();
				*(m_pfVertexIterator++) = pos.x;
				*(m_pfVertexIterator++) = pos.y;
				*(m_pfVertexIterator++) = pos.z;

				memcpy(m_pfVertexIterator, m_pfVertexIterator - 3, 3*sizeof(float));
				m_pfVertexIterator += (m_nNumOfSamples + 1)*3;

				m_pfColorIterator += 4; // Skips post degenerated vertex color
				*(m_pfColorIterator++) = cParticle.getR();
				*(m_pfColorIterator++) = cParticle.getG();
				*(m_pfColorIterator++) = cParticle.getB();
				*(m_pfColorIterator++) = cParticle.getParamCurrentValue(SPK::PARAM_ALPHA);
				m_pfColorIterator += 3;

				*(m_pfValueIterator++) = fAge;

				// Updates alpha
				for (uint32 i=0; i<m_nNumOfSamples-1; i++) {
					const float fRatio = (fAge - fOldAge)/(m_fDuration - fAge + *m_pfValueIterator);
					if (fRatio > 0.0f)
						*m_pfColorIterator *= (fRatio < 1.0f) ? 1.0f - fRatio : 0.0f;
					m_pfColorIterator += 4;
					++m_pfValueIterator;
				}
				++m_pfColorIterator;
			}
		}

		// Get the vertex buffer instance from m_pSPK_PLBuffer and lock it
		VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Vertex buffer data
			const uint32 nVertexSize = pVertexBuffer->GetVertexSize();
			float *pfPosition = static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::Position));

			// Fill the vertex buffer with the current data
			m_pfVertexIterator = m_pfVertexBuffer;
			m_pfColorIterator = m_pfColorBuffer;
			for (size_t i=0; i<group.getNbParticles()*(m_nNumOfSamples + 2); i++) {
				// Copy over the particle position into the vertex data
				pfPosition[0] = m_pfVertexIterator[0];
				pfPosition[1] = m_pfVertexIterator[1];
				pfPosition[2] = m_pfVertexIterator[2];
				pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!
				m_pfVertexIterator += 3;	// Next, please!

				// Copy over the particle color into the vertex data
				pVertexBuffer->SetColor(i, Color4(m_pfColorIterator[0], m_pfColorIterator[1], m_pfColorIterator[2], m_pfColorIterator[3]));
				m_pfColorIterator += 4;	// Next, please!
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}

		// Setup render states
		InitBlending();
		GetPLRenderer().SetRenderState(RenderState::ZEnable,      isRenderingHintEnabled(SPK::DEPTH_TEST));
		GetPLRenderer().SetRenderState(RenderState::ZWriteEnable, isRenderingHintEnabled(SPK::DEPTH_WRITE));
		GetPLRenderer().SetRenderState(RenderState::LineWidth,    Tools::FloatToUInt32(m_fWidth));

		// Make our program to the current one
		if (GetPLRenderer().SetProgram(m_pProgram)) {
			// Set the "ObjectSpaceToClipSpaceMatrix" fragment shader parameter
			if (m_pObjectSpaceToClipSpaceMatrixProgramUniform)
				m_pObjectSpaceToClipSpaceMatrixProgramUniform->Set(m_mWorldViewProjection);

			// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
			if (m_pPositionProgramAttribute)
				m_pPositionProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);
			if (m_pColorProgramAttribute)
				m_pColorProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Color);

			// Draw
			GetPLRenderer().DrawPrimitives(Primitive::LineStrip, 0, group.getNbParticles()*(m_nNumOfSamples + 2));
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a program became dirty
*/
void SPK_PLLineTrailRendererShaders::OnDirty(Program *pProgram)
{
	// Get attributes and uniforms
	if (pProgram == m_pProgram) {
		m_pPositionProgramAttribute						= m_pProgram->GetAttribute("VertexPosition");
		m_pColorProgramAttribute						= m_pProgram->GetAttribute("VertexColor");
		m_pObjectSpaceToClipSpaceMatrixProgramUniform	= m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
