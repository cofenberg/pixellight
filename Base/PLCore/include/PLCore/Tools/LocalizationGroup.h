/*********************************************************\
 *  File: LocalizationGroup.h                            *
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


#ifndef __PLCORE_LOCALIZATIONGROUP_H__
#define __PLCORE_LOCALIZATIONGROUP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Container/Array.h"
#include "PLCore/Container/HashMap.h"
#include "PLCore/Tools/Loadable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class LocalizationText;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Localization group
*/
class LocalizationGroup : public Loadable {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Localization;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API static const String English;	/**< "English" (default) */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the group
		*
		*  @return
		*    The name of the group
		*/
		PLCORE_API String GetName() const;

		/**
		*  @brief
		*    Returns the language used as 'from-key'
		*
		*  @return
		*    The language used as 'from-key'
		*/
		PLCORE_API String GetFromLanguage() const;

		/**
		*  @brief
		*    Sets the language used as 'from-key'
		*
		*  @param[in] sFrom
		*    The language used as 'from-key'
		*/
		PLCORE_API void SetFromLanguage(const String &sFrom = English);

		/**
		*  @brief
		*    Returns the language used as 'to-key'
		*
		*  @return
		*    The language used as 'to-key'
		*/
		PLCORE_API String GetToLanguage() const;

		/**
		*  @brief
		*    Sets the language used as 'to-key'
		*
		*  @param[in] sTo
		*    The language used as 'to-key'
		*/
		PLCORE_API void SetToLanguage(const String &sTo = English);

		/**
		*  @brief
		*    Returns the number of texts
		*
		*  @return
		*    The number of texts
		*/
		PLCORE_API uint32 GetNumOfTexts() const;

		/**
		*  @brief
		*    Returns a text by index
		*
		*  @param[in] nIndex
		*    Index of the text
		*
		*  @return
		*    The requested text, a null pointer on error
		*/
		PLCORE_API LocalizationText *GetText(uint32 nIndex) const;

		/**
		*  @brief
		*    Returns a text by name
		*
		*  @param[in] sName
		*    Name of the text
		*
		*  @return
		*    The requested text, a null pointer on error
		*/
		PLCORE_API LocalizationText *GetText(const String &sName) const;

		/**
		*  @brief
		*    Adds a new text
		*
		*  @param[in] sName
		*    Name of the new text
		*  @param[in] sTranslation
		*    The translation of the text
		*
		*  @return
		*    The new text, a null pointer on error (maybe there's already a text with the given name?)
		*/
		PLCORE_API LocalizationText *AddText(const String &sName, const String &sTranslation);

		/**
		*  @brief
		*    Removes a text by index
		*
		*  @param[in] nIndex
		*    Index of the text
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's no text with the given name?)
		*/
		PLCORE_API bool RemoveText(uint32 nIndex);

		/**
		*  @brief
		*    Removes a text by name
		*
		*  @param[in] sName
		*    Name of the text
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's no text with the given name?)
		*/
		PLCORE_API bool RemoveText(const String &sName);

		/**
		*  @brief
		*    Removes all texts
		*/
		PLCORE_API void RemoveAllTexts();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Name of the group
		*/
		LocalizationGroup(const String &sName);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		LocalizationGroup(const LocalizationGroup &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~LocalizationGroup();

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
		LocalizationGroup &operator =(const LocalizationGroup &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String							   m_sName;			/**< Name of the group */
		String							   m_sFromLanguage;	/**< The language used as 'from-key' */
		String							   m_sToLanguage;	/**< The language used as 'to-key' */
		Array<LocalizationText*>		   m_lstTexts;		/**< Localization texts list */
		HashMap<String, LocalizationText*> m_mapTexts;		/**< Localization texts map */


	//[-------------------------------------------------------]
	//[ Public virtual Loadable functions                     ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API virtual bool Unload();
		PLCORE_API virtual String GetLoadableTypeName() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOCALIZATIONGROUP_H__
