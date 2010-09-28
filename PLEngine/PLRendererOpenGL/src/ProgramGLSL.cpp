/*********************************************************\
 *  File: ProgramGLSL.cpp                                *
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
#include "PLRendererOpenGL/VertexShaderGLSL.h"
#include "PLRendererOpenGL/ShaderLanguageGLSL.h"
#include "PLRendererOpenGL/GeometryShaderGLSL.h"
#include "PLRendererOpenGL/FragmentShaderGLSL.h"
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/ShaderToolsGLSL.h"
#include "PLRendererOpenGL/ProgramAttributeGLSL.h"
#include "PLRendererOpenGL/ProgramUniformGLSL.h"
#include "PLRendererOpenGL/ProgramGLSL.h"


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
ProgramGLSL::~ProgramGLSL()
{
	// Destroy the attribute information
	DestroyAttributeInformation();

	// Destroy the uniform information
	DestroyUniformInformation();

	// Destroy the OpenGL program
	glDeleteObjectARB(m_nOpenGLProgram);
}

/**
*  @brief
*    Returns the OpenGL program
*/
GLuint ProgramGLSL::GetOpenGLProgram(bool bAutomaticLink)
{
	// Is the program already linked?
	if (!m_bLinked && bAutomaticLink) {
		// Program linked already failed? (so we don't see the linker errors only once!)
		if (!m_bLinkedFailed) {
			// Attach vertex shader
			if (!m_bVertexShaderAttached) {
				VertexShaderGLSL *pVertexShaderGLSL = (VertexShaderGLSL*)m_cVertexShaderHandler.GetResource();
				if (pVertexShaderGLSL) {
					glAttachObjectARB(m_nOpenGLProgram, pVertexShaderGLSL->GetOpenGLVertexShader());
					m_bVertexShaderAttached = true;
				}
			}

			// Attach geometry shader
			if (!m_bGeometryShaderAttached) {
				GeometryShaderGLSL *pGeometryShaderGLSL = (GeometryShaderGLSL*)m_cGeometryShaderHandler.GetResource();
				if (pGeometryShaderGLSL) {
					glAttachObjectARB(m_nOpenGLProgram, pGeometryShaderGLSL->GetOpenGLGeometryShader());
					m_bGeometryShaderAttached = true;
				}
			}

			// Attach fragment shader
			if (!m_bFragmentShaderAttached) {
				FragmentShaderGLSL *pFragmentShaderGLSL = (FragmentShaderGLSL*)m_cFragmentShaderHandler.GetResource();
				if (pFragmentShaderGLSL) {
					glAttachObjectARB(m_nOpenGLProgram, pFragmentShaderGLSL->GetOpenGLFragmentShader());
					m_bFragmentShaderAttached = true;
				}
			}

			// Link the program
			glLinkProgramARB(m_nOpenGLProgram);

			// Check the link status
			GLint nLinked = GL_FALSE;
			glGetObjectParameterivARB(m_nOpenGLProgram, GL_OBJECT_LINK_STATUS_ARB, &nLinked);
			if (nLinked == GL_TRUE) {
				// Congratulations, the program is now linked!
				m_bLinked = true;
			} else {
				// Error, program link failed!
				m_bLinkedFailed = true;
				ShaderToolsGLSL::WriteInformationIntoLog(m_nOpenGLProgram);
			}
		}
	}
	return m_nOpenGLProgram;
}

/**
*  @brief
*    Returns whether or not the program is currently linked
*/
bool ProgramGLSL::IsLinked() const
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
ProgramGLSL::ProgramGLSL(PLRenderer::Renderer &cRenderer) : Program(cRenderer),
	m_nOpenGLProgram(glCreateProgramObjectARB()),
	m_bLinked(false),
	m_bLinkedFailed(false),
	m_bVertexShaderAttached(false),
	m_bGeometryShaderAttached(false),
	m_bFragmentShaderAttached(false),
	m_bAttributeInformationBuild(false),
	m_bUniformInformationBuild(false)
{
}

/**
*  @brief
*    Denotes that a program relink is required
*/
void ProgramGLSL::RelinkRequired()
{
	// Is the program currently linked?
	if (m_bLinked) {
		// The linked state is now dirty
		m_bLinked = m_bLinkedFailed = false;

		// Destroy the attribute information
		DestroyAttributeInformation();

		// Destroy the uniform information
		DestroyUniformInformation();

		// The program is now dirty
		EventDirty.Emit(this);
	}
}

/**
*  @brief
*    Builds the attribute information
*/
void ProgramGLSL::BuildAttributeInformation()
{
	// Attribute information already build?
	if (!m_bAttributeInformationBuild) {
		// Get the OpenGL program - this also ensures that the program is linked
		const GLuint nOpenGLProgram = GetOpenGLProgram();

		// Is the program linked?
		if (m_bLinked) {
			// Get the number of active attributes
			GLint nNumOfActiveAttributes = 0;
			glGetObjectParameterivARB(nOpenGLProgram, GL_OBJECT_ACTIVE_ATTRIBUTES_ARB, &nNumOfActiveAttributes);
			if (nNumOfActiveAttributes) {
				// Get the length of the longest active attribute name, including a null terminator
				GLint nMaxNameLength = 0;
				glGetObjectParameterivARB(nOpenGLProgram, GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB, &nMaxNameLength);
				if (nMaxNameLength) {
					// Allocate the name buffer
					char *pszName = new char[nMaxNameLength];

					// Iterate over all attributes
					for (int i=0; i<nNumOfActiveAttributes; i++) {
						// Get the current attribute
						GLsizei nCurrentNameLength = 0;	// The actual number of characters written into pszName, excluding the null terminator
						int		nTypeSize		   = 0;	// The size of the attribute, the value is in units of the type, for arrays, normally 1
						GLenum  nType			   = 0;	// Attribute type, e.g. GL_FLOAT_VEC3
						glGetActiveAttribARB(nOpenGLProgram, i, nMaxNameLength, &nCurrentNameLength, &nTypeSize, &nType, pszName);

						// Get the attribute location
						const int nOpenGLAttributeLocation = glGetAttribLocationARB(nOpenGLProgram, pszName);
						if (nOpenGLAttributeLocation != -1) {
							// Create a new program attribute instance
							ProgramAttributeGLSL *pProgramAttribute = new ProgramAttributeGLSL(nOpenGLAttributeLocation);

							// Register the new program attribute
							m_lstAttributes.Add(pProgramAttribute);
							m_mapAttributes.Add(String(pszName, true, nCurrentNameLength), pProgramAttribute);
						}
					}

					// Destroy the name buffer
					delete [] pszName;
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
void ProgramGLSL::DestroyAttributeInformation()
{
	// Is there anything to destroy?
	const uint32 nNumOfAttributes = m_lstAttributes.GetNumOfElements();
	if (nNumOfAttributes) {
		// Destroy the attribute instances
		for (uint32 i=0; i<nNumOfAttributes; i++)
			delete (ProgramAttributeGLSL*)m_lstAttributes[i];

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
void ProgramGLSL::BuildUniformInformation()
{
	// Uniform information already build?
	if (!m_bUniformInformationBuild) {
		// Get the OpenGL program - this also ensures that the program is linked
		const GLuint nOpenGLProgram = GetOpenGLProgram();

		// Is the program linked?
		if (m_bLinked) {
			// Get the number of active uniforms
			GLint nNumOfActiveUniforms = 0;
			glGetObjectParameterivARB(nOpenGLProgram, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &nNumOfActiveUniforms);
			if (nNumOfActiveUniforms) {
				// Get the length of the longest active uniform name, including a null terminator
				GLint nMaxNameLength = 0;
				glGetObjectParameterivARB(nOpenGLProgram, GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB, &nMaxNameLength);
				if (nMaxNameLength) {
					// Allocate the name buffer
					char *pszName = new char[nMaxNameLength];

					// Next free texture unit which can be assigned to a sampler uniform
					int nNextFreeTextureUnit = 0;

					// Iterate over all uniforms
					for (int i=0; i<nNumOfActiveUniforms; i++) {
						// Get the current uniform
						GLsizei nCurrentNameLength = 0;	// The actual number of characters written into pszName, excluding the null terminator
						int		nTypeSize		   = 0;	// The size of the uniform, the value is in units of the type, for arrays, normally 1
						GLenum  nType			   = 0;	// Uniform type, e.g. GL_FLOAT_VEC3
						glGetActiveUniformARB(nOpenGLProgram, i, nMaxNameLength, &nCurrentNameLength, &nTypeSize, &nType, pszName);

						// Get the uniform location
						const int nOpenGLUniformLocation = glGetUniformLocationARB(nOpenGLProgram, pszName);
						if (nOpenGLUniformLocation != -1) {
							// Is this a sampler uniform?
							int nTextureUnit = -1;
							if (nType == GL_SAMPLER_1D_ARB || nType == GL_SAMPLER_2D_ARB || nType == GL_SAMPLER_3D_ARB || nType == GL_SAMPLER_CUBE_ARB ||
								nType == GL_SAMPLER_1D_SHADOW_ARB || nType == GL_SAMPLER_2D_SHADOW_ARB || nType == GL_SAMPLER_2D_RECT_ARB || nType == GL_SAMPLER_2D_RECT_SHADOW_ARB) {
								// Assign the next free texture unit
								nTextureUnit = nNextFreeTextureUnit;

								// Update the next free texture unit
								nNextFreeTextureUnit++;
							}

							// Create a new program uniform instance
							ProgramUniformGLSL *pProgramUniform = new ProgramUniformGLSL(nOpenGLProgram, nOpenGLUniformLocation, nTextureUnit);

							// Register the new program uniform
							m_lstUniforms.Add(pProgramUniform);
							m_mapUniforms.Add(String(pszName, true, nCurrentNameLength), pProgramUniform);
						}
					}

					// Destroy the name buffer
					delete [] pszName;
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
void ProgramGLSL::DestroyUniformInformation()
{
	// Is there anything to destroy?
	const uint32 nNumOfUniforms = m_lstUniforms.GetNumOfElements();
	if (nNumOfUniforms) {
		// Destroy the uniform instances
		for (uint32 i=0; i<nNumOfUniforms; i++)
			delete (ProgramUniformGLSL*)m_lstUniforms[i];

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
String ProgramGLSL::GetShaderLanguage() const
{
	return ShaderLanguageGLSL::GLSL;
}

PLRenderer::VertexShader *ProgramGLSL::GetVertexShader() const
{
	return (PLRenderer::VertexShader*)m_cVertexShaderHandler.GetResource();
}

bool ProgramGLSL::SetVertexShader(PLRenderer::VertexShader *pVertexShader)
{
	// Is the new vertex shader the same one as the current one?
	PLRenderer::VertexShader *pCurrentVertexShader = (PLRenderer::VertexShader*)m_cVertexShaderHandler.GetResource();
	if (pCurrentVertexShader != pVertexShader) {
		// The shader language of the program and the vertex shader must match
		if (pVertexShader && pVertexShader->GetShaderLanguage() != ShaderLanguageGLSL::GLSL)
			return false; // Error, shader language mismatch!

		// Detach the current vertex shader from the program
		if (pCurrentVertexShader && m_bVertexShaderAttached)
			glDetachObjectARB(m_nOpenGLProgram, ((VertexShaderGLSL*)pCurrentVertexShader)->GetOpenGLVertexShader());

		// Update the vertex shader resource handler
		m_cVertexShaderHandler.SetResource(pVertexShader);

		// Attached within "ProgramGLSL::GetOpenGLProgram()" on demand
		m_bVertexShaderAttached = false;

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

PLRenderer::GeometryShader *ProgramGLSL::GetGeometryShader() const
{
	return (PLRenderer::GeometryShader*)m_cGeometryShaderHandler.GetResource();
}

bool ProgramGLSL::SetGeometryShader(PLRenderer::GeometryShader *pGeometryShader)
{
	// Is the new geometry shader the same one as the current one?
	PLRenderer::GeometryShader *pCurrentGeometryShader = (PLRenderer::GeometryShader*)m_cGeometryShaderHandler.GetResource();
	if (pCurrentGeometryShader != pGeometryShader) {
		// The shader language of the program and the geometry shader must match
		if (pGeometryShader && pGeometryShader->GetShaderLanguage() != ShaderLanguageGLSL::GLSL)
			return false; // Error, shader language mismatch!

		// Detach the current geometry shader from the program
		if (pCurrentGeometryShader && m_bGeometryShaderAttached)
			glDetachObjectARB(m_nOpenGLProgram, ((GeometryShaderGLSL*)pCurrentGeometryShader)->GetOpenGLGeometryShader());

		// Update the geometry shader resource handler
		m_cGeometryShaderHandler.SetResource(pGeometryShader);

		// Attached within "ProgramGLSL::GetOpenGLProgram()" on demand
		m_bGeometryShaderAttached = false;

		// [TODO] Add methods
		// This settings will be used as soon as the OpenGL program get's linked, after linking the program, they are fixed
		glProgramParameteriEXT(m_nOpenGLProgram, GL_GEOMETRY_INPUT_TYPE_EXT,  GL_TRIANGLES);
		glProgramParameteriEXT(m_nOpenGLProgram, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP);
		GLint nTemp = 0;
		glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &nTemp);
		glProgramParameteriEXT(m_nOpenGLProgram, GL_GEOMETRY_VERTICES_OUT_EXT, nTemp);

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

PLRenderer::FragmentShader *ProgramGLSL::GetFragmentShader() const
{
	return (PLRenderer::FragmentShader*)m_cFragmentShaderHandler.GetResource();
}

bool ProgramGLSL::SetFragmentShader(PLRenderer::FragmentShader *pFragmentShader)
{
	// Is the new fragment shader the same one as the current one?
	PLRenderer::FragmentShader *pCurrentFragmentShader = (PLRenderer::FragmentShader*)m_cFragmentShaderHandler.GetResource();
	if (pCurrentFragmentShader != pFragmentShader) {
		// The shader language of the program and the fragment shader must match
		if (pFragmentShader && pFragmentShader->GetShaderLanguage() != ShaderLanguageGLSL::GLSL)
			return false; // Error, shader language mismatch!

		// Detach the current fragment shader from the program
		if (pCurrentFragmentShader && m_bFragmentShaderAttached)
			glDetachObjectARB(m_nOpenGLProgram, ((FragmentShaderGLSL*)pCurrentFragmentShader)->GetOpenGLFragmentShader());

		// Update the fragment shader resource handler
		m_cFragmentShaderHandler.SetResource(pFragmentShader);

		// Attached within "ProgramGLSL::GetOpenGLProgram()" on demand
		m_bFragmentShaderAttached = false;

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

const Array<PLRenderer::ProgramAttribute*> &ProgramGLSL::GetAttributes()
{
	// Build the attribute information, if required
	if (!m_bAttributeInformationBuild)
		BuildAttributeInformation();

	// Return the list of all attributes
	return m_lstAttributes;
}

PLRenderer::ProgramAttribute *ProgramGLSL::GetAttribute(const String &sName)
{
	// Build the attribute information, if required
	if (!m_bAttributeInformationBuild)
		BuildAttributeInformation();

	// Return the requested attribute
	return m_mapAttributes.Get(sName);
}

const Array<PLRenderer::ProgramUniform*> &ProgramGLSL::GetUniforms()
{
	// Build the uniform information, if required
	if (!m_bUniformInformationBuild)
		BuildUniformInformation();

	// Return the list of all uniforms
	return m_lstUniforms;
}

PLRenderer::ProgramUniform *ProgramGLSL::GetUniform(const String &sName)
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
bool ProgramGLSL::MakeCurrent()
{
	// Get the OpenGL program - this also ensures that the program is linked
	const GLuint nOpenGLProgram = GetOpenGLProgram();

	// Is the OpenGL program linked?
	if (IsLinked()) {
		// Make this to the currently used program
		glUseProgramObjectARB(nOpenGLProgram);

		// Enable all vertex attribute arrays
		for (uint32 i=0; i<m_lstAttributes.GetNumOfElements(); i++)
			glEnableVertexAttribArrayARB(((ProgramAttributeGLSL*)m_lstAttributes[i])->m_nOpenGLAttributeLocation);

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

bool ProgramGLSL::UnmakeCurrent()
{
	// Disable all vertex attribute arrays
	for (uint32 i=0; i<m_lstAttributes.GetNumOfElements(); i++)
		glDisableVertexAttribArrayARB(((ProgramAttributeGLSL*)m_lstAttributes[i])->m_nOpenGLAttributeLocation);

	// Currently, no program is set
	glUseProgramObjectARB(0);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void ProgramGLSL::BackupDeviceData(uint8 **ppBackup)
{
	if (m_nOpenGLProgram) {
		// Call the relink method, this automatically destroys the used resources
		RelinkRequired();

		// Destroy the OpenGL program
		glDeleteObjectARB(m_nOpenGLProgram);
		m_nOpenGLProgram = NULL;
	}
}

void ProgramGLSL::RestoreDeviceData(uint8 **ppBackup)
{
	if (!m_nOpenGLProgram) {
		m_nOpenGLProgram = glCreateProgramObjectARB();
		m_bVertexShaderAttached = m_bGeometryShaderAttached = m_bFragmentShaderAttached = false;

		// Call the relink method, this automatically destroys the used resources
		RelinkRequired();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
