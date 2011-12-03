/*********************************************************\
 *  File: CommandLine.h                                  *
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


#ifndef __PLCORE_COMMANDLINE_H__
#define __PLCORE_COMMANDLINE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"
#include "PLCore/Container/List.h"
#include "PLCore/Container/Array.h"
#include "PLCore/Container/HashMap.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class CommandLineOption;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Command line parser
*
*  @remarks
*    This class is used to define the command line arguments your application understands and parse a given
*    command line string passed to the application. Typical problems like quotes and filenames, or errors like
*    missing arguments or unknown options are automatically taken care of. This makes it quite easy to provide
*    nice command line arguments for your application without having to go through parsing hell yourself :-)
*/
class CommandLine {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Convert a command array to a string
		*
		*  @param[in] lstArguments
		*    List of arguments
		*
		*  @return
		*    Command string
		*/
		static PLCORE_API String ArgumentsToString(const Array<String> &lstArguments);

		/**
		*  @brief
		*    Convert a command string to an array
		*
		*  @param[in] sCmdLine
		*    Command string
		*
		*  @return
		*    Command array of arguments
		*/
		static PLCORE_API Array<String> StringToArguments(const String &sCmdLine);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		inline CommandLine();

		/**
		*  @brief
		*    Destructor
		*/
		inline ~CommandLine();

		/**
		*  @brief
		*    Get number of registered options
		*
		*  @return
		*    Number of options that have been registered
		*/
		inline uint32 GetNumOfOptions() const;

		/**
		*  @brief
		*    Get option by index
		*
		*  @param[in] nIndex
		*    Index of the option to retrieve
		*
		*  @return
		*    Pointer to option, or a null pointer
		*/
		inline CommandLineOption *GetOption(uint32 nIndex) const;

		/**
		*  @brief
		*    Get option by name
		*
		*  @param[in] sName
		*    Name of the option to retrieve (short or long name)
		*
		*  @return
		*    Pointer to option, or a null pointer
		*/
		inline CommandLineOption *GetOption(const String &sName) const;

		/**
		*  @brief
		*    Delete all options
		*/
		PLCORE_API void Clear();

		/**
		*  @brief
		*    Add parameter
		*
		*  @param[in] sName
		*    Parameter name (logical name, must *not* start with "-" or "--")
		*  @param[in] sShort
		*    Short name (must start with "-", e.g. "-a") or ""
		*  @param[in] sLong
		*    Long name (must start with "--", e.g. "-optiona") or ""
		*  @param[in] sDescription
		*    Description text for this option
		*  @param[in] sDefault
		*    Default value
		*  @param[in] bRequired
		*    Is the option required?
		*
		*  @return
		*    'true' if option could be added, 'false' on error
		*
		*  @remarks
		*    A parameter is an option that can receive a value.
		*    Example: command --name <name>
		*/
		PLCORE_API bool AddParameter(const String &sName, const String &sShort, const String &sLong, const String &sDescription, const String &sDefault, bool bRequired = false);

		/**
		*  @brief
		*    Add flag (on/off)
		*
		*  @param[in] sName
		*    Parameter name (logical name, must *not* start with "-" or "--")
		*  @param[in] sShort
		*    Short name (must start with "-", e.g. "-a") or ""
		*  @param[in] sLong
		*    Long name (must start with "--", e.g. "-optiona") or ""
		*  @param[in] sDescription
		*    Description text for this option
		*  @param[in] bRequired
		*    Is the option required?
		*
		*  @return
		*    'true' if option could be added, 'false' on error
		*
		*  @remarks
		*    A flag is an option that is either on or off (off as default).
		*    Example: command --option
		*/
		PLCORE_API bool AddFlag(const String &sName, const String &sShort, const String &sLong, const String &sDescription, bool bRequired = false);

		/**
		*  @brief
		*    Add argument
		*
		*  @param[in] sName
		*    Parameter name (logical name, must *not* start with "-" or "--")
		*  @param[in] sDescription
		*    Description text for this option
		*  @param[in] sDefault
		*    Default value
		*  @param[in] bRequired
		*    Is the option required?
		*
		*  @return
		*    'true' if option could be added, 'false' on error
		*
		*  @remarks
		*    An argument is an option that can receive a value, but is not preceded by the option name (like a parameter).
		*    Example: command <name>
		*/
		PLCORE_API bool AddArgument(const String &sName, const String &sDescription, const String &sDefault, bool bRequired = false);

		/**
		*  @brief
		*    Parse command line arguments
		*
		*  @param[in] lstArgs
		*    List of arguments
		*
		*  @return
		*    'true' if the command line could be parsed without error, else 'false'
		*/
		PLCORE_API bool ParseCommandLine(const Array<String> &lstArgs);

		/**
		*  @brief
		*    Check if there were any errors parsing the command line arguments
		*
		*  @return
		*    'true' if there were errors, else 'false'
		*/
		inline bool HasErrors() const;

		/**
		*  @brief
		*    Check if an option value is set ('true' for boolean options or any other than "" for string values)
		*
		*  @param[in] sName
		*    Name of option (short or long name)
		*
		*  @return
		*    'true' if the value is set, else 'false'
		*/
		PLCORE_API bool IsValueSet(const String &sName) const;

		/**
		*  @brief
		*    Get option value
		*
		*  @param[in] sName
		*    Name of option (short or long name)
		*
		*  @return
		*    Value of option ("true"/"false" for boolean values)
		*/
		PLCORE_API String GetValue(const String &sName) const;

		/**
		*  @brief
		*    Get number of additional arguments that have been defined
		*
		*  @return
		*    Number of additional arguments
		*
		*  @remarks
		*    Additional arguments are values that have been provided on the command line but
		*    do not belong to a specific option (for arbitrary number of arguments)
		*/
		inline uint32 GetNumOfAdditionalArguments() const;

		/**
		*  @brief
		*    Get additional argument
		*
		*  @param[in] nIndex
		*    Index of argument to get
		*
		*  @return
		*    Additional argument, or ""
		*/
		inline String GetAdditionalArgument(uint32 nIndex) const;

		/**
		*  @brief
		*    Display a help text with all available options on the console
		*
		*  @param[in] sProgramName
		*    Name of the program
		*/
		PLCORE_API void PrintHelp(const String &sProgramName) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Array<CommandLineOption*>			m_lstOptions;		/**< List of command line options */
		HashMap<String, CommandLineOption*> m_mapOptions;		/**< Map name -> option */
		List<String>						m_lstParameters;	/**< Additional parameters */
		bool								m_bError;			/**< Error indicator */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Tools/CommandLine.inl"


#endif // __PLCORE_COMMANDLINE_H__
