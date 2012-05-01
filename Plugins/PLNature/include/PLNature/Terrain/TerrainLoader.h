/*********************************************************\
 *  File: TerrainLoader.h                                *
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


#ifndef __PLNATURE_SCENENODE_TERRAINLOADER_H__
#define __PLNATURE_SCENENODE_TERRAINLOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/LoaderImpl.h>
#include "PLNature/PLNature.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLNature {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract terrain loader base class
*/
class TerrainLoader : public PLCore::LoaderImpl {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLNATURE_RTTI_EXPORT, TerrainLoader, "PLNature", PLCore::LoaderImpl, "Abstract terrain loader base class")
		// Properties
		pl_properties
			pl_property("Type",	"Terrain")
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
		PLNATURE_API TerrainLoader();

		/**
		*  @brief
		*    Destructor
		*/
		PLNATURE_API virtual ~TerrainLoader();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLNature


#endif // __PLNATURE_SCENENODE_TERRAINLOADER_H__
