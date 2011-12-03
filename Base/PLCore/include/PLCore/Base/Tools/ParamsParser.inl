/*********************************************************\
 *  File: ParamsParser.inl                               *
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
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline ParamsParser::ParamsParser() :
	m_cRegEx("\\s*((\\w*\\s*=\\s*\"[^\"]*\")|(\\w*\\s*=\\s*'[^']*')|(\\w*\\s*=\\s*\\w*))"),
	m_nParsePos(-1)
{
}

/**
*  @brief
*    Destructor
*/
inline ParamsParser::~ParamsParser()
{
}

/**
*  @brief
*    Check if the current (last parsed) parameter is valid
*/
inline bool ParamsParser::HasParam() const
{
	return (m_sName.GetLength() != 0);
}

/**
*  @brief
*    Get name of currently parsed parameter
*/
inline String ParamsParser::GetName() const
{
	// Return parameter name
	return m_sName;
}

/**
*  @brief
*    Get value of currently parsed parameter
*/
inline String ParamsParser::GetValue() const
{
	// Return parameter value
	return m_sValue;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
