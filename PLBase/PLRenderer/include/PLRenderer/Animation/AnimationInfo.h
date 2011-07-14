/*********************************************************\
 *  File: AnimationInfo.h                                *
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


#ifndef __PLRENDERER_ANIMATIONINFO_H__
#define __PLRENDERER_ANIMATIONINFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Animation/AnimationEvent.h"
#include "PLRenderer/Animation/AnimationFrameInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Animation information
*/
class AnimationInfo {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Animation flags
		*/
		enum EFlags {
			Loop	 = 1<<0,	/**< Loop animation */
			PingPong = 1<<1		/**< Ping pong animation */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API AnimationInfo();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~AnimationInfo();

		/**
		*  @brief
		*    Returns the type of the animation
		*
		*  @return
		*    Animation type (for instance  0=skeleton  1=vertex)
		*/
		PLRENDERER_API PLGeneral::uint32 GetType() const;

		/**
		*  @brief
		*    Sets the animation type
		*
		*  @param[in] nType
		*    Animation type (for instance  0=skeleton  1=vertex)
		*/
		PLRENDERER_API void SetType(PLGeneral::uint32 nType = 0);

		/**
		*  @brief
		*    Returns the animation start frame
		*
		*  @return
		*    Animation start frame
		*/
		PLRENDERER_API PLGeneral::uint32 GetStartFrame() const;

		/**
		*  @brief
		*    Sets the animation start frame
		*
		*  @param[in] nStartFrame
		*    Animation start frame
		*/
		PLRENDERER_API void SetStartFrame(PLGeneral::uint32 nStartFrame = 0);

		/**
		*  @brief
		*    Returns the animation end frame
		*
		*  @return
		*    Animation end frame
		*/
		PLRENDERER_API PLGeneral::uint32 GetEndFrame() const;

		/**
		*  @brief
		*    Sets the animation end frame
		*
		*  @param[in] nEndFrame
		*    Animation end frame
		*/
		PLRENDERER_API void SetEndFrame(PLGeneral::uint32 nEndFrame = 0);

		/**
		*  @brief
		*    Returns the number of animation frames
		*
		*  @return
		*    Number of animation frames (normally EndFrame-StartFrame+1)
		*/
		PLRENDERER_API PLGeneral::uint32 GetNumOfFrames() const;

		/**
		*  @brief
		*    Get the animation speed
		*
		*  @return
		*    Playback speed of the animation, if negative, the animation is played reversed
		*/
		PLRENDERER_API float GetSpeed() const;

		/**
		*  @brief
		*    Set the animation speed
		*
		*  @param[in] fSpeed
		*    New playback speed for the animation, if negative, the animation is played reversed
		*/
		PLRENDERER_API void SetSpeed(float fSpeed = 24.0f);

		/**
		*  @brief
		*    Get the animation information flags
		*
		*  @return
		*    Animation information flags (see EFlags)
		*/
		PLRENDERER_API PLGeneral::uint32 GetFlags() const;

		/**
		*  @brief
		*    Sets the animation information flags
		*
		*  @param[in] nFlags
		*    Animation information flags (see EFlags)
		*/
		PLRENDERER_API void SetFlags(PLGeneral::uint32 nFlags = 0);

		/**
		*  @brief
		*    Returns information about a frame
		*
		*  @param[in] nIndex
		*    Index of the frame the information should be returned
		*
		*  @return
		*    Frame information, a null pointer if there's an error
		*/
		PLRENDERER_API AnimationFrameInfo *GetFrameInfo(PLGeneral::uint32 nIndex = 0) const;

		/**
		*  @brief
		*    Returns the event manager
		*
		*  @return
		*    Event manager
		*/
		PLRENDERER_API AnimationEventManager &GetEventManager();
		PLRENDERER_API const AnimationEventManager &GetEventManager() const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @note
		*    - The animation name itself is copied but at the end a
		*      number is added because each animation name must be unique!
		*
		*  @return
		*    Reference to this instance
		*/
		PLRENDERER_API virtual AnimationInfo &operator =(const AnimationInfo &cSource);

		/**
		*  @brief
		*    Get the animation source name
		*
		*  @return
		*    Animation source name, empty on error
		*
		*  @note
		*    - If this is a skeleton animation, the source name is the name of a skeleton.
		*      (SkeletonManager::Get(...))
		*    - If this is a vertex animation, the source name is the name of a morph target animation.
		*      (pMyMesh->GetMorphTargetAnimationManager().Get(...))
		*/
		PLRENDERER_API virtual PLGeneral::String GetSourceName() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32 m_nType;	/**< Animation type (for instance  0=skeleton  1=vertex) */
		PLGeneral::uint32 m_nStart;	/**< Start frame of the animation */
		PLGeneral::uint32 m_nEnd;	/**< End frame of the animation */
		float			  m_fSpeed;	/**< Playback speed */
		PLGeneral::uint32 m_nFlags;	/**< Animation information flags */

		/** Frame information */
		PLGeneral::Array<AnimationFrameInfo> m_lstFrameInfos;

		/** Event manager */
		AnimationEventManager m_cEventManager;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_ANIMATIONINFO_H__
