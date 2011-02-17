/*********************************************************\
 *  File: PGImage.h                                      *
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


#ifndef __PLPG_PGIMAGE_H__
#define __PLPG_PGIMAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLParticleGroups/SNParticleGroup.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Image particle group
*/
class PGImage : public SNParticleGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPG_RTTI_EXPORT, PGImage, "PLParticleGroups", PLParticleGroups::SNParticleGroup, "Image particle group")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(ImageFilename,		PLGeneral::String,		"Data/Textures/PGImage_Test.dds",	ReadWrite,	DirectValue,	"Image to create the particles from",	"Type='Image'")
		pl_attribute(RedColorKey,		PLGeneral::uint8,		0,									ReadWrite,	DirectValue,	"Color key red component",				"")
		pl_attribute(GreenColorKey,		PLGeneral::uint8,		0,									ReadWrite,	DirectValue,	"Color key green component",			"")
		pl_attribute(BlueColorKey,		PLGeneral::uint8,		0,									ReadWrite,	DirectValue,	"Color key blue component",				"")
		pl_attribute(ColorKeyTolerance,	char,					0,									ReadWrite,	DirectValue,	"Color key tolerance",					"")
		pl_attribute(ImageScale,		float,					0.1f,								ReadWrite,	DirectValue,	"Image scale",							"")
		// Overwritten SNParticleGroup variables
		pl_attribute(Material,			PLGeneral::String,		"Data/Effects/PGImage.plfx",		ReadWrite,	GetSet,			"Particle group material",				"Type='Material Effect Image TextureAni'")
		pl_attribute(Particles,			PLGeneral::uint32,		1,									ReadWrite,	GetSet,			"Number of particles",					"Min=1")
		// Overwritten PLScene::SceneNode variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	PointSprites,						ReadWrite,	GetSet,			"Flags",								"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPG_API PGImage();

		/**
		*  @brief
		*    Destructor
		*/
		PLPG_API virtual ~PGImage();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();
		virtual void OnActivate(bool bActivate);
		virtual void OnAddedToVisibilityTree(PLScene::VisNode &cVisNode);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bUpdate;	/**< Perform an update the next time? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups


#endif // __PLPG_PGIMAGE_H__
