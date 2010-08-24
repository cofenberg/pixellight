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
#include "PLRendererD3D9/TextureBuffer1D.h"
#include "PLRendererD3D9/TextureBuffer2D.h"
#include "PLRendererD3D9/TextureBufferRectangle.h"
#include "PLRendererD3D9/TextureBuffer3D.h"
#include "PLRendererD3D9/TextureBufferCube.h"
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/ShaderProgram.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
ShaderProgram::~ShaderProgram()
{
	// Check Cg context
	if (!(m_nContexCounter-1) && m_pCgContext)
		cgD3D9SetDevice(NULL);
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

	// Check if there's a program
	if (pProgram) {
		// Check Cg context
		if (!m_nContexCounter && !m_pCgContext) {
			PL_LOG(Info, PLGeneral::String::Format("Initialize Cg %d", CG_VERSION_NUM))
			m_pCgContext = cgCreateContext();
			cgSetErrorCallback(CgErrorCallback);

			// [TODO] Check this, looks like this is NOT working correctly!
			// Delay program recompilation until the program object code is needed
//			cgSetAutoCompile(m_pCgContext, CG_COMPILE_LAZY);
		}
		m_nContexCounter++;

		// Get combined shader program
		PLGeneral::String sCompleteProgram = "#define D3D\n";
		if (sDefines.GetLength())
			sCompleteProgram += sDefines;
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
			// [TODO] Some shader programs are NOT working correctly on my system, this functions return for me CG_PROFILE_VS_3_0 and CG_PROFILE_PS_3_0
			if (GetType() == TypeVertexShaderProgram)
				m_pCgProfile = CG_PROFILE_VS_2_X;
			else if (GetType() == TypeFragmentShaderProgram)
				m_pCgProfile = CG_PROFILE_PS_2_X;
//			if (GetType() == VertexShaderProgram)
//				m_pCgProfile = cgD3D9GetLatestVertexProfile();
//			else if (GetType() == FragmentShaderProgram)
//				m_pCgProfile = cgD3D9GetLatestPixelProfile();
		}

		// Check if there's a profile
		if (m_pCgProfile != CG_PROFILE_UNKNOWN) {
			// [TODO] Check/test this
			// Grab the optimal options for the profile
//			const char **ppszOptions[] = { NULL };
			// Hm, I received a compiler error using this...
			const char **ppszOptions[] = { cgD3D9GetOptimalOptions(m_pCgProfile), NULL};

			// Create the program
			m_pCgProgram = cgCreateProgram(m_pCgContext, CG_SOURCE, (const char*)pProgram,
										   m_pCgProfile, GetEntry().GetLength() ? GetEntry() : "main", *ppszOptions);
			if (m_pCgProgram) {
				// Assemble the shader program with own error handling
				cgSetErrorCallback(NULL);
				// [TODO] Check this, if I set this to CG_TRUE I get a lot of graphics bugs
				cgD3D9LoadProgram(m_pCgProgram, CG_FALSE, 0);
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
	cgD3D9BindProgram(m_pCgProgram);

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
			IDirect3DBaseTexture9 *pD3DTexture = NULL;
			switch (pTextureBuffer->GetType()) {
				case PLRenderer::Resource::TypeTextureBuffer1D:
					pD3DTexture = ((PLRendererD3D9::TextureBuffer1D*)pTextureBuffer)->GetD3D9Texture();
					break;

				case PLRenderer::Resource::TypeTextureBuffer2D:
					pD3DTexture = ((PLRendererD3D9::TextureBuffer2D*)pTextureBuffer)->GetD3D9Texture();
					break;

				case PLRenderer::Resource::TypeTextureBufferRectangle:
					pD3DTexture = ((PLRendererD3D9::TextureBufferRectangle*)pTextureBuffer)->GetD3D9Texture();
					break;

				case PLRenderer::Resource::TypeTextureBuffer3D:
					pD3DTexture = ((PLRendererD3D9::TextureBuffer3D*)pTextureBuffer)->GetD3D9Texture();
					break;

				case PLRenderer::Resource::TypeTextureBufferCube:
					pD3DTexture = ((PLRendererD3D9::TextureBufferCube*)pTextureBuffer)->GetD3D9Texture();
					break;
			}
			cgD3D9SetTexture(pCgParameter, pD3DTexture);

			// Get current texture stage and inform the renderer... intricate but I can't find another way to
			// get the texture stage the texture was bound to...
			Renderer	     &cRenderer = (Renderer&)GetRenderer();
			LPDIRECT3DDEVICE9 pD3DDevice = cRenderer.GetDevice();
			if (pD3DDevice) {
				uint32 nMaxTextureUnits = cRenderer.GetCapabilities().nMaxTextureUnits;
				for (uint32 i=0; i<nMaxTextureUnits; i++) {
					IDirect3DBaseTexture9 *pCurrentTexture = NULL;
					pD3DDevice->GetTexture(i, &pCurrentTexture);
					if (pD3DTexture == pCurrentTexture)
						return i; // Done
				}
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
} // PLRenderer
