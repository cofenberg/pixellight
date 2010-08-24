/*********************************************************\
 *  File: Loader.h                                       *
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


#ifndef __PLCORE_LOADER_H__
#define __PLCORE_LOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Object.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
	class Parameters;
}
namespace PLCore {
	class Loadable;
	class LoadableType;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract loader base class, derive your concrete loader implementations from this class
*
*  @remarks
*    A loader implementation is ONLY responsible for loading & saving, NOT for opening/closing
*    concrete file objects!
*    There's only one instance of each loader within the system, do NOT use class member variables,
*    do ONLY use local variables else you may get in trouble when using multi-threading.
*    By default, the loadable system looks for "Load" and "LoadParams" RTTI methods for loading, and
*    "Save" and "SaveParams" for saving. For example "Load" is used if there are no special user provided
*    parameters, "LoadParams" is used if a loader supports special format dependent parameters and
*    the user explicitly set them. Please note that it's also possible to add methods with other names,
*    when loading a loadable, this method name can be used explicitly. The first method parameter has to
*    be a reference to the loadable, the second parameter has to be a reference to the file to operate on.
*
*    Each loader should have the followig properties:
*    - "Type":    Loader type, usually only defined once within the abstract loader base class
*    - "Formats": File format extensions this loader can load in (for example: "bmp" or "jpg,jpeg")
*    - "Load":    "1" if loading is implemented, else "0"
*    - "Save":    "1" if saving is implemented, else "0"
*/
class Loader : public Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Loadable;
	friend class LoadableType;
	friend class LoadableManager;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API static const PLGeneral::String UnknownFormatVersion;				/**< 'Unknown format version' string */
		PLCORE_API static const PLGeneral::String DeprecatedFormatVersion;			/**< 'Deprecated format version' string */
		PLCORE_API static const PLGeneral::String NoLongerSupportedFormatVersion;	/**< 'No longer supported format version' string */
		PLCORE_API static const PLGeneral::String InvalidFormatVersion;				/**< 'Invalid format version' string */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, Loader, "PLCore", PLCore::Object, "Abstract loader base class, derive your concrete loader implementations from this class")
		pl_properties
			pl_property("Type",		"Unknown")
			pl_property("Formats",	"")
			pl_property("Load",		"0")
			pl_property("Save",		"0")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the loadable type
		*
		*  @return
		*    The loadable type, NULL on (terrible) error
		*/
		PLCORE_API LoadableType *GetType() const;

		/**
		*  @brief
		*    Returns the name of the loadable type
		*
		*  @return
		*    The name of the loadable type
		*/
		PLCORE_API PLGeneral::String GetTypeName() const;

		/**
		*  @brief
		*    Returns the number of supported formats
		*
		*  @return
		*    The number of supported formats
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfFormats();

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
		PLCORE_API PLGeneral::String GetFormat(PLGeneral::uint32 nIndex);

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
		PLCORE_API bool IsFormatSupported(const PLGeneral::String &sExtension);

		/**
		*  @brief
		*    Returns the formats string
		*
		*  @return
		*    The formats string
		*/
		PLCORE_API PLGeneral::String GetFormats() const;

		/**
		*  @brief
		*    Returns the description string
		*
		*  @return
		*    The description string
		*/
		PLCORE_API PLGeneral::String GetDescription() const;

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

		/**
		*  @brief
		*    Opens a file
		*
		*  @param[in] cFile
		*    File object
		*  @param[in] sFilename
		*    Filename of the file to open
		*  @param[in] bCreate
		*    Create the file if it doesn't exist?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool OpenFile(PLGeneral::File &cFile, const PLGeneral::String &sFilename, bool bCreate = false) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API Loader();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Loader();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initializes the formats list
		*
		*  @note
		*    - If the list is already initialized, nothing happens
		*/
		void InitFormatsList();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		LoadableType						*m_pLoadableType;	/**< Loadable type, can be NULL */
		PLGeneral::Array<PLGeneral::String>  m_lstFormats;		/**< List of parsed formats */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOADER_H__
