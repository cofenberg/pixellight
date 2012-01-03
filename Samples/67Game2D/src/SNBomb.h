/*********************************************************\
 *  File: SNBomb.h                                       *
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


#ifndef __PLSAMPLE_67_SNBOMB_H__
#define __PLSAMPLE_67_SNBOMB_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/SceneNodes/SNSound.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bomb scene node
*/
class SNBomb : public PLSound::SNSound {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNBomb, "", PLSound::SNSound, "Bomb scene node")
		// Attributes
		pl_attribute(Killed,	bool,					false,							ReadWrite,	DirectValue,	"Killed?",																								"")
			// Overwritten PLSound::SNSound attributes
		pl_attribute(Sound,		PLCore::String,			"Data/Sounds/Explosion.ogg",	ReadWrite,	GetSet,			"Filename of the sound which should be played (full path, supported file formats are API dependent)",	"Ext='mp3 ogg wav mid midi it mod s3m xm'")
			// Overwritten PLScene::SceneNode attributes
		pl_attribute(Flags,		pl_flag_type(EFlags),	NoCulling,						ReadWrite,	GetSet,			"Flags",																								"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Slots
		pl_slot_0(OnUpdate,	"Called when the scene node needs to be updated",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SNBomb();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNBomb();

		/**
		*  @brief
		*    Returns the current frame
		*
		*  @return
		*    The current frame
		*/
		char GetFrame() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnUpdate();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fTimer;
		char  m_nFrame;
		float m_fFrame;
		bool  m_bAnimationDirection;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void OnActivate(bool bActivate) override;


};


#endif // __PLSAMPLE_67_SNBOMB_H__
