/*********************************************************\
 *  File: MousePicking.h                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLENGINE_MOUSEPICKING_H__
#define __PLENGINE_MOUSEPICKING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/Picking/Picking.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Frontend;
}
namespace PLMath {
	class Vector2i;
}
namespace PLScene {
	class SNCamera;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class offering scene picking functionality by using the mouse
*/
class MousePicking : public Picking {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFrontend
		*    Frontend instance used to determine the mouse position
		*  @param[in] pCamera
		*    Camera to perform the picking with, if a null pointer no picking is possible
		*/
		PL_API MousePicking(PLCore::Frontend &cFrontend, PLScene::SNCamera *pCamera = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~MousePicking();

		/**
		*  @brief
		*    Returns the frontend instance used to determine the mouse position
		*
		*  @return
		*    The frontend instance used to determine the mouse position
		*/
		PL_API PLCore::Frontend &GetFrontend() const;

		/**
		*  @brief
		*    Returns the camera to perform the picking with
		*
		*  @return
		*    The camera to perform the picking with, if a null pointer no picking is possible
		*/
		PL_API PLScene::SNCamera *GetCamera() const;

		/**
		*  @brief
		*    Sets the camera to perform the picking with
		*
		*  @param[in] pCamera
		*    The camera to perform the picking with, if a null pointer no picking is possible
		*/
		PL_API void SetCamera(PLScene::SNCamera *pCamera);

		/**
		*  @brief
		*    Performs picking by using the current camera and current mouse position within the widget
		*
		*  @param[out] cPickingResult
		*    Receives the picking result if all went fine
		*  @param[in]  fMaxDistance
		*    Maximum picking distance, if negative there's no maximum picking distance (in the same scene container the camera is in)
		*  @param[in]  nCull
		*    Cull mode (see "PLRenderer::Cull")
		*
		*  @return
		*    'true' if anything has been picked, else 'false'
		*
		*  @note
		*    - For performance reasons we recommend to always set a maximum picking distance
		*    - The function will only work if a widget and camera is set ('SetWidget()' and 'GetCamera()')
		*/
		PL_API bool PerformMousePicking(PickingResult &cPickingResult, float fMaxDistance = -1.0f, PLRenderer::Cull::Enum nCull = PLRenderer::Cull::CCW);

		/**
		*  @brief
		*    Performs picking by using the current camera and the given mouse position
		*
		*  @param[out] cPickingResult
		*    Receives the picking result if all went fine
		*  @param[in]  vMousePos
		*    Position of the mouse inside the widget the picking takes place
		*  @param[in]  fMaxDistance
		*    Maximum picking distance, if negative there's no maximum picking distance (in the same scene container the camera is in)
		*  @param[in]  nCull
		*    Cull mode (see "PLRenderer::Cull")
		*
		*  @return
		*    'true' if anything has been picked, else 'false'
		*
		*  @note
		*    - For performance reasons we recommend to always set a maximum picking distance
		*    - The function will only work if a widget and camera is set ('SetWidget()' and 'GetCamera()')
		*/
		PL_API bool PerformMousePicking(PickingResult &cPickingResult, const PLMath::Vector2i &vMousePos, float fMaxDistance = -1.0f, PLRenderer::Cull::Enum nCull = PLRenderer::Cull::CCW);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a camera was destroyed
		*/
		void OnCameraDestroy();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerCameraDestroy;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Frontend  *m_pFrontend;	/**< Frontend instance used to determine the mouse position, always valid! */
		PLScene::SNCamera *m_pCamera;	/**< Camera to perform the picking with, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_MOUSEPICKING_H__
