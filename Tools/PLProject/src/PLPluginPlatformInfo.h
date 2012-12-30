/*********************************************************\
 *  File: PLPluginPlatformInfo.h                         *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLPLUGINPLATFORMINFO_H__
#define __PLPLUGINPLATFORMINFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLCore/Container/Array.h>
#include <PLCore/Container/HashMap.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
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
		void SetLibraryName(const PLCore::String &sLibraryName);

		/**
		*  @brief
		*    Sets a library suffix, this string is appended to the library name
		*
		*  @param[in] sSuffix
		*    Library suffix
		*/
		void SetSuffixName(const PLCore::String &sSuffix);

		/**
		*  @brief
		*    Parse a line for platform specific bits
		*
		*  @param[in] sLine
		*    Line to parse
		*/
		void ParseLine(const PLCore::String &sLine);

		/**
		*  @brief
		*    Appends the parsed information to the given XML element
		*
		*  @param[out] cParent
		*    XML element to append to
		*/
		void Save(PLCore::XmlElement &cParent) const;


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
		PLCore::String									m_sLibraryName;				/**< Name of the compiled library */
		PLCore::String									m_sSuffix;					/**< Suffix which gets appended to name of the compiled library */
		PLCore::Array<PLCore::String>					m_lstPlatformNames;			/**< List of supported platforms (e.g. Windows, Linux) */
		PLCore::Array<PLCore::String>					m_lstBuildTypes;			/**< List of supported build types (release, debug) */
		PLCore::HashMap<PLCore::String, PLCore::String> m_mapLibraryDependencies;	/**< Library dependency list for a specific platform and build type */
		PLCore::HashMap<PLCore::String, PLCore::String> m_mapLibraryPostfix;		/**< Library postfix list for a specific platform and build type */


};


#endif // __PLPLUGINPLATFORMINFO_H__
