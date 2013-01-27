/*********************************************************\
 *  File: PLPluginPlatformInfo.cpp                       *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Xml/Xml.h>
#include <PLCore/String/RegEx.h>
#include <PLCore/System/System.h>
#include "PLPluginPlatformInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PLPluginPlatformInfo::PLPluginPlatformInfo()
{
	// Setup defaults, only adding the information of the current platform is sufficient
	const String sPlatform = System::GetInstance()->GetPlatform();
	m_lstPlatformNames.Add(sPlatform);
	m_mapLibraryPostfix.Add(sPlatform + "Release", '.' + System::GetInstance()->GetSharedLibraryExtension());
	m_mapLibraryPostfix.Add(sPlatform + "Debug", "D." + System::GetInstance()->GetSharedLibraryExtension());
	m_lstBuildTypes.Add("Release");
	m_lstBuildTypes.Add("Debug");
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
			RegEx cDependencies("^\\s*pl_module_dependencies_" + sPlatformName.ToLower() + '_' + System::GetInstance()->GetPlatformBitArchitecture() + '_' + sBuildType.ToLower() + "\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
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
		pPlatformElement->SetAttribute("BitArchitecture", System::GetInstance()->GetPlatformBitArchitecture());
		for (uint32 j=0; j<m_lstBuildTypes.GetNumOfElements(); j++) {
			String sBuildType = m_lstBuildTypes[j];
			XmlElement *pLibrary = new XmlElement("Library");
			pLibrary->SetAttribute("Type", sBuildType);
			const String &sDependecies = m_mapLibraryDependencies.Get(sPlatformName + sBuildType);
			if (sDependecies != m_mapLibraryDependencies.NullKey)
				pLibrary->SetAttribute("Dependency", sDependecies);

			String sLibraryName = System::GetInstance()->GetSharedLibraryPrefix();
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
