/*********************************************************\
 *  File: GuiApplication.h                              *
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


#ifndef __PLGUI_GUI_APPLICATION_H__
#define __PLGUI_GUI_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Application/ConsoleApplication.h>
#include <PLCore/Base/Event/EventHandler.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Widget;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gui application class
*
*  @remarks
*    An application class for a typical GUI application. Runs a
*    main loop that does the necessary message procressing and
*    provides methods to manage a main application window.
*/
class GuiApplication : public PLCore::ConsoleApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, GuiApplication, "PLGui", PLCore::ConsoleApplication, "Gui application class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sGuiFilename
		*    Filename of GUI to load, can be empty
		*/
		PLGUI_API GuiApplication(const PLGeneral::String &sGuiFilename = "");

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~GuiApplication();

		/**
		*  @brief
		*    Get main window
		*
		*  @return
		*    Pointer to the main window of the application, a null pointer on error
		*/
		PLGUI_API Widget *GetMainWindow() const;

		/**
		*  @brief
		*    Set main window
		*
		*  @param[in] pMainWindow
		*    Pointer to the main window of the application (a null pointer is also valid)
		*/
		PLGUI_API void SetMainWindow(Widget *pMainWindow);


	//[-------------------------------------------------------]
	//[ Protected virtual ConsoleApplication functions        ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initialization function that is called prior to Main()
		*
		*  @return
		*    'true' if all went fine, else 'false' which will stop the application
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that ConsoleApplication::Init() does
		*    - Call OnCreateMainWindow()
		*    - Return and go on with Main()
		*/
		PLGUI_API virtual bool Init();

		/**
		*  @brief
		*    Main function
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Run GUI main loop (processing GUI messages)
		*    - Exit loop when either the GUI or the application has been stopped
		*/
		PLGUI_API virtual void Main();

		/**
		*  @brief
		*    De-initialization function that is called after Main()
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that ConsoleApplication::DeInit() does
		*    - De-initialize system GUI
		*/
		PLGUI_API virtual void DeInit();


	//[-------------------------------------------------------]
	//[ Protected virtual GuiApplication functions            ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when application should open it's main window
		*
		*  @remarks
		*    Use this function to create a main window and set as pointer to it using SetMainWindow().
		*    The default implementation does the following tasks:
		*    - If a GUI filename is provided, create a window by loading that file
		*    - Otherwise, create an empty top-level window
		*/
		PLGUI_API virtual void OnCreateMainWindow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when main window was destroyed
		*/
		void OnDestroyMainWindow();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Event handlers
		PLCore::EventHandler<> EventHandlerOnDestroy;

		// Data
		Widget *m_pMainWindow;	/**< Main window of the application (can be a null pointer) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GUI_APPLICATION_H__
