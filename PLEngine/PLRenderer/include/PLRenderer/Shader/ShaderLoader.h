/*********************************************************\
 *  File: ShaderLoader.h                                 *
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


#ifndef __PLRENDERER_SHADERLOADER_H__
#define __PLRENDERER_SHADERLOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Loader.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract shader loader base class
*
*  @note
*    - Normally all load functions accept a PixelLight string 'Type'-parameter, (default setting: 'Vertex')
*      if this parameter is not empty, this is the shader type that can be 'Vertex' or 'Fragment'
*    - Normally all load functions accept a PixelLight string 'Profile'-parameter, (default setting: empty string
*      = the best available profile will be used) if this parameter is not empty, the shader is compiled using this profile
*    - Normally all load functions accept a PixelLight string 'Defines'-parameter, (default setting: empty string)
*      if this parameter is not empty, the defines are added to the shader before it is compiled
*    - Normally all load functions accept a PixelLight string 'Entry'-parameter, (default setting: 'main')
*      if this parameter is not empty, this is the entry point to the program in the shader source
*/
class ShaderLoader : public PLCore::Loader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, ShaderLoader, "PLRenderer", PLCore::Loader, "Abstract shader loader base class")
		pl_properties
			pl_property("Type", "Shader")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API ShaderLoader();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~ShaderLoader();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADERLOADER_H__
