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


#ifndef __PLRENDERERD3D9_SHADERPROGRAM_H__
#define __PLRENDERERD3D9_SHADERPROGRAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cgD3D9.h>
#include <_PLRendererBackend/ShaderProgramCgBackend.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Direct3D 9 shader program resource
*/
class ShaderProgram : public PLRenderer::ShaderProgramCgBackend {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ShaderProgram();


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
		*  @param[in] nType
		*    Resource type
		*  @param[in] pProgram
		*    Shader program this shader is using
		*  @param[in] sProfile
		*    Profile requirement (e.g. "arbvp1")
		*    If empty, the best available profile is used.
		*  @param[in] sDefines
		*    Additional defines for the shader program
		*  @param[in] sEntry
		*    The entry point to the program in the shader program source. If empty, 'main' is used by default.
		*  @param[in] ppszAttributes
		*    Some additional attributes for the shader program compiler, can be NULL
		*/
		ShaderProgram(PLRenderer::Renderer &cRenderer, EType nType, const void *pProgram,
					  const PLGeneral::String &sProfile = "", const PLGeneral::String &sDefines = "",
					  const PLGeneral::String &sEntry = "main", const char **ppszAttributes = NULL);


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::ShaderProgramCgBackend functions ]
	//[-------------------------------------------------------]
	private:
		virtual void Init(const void *pProgram, CGprofile pCgProfile);


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::ShaderProgram functions   ]
	//[-------------------------------------------------------]
	private:
		virtual bool MakeCurrent();


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Parameters functions       ]
	//[-------------------------------------------------------]
	public:
		virtual int SetParameterTextureBuffer(const PLGeneral::String &sName, PLRenderer::TextureBuffer *pTextureBuffer);
		virtual int SetParameterTexture(const PLGeneral::String &sName, const PLGeneral::String &sFilename);
		virtual int SetParameterTexture(const PLGeneral::String &sName, PLRenderer::Texture *pTexture);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_SHADERPROGRAM_H__
