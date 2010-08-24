/*********************************************************\
 *  File: ClipBoardWindows.cpp                           *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/PLGuiWindowsIncludes.h"
#include "PLGui/Gui/Data/DataObject.h"
#include "PLGui/Backend/Windows/ClipBoardWindows.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ClipBoardWindows::ClipBoardWindows(ClipBoard &cClipBoard) : ClipBoardImpl(cClipBoard)
{
}

/**
*  @brief
*    Destructor
*/
ClipBoardWindows::~ClipBoardWindows()
{
}


//[-------------------------------------------------------]
//[ Private virtual ClipBoardImpl functions               ]
//[-------------------------------------------------------]
DataObject ClipBoardWindows::GetData()
{
	// Is Unicode text on the clipboard? Even if we copy ASCII into the clipboard this test
	// doesn't fail - we can't figure out if ASCII is enough :(
	if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
		// First at all, open the clipboard
		if (OpenClipboard(NULL)) {
			// Get the clipboard text
			String sText;
			HANDLE hData = GetClipboardData(CF_UNICODETEXT);
			if (hData) {
				wchar_t *pszBuffer = (wchar_t*)GlobalLock(hData);
				sText = pszBuffer; // We need to copy the text!
				GlobalUnlock(hData);
			}

			// Close the clipboard
			CloseClipboard();

			// Return text
			return DataObject(sText);
		}

	// Is ASCII text on the clipboard?
	} else if (IsClipboardFormatAvailable(CF_TEXT)) {
		// First at all, open the clipboard
		if (OpenClipboard(NULL)) {
			// Get the clipboard text
			String sText;
			HANDLE hData = GetClipboardData(CF_TEXT);
			if (hData) {
				char *pszBuffer = (char*)GlobalLock(hData);
				sText = pszBuffer; // We need to copy the text!
				GlobalUnlock(hData);
			}

			// Close the clipboard
			CloseClipboard();

			// Return text
			return DataObject(sText);
		}
	}

	// Error!
	return DataObject();
}

void ClipBoardWindows::SetData(const DataObject &cData)
{
	// Check format
	if (cData.GetType() == DataString) {
		// Text
		String sText = cData.GetString();
		if (sText.GetLength()) {
			// First at all, open the clipboard
			if (OpenClipboard(0)) {
				// Empty the clipboard
				EmptyClipboard();

				// ASCII or Unicode/UTF8 text?
				if (sText.GetFormat() == String::ASCII) {
					// Allocate a global memory object for the text
					HGLOBAL hClipBuffer = GlobalAlloc(GMEM_MOVEABLE, sText.GetLength() + 1);
					if (hClipBuffer) {
						// Lock the handle and copy the text to the buffer
						char *pszBuffer = (char*)GlobalLock(hClipBuffer);
						MemoryManager::Copy(pszBuffer, sText.GetASCII(), sText.GetLength());
						pszBuffer[sText.GetLength()] = '\0'; // Set terminating zero
						GlobalUnlock(hClipBuffer);

						// Place the handle on the clipboard
						SetClipboardData(CF_TEXT, hClipBuffer);
					}
				} else {
					// Allocate a global memory object for the text
					size_t  nCharacterSize = sizeof(wchar_t);
					HGLOBAL hClipBuffer    = GlobalAlloc(GMEM_MOVEABLE, (sText.GetLength() + 1)*nCharacterSize);
					if (hClipBuffer) {
						// Lock the handle and copy the text to the buffer
						wchar_t *pszBuffer = (wchar_t*)GlobalLock(hClipBuffer);
						MemoryManager::Copy(pszBuffer, sText.GetUnicode(), uint32(sText.GetLength()*nCharacterSize));
						pszBuffer[sText.GetLength()] = '\0'; // Set terminating zero
						GlobalUnlock(hClipBuffer);

						// Place the handle on the clipboard
						SetClipboardData(CF_UNICODETEXT, hClipBuffer);
					}
				}

				// Close the clipboard
				CloseClipboard();
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
