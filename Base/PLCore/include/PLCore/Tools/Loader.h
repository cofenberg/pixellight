/*********************************************************\
 *  File: Loader.h                                       *
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


#ifndef __PLCORE_LOADER_H__
#define __PLCORE_LOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"
#include "PLCore/Container/Array.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Class;
class Loadable;
class LoaderImpl;
class LoadableType;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader class
*
*  @note
*    - Implementation of the proxy design pattern
*/
class Loader {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Loadable;
	friend class LoadableType;
	friend class LoadableManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Loader implementation class
		*
		*  @return
		*    Loader implementation class
		*/
		inline const Class &GetClass() const;

		/**
		*  @brief
		*    Returns the loader implementation
		*
		*  @return
		*    The loader implementation, a null pointer on error
		*
		*  @note
		*    - If required, this method creates an instance of the loader implementation class
		*/
		PLCORE_API LoaderImpl *GetImpl();

		/**
		*  @brief
		*    Returns the loadable type
		*
		*  @return
		*    The loadable type, a null pointer on (terrible) error
		*/
		inline LoadableType *GetType() const;

		/**
		*  @brief
		*    Returns the name of the loadable type
		*
		*  @return
		*    The name of the loadable type
		*/
		PLCORE_API String GetTypeName() const;

		/**
		*  @brief
		*    Returns the number of supported formats
		*
		*  @return
		*    The number of supported formats
		*/
		inline uint32 GetNumOfFormats();

		/**
		*  @brief
		*    Returns a supported format
		*
		*  @param[in] nIndex
		*    Format index
		*
		*  @return
		*    The requested supported format, empty string on error
		*/
		inline String GetFormat(uint32 nIndex);

		/**
		*  @brief
		*    Checks if a format is supported in a list of extensions
		*
		*  @param[in] sExtension
		*    Extension of loadable
		*
		*  @return
		*    'true' if the format is supported, else 'false'
		*/
		PLCORE_API bool IsFormatSupported(const String &sExtension);

		/**
		*  @brief
		*    Returns the formats string
		*
		*  @return
		*    The formats string
		*/
		PLCORE_API String GetFormats() const;

		/**
		*  @brief
		*    Returns the description string
		*
		*  @return
		*    The description string
		*/
		PLCORE_API String GetDescription() const;

		/**
		*  @brief
		*    Returns the whether loading is supported
		*
		*  @return
		*    'true' if loading is supported, else 'false'
		*/
		PLCORE_API bool CanLoad() const;

		/**
		*  @brief
		*    Returns the whether saving is supported
		*
		*  @return
		*    'true' if saving is supported, else 'false'
		*/
		PLCORE_API bool CanSave() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Default constructor
		*/
		Loader();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cClass
		*    Loader implementation class, must be derived from "PLCore::LoaderImpl"
		*/
		Loader(const Class &cClass);

		/**
		*  @brief
		*    Destructor
		*/
		~Loader();

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
		Loader &operator =(const Loader &cSource);

		/**
		*  @brief
		*    Initializes the formats list
		*
		*  @note
		*    - If the list is already initialized, nothing happens
		*/
		PLCORE_API void InitFormatsList();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const Class	  *m_pClass;		/**< Loader implementation class, must be derived from "PLCore::LoaderImpl", always valid! */
		LoaderImpl	  *m_pLoaderImpl;	/**< Loader implementation class instance, can be a null pointer */
		LoadableType  *m_pLoadableType;	/**< Loadable type, can be a null pointer */
		Array<String>  m_lstFormats;	/**< List of parsed formats */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Loader.inl"


#endif // __PLCORE_LOADER_H__
