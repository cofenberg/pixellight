/*********************************************************\
 *  File: AndroidSplitTouchPadDevice.h                   *
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
*    Android gamepad device emulation by using a touch screen making it possible to e.g. move & look at the same time
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
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Left
		int   m_nLeftTouchPointerID;		/**< Left screen touch pointer ID, -1 if none */
		float m_fOriginLeftTouchPositionX;	/**< Origin left touch x position */
		float m_fOriginLeftTouchPositionY;	/**< Origin left touch y position */
		float m_fLeftTouchPositionX;		/**< Current left touch x position */
		float m_fLeftTouchPositionY;		/**< Current left touch y position */
		// Right
		int   m_nRightTouchPointerID;		/**< Right screen touch pointer ID, -1 if none */
		float m_fOriginRightTouchPositionX;	/**< Origin right touch x position */
		float m_fOriginRightTouchPositionY;	/**< Origin right touch y position */
		float m_fRightTouchPositionX;		/**< Current right touch x position */
		float m_fRightTouchPositionY;		/**< Current right touch y position */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_ANDROIDSPLITTOUCHPADDEVICE_H__
