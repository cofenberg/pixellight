/*********************************************************\
 *  File: ShaderLanguage.h                               *
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


#ifndef __PLRENDERER_SHADERLANGUAGE_H__
#define __PLRENDERER_SHADERLANGUAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLRenderer/Renderer/GeometryShader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Program;
class VertexShader;
class UniformBuffer;
class FragmentShader;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract shader language class
*/
class ShaderLanguage : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, ShaderLanguage, "PLRenderer", PLCore::Object, "Abstract shader language class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates a vertex shader and sets the shader source code
		*
		*  @param[in] sSourceCode
		*    Shader source code, usually blank ASCII code
		*  @param[in] sProfile
		*    Shader profile to use, if empty string, a default profile will be used which usually
		*    tries to use the best available profile that runs on most hardware
		*  @param[in] sEntry
		*    Entry point, if empty string, "main" is used as default
		*
		*  @return
		*    The created vertex shader, a null pointer on error
		*
		*  @see
		*    - Virtual "ShaderLanguage::CreateVertexShader()"-method
		*    - "Shader::SetSourceCode()"
		*/
		PLRENDERER_API VertexShader *CreateVertexShader(const PLCore::String &sSourceCode, const PLCore::String &sProfile = "", const PLCore::String &sEntry = "");

		/**
		*  @brief
		*    Creates a geometry shader and sets the shader source code
		*
		*  @param[in] sSourceCode
		*    Geometry shader source code, usually blank ASCII code
		*  @param[in] nInputPrimitiveType
		*    Input primitive type, for "Shader::SetSourceCode()" "InputTriangles" is used as default
		*  @param[in] nOutputPrimitiveType
		*    Output primitive type, for "Shader::SetSourceCode()" "OutputTriangles" is used as default
		*  @param[in] nNumOfOutputVertices
		*    Number of output vertices, 0 if the maximum possible number of output vertices should be used, for "Shader::SetSourceCode()" "0" is used as default
		*  @param[in] sProfile
		*    Geometry shader profile to use, if empty string, a default profile will be used which usually
		*    tries to use the best available profile that runs on most hardware
		*  @param[in] sEntry
		*    Entry point, if empty string, "main" is used as default
		*
		*  @return
		*    The created geometry shader, a null pointer on error
		*
		*  @see
		*    - Virtual "ShaderLanguage::CreateGeometryShader()"-method
		*    - "GeometryShader::SetSourceCode()"
		*/
		PLRENDERER_API GeometryShader *CreateGeometryShader(const PLCore::String &sSourceCode, GeometryShader::EInputPrimitiveType nInputPrimitiveType, GeometryShader::EOutputPrimitiveType nOutputPrimitiveType, PLCore::uint32 nNumOfOutputVertices, const PLCore::String &sProfile = "", const PLCore::String &sEntry = "");

		/**
		*  @brief
		*    Creates a fragment shader and sets the shader source code
		*
		*  @param[in] sSourceCode
		*    Shader source code, usually blank ASCII code
		*  @param[in] sProfile
		*    Shader profile to use, if empty string, a default profile will be used which usually
		*    tries to use the best available profile that runs on most hardware
		*  @param[in] sEntry
		*    Entry point, if empty string, "main" is used as default
		*
		*  @return
		*    The created fragment shader, a null pointer on error
		*
		*  @see
		*    - Virtual "ShaderLanguage::CreateFragmentShader()"-method
		*    - "Shader::SetSourceCode()"
		*/
		PLRENDERER_API FragmentShader *CreateFragmentShader(const PLCore::String &sSourceCode, const PLCore::String &sProfile = "", const PLCore::String &sEntry = "");

		/**
		*  @brief
		*    Creates a program and assigns a vertex and fragment shader to it
		*
		*  @param[in] pVertexShader
		*    Vertex shader the program is using, can be a null pointer, vertex shader and program language must match!
		*  @param[in] pFragmentShader
		*    Fragment shader the program is using, can be a null pointer, fragment shader and program language must match!
		*
		*  @return
		*    The created program, a null pointer on error
		*
		*  @see
		*    - Virtual "ShaderLanguage::CreateProgram()"-method
		*    - "Program::SetVertexShader()"
		*    - "Program::SetFragmentShader()"
		*/
		PLRENDERER_API Program *CreateProgram(VertexShader *pVertexShader, FragmentShader *pFragmentShader);

		/**
		*  @brief
		*    Creates a program and assigns a vertex, geometry and fragment shader to it
		*
		*  @param[in] pVertexShader
		*    Vertex shader the program is using, can be a null pointer, vertex shader and program language must match!
		*  @param[in] pGeometryShader
		*    Geometry shader the program is using, can be a null pointer, geometry shader and program language must match!
		*  @param[in] pFragmentShader
		*    Fragment shader the program is using, can be a null pointer, fragment shader and program language must match!
		*
		*  @return
		*    The created program, a null pointer on error
		*
		*  @see
		*    - Virtual "ShaderLanguage::CreateProgram()"-method
		*    - "Program::SetVertexShader()"
		*    - "Program::SetGeometryShader()"
		*    - "Program::SetFragmentShader()"
		*/
		PLRENDERER_API Program *CreateProgram(VertexShader *pVertexShader, GeometryShader *pGeometryShader, FragmentShader *pFragmentShader);


	//[-------------------------------------------------------]
	//[ Public virtual ShaderLanguage functions               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the shader language
		*
		*  @return
		*    The name of the shader language (for example "GLSL" or "Cg")
		*/
		virtual PLCore::String GetShaderLanguage() const = 0;

		/**
		*  @brief
		*    Creates a vertex shader
		*
		*  @return
		*    The created vertex shader, a null pointer on error
		*/
		virtual VertexShader *CreateVertexShader() = 0;

		/**
		*  @brief
		*    Creates a geometry shader
		*
		*  @return
		*    The created geometry shader, a null pointer on error
		*/
		virtual GeometryShader *CreateGeometryShader() = 0;

		/**
		*  @brief
		*    Creates a fragment shader
		*
		*  @return
		*    The created fragment shader, a null pointer on error
		*/
		virtual FragmentShader *CreateFragmentShader() = 0;

		/**
		*  @brief
		*    Creates a program
		*
		*  @return
		*    The created program, a null pointer on error
		*/
		virtual Program *CreateProgram() = 0;

		/**
		*  @brief
		*    Creates an uniform buffer
		*
		*  @return
		*    The created uniform buffer, a null pointer on error
		*/
		virtual UniformBuffer *CreateUniformBuffer() = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API ShaderLanguage();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~ShaderLanguage();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ShaderLanguage(const ShaderLanguage &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		ShaderLanguage &operator =(const ShaderLanguage &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADERLANGUAGE_H__
