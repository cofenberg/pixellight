/*********************************************************\
 *  File: Timing.h                                       *
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


#ifndef __PLGENERAL_TIMING_H__
#define __PLGENERAL_TIMING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/Singleton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
class Timing;
PLGENERAL_TEMPLATE template class PLGENERAL_API Singleton<Timing>;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Timing stuff
*
*  @remarks
*     This timing class offers a lot of timing tool functions you can for
*     instance use to create timed movement. Have a look at the 'System'-singleton
*     for the basic timing functions.
*/
class Timing : public Singleton<Timing> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Singleton<Timing>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ General                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns whether the timing is active or not
		*
		*  @return
		*    'true' if the timing is active, else 'false'
		*/
		PLGENERAL_API bool IsActive() const;

		/**
		*  @brief
		*    Sets whether the timing is active or not
		*
		*  @param[in] bActive
		*    Should the timing be active?
		*
		*  @note
		*    - If the timing is disabled the time difference between
		*      two frames will be always the maximum time difference
		*    - Use it only for testing
		*/
		PLGENERAL_API void SetActive(bool bActive = true);

		/**
		*  @brief
		*    Resets the timing
		*/
		PLGENERAL_API void Reset();

		/**
		*  @brief
		*    Checks whether the timing has to be updated or not
		*
		*  @param[in] pnTimeToWait
		*    If not NULL, if there's a FPS limit and it's not time for an update -> receives the time in
		*    milliseconds we need to wait until it's time for the next update, receives '0' in all other cases
		*
		*  @return
		*    'true' if the timing has to be updated, else 'false'
		*
		*  @remarks
		*    Normally the timing must be updated every frame. But if theres a frame
		*    rate limitation it's not allowed to update the timing every frame!
		*/
		PLGENERAL_API bool CheckUpdate(uint32 *pnTimeToWait = NULL) const;

		/**
		*  @brief
		*    Updates all time relevant stuff
		*
		*  @param[in] pnTimeToWait
		*    If not NULL, if there's a FPS limit and it's not time for an update -> receives the time in
		*    milliseconds we need to wait until it's time for the next update, receives '0' in all other cases
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's a frame rate limitation)
		*
		*  @see
		*    - CheckUpdate()
		*/
		PLGENERAL_API bool Update(uint32 *pnTimeToWait = NULL);

		//[-------------------------------------------------------]
		//[ Past time                                             ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the past time since last frame (seconds)
		*
		*  @return
		*    Past time since last frame
		*
		*  @remarks
		*    The timing class tries to compensate irregularities in timing automatically to
		*    avoid for instance sudden jumps through half of the universe. Further a maximum
		*    time difference is applied to avoid any totally undesired results.
		*/
		PLGENERAL_API float GetTimeDifference() const;

		/**
		*  @brief
		*    Returns the past time since last frame without any compensating (seconds)
		*
		*  @return
		*    Past time since last frame without any compensating
		*
		*  @note
		*   - Use GetTimeDifference() instead this function whenever you can
		*/
		PLGENERAL_API float GetTimeDifferenceNoCompensating() const;

		/**
		*  @brief
		*    Returns the maximum time difference
		*
		*  @return
		*    The maximum time difference since the last frame in seconds
		*
		*  @note
		*    - The maximum time difference will avoid a too hight time difference
		*      value which would probably end in undefined problems.
		*    - A maximum time difference of 0.15 is a good value
		*/
		PLGENERAL_API float GetMaxTimeDifference() const;

		/**
		*  @brief
		*    Sets the maximum time difference
		*
		*  @param[in] fMaxTimeDifference
		*    The maximum time difference since the last frame in seconds (> 0)
		*
		*  @see
		*    - GetMaxTimeDifference()
		*/
		PLGENERAL_API void SetMaxTimeDifference(float fMaxTimeDifference = 0.15f);

		/**
		*  @brief
		*    Returns the past time in milliseconds since the application start
		*
		*  @return
		*    Past time in milliseconds since the application start
		*/
		PLGENERAL_API uint32 GetPastTime() const;

		/**
		*  @brief
		*    Returns a general timing
		*
		*  @return
		*    General timing
		*
		*  @remarks
		*    On each timing update, the current time difference is added to this general timing.
		*/
		PLGENERAL_API float GetTimer() const;

		//[-------------------------------------------------------]
		//[ Frames                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the current frames per second (FPS)
		*
		*  @return
		*    Current frames per second
		*/
		PLGENERAL_API float GetFramesPerSecond() const;

		/**
		*  @brief
		*    Returns the number of past frames since timing start
		*
		*  @return
		*    Current frames per second (FPS)
		*/
		PLGENERAL_API uint32 GetPastFrames() const;

		/**
		*  @brief
		*    Returns the FPS limit
		*
		*  @return
		*    FPS limit, 0 if there's no FPS limitation
		*
		*  @note
		*    - FPS limitation could be used to avoid that the application
		*      uses to much system resources. (normally 30 FPS are enough)
		*    - Use a FPS limitation only in special situations!
		*      (users love FPS over 100 even if its more or less senseless ;-)
		*/
		PLGENERAL_API float GetFPSLimit() const;

		/**
		*  @brief
		*    Sets the FPS limit
		*
		*  @param[in] fFPSLimit
		*    FPS limit, 0 if there should be no limitation (>= 0)
		*
		*  @see
		*    - GetFPSLimit()
		*/
		PLGENERAL_API void SetFPSLimit(float fFPSLimit = 0.0f);

		//[-------------------------------------------------------]
		//[ Time scale                                            ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns if the timing is currently freezed or not
		*
		*  @return
		*    'true' if the timing is freezed at the moment, else 'false'
		*/
		PLGENERAL_API bool IsFreezed() const;

		/**
		*  @brief
		*    Set freezed mode
		*
		*  @param[in] bFreeze
		*    Should the timing be freezed or not?
		*
		*  @note
		*    - Freeze your application if you are not in rendering mode
		*      (e.g. you load something)
		*/
		PLGENERAL_API void Freeze(bool bFreeze = true);

		/**
		*  @brief
		*    Returns whether the timing is paused of not
		*
		*  @return
		*    'true' if the timing is paused, else 'false'
		*
		*  @note
		*    - If the timing is paused scene nodes, particles etc. are not updated
		*    - The timing will still be updated
		*/
		PLGENERAL_API bool IsPaused() const;

		/**
		*  @brief
		*    Set pause mode
		*
		*  @param[in] bPause
		*    Should the timing be paused or not?
		*/
		PLGENERAL_API void Pause(bool bPause = true);

		/**
		*  @brief
		*    Returns the time scale factor
		*
		*  @return
		*    Time scale factor
		*
		*  @note
		*    - The global time scale factor should only be manipulated for debugging
		*    - For 'slow motion' effects use the slow motion functions instead!
		*    - A factor of <= 0 is NOT allowed because this may cause problems in certain
		*      situations, pause the timer instead by hand!
		*    - Do NOT make the factor 'too' (for example > 4) extreme, this may cause
		*      problems in certain situations!
		*/
		PLGENERAL_API float GetTimeScaleFactor() const;

		/**
		*  @brief
		*    Sets the time scale factor
		*
		*  @param[in] fFactor
		*    Time scale, a factor of <= 0 is NOT allowed!
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the given factor is <= 0?)
		*
		*  @see
		*    - GetTimeScaleFactor()
		*/
		PLGENERAL_API bool SetTimeScaleFactor(float fFactor = 1.0f);

		/**
		*  @brief
		*    Returns if the slow motion is activated or not
		*
		*  @return
		*    'true' is the slow motion mode is activated, else 'false'
		*/
		PLGENERAL_API bool IsSlowMotion() const;

		/**
		*  @brief
		*    Activates/deactivates the slow motion mode
		*
		*  @param[in] bSlowMotion
		*    Should the slow motion mode be activated?
		*/
		PLGENERAL_API void SetSlowMotion(bool bSlowMotion = false);

		/**
		*  @brief
		*    Returns the slow motion factor
		*
		*  @param[in] bRealUsed
		*    The real used slow motion factor will be returned. If the slow motion mode
		*    is deactivated this will be 1!
		*
		*  @return
		*    The current slow motion factor
		*
		*  @note
		*    - The slow motion mode must be activated that this factor
		*      changes the game speed
		*    - Use this function to change the speed in general
		*    - A factor of <= 0 is NOT allowed because this may cause problems in certain
		*      situations, pause the timer instead by hand!
		*    - Do NOT make the factor 'too' (for example > 4) extreme, this may cause
		*      problems in certain situations!
		*/
		PLGENERAL_API float GetSlowMotionFactor(bool bRealUsed = true) const;

		/**
		*  @brief
		*    Sets the slow motion factor
		*
		*  @param[in] fSlowMotionFactor
		*    The slow motion factor, a factor of <= 0 is NOT allowed!
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the given factor is <= 0?)
		*
		*  @see
		*    - GetSlowMotionFactor()
		*/
		PLGENERAL_API bool SetSlowMotionFactor(float fSlowMotionFactor = 1.0f);

		/**
		*  @brief
		*    Returns the custom slow motion factor
		*
		*  @param[in] bRealUsed
		*    The real used slow motion factor will be returned. If the slow motion mode
		*    is deactivated this will be 1!
		*
		*  @return
		*    The current slow motion factor
		*
		*  @note
		*    - The slow motion mode must be activated that this
		*      factor changes the game speed
		*    - Use this factor to temporal slow motion effects
		*/
		PLGENERAL_API float GetCustomSlowMotionFactor(bool bRealUsed = true) const;

		/**
		*  @brief
		*    Sets the custom slow motion factor
		*
		*  @param[in] fSlowMotionFactor
		*    The slow motion factor, a factor of <= 0 is NOT allowed!
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the given factor is <= 0?)
		*
		*  @see
		*    - GetCustomSlowMotionFactor()
		*/
		PLGENERAL_API bool SetCustomSlowMotionFactor(float fSlowMotionFactor = 1.0f);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		Timing();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Timing(const Timing &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Timing();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Timing &operator =(const Timing &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool   m_bActive;						/**< Is the timing active? */
		uint32 m_nTimeStart;					/**< The start system time */
		uint32 m_nTimeNow;						/**< Current system time */
		uint32 m_nTimeLast;						/**< System time of the last frame */
		float  m_fTimeDifference;				/**< The past time since last frame (seconds) */
		float  m_fTimeDifferenceNoCompensating;	/**< The past time since last frame without any compensating (seconds) */
		float  m_fMaxTimeDifference;			/**< The maximum possible time difference (seconds) */
		float  m_fFramesPerSecond;				/**< Current frames per second (FPS... hopefully not SPS... Seconds Per Frame ;) */
		int	   m_nFramesSinceCheck;				/**< Number of frames since last FPS update */
		uint32 m_nPastFrames;					/**< Number of past frames since timing start */
		uint32 m_nLastFPSUpdateTime;			/**< The time were the last FPS update was done */
		float  m_fFPSUpdateTimer;				/**< Timing for updating FPS (only each second) */
		bool   m_bFreezed;						/**< Is the application currently freezed? */
		uint32 m_nFreezeTime;					/**< The time were the application was frozen */
		bool   m_bPause;						/**< Is the timing paused? */
		float  m_fTimeScaleFactor;				/**< Time scale factor */
		bool   m_bSlowMotion;					/**< Is the slow motion modus activated? */
		float  m_fSlowMotionFactor;				/**< The slow motion factor */
		float  m_fCustomSlowMotionFactor;		/**< The custom slow motion factor */
		uint32 m_nFPSLimitLastTime;				/**< Time were the last update was done */
		float  m_fFPSLimit;						/**< FPS limitation */
		float  m_fTimer;						/**< General timing */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_TIMING_H__
