/*********************************************************\
 *  File: Version.inl                                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
inline Version::~Version()
{
}

/**
*  @brief
*    Get project name
*/
inline String Version::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Set project name
*/
inline void Version::SetName(const String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Get codename
*/
inline String Version::GetCodename() const
{
	return m_sCodename;
}

/**
*  @brief
*    Set codename
*/
inline void Version::SetCodename(const String &sCodename)
{
	m_sCodename = sCodename;
}

/**
*  @brief
*    Get major version number
*/
inline uint16 Version::GetMajor() const
{
	return m_nMajor;
}

/**
*  @brief
*    Set major version number
*/
inline void Version::SetMajor(uint16 nMajor)
{
	m_nMajor = nMajor;
}

/**
*  @brief
*    Get minor version number
*/
inline uint16 Version::GetMinor() const
{
	return m_nMinor;
}

/**
*  @brief
*    Set minor version number
*/
inline void Version::SetMinor(uint16 nMinor)
{
	m_nMinor = nMinor;
}

/**
*  @brief
*    Get patch number
*/
inline uint16 Version::GetPatch() const
{
	return m_nPatch;
}

/**
*  @brief
*    Set patch number
*/
inline void Version::SetPatch(uint16 nPatch)
{
	m_nPatch = nPatch;
}

/**
*  @brief
*    Get release name
*/
inline String Version::GetRelease() const
{
	return m_sName;
}

/**
*  @brief
*    Set release name
*/
inline void Version::SetRelease(const String &sRelease)
{
	m_sRelease = sRelease;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
