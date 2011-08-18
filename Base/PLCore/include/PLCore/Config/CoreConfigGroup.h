/*********************************************************\
 *  File: CoreConfigGroup.h                              *
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


#ifndef __PLCORE_CONFIGGROUP_H__
#define __PLCORE_CONFIGGROUP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Config/Config.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PLCore general configuration 'collection' class
*/
class CoreConfigGroup : public ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, CoreConfigGroup, "PLCore", PLCore::ConfigGroup, "PLCore general configuration 'collection' class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		CoreConfigGroup();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~CoreConfigGroup();


};

/**
*  @brief
*    PLCore general configuration classes
*/
class CoreGeneralConfig : public CoreConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, CoreGeneralConfig, "PLCore", PLCore::CoreConfigGroup, "PLCore general configuration classes")
		// Attributes
		pl_attribute(UsePixelLightRuntime,	bool,	true,	ReadWrite,	DirectValue,	"Use plugins and data from the PixelLight runtime directory? It's recommended to set this to false for standalone releases.",	"")
		pl_attribute(FirstRun,				bool,	true,	ReadWrite,	DirectValue,	"Is this the first application start?",																							"")
		pl_attribute(Language,				String,	"",		ReadWrite,	DirectValue,	"Current used language, if empty the current set OS locale language is used (for instance 'German'",							"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API CoreGeneralConfig();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~CoreGeneralConfig();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONFIGGROUP_H__
