/*********************************************************\
 *  File: ProgramCg.h                                    *
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


#ifndef __PLRENDEREROPENGLCG_PROGRAMCG_H__
#define __PLRENDEREROPENGLCG_PROGRAMCG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cg.h>
#include <PLGeneral/Container/HashMap.h>
#include <PLRenderer/Renderer/ResourceHandler.h>
#include <PLRendererOpenGL/Program.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL Cg renderer program resource
*/
class ProgramCg : public PLRendererOpenGL::Program {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;
	friend class ShaderLanguageCg;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramCg();

		/**
		*  @brief
		*    Returns the Cg combined program
		*
		*  @param[in] bAutomaticLink
		*    If 'true', the program is automatically linked if it's not yet linked
		*
		*  @return
		*    The Cg combined program, do not destroy it!
		*/
		CGprogram GetCgCombinedProgram(bool bAutomaticLink = true);

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
		ProgramCg(PLRenderer::Renderer &cRenderer);

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
		CGprogram																m_pCgCombinedProgram;			/**< Cg combined program, can be NULL */
		bool																	m_bLinked;						/**< Is the Cg combined program currently linked? */
		bool																	m_bLinkedFailed;				/**< Cg combined program link failed? */
		// Shaders
		PLRenderer::ResourceHandler												m_cVertexShaderHandler;			/**< Vertex shader resource handler */
		PLRenderer::ResourceHandler												m_cGeometryShaderHandler;		/**< Geometry shader resource handler */
		PLRenderer::ResourceHandler												m_cFragmentShaderHandler;		/**< Fragment shader resource handler */
		// Attributes
		bool																	m_bAttributeInformationBuild;	/**< Attribute information already build? */
		PLGeneral::Array<PLRenderer::ProgramAttribute*>							m_lstAttributes;				/**< List of attributes */
		PLGeneral::HashMap<PLGeneral::String, PLRenderer::ProgramAttribute*>	m_mapAttributes;				/**< Hash map of names -> attributes */
		// Uniforms
		bool																	m_bUniformInformationBuild;		/**< Uniform information already build? */
		PLGeneral::Array<PLRenderer::ProgramUniform*>							m_lstUniforms;					/**< List of uniforms */
		PLGeneral::HashMap<PLGeneral::String, PLRenderer::ProgramUniform*>		m_mapUniforms;					/**< Hash map of names -> uniforms */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Program functions          ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetShaderLanguage() const;
		virtual PLRenderer::VertexShader *GetVertexShader() const;
		virtual bool SetVertexShader(PLRenderer::VertexShader *pVertexShader);
		virtual PLRenderer::GeometryShader *GetGeometryShader() const;
		virtual bool SetGeometryShader(PLRenderer::GeometryShader *pGeometryShader);
		virtual PLRenderer::FragmentShader *GetFragmentShader() const;
		virtual bool SetFragmentShader(PLRenderer::FragmentShader *pFragmentShader);
		virtual const PLGeneral::Array<PLRenderer::ProgramAttribute*> &GetAttributes();
		virtual PLRenderer::ProgramAttribute *GetAttribute(const PLGeneral::String &sName);
		virtual const PLGeneral::Array<PLRenderer::ProgramUniform*> &GetUniforms();
		virtual PLRenderer::ProgramUniform *GetUniform(const PLGeneral::String &sName);


	//[-------------------------------------------------------]
	//[ Protected virtual PLRenderer::Program functions       ]
	//[-------------------------------------------------------]
	protected:
		virtual bool MakeCurrent();
		virtual bool UnmakeCurrent();


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg


#endif // __PLRENDEREROPENGLCG_PROGRAMCG_H__
