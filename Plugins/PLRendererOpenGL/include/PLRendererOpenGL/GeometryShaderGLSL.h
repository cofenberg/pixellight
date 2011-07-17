/*********************************************************\
 *  File: GeometryShaderGLSL.h                           *
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


#ifndef __PLRENDEREROPENGL_GEOMETRYSHADERGLSL_H__
#define __PLRENDEREROPENGL_GEOMETRYSHADERGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/GeometryShader.h>
#include "PLRendererOpenGL/PLRendererOpenGL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL GLSL renderer geometry shader resource
*/
class GeometryShaderGLSL : public PLRenderer::GeometryShader {


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
		virtual ~GeometryShaderGLSL();

		/**
		*  @brief
		*    Returns the OpenGL geometry shader
		*
		*  @return
		*    The OpenGL geometry shader, do not destroy it!
		*/
		GLuint GetOpenGLGeometryShader() const;


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
		GeometryShaderGLSL(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		EInputPrimitiveType	 m_nInputPrimitiveType;		/**< Input primitive type */
		EOutputPrimitiveType m_nOutputPrimitiveType;	/**< Output primitive type */
		PLGeneral::uint32	 m_nNumOfOutputVertices;	/**< Num of output vertices */
		GLuint				 m_nOpenGLGeometryShader;	/**< OpenGL geometry shader, always valid! */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::GeometryShader functions   ]
	//[-------------------------------------------------------]
	public:
		virtual EInputPrimitiveType GetInputPrimitiveType() const;
		virtual EOutputPrimitiveType GetOutputPrimitiveType() const;
		virtual PLGeneral::uint32 GetNumOfOutputVertices() const;
		virtual bool SetSourceCode(const PLGeneral::String &sSourceCode, EInputPrimitiveType nInputPrimitiveType, EOutputPrimitiveType nOutputPrimitiveType, PLGeneral::uint32 nNumOfOutputVertices, const PLGeneral::String &sProfile = "", const PLGeneral::String &sEntry = "");


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Shader functions           ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetShaderLanguage() const;
		virtual PLGeneral::String GetSourceCode() const;
		virtual PLGeneral::String GetProfile() const;
		virtual PLGeneral::String GetEntry() const;
		virtual bool SetSourceCode(const PLGeneral::String &sSourceCode, const PLGeneral::String &sProfile = "", const PLGeneral::String &sEntry = "");


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
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_GEOMETRYSHADERGLSL_H__
