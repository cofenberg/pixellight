/*/*********************************************************\
 *  File: MyRenderWindow.h                                 *
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


#ifndef __PLSAMPLE_82_QTINPUTHANDLING_MYRENDERWINDOW_H__
#define __PLSAMPLE_82_QTINPUTHANDLING_MYRENDERWINDOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLFrontendQt/QPLRenderWindow.h>
#include <PLInput/Input/Virtual/VirtualStandardController.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SceneNode;
}
namespace PLFrontendQt {
	class QPLSceneContext;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Render window
*/
class MyRenderWindow : public PLFrontendQt::QPLRenderWindow {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cContext
		*    Scene context this window is using
		*  @param[in] sCameraNodeName
		*    Name of the camera scene node assigned to this window
		*  @param[in] pDisplayMode
		*    Display mode information, can be a null pointer
		*  @param[in] pParent
		*    Parent window, can be a null pointer
		*/
		MyRenderWindow(PLFrontendQt::QPLSceneContext &cContext, const QString &sCameraNodeName, const PLRenderer::DisplayMode *pDisplayMode = nullptr, QWidget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MyRenderWindow();


	//[-------------------------------------------------------]
	//[ Protected virtual QWidget functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void mousePressEvent(QMouseEvent *pQMouseEvent) override;
		virtual void mouseReleaseEvent(QMouseEvent *pQMouseEvent) override;
		virtual void mouseMoveEvent(QMouseEvent *pQMouseEvent) override;
		virtual void keyPressEvent(QKeyEvent *pQKeyEvent) override;
		virtual void keyReleaseEvent(QKeyEvent *pQKeyEvent) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void UpdateInputAndSceneContext();
		void HandleKeyboardEvents(QKeyEvent *pQKeyEvent, bool bPressed);
		void HandleMousePressReleaseEvents(QMouseEvent *pQMouseEvent, bool bPressed);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLInput::VirtualStandardController	 m_cVirtualStandardController;	/**< Virtual standard controller instance */
		QPointF								 m_vPreviousMousePosition;		/**< Previous mouse position */
		PLScene::SceneNode					*m_pSceneNode;					/**< Camera scene node assigned to this window, can be a null pointer */


};


#endif // __PLSAMPLE_82_QTINPUTHANDLING_MYRENDERWINDOW_H__
