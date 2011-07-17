/*********************************************************\
 *  File: FileSearchWindows.h                            *
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


#ifndef __PLGENERAL_FILESEARCH_WINDOWS_H__
#define __PLGENERAL_FILESEARCH_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneralWindowsIncludes.h"
#include "PLGeneral/File/FileSearchImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows implementation of 'FileSearchImpl'
*/
class FileSearchWindows : public FileSearchImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FileSearch;
	friend class FileWindows;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sPath
		*    Search path
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		FileSearchWindows(const String &sPath, const FileAccess *pAccess);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FileSearchWindows();


	//[-------------------------------------------------------]
	//[ Private virtual FileSearchImpl functions              ]
	//[-------------------------------------------------------]
	private:
		virtual bool HasNextFile();
		virtual String GetNextFile();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HANDLE			m_hFind;
		String			m_sPath;
		String			m_sFind;
		WIN32_FIND_DATA	m_sFindData;
		bool			m_bHasNext;
		String			m_sFilename;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_FILESEARCH_WINDOWS_H__
