/*********************************************************\
 *  File: Program.h                                      *
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


#ifndef __PLRENDERER_PROGRAM_H__
#define __PLRENDERER_PROGRAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLCore/Base/Event/Event.h>
#include "PLRenderer/Renderer/Resource.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	template <class ValueType> class Array;
}
namespace PLRenderer {
	class VertexShader;
	class ProgramUniform;
	class GeometryShader;
	class FragmentShader;
	class ProgramAttribute;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer program resource
*
*  @note
*    - While each program must have a vertex shader and a fragment shader, a geometry shader is optional
*    - The program is using lazy evaluation, so the program is only compiled & linked when really required
*/
class Program : public Resource {


	//[-------------------------------------------------------]
	//[ Events                                                ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<Program*>	EventDirty;	/**< The program became dirty, previous pointers to attributes or uniforms may no longer be valid, pointer to this program as parameter */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Program();


	//[-------------------------------------------------------]
	//[ Public virtual Program functions                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the shader language the program is using
		*
		*  @return
		*    The name of the shader language the program is using (for example "GLSL" or "Cg")
		*/
		virtual PLGeneral::String GetShaderLanguage() const = 0;

		/**
		*  @brief
		*    Returns the vertex shader the program is using
		*
		*  @return
		*    Vertex shader the program is using, can be a null pointer
		*/
		virtual PLRenderer::VertexShader *GetVertexShader() const = 0;

		/**
		*  @brief
		*    Sets the vertex shader the program is using
		*
		*  @param[in] pVertexShader
		*    Vertex shader the program is using, can be a null pointer, vertex shader and program language must match!
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe shader language mismatch?)
		*/
		virtual bool SetVertexShader(PLRenderer::VertexShader *pVertexShader) = 0;

		/**
		*  @brief
		*    Returns the geometry shader the program is using
		*
		*  @return
		*    Geometry shader the program is using, can be a null pointer
		*/
		virtual PLRenderer::GeometryShader *GetGeometryShader() const = 0;

		/**
		*  @brief
		*    Sets the geometry shader the program is using
		*
		*  @param[in] pGeometryShader
		*    Geometry shader the program is using, can be a null pointer, geometry shader and program language must match!
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe shader language mismatch?)
		*/
		virtual bool SetGeometryShader(PLRenderer::GeometryShader *pGeometryShader) = 0;

		/**
		*  @brief
		*    Returns the fragment shader the program is using
		*
		*  @return
		*    Fragment shader the program is using, can be a null pointer
		*/
		virtual PLRenderer::FragmentShader *GetFragmentShader() const = 0;

		/**
		*  @brief
		*    Sets the fragment shader the program is using
		*
		*  @param[in] pFragmentShader
		*    Fragment shader the program is using, can be a null pointer, fragment shader and program language must match!
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe shader language mismatch?)
		*/
		virtual bool SetFragmentShader(PLRenderer::FragmentShader *pFragmentShader) = 0;

		/**
		*  @brief
		*    Returns whether or not the program is valid (successfully compiled, linked and ready to be used)
		*
		*  @return
		*    'true' if the program is valid, else 'false'
		*/
		virtual bool IsValid() = 0;

		/**
		*  @brief
		*    Returns the compiled program
		*
		*  @return
		*    The compiled program
		*
		*  @note
		*    - The compiled program depends on the used shader language, it's also possible
		*      that an implementation is not able to return a compiled program
		*/
		virtual PLGeneral::String GetCompiledProgram() = 0;

		/**
		*  @brief
		*    Get attributes
		*
		*  @return
		*    List of attributes
		*/
		virtual const PLGeneral::Array<ProgramAttribute*> &GetAttributes() = 0;

		/**
		*  @brief
		*    Get attribute
		*
		*  @param[in] sName
		*    Attribute name
		*
		*  @return
		*    Attribute (can be a null pointer, if no attribute with that name could be found)
		*/
		virtual ProgramAttribute *GetAttribute(const PLGeneral::String &sName) = 0;

		/**
		*  @brief
		*    Get uniforms
		*
		*  @return
		*    List of uniforms
		*/
		virtual const PLGeneral::Array<ProgramUniform*> &GetUniforms() = 0;

		/**
		*  @brief
		*    Get uniform
		*
		*  @param[in] sName
		*    Uniform name
		*
		*  @return
		*    Uniform (can be a null pointer, if no uniform with that name could be found)
		*/
		virtual ProgramUniform *GetUniform(const PLGeneral::String &sName) = 0;


	//[-------------------------------------------------------]
	//[ Protected virtual Program functions                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Makes this program to the renderers currently used program
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool MakeCurrent() = 0;

		/**
		*  @brief
		*    This program will no longer be the renderers currently used program
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool UnmakeCurrent() = 0;


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
		*/
		PLRENDERER_API Program(Renderer &cRenderer);


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
		Program(const Program &cSource);

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
		Program &operator =(const Program &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_PROGRAM_H__
