/*********************************************************\
 *  File: LocalizationText.h                             *
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


#ifndef __PLCORE_LOCALIZATIONTEXT_H__
#define __PLCORE_LOCALIZATIONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class LocalizationGroup;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Localization text
*/
class LocalizationText {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class LocalizationGroup;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the group the text is in
		*
		*  @return
		*    The group the text is in
		*/
		PLCORE_API LocalizationGroup &GetGroup() const;

		/**
		*  @brief
		*    Returns the name of the text
		*
		*  @return
		*    The name of the text
		*/
		PLCORE_API String GetName() const;

		/**
		*  @brief
		*    Returns the translation of the text
		*
		*  @return
		*    The translation of the text
		*/
		PLCORE_API String GetTranslation() const;

		/**
		*  @brief
		*    Sets the translation of the text
		*
		*  @param[in] sTranslation
		*    The translation of the text
		*/
		PLCORE_API void SetTranslation(const String &sTranslation);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGroup
		*    The group the text is in
		*  @param[in] sName
		*    Name of the text
		*  @param[in] sTranslation
		*    The translation of the text
		*
		*  @note
		*    - By default, the translation if set to the text name
		*/
		LocalizationText(LocalizationGroup &cGroup, const String &sName, const String &sTranslation);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		LocalizationText(const LocalizationText &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		~LocalizationText();

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
		LocalizationText &operator =(const LocalizationText &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		LocalizationGroup *m_pGroup;		/**< The group the text is in (always valid!) */
		String			   m_sName;			/**< Name of the group */
		String			   m_sTranslation;	/**< The translation of the text */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOCALIZATIONTEXT_H__
