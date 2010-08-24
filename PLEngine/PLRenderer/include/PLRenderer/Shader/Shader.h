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
#include <PLCore/Tools/Resource.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ShaderManager;
class ShaderProgram;
class ResourceHandler;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Shader resource class
*/
class Shader : public PLCore::Resource<Shader> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ShaderManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Shader();

		/**
		*  @brief
		*    Returns the shader manager this shader is in
		*
		*  @return
		*     The shader manager this shader is in
		*/
		PLRENDERER_API ShaderManager &GetShaderManager() const;

		/**
		*  @brief
		*    Binds the shader
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool Bind() const;

		/**
		*  @brief
		*    Unbinds the shader
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool Unbind() const;

		/**
		*  @brief
		*    Returns the shader program
		*
		*  @return
		*    The shader program, there you can setup the shader program parameters etc. can be NULL
		*/
		PLRENDERER_API PLRenderer::ShaderProgram *GetShaderProgram() const;

		/**
		*  @brief
		*    Sets the shader program
		*
		*  @param[in] pShaderProgram
		*    Shader program to set, can be NULL
		*/
		PLRENDERER_API void SetShaderProgram(PLRenderer::ShaderProgram *pShaderProgram = NULL);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cManager
		*    Shader manager using this resource
		*  @param[in] sName
		*    Resource name to set
		*/
		Shader(ShaderManager &cManager, const PLGeneral::String &sName);

		/**
		*  @brief
		*    Destroys the used shader program
		*/
		void DestroyShaderProgram();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::ResourceHandler *m_pShaderProgramHandler;	/**< The shader program handler (NEVER NULL!) */


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool Unload();
		PLRENDERER_API virtual PLGeneral::String GetLoadableTypeName() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADER_H__
