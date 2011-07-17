/*********************************************************\
 *  File: FileSearchImpl.h                               *
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


#ifndef __PLGENERAL_FILESEARCH_IMPL_H__
#define __PLGENERAL_FILESEARCH_IMPL_H__
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
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FileSearch;
class FileAccess;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for platform specific file search implementations
*
*  @note
*    - Implementation of the bridge design pattern, this class is the implementor of the 'FileSearch' abstraction
*/
class FileSearchImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FileSearch;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		PLGENERAL_API FileSearchImpl(const FileAccess *pAccess);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~FileSearchImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual FileSearchImpl functions            ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Returns whether the file searcher has a next file
		*
		*  @return
		*    'true' if the file searcher has a next file, else 'false'
		*/
		virtual bool HasNextFile() = 0;

		/**
		*  @brief
		*    Returns the next filename
		*
		*  @return
		*    The next filename, empty on error
		*
		*  @note
		*    - Only the filename, no path shall be returned
		*    - No '/' at the end of the file name shall be added for directories
		*/
		virtual String GetNextFile() = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		const FileAccess *m_pAccess;	/**< File access information, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_FILESEARCH_IMPL_H__
