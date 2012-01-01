/*********************************************************\
 *  File: ConstructFileFilter.cpp                        *
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
