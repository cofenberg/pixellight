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
#include <PLCore/String/String.h>
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
	m_bRightTouchMoved(false),
	m_fPreviousRightTouchPositionX(0.0f),
	m_fPreviousRightTouchPositionY(0.0f),
	m_fPreviousRightTouchPressure(0.0f),
	m_fRightTouchPositionX(0.0f),
	m_fRightTouchPositionY(0.0f),
	m_fRightTouchPressure(0.0f),
	m_bLeftTouchMoved(false),
	m_fPreviousLeftTouchPositionX(0.0f),
	m_fPreviousLeftTouchPositionY(0.0f),
	m_fPreviousLeftTouchPressure(0.0f),
	m_fLeftTouchPositionX(0.0f),
	m_fLeftTouchPositionY(0.0f),
	m_fLeftTouchPressure(0.0f)
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
	// Get display size 
	struct android_app *app = ((SystemAndroid *) System::GetInstance())->GetAndroidApp();
	if(app != NULL) {
		ANativeWindow *pANativeWindow = app->window;
		if(pANativeWindow != NULL) {
			//get the screen width ... this is our base line for splitting
			const int32_t iScreenWidth  = ANativeWindow_getWidth(pANativeWindow);
			//const int32_t iScreenHeight = ANativeWindow_getHeight(pANativeWindow);

			// Get the number of pointers of data contained in this event
			const size_t nAndroidPointerCount = AMotionEvent_getPointerCount(&cAMotionInputEvent);

			// Evaluate every point
			for(int i = 0; i < nAndroidPointerCount; i++) {
				//LogEventValues(cAMotionInputEvent);
	
				// Get the current action and pointer index
				const int32_t nAndroidCombinedAction		= AMotionEvent_getAction(&cAMotionInputEvent);
				const int32_t nAndroidAction				= (nAndroidCombinedAction & AMOTION_EVENT_ACTION_MASK);
				const int32_t nAndroidActionPointerIndex	= ((nAndroidCombinedAction & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT);
										
				// Get the current X and Y coordinate of this event for the given pointer index
				const float fPointerPositionX = AMotionEvent_getX(&cAMotionInputEvent, i);
				const float fPointerPositionY = AMotionEvent_getY(&cAMotionInputEvent, i);
				const float fPointerPressure  = AMotionEvent_getPressure(&cAMotionInputEvent, i);
				
				
				// Does the touch start ?
				if(nAndroidAction == AMOTION_EVENT_ACTION_DOWN) {

					// Decide if the point is in the left or right screen half
					if(fPointerPositionX < (iScreenWidth/2)) {
						// This is the on the left half of the screen

						// This is our initial start point (previous position = current position)
						m_fPreviousLeftTouchPositionX = fPointerPositionX;
						m_fPreviousLeftTouchPositionY = fPointerPositionY;
						m_fPreviousLeftTouchPressure  = fPointerPressure;

						// The pointer was not yet moved
						m_bLeftTouchMoved = false;

					} else {
						// This is on the right half of the screen

						// This is our initial start point (previous position = current position)
						m_fPreviousRightTouchPositionX = fPointerPositionX;
						m_fPreviousRightTouchPositionY = fPointerPositionY;
						m_fPreviousRightTouchPressure  = fPointerPressure;

						// The pointer was not yet moved
						m_bRightTouchMoved = false;

					}
				} else {
					// Does the touch stop?
					if(nAndroidAction == AMOTION_EVENT_ACTION_UP) {

						// Decide if the pointer is in the left or right screen half
						if(fPointerPositionX < (iScreenWidth/2)) {
							// This is the on the left half of the screen

							// This is our initial end point (previous position = current position)
							m_fPreviousLeftTouchPositionX = fPointerPositionX;
							m_fPreviousLeftTouchPositionY = fPointerPositionY;
							m_fPreviousLeftTouchPressure  = fPointerPressure;
							
							// The pointer stoped moving
							m_bLeftTouchMoved = false;
						} else {
							// This is on the right half of the screen

							// this is our initial end point (previous position = current position)
							m_fPreviousRightTouchPositionX = fPointerPositionX;
							m_fPreviousRightTouchPositionY = fPointerPositionY;
							m_fPreviousRightTouchPressure  = fPointerPressure;
							
							// The pointer stoped moving
							m_bRightTouchMoved = false;

						}
					} else {
						// Did we move?
						if(nAndroidAction == AMOTION_EVENT_ACTION_MOVE)
						{
							// Decide if the pointer is in the left or right screen half
							if(fPointerPositionX < (iScreenWidth/2)) {
								// This is the on the left half of the screen
								m_fLeftTouchPositionX = fPointerPositionX;
								m_fLeftTouchPositionY = fPointerPositionY;
								m_fLeftTouchPressure  = fPointerPressure;
								m_bLeftTouchMoved = true;
								
							} else {
								// This is on the right half of the screen
								m_fRightTouchPositionX = fPointerPositionX;
								m_fRightTouchPositionY = fPointerPositionY;
								m_fRightTouchPressure  = fPointerPressure;
								m_bRightTouchMoved = true;

							}
						}
					}
				}

				
			}

		} else {
			//Error: there is now window instance ...
			PL_LOG(Debug,String("Error: No window instance, can't get the screen size"));
		}
	} else {
		PL_LOG(Debug,String("Error: No window instance, can't get the screen size"));
	}
	
}

//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void AndroidSplitTouchPadDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get mouse device
		SplitTouchPad *pSplitTouchPad = static_cast<SplitTouchPad*>(m_pDevice);

		{ // Update right axes
			
			// Get the right touch movement
			float fRightDeltaX		  = m_fRightTouchPositionX - m_fPreviousRightTouchPositionX;
			float fRightDeltaY		  = m_fRightTouchPositionY - m_fPreviousRightTouchPositionY;
			float fRightDeltaPressure = m_fRightTouchPressure - m_fPreviousRightTouchPressure;
			
			// Was the right touch point already moved?
			if (!m_bRightTouchMoved) {
				fRightDeltaX = fRightDeltaY = 0.0f;
				m_fPreviousRightTouchPositionX = m_fRightTouchPositionX;
				m_fPreviousRightTouchPositionY = m_fRightTouchPositionY;
			}

			// Now update right axes
			if (pSplitTouchPad->RightX.GetValue() != fRightDeltaX)
			{
				PL_LOG(Debug,String("Touch RightDeltaX: ") + fRightDeltaX);	
				pSplitTouchPad->RightX.SetValue(fRightDeltaX, false);
			}
			if (pSplitTouchPad->RightY.GetValue() != fRightDeltaY)
			{
				PL_LOG(Debug,String("Touch RightDeltaY: ") + fRightDeltaY);	
				pSplitTouchPad->RightY.SetValue(fRightDeltaY, false);
			}
		}

		{ // Update left axes
			// Get the left touch movement
			float fLeftDeltaX		 = m_fLeftTouchPositionX - m_fPreviousLeftTouchPositionX;
			float fLeftDeltaY		 = m_fLeftTouchPositionY - m_fPreviousLeftTouchPositionY;
			float fLeftDeltaPressure = m_fLeftTouchPressure - m_fPreviousLeftTouchPressure;

			// Was the left touch point already moved?
			if (!m_bLeftTouchMoved) {
				fLeftDeltaX = fLeftDeltaY = 0.0f;
				m_fPreviousLeftTouchPositionX = m_fLeftTouchPositionX;
				m_fPreviousLeftTouchPositionY = m_fLeftTouchPositionY;
			}

			// Now update left axes
			if (pSplitTouchPad->LeftX.GetValue() != fLeftDeltaX)
			{
				PL_LOG(Debug,String("Touch LeftDeltaX: ") + fLeftDeltaX);
				pSplitTouchPad->LeftX.SetValue(fLeftDeltaX, false);
			}
			if (pSplitTouchPad->LeftY.GetValue() != fLeftDeltaY)
			{
				PL_LOG(Debug,String("Touch LeftDeltaY: ") + fLeftDeltaY);
				pSplitTouchPad->LeftY.SetValue(fLeftDeltaY, false);
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
			if(app != NULL) {
				ANativeWindow *pANativeWindow = app->window;
				if(pANativeWindow != NULL) {
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
