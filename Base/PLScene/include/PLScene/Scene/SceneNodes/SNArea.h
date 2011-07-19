/*********************************************************\
 *  File: SNArea.h                                       *
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


#ifndef __PLSCENE_SCENENODE_AREA_H__
#define __PLSCENE_SCENENODE_AREA_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/PlaneSet.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    An area is a set of planes defining a convex area in your scene
*
*  @note
*    - Don't scale an area, this will produce some problems...
*/
class SNArea : public SceneNode, public PLMath::PlaneSet {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNArea, "PLScene", PLScene::SceneNode, "An area is a set of planes defining a convex area in your scene")
		// Properties
		pl_properties
			pl_property("Icon",	"Data/Textures/IconArea.dds")
		pl_properties_end
		// Attributes
		pl_attribute(Box,		PLCore::String,	"-0.5 -0.5 -0.5 0.5 0.5 0.5",	ReadWrite,	GetSet,	"Box min/max position (creates automatically the required planes)",	"")
		pl_attribute(Planes,	PLCore::String,	"",								ReadWrite,	GetSet,	"Planes defining the (normally convex) area",						"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLCore::String GetBox() const;
		PLS_API void SetBox(const PLCore::String &sValue);
		PLS_API PLCore::String GetPlanes() const;
		PLS_API void SetPlanes(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNArea();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNArea();

		/**
		*  @brief
		*    Draws the area
		*/
		PLS_API void Draw();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Check if an box should be created
		*/
		void CheckBox();

		/**
		*  @brief
		*    Check if planes should be added to the area
		*/
		void CheckPlanes();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sBox;		/**< Box min/max position (creates automatically the required planes) */
		PLCore::String m_sPlanes;	/**< Planes defining the (normally convex) area */


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNode functions                 ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void InitFunction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_AREA_H__
