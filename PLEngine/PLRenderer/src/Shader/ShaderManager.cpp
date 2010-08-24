/*********************************************************\
 *  File: ShaderManager.cpp                              *
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
#include <PLGeneral/Tools/Profiling.h>
#include <PLGeneral/Log/Log.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Shader/ShaderManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner renderer context of this manager
*/
RendererContext &ShaderManager::GetRendererContext() const
{
	return *m_pRendererContext;
}

/**
*  @brief
*    Load a shader
*/
Shader *ShaderManager::Load(const String &sName, const String &sFilename, const String &sProfile,
							const String &sDefines, const String &sEntry)
{
	// Is the profile available?
	if (sProfile.GetLength()) {
		if (!m_pRendererContext->GetRenderer().IsShaderProgramProfileSupported(sProfile))
			return NULL; // Error!
	}

	// Load shader
	Shader *pShader = Get(sName);
	if (pShader)
		return pShader; // Done
	else {
		// Create the shader
		pShader = Create(sName);
		if (pShader) {
			// Load in
			String sType;
			String sFilenameT = sFilename;
			if (sFilenameT[sFilenameT.GetLength()-1] == '+') {
				static const String Fragment = "Fragment";
				sType = Fragment; // Fragment program
				sFilenameT.Delete(sFilenameT.GetLength()-1); // Remove the '+' at the end
			} else {
				static const String Vertex = "Vertex";
				sType = Vertex;  // Vertex program
			}
			if (pShader->Load(sFilenameT, "Type=\"" + sType + "\" Profile=\"" + sProfile + "\" Defines=\"" + sDefines + "\" Entry=\"" + sEntry + '\"'))
				return pShader; // Done

			// Cleanup on error
			delete pShader;
		}
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Load a shader
*/
Shader *ShaderManager::Load(const String &sName, File &cFile, bool bFragmentShader, const String &sProfile,
							const String &sDefines, const String &sEntry)
{
	// Is the profile available?
	if (sProfile.GetLength()) {
		if (!m_pRendererContext->GetRenderer().IsShaderProgramProfileSupported(sProfile))
			return NULL; // Error!
	}

	// Load shader
	Shader *pShader = Get(sName);
	if (pShader)
		return pShader; // Done
	else {
		// Create the shader
		pShader = Create(sName);
		if (pShader) {
			// Load in
			static const String Fragment = "Fragment";
			static const String Vertex   = "Vertex";
			if (pShader->Load(cFile, "Type=\"" + (bFragmentShader ? Fragment : Vertex) + "\" Profile=\"" + sProfile + "\" Defines=\"" + sDefines + "\" Entry=\"" + sEntry + '\"'))
				return pShader; // Done

			// Cleanup on error
			delete pShader;
		}
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Reloads all shaders
*/
bool ShaderManager::ReloadShaders()
{
	bool bResult = true; // No error by default

	for (uint32 i=0; i<m_lstResources.GetNumOfElements(); i++) {
		Shader *pShader = m_lstResources[i];
		if (!pShader->Reload())
			bResult = false; // Error!
	}

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShaderManager::ShaderManager(RendererContext &cRendererContext) :
	m_pRendererContext(&cRendererContext)
{
	PL_LOG(Debug, "Create shader manager")

	// Set manager name
	SetManagerName("Shader manager");

	// Unload unused resources, please
	SetUnloadUnused(true);
}

/**
*  @brief
*    Destructor
*/
ShaderManager::~ShaderManager()
{
	PL_LOG(Debug, "Destroy shader manager")

	// Clear all shaders
	Clear();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ResourceManager functions     ]
//[-------------------------------------------------------]
Shader *ShaderManager::CreateResource(const String &sName)
{
	return new Shader(*this, sName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
