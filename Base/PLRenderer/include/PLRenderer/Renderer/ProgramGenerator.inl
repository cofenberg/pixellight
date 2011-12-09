/*********************************************************\
 *  File: ProgramGenerator.inl                           *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the used renderer
*/
inline Renderer &ProgramGenerator::GetRenderer() const
{
	return *m_pRenderer;
}

/**
*  @brief
*    Returns the name of the used shader language
*/
inline PLCore::String ProgramGenerator::GetShaderLanguage() const
{
	return m_sShaderLanguage;
}

/**
*  @brief
*    Returns the used vertex shader source code
*/
inline PLCore::String ProgramGenerator::GetVertexShaderSourceCode() const
{
	return m_sVertexShader;
}

/**
*  @brief
*    Returns the used fragment shader source code
*/
inline PLCore::String ProgramGenerator::GetFragmentShaderSourceCode() const
{
	return m_sFragmentShader;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
