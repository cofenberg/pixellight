/*********************************************************\
 *  File: TessellationControlShaderCg.cpp                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/Tools/Wrapper.h>
#include <PLCore/Core/MemoryManager.h>
#include "PLRendererOpenGLCg/ShaderLanguageCg.h"
#include "PLRendererOpenGLCg/CgContext.h"
#include "PLRendererOpenGLCg/TessellationControlShaderCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
TessellationControlShaderCg::~TessellationControlShaderCg()
{
	// Destroy the Cg tessellation control program
	if (m_pCgTessellationControlProgram)
		cgDestroyProgram(m_pCgTessellationControlProgram);

	// Release a Cg context reference
	CgContext::ReleaseCgContextReference();
}

/**
*  @brief
*    Returns the Cg profile
*/
CGprofile TessellationControlShaderCg::GetCgProfile() const
{
	return m_pCgProfile;
}

/**
*  @brief
*    Returns the Cg tessellation control program
*/
CGprogram TessellationControlShaderCg::GetCgTessellationControlProgram() const
{
	return m_pCgTessellationControlProgram;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TessellationControlShaderCg::TessellationControlShaderCg(PLRenderer::Renderer &cRenderer) : PLRenderer::TessellationControlShader(cRenderer),
	m_pCgProfile(CG_PROFILE_UNKNOWN),
	m_pCgTessellationControlProgram(nullptr)
{
	// Add a Cg context reference
	CgContext::AddCgContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Shader functions           ]
//[-------------------------------------------------------]
String TessellationControlShaderCg::GetShaderLanguage() const
{
	return ShaderLanguageCg::Cg;
}

String TessellationControlShaderCg::GetSourceCode() const
{
	return m_pCgTessellationControlProgram ? cgGetProgramString(m_pCgTessellationControlProgram, CG_PROGRAM_SOURCE) : "";
}

String TessellationControlShaderCg::GetProfile() const
{
	return cgGetProfileString(m_pCgProfile);
}

String TessellationControlShaderCg::GetArguments() const
{
	return m_sArguments;
}

String TessellationControlShaderCg::GetEntry() const
{
	return m_sEntry;
}

bool TessellationControlShaderCg::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sArguments, const String &sEntry)
{
	// Destroy the previous Cg tessellation control program, if there's one
	if (m_pCgTessellationControlProgram) {
		cgDestroyProgram(m_pCgTessellationControlProgram);
		m_pCgTessellationControlProgram = nullptr;
	}

	// Get the profile from a user given string
	// -> "February 2012 version of Cg 3.1": No GLSL tessellation control shader support, at least one that's not using special NVIDIA-only extensions
	m_pCgProfile = cgGetProfile(sProfile);
//	m_pCgProfile = cgGetProfile(sProfile.GetLength() ? sProfile : "?"); // We're using a GLSL profile as default so ATI users have reasonable shader support when using Cg

	// On unknown or invalid profile, choose a fallback profile
	if (m_pCgProfile == CG_PROFILE_UNKNOWN || (!cgGetProfileProperty(m_pCgProfile, CG_IS_TESSELLATION_CONTROL_PROFILE) && m_pCgProfile != CG_PROFILE_GLSLF)) {
		m_pCgProfile = cgGLGetLatestProfile(CG_GL_TESSELLATION_CONTROL);
		if (m_pCgProfile == CG_PROFILE_UNKNOWN && cgGLIsProfileSupported(CG_PROFILE_GLSLF))
			m_pCgProfile = CG_PROFILE_GLSLF;
	}

	// Create the Cg tessellation control program
	if (m_pCgProfile != CG_PROFILE_UNKNOWN)
		m_pCgTessellationControlProgram = CgContext::CreateCgProgram(m_pCgProfile, sSourceCode, sArguments, sEntry);

	// Was the Cg program created successfully?
	if (m_pCgTessellationControlProgram) {
		// Backup the optional shader compiler arguments and the user defined entry point
		m_sArguments = sArguments;
		m_sEntry     = sEntry;

		// Done
		return true;
	} else {
		m_pCgProfile = CG_PROFILE_UNKNOWN;
		m_sArguments = "";
		m_sEntry     = "";

		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void TessellationControlShaderCg::BackupDeviceData(uint8 **ppBackup)
{
	// Backup data
	const char *pszProgram = m_pCgTessellationControlProgram ? cgGetProgramString(m_pCgTessellationControlProgram, CG_PROGRAM_SOURCE) : nullptr;
	if (pszProgram) {
		const uint32 nNumOfBytes = Wrapper::GetStringLength(pszProgram) + 1;
		*ppBackup = new uint8[nNumOfBytes];
		MemoryManager::Copy(*ppBackup, pszProgram, nNumOfBytes);
		cgDestroyProgram(m_pCgTessellationControlProgram);
		m_pCgTessellationControlProgram = nullptr;
	} else {
		*ppBackup = nullptr;
	}
}

void TessellationControlShaderCg::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup) {
		// The string class takes over the control of the string memory and also deletes it
		SetSourceCode(String(reinterpret_cast<char*>(*ppBackup), false), GetProfile(), m_sArguments, m_sEntry);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
