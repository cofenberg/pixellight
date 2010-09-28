/*********************************************************\
 *  File: VertexShaderCg.cpp                             *
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
#include <PLGeneral/Tools/Wrapper.h>
#include <PLGeneral/Core/MemoryManager.h>
#include "PLRendererOpenGLCg/ShaderLanguageCg.h"
#include "PLRendererOpenGLCg/ShaderToolsCg.h"
#include "PLRendererOpenGLCg/VertexShaderCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
VertexShaderCg::~VertexShaderCg()
{
	// Destroy the Cg vertex program
	if (m_pCgVertexProgram)
		cgDestroyProgram(m_pCgVertexProgram);

	// Release a Cg context reference
	ShaderToolsCg::ReleaseCgContextReference();
}

/**
*  @brief
*    Returns the Cg profile
*/
CGprofile VertexShaderCg::GetCgProfile() const
{
	return m_pCgProfile;
}

/**
*  @brief
*    Returns the Cg vertex program
*/
CGprogram VertexShaderCg::GetCgVertexProgram() const
{
	return m_pCgVertexProgram;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VertexShaderCg::VertexShaderCg(PLRenderer::Renderer &cRenderer) : PLRenderer::VertexShader(cRenderer),
	m_pCgProfile(CG_PROFILE_UNKNOWN),
	m_pCgVertexProgram(NULL)
{
	// Add a Cg context reference
	ShaderToolsCg::AddCgContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::AbstractShader functions   ]
//[-------------------------------------------------------]
String VertexShaderCg::GetShaderLanguage() const
{
	return ShaderLanguageCg::Cg;
}

String VertexShaderCg::GetSourceCode() const
{
	return m_pCgVertexProgram ? cgGetProgramString(m_pCgVertexProgram, CG_PROGRAM_SOURCE) : "";
}

String VertexShaderCg::GetProfile() const
{
	return cgGetProfileString(m_pCgProfile);
}

String VertexShaderCg::GetEntry() const
{
	return m_sEntry;
}

bool VertexShaderCg::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sEntry)
{
	// Destroy the previous Cg vertex program, if there's one
	if (m_pCgVertexProgram) {
		cgDestroyProgram(m_pCgVertexProgram);
		m_pCgVertexProgram = NULL;
	}

	// Get the profile from a user given string
	m_pCgProfile = cgGetProfile(sProfile.GetLength() ? sProfile : "glslv"); // We're using a GLSL profile as default so ATI users have resonable shader support when using Cg

	// On unknown or invalid profile, choose a fallback profile
	if (m_pCgProfile == CG_PROFILE_UNKNOWN || (!cgGetProfileProperty(m_pCgProfile, CG_IS_VERTEX_PROFILE) && m_pCgProfile != CG_PROFILE_GLSLV)) {
		m_pCgProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
		if (m_pCgProfile == CG_PROFILE_UNKNOWN && cgGLIsProfileSupported(CG_PROFILE_GLSLV))
			m_pCgProfile = CG_PROFILE_GLSLV;
	}

	// Create the Cg vertex program
	if (m_pCgProfile != CG_PROFILE_UNKNOWN)
		m_pCgVertexProgram = ShaderToolsCg::CreateCgProgram(m_pCgProfile, sSourceCode, sEntry);

	// Was the Cg program created successfully?
	if (m_pCgVertexProgram) {
		// Backup the user defined entry point
		m_sEntry = sEntry;

		// Done
		return true;
	} else {
		m_pCgProfile = CG_PROFILE_UNKNOWN;
		m_sEntry     = "";

		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void VertexShaderCg::BackupDeviceData(uint8 **ppBackup)
{
	// Backup data
	const char *pszProgram = m_pCgVertexProgram ? cgGetProgramString(m_pCgVertexProgram, CG_PROGRAM_SOURCE) : NULL;
	if (pszProgram) {
		const uint32 nNumOfBytes = Wrapper::GetStringLength(pszProgram) + 1;
		*ppBackup = new uint8[nNumOfBytes];
		MemoryManager::Copy(*ppBackup, pszProgram, nNumOfBytes);
		cgDestroyProgram(m_pCgVertexProgram);
		m_pCgVertexProgram = NULL;
	} else {
		*ppBackup = NULL;
	}
}

void VertexShaderCg::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup) {
		// The string class takes over the control of the string memory and also deletes it
		SetSourceCode(String((char*)*ppBackup, false), GetProfile(), m_sEntry);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
