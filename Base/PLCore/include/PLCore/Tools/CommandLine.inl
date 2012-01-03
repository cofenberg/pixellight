/*********************************************************\
 *  File: CommandLine.inl                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
inline CommandLine::CommandLine() :
	m_bError(false)
{
}

/**
*  @brief
*    Destructor
*/
inline CommandLine::~CommandLine()
{
	// Clear options
	Clear();
}

/**
*  @brief
*    Get number of registered options
*/
inline uint32 CommandLine::GetNumOfOptions() const
{
	// Return number of options stored in our array
	return m_lstOptions.GetNumOfElements();
}

/**
*  @brief
*    Get option by index
*/
inline CommandLineOption *CommandLine::GetOption(uint32 nIndex) const
{
	// Return option
	return m_lstOptions[nIndex];
}

/**
*  @brief
*    Get option by name
*/
inline CommandLineOption *CommandLine::GetOption(const String &sName) const
{
	// Return option
	return m_mapOptions.Get(sName);
}

/**
*  @brief
*    Check if there were any errors parsing the command line arguments
*/
inline bool CommandLine::HasErrors() const
{
	// Return error flag
	return m_bError;
}

/**
*  @brief
*    Get number of additional arguments that have been defined
*/
inline uint32 CommandLine::GetNumOfAdditionalArguments() const
{
	// Return number of additional arguments
	return m_lstParameters.GetNumOfElements();
}

/**
*  @brief
*    Get additional argument
*/
inline String CommandLine::GetAdditionalArgument(uint32 nIndex) const
{
	// Return argument
	return m_lstParameters[nIndex];
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
