/*********************************************************\
 *  File: SearchFilterWildcard.cpp                       *
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
#include "PLCore/File/SearchFilterWildcard.h"


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
SearchFilterWildcard::SearchFilterWildcard(const String &sFilter) :
	m_sFilter(sFilter)
{
}

/**
*  @brief
*    Destructor
*/
SearchFilterWildcard::~SearchFilterWildcard()
{
}

/**
*  @brief
*    Get filter string
*/
String SearchFilterWildcard::GetFilter() const
{
	return m_sFilter;
}


//[-------------------------------------------------------]
//[ Public virtual SearchFilter functions                 ]
//[-------------------------------------------------------]
bool SearchFilterWildcard::CheckFile(const String &sFilename)
{
	// To be Unicode save, we can't just use m_sFilter[nPosFilter] or sFilename[nPosName], we use GetSubstring() instead

	// Check empty filter (matches all files)
	if (!m_sFilter.GetLength())
		return true; // Match

	// Check file matching
	uint32 nNamePos   = 0;
	uint32 nFilterPos = 0;
	while (nFilterPos < m_sFilter.GetLength()) {
		// Get current symbols
		const String sFilterSymbol = m_sFilter.GetSubstring(nFilterPos, 1);
		const String sNameSymbol   = sFilename.GetSubstring(nNamePos,   1);

		// Check filter symbol
		if (sFilterSymbol == '?') {
			// Any character must follow
			if (sNameSymbol.GetLength() != 1)
				return false; // No match
			nNamePos++;
		} else if (sFilterSymbol == '*') {
			// *, check following *'s or ?'s
			int nMinLength = 0;
			while (m_sFilter.GetSubstring(nFilterPos+1, 1) == '*' || m_sFilter.GetSubstring(nFilterPos+1, 1) == '?') {
				if (m_sFilter.GetSubstring(nFilterPos+1, 1) == '?')
					nMinLength++;
				nFilterPos++;
			}

			// Get postfix index
			const uint32 nPostfix = nFilterPos + 1;			// Start index
				  uint32 nEnd     = m_sFilter.GetLength();	// End index sitting on '\0'

			// Find the first appearance of '*' and update 'nEnd' if something was found
			int nIndex = m_sFilter.IndexOf('*', nPostfix);
			if (nIndex >= 0)
				nEnd = nIndex; // Set the new '\0'

			// Find the first appearance of '?' and update 'nEnd' if something was found
			nIndex = m_sFilter.IndexOf('?', nPostfix);
			if (nIndex >= 0 && static_cast<uint32>(nIndex) < nEnd)
				nEnd = nIndex; // Set the new '\0'

			// Search for postfix in name
			int nFound;
			if (nEnd > nPostfix)
				nFound = sFilename.IndexOf(m_sFilter.GetSubstring(nPostfix, nEnd - nPostfix));
			else
				nFound = sFilename.GetLength();

			// Check result
			if (nFound >= 0 && nFound-static_cast<int>(nNamePos) >= nMinLength) {
				// Postfix found
				nNamePos = nFound;
			} else {
				// No match
				return false;
			}
		} else {
			// Character, must be equal
			if (m_sFilter.GetSubstring(nFilterPos, 1) != sFilename.GetSubstring(nNamePos, 1))
				return false; // No match
			nNamePos++;
		}

		// Next
		nFilterPos++;
	}

	// Check matching
	return (nNamePos == sFilename.GetLength());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
