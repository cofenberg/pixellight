/*********************************************************\
 *  File: SPMultiViewShaders.cpp                         *
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
#include <PLMath/Matrix4x4.h>
#include <PLMath/Rectangle.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include "SPMultiViewShaders.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SPMultiViewShaders)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPMultiViewShaders::SPMultiViewShaders(Renderer &cRenderer) : SPMultiView(cRenderer),
	m_pVertexShader(NULL),
	m_pFragmentShader(NULL),
	m_pProgram(NULL)
{
	// Decide which shader language should be used (for example "GLSL" or "Cg")
	ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(cRenderer.GetDefaultShaderLanguage());
	if (pShaderLanguage) {
		// Shader source code
		String sVertexShaderSourceCode;
		String sFragmentShaderSourceCode;
		if (pShaderLanguage->GetShaderLanguage() == "GLSL") {
			#include "SPMultiViewShaders_GLSL.h"
			sVertexShaderSourceCode   = ProgramGenerator::ApplyGLSLHacks(sVertexShaderSourceCodeGLSL);
			sFragmentShaderSourceCode = ProgramGenerator::ApplyGLSLHacks(sFragmentShaderSourceCodeGLSL);
		} else if (pShaderLanguage->GetShaderLanguage() == "Cg") {
			#include "SPMultiViewShaders_Cg.h"
			sVertexShaderSourceCode   = sVertexShaderSourceCodeCg;
			sFragmentShaderSourceCode = sFragmentShaderSourceCodeCg;
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
		}
	}
}

/**
*  @brief
*    Destructor
*/
SPMultiViewShaders::~SPMultiViewShaders()
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
//[ Private virtual SPMultiView functions                 ]
//[-------------------------------------------------------]
void SPMultiViewShaders::DrawScene(uint32 nScene)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Make our program to the current one
	if (cRenderer.SetProgram(m_pProgram)) {
		// Calculate the world matrix
		Matrix4x4 mWorld;
		{
			// Build a rotation matrix by using a given euler angle around the y-axis
			mWorld.FromEulerAngleY(float(m_fRotation*Math::DegToRad));
		}

		// Set program uniforms
		ProgramUniform *pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
		if (pProgramUniform) {
			// Calculate the view matrix
			Matrix4x4 mView;
			{
				mView.SetTranslation(0.0f, 0.0f, -10.0f);
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

		// Set object space to world space matrix uniform
		pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToWorldSpaceMatrix");
		if (pProgramUniform)
			pProgramUniform->Set(mWorld);

		// Set world space light direction
		pProgramUniform = m_pProgram->GetUniform("LightDirection");
		if (pProgramUniform)
			pProgramUniform->Set(Vector3::UnitZ);

		// Get the mesh handler representing the scene to draw
		const MeshHandler *pMeshHandler = NULL;
		switch (nScene) {
			case 0:
				pMeshHandler = m_pMeshHandlerSphere;
				break;

			case 1:
				pMeshHandler = m_pMeshHandlerTorus;
				break;

			case 2:
				pMeshHandler = m_pMeshHandlerCube;
				break;
		}

		// Get the used mesh
		const Mesh *pMesh = pMeshHandler ? pMeshHandler->GetMesh() : NULL;
		if (pMesh) {
			// Get the mesh LOD level to use
			const MeshLODLevel *pLODLevel = pMesh->GetLODLevel(0);
			if (pLODLevel && pLODLevel->GetIndexBuffer()) {
				// Get and use the index buffer of the mesh LOD level
				cRenderer.SetIndexBuffer(pLODLevel->GetIndexBuffer());

				// Get the vertex buffer of the mesh handler
				VertexBuffer *pVertexBuffer = pMeshHandler->GetVertexBuffer();
				if (pVertexBuffer) {
					// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
					ProgramAttribute *pProgramAttribute = m_pProgram->GetAttribute("VertexPosition");
					if (pProgramAttribute)
						pProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);
					pProgramAttribute = m_pProgram->GetAttribute("VertexNormal");
					if (pProgramAttribute)
						pProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Normal);

					// Loop through all geometries of the mesh
					const Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
					for (uint32 nGeo=0; nGeo<lstGeometries.GetNumOfElements(); nGeo++) {
						// Is this geometry active?
						const Geometry &cGeometry = lstGeometries[nGeo];
						if (cGeometry.IsActive()) {
							// Draw the geometry
							cRenderer.DrawIndexedPrimitives(
								cGeometry.GetPrimitiveType(),
								0,
								pVertexBuffer->GetNumOfElements()-1,
								cGeometry.GetStartIndex(),
								cGeometry.GetIndexSize()
							);
						}
					}
				}
			}
		}
	}
}
