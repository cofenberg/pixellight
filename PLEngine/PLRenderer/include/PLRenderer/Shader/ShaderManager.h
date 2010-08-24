/*********************************************************\
 *  File: ShaderManager.h                                *
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


#ifndef __PLRENDERER_SHADERMANAGER_H__
#define __PLRENDERER_SHADERMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/ResourceManager.h>
#include "PLRenderer/Shader/ShaderHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Shader;
class RendererContext;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a manager for the renderers shader resource
*
*  @note
*    - Unloads unused resources automatically by default
*    - By default, this resource manager has NO default resource because a 'default shader' makes not really sense
*/
class ShaderManager : public PLCore::ResourceManager<Shader> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class RendererContext;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the owner renderer context of this manager
		*
		*  @return
		*    Reference to the owner renderer context of this manager
		*/
		PLRENDERER_API RendererContext &GetRendererContext() const;

		/**
		*  @brief
		*    Load a shader
		*
		*  @param[in] sName
		*    Shader name within the shader manager
		*  @param[in] sFilename
		*    Shader filename
		*  @param[in] sProfile
		*    Profile requirement (e.g. "arbvp1")
		*  @param[in] sDefines
		*    Additional defines for the shader
		*  @param[in] sEntry
		*    The entry point to the program in the shader source. If empty, 'main' is used by default.
		*
		*  @return
		*    Pointer to the loaded shader if all went fine, else NULL (e.g. not supported
		*    profile or shader loading error)
		*
		*  @note
		*    - If the filename ends with a '+' it's a fragment program, else a vertex program
		*/
		PLRENDERER_API Shader *Load(const PLGeneral::String &sName, const PLGeneral::String &sFilename, const PLGeneral::String &sProfile = "",
									const PLGeneral::String &sDefines = "", const PLGeneral::String &sEntry = "main");

		/**
		*  @brief
		*    Load a shader
		*
		*  @param[in] sName
		*    Shader name within the shader manager
		*  @param[in] cFile
		*    Shader file
		*  @param[in] bFragmentShader
		*    Is this a fragment shader? If not, it's a vertex shader.
		*  @param[in] sProfile
		*    Profile requirement (e.g. "arbvp1")
		*  @param[in] sDefines
		*    Additional defines for the shader
		*  @param[in] sEntry
		*    The entry point to the program in the shader source. If empty, 'main' is used by default.
		*
		*  @return
		*    Pointer to the loaded shader if all went fine, else NULL (e.g. not supported
		*    profile or shader loading error)
		*/
		PLRENDERER_API Shader *Load(const PLGeneral::String &sName, PLGeneral::File &cFile, bool bFragmentShader, const PLGeneral::String &sProfile = "",
									const PLGeneral::String &sDefines = "", const PLGeneral::String &sEntry = "main");

		/**
		*  @brief
		*    Reloads all shaders
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool ReloadShaders();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRendererContext
		*    Owner renderer context
		*/
		ShaderManager(RendererContext &cRendererContext);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ShaderManager();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		RendererContext *m_pRendererContext;	/**< Owner renderer context of this manager, always valid! */


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual Shader *CreateResource(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADERMANAGER_H__
