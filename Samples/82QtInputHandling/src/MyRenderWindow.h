/*/*********************************************************\
 *  File: MyRenderWindow.h                                 *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
