/*********************************************************\
 *  File: GuiAndroid.h                                   *
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


#ifndef __PLGUI_GUIANDROID_H__
#define __PLGUI_GUIANDROID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLGui/Backend/Null/GuiNull.h"


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
struct AInputEvent;
typedef struct AInputEvent AInputEvent;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Android GUI implementation
*/
class GuiAndroid : public GuiNull {

	
	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pGui
		*    Platform independent GUI
		*/
		PLGUI_API GuiAndroid(Gui *pGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~GuiAndroid();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called to process the next Android input event
		*
		*  @param[in] cAInputEvent
		*    Android input event to process
		*/
		void OnInputEvent(const struct AInputEvent &cAInputEvent);

		/**
		*  @brief
		*    Call this to process the next key input event
		*
		*  @param[in] cAKeyInputEvent
		*    Key input event to process
		*/
		void OnKeyInputEvent(const struct AInputEvent &cAKeyInputEvent);

		/**
		*  @brief
		*    Get PLGui key for Android key code
		*
		*  @param[in] int32_t
		*    Key code
		*
		*  @return
		*    Corresponding PLGui key, null if Android key code is invalid
		*/
		PLCore::uint32 GetKeyboardKey(int32_t nKeyCode);


	//[-------------------------------------------------------]
	//[ Private slots                                         ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<const struct AInputEvent&> SlotInputEvent;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GUIANDROID_H__
