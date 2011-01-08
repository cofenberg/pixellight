/*********************************************************\
 *  File: LocalizationLoaderPL.cpp                       *
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
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/Log/Log.h>
#include "PLCore/Tools/LocalizationText.h"
#include "PLCore/Tools/LocalizationGroup.h"
#include "PLCore/Tools/LocalizationLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(LocalizationLoaderPL)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool LocalizationLoaderPL::Load(LocalizationGroup &cLocalizationGroup, File &cFile)
{
	// Load XML document
	XmlDocument cDocument;
	if (cDocument.Load(cFile)) {
		// Get localization element
		const XmlElement *pLocalizationElement = cDocument.GetFirstChildElement("Localization");
		if (pLocalizationElement) {
			// Get the format version
			int nVersion = pLocalizationElement->GetAttribute("Version").GetInt();

			// Unkown
			if (nVersion > 1) {
				PL_LOG(Error, cDocument.GetValue() + ": " + UnknownFormatVersion)

			// 1 (current)
			} else if (nVersion == 1) {
				return LoadV1(cLocalizationGroup, *pLocalizationElement);

			// ""/0 (same format as 1)
			} else if (nVersion == 0) {
				// [DEPRECATED]
				PL_LOG(Warning, cDocument.GetValue() + ": " + DeprecatedFormatVersion)
				return LoadV1(cLocalizationGroup, *pLocalizationElement);

			// No longer supported format version
			} else if (nVersion >= 0) {
				PL_LOG(Warning, cDocument.GetValue() + ": " + NoLongerSupportedFormatVersion)

			// Invalid format version (negative!)
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + InvalidFormatVersion)
			}
		} else PL_LOG(Error, "Can't find 'Localization' element")
	} else PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())

	// Error!
	return false;
}

bool LocalizationLoaderPL::Save(const LocalizationGroup &cLocalizationGroup, File &cFile)
{
	// Create XML document
	XmlDocument cDocument;

	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Add localization
	XmlElement *pLocalizationElement = new XmlElement("Localization");
	pLocalizationElement->SetAttribute("Version", "1");

	// Set from/to attributes
	pLocalizationElement->SetAttribute("From", cLocalizationGroup.GetFromLanguage());
	pLocalizationElement->SetAttribute("To",   cLocalizationGroup.GetToLanguage());

	// Loop through all texts and save them
	for (uint32 nText=0; nText<cLocalizationGroup.GetNumOfTexts(); nText++) {
		// Get the text
		const LocalizationText *pLocalizationText = cLocalizationGroup.GetText(nText);
		if (pLocalizationText) {
			// Create the text element
			XmlElement *pText = new XmlElement("Text");
			pText->SetAttribute("Name", pLocalizationText->GetName());

			// Add value
			XmlText *pValue = new XmlText(pLocalizationText->GetTranslation());
			pText->LinkEndChild(*pValue);

			// Link text element to parent
			pLocalizationElement->LinkEndChild(*pText);
		}
	}

	// Link localization element to parent
	cDocument.LinkEndChild(*pLocalizationElement);

	// Save config
	cDocument.Save(cFile);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LocalizationLoaderPL::LocalizationLoaderPL() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
LocalizationLoaderPL::~LocalizationLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool LocalizationLoaderPL::LoadV1(LocalizationGroup &cLocalizationGroup, const XmlElement &cLocalizationElement) const
{
	// Get 'from'-attribute
	String sFromLanguage = cLocalizationElement.GetAttribute("From");
	cLocalizationGroup.SetFromLanguage(sFromLanguage.GetLength() ? sFromLanguage : LocalizationGroup::English);

	// Get 'to'-attribute
	String sToLanguage = cLocalizationElement.GetAttribute("To");
	cLocalizationGroup.SetToLanguage(sToLanguage.GetLength() ? sToLanguage : LocalizationGroup::English);

	// Iterate through all texts
	const XmlElement *pTextElement = cLocalizationElement.GetFirstChildElement("Text");
	while (pTextElement) {
		// Get name
		String sName = pTextElement->GetAttribute("Name");
		if (sName.GetLength()) {
			// Get value
			const XmlNode *pNode = pTextElement->GetFirstChild();
			if (pNode && pNode->GetType() == XmlNode::Text) {
				String sValue = pNode->GetValue();
				if (sValue.GetLength()) {
					// Is this text already within the localization group?
					if (cLocalizationGroup.GetText(sName)) {
						// Write a warning into the log
						PL_LOG(Warning, "Text '" + sName + "' of localization at row " + pTextElement->GetRow() + ", column " + pTextElement->GetColumn() + " is already used! (this text is ignored)")
					} else cLocalizationGroup.AddText(sName, sValue);
				}
			}
		}

		// Next element, please
		pTextElement = pTextElement->GetNextSiblingElement("Text");
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
