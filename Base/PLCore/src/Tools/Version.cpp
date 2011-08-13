/*********************************************************\
 *  File: Version.cpp                                    *
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
#include "PLCore/Tools/Version.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Version::Version() :
	m_nMajor(0),
	m_nMinor(0),
	m_nPatch(0),
	m_sRelease("")
{
}

/**
*  @brief
*    Constructor
*/
Version::Version(const String &sName, const String &sCodename, uint16 nMajor, uint16 nMinor, uint16 nPatch, const String &sRelease) :
	m_sName(sName),
	m_sCodename(sCodename),
	m_nMajor(nMajor),
	m_nMinor(nMinor),
	m_nPatch(nPatch),
	m_sRelease(sRelease)
{
}

/**
*  @brief
*    Destructor
*/
Version::~Version()
{
}

/**
*  @brief
*    Get project name
*/
String Version::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Set project name
*/
void Version::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Get codename
*/
String Version::GetCodename() const
{
	return m_sCodename;
}

/**
*  @brief
*    Set codename
*/
void Version::SetCodename(const String &sCodename)
{
	m_sCodename = sCodename;
}

/**
*  @brief
*    Get major version number
*/
uint16 Version::GetMajor() const
{
	return m_nMajor;
}

/**
*  @brief
*    Set major version number
*/
void Version::SetMajor(uint16 nMajor)
{
	m_nMajor = nMajor;
}

/**
*  @brief
*    Get minor version number
*/
uint16 Version::GetMinor() const
{
	return m_nMinor;
}

/**
*  @brief
*    Set minor version number
*/
void Version::SetMinor(uint16 nMinor)
{
	m_nMinor = nMinor;
}

/**
*  @brief
*    Get patch number
*/
uint16 Version::GetPatch() const
{
	return m_nPatch;
}

/**
*  @brief
*    Set patch number
*/
void Version::SetPatch(uint16 nPatch)
{
	m_nPatch = nPatch;
}

/**
*  @brief
*    Get release name
*/
String Version::GetRelease() const
{
	return m_sName;
}

/**
*  @brief
*    Set release name
*/
void Version::SetRelease(const String &sRelease)
{
	m_sRelease = sRelease;
}

/**
*  @brief
*    Returns a string representation of the version
*/
String Version::ToString() const
{
	String sVersion;

	// "Name "
	if (m_sName.GetLength())
		sVersion = m_sName + ' ';

	// "Major.Minor.Patch"
	sVersion += String() + static_cast<uint32>(m_nMajor) + '.' + static_cast<uint32>(m_nMinor) + '.' + static_cast<uint32>(m_nPatch);

	// "-release"
	if (m_sRelease.GetLength())
		sVersion += '-' + m_sRelease;

	// " - Codename"
	if (m_sCodename.GetLength())
		sVersion += " - " + m_sCodename;

	// Done
	return sVersion;
}


//[-------------------------------------------------------]
//[ Comparison                                            ]
//[-------------------------------------------------------]
bool Version::operator ==(const Version &cVersion) const
{
	return (m_sName		== cVersion.m_sName	 &&
			m_sCodename	== cVersion.m_sName	 &&
			m_nMajor	== cVersion.m_nMajor &&
			m_nMinor	== cVersion.m_nMinor &&
			m_nPatch	== cVersion.m_nPatch &&
			m_sRelease	== cVersion.m_sRelease);
}

bool Version::operator !=(const Version &cVersion) const
{
	return (m_sName		!= cVersion.m_sName	 ||
			m_sCodename	!= cVersion.m_sName	 ||
			m_nMajor	!= cVersion.m_nMajor ||
			m_nMinor	!= cVersion.m_nMinor ||
			m_nPatch	!= cVersion.m_nPatch ||
			m_sRelease	== cVersion.m_sRelease);
}

bool Version::operator <(const Version &cVersion) const
{
	// Major
	if (m_nMajor < cVersion.m_nMajor)
		return true;
	else if (m_nMajor == cVersion.m_nMajor) {
		// Minor
		if (m_nMinor < cVersion.m_nMinor)
			return true;
		else if (m_nMinor == cVersion.m_nMinor) {
			// Patch
			if (m_nPatch < cVersion.m_nPatch)
				return true;
		}
	}
	return false;
}

bool Version::operator >(const Version &cVersion) const
{
	// Major
	if (m_nMajor > cVersion.m_nMajor)
		return true;
	else if (m_nMajor == cVersion.m_nMajor) {
		// Minor
		if (m_nMinor > cVersion.m_nMinor)
			return true;
		else if (m_nMinor == cVersion.m_nMinor) {
			// Patch
			if (m_nPatch > cVersion.m_nPatch)
				return true;
		}
	}
	return false;
}

bool Version::operator <=(const Version &cVersion) const
{
	// Major
	if (m_nMajor < cVersion.m_nMajor)
		return true;
	else if (m_nMajor == cVersion.m_nMajor) {
		// Minor
		if (m_nMinor < cVersion.m_nMinor)
			return true;
		else if (m_nMinor == cVersion.m_nMinor) {
			// Patch
			if (m_nPatch < cVersion.m_nPatch)
				return true;
		}
	}
	return false;
}

bool Version::operator >=(const Version &cVersion) const
{
	// Major
	if (m_nMajor > cVersion.m_nMajor)
		return true;
	else if (m_nMajor == cVersion.m_nMajor) {
		// Minor
		if (m_nMinor > cVersion.m_nMinor)
			return true;
		else if (m_nMinor == cVersion.m_nMinor) {
			// Patch
			if (m_nPatch > cVersion.m_nPatch)
				return true;
		}
	}
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
