/*********************************************************\
 *  File: PGMagic1.h                                     *
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


#ifndef __PLPG1_PGMAGIC1_H__
#define __PLPG1_PGMAGIC1_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLParticleGroups/PGPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Magic particle group 1
*/
class PGMagic1 : public PGPhysics {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPG1_RTTI_EXPORT, PGMagic1, "PLParticleGroups", PLParticleGroups::PGPhysics, "Magic particle group 1")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Size,			float,				0.2f,							ReadWrite,	DirectValue,	"Size",						"Min='0.0001'")
		pl_attribute(BuildPerSec,	PLGeneral::uint32,	100,							ReadWrite,	DirectValue,	"Particle building speed",	"")
		// Overwritten PLScene::SNParticleGroup variables
		pl_attribute(Material,		PLGeneral::String,	"Data/Textures/PGMagic1.dds",	ReadWrite,	GetSet,			"Particle group material",	"Type='Material Effect Image TextureAni'")
		pl_attribute(Particles,		PLGeneral::uint32,	200,							ReadWrite,	GetSet,			"Number of particles",		"Min=1")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPG1_API PGMagic1();

		/**
		*  @brief
		*    Destructor
		*/
		PLPG1_API virtual ~PGMagic1();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void UpdateFunction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups


#endif // __PLPG1_PGMAGIC1_H__
