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

#ifndef PLPLUGINPLATFORMINFO_H
#define PLPLUGINPLATFORMINFO_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/HashMap.h>
#include <PLGeneral/Container/Array.h>


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
*    class to parse platform specific bits from an pl_module_plugin pl_module_end block
*
*/
class PLPLuginPlatformInfo {

	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPLuginPlatformInfo();

		/**
		*  @brief
		*    Destructor
		*/
		~PLPLuginPlatformInfo();

		/**
		*  @brief
		*    Sets the name of the library.
		*/
		void SetLibraryName(const PLGeneral::String &sLibraryName);

		/**
		*  @brief
		*    Sets a library suffix. This String is appended after die library name
		*/
		void SetSuffixName(const PLGeneral::String &sSuffix);

		/**
		*  @brief
		*    Parse a line for platform specific bits
		*/
		void ParseLine(const PLGeneral::String &sLine);

		/**
		*  @brief
		*    Appends the parsed information to the given xml element
		*/
		void Save(PLGeneral::XmlElement& pParent);

	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    copy constructor
		*/
		PLPLuginPlatformInfo(const PLPLuginPlatformInfo& other);

		/**
		*  @brief
		*    assignment operator
		*/
		PLPLuginPlatformInfo& operator=(const PLPLuginPlatformInfo& other);

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sLibraryName;													/** name of the compiled library */
		PLGeneral::String m_sSuffix;														/** suffix which gets appended to name of the compiled library */
		PLGeneral::Array<PLGeneral::String> m_lstPlatformNames;								/** List of supported platforms (e.g. win32, linux) */
		PLGeneral::Array<PLGeneral::String> m_lstBuildTypes;								/** List of supported build types (release debug) */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapLibraryDependencies;	/** Library Dependency list for a specific platform and build type */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapLibraryPrefix;		/** Library prefix list for a specific platform and build type */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapLibraryPostfix;		/** Library postfix list for a specific platform and build type */
};

#endif // PLPLUGINPLATFORMINFO_H
