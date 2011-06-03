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

#ifndef PLPLUGININFO_H
#define PLPLUGININFO_H
#pragma once

//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include "PLPLuginPlatformInfo.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLPLuginClassInfo;

namespace PLGeneral {
	class XmlElement;
	class XmlDocument;
	class File;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    class to parse source and header files to generate information which gets saved in .plugins files
*
*  @verbatim
*    Usage example:
*    String sLibraryName = "MyExamplePlugin"; // Name of the compiled library
*    String sMainModulePath = "<projectPath>/source/MyExamplePlugin.cpp"; // Path to the source file which holds the pl_plugin_module definition
*    String sIncludePath = "<projectPath>/include/"; // Path where the include files of the projekt are located
*
*    PLPluginInfo pluginInfo;
*    pluginInfo.SetPluginFileVersion("1"); // Set version of the plugin file
*    pluginInfo.SetDelayed(true); // Set delayed value.
*    pluginInfo.SetActive(true); // Set active value.
*    pluginInfo.SetPLVersion("PixelLight 0.9.7-R1"); // Set Version String of Pixellight
*    pluginInfo.SetLibraryName(sLibraryName); // Set the name of the library to which the sources gets compiled
*    pluginInfo.ParseMainModuleFile(sMainModulePath); // Let the class parse the main module source file for an pl_plugin_module pl_module_end block
*    pluginInfo.ParseIncludeFiles(sIncludePath); // Let the class parse all include files at the given path for pl_class pl_class_end blocks
*
*    pluginInfo.Save(File::StandardOutput); // print the result to the standard output
* 
*    Example output:
* <?xml version="1.0" ?>
* <Plugin Version="1" PixelLightVersion="PixelLight 0.9.7-R1">
*    <Active>1</Active>
*    <Delayed>1</Delayed>
*    <Name>MyExample</Name>
*    <Vendor>Copyright (C) 2002-2011 by The PixelLight Team</Vendor>
*    <License>GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version</License>
*    <Description>Example Plugin Module Description</Description>
*    <Platform Name="Win32">
*        <Library Type="Release">MyExamplePlugin.dll</Library>
*        <Library Type="Debug">MyExamplePluginD.dll</Library>
*    </Platform>
*    <Platform Name="Win64">
*        <Library Type="Release">MyExamplePlugin64.dll</Library>
*        <Library Type="Debug">MyExamplePluginD64.dll</Library>
*    </Platform>
*    <Platform Name="Linux">
*        <Library Type="Release">libMyExamplePlugin.so</Library>
*        <Library Type="Debug">libMyExamplePluginLD.so</Library>
*    </Platform>
*    <Classes>
*        <Class Name="MyExamplePluginClass" Namespace="MyExamplePlugin Class Description" BaseClassName="PLRenderer::RendererBackend" Description="Example Plugin" HasConstructor="1" HasDefaultConstructor="0" />
* </Plugin>
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
		*    Sets the name of the library.
		*/
		void SetLibraryName(const PLGeneral::String &sLibraryName);

		/**
		*  @brief
		*    Sets a library suffix. This String is appended after die library name
		*/
		void SetLibrarySuffix(const PLGeneral::String &sLibrarySuffix);

		/**
		*  @brief
		*    Sets the version of the plugin file
		*/
		void SetPluginFileVersion(const PLGeneral::String &sPluginVersion);

		/**
		*  @brief
		*    Sets the pixellight version string
		*/
		void SetPLVersion(const PLGeneral::String &sPLVersion);

		/**
		*  @brief
		*    Set active flag. This flag indicates if the plugin is active or not.
		* 
		*  @note
		*    - This value can be overwritten by the pl_module_active definition in the main source file of the parsed project
		*/
		void SetActive(bool bIsActive);

		/**
		*  @brief
		*    Set delayed flag. This flag indicates if delayed loading should be used for this plugin.
		* 
		*  @note
		*    - This value can be overwritten by the pl_module_delayed definition in the main source file of the parsed project
		*/
		void SetDelayed(bool bIsDelayed);

		/**
		*  @brief
		*    Saves the parsed information to the given file
		*/
		void Save(const PLGeneral::String &sFilename);
		void Save(PLGeneral::File &file);

		/**
		*  @brief
		*    Parses the found header files in the given include path for pl_class..pl_class_end blocks
		*/
		void ParseIncludeFiles(const PLGeneral::String &sIncludePath);

		/**
		*  @brief
		*    Parses the given main module source file for pl_module_plugin..pl_module_end blocks
		*/
		void ParseMainModuleFile(const PLGeneral::String &sMainModuleFilename);

	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    copy constructor
		*/
		PLPluginInfo(const PLPluginInfo& other);

		/**
		*  @brief
		*    assignment operator
		*/
		PLPluginInfo& operator=(const PLPluginInfo& other);

		/**
		*  @brief
		*    Parses a single file for an pl_class..pl_class_end block
		*/
		void ParseFile(const PLGeneral::String &sFilename);

		/**
		*  @brief
		*    Find files in a directory tree
		*/
		void Find(PLGeneral::Array<PLGeneral::String> &lstNames, const PLGeneral::String &sPath, const PLGeneral::String &sPattern, bool bRecursive);

		/**
		*  @brief
		*    Adds an XmlTextElement child to an XmlElement.
		*/
		void AddTextXmlElement(PLGeneral::XmlElement* pParent, const PLGeneral::String &sName, const PLGeneral::String &sValue);

		/**
		*  @brief
		*    Parses an pl_module_plugin..pl_module_end block
		*/
		void ParsePluginModuleBlock(const PLGeneral::String &sPluginModuleBlock);

		/**
		 * @brief
		 *   Returns the complete content of a file as text
		 * */
		PLGeneral::String GetContentFormFile(const PLGeneral::String &sFilename);

		/**
		*  @brief
		*    Appends the parsed information about a plugin to the given xml document
		*/
		void AppendInformation(PLGeneral::XmlDocument &cDocument);

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sPluginFileVersion;		/** Plugin version string */
		PLGeneral::String m_sPLVersion;				/** Pixellight version string */
		bool m_bIsActive;							/** Flag if the plugin is active */
		bool m_bDelayed;							/** Flag if the delayed loading should be used */
		PLGeneral::String m_sDescription;			/** Plugin description */
		PLGeneral::String m_sVendor;				/** Plugin vendor information */
		PLGeneral::String m_sLicense;				/** Plugin license information */
		PLGeneral::String m_sPluginName;			/** Name of the plugin */
		PLGeneral::String m_sModuleVersion;			/** Version of the module */

		PLGeneral::Array<PLPLuginClassInfo*> m_lstClasses;	/** List of PLPLuginClassInfo instances */
		PLPLuginPlatformInfo m_cPluginPlatformInfo;			/** Parser for the platform specific bits in an pl_module_plugin pl_module_end block*/
};

#endif // PLPLUGININFO_H
