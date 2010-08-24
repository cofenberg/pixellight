/*********************************************************\
 *  File: TrayIconImpl.h                                 *
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


#ifndef __PLGUI_TRAYICONIMPL_H__
#define __PLGUI_TRAYICONIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Image;
class TrayIcon;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tray icon implementation base class
*/
class TrayIconImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class TrayIcon;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cTrayIcon
		*    Reference to platform independent tray icon
		*/
		PLGUI_API TrayIconImpl(TrayIcon &cTrayIcon);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~TrayIconImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual TrayIconImpl functions              ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Create tray icon
		*/
		virtual void CreateTrayIcon() = 0;

		/**
		*  @brief
		*    Destroy tray icon
		*/
		virtual void DestroyTrayIcon() = 0;

		/**
		*  @brief
		*    Set visibility
		*
		*  @param[in] bVisible
		*    'true' if tray icon is visible, else 'false'
		*/
		virtual void SetVisible(bool bVisible) = 0;

		/**
		*  @brief
		*    Update tray icon
		*
		*  @remarks
		*    Call this after changing e.g. icon or tooltip text
		*/
		virtual void Update() = 0;

		/**
		*  @brief
		*    Show a notification text
		*
		*  @param[in] sTitle
		*    Title
		*  @param[in] sText
		*    Text
		*/
		virtual void ShowNotification(const PLGeneral::String &sTitle, const PLGeneral::String &sText) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		TrayIcon *m_pTrayIcon;	/**< Pointer to the platform independent tray icon object */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_TRAYICONIMPL_H__
