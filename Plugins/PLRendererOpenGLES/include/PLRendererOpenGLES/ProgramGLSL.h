/*********************************************************\
 *  File: ProgramGLSL.h                                  *
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


#ifndef __PLRENDEREROPENGLES_PROGRAMGLSL_H__
#define __PLRENDEREROPENGLES_PROGRAMGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <GLES2/gl2.h>
#include <PLCore/Container/HashMap.h>
#include <PLRenderer/Renderer/ResourceHandler.h>
#include <PLRenderer/Renderer/Program.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES GLSL renderer program resource
*/
class ProgramGLSL : public PLRenderer::Program {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;
	friend class ShaderLanguageGLSL;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramGLSL();

		/**
		*  @brief
		*    Returns the OpenGL ES program
		*
		*  @param[in] bAutomaticLink
		*    If 'true', the program is automatically linked if it's not yet linked
		*
		*  @return
		*    The OpenGL ES program, do not destroy it!
		*/
		GLuint GetOpenGLESProgram(bool bAutomaticLink = true);

		/**
		*  @brief
		*    Returns whether or not the program is currently linked
		*
		*  @return
		*    'true' if the program is currently linked, else 'false'
		*/
		bool IsLinked() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		ProgramGLSL(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Denotes that a program relink is required
		*/
		void RelinkRequired();

		/**
		*  @brief
		*    Builds the attribute information
		*/
		void BuildAttributeInformation();

		/**
		*  @brief
		*    Destroys the attribute information
		*/
		void DestroyAttributeInformation();

		/**
		*  @brief
		*    Builds the uniform information
		*/
		void BuildUniformInformation();

		/**
		*  @brief
		*    Destroys the uniform information
		*/
		void DestroyUniformInformation();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Program
		GLuint															m_nOpenGLESProgram;				/**< OpenGL ES program, always valid! */
		bool															m_bLinked;						/**< Is the OpenGL ES program currently linked? */
		bool															m_bLinkedFailed;				/**< OpenGL ES program link failed? */
		// Shaders
		PLRenderer::ResourceHandler										m_cVertexShaderHandler;			/**< Vertex shader resource handler */
		PLRenderer::ResourceHandler										m_cFragmentShaderHandler;		/**< Fragment shader resource handler */
		// Attributes
		bool															m_bAttributeInformationBuild;	/**< Attribute information already build? */
		PLCore::Array<PLRenderer::ProgramAttribute*>					m_lstAttributes;				/**< List of attributes */
		PLCore::HashMap<PLCore::String, PLRenderer::ProgramAttribute*>	m_mapAttributes;				/**< Hash map of names -> attributes */
		// Uniforms
		bool															m_bUniformInformationBuild;		/**< Uniform information already build? */
		PLCore::Array<PLRenderer::ProgramUniform*>						m_lstUniforms;					/**< List of uniforms */
		PLCore::HashMap<PLCore::String, PLRenderer::ProgramUniform*>	m_mapUniforms;					/**< Hash map of names -> uniforms */
		PLCore::Array<PLRenderer::ProgramUniformBlock*>					m_lstUniformBlocks;				/**< List of uniform blocks - There's no uniform block support in OpenGL ES 2.0, this is just a dummy so the interface can return "something" */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Program functions          ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::String GetShaderLanguage() const;
		virtual PLRenderer::VertexShader *GetVertexShader() const;
		virtual bool SetVertexShader(PLRenderer::VertexShader *pVertexShader);
		virtual PLRenderer::GeometryShader *GetGeometryShader() const;
		virtual bool SetGeometryShader(PLRenderer::GeometryShader *pGeometryShader);
		virtual PLRenderer::FragmentShader *GetFragmentShader() const;
		virtual bool SetFragmentShader(PLRenderer::FragmentShader *pFragmentShader);
		virtual bool IsValid();
		virtual PLCore::String GetCompiledProgram();
		virtual const PLCore::Array<PLRenderer::ProgramAttribute*> &GetAttributes();
		virtual PLRenderer::ProgramAttribute *GetAttribute(const PLCore::String &sName);
		virtual const PLCore::Array<PLRenderer::ProgramUniform*> &GetUniforms();
		virtual PLRenderer::ProgramUniform *GetUniform(const PLCore::String &sName);
		virtual const PLCore::Array<PLRenderer::ProgramUniformBlock*> &GetUniformBlocks();
		virtual PLRenderer::ProgramUniformBlock *GetUniformBlock(const PLCore::String &sName);


	//[-------------------------------------------------------]
	//[ Protected virtual PLRenderer::Program functions       ]
	//[-------------------------------------------------------]
	protected:
		virtual bool MakeCurrent();
		virtual bool UnmakeCurrent();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES


#endif // __PLRENDEREROPENGLES_PROGRAMGLSL_H__
