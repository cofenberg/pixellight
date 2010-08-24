/*********************************************************\
 *  File: TrayIconLinux.h                                *
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


#ifndef __PLGUI_TRAYICONLINUX_H__
#define __PLGUI_TRAYICONLINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLGui/Backend/TrayIconImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Widget;
class TrayIconWidgetLinux;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tray icon implementation for Linux
*/
class TrayIconLinux : public TrayIconImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GuiLinux;
	friend class TrayIconWidgetLinux;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cTrayIcon
		*    Reference to platform independent tray icon
		*/
		PLGUI_API TrayIconLinux(TrayIcon &cTrayIcon);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~TrayIconLinux();


	//[-------------------------------------------------------]
	//[ Private virtual TrayIconImpl functions                ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual void CreateTrayIcon();
		PLGUI_API virtual void DestroyTrayIcon();
		PLGUI_API virtual void SetVisible(bool bVisible);
		PLGUI_API virtual void Update();
		PLGUI_API virtual void ShowNotification(const PLGeneral::String &sTitle, const PLGeneral::String &sText);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Display				*m_pDisplay;	/**< X display */
		TrayIconWidgetLinux *m_pWidget;		/**< Tray icon widget */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TRAYICONLINUX_H__
