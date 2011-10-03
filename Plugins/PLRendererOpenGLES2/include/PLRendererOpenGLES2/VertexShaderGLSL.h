/*********************************************************\
 *  File: VertexShaderGLSL.h                             *
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


#ifndef __PLRENDEREROPENGLES2_VERTEXSHADERGLSL_H__
#define __PLRENDEREROPENGLES2_VERTEXSHADERGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/VertexShader.h>
#include "PLRendererOpenGLES2/Context.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES renderer GLSL vertex shader resource
*/
class VertexShaderGLSL : public PLRenderer::VertexShader {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ShaderLanguageGLSL;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VertexShaderGLSL();

		/**
		*  @brief
		*    Returns the OpenGL ES vertex shader
		*
		*  @return
		*    The OpenGL ES vertex shader, do not destroy it!
		*/
		GLuint GetOpenGLESVertexShader() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nShaderType
		*    Shader type (GLSL or Cg vertex shader)
		*/
		VertexShaderGLSL(PLRenderer::Renderer &cRenderer, GLenum nShaderType = GL_VERTEX_SHADER);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		GLuint m_nOpenGLESVertexShader;	/**< OpenGL ES vertex shader, always valid! */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Shader functions           ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::String GetShaderLanguage() const override;
		virtual PLCore::String GetSourceCode() const override;
		virtual PLCore::String GetProfile() const override;
		virtual PLCore::String GetEntry() const override;
		virtual bool SetSourceCode(const PLCore::String &sSourceCode, const PLCore::String &sProfile = "", const PLCore::String &sEntry = "") override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_VERTEXSHADERGLSL_H__
