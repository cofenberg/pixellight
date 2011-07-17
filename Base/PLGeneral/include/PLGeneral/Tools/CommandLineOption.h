/*********************************************************\
 *  File: CommandLineOption.h                            *
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


#ifndef __PLGENERAL_COMMANDLINEOPTION_H__
#define __PLGENERAL_COMMANDLINEOPTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Command line option
*/
class CommandLineOption {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Command line option type
		*/
		enum EType {
			OptionFlag,			/**< A flag, e.g. 'command -v' or 'command --verbose' */
			OptionParam,		/**< A parameter, e.g. 'command -f name' or 'command --filename name' */
			OptionArgument		/**< An argument, e.g. 'command name' */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API CommandLineOption();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~CommandLineOption();

		/**
		*  @brief
		*    Get option type
		*
		*  @return
		*    Type of option
		*/
		PLGENERAL_API EType GetType() const;

		/**
		*  @brief
		*    Set option type
		*
		*  @param[in] nType
		*    Type of option
		*/
		PLGENERAL_API void SetType(EType nType);

		/**
		*  @brief
		*    Check if this option is required
		*
		*  @return
		*    'true' if the option is required, else 'false'
		*/
		PLGENERAL_API bool IsRequired() const;

		/**
		*  @brief
		*    Set if this option is required
		*
		*  @param[in] bRequired
		*    'true' if the option is required, else 'false'
		*/
		PLGENERAL_API void SetRequired(bool bRequired);

		/**
		*  @brief
		*    Get name
		*
		*  @return
		*    Option name (e.g. "Name")
		*/
		PLGENERAL_API String GetName() const;

		/**
		*  @brief
		*    Set name
		*
		*  @param[in] sName
		*    Option name (e.g. "Name")
		*/
		PLGENERAL_API void SetName(const String &sName);

		/**
		*  @brief
		*    Get short name
		*
		*  @return
		*    Short option name (e.g. "-a")
		*/
		PLGENERAL_API String GetShortName() const;

		/**
		*  @brief
		*    Set short name
		*
		*  @param[in] sName
		*    Short option name (e.g. "-a")
		*/
		PLGENERAL_API void SetShortName(const String &sName);

		/**
		*  @brief
		*    Get long name
		*
		*  @return
		*    Long option name (e.g. "--optiona")
		*/
		PLGENERAL_API String GetLongName() const;

		/**
		*  @brief
		*    Set long name
		*
		*  @param[in] sName
		*    Long option name (e.g. "--optiona")
		*/
		PLGENERAL_API void SetLongName(const String &sName);

		/**
		*  @brief
		*    Get description
		*
		*  @return
		*    Description string
		*/
		PLGENERAL_API String GetDescription() const;

		/**
		*  @brief
		*    Set description
		*
		*  @param[in] sDescription
		*    Description string
		*/
		PLGENERAL_API void SetDescription(const String &sDescription);

		/**
		*  @brief
		*    Get default value
		*
		*  @return
		*    Default value
		*/
		PLGENERAL_API String GetDefault() const;

		/**
		*  @brief
		*    Set default value
		*
		*  @param[in] sDefault
		*    Default value
		*/
		PLGENERAL_API void SetDefault(const String &sDefault);

		/**
		*  @brief
		*    Check if option value is set (either by command line or by default value)
		*
		*  @return
		*    'true' if the value is set, else 'false'
		*/
		PLGENERAL_API bool IsSet() const;

		/**
		*  @brief
		*    Get option value
		*
		*  @return
		*    Value of option ("true"/"false" for boolean values)
		*/
		PLGENERAL_API String GetValue() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] sValue
		*    Option value
		*/
		PLGENERAL_API void SetValue(const String &sValue);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		EType	m_nType;		/**< Type of command line option */
		bool	m_bRequired;	/**< Is this option required? */
		String	m_sName;		/**< Name, can be "" except for OptionArgument */
		String	m_sShortName;	/**< Short name (e.g. "-a"), can be "" */
		String	m_sLongName;	/**< Long name (e.g. "--optiona"), can be "" */
		String	m_sDescription;	/**< Description */
		String	m_sDefault;		/**< Default value */
		String	m_sValue;		/**< Current value */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_COMMANDLINEOPTION_H__
