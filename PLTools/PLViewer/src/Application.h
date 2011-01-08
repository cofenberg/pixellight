/*********************************************************\
 *  File: Application.h                                  *
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


#ifndef __PLVIEWER_APPLICATION_H__
#define __PLVIEWER_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLEngine/Application/BasicSceneApplication.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class DataObject;
	class DialogChooseFile;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*/
class Application : public PLEngine::BasicSceneApplication {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLGeneral::String DefaultScene;	/**< The used default scene loaded at start, if empty a file dialog will appear */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Application();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Application();

		/**
		*  @brief
		*    Openes a file dialog in which the user can choose a scene
		*
		*  @return
		*    The chooen scene
		*/
		PLGeneral::String ChooseScene();

		/**
		*  @brief
		*    Loads a scene
		*
		*  @param[in] sFilename
		*    Filename of the scene to load
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Similar to PLEngine::BasicSceneApplication::LoadScene, but sets the base path the scene is in, as the new current system directory
		*/
		bool LoadScene(const PLGeneral::String &sFilename);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a key is pressed down
		*
		*  @param[in] nKey
		*    Pressed key
		*  @param[in] nModifiers
		*    Modifier keys pressed
		*/
		void NotifyKeyDown(PLGeneral::uint32 nKey, PLGeneral::uint32 nModifiers);

		/**
		*  @brief
		*    Called when something was dropped down
		*
		*  @param[in] cDataObject
		*    Dropped data object
		*/
		void NotifyDrop(const PLGui::DataObject &cDataObject);


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::ConsoleApplication functions ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnInitLog();
		virtual void OnInit();


	//[-------------------------------------------------------]
	//[ Private virtual PLGui::GuiApplication functions       ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateMainWindow();


	//[-------------------------------------------------------]
	//[ Private virtual PLEngine::BasicSceneApplication functions ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateScene(PLScene::SceneContainer &cContainer);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLGeneral::uint32, PLGeneral::uint32> EventHandlerKeyDown;
		PLCore::EventHandler<const PLGui::DataObject &>			   EventHandlerDrop;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::DialogChooseFile *m_pFileDialog;					/**< File dialog, can be a null pointer */
		PLGeneral::String		 m_sCurrentSceneBaseDirectory;	/**< Base directory of the currently loaded scene */



};


#endif // __PLVIEWER_APPLICATION_H__
