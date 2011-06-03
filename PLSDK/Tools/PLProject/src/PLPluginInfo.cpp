/*********************************************************\
 *  File: PLPluginInfo.cpp                               *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPluginInfo.h"
#include "PLPLuginClassInfo.h"
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/FileSearch.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/String/RegEx.h>
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/String/Tokenizer.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PLPluginInfo::PLPluginInfo()
{

}

/**
*  @brief
*    Destructor
*/
PLPluginInfo::~PLPluginInfo()
{
	// Cleanup all PLPLuginClassInfo instances
	for (int i = 0; i < m_lstClasses.GetNumOfElements(); ++i) {
		PLPLuginClassInfo *pInfo = m_lstClasses[i];
		delete pInfo;
	}
	m_lstClasses.Clear();
}

/**
*  @brief
*    Sets the name of the library.
*/
void PLPluginInfo::SetLibraryName(const PLGeneral::String &sLibraryName)
{
	m_cPluginPlatformInfo.SetLibraryName(sLibraryName);
}

/**
*  @brief
*    Sets a library suffix. This String is appended after die library name
*/
void PLPluginInfo::SetLibrarySuffix(const PLGeneral::String &sLibrarySuffix)
{
	m_cPluginPlatformInfo.SetSuffixName(sLibrarySuffix);
}

/**
*  @brief
*    Sets the version of the plugin file
*/
void PLPluginInfo::SetPluginFileVersion(const PLGeneral::String &sPluginVersion)
{
	m_sPluginFileVersion = sPluginVersion;
}

/**
*  @brief
*    Sets the pixellight version string
*/
void PLPluginInfo::SetPLVersion(const PLGeneral::String &sPLVersion)
{
	m_sPLVersion = sPLVersion;
}

/**
*  @brief
*    Set active flag. This flag indicates if the plugin is active or not.
*/ 
void PLPluginInfo::SetActive(bool bIsActive)
{
	m_bIsActive = bIsActive;
}

/**
*  @brief
*    Set delayed flag. This flag indicates if delayed loading should be used for this plugin.
*/
void PLPluginInfo::SetDelayed(bool bIsDelayed)
{
	m_bDelayed = bIsDelayed;
}

/**
*  @brief
*    Saves the parsed information to the given file
*/
void PLPluginInfo::Save(const PLGeneral::String &sFilename)
{
	XmlDocument cDocument;
	AppendInformation(cDocument);
	cDocument.Save(sFilename);
}

/**
*  @brief
*    Saves the parsed information to the given file
*/
void PLPluginInfo::Save(File &file)
{
	XmlDocument cDocument;
	AppendInformation(cDocument);
	cDocument.Save(file);
}

/**
*  @brief
*    Parses the found header files in the given include path for pl_class..pl_class_end blocks
*/
void PLPluginInfo::ParseIncludeFiles(const PLGeneral::String &sIncludePath)
{
	FileObject cIncFile(sIncludePath);

	// Check if path exists and if it points to a directory
	if (!(cIncFile.Exists() && cIncFile.IsDirectory())) {
		return;
	}

	// Get all header files form the include directory
	Array<String> lstFiles;
	Find(lstFiles, sIncludePath, "*.h", true);

	// Parse each header file
	for (int i = 0; i < lstFiles.GetNumOfElements(); ++i) {
		ParseFile(lstFiles[i]);
	}
}

/**
*  @brief
*    Parses the given main module source file for pl_module_plugin..pl_module_end blocks
*/
void PLPluginInfo::ParseMainModuleFile(const PLGeneral::String &sMainModuleFilename)
{
	String content = GetContentFormFile(sMainModuleFilename);
	
	if (!content.GetLength()) {
		return;
	}
	
	RegEx cPlPLuginModuleBlock("^\\s*(pl_module_plugin.*pl_module_end)", RegEx::Multiline | RegEx::DotAll);
	
	if (cPlPLuginModuleBlock.Match(content)) {
		content = cPlPLuginModuleBlock.GetResult(0);

		ParsePluginModuleBlock(content);
	}
}

//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    copy constructor
*/
PLPluginInfo::PLPluginInfo(const PLPluginInfo& other)
{

}

/**
*  @brief
*    assignment operator
*/
PLPluginInfo& PLPluginInfo::operator=(const PLPluginInfo & other)
{
	return *this;
}

/**
*  @brief
*    Parses a single file for an pl_class..pl_class_end block
*/
void PLPluginInfo::ParseFile(const PLGeneral::String &sFilename)
{
	String content = GetContentFormFile(sFilename);
	
	if (!content.GetLength()) {
		return;
	}

	RegEx cplclass_plclassendblock("^\\s*(pl_class\\s*.*\\s*pl_class_end)", RegEx::Multiline | RegEx::DotAll);

	if (cplclass_plclassendblock.Match(content)) {
		content = cplclass_plclassendblock.GetResult(0);

		PLPLuginClassInfo *pInfo = new PLPLuginClassInfo;
		pInfo->ParsePlClassBlock(content);
		m_lstClasses.Add(pInfo);
	}
}

/**
*  @brief
*    Find files in a directory tree
*/
void PLPluginInfo::Find(PLGeneral::Array<PLGeneral::String> &lstNames, const PLGeneral::String &sPath, const PLGeneral::String &sPattern, bool bRecursive)
{
	// Open directory
	Directory cDir(sPath);

	// Find files
	FileSearch cSearch(cDir, sPattern);
	while (cSearch.HasNextFile()) {
		String sFilename =  cSearch.GetNextFile();
		String sFile = sPath + '/' + sFilename;
		lstNames.Add(sFile);
	}

	// Recurse into subdirectories
	if (bRecursive) {
		FileSearch cSearch2(cDir);
		while (cSearch2.HasNextFile()) {
			String sFilename =  cSearch2.GetNextFile();
			String sFile = sPath + '/' + sFilename;
			if (FileObject(sFile).IsDirectory() && bRecursive && sFilename != "." && sFilename != "..") {
				Find(lstNames, sFile, sPattern, bRecursive);
			}
		}
	}
}

/**
*  @brief
*    Adds an XmlTextElement child to an XmlElement.
*/
void PLPluginInfo::AddTextXmlElement(PLGeneral::XmlElement* pParent, const PLGeneral::String &sName, const PLGeneral::String &sValue)
{
	if (!pParent)
		return;

	XmlElement *pElement = new XmlElement(sName);
	XmlText *ptextValue = new XmlText(sValue);
	pElement->LinkEndChild(*ptextValue);
	pParent->LinkEndChild(*pElement);
}

/**
*  @brief
*    Parses an pl_module_plugin..pl_module_end block
*/
void PLPluginInfo::ParsePluginModuleBlock(const PLGeneral::String& sPluginModuleBlock)
{
	// Setup regular expressions
	RegEx cRegExModulePlugin("^\\s*pl_module_plugin\\(\\s*\\\"(?<name>\\w*)\\\"\\s*\\)\\s*$");
	RegEx cRegExVendor("^\\s*pl_module_vendor\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExLicense("^\\s*pl_module_license\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDescription("^\\s*pl_module_description\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExVersion("^\\s*pl_module_version\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExActive("^\\s*pl_module_active\\s*\\((?<num>\\d)\\)\\s*$");
	RegEx cRegExDelayed("^\\s*pl_module_delayed\\s*\\((?<num>\\d)\\)\\s*$");
	
	Tokenizer cTokenizer;

	cTokenizer.SetDelimiters("\r\n");
	cTokenizer.SetSingleChars("");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCommentStartTag("");
	cTokenizer.SetCommentEndTag("");
	cTokenizer.SetSingleLineComment("");
	cTokenizer.Start(sPluginModuleBlock);

	String sLine = cTokenizer.GetNextToken();
	
	while (sLine.GetLength() != 0) {
		// check for pl_module_plugin
		if (cRegExModulePlugin.Match(sLine)) {
			m_sPluginName = cRegExModulePlugin.GetNameResult("name");
		// Check for pl_module_vendor
		} else if (cRegExVendor.Match(sLine)) {
			m_sVendor = cRegExVendor.GetNameResult("text");

		// Check for pl_module_license
		} else if (cRegExLicense.Match(sLine)) {
			m_sLicense = cRegExLicense.GetNameResult("text");

		// Check for pl_module_description
		} else if (cRegExDescription.Match(sLine)) {
			m_sDescription = cRegExDescription.GetNameResult("text");

		// Check for pl_module_version
		} else if (cRegExVersion.Match(sLine)) {
			m_sModuleVersion = cRegExVersion.GetNameResult("text");

		// let PluginPlatformInfo parse the line
		} else {
			m_cPluginPlatformInfo.ParseLine(sLine);
		}
		sLine = cTokenizer.GetNextToken();
	}
}

/**
* @brief
*   Returns the complete content of a file as text
* */
PLGeneral::String PLPluginInfo::GetContentFormFile(const PLGeneral::String &sFilename)
{
	File cFile(sFilename);

	if (!cFile.Open(File::FileRead | File::FileText)) {
		return "";
	}

	String content = cFile.GetContentAsString();

	cFile.Close();
	
	return content;
}

/**
*  @brief
*    Appends the parsed information about a plugin to the given xml document
*/
void PLPluginInfo::AppendInformation(PLGeneral::XmlDocument &cDocument)
{
	// Add declaration
	XmlDeclaration *cDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*cDeclaration);
	XmlElement *cRootElement = new XmlElement("Plugin");
	cRootElement->SetAttribute("Version", m_sPluginFileVersion);
	cRootElement->SetAttribute("PixelLightVersion", m_sPLVersion);

	AddTextXmlElement(cRootElement, "Active", m_bIsActive ? "1" : "0");
	AddTextXmlElement(cRootElement, "Delayed", m_bDelayed ? "1" : "0");
	AddTextXmlElement(cRootElement, "Name", m_sPluginName);
	if (m_sModuleVersion.GetLength())
		AddTextXmlElement(cRootElement, "Version", m_sModuleVersion);
	if (m_sVendor.GetLength())
		AddTextXmlElement(cRootElement, "Vendor", m_sVendor);
	if (m_sLicense.GetLength())
		AddTextXmlElement(cRootElement, "License", m_sLicense);
	if (m_sDescription.GetLength())
		AddTextXmlElement(cRootElement, "Description", m_sDescription);

	cDocument.LinkEndChild(*cRootElement);
	
	m_cPluginPlatformInfo.Save(*cRootElement);

	if (m_lstClasses.IsEmpty())
		return;

	XmlElement *pClassesElement = new XmlElement("Classes");
	cRootElement->LinkEndChild(*pClassesElement);

	ConstIterator<PLPLuginClassInfo*> iter = m_lstClasses.GetConstIterator();
	while (iter.HasNext()) {
		iter.Next()->Save(*pClassesElement);
	}
}
