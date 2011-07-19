/*********************************************************\
 *  File: ParamsParser.h                                 *
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


#ifndef __PLCORE_TOOLS_PARAMSPARSER_H__
#define __PLCORE_TOOLS_PARAMSPARSER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/RegEx.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class for parsing parameters
*
*  @remarks
*    This class can parse parameter lists given as strings (e.g. "param1=\"hello\" param2=10")
*/
class ParamsParser {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API ParamsParser();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API ~ParamsParser();

		/**
		*  @brief
		*    Parse parameter string
		*
		*  @param[in] sParameters
		*    String containing parameters (e.g. "Param0=\"Hello\" Param1=10)
		*
		*  @return
		*    'true' if the string could be parsed, else 'false'
		*
		*  @remarks
		*    This will first check if the string is a valid parameter string
		*    and then parse the first parameter and value. If the string is not
		*    valid or empty, the function will return 'false'.
		*/
		PLCORE_API bool ParseString(const String &sParameters);

		/**
		*  @brief
		*    Parse next parameter
		*
		*  @return
		*    'true' if the next name/value pair could be parsed, else 'false'
		*/
		PLCORE_API bool Next();

		/**
		*  @brief
		*    Check if the current (last parsed) parameter is valid
		*
		*  @return
		*    'true' if there is a current parameter, else 'false'
		*/
		PLCORE_API bool HasParam() const;

		/**
		*  @brief
		*    Get name of currently parsed parameter
		*
		*  @return
		*    Parameter name
		*/
		PLCORE_API String GetName() const;

		/**
		*  @brief
		*    Get value of currently parsed parameter
		*
		*  @return
		*    Parameter name
		*/
		PLCORE_API String GetValue() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String	m_sParameters;	/**< Parsed parameter string */
		RegEx	m_cRegEx;		/**< Regular expression for parsing a parameter string */
		long	m_nParsePos;	/**< Current parsing position (-1 for inactive) */
		String	m_sName;		/**< Name of next parameter */
		String	m_sValue;		/**< Value of next parameter */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_TOOLS_PARAMSPARSER_H__
