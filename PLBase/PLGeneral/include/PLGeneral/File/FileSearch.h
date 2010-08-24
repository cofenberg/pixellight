/*********************************************************\
 *  File: FileSearch.h                                   *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_FILESEARCH_H__
#define __PLGENERAL_FILESEARCH_H__
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
class Directory;
class FileSearchImpl;
class SearchFilter;
class SearchFilterWildcard;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class for searching inside a directory
*/
class FileSearch {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cDirectory
		*    Directory to search in
		*  @param[in] pFilter
		*    Search filter to use (can be NULL)
		*/
		PLGENERAL_API FileSearch(const Directory &cDirectory, SearchFilter *pFilter = NULL);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cDirectory
		*    Directory to search in
		*  @param[in] sFilter
		*    Wildcard search filter (e.g. "*.txt")
		*/
		PLGENERAL_API FileSearch(const Directory &cDirectory, const String &sFilter);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cFileSearch
		*    'FileSearch' to be copied
		*/
		PLGENERAL_API FileSearch(const FileSearch &cFileSearch);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~FileSearch();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cFileSearch
		*    'FileSearch' to be copied
		*
		*  @return
		*    Reference to this instance
		*/
		PLGENERAL_API FileSearch &operator =(const FileSearch &cFileSearch);

		/**
		*  @brief
		*    Returns whether the file searcher has a next file
		*
		*  @return
		*    'true' if the file searcher has a next file, else 'false'
		*/
		PLGENERAL_API bool HasNextFile();

		/**
		*  @brief
		*    Returns the next filename
		*
		*  @return
		*    The next filename, empty on error
		*/
		PLGENERAL_API String GetNextFile();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Finds the next file (according to the filter)
		*
		*  @return
		*    'true' if a next file is available
		*/
		bool FindNextFile();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const Directory		 *m_pDirectory;			/**< The owning directory (always valid!) */
		FileSearchImpl		 *m_pFileSearchImpl;	/**< File searcher implementation, can be NULL */
		SearchFilterWildcard *m_pFilterWildcard;	/**< Automatically created wildcard filter, can be NULL */
		SearchFilter		 *m_pFilter;			/**< Search filter, can be NULL */
		String				  m_sNextFilename;		/**< Filename of next file */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_FILESEARCH_H__
