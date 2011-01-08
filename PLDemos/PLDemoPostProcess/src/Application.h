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


#ifndef __PLDEMOPOSTPROCESS_APPLICATION_H__
#define __PLDEMOPOSTPROCESS_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLEngine/Application/BasicSceneApplication.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*/
class Application : public PLEngine::BasicSceneApplication {


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32					  m_nCurrentSelectedModifier;	/**< Current selected modifier */
		PLGeneral::List<const PLCore::Class*> m_lstModifierClasses;			/**< Class list of all available post process scene node modifiers */


};


#endif // __PLDEMOPOSTPROCESS_APPLICATION_H__
