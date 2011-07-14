/*********************************************************\
 *  File: SNMScaleKeyframeAnimation.h                    *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_SCALEKEYFRAMEANIMATION_H__
#define __PLSCENE_SCENENODEMODIFIER_SCALEKEYFRAMEANIMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMTransform.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Chunk;
}
namespace PLRenderer {
	class Animation;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Keyframe scale animation scene node modifier class
*
*  @remarks
*    Animates the scale of the scene nodes over time using keyframes.
*/
class SNMScaleKeyframeAnimation : public SNMTransform {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			PlaybackNoLoop	 = 1<<2,	/**< No loop animation */
			PlaybackPingPong = 1<<3		/**< Ping pong animation */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMTransform::EFlags)
			pl_enum_value(PlaybackNoLoop,	"No loop animation")
			pl_enum_value(PlaybackPingPong,	"Ping pong animation")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMScaleKeyframeAnimation, "PLScene", PLScene::SNMTransform, "Keyframe scale animation scene node modifier class")
		// Attributes
		pl_attribute(Speed,				float,					1.0f,	ReadWrite,	DirectValue,	"Animation playback speed",					"")
		pl_attribute(FramesPerSecond,	PLGeneral::uint32,		24,		ReadWrite,	DirectValue,	"Frames per second",						"")
		pl_attribute(Keys,				PLGeneral::String,		"",		ReadWrite,	GetSet,			"Scale keys (x, y and z) chunk filename",	"")
			// Overwritten SceneNodeModifier attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",									"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	SceneNode&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetKeys() const;
		PLS_API void SetKeys(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLS_API SNMScaleKeyframeAnimation(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMScaleKeyframeAnimation();

		/**
		*  @brief
		*    Returns the chunk holding the keyframe data
		*
		*  @return
		*    The chunk holding the keyframe data
		*/
		PLS_API PLCore::Chunk &GetChunk();

		/**
		*  @brief
		*    Returns the animation controller
		*
		*  @return
		*    The animation controller
		*/
		PLS_API PLRenderer::Animation &GetAnimation();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
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
		PLGeneral::String	   m_sKeys;			/**< Scale keys (x, y and z) chunk filename */
		PLCore::Chunk		  *m_pChunk;		/**< Chunk holding the keyframe data, always valid! */
		PLRenderer::Animation *m_pAnimation;	/**< Animation, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_SCALEKEYFRAMEANIMATION_H__
