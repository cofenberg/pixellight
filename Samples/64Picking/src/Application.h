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


#ifndef __PLSAMPLE_64_APPLICATION_H__
#define __PLSAMPLE_64_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLEngine/Application/BasicSceneApplication.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class MyPicking;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*/
class Application : public PLEngine::BasicSceneApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Application, "", PLEngine::BasicSceneApplication, "Application class")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Slots
		pl_slot_2(OnKeyDown,	PLCore::uint32,	PLCore::uint32,	"Called when a key is pressed down. pressed key as first parameter and modifier keys pressed as second parameter",	"")
	pl_class_end


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
	//[ Public virtual PLEngine::BasicSceneApplication functions ]
	//[-------------------------------------------------------]
	public:
		virtual void SetCamera(PLScene::SNCamera *pCamera) override;


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
		void OnKeyDown(PLCore::uint32 nKey, PLCore::uint32 nModifiers);


	//[-------------------------------------------------------]
	//[ Private virtual PLGui::GuiApplication functions       ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateMainWindow() override;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::RenderApplication functions ]
	//[-------------------------------------------------------]
	private:
		virtual bool OnUpdate() override;


	//[-------------------------------------------------------]
	//[ Private virtual PLEngine::BasicSceneApplication functions ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateScene(PLScene::SceneContainer &cContainer) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		MyPicking *m_pMyPicking;	/**< Picking application component, can be a null pointer */


};


#endif // __PLSAMPLE_64_APPLICATION_H__
