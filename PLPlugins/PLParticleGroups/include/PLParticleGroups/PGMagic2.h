/*********************************************************\
 *  File: PGMagic2.h                                     *
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


#ifndef __PLPG1_PGMAGIC2_H__
#define __PLPG1_PGMAGIC2_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodes/SNParticleGroup.h>
#include "PLParticleGroups/PLParticleGroups.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Magic particle group 2
*/
class PGMagic2 : public PLScene::SNParticleGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPG1_RTTI_EXPORT, PGMagic2, "PLParticleGroups", PLScene::SNParticleGroup, "Magic particle group 2")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(SmallParticles,			bool,				true,							ReadWrite,	DirectValue,	"Small particles?",									"")
		pl_attribute(TexAni,					bool,				false,							ReadWrite,	DirectValue,	"Texture animation?",								"")
		pl_attribute(Size,						float,				1.0f,							ReadWrite,	DirectValue,	"Size",												"Min='0.0001'")
		// Overwritten PLScene::SNParticleGroup variables
		pl_attribute(Material,					PLGeneral::String,	"Data/Textures/PGMagic2.dds",	ReadWrite,	GetSet,			"Particle group material",							"Type='Material Effect Image TextureAni'")
		pl_attribute(Particles,					PLGeneral::uint32,	100,							ReadWrite,	GetSet,			"Number of particles",								"Min=1")
		pl_attribute(TextureAnimationColumns,	PLGeneral::uint32,	2,								ReadWrite,	GetSet,			"Number of animation frame columns in the texture",	"")
		pl_attribute(TextureAnimationRows,		PLGeneral::uint32,	1,								ReadWrite,	GetSet,			"Number of animation frame rows in the texture",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPG1_API PGMagic2();

		/**
		*  @brief
		*    Destructor
		*/
		PLPG1_API virtual ~PGMagic2();


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


#endif // __PLPG1_PGMAGIC2_H__
