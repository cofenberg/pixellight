/*********************************************************\
 *  File: LoaderImpl.h                                   *
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


#ifndef __PLCORE_LOADER_IMPL_H__
#define __PLCORE_LOADER_IMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Object.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract loader implementation base class, derive your concrete loader implementations from this class
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
*    Each loader should have the following properties:
*    - "Type":    Loader type, usually only defined once within the abstract loader base class
*    - "Formats": File format extensions this loader can load in (for example: "bmp" or "jpg,jpeg")
*    - "Load":    "1" if loading is implemented, else "0"
*    - "Save":    "1" if saving is implemented, else "0"
*/
class LoaderImpl : public Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Loader;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API static const String UnknownFormatVersion;			/**< 'Unknown format version' string */
		PLCORE_API static const String DeprecatedFormatVersion;			/**< 'Deprecated format version' string */
		PLCORE_API static const String NoLongerSupportedFormatVersion;	/**< 'No longer supported format version' string */
		PLCORE_API static const String InvalidFormatVersion;			/**< 'Invalid format version' string */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, LoaderImpl, "PLCore", PLCore::Object, "Abstract loader implementation base class, derive your concrete loader implementations from this class")
		// Properties
		pl_properties
			pl_property("Type",		"Unknown")
			pl_property("Formats",	"")
			pl_property("Load",		"0")
			pl_property("Save",		"0")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API LoaderImpl();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~LoaderImpl();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_LOADER_IMPL_H__
