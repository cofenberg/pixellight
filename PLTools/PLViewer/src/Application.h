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
#include <PLEngine/Application/ScriptApplication.h>


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
class Application : public PLEngine::ScriptApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Application, "", PLEngine::ScriptApplication, "Application class")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Slots
		pl_slot_2(OnKeyDown,	PLGeneral::uint32,			PLGeneral::uint32,	"Called when a key is pressed down. pressed key as first parameter and modifier keys pressed as second parameter",	"")
		pl_slot_1(OnDrop,		const PLGui::DataObject&,						"Called when something was dropped down, dropped data object as first parameter",									"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLGeneral::String DefaultFilename;	/**< The used default resource loaded at start, if empty a file dialog will appear */


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
		*    Openes a file dialog in which the user can choose a resource
		*
		*  @return
		*    The chooen resource
		*/
		PLGeneral::String ChooseFilename();

		/**
		*  @brief
		*    Loads a resource
		*
		*  @param[in] sFilename
		*    Filename of the resource to load
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadResource(const PLGeneral::String &sFilename);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
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

		/**
		*  @brief
		*    Called when a key is pressed down
		*
		*  @param[in] nKey
		*    Pressed key
		*  @param[in] nModifiers
		*    Modifier keys pressed
		*/
		void OnKeyDown(PLGeneral::uint32 nKey, PLGeneral::uint32 nModifiers);

		/**
		*  @brief
		*    Called when something was dropped down
		*
		*  @param[in] cDataObject
		*    Dropped data object
		*/
		void OnDrop(const PLGui::DataObject &cDataObject);


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ConsoleApplication functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnInitLog();
		virtual void OnInit();


	//[-------------------------------------------------------]
	//[ Private virtual PLGui::GuiApplication functions       ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateMainWindow();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::DialogChooseFile *m_pFileDialog;	/**< File dialog, can be a null pointer */


};


#endif // __PLVIEWER_APPLICATION_H__
