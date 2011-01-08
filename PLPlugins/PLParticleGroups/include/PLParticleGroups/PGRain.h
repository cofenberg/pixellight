/*********************************************************\
 *  File: PGRain.h                                       *
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


#ifndef __PLPG1_PGRAIN_H__
#define __PLPG1_PGRAIN_H__
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
*    Rain particle group
*/
class PGRain : public PGPhysics {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPG1_RTTI_EXPORT, PGRain, "PLParticleGroups", PLParticleGroups::PGPhysics, "Rain particle group")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(EnergyPerSec,		PLGeneral::uint32,	30,							ReadWrite,	DirectValue,	"The energy consumption per second of one particle",					"")
		pl_attribute(EnergyMin,			PLGeneral::uint32,	300,						ReadWrite,	DirectValue,	"Minimum of energy",													"")
		pl_attribute(EnergyRange,		PLGeneral::uint32,	90,							ReadWrite,	DirectValue,	"EnergyMin + EnergyRange = particles energy",							"")
		pl_attribute(Brightness,		PLGeneral::uint32,	250,						ReadWrite,	DirectValue,	"Brightness",															"")
		pl_attribute(MediumSpeed,		float,				150.0f,						ReadWrite,	DirectValue,	"The speed factor of the particles",									"")
		pl_attribute(MediumSize,		PLGeneral::uint32,	5,							ReadWrite,	DirectValue,	"Medium size for each particles",										"")
		pl_attribute(DownVsAwayRatio,	PLGeneral::uint32,	150,						ReadWrite,	DirectValue,	"150 -> every 150 particle fly randomly away instead of falling down",	"")
		pl_attribute(BuildPerSec,		PLGeneral::uint32,	100,						ReadWrite,	DirectValue,	"Particle building speed",												"")
		// Overwritten PLScene::SNParticleGroup variables
		pl_attribute(Material,			PLGeneral::String,	"Data/Textures/PGRain.dds",	ReadWrite,	GetSet,			"Particle group material",												"Type='Material Effect Image TextureAni'")
		pl_attribute(Particles,			PLGeneral::uint32,	800,						ReadWrite,	GetSet,			"Number of particles",													"Min=1")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPG1_API PGRain();

		/**
		*  @brief
		*    Destructor
		*/
		PLPG1_API virtual ~PGRain();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void OnActivate(bool bActivate);
		virtual void OnAddedToVisibilityTree(PLScene::VisNode &cVisNode);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initializes a particle
		*
		*  @param[in] cParticle
		*    Particle to initialize
		*/
		void InitParticle(PLScene::SNParticleGroup::Particle &cParticle) const;

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


#endif // __PLPG1_PGRAIN_H__
