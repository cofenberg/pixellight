/*********************************************************\
 *  File: SPK_PLLineRendererShaders.cpp                  *
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
#include <PLMath/Math.h>	// On Mac OS X I'am getting the compiler error "error: ‘isfinite’ was not declared in this scope" when not including this header, first... I'am not sure what SPARK is changing in order to cause this error...
#include <PLCore/Tools/Tools.h>
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
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineRendererShaders.h"


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
SPK_PLLineRendererShaders *SPK_PLLineRendererShaders::Create(PLRenderer::Renderer &cRenderer, const String &sShaderLanguage, float fLength, float fWidth)
{
	SPK_PLLineRendererShaders *pSPK_PLLineRendererShaders = new SPK_PLLineRendererShaders(cRenderer, sShaderLanguage, fLength, fWidth);
	registerObject(pSPK_PLLineRendererShaders);
	return pSPK_PLLineRendererShaders;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
SPK_PLLineRendererShaders::SPK_PLLineRendererShaders(PLRenderer::Renderer &cRenderer, const String &sShaderLanguage, float fLength, float fWidth) : SPK_PLLineRenderer(cRenderer, fLength, fWidth),
	m_pEventHandlerDirty(new PLCore::EventHandler<PLRenderer::Program*>(&SPK_PLLineRendererShaders::OnDirty, this)),
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
			m_pVertexShader = pShaderLanguage->CreateVertexShader(sVertexShaderSourceCode, "arbvp1");

			// Create a fragment shader instance
			m_pFragmentShader = pShaderLanguage->CreateFragmentShader(sFragmentShaderSourceCode, "arbfp1");

			// Create a program instance and assign the created vertex and fragment shaders to it
			m_pProgram = pShaderLanguage->CreateProgram(m_pVertexShader, m_pFragmentShader);
			if (m_pProgram) {
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
*    Destructor of SPK_PLLineRendererShaders
*/
SPK_PLLineRendererShaders::~SPK_PLLineRendererShaders()
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
void SPK_PLLineRendererShaders::render(const SPK::Group &group)
{
	// Is there a valid m_pSPK_PLBuffer instance?
	if (prepareBuffers(group) && m_pSPK_PLBuffer && m_pSPK_PLBuffer->GetVertexBuffer()) {
		// Get the vertex buffer instance from m_pSPK_PLBuffer and lock it
		VertexBuffer *pVertexBuffer = m_pSPK_PLBuffer->GetVertexBuffer();
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Vertex buffer data
			const uint32 nVertexSize = pVertexBuffer->GetVertexSize();
			float *pfPosition = static_cast<float*>(pVertexBuffer->GetData(0, VertexBuffer::Position));

			// Fill the vertex buffer with the current data
			for (size_t i=0, nCurrentVertex=0; i<group.getNbParticles(); i++) {
				// Get the particle
				const SPK::Particle &cParticle = group.getParticle(i);

				// Copy over the particle position into the vertex data
				pfPosition[0] = cParticle.position().x;
				pfPosition[1] = cParticle.position().y;
				pfPosition[2] = cParticle.position().z;
				pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!
				// Copy over the particle color into the vertex data
				pVertexBuffer->SetColor(static_cast<uint32>(nCurrentVertex), Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), cParticle.getParamCurrentValue(SPK::PARAM_ALPHA)));
				nCurrentVertex++;	// Next, please!

				// Copy over the particle position into the vertex data
				pfPosition[0] = cParticle.position().x + cParticle.velocity().x*length;
				pfPosition[1] = cParticle.position().y + cParticle.velocity().y*length;
				pfPosition[2] = cParticle.position().z + cParticle.velocity().z*length;
				pfPosition = reinterpret_cast<float*>(reinterpret_cast<char*>(pfPosition) + nVertexSize);	// Next, please!
				// Copy over the particle color into the vertex data
				pVertexBuffer->SetColor(static_cast<uint32>(nCurrentVertex), Color4(cParticle.getR(), cParticle.getG(), cParticle.getB(), cParticle.getParamCurrentValue(SPK::PARAM_ALPHA)));
				nCurrentVertex++;	// Next, please!
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}

		// Setup render states
		InitBlending();
		GetPLRenderer().SetRenderState(RenderState::ZEnable,      isRenderingHintEnabled(SPK::DEPTH_TEST));
		GetPLRenderer().SetRenderState(RenderState::ZWriteEnable, isRenderingHintEnabled(SPK::DEPTH_WRITE));
		GetPLRenderer().SetRenderState(RenderState::LineWidth,    Tools::FloatToUInt32(width));

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
			GetPLRenderer().DrawPrimitives(Primitive::LineList, 0, static_cast<uint32>(group.getNbParticles() << 1));
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
void SPK_PLLineRendererShaders::OnDirty(Program *pProgram)
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
