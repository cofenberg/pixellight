/*********************************************************\
 *  File: GeometryShaderCg.cpp                           *
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
#include <PLGeneral/Tools/Wrapper.h>
#include <PLGeneral/Core/MemoryManager.h>
#include "PLRendererOpenGLCg/ShaderLanguageCg.h"
#include "PLRendererOpenGLCg/ShaderToolsCg.h"
#include "PLRendererOpenGLCg/GeometryShaderCg.h"


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
GeometryShaderCg::~GeometryShaderCg()
{
	// Destroy the Cg geometry program
	if (m_pCgGeometryProgram)
		cgDestroyProgram(m_pCgGeometryProgram);

	// Release a Cg context reference
	ShaderToolsCg::ReleaseCgContextReference();
}

/**
*  @brief
*    Returns the Cg profile
*/
CGprofile GeometryShaderCg::GetCgProfile() const
{
	return m_pCgProfile;
}

/**
*  @brief
*    Returns the Cg geometry program
*/
CGprogram GeometryShaderCg::GetCgGeometryProgram() const
{
	return m_pCgGeometryProgram;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GeometryShaderCg::GeometryShaderCg(PLRenderer::Renderer &cRenderer) : PLRenderer::GeometryShader(cRenderer),
	m_pCgProfile(CG_PROFILE_UNKNOWN),
	m_pCgGeometryProgram(nullptr)
{
	// Add a Cg context reference
	ShaderToolsCg::AddCgContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Shader functions           ]
//[-------------------------------------------------------]
String GeometryShaderCg::GetShaderLanguage() const
{
	return ShaderLanguageCg::Cg;
}

String GeometryShaderCg::GetSourceCode() const
{
	return m_pCgGeometryProgram ? cgGetProgramString(m_pCgGeometryProgram, CG_PROGRAM_SOURCE) : "";
}

String GeometryShaderCg::GetProfile() const
{
	return cgGetProfileString(m_pCgProfile);
}

String GeometryShaderCg::GetEntry() const
{
	return m_sEntry;
}

bool GeometryShaderCg::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sEntry)
{
	// Destroy the previous Cg geometry program, if there's one
	if (m_pCgGeometryProgram) {
		cgDestroyProgram(m_pCgGeometryProgram);
		m_pCgGeometryProgram = nullptr;
	}

	// Get the profile from a user given string
	m_pCgProfile = cgGetProfile(sProfile.GetLength() ? sProfile : "glslg"); // We're using a GLSL profile as default so ATI users have resonable shader support when using Cg

	// On unknown or invalid profile, choose a fallback profile
	if (m_pCgProfile == CG_PROFILE_UNKNOWN || (!cgGetProfileProperty(m_pCgProfile, CG_IS_GEOMETRY_PROFILE) && m_pCgProfile != CG_PROFILE_GLSLG)) {
		m_pCgProfile = cgGLGetLatestProfile(CG_GL_GEOMETRY);
		if (m_pCgProfile == CG_PROFILE_UNKNOWN && cgGLIsProfileSupported(CG_PROFILE_GLSLG))
			m_pCgProfile = CG_PROFILE_GLSLG;
	}

	// Create the Cg geometry program
	if (m_pCgProfile != CG_PROFILE_UNKNOWN)
		m_pCgGeometryProgram = ShaderToolsCg::CreateCgProgram(m_pCgProfile, sSourceCode, sEntry);

	// Was the Cg program created successfully?
	if (m_pCgGeometryProgram) {
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
void GeometryShaderCg::BackupDeviceData(uint8 **ppBackup)
{
	// Backup data
	const char *pszProgram = m_pCgGeometryProgram ? cgGetProgramString(m_pCgGeometryProgram, CG_PROGRAM_SOURCE) : nullptr;
	if (pszProgram) {
		const uint32 nNumOfBytes = Wrapper::GetStringLength(pszProgram) + 1;
		*ppBackup = new uint8[nNumOfBytes];
		MemoryManager::Copy(*ppBackup, pszProgram, nNumOfBytes);
		cgDestroyProgram(m_pCgGeometryProgram);
		m_pCgGeometryProgram = nullptr;
	} else {
		*ppBackup = nullptr;
	}
}

void GeometryShaderCg::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup) {
		// The string class takes over the control of the string memory and also deletes it
		SetSourceCode(String(reinterpret_cast<char*>(*ppBackup), false), GetProfile(), m_sEntry);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
