/*********************************************************\
 *  File: AndroidSplitTouchPadDevice.cpp                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <android/input.h>
#include <android_native_app_glue.h>
#include <PLMath/Math.h>
#include <PLCore/Log/Log.h>
#include <PLCore/System/System.h>
#include <PLCore/System/SystemAndroid.h>
#include "PLInput/Input/Devices/SplitTouchPad.h"
#include "PLInput/Backend/Android/AndroidSplitTouchPadDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AndroidSplitTouchPadDevice::AndroidSplitTouchPadDevice() :
	// Left
	m_nLeftTouchPointerID(-1),
	m_fOriginLeftTouchPositionX(0.0f),
	m_fOriginLeftTouchPositionY(0.0f),
	m_fOriginLeftTouchPressure(0.0f),
	m_fLeftTouchPositionX(0.0f),
	m_fLeftTouchPositionY(0.0f),
	m_fLeftTouchPressure(0.0f),
	// Right
	m_nRightTouchPointerID(-1),
	m_fOriginRightTouchPositionX(0.0f),
	m_fOriginRightTouchPositionY(0.0f),
	m_fOriginRightTouchPressure(0.0f),
	m_fRightTouchPositionX(0.0f),
	m_fRightTouchPositionY(0.0f),
	m_fRightTouchPressure(0.0f)
{
	// Destroy device implementation automatically
	m_bDelete = true;
}

/**
*  @brief
*    Destructor
*/
AndroidSplitTouchPadDevice::~AndroidSplitTouchPadDevice()
{
}

/**
*  @brief
*    Call this to process the next motion input event
*/
void AndroidSplitTouchPadDevice::OnMotionInputEvent(const struct AInputEvent &cAMotionInputEvent)
{
	// We need the display size and orientation for splitting the screen
	struct android_app *pAndroidApp = reinterpret_cast<SystemAndroid*>(System::GetInstance())->GetAndroidApp();
	if (pAndroidApp) {
		ANativeWindow *pANativeWindow = pAndroidApp->window;
		if (pANativeWindow) {
			// Get the screen width: This is our base line for splitting
			const int32_t nScreenWidth = ANativeWindow_getWidth(pANativeWindow);

			// Get the number of pointers of data contained in this event
			const size_t nAndroidPointerCount = AMotionEvent_getPointerCount(&cAMotionInputEvent);

			// Evaluate every point
			for (size_t i=0; i<nAndroidPointerCount; i++) {
				size_t nAndroidPointerID    = AMotionEvent_getPointerId(&cAMotionInputEvent, i);
				size_t nAndroidAction       = (AMotionEvent_getAction(&cAMotionInputEvent) & AMOTION_EVENT_ACTION_MASK);
				size_t nAndroidPointerIndex = i;
				if (nAndroidAction == AMOTION_EVENT_ACTION_POINTER_DOWN || nAndroidAction == AMOTION_EVENT_ACTION_POINTER_UP) {
					nAndroidPointerIndex = (AMotionEvent_getAction(&cAMotionInputEvent) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
					nAndroidPointerID    = AMotionEvent_getPointerId(&cAMotionInputEvent, nAndroidPointerIndex);
				}

				// Get the current X and Y coordinate of this event for the given pointer index
				const float fPointerPositionX = AMotionEvent_getX(&cAMotionInputEvent, nAndroidPointerIndex);
				const float fPointerPositionY = AMotionEvent_getY(&cAMotionInputEvent, nAndroidPointerIndex);
				const float fPointerPressure  = AMotionEvent_getPressure(&cAMotionInputEvent, nAndroidPointerIndex);

				// Does the touch start?
				if (nAndroidAction == AMOTION_EVENT_ACTION_DOWN || nAndroidAction == AMOTION_EVENT_ACTION_POINTER_DOWN) {
					// Decide if the point is in the left or right screen half
					if (fPointerPositionX < (nScreenWidth/2)) {
						// This is the on the left half of the screen
						if (m_nLeftTouchPointerID == -1) {
							// This is our initial start point (origin position = current position)
							m_fOriginLeftTouchPositionX = m_fLeftTouchPositionX = fPointerPositionX;
							m_fOriginLeftTouchPositionY = m_fLeftTouchPositionY = fPointerPositionY;
							m_fOriginLeftTouchPressure  = m_fLeftTouchPressure  = fPointerPressure;

							// We're now active, save the ID of this pointer
							m_nLeftTouchPointerID = nAndroidPointerID;
						}
					} else {
						// This is on the right half of the screen
						if (m_nRightTouchPointerID == -1) {
							// This is our initial start point (origin position = current position)
							m_fOriginRightTouchPositionX = m_fRightTouchPositionX = fPointerPositionX;
							m_fOriginRightTouchPositionY = m_fRightTouchPositionY = fPointerPositionY;
							m_fOriginRightTouchPressure  = m_fRightTouchPressure  = fPointerPressure;

							// We're now active, save the ID of this pointer
							m_nRightTouchPointerID = nAndroidPointerID;
						}
					}

				// Does the touch stop?
				} else if (nAndroidAction == AMOTION_EVENT_ACTION_UP || nAndroidAction == AMOTION_EVENT_ACTION_POINTER_UP) {
					// Use the pointer ID to figure out whether this is our left or right pointer
					if (m_nLeftTouchPointerID == nAndroidPointerID) {
						// We're now longer active
						m_nLeftTouchPointerID = -1;

						// Let the left simulated pad stick snap back to it's origin
						SplitTouchPad *pSplitTouchPad = static_cast<SplitTouchPad*>(m_pDevice);
						if (pSplitTouchPad) {
							pSplitTouchPad->LeftX.SetValue(0.0f, false);
							pSplitTouchPad->LeftY.SetValue(0.0f, false);
						}
						m_fLeftTouchPositionX = m_fOriginLeftTouchPositionX;
						m_fLeftTouchPositionY = m_fOriginLeftTouchPositionY;
						m_fLeftTouchPressure  = m_fOriginLeftTouchPressure;

					} else if (m_nRightTouchPointerID == nAndroidPointerID) {
						// We're now longer active
						m_nRightTouchPointerID = -1;

						// Let the right simulated pad stick snap back to it's origin
						SplitTouchPad *pSplitTouchPad = static_cast<SplitTouchPad*>(m_pDevice);
						if (pSplitTouchPad) {
							pSplitTouchPad->RightX.SetValue(0.0f, false);
							pSplitTouchPad->RightY.SetValue(0.0f, false);
						}
						m_fRightTouchPositionX = m_fOriginRightTouchPositionX;
						m_fRightTouchPositionY = m_fOriginRightTouchPositionY;
						m_fRightTouchPressure  = m_fOriginRightTouchPressure;
					}

				// Did we move?
				} else if (nAndroidAction == AMOTION_EVENT_ACTION_MOVE) {
					// Use the pointer ID to figure out whether this is our left or right pointer
					if (m_nLeftTouchPointerID == nAndroidPointerID) {
						m_fLeftTouchPositionX = fPointerPositionX;
						m_fLeftTouchPositionY = fPointerPositionY;
						m_fLeftTouchPressure  = fPointerPressure;

					} else if (m_nRightTouchPointerID == nAndroidPointerID) {
						m_fRightTouchPositionX = fPointerPositionX;
						m_fRightTouchPositionY = fPointerPositionY;
						m_fRightTouchPressure  = fPointerPressure;
					}
				}
			}
		} else {
			// Error: there is now window instance...
			PL_LOG(Debug, "Error: No window instance, can't get the screen size")
		}
	} else {
		PL_LOG(Debug, "Error: No window instance, can't get the screen size")
	}
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void AndroidSplitTouchPadDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get split touch pad device
		SplitTouchPad *pSplitTouchPad = static_cast<SplitTouchPad*>(m_pDevice);

		// Maximum allowed delta
		static const float MaxDelta = 160.0f;
		static const float MinDelta = 5.0f;

		// Update left axes?
		if (m_nLeftTouchPointerID != -1) {
			// Get the left touch movement and clamp it to the maximum allowed delta
			float fLeftDeltaX		 = m_fLeftTouchPositionX - m_fOriginLeftTouchPositionX;
			float fLeftDeltaY		 = m_fLeftTouchPositionY - m_fOriginLeftTouchPositionY;
			float fLeftDeltaPressure = m_fLeftTouchPressure  - m_fOriginLeftTouchPressure;
			if (fLeftDeltaX > MaxDelta)
				fLeftDeltaX = MaxDelta;
			if (fLeftDeltaX < -MaxDelta)
				fLeftDeltaX = -MaxDelta;
			if (fLeftDeltaY > MaxDelta)
				fLeftDeltaY = MaxDelta;
			if (fLeftDeltaY < -MaxDelta)
				fLeftDeltaY = -MaxDelta;

			// Give our fat finger some space to sit down :D
			if (Math::Abs(fLeftDeltaX) < MinDelta)
				fLeftDeltaX = 0.0f;
			else
				fLeftDeltaX -= MinDelta*Math::Sign(fLeftDeltaX);
			if (Math::Abs(fLeftDeltaY) < MinDelta)
				fLeftDeltaY = 0.0f;
			else
				fLeftDeltaY -= MinDelta*Math::Sign(fLeftDeltaY);

			// Now update left axes
			if (pSplitTouchPad->LeftX.GetValue() != fLeftDeltaX) {
				PL_LOG(Debug, String("Touch LeftDeltaX: ") + fLeftDeltaX)
				pSplitTouchPad->LeftX.SetValue(fLeftDeltaX, false);
			}
			if (pSplitTouchPad->LeftY.GetValue() != fLeftDeltaY) {
				PL_LOG(Debug, String("Touch LeftDeltaY: ") + fLeftDeltaY)
				pSplitTouchPad->LeftY.SetValue(fLeftDeltaY, false);
			}
		}

		// Update right axes?
		if (m_nRightTouchPointerID != -1) {
			// Get the right touch movement and clamp it to the maximum allowed delta
			float fRightDeltaX		  = m_fRightTouchPositionX - m_fOriginRightTouchPositionX;
			float fRightDeltaY		  = m_fRightTouchPositionY - m_fOriginRightTouchPositionY;
			float fRightDeltaPressure = m_fRightTouchPressure  - m_fOriginRightTouchPressure;
			if (fRightDeltaX > MaxDelta)
				fRightDeltaX = MaxDelta;
			if (fRightDeltaX < -MaxDelta)
				fRightDeltaX = -MaxDelta;
			if (fRightDeltaY > MaxDelta)
				fRightDeltaY = MaxDelta;
			if (fRightDeltaY < -MaxDelta)
				fRightDeltaY = -MaxDelta;

			// Give our fat finger some space to sit down :D
			if (Math::Abs(fRightDeltaX) < MinDelta)
				fRightDeltaX = 0.0f;
			else
				fRightDeltaX -= MinDelta*Math::Sign(fRightDeltaX);
			if (Math::Abs(fRightDeltaY) < MinDelta)
				fRightDeltaY = 0.0f;
			else
				fRightDeltaY -= MinDelta*Math::Sign(fRightDeltaY);

			// Now update right axes
			if (pSplitTouchPad->RightX.GetValue() != fRightDeltaX) {
				PL_LOG(Debug, String("Touch RightDeltaX: ") + fRightDeltaX)
				pSplitTouchPad->RightX.SetValue(fRightDeltaX, false);
			}
			if (pSplitTouchPad->RightY.GetValue() != fRightDeltaY) {
				PL_LOG(Debug, String("Touch RightDeltaY: ") + fRightDeltaY)
				pSplitTouchPad->RightY.SetValue(fRightDeltaY, false);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Writes all possible values from an android event to the consol
*  @param[in] cAInputEvent
*    Input event to log
**/
void AndroidSplitTouchPadDevice::LogEventValues(const struct AInputEvent &cAInputEvent)
{
	// Get the number of pointers of data contained in this event
	const size_t nAndroidPointerCount = AMotionEvent_getPointerCount(&cAInputEvent);
	PL_LOG(Debug,String("Number of Points: ") + nAndroidPointerCount);

	for(int i = 0; i < nAndroidPointerCount; i++) {
		
		const int32_t nAndroidEventType = AInputEvent_getType (&cAInputEvent);
		if( nAndroidEventType == AINPUT_EVENT_TYPE_KEY)
		{
			//[TODO] implement this
		} else if(nAndroidEventType == AINPUT_EVENT_TYPE_MOTION)
		{
			PL_LOG(Debug,String("Event: ")				+ i								+ "     --");
		
			//Get the event source
			const int32_t nAndroidEventSource			= AInputEvent_getSource(&cAInputEvent);
			const int32_t nAndroidSourceClass			= (nAndroidEventSource & AINPUT_SOURCE_CLASS_MASK);
			const int32_t nAndroidSource				= (nAndroidEventSource & AINPUT_SOURCE_ANY);
			PL_LOG(Debug,String("-- Source Class:    ")	+ nAndroidSourceClass			+ "     --");
			PL_LOG(Debug,String("--- Source:         ")	+ nAndroidSource				+ "     --");
		
			// Get the combined motion event action code and the action code
			const int32_t nAndroidCombinedAction		= AMotionEvent_getAction(&cAInputEvent);
			const int32_t nAndroidAction				= (nAndroidCombinedAction & AMOTION_EVENT_ACTION_MASK);
			const int32_t nAndroidActionPointerIndex	= ((nAndroidCombinedAction & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT);
			const int32_t nAndroidPointerID				= AMotionEvent_getPointerId(&cAInputEvent, nAndroidActionPointerIndex);
			PL_LOG(Debug,String("-- Action:          ")	+ nAndroidAction				+ "     --");
			PL_LOG(Debug,String("--- APointerIndex:  ")	+ nAndroidActionPointerIndex	+ "     --");
			PL_LOG(Debug,String("--- APointerID:     ")	+ nAndroidPointerID				+ "     --");
		
			// Get the current X and Y coordingate of this event for the given pointer index
			m_fRightTouchPositionX		= AMotionEvent_getX(&cAInputEvent, nAndroidActionPointerIndex);
			m_fRightTouchPositionY		= AMotionEvent_getY(&cAInputEvent, nAndroidActionPointerIndex);
			m_fRightTouchPressure		= AMotionEvent_getPressure(&cAInputEvent, nAndroidActionPointerIndex);
			const float nAndroidRawX	= AMotionEvent_getRawX(&cAInputEvent, nAndroidActionPointerIndex);
			const float nAndroidRawY	= AMotionEvent_getRawY(&cAInputEvent, nAndroidActionPointerIndex);

			PL_LOG(Debug,String("-- Coordingate:     ")											   );
			PL_LOG(Debug,String("-- X:               ") + m_fRightTouchPositionX		+ "     --");
			PL_LOG(Debug,String("-- Y:               ") + m_fRightTouchPositionY		+ "     --");
			PL_LOG(Debug,String("-- Pressure:        ") + m_fRightTouchPressure			+ "     --");
			PL_LOG(Debug,String("-- Raw X:           ") + nAndroidRawX					+ "     --");
			PL_LOG(Debug,String("-- Raw Y:           ") + nAndroidRawY					+ "     --");

			//timeing -> get the initial down time and the 
			const int64_t nAndroidDownTime	= AMotionEvent_getDownTime(&cAInputEvent);
			const int64_t nAndroidEventTime = AMotionEvent_getEventTime(&cAInputEvent);
			const int64_t nPastTime = nAndroidEventTime - nAndroidDownTime;

			PL_LOG(Debug,String("- Timeing:          ")											   );
			PL_LOG(Debug,String("-- Down Time:       ") + nAndroidDownTime				+ "     --");
			PL_LOG(Debug,String("-- Event Time:      ") + nAndroidEventTime				+ "     --");
			PL_LOG(Debug,String("-- Time Elepsed:    ") + nPastTime						+ "     --");

			//get display size 
			PL_LOG(Debug,String("- Window:           "));
			struct android_app *app = ((SystemAndroid *) System::GetInstance())->GetAndroidApp();
			if (app) {
				ANativeWindow *pANativeWindow = app->window;
				if (pANativeWindow) {
					const int32_t width = ANativeWindow_getWidth(pANativeWindow);
					const int32_t height = ANativeWindow_getHeight(pANativeWindow);
					PL_LOG(Debug,String("-- Width:          ") + width							+ "     --");
					PL_LOG(Debug,String("-- Height:         ") + height							+ "     --");
				} else {
					PL_LOG(Debug,String("-- Error: NO WINDOW INSTANCE   --"));
				}
			} else {
				PL_LOG(Debug,String("-- Error: NO APPLICATION INSTANCE   --"));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
