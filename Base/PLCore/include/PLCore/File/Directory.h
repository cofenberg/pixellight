/*********************************************************\
 *  File: Directory.h                                    *
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


#ifndef __PLCORE_DIRECTORY_H__
#define __PLCORE_DIRECTORY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/File/FileObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FileSearch;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class for accessing a directory within the file system
*/
class Directory : public FileObject {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FileSearch;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		inline Directory();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sUrl
		*    URL of a directory
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		inline Directory(const String &sUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cUrl
		*    URL of a directory
		*  @param[in] pAccess
		*    Additional file access information (can be a null pointer)
		*/
		inline Directory(const Url &cUrl, const FileAccess *pAccess = nullptr);

		/**
		*  @brief
		*    Destructor
		*
		*  @note
		*    - The directory is closed automatically
		*/
		inline virtual ~Directory();

		/**
		*  @brief
		*    Create directory
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		inline bool Create();

		/**
		*  @brief
		*    Create a directory recursively
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		PLCORE_API bool CreateRecursive();

		/**
		*  @brief
		*    Delete directory
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		inline bool Delete();

		/**
		*  @brief
		*    Returns a file searcher for listing the content of a directory
		*
		*  @param[in] sFilter
		*    Filter to be applied (e.g. "*.txt")
		*
		*  @return
		*    Pointer to a new file searcher, a null pointer on error (has to be deleted be the caller)
		*/
		PLCORE_API FileSearch *Search(const String &sFilter) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Directory(const Directory &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Directory &operator =(const Directory &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/File/Directory.inl"


#endif // __PLCORE_DIRECTORY_H__
