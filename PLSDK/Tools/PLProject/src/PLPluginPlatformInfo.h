/*********************************************************\
 *  File: PLPluginPlatformInfo.h                         *
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


#ifndef __PLPLUGINPLATFORMINFO_H__
#define __PLPLUGINPLATFORMINFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/Container/HashMap.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class to parse platform specific bits from a pl_module_plugin pl_module_end block
*/
class PLPluginPlatformInfo {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPluginPlatformInfo();

		/**
		*  @brief
		*    Destructor
		*/
		~PLPluginPlatformInfo();

		/**
		*  @brief
		*    Sets the name of the library
		*
		*  @param[in] sLibraryName
		*    Name of the library
		*/
		void SetLibraryName(const PLGeneral::String &sLibraryName);

		/**
		*  @brief
		*    Sets a library suffix, this string is appended to the library name
		*
		*  @param[in] sSuffix
		*    Library suffix
		*/
		void SetSuffixName(const PLGeneral::String &sSuffix);

		/**
		*  @brief
		*    Parse a line for platform specific bits
		*
		*  @param[in] sLine
		*    Line to parse
		*/
		void ParseLine(const PLGeneral::String &sLine);

		/**
		*  @brief
		*    Appends the parsed information to the given XML element
		*
		*  @param[out] cParent
		*    XML element to append to
		*/
		void Save(PLGeneral::XmlElement &cParent) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    Source to copy from
		*/
		PLPluginPlatformInfo(const PLPluginPlatformInfo &cOther);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cOther
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLPluginPlatformInfo &operator =(const PLPluginPlatformInfo &cOther);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String										 m_sLibraryName;			/**< Name of the compiled library */
		PLGeneral::String										 m_sSuffix;					/**< Suffix which gets appended to name of the compiled library */
		PLGeneral::Array<PLGeneral::String>						 m_lstPlatformNames;		/**< List of supported platforms (e.g. Win32, Linux) */
		PLGeneral::Array<PLGeneral::String>						 m_lstBuildTypes;			/**< List of supported build types (release, debug) */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapLibraryDependencies;	/**< Library dependency list for a specific platform and build type */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapLibraryPrefix;		/**< Library prefix list for a specific platform and build type */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapLibraryPostfix;		/**< Library postfix list for a specific platform and build type */


};


#endif // __PLPLUGINPLATFORMINFO_H__
