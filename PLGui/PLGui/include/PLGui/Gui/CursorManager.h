/*********************************************************\
 *  File: CursorManager.h                                *
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


#ifndef __PLGUI_CURSORMANAGER_H__
#define __PLGUI_CURSORMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
#include "PLGui/Gui/Resources/Cursor.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Gui;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Cursor manager
*/
class CursorManager {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*/
		PLGUI_API CursorManager(Gui &cGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~CursorManager();

		/**
		*  @brief
		*    Get owner GUI
		*
		*  @return
		*    Pointer to GUI object (never a null pointer)
		*/
		PLGUI_API Gui *GetGui() const;

		/**
		*  @brief
		*    Get standard cursor
		*
		*  @param[in] nCursor
		*    Cursor ID
		*
		*  @return
		*    Mouse cursor, can be a null pointer if the backend doesn't support it
		*/
		PLGUI_API Cursor *GetCursor(EMouseCursor nCursor);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Gui		*m_pGui;						/**< Pointer to GUI */
		Cursor	*m_pCursors[Cursor_Count];		/**< Standard mouse cursors */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_CURSORMANAGER_H__
