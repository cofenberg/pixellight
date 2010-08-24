/*********************************************************\
 *  File: ShaderLoaderCg.h                               *
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


#ifndef __PLRENDERER_SHADERLOADER_PL_H__
#define __PLRENDERER_SHADERLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Shader/ShaderLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Shader loader implementation for the Cg shader file format
*/
class ShaderLoaderCg : public ShaderLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, ShaderLoaderCg, "PLRenderer", PLRenderer::ShaderLoader, "Shader loader implementation for the Cg shader file format")
		pl_properties
			pl_property("Formats",	"cg")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, Shader&, PLGeneral::File&, "Load method. Type is 'Vertex', entry point is 'main'.", "")
		pl_method_6(LoadParams, bool, Shader&, PLGeneral::File&, PLGeneral::String, PLGeneral::String, PLGeneral::String, PLGeneral::String, "Load method. Parameters: First parameter is type as 'String', second parameter is profile as string, third parameter are defines as string, fouth parameter is entry point as string.", "")
		pl_method_2(Save, bool, const Shader&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API bool Load(Shader &cShader, PLGeneral::File &cFile);
		PLRENDERER_API bool LoadParams(Shader &cShader, PLGeneral::File &cFile, PLGeneral::String sType, PLGeneral::String sProfile, PLGeneral::String sDefines, PLGeneral::String sEntry);
		PLRENDERER_API bool Save(const Shader &cShader, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API ShaderLoaderCg();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~ShaderLoaderCg();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADERLOADER_PL_H__
