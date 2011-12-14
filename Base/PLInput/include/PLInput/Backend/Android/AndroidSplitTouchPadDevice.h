/*********************************************************\
 *  File: AndroidSplitTouchPadDevice.h                   *
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


#ifndef __PLINPUT_ANDROIDSPLITTOUCHPADDEVICE_H__
#define __PLINPUT_ANDROIDSPLITTOUCHPADDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/UpdateDevice.h"


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
struct AInputEvent;
typedef struct AInputEvent AInputEvent;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Slitscreen touchpad device for Android
*/
class AndroidSplitTouchPadDevice : public UpdateDevice {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		AndroidSplitTouchPadDevice();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~AndroidSplitTouchPadDevice();

		/**
		*  @brief
		*    Call this to process the next motion input event
		*
		*  @param[in] cAMotionInputEvent
		*    Motion input event to process
		*/
		void OnMotionInputEvent(const struct AInputEvent &cAMotionInputEvent);


	//[-------------------------------------------------------]
	//[ Public virtual UpdateDevice functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual void Update() override;

	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Writes all possible values from an android event to the consol
		*  @param[in] cAInputEvent
		*    Input event to log
		**/
		void LogEventValues(const struct AInputEvent &cAInputEvent);

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool  m_bRightTouchMoved;				/**< The right screen touch moved during the current touch? */
		float m_fPreviousRightTouchPositionX;	/**< Previous right touch x position */
		float m_fPreviousRightTouchPositionY;	/**< Previous right touch y position */
		float m_fPreviousRightTouchPressure;	/**< Previous right touch pressure */
		float m_fRightTouchPositionX;			/**< Current right touch x position */
		float m_fRightTouchPositionY;			/**< Current right touch y position */
		float m_fRightTouchPressure;			/**< Current right touch pressure */
		bool  m_bLeftTouchMoved;				/**< The left screen touch moved during the current touch? */
		float m_fPreviousLeftTouchPositionX;	/**< Previous left touch x position */
		float m_fPreviousLeftTouchPositionY;	/**< Previous left touch y position */
		float m_fPreviousLeftTouchPressure;		/**< Previous left touch pressure */
		float m_fLeftTouchPositionX;			/**< Current left touch x position */
		float m_fLeftTouchPositionY;			/**< Current left touch y position */
		float m_fLeftTouchPressure;				/**< Current left touch pressure */

};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_ANDROIDSPLITTOUCHPADDEVICE_H__
