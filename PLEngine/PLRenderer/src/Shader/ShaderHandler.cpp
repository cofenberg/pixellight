/*********************************************************\
 *  File: ShaderHandler.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/ShaderProgram.h"
#include "PLRenderer/Shader/Shader.h"
#include "PLRenderer/Shader/ShaderHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShaderHandler::ShaderHandler()
{
}

/**
*  @brief
*    Destructor
*/
ShaderHandler::~ShaderHandler()
{
}

/**
*  @brief
*    Returns the profile requirement (e.g. "arbvp1")
*/
String ShaderHandler::GetProfile() const
{
	return (GetResource() && GetResource()->GetShaderProgram()) ? GetResource()->GetShaderProgram()->GetProfile() : "";
}

/**
*  @brief
*    Binds the shader handlers shader
*/
bool ShaderHandler::Bind() const
{
	return (GetResource() && GetResource()->Bind());
}

/**
*  @brief
*    Unbinds the shader handlers shader
*/
bool ShaderHandler::Unbind() const
{
	return (GetResource() && GetResource()->Unbind());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
