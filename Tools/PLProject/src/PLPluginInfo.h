/*********************************************************\
 *  File: PLPluginInfo.h                                 *
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


#ifndef __PLPLUGININFO_H__
#define __PLPLUGININFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPluginPlatformInfo.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class File;
	class XmlElement;
	class XmlDocument;
}
class PLPluginClassInfo;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class to parse source and header files to generate information which gets saved in .plugins files
*
*  @verbatim
*    Usage example:
*    String sLibraryName    = "MyExamplePlugin";							// Name of the compiled library
*    String sMainModulePath = "<projectPath>/source/MyExamplePlugin.cpp";	// Path to the source file which holds the pl_plugin_module definition
*    String sIncludePath    = "<projectPath>/include/";						// Path where the include files of the project are located
*
*    PLPluginInfo cPluginInfo;
*    cPluginInfo.SetPluginFileVersion("1");				// Set version of the plugin file
*    cPluginInfo.SetDelayed(true);						// Set delayed value
*    cPluginInfo.SetActive(true);						// Set active value
*    cPluginInfo.SetPLVersion("PixelLight 0.9.8-R1");	// Set version string of PixelLight
*    cPluginInfo.SetLibraryName(sLibraryName);			// Set the name of the library to which the sources gets compiled
*    cPluginInfo.ParseMainModuleFile(sMainModulePath);	// Let the class parse the main module source file for an pl_plugin_module pl_module_end block
*    cPluginInfo.ParseIncludeFiles(sIncludePath);		// Let the class parse all include files at the given path for pl_class pl_class_end blocks
*
*    cPluginInfo.Save(File::StandardOutput); // Print the result to the standard output
*
*    Example output:
*    <?xml version="1.0" ?>
*    <Plugin Version="1" PixelLightVersion="PixelLight 0.9.8-R1">
*       <Active>1</Active>
*       <Delayed>1</Delayed>
*       <Name>MyExample</Name>
*       <Vendor>Copyright (C) 2002-2011 by The PixelLight Team</Vendor>
*       <License>GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version</License>
*       <Description>Example Plugin Module Description</Description>
*       <Platform Name="Win32">
*           <Library Type="Release">MyExamplePlugin.dll</Library>
*           <Library Type="Debug">MyExamplePluginD.dll</Library>
*       </Platform>
*       <Platform Name="Win64">
*           <Library Type="Release">MyExamplePlugin64.dll</Library>
*           <Library Type="Debug">MyExamplePluginD64.dll</Library>
*       </Platform>
*       <Platform Name="Linux">
*           <Library Type="Release">libMyExamplePlugin.so</Library>
*           <Library Type="Debug">libMyExamplePluginLD.so</Library>
*       </Platform>
*       <Classes>
*           <Class Name="MyExamplePluginClass" Namespace="MyExamplePlugin Class Description" BaseClassName="PLRenderer::RendererBackend" Description="Example Plugin" HasConstructor="1" HasDefaultConstructor="0" />
*    </Plugin>
*  @endverbatim
*/
class PLPluginInfo {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPluginInfo();

		/**
		*  @brief
		*    Destructor
		*/
		~PLPluginInfo();

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
		*  @param[in] sLibrarySuffix
		*    Library suffix
		*/
		void SetLibrarySuffix(const PLCore::String &sLibrarySuffix);

		/**
		*  @brief
		*    Sets the version of the plugin file
		*
		*  @param[in] sPluginVersion
		*    Version of the plugin file
		*/
		void SetPluginFileVersion(const PLCore::String &sPluginVersion);

		/**
		*  @brief
		*    Sets the PixelLight version string
		*
		*  @param[in] sPLVersion
		*    PixelLight version string
		*/
		void SetPLVersion(const PLCore::String &sPLVersion);

		/**
		*  @brief
		*    Set active flag, this flag indicates if the plugin is active or not
		*
		*  @note
		*    - This value can be overwritten by the pl_module_active definition in the main source file of the parsed project
		*/
		void SetActive(bool bIsActive);

		/**
		*  @brief
		*    Set delayed flag, this flag indicates if delayed loading should be used for this plugin
		*
		*  @note
		*    - This value can be overwritten by the pl_module_delayed definition in the main source file of the parsed project
		*/
		void SetDelayed(bool bIsDelayed);

		/**
		*  @brief
		*    Saves the parsed information to the given file
		*
		*  @param[in] sFilename
		*    Name of the file to write into
		*/
		void Save(const PLCore::String &sFilename) const;

		/**
		*  @brief
		*    Saves the parsed information to the given file
		*
		*  @param[out] cFile
		*    File to write in, must be opened and writable
		*/
		void Save(PLCore::File &cFile) const;

		/**
		*  @brief
		*    Parses the found header files in the given include path for pl_class..pl_class_end blocks
		*
		*  @parse[in] sIncludePath
		*    Include path to parse
		*/
		void ParseIncludeFiles(const PLCore::String &sIncludePath);

		/**
		*  @brief
		*    Parses the given main module source file for pl_module_plugin..pl_module_end blocks
		*
		*  @parse[in] sMainModuleFilename
		*    Filename of the main module to parse
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool ParseMainModuleFile(const PLCore::String &sMainModuleFilename);


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
		PLPluginInfo(const PLPluginInfo &Other);

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
		PLPluginInfo &operator =(const PLPluginInfo &cOther);

		/**
		*  @brief
		*    Parses a single file for an pl_class..pl_class_end block
		*
		*  @param[in] sFilename
		*    Name of the file to parse
		*/
		void ParseFile(const PLCore::String &sFilename);

		/**
		*  @brief
		*    Find files in a directory tree
		*
		*  @param[out] lstNames
		*    Receives the found filenames
		*  @param[in]  sPath
		*    Path were to search
		*  @param[in]  bRecursive
		*    'true' to search recursive
		*/
		void Find(PLCore::Array<PLCore::String> &lstNames, const PLCore::String &sPath, const PLCore::String &sPattern, bool bRecursive) const;

		/**
		*  @brief
		*    Adds an XmlTextElement child to an XmlElement
		*
		*  @param[out] cParent
		*    Parent to add to
		*  @param[in]  sName
		*    XML element name
		*  @param[in]  sValue
		*    XML element value
		*/
		void AddTextXmlElement(PLCore::XmlElement &cParent, const PLCore::String &sName, const PLCore::String &sValue) const;

		/**
		*  @brief
		*    Parses an pl_module_plugin..pl_module_end block
		*
		*  @param[in] sPluginModuleBlock
		*    Block to parse
		*/
		void ParsePluginModuleBlock(const PLCore::String &sPluginModuleBlock);

		/**
		*  @brief
		*    Returns the complete content of a file as text
		*
		*  @param[in] sFilename
		*    Filename of the file to get the content from
		*
		*  @return
		*    The file content
		*/
		PLCore::String GetContentFromFile(const PLCore::String &sFilename) const;

		/**
		*  @brief
		*    Appends the parsed information about a plugin to the given XML document
		*
		*  @param[out] cDocument
		*    XML document to append to
		*/
		void AppendInformation(PLCore::XmlDocument &cDocument) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String					  m_sPluginFileVersion;		/**< Plugin version string */
		PLCore::String					  m_sPLVersion;				/**< PixelLight version string */
		bool							  m_bIsActive;				/**< Flag if the plugin is active */
		bool							  m_bDelayed;				/**< Flag if the delayed loading should be used */
		PLCore::String					  m_sDescription;			/**< Plugin description */
		PLCore::String					  m_sVendor;				/**< Plugin vendor information */
		PLCore::String					  m_sLicense;				/**< Plugin license information */
		PLCore::String					  m_sPluginName;			/**< Name of the plugin */
		PLCore::String					  m_sModuleVersion;			/**< Version of the module */
		PLCore::Array<PLPluginClassInfo*> m_lstClasses;				/**< List of PLPLuginClassInfo instances */
		PLPluginPlatformInfo			  m_cPluginPlatformInfo;	/**< Parser for the platform specific bits in an pl_module_plugin pl_module_end block */


};


#endif // __PLPLUGININFO_H__
