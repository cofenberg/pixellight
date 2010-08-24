/*********************************************************\
 *  File: ShaderProgram.cpp                              *
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
#include <PLGeneral/Log/Log.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Texture/TextureManager.h>
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/TextureBuffer1D.h"
#include "PLRendererOpenGL/TextureBuffer2D.h"
#include "PLRendererOpenGL/TextureBufferRectangle.h"
#include "PLRendererOpenGL/TextureBuffer3D.h"
#include "PLRendererOpenGL/TextureBufferCube.h"
#include "PLRendererOpenGL/ShaderProgram.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
ShaderProgram::~ShaderProgram()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShaderProgram::ShaderProgram(PLRenderer::Renderer &cRenderer, EType nType, const void *pProgram, const PLGeneral::String &sProfile,
							 const PLGeneral::String &sDefines, const PLGeneral::String &sEntry, const char **ppszAttributes) :
	PLRenderer::ShaderProgramCgBackend(cRenderer, nType, sDefines, sEntry)
{
	// [TODO] Use attributes

	// Check if there's an renderer and a program
	if (pProgram) {
		// Check Cg context
		if (!m_nContexCounter && !m_pCgContext) {
			PL_LOG(Info, PLGeneral::String::Format("Initialize Cg %d", CG_VERSION_NUM))
			m_pCgContext = cgCreateContext();
			cgSetErrorCallback(CgErrorCallback);

			// Delay program recompilation until the program object code is needed
			cgSetAutoCompile(m_pCgContext, CG_COMPILE_LAZY);
		}
		m_nContexCounter++;

		// Get combined shader program
		PLGeneral::String		  sCompleteProgram = "#define OPENGL\n";
		if (sDefines.GetLength()) sCompleteProgram += sDefines;
								  sCompleteProgram += (const char*)pProgram;

		// Initialize the shader program
		Init(sCompleteProgram.GetASCII(), cgGetProfile(sProfile));
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::ShaderProgramCgBackend functions ]
//[-------------------------------------------------------]
void ShaderProgram::Init(const void *pProgram, CGprofile pCgProfile)
{
	// Check parameter
	if (pProgram) {
		// Get the latest shader program profile if the given profile is invalid
		m_pCgProfile = pCgProfile;
		if (m_pCgProfile == CG_PROFILE_UNKNOWN) {
			if (GetType() == TypeVertexShaderProgram) {
				m_pCgProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
			} else if (GetType() == TypeFragmentShaderProgram) {
				m_pCgProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
			}
		}

		// Check if there's a profile
		if (m_pCgProfile != CG_PROFILE_UNKNOWN) {
			// Not working corrently for me with Cg 2.1
//			cgGLSetOptimalOptions(m_pCgProfile);

			// Create the program
			m_pCgProgram = cgCreateProgram(m_pCgContext, CG_SOURCE, (const char*)pProgram,
										   m_pCgProfile, GetEntry().GetLength() ? GetEntry() : "main", NULL);
			if (m_pCgProgram) {
				// Assemble the shader program with own error handling
				cgSetErrorCallback(NULL);
				cgGLLoadProgram(m_pCgProgram);
				cgSetErrorCallback(CgErrorCallback);
				CGerror nLastError = cgGetError();
				if (nLastError) {
					const char *pszListing = cgGetLastListing(m_pCgContext);
					PL_LOG(Error, PLGeneral::String::Format("Can't load Cg program! Error: %s", cgGetErrorString(nLastError)))
					if (pszListing)
						PL_LOG(Error, PLGeneral::String::Format("  >> %s", pszListing))

					// Cleanup the mess
					cgDestroyProgram(m_pCgProgram);
					m_pCgProgram = NULL;
					m_pCgProfile = CG_PROFILE_UNKNOWN;
				}
			} else {
				// Error!
				PL_LOG(Error, PLGeneral::String::Format("Can't create Cg program! Error: %s", cgGetErrorString(cgGetError())))
				m_pCgProfile = CG_PROFILE_UNKNOWN;
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::ShaderProgram functions   ]
//[-------------------------------------------------------]
bool ShaderProgram::MakeCurrent()
{
	// Check profile and program
	if (!m_pCgProfile || !m_pCgProgram)
		return false; // Error!

	// Enable profile and bind program
	cgGLEnableProfile(m_pCgProfile);
	cgGLBindProgram(m_pCgProgram);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Parameters functions       ]
//[-------------------------------------------------------]
int ShaderProgram::SetParameterTextureBuffer(const PLGeneral::String &sName, PLRenderer::TextureBuffer *pTextureBuffer)
{
	// Check parameter
	if (pTextureBuffer) {
		// Get Cg parameter
		CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
		if (pCgParameter) {
			// Check resource type
			switch (pTextureBuffer->GetType()) {
				case PLRenderer::Resource::TypeTextureBuffer1D:
					cgGLSetTextureParameter(pCgParameter, ((PLRendererOpenGL::TextureBuffer1D*)pTextureBuffer)->GetOpenGLTexture());
					break;

				case PLRenderer::Resource::TypeTextureBuffer2D:
					cgGLSetTextureParameter(pCgParameter, ((PLRendererOpenGL::TextureBuffer2D*)pTextureBuffer)->GetOpenGLTexture());
					break;

				case PLRenderer::Resource::TypeTextureBufferRectangle:
					cgGLSetTextureParameter(pCgParameter, ((PLRendererOpenGL::TextureBufferRectangle*)pTextureBuffer)->GetOpenGLTexture());
					break;

				case PLRenderer::Resource::TypeTextureBuffer3D:
					cgGLSetTextureParameter(pCgParameter, ((PLRendererOpenGL::TextureBuffer3D*)pTextureBuffer)->GetOpenGLTexture());
					break;

				case PLRenderer::Resource::TypeTextureBufferCube:
					cgGLSetTextureParameter(pCgParameter, ((PLRendererOpenGL::TextureBufferCube*)pTextureBuffer)->GetOpenGLTexture());
					break;
			}
			cgGLEnableTextureParameter(pCgParameter);

			// Get current texture stage and inform the renderer
			int nCurrentStage = cgGLGetTextureEnum(pCgParameter)-GL_TEXTURE0_ARB;
			if (nCurrentStage >= 0) {
				((Renderer&)pTextureBuffer->GetRenderer()).SetShaderProgramTextureBuffer(nCurrentStage, pTextureBuffer);

				// Done
				return nCurrentStage;
			}
		}
	}

	// Error!
	return -1;
}

int ShaderProgram::SetParameterTexture(const PLGeneral::String &sName, const PLGeneral::String &sFilename)
{
	// Try to get/load the texture
	return SetParameterTexture(sName, GetRenderer().GetRendererContext().GetTextureManager().LoadResource(sFilename));
}

int ShaderProgram::SetParameterTexture(const PLGeneral::String &sName, PLRenderer::Texture *pTexture)
{
	// Set texture buffer
	if (pTexture && pTexture->GetTextureBuffer()) {
		return SetParameterTextureBuffer(sName, pTexture->GetTextureBuffer());
	} else {
		// Error!
		return -1;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
