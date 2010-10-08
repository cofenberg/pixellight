/*********************************************************\
 *  File: SNGun.h                                        *
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


#ifndef __PLDEMO2DGAME_SNGUN_H__
#define __PLDEMO2DGAME_SNGUN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/SceneNodes/SNSound.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class GunController;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gun scene node
*/
class SNGun : public PLSound::SNSound {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNGun, "", PLSound::SNSound, "Gun scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		// Overwritten PLSound::SNSound variables
		pl_attribute(Sound,	PLGeneral::String,		"Data/Sounds/Shot.ogg",	ReadWrite,	GetSet,	"Filename of the sound which should be played (full path, supported file formats are API dependent)",	"Ext='mp3 ogg wav mid midi it mod s3m xm'")
		// Overwritten PLScene::SceneNode variables
		pl_attribute(Flags,	pl_flag_type(EFlags),	NoLoop|NoStartPlayback,	ReadWrite,	GetSet,	"Flags",																								"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SNGun();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNGun();

		/**
		*  @brief
		*    Returns the current frame
		*
		*  @return
		*    The current frame
		*/
		char GetFrame() const;


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SceneNodeModifier functions   ]
	//[-------------------------------------------------------]
	public:
		virtual PLInput::Controller *GetInputController() const;


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNode functions                 ]
	//[-------------------------------------------------------]
	protected:
		virtual void InitFunction();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a scene node was found
		*
		*  @param[in] cQuery
		*    Query found the scene node
		*  @param[in] cSceneNode
		*    Found scene node
		*/
		void OnSceneNode(PLScene::SceneQuery &cQuery, PLScene::SceneNode &cSceneNode);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLScene::SceneQuery &, PLScene::SceneNode &>	EventHandlerOnSceneNode;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		GunController *m_pController;	/**< Gun input controller instance, always valid! */
		char		   m_nFrame;
		float		   m_fFrame;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ] 
	//[-------------------------------------------------------]
	private:
		virtual void UpdateFunction();


};


#endif // __PLDEMO2DGAME_SNGUN_H__
