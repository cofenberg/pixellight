/*********************************************************\
 *  File: ProgramCg.cpp                                  *
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
#include "PLRendererOpenGL/VertexShaderCg.h"
#include "PLRendererOpenGL/GeometryShaderCg.h"
#include "PLRendererOpenGL/FragmentShaderCg.h"
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/ShaderToolsCg.h"
#include "PLRendererOpenGL/ProgramAttributeCg.h"
#include "PLRendererOpenGL/ProgramUniformCg.h"
#include "PLRendererOpenGL/ProgramCg.h"


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
ProgramCg::~ProgramCg()
{
	// Call the relink method, this automatically destroys the used resources
	RelinkRequired();
}

/**
*  @brief
*    Returns the Cg combined program
*/
CGprogram ProgramCg::GetCgCombinedProgram(bool bAutomaticLink)
{
	// Is the program already linked?
	if (!m_bLinked && bAutomaticLink) {
		// Program linked already failed? (so we don't see the linker errors only once!)
		if (!m_bLinkedFailed) {
			// If one shader is using GLSL, ALL other shaders must use GLSL as well!
			bool bGLSL = false;

			// There must be a vertex and a fragment shader
			VertexShaderCg *pVertexShader = (VertexShaderCg*)m_cVertexShaderHandler.GetResource();
			if (pVertexShader) {
				// Is this a GLSL vertex shader?
				if (pVertexShader->GetCgProfile() == CG_PROFILE_GLSLV)
					bGLSL = true;

				// Get the fragment shader
				FragmentShaderCg *pFragmentShader = (FragmentShaderCg*)m_cFragmentShaderHandler.GetResource();
				if (pFragmentShader) {
					// Is this a GLSL fragment shader?
					if (pFragmentShader->GetCgProfile() == CG_PROFILE_GLSLF && !bGLSL) {
						// Error!
						PL_LOG(Error, "Fragment shader is using GLSL, but vertex shader is not!")
					} else {
						// Geometry shader is optional
						GeometryShaderCg *pGeometryShader = (GeometryShaderCg*)m_cGeometryShaderHandler.GetResource();

						// Create the Cg combined program
						if (pGeometryShader) {
							// Is this a GLSL geometry shader?
							if (pGeometryShader->GetCgProfile() == CG_PROFILE_GLSLG && !bGLSL) {
								// Error!
								PL_LOG(Error, "Geometry shader is using GLSL, but vertex shader and fragment shader don't use GLSL!")
							} else {
								// Vertex shader, geometry shader and fragment shader
								m_pCgCombinedProgram = cgCombinePrograms3(pVertexShader->GetCgVertexProgram(), pGeometryShader->GetCgGeometryProgram(), pFragmentShader->GetCgFragmentProgram());
							}
						} else {
							// Just vertex shader and fragment shader
							m_pCgCombinedProgram = cgCombinePrograms2(pVertexShader->GetCgVertexProgram(), pFragmentShader->GetCgFragmentProgram());
						}
					}
				}
			}

			// Was the Cg combined program created successfully?
			if (m_pCgCombinedProgram) {
				// Load the Cg combined program
				cgGLLoadProgram(m_pCgCombinedProgram);

				// cgGLIsProgramLoaded has an ugly different behaviour when not using GLSL...
				if (bGLSL) {
					// Was the program loaded successfully?
					if (cgGLIsProgramLoaded(m_pCgCombinedProgram)) {
						// Congratulations, the program is now linked!
						m_bLinked = true;
					} else {
						// Error, program link failed!
						m_bLinkedFailed = true;
					}
				} else {
					// Iterate through all Cg programs of the Cg combined program
					const int nNumOfProgramDomains = cgGetNumProgramDomains(m_pCgCombinedProgram);
					for (int i=0; i<nNumOfProgramDomains && !m_bLinkedFailed; i++) {
						// Get the Cg program of the current domain
						CGprogram pCgDomainProgram = cgGetProgramDomainProgram(m_pCgCombinedProgram, i);

						// Was the program loaded successfully? If not, the whole linking failed!
						if (!cgGLIsProgramLoaded(pCgDomainProgram))
							m_bLinkedFailed = true;
					}

					// Congratulations, the program is now linked!
					if (!m_bLinkedFailed)
						m_bLinked = true;
				}
			} else {
				// Error, program link failed!
				m_bLinkedFailed = true;
			}
		}
	}

	// Return the Cg combined program
	return m_pCgCombinedProgram;
}

/**
*  @brief
*    Returns whether or not the program is currently linked
*/
bool ProgramCg::IsLinked() const
{
	return m_bLinked;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramCg::ProgramCg(PLRenderer::Renderer &cRenderer) : PLRenderer::Program(cRenderer),
	m_pCgCombinedProgram(NULL),
	m_bLinked(false),
	m_bLinkedFailed(false),
	m_bAttributeInformationBuild(false),
	m_bUniformInformationBuild(false)
{
}

/**
*  @brief
*    Denotes that a program relink is required
*/
void ProgramCg::RelinkRequired()
{
	// The linked state is now dirty
	m_bLinked = m_bLinkedFailed = false;

	// Destroy the attribute information
	DestroyAttributeInformation();

	// Destroy the uniform information
	DestroyUniformInformation();

	// Destroy the tCg combined program
	if (m_pCgCombinedProgram) {
		cgDestroyProgram(m_pCgCombinedProgram);
		m_pCgCombinedProgram = NULL;
	}

	// The program is now dirty
	EventDirty.Emit(this);
}

/**
*  @brief
*    Builds the attribute information
*/
void ProgramCg::BuildAttributeInformation()
{
	// Attribute information already build?
	if (!m_bAttributeInformationBuild) {
		// Get the Cg combined program - this also ensures that the program is linked
		CGprogram pCgCombinedProgram = GetCgCombinedProgram();

		// Is the program linked?
		if (m_bLinked) {
			// Iterate through all Cg programs of the Cg combined program
			const int nNumOfProgramDomains = cgGetNumProgramDomains(pCgCombinedProgram);
			for (int i=0; i<nNumOfProgramDomains; i++) {
				// Get the Cg program of the current domain
				CGprogram pCgDomainProgram = cgGetProgramDomainProgram(pCgCombinedProgram, i);

				// Iterate through all Cg parameters of the Cg vertex program
				CGparameter pCgParameter = cgGetFirstParameter(pCgDomainProgram, CG_PROGRAM);
				while (pCgParameter) {
					// Is this an attribute?
					if (cgGetParameterVariability(pCgParameter) == CG_VARYING) {
						// Register the new program attribute
						ProgramAttributeCg *pProgramAttribute = new ProgramAttributeCg(pCgParameter);
						m_lstAttributes.Add(pProgramAttribute);
						m_mapAttributes.Add(cgGetParameterName(pCgParameter), pProgramAttribute);
					}

					// Next Cg parameter, please
					pCgParameter = cgGetNextParameter(pCgParameter);
				}
			}

			// The attribute information build is now build
			m_bAttributeInformationBuild = true;
		}
	}
}

/**
*  @brief
*    Destroys the attribute information
*/
void ProgramCg::DestroyAttributeInformation()
{
	// Is there anything to destroy?
	const uint32 nNumOfAttributes = m_lstAttributes.GetNumOfElements();
	if (nNumOfAttributes) {
		// Destroy the attribute instances
		for (uint32 i=0; i<nNumOfAttributes; i++)
			delete (ProgramAttributeCg*)m_lstAttributes[i];

		// Clear the attribute list and hash map
		m_lstAttributes.Clear();
		m_mapAttributes.Clear();
	}

	// Currently, there's no attribute information build
	m_bAttributeInformationBuild = false;
}

/**
*  @brief
*    Builds the uniform information
*/
void ProgramCg::BuildUniformInformation()
{
	// Uniform information already build?
	if (!m_bUniformInformationBuild) {
		// Get the Cg combined program - this also ensures that the program is linked
		CGprogram pCgCombinedProgram = GetCgCombinedProgram();

		// Is the program linked?
		if (m_bLinked) {
			// Iterate through all Cg programs of the Cg combined program
			const int nNumOfProgramDomains = cgGetNumProgramDomains(pCgCombinedProgram);
			for (int i=0; i<nNumOfProgramDomains; i++) {
				// Get the Cg program of the current domain
				CGprogram pCgDomainProgram = cgGetProgramDomainProgram(pCgCombinedProgram, i);

				// Iterate through all Cg parameters of the Cg vertex program
				CGparameter pCgParameter = cgGetFirstParameter(pCgDomainProgram, CG_PROGRAM);
				while (pCgParameter) {
					// Is this an uniform?
					if (cgGetParameterVariability(pCgParameter) == CG_UNIFORM) {
						// Register the new program uniform
						ProgramUniformCg *pProgramUniform = new ProgramUniformCg(pCgParameter);
						m_lstUniforms.Add(pProgramUniform);
						m_mapUniforms.Add(cgGetParameterName(pCgParameter), pProgramUniform);
					}

					// Next Cg parameter, please
					pCgParameter = cgGetNextParameter(pCgParameter);
				}
			}

			// The uniform information build is now build
			m_bUniformInformationBuild = true;
		}
	}
}

/**
*  @brief
*    Destroys the uniform information
*/
void ProgramCg::DestroyUniformInformation()
{
	// Is there anything to destroy?
	const uint32 nNumOfUniforms = m_lstUniforms.GetNumOfElements();
	if (nNumOfUniforms) {
		// Destroy the uniform instances
		for (uint32 i=0; i<nNumOfUniforms; i++)
			delete (ProgramUniformCg*)m_lstUniforms[i];

		// Clear the uniform list and hash map
		m_lstUniforms.Clear();
		m_mapUniforms.Clear();
	}

	// Currently, there's no uniform information build
	m_bUniformInformationBuild = false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Program functions          ]
//[-------------------------------------------------------]
String ProgramCg::GetShaderLanguage() const
{
	return Renderer::ShaderLanguageCg;
}

PLRenderer::VertexShader *ProgramCg::GetVertexShader() const
{
	return (PLRenderer::VertexShader*)m_cVertexShaderHandler.GetResource();
}

bool ProgramCg::SetVertexShader(PLRenderer::VertexShader *pVertexShader)
{
	// Is the new vertex shader the same one as the current one?
	PLRenderer::VertexShader *pCurrentVertexShader = (PLRenderer::VertexShader*)m_cVertexShaderHandler.GetResource();
	if (pCurrentVertexShader != pVertexShader) {
		// The shader language of the program and the vertex shader must match and the vertex shader must be valid!
		if (pVertexShader && (pVertexShader->GetShaderLanguage() != Renderer::ShaderLanguageCg ||
			!((PLRendererOpenGL::VertexShaderCg*)pVertexShader)->GetCgVertexProgram()))
			return false; // Error!

		// Update the vertex shader resource handler
		m_cVertexShaderHandler.SetResource(pVertexShader);

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

PLRenderer::GeometryShader *ProgramCg::GetGeometryShader() const
{
	return (PLRenderer::GeometryShader*)m_cGeometryShaderHandler.GetResource();
}

bool ProgramCg::SetGeometryShader(PLRenderer::GeometryShader *pGeometryShader)
{
	// Is the new geometry shader the same one as the current one?
	PLRenderer::GeometryShader *pCurrentGeometryShader = (PLRenderer::GeometryShader*)m_cGeometryShaderHandler.GetResource();
	if (pCurrentGeometryShader != pGeometryShader) {
		// The shader language of the program and the geometry shader must match and the geometry shader must be valid!
		if (pGeometryShader && (pGeometryShader->GetShaderLanguage() != Renderer::ShaderLanguageCg ||
			!((PLRendererOpenGL::GeometryShaderCg*)pGeometryShader)->GetCgGeometryProgram()))
			return false; // Error, shader language mismatch!

		// Update the geometry shader resource handler
		m_cGeometryShaderHandler.SetResource(pGeometryShader);

		// [TODO] Add methods for geometry shader

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

PLRenderer::FragmentShader *ProgramCg::GetFragmentShader() const
{
	return (PLRenderer::FragmentShader*)m_cFragmentShaderHandler.GetResource();
}

bool ProgramCg::SetFragmentShader(PLRenderer::FragmentShader *pFragmentShader)
{
	// Is the new fragment shader the same one as the current one?
	PLRenderer::FragmentShader *pCurrentFragmentShader = (PLRenderer::FragmentShader*)m_cFragmentShaderHandler.GetResource();
	if (pCurrentFragmentShader != pFragmentShader) {
		// The shader language of the program and the fragment shader must match and the fragment shader must be valid!
		if (pFragmentShader && (pFragmentShader->GetShaderLanguage() != Renderer::ShaderLanguageCg ||
			!((PLRendererOpenGL::FragmentShaderCg*)pFragmentShader)->GetCgFragmentProgram()))
			return false; // Error, shader language mismatch!

		// Update the fragment shader resource handler
		m_cFragmentShaderHandler.SetResource(pFragmentShader);

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

const Array<PLRenderer::ProgramAttribute*> &ProgramCg::GetAttributes()
{
	// Build the attribute information, if required
	if (!m_bAttributeInformationBuild)
		BuildAttributeInformation();

	// Return the list of all attributes
	return m_lstAttributes;
}

PLRenderer::ProgramAttribute *ProgramCg::GetAttribute(const String &sName)
{
	// Build the attribute information, if required
	if (!m_bAttributeInformationBuild)
		BuildAttributeInformation();

	// Return the requested attribute
	return m_mapAttributes.Get(sName);
}

const Array<PLRenderer::ProgramUniform*> &ProgramCg::GetUniforms()
{
	// Build the uniform information, if required
	if (!m_bUniformInformationBuild)
		BuildUniformInformation();

	// Return the list of all uniforms
	return m_lstUniforms;
}

PLRenderer::ProgramUniform *ProgramCg::GetUniform(const String &sName)
{
	// Build the uniform information, if required
	if (!m_bUniformInformationBuild)
		BuildUniformInformation();

	// Return the requested uniform
	return m_mapUniforms.Get(sName);
}


//[-------------------------------------------------------]
//[ Protected virtual PLRenderer::Program functions       ]
//[-------------------------------------------------------]
bool ProgramCg::MakeCurrent()
{
	// Get the Cg combined program - this also ensures that the program is linked
	CGprogram pCgCombinedProgram = GetCgCombinedProgram();
	if (pCgCombinedProgram) {
		// Bind the Cg combined program
		cgGLBindProgram(pCgCombinedProgram);

		// Iterate through all Cg programs of the Cg combined program and enable all required profiles
		const int nNumOfProgramDomains = cgGetNumProgramDomains(pCgCombinedProgram);
		for (int i=0; i<nNumOfProgramDomains; i++)
			cgGLEnableProfile(cgGetProgramDomainProfile(pCgCombinedProgram, i));

		// Done
		return true;
	}

	// Error!
	return false;
}

bool ProgramCg::UnmakeCurrent()
{
	// There must be a Cg combined program
	if (m_pCgCombinedProgram) {
		// Iterate through all Cg programs of the Cg combined program and disable all required profiles
		const int nNumOfProgramDomains = cgGetNumProgramDomains(m_pCgCombinedProgram);
		for (int i=0; i<nNumOfProgramDomains; i++)
			cgGLDisableProfile(cgGetProgramDomainProfile(m_pCgCombinedProgram, i));

		// [HACK] When using GLSL as Cg profile we need to use 'glUseProgramObjectARB()' to deactivate shaders
		glUseProgramObjectARB(0);
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void ProgramCg::BackupDeviceData(uint8 **ppBackup)
{
	// Call the relink method, this automatically destroys the used resources
	RelinkRequired();
}

void ProgramCg::RestoreDeviceData(uint8 **ppBackup)
{
	// Call the relink method, this automatically destroys the used resources
	RelinkRequired();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
