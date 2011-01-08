/*********************************************************\
 *  File: SPTriangleShaders.cpp                          *
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
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/GeometryShader.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include "SPTriangleShaders.h"


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
pl_implement_class(SPTriangleShaders)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPTriangleShaders::SPTriangleShaders(Renderer &cRenderer) : SPTriangle(cRenderer),
	m_pVertexShader(nullptr),
	m_pGeometryShader(nullptr),
	m_pFragmentShader(nullptr),
	m_pProgram(nullptr)
{
	// Decide which shader language should be used (for example "GLSL" or "Cg")
	ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(cRenderer.GetDefaultShaderLanguage());
	if (pShaderLanguage) {
		// Create the shader instances
		m_pVertexShader   = pShaderLanguage->CreateVertexShader();
		m_pGeometryShader = pShaderLanguage->CreateGeometryShader();
		m_pFragmentShader = pShaderLanguage->CreateFragmentShader();

		// Shader source code
		String sVertexShaderSourceCode;
		String sGeometryShaderSourceCode;
		String sFragmentShaderSourceCode;
		if (pShaderLanguage->GetShaderLanguage() == "GLSL") {
			#include "SPTriangleShaders_GLSL.h"
			sVertexShaderSourceCode   = ProgramGenerator::ApplyGLSLHacks(sVertexShaderSourceCodeGLSL);
			sGeometryShaderSourceCode = ProgramGenerator::ApplyGLSLHacks(sGeometryShaderSourceCodeGLSL);
			sFragmentShaderSourceCode = ProgramGenerator::ApplyGLSLHacks(m_pGeometryShader ? sFragmentShaderSourceCodeGLSL_GS : sFragmentShaderSourceCodeGLSL);
		} else if (pShaderLanguage->GetShaderLanguage() == "Cg") {
			#include "SPTriangleShaders_Cg.h"
			sVertexShaderSourceCode   = sVertexShaderSourceCodeCg;
			sGeometryShaderSourceCode = sGeometryShaderSourceCodeCg;
			sFragmentShaderSourceCode = sFragmentShaderSourceCodeCg;
		}

		// Set the vertex shader source code
		if (m_pVertexShader)
			m_pVertexShader->SetSourceCode(sVertexShaderSourceCode);

		// Set the geometry shader source code
		if (m_pGeometryShader)
			m_pGeometryShader->SetSourceCode(sGeometryShaderSourceCode);

		// Set the fragment shader source code
		if (m_pFragmentShader)
			m_pFragmentShader->SetSourceCode(sFragmentShaderSourceCode);

		// Create a program instance
		m_pProgram = pShaderLanguage->CreateProgram();
		if (m_pProgram) {
			// Assign the created vertex, geometry and fragment shaders to the program
			m_pProgram->SetVertexShader(m_pVertexShader);
			m_pProgram->SetGeometryShader(m_pGeometryShader);
			m_pProgram->SetFragmentShader(m_pFragmentShader);
		}
	}
}

/**
*  @brief
*    Destructor
*/
SPTriangleShaders::~SPTriangleShaders()
{
	// Cleanup
	if (m_pProgram)
		delete m_pProgram;
	if (m_pFragmentShader)
		delete m_pFragmentShader;
	if (m_pGeometryShader)
		delete m_pGeometryShader;
	if (m_pVertexShader)
		delete m_pVertexShader;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPTriangleShaders::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Clear the content of the current used render target (color to black and depth to 1.0 by default)
	cRenderer.Clear();

	// Make our program to the current one
	if (cRenderer.SetProgram(m_pProgram)) {
		// Set program uniforms
		ProgramUniform *pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
		if (pProgramUniform) {
			// Calculate the world matrix
			Matrix4x4 mWorld;
			{
				// Build a rotation matrix by using a given euler angle around the y-axis
				mWorld.FromEulerAngleY(float(m_fRotation*Math::DegToRad));

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
				mProjection.PerspectiveFov(float(45.0f*Math::DegToRad), fAspectRadio, 0.001f, 1000.0f);
			}

			// Calculate the final composed world view projection matrix
			const Matrix4x4 mWorldViewProjection = mProjection*mView*mWorld;

			// Set object space to clip space matrix uniform
			pProgramUniform->Set(mWorldViewProjection);
		}

		// No back face culling, please. Else we can only see one 'side' of the triangle
		cRenderer.SetRenderState(RenderState::CullMode, Cull::None);

		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		ProgramAttribute *pProgramAttribute = m_pProgram->GetAttribute("VertexPosition");
		if (pProgramAttribute)
			pProgramAttribute->Set(m_pVertexBuffer, PLRenderer::VertexBuffer::Position);
		pProgramAttribute = m_pProgram->GetAttribute("VertexColor");
		if (pProgramAttribute)
			pProgramAttribute->Set(m_pVertexBuffer, PLRenderer::VertexBuffer::Color);

		// Now draw the primitives of our cool triangle.
		// The primitive type is 'triangles', we start at vertex 0 and draw '3' vertices.
		cRenderer.DrawPrimitives(PLRenderer::Primitive::TriangleList, 0, 3);
	}
}
