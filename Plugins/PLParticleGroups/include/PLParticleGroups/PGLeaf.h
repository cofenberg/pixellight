/*********************************************************\
 *  File: PGLeaf.h                                       *
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


#ifndef __PLPG_PGLEAF_H__
#define __PLPG_PGLEAF_H__
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
*    Leaf particle group
*/
class PGLeaf : public SNParticleGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPG_RTTI_EXPORT, PGLeaf, "PLParticleGroups", PLParticleGroups::SNParticleGroup, "Leaf particle group")
		// Attributes
		pl_attribute(Radius,			float,				5.0f,								ReadWrite,	DirectValue,	"Leaf area radius",			"Min='0.0001'")
		pl_attribute(Height,			float,				15.0f,								ReadWrite,	DirectValue,	"Maximum leaf height",		"")
		pl_attribute(FloorHeight,		float,				0.0f,								ReadWrite,	DirectValue,	"Floor height",				"")
		pl_attribute(Wind,				PLMath::Vector3,	PLMath::Vector3(0.2f, 0.5f, -1.5f),	ReadWrite,	DirectValue,	"Wind direction",			"")
		pl_attribute(LeafSize,			float,				0.8f,								ReadWrite,	DirectValue,	"Leaf size",				"Min='0.0001'")
		pl_attribute(LeafSizeVariation,	float,				0.5f,								ReadWrite,	DirectValue,	"Leaf size variation",		"Min='0.0'")
			// Overwritten SNParticleGroup attributes
		pl_attribute(Material,			PLCore::String,		"Data/Effects/PGLeaf.plfx",			ReadWrite,	GetSet,			"Particle group material",	"Type='Material Effect Image TextureAni'")
		pl_attribute(Particles,			PLCore::uint32,		100,								ReadWrite,	GetSet,			"Number of particles",		"Min=1")
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
		PLPG_API PGLeaf();

		/**
		*  @brief
		*    Destructor
		*/
		PLPG_API virtual ~PGLeaf();


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
		void InitParticle(SNParticleGroup::Particle &cParticle) const;

		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnUpdate();


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


#endif // __PLPG_PGLEAF_H__
