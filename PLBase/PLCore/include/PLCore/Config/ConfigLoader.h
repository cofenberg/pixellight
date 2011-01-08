/*********************************************************\
 *  File: ConfigLoader.h                                 *
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


#ifndef __PLCORE_CONFIGLOADER_H__
#define __PLCORE_CONFIGLOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Loader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract config loader base class
*
*  @note
*    - Normally all save functions accept a PixelLight string 'Group'-parameter, (default setting: empty string)
*      if this parameter is not empty, only configuration class instances are saved which are within the
*      provided configuration class group, else ALL configuration class instances are saved.
*    - Normally all save functions accept a boolean 'NoDefault'-parameter, (default setting: 'false')
*      if this parameter is 'true', all variables with default valures are not saved
*/
class ConfigLoader : public Loader {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Config;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, ConfigLoader, "PLCore", PLCore::Loader, "Abstract config loader base class")
		pl_properties
			pl_property("Type", "Config")
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
		PLCORE_API ConfigLoader();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ConfigLoader();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONFIGLOADER_H__
