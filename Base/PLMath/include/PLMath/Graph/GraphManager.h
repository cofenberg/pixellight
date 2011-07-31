/*********************************************************\
 *  File: GraphManager.h                                 *
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


#ifndef __PLMATH_GRAPH_GRAPHMANAGER_H__
#define __PLMATH_GRAPH_GRAPHMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/ResourceManager.h>
#include "PLMath/Graph/Graph.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a manager for the graph resource
*
*  @note
*    - Unloads unused resources automatically by default
*/
class GraphManager : public PLCore::ResourceManager<Graph> {


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		GraphManager();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GraphManager();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual Graph *CreateResource(const PLCore::String &sName) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_GRAPH_GRAPHMANAGER_H__
