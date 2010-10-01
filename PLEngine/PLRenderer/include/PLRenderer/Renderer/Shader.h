/*********************************************************\
 *  File: Shader.h                                       *
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


#ifndef __PLRENDERER_SHADER_H__
#define __PLRENDERER_SHADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLRenderer/Renderer/Resource.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer shader resource
*/
class Shader : public Resource {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Shader();


	//[-------------------------------------------------------]
	//[ Public virtual Shader functions                       ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the shader language the shader is using
		*
		*  @return
		*    The name of the shader language the shader is using (for example "GLSL" or "Cg")
		*/
		virtual PLGeneral::String GetShaderLanguage() const = 0;

		/**
		*  @brief
		*    Returns the shader source code
		*
		*  @return
		*    The shader source code
		*/
		virtual PLGeneral::String GetSourceCode() const = 0;

		/**
		*  @brief
		*    Returns the name of the shader profile the shader is using
		*
		*  @return
		*    The name of the shader profile the shader is using (for example "arbvp1")
		*/
		virtual PLGeneral::String GetProfile() const = 0;

		/**
		*  @brief
		*    Returns the name of the shader entry point the shader is using
		*
		*  @return
		*    The name of the shader entry point the shader is using (for example "main")
		*/
		virtual PLGeneral::String GetEntry() const = 0;

		/**
		*  @brief
		*    Sets the shader source code
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
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    'sProfile' is not supported by each shader-API and is in general shader-API dependent. GLSL doesn't have such
		*    profiles. Within Cg, a basic vertex profile may be "arbvp1" and a basic fragment profile "arbfp1". Cg also
		*    provides GLSL profiles: "glslv" for vertex shader, "glslg" for geometry shader and "glslf" for fragment shader.
		*    Please note that the profile is just a hint, if necessary, the implemenation is free to choose another profile.
		*    In general, be carefully when explicitly setting a profile - when using Cg, and one of the shaders, a GPU program
		*    is composed of, is a GLSL profile like "glslv", all other shaders must use GLSL profiles as well!
		*
		*   'sEntry' is not supported by each shader-API. GLSL doesn't have such an user defined entry point and the main
		*   function must always be "main". Cg supports entry points with names other than "main".
		*/
		virtual bool SetSourceCode(const PLGeneral::String &sSourceCode, const PLGeneral::String &sProfile = "", const PLGeneral::String &sEntry = "") = 0;


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
		*  @param[in] nType
		*    Resource type
		*/
		PLRENDERER_API Shader(Renderer &cRenderer, EType nType);


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
		Shader(const Shader &cSource);

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
		Shader &operator =(const Shader &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADER_H__
