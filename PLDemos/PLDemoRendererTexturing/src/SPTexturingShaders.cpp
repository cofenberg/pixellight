/*********************************************************\
 *  File: SPTexturingShaders.cpp                          *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/Rectangle.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include "SPTexturingShaders.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPTexturingShaders)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPTexturingShaders::SPTexturingShaders(Renderer &cRenderer) : SPTexturing(cRenderer),
	m_pVertexShader(nullptr),
	m_pFragmentShader(nullptr),
	m_pProgram(nullptr)
{
	// Decide which shader language should be used (for example "GLSL" or "Cg")
	ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(cRenderer.GetDefaultShaderLanguage());
	if (pShaderLanguage) {
		// Create the shader instances
		m_pVertexShader   = pShaderLanguage->CreateVertexShader();
		m_pFragmentShader = pShaderLanguage->CreateFragmentShader();

		// Shader source code
		String sVertexShaderSourceCode;
		String sFragmentShaderSourceCode;
		if (pShaderLanguage->GetShaderLanguage() == "GLSL") {
			// Figure out the GLSL version to use
			const String sVersion = (cRenderer.GetAPI() == "OpenGL ES 2.0") ? "#version 100\n" : "#version 130\n";	// 130 = OpenGL 3.0 shaders (with this version, we can keep the precision qualifiers)

			// Get shader source codes
			#include "SPTexturingShaders_GLSL.h"
			sVertexShaderSourceCode   = sVersion + sVertexShaderSourceCodeGLSL;
			sFragmentShaderSourceCode = sVersion + sFragmentShaderSourceCodeGLSL;
		} else if (pShaderLanguage->GetShaderLanguage() == "Cg") {
			#include "SPTexturingShaders_Cg.h"
			sVertexShaderSourceCode   = sVertexShaderSourceCodeCg;
			sFragmentShaderSourceCode = sFragmentShaderSourceCodeCg;
		}

		// Set the vertex shader source code
		if (m_pVertexShader)
			m_pVertexShader->SetSourceCode(sVertexShaderSourceCode, "arbvp1");

		// Set the fragment shader source code
		if (m_pFragmentShader)
			m_pFragmentShader->SetSourceCode(sFragmentShaderSourceCode, "arbfp1");

		// Create a program instance
		m_pProgram = pShaderLanguage->CreateProgram();
		if (m_pProgram) {
			// Assign the created vertex and fragment shaders to the program
			m_pProgram->SetVertexShader(m_pVertexShader);
			m_pProgram->SetFragmentShader(m_pFragmentShader);
		}
	}
}

/**
*  @brief
*    Destructor
*/
SPTexturingShaders::~SPTexturingShaders()
{
	// Cleanup
	if (m_pProgram)
		delete m_pProgram;
	if (m_pFragmentShader)
		delete m_pFragmentShader;
	if (m_pVertexShader)
		delete m_pVertexShader;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPTexturingShaders::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Clear the content of the current used render target (color to black and depth to 1.0 by default)
	cRenderer.Clear();

	// Make our program to the current one
	if (cRenderer.SetProgram(m_pProgram)) {
		// Set "ObjectSpaceToClipSpaceMatrix" program uniform
		ProgramUniform *pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
		if (pProgramUniform) {
			// Calculate the world matrix
			Matrix4x4 mWorld;
			{
				// Build a rotation matrix by using a given euler angle around the y-axis
				mWorld.FromEulerAngleY(static_cast<float>(m_fRotation*Math::DegToRad));

				// Increase the rotation by the current time difference (time past since the last frame)
				// -> Normally, such work should NOT be performed within the rendering step, but we want
				//    to keep the implementation simple in here...
				m_fRotation += Timing::GetInstance()->GetTimeDifference()*50;
			}

			// Calculate the view matrix
			Matrix4x4 mView;
			{
				mView.SetTranslation(0.0f, 0.0f, -5.0f);
			}

			// Calculate the projection matrix
			Matrix4x4 mProjection;
			{
				const float fAspect      = 1.0f;
				const float fAspectRadio = cRenderer.GetViewport().GetWidth()/(cRenderer.GetViewport().GetHeight()*fAspect);
				mProjection.PerspectiveFov(static_cast<float>(45.0f*Math::DegToRad), fAspectRadio, 0.001f, 1000.0f);
			}

			// Calculate the final composed world view projection matrix
			const Matrix4x4 mWorldViewProjection = mProjection*mView*mWorld;

			// Set object space to clip space matrix uniform
			pProgramUniform->Set(mWorldViewProjection);
		}

		// Set "TextureMap" program uniform
		pProgramUniform = m_pProgram->GetUniform("TextureMap");
		if (pProgramUniform)
			pProgramUniform->Set(m_pTextureBuffer);

		// No back face culling, please. Else we can only see one 'side' of the quad
		cRenderer.SetRenderState(RenderState::CullMode, Cull::None);

		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		ProgramAttribute *pProgramAttribute = m_pProgram->GetAttribute("VertexPosition");
		if (pProgramAttribute)
			pProgramAttribute->Set(m_pVertexBuffer, PLRenderer::VertexBuffer::Position);
		pProgramAttribute = m_pProgram->GetAttribute("VertexTexCoord");
		if (pProgramAttribute)
			pProgramAttribute->Set(m_pVertexBuffer, PLRenderer::VertexBuffer::TexCoord);

		// Now draw the primitives of our cool quad.
		// The primitive type is 'triangle strip', we start at vertex 0 and draw '4' vertices.
		cRenderer.DrawPrimitives(PLRenderer::Primitive::TriangleStrip, 0, 4);
	}
}
