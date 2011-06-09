/*********************************************************\
 *  File: MousePicking.h                                 *
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
namespace PLMath {
	class Vector2i;
}
namespace PLGui {
	class Widget;
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
		*  @param[in] pWidget
		*    Widget to perform the picking in, if a null pointer no picking is possible
		*  @param[in] pCamera
		*    Camera to perform the picking with, if a null pointer no picking is possible
		*/
		PL_API MousePicking(PLGui::Widget *pWidget = nullptr, PLScene::SNCamera *pCamera = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~MousePicking();

		/**
		*  @brief
		*    Returns the widget to perform the picking in
		*
		*  @return
		*    The widget to perform the picking in, a null pointer if there's no widget (= no picking is possible)
		*/
		PL_API PLGui::Widget *GetWidget() const;

		/**
		*  @brief
		*    Sets the widget to perform the picking in
		*
		*  @param[in] pWidget
		*    The widget to perform the picking in, a null pointer if there's no widget (= no picking is possible)
		*/
		PL_API void SetWidget(PLGui::Widget *pWidget);

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
		*
		*  @return
		*    'true' if anything has been picked, else 'false'
		*
		*  @note
		*    - For performance reasons we recommend to always set a maximum picking distance
		*    - The function will only work if a widget and camera is set ('SetWidget()' and 'GetCamera()')
		*/
		PL_API bool PerformMousePicking(PickingResult &cPickingResult, float fMaxDistance = -1.0f);

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
		*
		*  @return
		*    'true' if anything has been picked, else 'false'
		*
		*  @note
		*    - For performance reasons we recommend to always set a maximum picking distance
		*    - The function will only work if a widget and camera is set ('SetWidget()' and 'GetCamera()')
		*/
		PL_API bool PerformMousePicking(PickingResult &cPickingResult, const PLMath::Vector2i &vMousePos, float fMaxDistance = -1.0f);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a widget was destroyed
		*/
		void OnWidgetDestroy();

		/**
		*  @brief
		*    Called when a camera was destroyed
		*/
		void OnCameraDestroy();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerWidgetDestroy;
		PLCore::EventHandler<> EventHandlerCameraDestroy;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Widget	  *m_pWidget;	/**< Widget to perform the picking in, can be a null pointer */
		PLScene::SNCamera *m_pCamera;	/**< Camera to perform the picking with, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_MOUSEPICKING_H__
