/*********************************************************\
 *  File: Animation.h                                    *
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


#ifndef __PLRENDERER_ANIMATION_H__
#define __PLRENDERER_ANIMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Element.h>
#include <PLCore/Base/Event/Event.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class AnimationInfo;
class AnimationManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Animation control
*/
class Animation : public PLGeneral::Element<Animation> {


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
	//[ Events                                                ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<>		EventStart;			/**< Animation has been started */
		PLCore::Event<>		EventStop;			/**< Animation has been stopped */
		PLCore::Event<>		EventFrameChange;	/**< Current frame change event */
		PLCore::Event<int>	EventSpecialFrame;	/**< Special marked frame reached event, event ID as parameter (see 'AnimationEvent') */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Element name to set
		*  @param[in] pManager
		*    Animation manager using this element, can be NULL
		*/
		PLRENDERER_API Animation(const PLGeneral::String &sName = "", AnimationManager *pManager = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Animation();

		/**
		*  @brief
		*    Resets the animation
		*/
		PLRENDERER_API void Reset();

		/**
		*  @brief
		*    Get the animation active status
		*
		*  @return
		*    'true' if the animation is active, else 'false'
		*/
		PLRENDERER_API bool IsActive() const;

		/**
		*  @brief
		*    Set the animation active status
		*
		*  @param[in] bActive
		*    Should the animation be active?
		*
		*  @note
		*    - If an animation is inactive it is ignored
		*/
		PLRENDERER_API void SetActive(bool bActive = true);

		/**
		*  @brief
		*    Type of animation
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
		*    Starts an animation
		*
		*  @param[in] nStart
		*    Start frame (inclusive)
		*  @param[in] nEnd
		*    End frame (inclusive)
		*  @param[in] fSpeed
		*    Animation speed, if negative, the animation is played reversed
		*  @param[in] nFlags
		*    Animation flags (see EFlags)
		*
		*  @note
		*    - Use the start function below wich accepts a AnimationInfo
		*      as parameter for more complex animations
		*/
		PLRENDERER_API void Start(PLGeneral::uint32 nStart, PLGeneral::uint32 nEnd, float fSpeed = 24.0f, PLGeneral::uint32 nFlags = 0);

		/**
		*  @brief
		*    Starts an animation
		*
		*  @param[in] cAnimationInfo
		*    The animation information
		*  @param[in] bRestart
		*    Restart animation if it is already currently played?
		*
		*  @note
		*    - cAnimationInfo must stay a valid reference as long as the animation is played!
		*    - Because events are stored in the animation information it's possible that events
		*      are caused during the animation playback if an scene node is set
		*/
		PLRENDERER_API void Start(AnimationInfo &cAnimationInfo, bool bRestart = false);

		/**
		*  @brief
		*    Stops the animation
		*/
		PLRENDERER_API void Stop();

		/**
		*  @brief
		*    Pause the animation
		*/
		PLRENDERER_API void Pause();

		/**
		*  @brief
		*    Continues the animation
		*/
		PLRENDERER_API void Continue();

		/**
		*  @brief
		*    Returns the animation information
		*
		*  @return
		*    Animation information, NULL if there's no one
		*/
		PLRENDERER_API AnimationInfo *GetAnimation() const;

		/**
		*  @brief
		*    Gets the animation weight
		*
		*  @return
		*    Animation weight (normally 0.0-1.0)
		*/
		PLRENDERER_API float GetWeight() const;

		/**
		*  @brief
		*    Sets the animation weight
		*
		*  @param[in] fWeight
		*    Animation weight (normally 0.0-1.0)
		*/
		PLRENDERER_API void SetWeight(float fWeight = 1.0f);

		/**
		*  @brief
		*    Get the animation speed
		*
		*  @return
		*    Current speed of the animation, if negative, the animation is played reversed
		*/
		PLRENDERER_API float GetSpeed() const;

		/**
		*  @brief
		*    Set the animation speed
		*
		*  @param[in] fSpeed
		*    New speed for the animation, if negative, the animation is played reversed
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
		*    Get the animation running status
		*
		*  @return
		*    'true' if the animation is currently running, else 'false'
		*/
		PLRENDERER_API bool IsRunning() const;

		/**
		*  @brief
		*    Returns the start frame
		*
		*  @return
		*    The start frame (inclusive)
		*/
		PLRENDERER_API PLGeneral::uint32 GetStartFrame() const;

		/**
		*  @brief
		*    Returns the end frame
		*
		*  @return
		*    The end frame (inclusive)
		*/
		PLRENDERER_API PLGeneral::uint32 GetEndFrame() const;

		/**
		*  @brief
		*    Returns the number of frames
		*
		*  @return
		*    The number of frames
		*/
		PLRENDERER_API PLGeneral::uint32 GetNumOfFrames() const;

		/**
		*  @brief
		*    Get the current animation frame
		*
		*  @return
		*    Current animation frame (for instance 2.6)
		*/
		PLRENDERER_API float GetFrame() const;

		/**
		*  @brief
		*    Gets the progress from the current state to the next state (0.0-1.0)
		*
		*  @return
		*    Current animation frame (for instance 0.6)
		*/
		PLRENDERER_API float GetProgress() const;

		/**
		*  @brief
		*    Get the current animation frame as an integer
		*
		*  @return
		*    Current animation frame as an integer
		*
		*  @note
		*    - This function returns an integer for the current animation frame, e.g. if the
		*      animation frame is at 2.6f, it will return 2
		*/
		PLRENDERER_API PLGeneral::uint32 GetCurrentFrame() const;

		/**
		*  @brief
		*    Set the current animation frame
		*
		*  @param[in] fFrame
		*    Current animation frame
		*
		*  @note
		*    - If the given frame is out of bounds, it's clamped automatically
		*/
		PLRENDERER_API void SetCurrentFrame(float fFrame);

		/**
		*  @brief
		*    Get the next animation frame as an integer
		*
		*  @return
		*    Next animation frame as an integer
		*
		*  @see
		*    - GetCurrentFrame()
		*/
		PLRENDERER_API PLGeneral::uint32 GetNextFrame() const;

		/**
		*  @brief
		*    Updates the animation
		*
		*  @param[in] fTimeDifference
		*    Past time since last frame (use e.g. PLGeneral::Timing::GetInstance()->GetTimeDifference())
		*/
		PLRENDERER_API void Update(float fTimeDifference);

		/**
		*  @brief
		*    Returns whether animation events are enabled or not
		*
		*  @return
		*    'true' if animation events are enabled, else 'false'
		*
		*  @note
		*    - If animation events are enabled special frames are able to send
		*      an event message to the scene node connected with the animation
		*/
		PLRENDERER_API bool GetEvents() const;

		/**
		*  @brief
		*    Sets whether animation events are enabled or not
		*
		*  @param[in] bEvents
		*    Are animation events enabled?
		*
		*  @see
		*    - GetEvents()
		*/
		PLRENDERER_API void SetEvents(bool bEvents = true);

		//[-------------------------------------------------------]
		//[ Operators                                             ]
		//[-------------------------------------------------------]
		PLRENDERER_API Animation &operator =(const Animation &cSource);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Check if events should be caused
		*
		*  @param[in] nPreviousFrame
		*    Previous frame
		*
		*  @note
		*    - An event is caused if the current frame isn't equal to
		*      the previous and if there is an scene node receiving the caused event
		*/
		void CheckEvent(int nPreviousFrame = -1) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float			   m_fFrame;			/**< Current animation frame */
		bool			   m_bActive;			/**< Active status (if the channel is used in calculations) */
		bool			   m_bRunning;			/**< Running status */
		PLGeneral::uint32  m_nType;				/**< Animation type (for instance  0=skeleton, 1=vertex) */
		PLGeneral::uint32  m_nFlags;			/**< Animation flags */
		PLGeneral::uint32  m_nStart;			/**< Start frame of the animation */
		PLGeneral::uint32  m_nEnd;				/**< End frame of the animation */
		float			   m_fSpeed;			/**< Playback speed */
		bool			   m_bEvents;			/**< Are animation events enabled? */
		AnimationInfo	  *m_pAnimationInfo;	/**< Pointer to the animation information, can be NULL */
		float			   m_fWeight;			/**< Animation weight */
		bool			   m_bBounced;			/**< If ping pong playback, was there already a 'bounce'? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_ANIMATION_H__
