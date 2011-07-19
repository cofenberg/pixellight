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
class UniformBuffer;
class GeometryShader;
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
