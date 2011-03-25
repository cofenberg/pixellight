/*********************************************************\
 *  File: ShaderToolsCg.h                                *
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


#ifndef __PLRENDEREROPENGLCG_SHADERTOOLSCG_H__
#define __PLRENDEREROPENGLCG_SHADERTOOLSCG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cgGL.h>
#include <PLGeneral/String/String.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some useful OpenGL Cg shader tool methods
*/
class ShaderToolsCg {


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Adds a Cg context reference
		*
		*  @note
		*    - Should be done when creating for example a vertex shader
		*    - If this is the first reference, the internal Cg context is created automatically
		*/
		static void AddCgContextReference();

		/**
		*  @brief
		*    Releases a Cg context reference
		*
		*  @note
		*    - Should be done when destroying for example a vertex shader
		*    - If this is the last reference, the internal Cg context is destroyed automatically
		*/
		static void ReleaseCgContextReference();

		/**
		*  @brief
		*    Returns the Cg context
		*
		*  @return
		*    The Cg context, can be a null pointer
		*/
		static CGcontext GetCgContext();

		/**
		*  @brief
		*    Creates a Cg program
		*
		*  @param[in] pCgProfile
		*    Cg profile the created Cg program should use
		*  @param[in] sSourceCode
		*    Shader source code, usually blank ASCII code
		*  @param[in] sEntry
		*    Entry point, if empty string, "main" is used as default
		*  @param[in] sArguments
		*    Optional arguments
		*
		*  @return
		*    The creates Cg program, a null pointer on error
		*
		*  @note
		*    - There must be at least one reference to the Cg context
		*/
		static CGprogram CreateCgProgram(CGprofile pCgProfile, const PLGeneral::String &sSourceCode, const PLGeneral::String &sEntry, const PLGeneral::String &sArguments = "");


	//[-------------------------------------------------------]
	//[ Private static Cg callback functions                  ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal Cg error callback function
		*/
		static void CgErrorCallback();


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static CGcontext		 m_pCgContext;			/**< Cg shader program context, can be a null pointer */
		static PLGeneral::uint32 m_nCgContexCounter;	/**< Cg context counter */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg


#endif // __PLRENDEREROPENGLCG_SHADERTOOLSCG_H__
