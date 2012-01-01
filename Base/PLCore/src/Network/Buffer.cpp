/*********************************************************\
 *  File: Buffer.cpp                                     *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string.h>
#include "PLCore/Core/MemoryManager.h"
#include "PLCore/Network/Buffer.h"


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
Buffer::Buffer(uint32 nSize) :
	m_pBuffer(nullptr),
	m_nSize(0),
	m_nUsed(0),
	m_bRemoveDelimiters(true)
{
	// Allocate buffer?
	if (nSize)
		Allocate(nSize);
}

/**
*  @brief
*    Copy constructor
*/
Buffer::Buffer(const Buffer &cSource) :
	m_pBuffer(cSource.m_nUsed ? new char[cSource.m_nUsed] : nullptr),
	m_nSize(cSource.m_nUsed),
	m_nUsed(cSource.m_nUsed),
	m_bRemoveDelimiters(cSource.m_bRemoveDelimiters)
{
	// Copy buffer data
	if (m_pBuffer)
		MemoryManager::Copy(m_pBuffer, cSource.m_pBuffer, m_nUsed);
}

/**
*  @brief
*    Clear buffer
*/
void Buffer::Clear()
{
	// Release memory
	if (m_pBuffer) {
		delete [] m_pBuffer;
		m_pBuffer = nullptr;
	}

	// Reset
	m_nSize = 0;
	m_nUsed = 0;
}

/**
*  @brief
*    Allocates a new buffer (all previous data will be lost)
*/
void Buffer::Allocate(uint32 nSize)
{
	// Clear buffer first
	if (m_pBuffer)
		Clear();

	// Allocate new buffer
	if (nSize) {
		m_pBuffer = new char[nSize];
		m_nSize   = nSize;
	}
}

/**
*  @brief
*    Add data to the buffer
*/
void Buffer::Add(const char *pData, uint32 nSize)
{
	// Check parameters
	if (pData && nSize) {
		// Enlarge the buffer if necessary
		if (m_nUsed+nSize+1 > m_nSize) {
			// +32 = give some more memory to reduce too frequently allocation
			m_nSize   = m_nUsed + nSize + 32;
			m_pBuffer = static_cast<char*>(MemoryManager::Reallocator(m_pBuffer, m_nSize));
		}

		// Add data to buffer
		MemoryManager::Copy(m_pBuffer + m_nUsed, pData, nSize);
		m_pBuffer[m_nUsed+nSize] = 0;
		m_nUsed += nSize;
	}
}

/**
*  @brief
*    Get a line from the buffer
*/
String Buffer::GetLine()
{
	// Is there a data buffer?
	if (m_pBuffer) {
		// Search for a line delimiter
		const char *pszEOL = strstr(m_pBuffer, "\n");
		if (pszEOL) {
			// Allocate new string
			const int nSize = static_cast<int>(pszEOL - m_pBuffer);
			char *pszString = new char[nSize+1];
			MemoryManager::Copy(pszString, m_pBuffer, nSize);
			pszString[nSize] = '\0';

			// Remove line from buffer
			const int nRemaining = m_nUsed - nSize - 1;
			if (nRemaining > 0)
				MemoryManager::Copy(m_pBuffer, m_pBuffer + nSize + 1, nRemaining);
			else
				m_pBuffer[0] = 0;
			m_nUsed = nRemaining;

			// Save string. The string will take control over the created buffer
			String sLine = String(pszString, false, nSize);
			if (m_bRemoveDelimiters)
				sLine.RemoveLineEndings();

			// Return string
			return sLine;
		}
	}

	// Error, no valid line found
	return "";
}

/**
*  @brief
*    Copy operator
*/
Buffer &Buffer::operator =(const Buffer &cSource)
{
	// Release memory
	if (m_pBuffer) {
		delete [] m_pBuffer;
		m_pBuffer = nullptr;
	}

	// Set data
	m_nSize = cSource.m_nUsed;
	m_nUsed = cSource.m_nUsed;
	m_bRemoveDelimiters = cSource.m_bRemoveDelimiters;

	// Copy data
	if (m_nUsed) {
		m_pBuffer = new char[m_nUsed];
		MemoryManager::Copy(m_pBuffer, cSource.m_pBuffer, m_nUsed);
	}

	// Return this instance
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
