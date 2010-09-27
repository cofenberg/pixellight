/*********************************************************\
 *  File: SPRTTShaders.cpp                               *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/Rectangle.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/VertexShader.h>
#include <PLRenderer/Renderer/ShaderLanguage.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Renderer/FragmentShader.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include "SPRTTShaders.h"


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
pl_implement_class(SPRTTShaders)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SPRTTShaders::SPRTTShaders(Renderer &cRenderer) : SPRTT(cRenderer),
	m_pRenderTarget(NULL),
	m_pColorTarget1(NULL),
	m_pColorTarget2(NULL),
	m_pColorTarget3(NULL),
	m_pSceneVertexShader(NULL),
	m_pSceneFragmentShader(NULL),
	m_pSceneProgram(NULL),
	m_pVertexShader(NULL),
	m_pFragmentShader(NULL),
	m_pProgram(NULL)
{
	// Check/get number of supported color render targets
	uint8 nMaxColorTargets = 4;
	if (nMaxColorTargets > cRenderer.GetCapabilities().nMaxColorRenderTargets)
		nMaxColorTargets = cRenderer.GetCapabilities().nMaxColorRenderTargets;

	{ // Render targets
		// Create the render target. We will create a very low resolution 2D texture buffer to see funny pixels.
		m_pRenderTarget = cRenderer.CreateSurfaceTextureBuffer2D(Vector2i(64, 64), TextureBuffer::R8G8B8, SurfaceTextureBuffer::Depth|SurfaceTextureBuffer::NoMultisampleAntialiasing, nMaxColorTargets);
		if (m_pRenderTarget && nMaxColorTargets > 1) {
			// Set additional color render targets
			if (nMaxColorTargets > 1 && !m_pColorTarget1) {
				Image cImage;
				ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
				pImageBuffer->CreateImage(DataByte, ColorRGB, Vector3i(64, 64, 1));
				m_pColorTarget1 = cRenderer.CreateTextureBuffer2D(cImage, TextureBuffer::Unknown, TextureBuffer::RenderTarget);
			}
			if (nMaxColorTargets > 2 && !m_pColorTarget2) {
				Image cImage;
				ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
				pImageBuffer->CreateImage(DataByte, ColorRGB, Vector3i(64, 64, 1));
				m_pColorTarget2 = cRenderer.CreateTextureBuffer2D(cImage, TextureBuffer::Unknown, TextureBuffer::RenderTarget);
			}
			if (nMaxColorTargets > 3 && !m_pColorTarget3) {
				Image cImage;
				ImageBuffer *pImageBuffer = cImage.CreatePart()->CreateMipmap();
				pImageBuffer->CreateImage(DataByte, ColorRGB, Vector3i(64, 64, 1));
				m_pColorTarget3 = cRenderer.CreateTextureBuffer2D(cImage, TextureBuffer::Unknown, TextureBuffer::RenderTarget);
			}
		}
	}

	// Decide which shader language should be used (for example "GLSL" or "Cg")
	ShaderLanguage *pShaderLanguage = cRenderer.GetShaderLanguage(cRenderer.GetDefaultShaderLanguage());
	if (pShaderLanguage) {
		{ // Scene program (with MRT support)
			// Shader source code
			String sVertexShaderSourceCode;
			String sFragmentShaderSourceCode;
			if (pShaderLanguage->GetShaderLanguage() == "GLSL") {
				#include "SPRTTShaders_GLSL.h"
				sVertexShaderSourceCode   = ProgramGenerator::ApplyGLSLHacks(sSceneVertexShaderSourceCodeGLSL);
				sFragmentShaderSourceCode = ProgramGenerator::ApplyGLSLHacks(sSceneFragmentShaderSourceCodeGLSL);
			} else if (pShaderLanguage->GetShaderLanguage() == "Cg") {
				#include "SPRTTShaders_Cg.h"
				sVertexShaderSourceCode   = sSceneVertexShaderSourceCodeCg;
				sFragmentShaderSourceCode = sSceneFragmentShaderSourceCodeCg;
			}

			// Create a vertex shader instance
			m_pSceneVertexShader = pShaderLanguage->CreateVertexShader();
			if (m_pSceneVertexShader) {
				// Set the vertex shader source code - I define a Cg profile, because if I don't and use Cg as shader language, MRT is not working (?)
				m_pSceneVertexShader->SetSourceCode(sVertexShaderSourceCode, "arbvp1");
			}

			// Create a fragment shader instance
			m_pSceneFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pSceneFragmentShader) {
				// Set the fragment shader source code - I define a Cg profile, because if I don't and use Cg as shader language, MRT is not working (?)
				m_pSceneFragmentShader->SetSourceCode(sFragmentShaderSourceCode, "arbfp1");
			}

			// Create a program instance
			m_pSceneProgram = pShaderLanguage->CreateProgram();
			if (m_pSceneProgram) {
				// Assign the created vertex and fragment shaders to the program
				m_pSceneProgram->SetVertexShader(m_pSceneVertexShader);
				m_pSceneProgram->SetFragmentShader(m_pSceneFragmentShader);
			}
		}

		{ // Program
			// Shader source code
			String sVertexShaderSourceCode;
			String sFragmentShaderSourceCode;
			if (pShaderLanguage->GetShaderLanguage() == "GLSL") {
				#include "SPRTTShaders_GLSL.h"
				sVertexShaderSourceCode   = ProgramGenerator::ApplyGLSLHacks(sVertexShaderSourceCodeGLSL);
				sFragmentShaderSourceCode = ProgramGenerator::ApplyGLSLHacks(sFragmentShaderSourceCodeGLSL);
			} else if (pShaderLanguage->GetShaderLanguage() == "Cg") {
				#include "SPRTTShaders_Cg.h"
				sVertexShaderSourceCode   = sVertexShaderSourceCodeCg;
				sFragmentShaderSourceCode = sFragmentShaderSourceCodeCg;
			}

			// Create a vertex shader instance
			m_pVertexShader = pShaderLanguage->CreateVertexShader();
			if (m_pVertexShader) {
				// Set the vertex shader source code
				m_pVertexShader->SetSourceCode(sVertexShaderSourceCode);
			}

			// Create a fragment shader instance
			m_pFragmentShader = pShaderLanguage->CreateFragmentShader();
			if (m_pFragmentShader) {
				// Set the fragment shader source code
				m_pFragmentShader->SetSourceCode(sFragmentShaderSourceCode);
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
}

/**
*  @brief
*    Destructor
*/
SPRTTShaders::~SPRTTShaders()
{
	// Destroy the render targets
	if (m_pRenderTarget)
		delete m_pRenderTarget;
	if (m_pColorTarget1)
		delete m_pColorTarget1;
	if (m_pColorTarget2)
		delete m_pColorTarget2;
	if (m_pColorTarget3)
		delete m_pColorTarget3;

	// Cleanup
	if (m_pSceneProgram)
		delete m_pSceneProgram;
	if (m_pSceneFragmentShader)
		delete m_pSceneFragmentShader;
	if (m_pSceneVertexShader)
		delete m_pSceneVertexShader;
	if (m_pProgram)
		delete m_pProgram;
	if (m_pFragmentShader)
		delete m_pFragmentShader;
	if (m_pVertexShader)
		delete m_pVertexShader;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws the scene
*/
void SPRTTShaders::DrawScene(Renderer &cRenderer)
{
	// Clear the content of the current used render target
	cRenderer.Clear();

	// Make our program to the current one
	if (cRenderer.SetProgram(m_pSceneProgram)) {
		// Calculate the world matrix
		Matrix4x4 mWorld;
		{
			// Build a rotation matrix by using a given euler angle around the y-axis
			mWorld.FromEulerAngleY(float(m_fRotation*Math::DegToRad));
		}

		// Set program uniforms
		ProgramUniform *pProgramUniform = m_pSceneProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
		if (pProgramUniform) {
			// Calculate the view matrix
			Matrix4x4 mView;
			{
				mView.SetTranslation(0.0f, -0.1f, -0.5f);
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
		pProgramUniform = m_pSceneProgram->GetUniform("ObjectSpaceToWorldSpaceMatrix");
		if (pProgramUniform)
			pProgramUniform->Set(mWorld);

		// Set world space light direction
		pProgramUniform = m_pSceneProgram->GetUniform("LightDirection");
		if (pProgramUniform)
			pProgramUniform->Set(Vector3::UnitZ);

		// Get the used mesh
		const Mesh *pMesh = m_pMeshHandler->GetMesh();
		if (pMesh) {
			// Get the mesh LOD level to use
			const MeshLODLevel *pLODLevel = pMesh->GetLODLevel(0);
			if (pLODLevel && pLODLevel->GetIndexBuffer()) {
				// Get and use the index buffer of the mesh LOD level
				cRenderer.SetIndexBuffer(pLODLevel->GetIndexBuffer());

				// Get the vertex buffer of the mesh handler
				VertexBuffer *pVertexBuffer = m_pMeshHandler->GetVertexBuffer();
				if (pVertexBuffer) {
					// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
					ProgramAttribute *pProgramAttribute = m_pSceneProgram->GetAttribute("VertexPosition");
					if (pProgramAttribute)
						pProgramAttribute->Set(pVertexBuffer, PLRenderer::VertexBuffer::Position);
					pProgramAttribute = m_pSceneProgram->GetAttribute("VertexNormal");
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


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::SurfacePainter functions  ]
//[-------------------------------------------------------]
void SPRTTShaders::OnPaint(Surface &cSurface)
{
	// Get the used renderer
	Renderer &cRenderer = GetRenderer();

	// Clear the content of the current used render target
	cRenderer.Clear();

	// Backup current render target and set the new one to render in our texture buffer
	Surface *pRenderSurfaceBackup = cRenderer.GetRenderTarget();
	if (cRenderer.SetRenderTarget(m_pRenderTarget)) {
		if (m_pColorTarget1)
			cRenderer.SetColorRenderTarget((TextureBuffer*)m_pColorTarget1, 1);
		if (m_pColorTarget2)
			cRenderer.SetColorRenderTarget((TextureBuffer*)m_pColorTarget2, 2);
		if (m_pColorTarget3)
			cRenderer.SetColorRenderTarget((TextureBuffer*)m_pColorTarget3, 3);

		// Draw the scene
		DrawScene(cRenderer);

		// Reset render target
		cRenderer.SetRenderTarget(pRenderSurfaceBackup);
	}

	// This code is similar to the code of the triangle demo. But instead of a
	// triangle we will draw three rotating quadrangles. Further the used vertex
	// buffer has texture coordinates and we apply the 'teapot' texture buffer on the primitives.
	// Clear the content of the current used render target

	// Make our program to the current one
	if (cRenderer.SetProgram(m_pProgram)) {
		// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
		ProgramAttribute *pProgramAttribute = m_pProgram->GetAttribute("VertexPosition");
		if (pProgramAttribute)
			pProgramAttribute->Set(m_pPositionVertexBuffer, PLRenderer::VertexBuffer::Position);
		pProgramAttribute = m_pProgram->GetAttribute("VertexTextureCoordinate");
		if (pProgramAttribute)
			pProgramAttribute->Set(m_pPositionVertexBuffer, PLRenderer::VertexBuffer::TexCoord);
		pProgramAttribute = m_pProgram->GetAttribute("VertexColor");
		if (pProgramAttribute)
			pProgramAttribute->Set(m_pColorVertexBuffer, PLRenderer::VertexBuffer::Color);

		// Set color factor
		ProgramUniform *pProgramUniform = m_pProgram->GetUniform("ColorFactor");
		if (pProgramUniform)
			pProgramUniform->Set(0.0f);

		// Calculate the composed view projection matrix - we need it multiple times
		Matrix4x4 mViewProjection;
		{
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

			// Calculate the composed view projection matrix
			mViewProjection = mProjection*mView;
		}

		// No back face culling, please. Else we can only see one 'side' of the quadrangle
		cRenderer.SetRenderState(RenderState::CullMode, Cull::None);

		Matrix4x4 mWorld;
		{ // Draw quadrangle 1: Primary render target
			// Set object space to clip space matrix uniform
			pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
			if (pProgramUniform) {
				mWorld.SetTranslationMatrix(2.0f, 1.0f, 0.0f);
				pProgramUniform->Set(mViewProjection*mWorld);
			}

			// Set the texture buffer we rendered our teapot in as the current texture buffer
			pProgramUniform = m_pProgram->GetUniform("DiffuseMap");
			if (pProgramUniform) {
				const int nTextureUnit = pProgramUniform->Set(m_pRenderTarget->GetTextureBuffer());
				if (nTextureUnit >= 0) {
					// Disable mip mapping - this is required because we created/filled no mipmaps for your texture buffer
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
		}

		{ // Draw quadrangle 2: Color render target 1
			// Set object space to clip space matrix uniform
			pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
			if (pProgramUniform) {
				mWorld.FromEulerAngleY(float(m_fRotation*Math::DegToRad));
				mWorld.SetTranslation(-2.0f, 1.0f, 0.0f);
				pProgramUniform->Set(mViewProjection*mWorld);
			}

			// Set the texture buffer we rendered our teapot in as the current texture buffer
			pProgramUniform = m_pProgram->GetUniform("DiffuseMap");
			if (pProgramUniform) {
				const int nTextureUnit = pProgramUniform->Set(m_pColorTarget1 ? (TextureBuffer*)m_pColorTarget1 : m_pRenderTarget->GetTextureBuffer());
				if (nTextureUnit >= 0) {
					// Disable mip mapping - this is required because we created/filled no mipmaps for your texture buffer
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
		}

		{ // Draw quadrangle 3: Color render target 2
			// Set object space to clip space matrix uniform
			pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
			if (pProgramUniform) {
				mWorld.FromEulerAngleZ(float(m_fRotation*Math::DegToRad));
				mWorld.SetTranslation(0.0f, 1.0f, 0.0f);
				pProgramUniform->Set(mViewProjection*mWorld);
			}

			// Set the texture buffer we rendered our teapot in as the current texture buffer
			pProgramUniform = m_pProgram->GetUniform("DiffuseMap");
			if (pProgramUniform) {
				const int nTextureUnit = pProgramUniform->Set(m_pColorTarget2 ? (TextureBuffer*)m_pColorTarget2 : m_pRenderTarget->GetTextureBuffer());
				if (nTextureUnit >= 0) {
					// Disable mip mapping - this is required because we created/filled no mipmaps for your texture buffer
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
		}

		{ // Draw quadrangle 4: Color render target 3
			// Set object space to clip space matrix uniform
			pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
			if (pProgramUniform) {
				mWorld.FromEulerAngleZ(float(-m_fRotation*Math::DegToRad));
				mWorld.SetTranslation(-2.0f, -1.0f, 0.0f);
				pProgramUniform->Set(mViewProjection*mWorld);
			}

			// Set the texture buffer we rendered our teapot in as the current texture buffer
			pProgramUniform = m_pProgram->GetUniform("DiffuseMap");
			if (pProgramUniform) {
				const int nTextureUnit = pProgramUniform->Set(m_pColorTarget3 ? (TextureBuffer*)m_pColorTarget3 : m_pRenderTarget->GetTextureBuffer());
				if (nTextureUnit >= 0) {
					// Disable mip mapping - this is required because we created/filled no mipmaps for your texture buffer
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
		}

		{ // Draw quadrangle 4: Primary render target, but with per vertex color - the primitive will be quite colorful :)
			// Set object space to clip space matrix uniform
			pProgramUniform = m_pProgram->GetUniform("ObjectSpaceToClipSpaceMatrix");
			if (pProgramUniform) {
				mWorld.FromEulerAngleZ(float(-m_fRotation*Math::DegToRad));
				mWorld.SetTranslation(2.0f, -1.0f, 0.0f);
				pProgramUniform->Set(mViewProjection*mWorld);
			}

			// Set color factor
			pProgramUniform = m_pProgram->GetUniform("ColorFactor");
			if (pProgramUniform)
				pProgramUniform->Set(1.0f);

			// Set the texture buffer we rendered our teapot in as the current texture buffer
			pProgramUniform = m_pProgram->GetUniform("DiffuseMap");
			if (pProgramUniform) {
				const int nTextureUnit = pProgramUniform->Set(m_pRenderTarget->GetTextureBuffer());
				if (nTextureUnit >= 0) {
					// Disable mip mapping - this is required because we created/filled no mipmaps for your texture buffer
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
					cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
				}
			}

			// Draw
			cRenderer.DrawPrimitives(Primitive::TriangleStrip, 0, 4);
		}

		// Change the backface culling back to the default setting
		cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);
	}

	// Increase the rotation by the current time difference (time past since the last frame)
	// -> Normally, such work should NOT be performed within the rendering step, but we want
	//    to keep the implementation simple in here...
	m_fRotation += Timing::GetInstance()->GetTimeDifference()*50;
}
