/*********************************************************\
 *  File: ProgramCg.cpp                                  *
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
#include <PLGeneral/Log/Log.h>
#include "PLRendererOpenGLCg/VertexShaderCg.h"
#include "PLRendererOpenGLCg/ShaderLanguageCg.h"
#include "PLRendererOpenGLCg/GeometryShaderCg.h"
#include "PLRendererOpenGLCg/FragmentShaderCg.h"
#include "PLRendererOpenGLCg/ShaderToolsCg.h"
#include "PLRendererOpenGLCg/ProgramAttributeCg.h"
#include "PLRendererOpenGLCg/ProgramUniformCg.h"
#include "PLRendererOpenGLCg/ProgramUniformBlockCg.h"
#include "PLRendererOpenGLCg/ProgramCg.h"
#include <GL/gl.h>
#include "../../../External/Recommended/OpenGL/glext.h"


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
			VertexShaderCg *pVertexShader = static_cast<VertexShaderCg*>(m_cVertexShaderHandler.GetResource());
			if (pVertexShader) {
				// Is this a GLSL vertex shader?
				if (pVertexShader->GetCgProfile() == CG_PROFILE_GLSLV)
					bGLSL = true;

				// Get the fragment shader
				FragmentShaderCg *pFragmentShader = static_cast<FragmentShaderCg*>(m_cFragmentShaderHandler.GetResource());
				if (pFragmentShader) {
					// Is this a GLSL fragment shader?
					if (pFragmentShader->GetCgProfile() == CG_PROFILE_GLSLF && !bGLSL) {
						// Error!
						PL_LOG(Error, "Fragment shader is using GLSL, but vertex shader is not!")
					} else {
						// Geometry shader is optional
						GeometryShaderCg *pGeometryShader = static_cast<GeometryShaderCg*>(m_cGeometryShaderHandler.GetResource());

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

						// Geometry shader settings - optional
						GeometryShaderCg *pGeometryShader = static_cast<GeometryShaderCg*>(m_cGeometryShaderHandler.GetResource());
						if (pGeometryShader) {
							// Ok, the next thing is definitively no fun in Cg because it looks like there's no unified way to do it:
							// Set the input/output primitive type and the number of output vertices

							// We're going to need "glProgramParameteriEXT" from "GL_EXT_geometry_shader4"
							#ifdef WIN32
								static PFNGLPROGRAMPARAMETERIEXTPROC glProgramParameteriEXT = reinterpret_cast<PFNGLPROGRAMPARAMETERIEXTPROC>(wglGetProcAddress("glProgramParameteriEXT"));
							#endif
							#ifdef LINUX
								static PFNGLPROGRAMPARAMETERIEXTPROC glProgramParameteriEXT = reinterpret_cast<PFNGLPROGRAMPARAMETERIEXTPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glProgramParameteriEXT")));
							#endif
							if (glProgramParameteriEXT) {
								// Get the OpenGL program ID associated with the Cg program
								const GLuint nOpenGLProgram = cgGLGetProgramID(m_pCgCombinedProgram);

								// Set the input primitive type
								GLint nTemp;
								switch (pGeometryShader->GetInputPrimitiveType()) {
									case PLRenderer::GeometryShader::InputPoints:
										nTemp = GL_POINTS;
										break;

									case PLRenderer::GeometryShader::InputLines:
										nTemp = GL_LINES;
										break;

									case PLRenderer::GeometryShader::InputLinesAdjacency:
										nTemp = GL_LINES_ADJACENCY_EXT;
										break;

									case PLRenderer::GeometryShader::InputTriangles:
										nTemp = GL_TRIANGLES;
										break;

									case PLRenderer::GeometryShader::InputTrianglesAdjacency:
										nTemp = GL_TRIANGLES_ADJACENCY_EXT;
										break;

									default:
										nTemp = GL_TRIANGLES;
										break;
								}
								glProgramParameteriEXT(nOpenGLProgram, GL_GEOMETRY_INPUT_TYPE_EXT, nTemp);

								// Set the output primitive type
								switch (pGeometryShader->GetOutputPrimitiveType()) {
									case PLRenderer::GeometryShader::OutputPoints:
										nTemp = GL_POINTS;
										break;

									case PLRenderer::GeometryShader::OutputLines:
										nTemp = GL_LINE_STRIP;
										break;

									case PLRenderer::GeometryShader::OutputTriangles:
										nTemp = GL_TRIANGLE_STRIP;
										break;

									default:
										nTemp = GL_TRIANGLE_STRIP;
										break;
								}
								glProgramParameteriEXT(nOpenGLProgram, GL_GEOMETRY_OUTPUT_TYPE_EXT, nTemp);

								// Set the number of output vertices
								nTemp = pGeometryShader->GetNumOfOutputVertices();
								if (!nTemp)
									glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &nTemp);	// Maximum possible number of output vertices should be used
								glProgramParameteriEXT(nOpenGLProgram, GL_GEOMETRY_VERTICES_OUT_EXT, nTemp);
							}
						}
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
ProgramCg::ProgramCg(PLRenderer::Renderer &cRenderer) : Program(cRenderer),
	m_pCgCombinedProgram(nullptr),
	m_bLinked(false),
	m_bLinkedFailed(false),
	m_bAttributeInformationBuild(false),
	m_bUniformInformationBuild(false),
	m_bUniformBlockInformationBuild(false)
{
}

/**
*  @brief
*    Denotes that a program relink is required
*/
void ProgramCg::RelinkRequired()
{
	// Is the program currently linked?
	if (m_bLinked) {
		// The linked state is now dirty
		m_bLinked = m_bLinkedFailed = false;

		// Destroy the attribute information
		DestroyAttributeInformation();

		// Destroy the uniform information
		DestroyUniformInformation();

		// Destroy the uniform block information
		DestroyUniformBlockInformation();

		// Destroy the Cg combined program
		if (m_pCgCombinedProgram) {
			cgDestroyProgram(m_pCgCombinedProgram);
			m_pCgCombinedProgram = nullptr;
		}

		// The program is now dirty
		EventDirty(this);
	}
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

				// Vertex domain attributes ONLY!
				if (cgGetProgramDomain(pCgDomainProgram) == CG_VERTEX_DOMAIN) {
					// Iterate through all Cg parameters of the Cg vertex program
					CGparameter pCgParameter = cgGetFirstParameter(pCgDomainProgram, CG_PROGRAM);
					while (pCgParameter) {
						// Is this an attribute? (ONLY scalar or vector input data can come from the vertex buffer!)
						if (cgGetParameterVariability(pCgParameter) == CG_VARYING && cgGetParameterDirection(pCgParameter) == CG_IN) {
							// Is this uniform actually a structure?
							if (cgGetParameterClass(pCgParameter) == CG_PARAMETERCLASS_STRUCT) {
								// Add the structure elements as individual attributes as well so we can for example access an
								// structure element by using "MyStructure.MyPosition" as attribute name to access the "MyPosition" attribute element

								// Iterate through all Cg parameters of the Cg structure
								CGparameter pStructureCgParameter = cgGetFirstStructParameter(pCgParameter);
								while (pStructureCgParameter) {
									// Register the new program attribute
									ProgramAttributeCg *pProgramAttribute = new ProgramAttributeCg(pStructureCgParameter);
									m_lstAttributes.Add(pProgramAttribute);
									m_mapAttributes.Add(cgGetParameterName(pStructureCgParameter), pProgramAttribute);

									// Next Cg structure parameter, please
									pStructureCgParameter = cgGetNextParameter(pStructureCgParameter);
								}
							} else {
								// Register the new program attribute
								ProgramAttributeCg *pProgramAttribute = new ProgramAttributeCg(pCgParameter);
								m_lstAttributes.Add(pProgramAttribute);
								m_mapAttributes.Add(cgGetParameterName(pCgParameter), pProgramAttribute);
							}
						}

						// Next Cg parameter, please
						pCgParameter = cgGetNextParameter(pCgParameter);
					}
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
			delete static_cast<ProgramAttributeCg*>(m_lstAttributes[i]);

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
			for (int nDomain=0; nDomain<nNumOfProgramDomains; nDomain++) {
				// Get the Cg program of the current domain
				CGprogram pCgDomainProgram = cgGetProgramDomainProgram(pCgCombinedProgram, nDomain);

				// Iterate through all Cg parameters of the Cg vertex program
				CGparameter pCgParameter = cgGetFirstParameter(pCgDomainProgram, CG_PROGRAM);
				while (pCgParameter) {
					// Is this an uniform?
					if (cgGetParameterVariability(pCgParameter) == CG_UNIFORM) {
						// Get the name of the uniform
						const String sUniformName = cgGetParameterName(pCgParameter);

						// Is this uniform actually an array?
						if (cgGetParameterClass(pCgParameter) == CG_PARAMETERCLASS_ARRAY) {
							// Get the array dimension
							const int nArrayDimension = cgGetArraySize(pCgParameter, 0);	// We currently only support one dimension...

							// Add the array elements as individual uniforms as well so we can for example access an
							// array element by using "MyArray[1]" as uniform name to access the second array element
							for (int i=0; i<nArrayDimension; i++) {
								// Get the uniform name
								const String sElementUniformName = sUniformName + '[' + i + ']';

								// Get the Cg parameter representing this array element
								CGparameter pElementCgParameter = cgGetNamedParameter(pCgDomainProgram, sElementUniformName);
								if (pElementCgParameter) {
									// Register the new program uniform
									ProgramUniformCg *pProgramUniform = new ProgramUniformCg(pElementCgParameter);
									m_lstUniforms.Add(pProgramUniform);
									m_mapUniforms.Add(sElementUniformName, pProgramUniform);
								}
							}
						} else {
							// Register the new program uniform
							ProgramUniformCg *pProgramUniform = new ProgramUniformCg(pCgParameter);
							m_lstUniforms.Add(pProgramUniform);
							m_mapUniforms.Add(sUniformName, pProgramUniform);
						}
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
			delete static_cast<ProgramUniformCg*>(m_lstUniforms[i]);

		// Clear the uniform list and hash map
		m_lstUniforms.Clear();
		m_mapUniforms.Clear();
	}

	// Currently, there's no uniform information build
	m_bUniformInformationBuild = false;
}

/**
*  @brief
*    Builds the uniform block information
*/
void ProgramCg::BuildUniformBlockInformation()
{
	// Uniform block information already build?
	if (!m_bUniformBlockInformationBuild) {
		// Get the Cg combined program - this also ensures that the program is linked
		CGprogram pCgCombinedProgram = GetCgCombinedProgram();

		// Is the program linked?
		if (m_bLinked) {
			// Iterate through all Cg programs of the Cg combined program
			const int nNumOfProgramDomains = cgGetNumProgramDomains(pCgCombinedProgram);
			for (int nDomain=0; nDomain<nNumOfProgramDomains; nDomain++) {
				// Get the Cg program of the current domain
				CGprogram pCgDomainProgram = cgGetProgramDomainProgram(pCgCombinedProgram, nDomain);

				// Iterate through all Cg parameters of the Cg vertex program
				CGparameter pCgParameter = cgGetFirstParameter(pCgDomainProgram, CG_PROGRAM);
				while (pCgParameter) {
					// Is this an uniform block? ... please note that I wasn't able to figure how how one can enumerate all uniform blocks within Cg, I wasn't
					// able to find helpful information about this topic within the Cg documentation or the internet... so this is the result of try and error...
					if (cgGetParameterVariability(pCgParameter) == CG_UNIFORM && cgGetParameterType(pCgParameter) == CG_STRUCT && String(cgGetParameterSemantic(pCgParameter)).IsSubstring("BUFFER[")) {
						// Get the name of the uniform block
						const String sUniformBlockName = cgGetParameterName(pCgParameter);

						// Register the new program uniform block
						ProgramUniformBlockCg *pProgramUniformBlock = new ProgramUniformBlockCg(pCgParameter, ShaderLanguageCg::Cg);
						m_lstUniformBlocks.Add(pProgramUniformBlock);
						m_mapUniformBlocks.Add(sUniformBlockName, pProgramUniformBlock);
					}

					// Next Cg parameter, please
					pCgParameter = cgGetNextParameter(pCgParameter);
				}
			}

			// The uniform block information build is now build
			m_bUniformBlockInformationBuild = true;
		}
	}
}

/**
*  @brief
*    Destroys the uniform block information
*/
void ProgramCg::DestroyUniformBlockInformation()
{
	// Is there anything to destroy?
	const uint32 nNumOfUniformBlocks = m_lstUniformBlocks.GetNumOfElements();
	if (nNumOfUniformBlocks) {
		// Destroy the uniform block instances
		for (uint32 i=0; i<nNumOfUniformBlocks; i++)
			delete static_cast<ProgramUniformBlockCg*>(m_lstUniformBlocks[i]);

		// Clear the uniform block list and hash map
		m_lstUniformBlocks.Clear();
		m_mapUniformBlocks.Clear();
	}

	// Currently, there's no uniform block information build
	m_bUniformBlockInformationBuild = false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Program functions          ]
//[-------------------------------------------------------]
String ProgramCg::GetShaderLanguage() const
{
	return ShaderLanguageCg::Cg;
}

PLRenderer::VertexShader *ProgramCg::GetVertexShader() const
{
	return static_cast<PLRenderer::VertexShader*>(m_cVertexShaderHandler.GetResource());
}

bool ProgramCg::SetVertexShader(PLRenderer::VertexShader *pVertexShader)
{
	// Is the new vertex shader the same one as the current one?
	PLRenderer::VertexShader *pCurrentVertexShader = static_cast<PLRenderer::VertexShader*>(m_cVertexShaderHandler.GetResource());
	if (pCurrentVertexShader != pVertexShader) {
		// The shader language of the program and the vertex shader must match and the vertex shader must be valid!
		if (pVertexShader && (pVertexShader->GetShaderLanguage() != ShaderLanguageCg::Cg ||
			!static_cast<VertexShaderCg*>(pVertexShader)->GetCgVertexProgram()))
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
	return static_cast<PLRenderer::GeometryShader*>(m_cGeometryShaderHandler.GetResource());
}

bool ProgramCg::SetGeometryShader(PLRenderer::GeometryShader *pGeometryShader)
{
	// Is the new geometry shader the same one as the current one?
	PLRenderer::GeometryShader *pCurrentGeometryShader = static_cast<PLRenderer::GeometryShader*>(m_cGeometryShaderHandler.GetResource());
	if (pCurrentGeometryShader != pGeometryShader) {
		// The shader language of the program and the geometry shader must match and the geometry shader must be valid!
		if (pGeometryShader && (pGeometryShader->GetShaderLanguage() != ShaderLanguageCg::Cg ||
			!static_cast<GeometryShaderCg*>(pGeometryShader)->GetCgGeometryProgram()))
			return false; // Error, shader language mismatch!

		// Update the geometry shader resource handler
		m_cGeometryShaderHandler.SetResource(pGeometryShader);

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

PLRenderer::FragmentShader *ProgramCg::GetFragmentShader() const
{
	return static_cast<PLRenderer::FragmentShader*>(m_cFragmentShaderHandler.GetResource());
}

bool ProgramCg::SetFragmentShader(PLRenderer::FragmentShader *pFragmentShader)
{
	// Is the new fragment shader the same one as the current one?
	PLRenderer::FragmentShader *pCurrentFragmentShader = static_cast<PLRenderer::FragmentShader*>(m_cFragmentShaderHandler.GetResource());
	if (pCurrentFragmentShader != pFragmentShader) {
		// The shader language of the program and the fragment shader must match and the fragment shader must be valid!
		if (pFragmentShader && (pFragmentShader->GetShaderLanguage() != ShaderLanguageCg::Cg ||
			!static_cast<FragmentShaderCg*>(pFragmentShader)->GetCgFragmentProgram()))
			return false; // Error, shader language mismatch!

		// Update the fragment shader resource handler
		m_cFragmentShaderHandler.SetResource(pFragmentShader);

		// Denote that a program relink is required
		RelinkRequired();
	}

	// Done
	return true;
}

bool ProgramCg::IsValid()
{
	// Get the Cg combined program - this also ensures that the program is linked
	CGprogram pCgCombinedProgram = GetCgCombinedProgram();

	// Is there a Cg combined program? If so, is it compiled?
	return (pCgCombinedProgram && cgIsProgramCompiled(pCgCombinedProgram));
}

String ProgramCg::GetCompiledProgram()
{
	// Get the Cg combined program - this also ensures that the program is linked
	CGprogram pCgCombinedProgram = GetCgCombinedProgram();

	// Is there a Cg combined program? If so, is it compiled? (... when not using "cgIsProgramCompiled()", "cgGetProgramString()" may just crash in case the program is not compiled...)
	if (pCgCombinedProgram && cgIsProgramCompiled(pCgCombinedProgram)) {
		// Ask Cg for the string for the compiled program
		return cgGetProgramString(pCgCombinedProgram, CG_COMPILED_PROGRAM);
	} else {
		// Error!
		return "";
	}
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

const Array<PLRenderer::ProgramUniformBlock*> &ProgramCg::GetUniformBlocks()
{
	// Build the uniform block information, if required
	if (!m_bUniformBlockInformationBuild)
		BuildUniformBlockInformation();

	// Return the list of all uniform blocks
	return m_lstUniformBlocks;
}

PLRenderer::ProgramUniformBlock *ProgramCg::GetUniformBlock(const String &sName)
{
	// Build the uniform block information, if required
	if (!m_bUniformBlockInformationBuild)
		BuildUniformBlockInformation();

	// Return the requested uniform block
	return m_mapUniformBlocks.Get(sName);
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
		for (int i=0; i<nNumOfProgramDomains; i++) {
			// Enable the profile
			cgGLEnableProfile(cgGetProgramDomainProfile(pCgCombinedProgram, i));
		}

		// Iterate through all attributes - use GetAttributes() to ensure the attributes list is valid
		const Array<PLRenderer::ProgramAttribute*> &lstAttributes = GetAttributes();
		for (uint32 i=0; i<lstAttributes.GetNumOfElements(); i++) {
			// Enable vertex attribute array
			cgGLEnableClientState(static_cast<ProgramAttributeCg*>(lstAttributes[i])->m_pCgParameter);
		}

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
		// Iterate through all attributes - use GetAttributes() to ensure the attributes list is valid
		const Array<PLRenderer::ProgramAttribute*> &lstAttributes = GetAttributes();
		for (uint32 i=0; i<lstAttributes.GetNumOfElements(); i++) {
			// Disable vertex attribute array
			cgGLDisableClientState(static_cast<ProgramAttributeCg*>(lstAttributes[i])->m_pCgParameter);
		}

		// Iterate through all Cg programs of the Cg combined program and disable all required profiles
		const int nNumOfProgramDomains = cgGetNumProgramDomains(m_pCgCombinedProgram);
		for (int i=0; i<nNumOfProgramDomains; i++) {
			// Disable the profile
			cgGLDisableProfile(cgGetProgramDomainProfile(m_pCgCombinedProgram, i));
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void ProgramCg::BackupDeviceData(uint8 **ppBackup)
{
	// Destroy the Cg combined program
	if (m_pCgCombinedProgram) {
		cgDestroyProgram(m_pCgCombinedProgram);
		m_pCgCombinedProgram = nullptr;
	}
}

void ProgramCg::RestoreDeviceData(uint8 **ppBackup)
{
	// Call the relink method, this automatically destroys the used resources and the user will be informed through an dirty-event
	RelinkRequired();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
