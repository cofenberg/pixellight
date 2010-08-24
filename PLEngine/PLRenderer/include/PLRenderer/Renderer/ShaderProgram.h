/*********************************************************\
 *  File: ShaderProgram.h                                *
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


#ifndef __PLRENDERER_SHADERPROGRAM_H__
#define __PLRENDERER_SHADERPROGRAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/Resource.h"
#include "PLRenderer/Renderer/Parameters.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer shader program resource
*
*  @note
*    - Use GetType() to find out whether this is a vertex (VertexShader) or a fragment (FragmentShader) shader program
*/
class ShaderProgram : public Resource, public Parameters {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class RendererBackend;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~ShaderProgram();

		/**
		*  @brief
		*    Returns the additional defines for the shader program
		*
		*  @return
		*    The additional defines for the shader program
		*/
		PLRENDERER_API PLGeneral::String GetDefines() const;

		/**
		*  @brief
		*    Returns the entry point to the program in the shader program source
		*
		*  @return
		*    The entry point to the program in the shader program source
		*/
		PLRENDERER_API PLGeneral::String GetEntry() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the used profile (e.g. "arbvp1")
		*
		*  @return
		*    Used profile
		*/
		virtual PLGeneral::String GetProfile() const = 0;


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
		*  @param[in] sDefines
		*    Additional defines for the shader program
		*  @param[in] sEntry
		*    The entry point to the program in the shader program source. If empty, 'main' is used by default.
		*/
		PLRENDERER_API ShaderProgram(Renderer &cRenderer, EType nType, const PLGeneral::String &sDefines = "",
									 const PLGeneral::String &sEntry = "main");


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Makes this vertex/fragment shader program to the renderers current vertex/fragment shader program
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - You can also use SetXXXShaderProgram() from the renderer whereby
		*      XXX stands for the shader program type
		*/
		virtual bool MakeCurrent() = 0;


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
		ShaderProgram(const ShaderProgram &cSource);

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
		ShaderProgram &operator =(const ShaderProgram &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sDefines;	/**< Additional defines for the shader program */
		PLGeneral::String m_sEntry;		/**< The entry point to the program in the shader program source */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADERPROGRAM_H__
