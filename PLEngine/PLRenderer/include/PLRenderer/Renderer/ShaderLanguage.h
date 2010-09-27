/*********************************************************\
 *  File: ShaderLanguage.h                               *
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


#ifndef __PLRENDERER_SHADERLANGUAGE_H__
#define __PLRENDERER_SHADERLANGUAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Program;
class VertexShader;
class GeometryShader;
class FragmentShader;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract shader language
*/
class ShaderLanguage {


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
		virtual PLGeneral::String GetShaderLanguage() const = 0;

		/**
		*  @brief
		*    Creates a vertex shader
		*
		*  @return
		*    The created vertex shader, NULL on error
		*/
		virtual VertexShader *CreateVertexShader() = 0;

		/**
		*  @brief
		*    Creates a geometry shader
		*
		*  @return
		*    The created geometry shader, NULL on error
		*/
		virtual GeometryShader *CreateGeometryShader() = 0;

		/**
		*  @brief
		*    Creates a fragment shader
		*
		*  @return
		*    The created fragment shader, NULL on error
		*/
		virtual FragmentShader *CreateFragmentShader() = 0;

		/**
		*  @brief
		*    Creates a program
		*
		*  @return
		*    The created program, NULL on error
		*/
		virtual Program *CreateProgram() = 0;


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
