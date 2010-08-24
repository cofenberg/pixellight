/*********************************************************\
 *  File: Screen.h                                       *
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


#ifndef __PLGUI_SCREEN_H__
#define __PLGUI_SCREEN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLMath/Vector2i.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Gui;
class Widget;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Screen class
*
*  @remarks
*    This class represents a physical or logical screen (e.g. a monitor device)
*/
class Screen {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Gui;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pGui
		*    Pointer to the owner GUI
		*/
		PLGUI_API Screen(Gui *pGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~Screen();

		/**
		*  @brief
		*    Get owner GUI
		*
		*  @return
		*    GUI
		*/
		PLGUI_API Gui *GetGui() const;

		/**
		*  @brief
		*    Get screen name
		*
		*  @return
		*    Name of screen (this depends on the system)
		*/
		PLGUI_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Set screen name
		*
		*  @param[in] sName
		*    Name of screen
		*/
		PLGUI_API void SetName(const PLGeneral::String &sName);

		/**
		*  @brief
		*    Get screen position
		*
		*  @return
		*    Screen position (upper/left corner)
		*/
		PLGUI_API PLMath::Vector2i GetPos() const;

		/**
		*  @brief
		*    Set screen position
		*
		*  @param[in] vPos
		*    Screen size (x, y)
		*/
		PLGUI_API void SetPos(const PLMath::Vector2i &vPos);

		/**
		*  @brief
		*    Get screen size
		*
		*  @return
		*    Screen size (width, height)
		*/
		PLGUI_API PLMath::Vector2i GetSize() const;

		/**
		*  @brief
		*    Set screen size
		*
		*  @param[in] vSize
		*    Screen size (width, height)
		*/
		PLGUI_API void SetSize(const PLMath::Vector2i &vSize);

		/**
		*  @brief
		*    Check if this is the default screen
		*
		*  @return
		*    'true', if the screen is the default screen
		*/
		PLGUI_API bool IsDefault() const;

		/**
		*  @brief
		*    Set if this is the default screen
		*
		*  @param[in] bDefault
		*    'true', if the screen is the default screen
		*/
		PLGUI_API void SetDefault(bool bDefault);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Gui					*m_pGui;			/**< Pointer to GUI instance */
		mutable Widget		*m_pDesktopWidget;	/**< Desktop widget */
		bool				 m_bDefault;		/**< 'true' if the screen is the default screen */
		PLGeneral::String	 m_sName;			/**< Screen name */
		PLMath::Vector2i	 m_vPos;			/**< Screen position */
		PLMath::Vector2i	 m_vSize;			/**< Screen size */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_SCREEN_H__
