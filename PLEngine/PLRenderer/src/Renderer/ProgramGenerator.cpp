/*********************************************************\
 *  File: ProgramGenerator.cpp                           *
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
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/Program.h"
#include "PLRenderer/Renderer/VertexShader.h"
#include "PLRenderer/Renderer/FragmentShader.h"
#include "PLRenderer/Renderer/ShaderLanguage.h"
#include "PLRenderer/Renderer/ProgramGenerator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Removes precision qualifiers from the given GLSL shader source code
*/
String ProgramGenerator::ApplyGLSLHacks(const String &sSourceCode)
{
	// Please note, this hacks are not really robust and may cause errors in certain situations,
	// but because this is just a hack for a buggy driver and currently works for our shaders,
	// it should do the job...

	// Remove precision qualifiers
	String sModifiedSourceCode = sSourceCode;
	sModifiedSourceCode.Replace("lowp",    "");
	sModifiedSourceCode.Replace("mediump", "");
	sModifiedSourceCode.Replace("highp",   "");

	// Done
	return sModifiedSourceCode;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramGenerator::ProgramGenerator(Renderer &cRenderer, const String &sShaderLanguage, const String &sVertexShader, const String &sVertexShaderProfile,
								   const String &sFragmentShader, const String &sFragmentShaderProfile, bool bGLSLHacks) :
	EventHandlerDirty(&ProgramGenerator::OnDirty, this),
	m_pRenderer(&cRenderer),
	m_sShaderLanguage(sShaderLanguage),
	m_sVertexShader(sVertexShader),
	m_sVertexShaderProfile(sVertexShaderProfile),
	m_sFragmentShader(sFragmentShader),
	m_sFragmentShaderProfile(sFragmentShaderProfile)
{
	// [HACK] Precision qualifiers within GLSL source code and NVIDIA GPU's (see ApplyGLSLHacks() documentation)
	if (bGLSLHacks && m_sShaderLanguage == "GLSL" && cRenderer.GetClass()->GetClassName() != "PLRendererOpenGLES::Renderer") {
		m_sVertexShader   = ApplyGLSLHacks(m_sVertexShader);
		m_sFragmentShader = ApplyGLSLHacks(m_sFragmentShader);
	}
}

/**
*  @brief
*    Destructor
*/
ProgramGenerator::~ProgramGenerator()
{
	// Clear the cache of the program generator
	ClearCache();
}

/**
*  @brief
*    Returns the name of the used shader language
*/
String ProgramGenerator::GetShaderLanguage() const
{
	return m_sShaderLanguage;
}

/**
*  @brief
*    Returns the used vertex shader source code
*/
String ProgramGenerator::GetVertexShaderSourceCode() const
{
	return m_sVertexShader;
}

/**
*  @brief
*    Returns the used fragment shader source code
*/
String ProgramGenerator::GetFragmentShaderSourceCode() const
{
	return m_sFragmentShader;
}

/**
*  @brief
*    Returns a program
*/
ProgramGenerator::GeneratedProgram *ProgramGenerator::GetProgram(const Flags &cFlags)
{
	// Get the unique vertex shader and fragment shader ID's, we're taking the flags for this :D
	const uint32 nVertexShaderID   = cFlags.GetVertexShaderFlags();
	const uint32 nFragmentShaderID = cFlags.GetFragmentShaderFlags();

	// Combine the two ID's into an unique 64 bit integer we can use to reference the linked program
	const uint64 nProgramID = nVertexShaderID + uint64(uint64(nFragmentShaderID)<<32);

	// Is there already a generated program with the requested flags?
	GeneratedProgram *pGeneratedProgram = m_mapPrograms.Get(nProgramID);
	if (!pGeneratedProgram) {
		// Is there already a vertex shader with the requested flags?
		VertexShader *pVertexShader = m_mapVertexShaders.Get(nVertexShaderID);
		if (!pVertexShader) {
			// Get the shader language to use
			ShaderLanguage *pShaderLanguage = m_pRenderer->GetShaderLanguage(m_sShaderLanguage);
			if (pShaderLanguage) {
				// Create a new vertex shader instance
				pVertexShader = pShaderLanguage->CreateVertexShader();
				if (pVertexShader) {
					// Add flag definitions to the shader source code
					String sSourceCode;
					const Array<const char *> &lstVertexShaderDefinitions = cFlags.GetVertexShaderDefinitions();
					const uint32 nNumOfVertexShaderDefinitions = lstVertexShaderDefinitions.GetNumOfElements();
					for (uint32 i=0; i<nNumOfVertexShaderDefinitions; i++) {
						// Get the flag definition
						const char *pszDefinition = lstVertexShaderDefinitions[i];
						if (pszDefinition)
							sSourceCode += String::Format("#define %s\n", pszDefinition);
					}

					// Add the shader source code
					sSourceCode += m_sVertexShader;

					// Set the combined shader source code
					pVertexShader->SetSourceCode(sSourceCode, m_sVertexShaderProfile);

					// Add the created shader to the cache of the program generator
					m_lstVertexShaders.Add(pVertexShader);
					m_mapVertexShaders.Add(nVertexShaderID, pVertexShader);
				}
			}
		}

		// If we have no vertex shader, we don't need to continue constructing a program...
		if (pVertexShader) {
			// Is there already a fragment shader with the requested flags?
			FragmentShader *pFragmentShader = m_mapFragmentShaders.Get(nFragmentShaderID);
			if (!pFragmentShader) {
				// Get the shader language to use
				ShaderLanguage *pShaderLanguage = m_pRenderer->GetShaderLanguage(m_sShaderLanguage);
				if (pShaderLanguage) {
					// Create a new fragment shader instance
					pFragmentShader = pShaderLanguage->CreateFragmentShader();
					if (pFragmentShader) {
						// Add flag definitions to the shader source code
						String sSourceCode;
						const Array<const char *> &lstFragmentShaderDefinitions = cFlags.GetFragmentShaderDefinitions();
						const uint32 nNumOfFragmentShaderDefinitions = lstFragmentShaderDefinitions.GetNumOfElements();
						for (uint32 i=0; i<nNumOfFragmentShaderDefinitions; i++) {
							// Get the flag definition
							const char *pszDefinition = lstFragmentShaderDefinitions[i];
							if (pszDefinition)
								sSourceCode += String::Format("#define %s\n", pszDefinition);
						}

						// Add the shader source code
						sSourceCode += m_sFragmentShader;

						// Set the combined shader source code
						pFragmentShader->SetSourceCode(sSourceCode, m_sFragmentShaderProfile);

						// Add the created shader to the cache of the program generator
						m_lstFragmentShaders.Add(pFragmentShader);
						m_mapFragmentShaders.Add(nFragmentShaderID, pFragmentShader);
					}
				}
			}

			// If we have no fragment shader, we don't need to continue constructing a program...
			if (pFragmentShader) {
				// Get the shader language to use
				ShaderLanguage *pShaderLanguage = m_pRenderer->GetShaderLanguage(m_sShaderLanguage);
				if (pShaderLanguage) {
					// Create a program instance
					Program *pProgram = pShaderLanguage->CreateProgram();
					if (pProgram) {
						// Assign the created vertex and fragment shaders to the program
						pProgram->SetVertexShader(pVertexShader);
						pProgram->SetFragmentShader(pFragmentShader);

						// Create a generated program contained
						pGeneratedProgram = new GeneratedProgram;
						pGeneratedProgram->pProgram			    = pProgram;
						pGeneratedProgram->nVertexShaderFlags   = cFlags.GetVertexShaderFlags();
						pGeneratedProgram->nFragmentShaderFlags = cFlags.GetFragmentShaderFlags();
						pGeneratedProgram->pUserData			= nullptr;

						// Add our nark which will inform us as soon as the program gets dirty
						pProgram->EventDirty.Connect(&EventHandlerDirty);

						// Add the created program to the cache of the program generator
						m_lstPrograms.Add(pGeneratedProgram);
						m_mapPrograms.Add(nProgramID, pGeneratedProgram);
					}
				}
			}
		}
	}

	// Return the program
	return pGeneratedProgram;
}

/**
*  @brief
*    Clears the cache of the program generator
*/
void ProgramGenerator::ClearCache()
{
	// Destroy all generated program instances
	for (uint32 i=0; i<m_lstPrograms.GetNumOfElements(); i++) {
		GeneratedProgram *pGeneratedProgram = m_lstPrograms[i];
		delete pGeneratedProgram->pProgram;
		if (pGeneratedProgram->pUserData)
			delete pGeneratedProgram->pUserData;
		delete pGeneratedProgram;
	}
	m_lstPrograms.Clear();
	m_mapPrograms.Clear();

	// Destroy all generated fragment shader instances
	for (uint32 i=0; i<m_lstFragmentShaders.GetNumOfElements(); i++)
		delete m_lstFragmentShaders[i];
	m_lstFragmentShaders.Clear();
	m_mapFragmentShaders.Clear();

	// Destroy all generated vertex shader instances
	for (uint32 i=0; i<m_lstVertexShaders.GetNumOfElements(); i++)
		delete m_lstVertexShaders[i];
	m_lstVertexShaders.Clear();
	m_mapVertexShaders.Clear();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
ProgramGenerator::ProgramGenerator(const ProgramGenerator &cSource) :
	m_pRenderer(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
ProgramGenerator &ProgramGenerator::operator =(const ProgramGenerator &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Called when a program became dirty
*/
void ProgramGenerator::OnDirty(Program *pProgram)
{
	// Search for the generated program and destroy the user data
	for (uint32 i=0; i<m_lstPrograms.GetNumOfElements(); i++) {
		GeneratedProgram *pGeneratedProgram = m_lstPrograms[i];
		if (pGeneratedProgram->pProgram == pProgram) {
			// Is there user data we can destroy?
			if (pGeneratedProgram->pUserData) {
				delete pGeneratedProgram->pUserData;
				pGeneratedProgram->pUserData = nullptr;
			}

			// We're done, get us out of the loop
			i = m_lstPrograms.GetNumOfElements();
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
