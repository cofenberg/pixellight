/*********************************************************\
 *  File: FileSearch.cpp                                 *
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
#include "PLGeneral/File/Directory.h"
#include "PLGeneral/File/FileImpl.h"
#include "PLGeneral/File/FileSearchImpl.h"
#include "PLGeneral/File/SearchFilterWildcard.h"
#include "PLGeneral/File/FileSearch.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FileSearch::FileSearch(const Directory &cDirectory, SearchFilter *pFilter) :
	m_pDirectory(&cDirectory),
	m_pFileSearchImpl(nullptr),
	m_pFilterWildcard(nullptr),
	m_pFilter(pFilter)
{
	// Valid file implementation?
	if (m_pDirectory->m_pFileImpl) {
		// Create a new file search implementation instance for the given directory
		m_pFileSearchImpl = m_pDirectory->m_pFileImpl->CreateSearch();

		// Find first file
		FindNextFile();
	}
}

/**
*  @brief
*    Constructor
*/
FileSearch::FileSearch(const Directory &cDirectory, const String &sFilter) :
	m_pDirectory(&cDirectory),
	m_pFileSearchImpl(nullptr),
	m_pFilterWildcard(new SearchFilterWildcard(sFilter)),
	m_pFilter(m_pFilterWildcard)
{
	// Valid file implementation?
	if (m_pDirectory->m_pFileImpl) {
		// Create a new file search implementation instance for the given directory
		m_pFileSearchImpl = m_pDirectory->m_pFileImpl->CreateSearch();

		// Find first file
		FindNextFile();
	}
}

/**
*  @brief
*    Copy constructor
*/
FileSearch::FileSearch(const FileSearch &cFileSearch) :
	m_pDirectory(cFileSearch.m_pDirectory),
	m_pFileSearchImpl(nullptr),
	m_pFilterWildcard(nullptr),
	m_pFilter(nullptr)
{
	// Copy wildcard filter
	if (cFileSearch.m_pFilterWildcard) {
		m_pFilterWildcard = new SearchFilterWildcard(cFileSearch.m_pFilterWildcard->GetFilter());
		m_pFilter		  = m_pFilterWildcard;
	}

	// Valid file implementation?
	if (m_pDirectory->m_pFileImpl) {
		// Create a new file search implementation instance for the given directory
		m_pFileSearchImpl = m_pDirectory->m_pFileImpl->CreateSearch();

		// Find first file
		FindNextFile();
	}
}

/**
*  @brief
*    Destructor
*/
FileSearch::~FileSearch()
{
	// Delete wildcard filter
	if (m_pFilterWildcard)
		delete m_pFilterWildcard;

	// Delete file searcher implementation
	if (m_pFileSearchImpl)
		delete m_pFileSearchImpl;
}

/**
*  @brief
*    Copy operator
*/
FileSearch &FileSearch::operator =(const FileSearch &cFileSearch)
{
	// Set directory
	m_pDirectory = cFileSearch.m_pDirectory;

	// Delete wildcard filter
	if (m_pFilterWildcard) {
		delete m_pFilterWildcard;
		m_pFilterWildcard = nullptr;
	}

	// Delete file searcher implementation
	if (m_pFileSearchImpl) {
		delete m_pFileSearchImpl;
		m_pFileSearchImpl = nullptr;
	}

	// Reset the filter and the next filename
	m_pFilter       = nullptr;
	m_sNextFilename = "";

	// Copy wildcard filter
	if (cFileSearch.m_pFilterWildcard) {
		m_pFilterWildcard = new SearchFilterWildcard(cFileSearch.m_pFilterWildcard->GetFilter());
		m_pFilter		  = m_pFilterWildcard;
	}

	// Valid file implementation?
	if (m_pDirectory->m_pFileImpl) {
		// Create a new file search implementation instance for the given directory
		m_pFileSearchImpl = m_pDirectory->m_pFileImpl->CreateSearch();

		// Find first file
		FindNextFile();
	}

	// Return this instance
	return *this;
}

/**
*  @brief
*    Returns whether the file searcher has a next file
*/
bool FileSearch::HasNextFile()
{
	return (m_sNextFilename.GetLength() > 0);
}

/**
*  @brief
*    Returns the next filename
*/
String FileSearch::GetNextFile()
{
	const String sFilename = m_sNextFilename;
	FindNextFile();
	return sFilename;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Finds the next file (according to the filter)
*/
bool FileSearch::FindNextFile()
{
	// Valid file search implementation?
	if (m_pFileSearchImpl) {
		// Find next file that matches the filter
		while (m_pFileSearchImpl->HasNextFile()) {
			m_sNextFilename = m_pFileSearchImpl->GetNextFile();

			// Check filter (if a filter is used)
			if (!m_pFilter || m_pFilter->CheckFile(m_sNextFilename)) {
				// Next file found
				return true;
			}
		}
	}

	// No more files
	m_sNextFilename = "";
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
