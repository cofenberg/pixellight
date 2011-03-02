/*********************************************************\
 *  File: MyPicking.h                                    *
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


#ifndef __PLDEMOPICKING_MYPICKING_H__
#define __PLDEMOPICKING_MYPICKING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeHandler.h>
#include <PLEngine/Picking/MousePicking.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Application;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Picking application component
*/
class MyPicking : public PLEngine::MousePicking {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cApplication
		*    Owner application
		*/
		MyPicking(Application &cApplication);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MyPicking();

		/**
		*  @brief
		*    Performs the picking
		*/
		void PerformPicking();


	//[-------------------------------------------------------]
	//[ Private virtual PLEngine::Picking functions           ]
	//[-------------------------------------------------------]
	private:
		virtual bool OnPickingCandidate(PLScene::SceneNode &cSceneNode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Application				   *m_pApplication;						/**< Owner application, always valid! */
		PLGeneral::uint64			m_nLastPickingTime;					/**< Last picking time */
		PLScene::SceneNodeHandler	m_cCurrentPickedSceneNodeHandler;	/**< Currently picked scene node */


};


#endif // __PLDEMOPICKING_MYPICKING_H__
