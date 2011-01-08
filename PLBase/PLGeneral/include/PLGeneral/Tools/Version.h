/*********************************************************\
 *  File: Version.h                                      *
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


#ifndef __PLGENERAL_VERSION_H__
#define __PLGENERAL_VERSION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Version class
*/
class Version {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API Version();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Project name
		*  @param[in] sCodename
		*    Code name for this release
		*  @param[in] nMajor
		*    Major version number
		*  @param[in] nMinor
		*    Minor version number
		*  @param[in] nPatch
		*    Patch number
		*  @param[in] sRelease
		*    Release name (e.g. "r1" for release #1, "rc1" for release candidate #1, "nightly-date" for a nightly build etc.)
		*/
		PLGENERAL_API Version(const String &sName, const String &sCodename, uint16 nMajor, uint16 nMinor, uint16 nPatch, const String &sRelease);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~Version();

		/**
		*  @brief
		*    Get project name
		*
		*  @return
		*    Name of the project
		*/
		PLGENERAL_API String GetName() const;

		/**
		*  @brief
		*    Set project name
		*
		*  @param[in] sName
		*    Name of the project
		*/
		PLGENERAL_API void SetName(const String &sName);

		/**
		*  @brief
		*    Get codename
		*
		*  @return
		*    Codename of the release
		*/
		PLGENERAL_API String GetCodename() const;

		/**
		*  @brief
		*    Set codename
		*
		*  @param[in] sCodename
		*    Codename of the release
		*/
		PLGENERAL_API void SetCodename(const String &sCodename);

		/**
		*  @brief
		*    Get major version number
		*
		*  @return
		*    Major version
		*/
		PLGENERAL_API uint16 GetMajor() const;

		/**
		*  @brief
		*    Set major version number
		*
		*  @param[in] nMajor
		*    Major version
		*/
		PLGENERAL_API void SetMajor(uint16 nMajor);

		/**
		*  @brief
		*    Get minor version number
		*
		*  @return
		*    Minor version
		*/
		PLGENERAL_API uint16 GetMinor() const;

		/**
		*  @brief
		*    Set minor version number
		*
		*  @param[in] nMinor
		*    Minor version
		*/
		PLGENERAL_API void SetMinor(uint16 nMinor);

		/**
		*  @brief
		*    Get patch number
		*
		*  @return
		*    Patch number
		*/
		PLGENERAL_API uint16 GetPatch() const;

		/**
		*  @brief
		*    Set patch number
		*
		*  @param[in] nPatch
		*    Patch number
		*/
		PLGENERAL_API void SetPatch(uint16 nPatch);

		/**
		*  @brief
		*    Get release name
		*
		*  @return
		*    Release name
		*/
		PLGENERAL_API PLGeneral::String GetRelease() const;

		/**
		*  @brief
		*    Set release name
		*
		*  @param[in] sRelease
		*    Release name
		*/
		PLGENERAL_API void SetRelease(const PLGeneral::String &sRelease);

		/**
		*  @brief
		*    Returns a string representation of the version
		*
		*  @return
		*    String representation (for example: FooBar 1.0.1-rc5 - Bulky Bug)
		*/
		PLGENERAL_API String ToString() const;

		//[-------------------------------------------------------]
		//[ Comparison                                            ]
		//[-------------------------------------------------------]
		PLGENERAL_API bool operator ==(const Version &cVersion) const;
		PLGENERAL_API bool operator !=(const Version &cVersion) const;
		PLGENERAL_API bool operator >=(const Version &cVersion) const;
		PLGENERAL_API bool operator <=(const Version &cVersion) const;
		PLGENERAL_API bool operator  >(const Version &cVersion) const;
		PLGENERAL_API bool operator  <(const Version &cVersion) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String m_sName;			/**< Project name */
		String m_sCodename;		/**< Code name for this release */
		uint16 m_nMajor;		/**< Major version number */
		uint16 m_nMinor;		/**< Minor version number */
		uint16 m_nPatch;		/**< Patch number */
		String m_sRelease;		/**< Release name (e.g. "r1") */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_VERSION_H__
