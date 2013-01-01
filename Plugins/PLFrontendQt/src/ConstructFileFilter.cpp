/*********************************************************\
 *  File: ConstructFileFilter.cpp                        *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/LoadableType.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLCore/Script/ScriptManager.h>
#include "PLFrontendQt/ConstructFileFilter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructs a file filter for "QFileDialog" by using the given loadable type
*/
String ConstructFileFilter::ByLoadableType(const String &sFilterName, const String &sLoadableType)
{
	String sFileFilter;

	// Get loadable type by using it's name
	LoadableType *pLoadableType = LoadableManager::GetInstance()->GetTypeByName(sLoadableType);
	if (pLoadableType) {
		// Get the number of supported formats
		const uint32 nNumOfFormats = pLoadableType->GetNumOfFormats();
		if (nNumOfFormats) {
			// Add scene file filter
			sFileFilter += sFilterName;
			sFileFilter += " (";

			// Add supported scene file formats
			for (uint32 i=0; i<nNumOfFormats-1; i++)
				sFileFilter += "*." + pLoadableType->GetFormat(i) + ' ';
			sFileFilter += "*." + pLoadableType->GetFormat(nNumOfFormats-1);

			// Finish the file filter
			sFileFilter += ")";
		}
	}

	// Done
	return sFileFilter;
}

/**
*  @brief
*    Constructs a file filter for "QFileDialog" by using the supported script languages
*/
String ConstructFileFilter::ByScriptLanguages(const String &sFilterName)
{
	String sFileFilter;

	// Get a list of supported script languages
	const Array<String> &lstScriptLanguages = ScriptManager::GetInstance()->GetScriptLanguages();
	if (lstScriptLanguages.GetNumOfElements()) {
		// Add scene file filter
		sFileFilter += sFilterName;
		sFileFilter += " (";

		// Iterate over the list of supported script languages and add the supported file formats
		for (uint32 i=0; i<lstScriptLanguages.GetNumOfElements(); i++) {
			// Get the name of the found script language
			const String sScriptLanguage = lstScriptLanguages[i];

			// Get the filename extension of the found script language
			String sScriptLanguageExtension = ScriptManager::GetInstance()->GetScriptLanguageExtension(sScriptLanguage);
			if (sScriptLanguageExtension.GetLength()) {
				sFileFilter += "*." + sScriptLanguageExtension + ' ';

				// Do also add upper case version to be on the safe side
				sFileFilter += "*." + sScriptLanguageExtension.ToUpper();
				if (i < lstScriptLanguages.GetNumOfElements()-1)
					sFileFilter += ' ';
			}
		}

		// Finish the file filter
		sFileFilter += ")";
	}

	// Done
	return sFileFilter;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
