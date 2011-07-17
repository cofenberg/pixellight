/*********************************************************\
 *  File: PLPluginPlatformInfo.cpp                       *
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
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/String/RegEx.h>
#include "PLPluginPlatformInfo.h"


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
PLPluginPlatformInfo::PLPluginPlatformInfo()
{
	// Setup defaults
	m_lstPlatformNames.Add("Win32");
	m_lstPlatformNames.Add("Win64");
	m_lstPlatformNames.Add("Linux");
	
	m_lstBuildTypes.Add("Release");
	m_lstBuildTypes.Add("Debug");
	
	m_mapLibraryPostfix.Add("LinuxRelease", ".so");
	m_mapLibraryPostfix.Add("Win32Release", ".dll");
	m_mapLibraryPostfix.Add("Win64Release", "64.dll");
	
	m_mapLibraryPostfix.Add("LinuxDebug", "D.so");
	m_mapLibraryPostfix.Add("Win32Debug", "D.dll");
	m_mapLibraryPostfix.Add("Win64Debug", "D64.dll");
	
	m_mapLibraryPrefix.Add("Linux", "lib");
}

/**
*  @brief
*    Destructor
*/
PLPluginPlatformInfo::~PLPluginPlatformInfo()
{
}

/**
*  @brief
*    Sets the name of the library
*/
void PLPluginPlatformInfo::SetLibraryName(const String &sLibraryName)
{
	m_sLibraryName = sLibraryName;
}

/**
*  @brief
*    Sets a library suffix, this string is appended to the library name
*/
void PLPluginPlatformInfo::SetSuffixName(const String &sSuffix)
{
	m_sSuffix = sSuffix;
}

/**
*  @brief
*    Parse a line for platform specific bits
*/
void PLPluginPlatformInfo::ParseLine(const String &sLine)
{
	// Try get dependencies
	for (uint32 i=0; i<m_lstPlatformNames.GetNumOfElements(); i++) {
		String sPlatformName = m_lstPlatformNames[i];
		for (uint32 j=0; j<m_lstBuildTypes.GetNumOfElements(); j++) {
			String sBuildType = m_lstBuildTypes[j];
			RegEx cDependencies("^\\s*pl_module_dependencies_" + sPlatformName.ToLower() + '_' + sBuildType.ToLower() + "\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
			if (cDependencies.Match(sLine))
				m_mapLibraryDependencies.Add(m_lstPlatformNames[i] + m_lstBuildTypes[j], cDependencies.GetNameResult("text"));
		}
	}
}

/**
*  @brief
*    Appends the parsed information to the given XML element
*/
void PLPluginPlatformInfo::Save(XmlElement &pParent) const
{
	for (uint32 i=0; i<m_lstPlatformNames.GetNumOfElements(); i++) {
		String sPlatformName = m_lstPlatformNames[i];
		XmlElement *pPlatformElement = new XmlElement("Platform");
		pPlatformElement->SetAttribute("Name", sPlatformName);
		for (uint32 j=0; j<m_lstBuildTypes.GetNumOfElements(); j++) {
			String sBuildType = m_lstBuildTypes[j];
			XmlElement *pLibrary = new XmlElement("Library");
			pLibrary->SetAttribute("Type", sBuildType);
			const String &sDependecies = m_mapLibraryDependencies.Get(sPlatformName + sBuildType);
			if (sDependecies != m_mapLibraryDependencies.NullKey)
				pLibrary->SetAttribute("Dependency", sDependecies);

			const String &sLibPrefix = m_mapLibraryPrefix.Get(sPlatformName);

			String sLibraryName = sLibPrefix;
			sLibraryName += m_sLibraryName;
			sLibraryName += m_sSuffix;
			sLibraryName += m_mapLibraryPostfix.Get(sPlatformName + sBuildType);

			XmlText *pTextElememt = new XmlText(sLibraryName);
			pLibrary->LinkEndChild(*pTextElememt);
			pPlatformElement->LinkEndChild(*pLibrary);
		}
		pParent.LinkEndChild(*pPlatformElement);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
PLPluginPlatformInfo::PLPluginPlatformInfo(const PLPluginPlatformInfo &cOther)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
PLPluginPlatformInfo &PLPluginPlatformInfo::operator =(const PLPluginPlatformInfo &cOther)
{
	// No implementation because the copy operator is never used
	return *this;
}
