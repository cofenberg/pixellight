/*********************************************************\
 *  File: ShaderProgram.cpp                              *
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
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/ShaderProgram.h"


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
*    Destructor
*/
ShaderProgram::~ShaderProgram()
{
	// Check if this is the renderers current vertex/fragment shader program
	if (GetType() == TypeVertexShaderProgram) {
		if (GetRenderer().GetVertexShaderProgram() == this)
			GetRenderer().SetVertexShaderProgram();
	} else if (GetType() == TypeFragmentShaderProgram) {
		if (GetRenderer().GetFragmentShaderProgram() == this)
			GetRenderer().SetFragmentShaderProgram();
	}
}

/**
*  @brief
*    Returns the additional defines for the shader program
*/
PLGeneral::String ShaderProgram::GetDefines() const
{
	return m_sDefines;
}

/**
*  @brief
*    Returns the entry point to the program in the shader program source
*/
PLGeneral::String ShaderProgram::GetEntry() const
{
	return m_sEntry;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShaderProgram::ShaderProgram(Renderer &cRenderer, EType nType, const PLGeneral::String &sDefines, const PLGeneral::String &sEntry) : Resource(cRenderer, nType),
	m_sDefines(sDefines),
	m_sEntry(sEntry)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
ShaderProgram::ShaderProgram(const ShaderProgram &cSource) : Resource(cSource.GetRenderer(), cSource.GetType()),
	m_sDefines(cSource.GetDefines()),
	m_sEntry(cSource.GetEntry())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
ShaderProgram &ShaderProgram::operator =(const ShaderProgram &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
