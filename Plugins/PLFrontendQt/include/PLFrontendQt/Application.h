/*********************************************************\
 *  File: Application.h                                  *
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


#ifndef __PLFRONTENDQT_APPLICATION_H__
#define __PLFRONTENDQT_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QApplication>
#include <PLCore/Config/Config.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class RendererContext;
}
namespace PLFrontendQt {
	class QPLContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
* @brief
*   This is the entry point for an Qt application which uses PixelLight for Rendering
*   This class initializes the core part of PixelLight and creates an RendererContext which is used for rendering
*
*   A timer is used to update some components of PixelLight which needs continuous updates to work correctly.
*   At least the Timing component will be updated. Optional the input handling and the renderer context will be updated
*/
class PLFRONTENDQT_API Application : public QApplication {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Qt signals (MOC)                                      ]
	//[-------------------------------------------------------]
	signals:
		void AfterFrameUpdate();


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		Application(int &argc, char **argv);
		Application(int &argc, char **argv, bool GUIenabled);
		Application(int &argc, char **argv, QApplication::Type);

		// [TODO] Check this: Linux only, is this really required?
		/*
		Application(Display* dpy, Qt::HANDLE visual = 0, Qt::HANDLE cmap = 0);
		Application(Display* dpy, int& argc, char** argv, Qt::HANDLE visual = 0, Qt::HANDLE cmap = 0);
		*/

		virtual ~Application();

		/**
		*  @brief
		*    Returns the configuration instance
		*
		*  @return
		*    The configuration instance
		*/
		PLCore::Config &GetConfig();

		/**
		*  @brief
		*    Adds a base directory to PixelLight
		*/
		void AddBasePath(const QString &path);

		/**
		*  @brief
		*    Removes a base directory from PixelLight
		*/
		void RemoveBasePath(const QString &path);

		/**
		*  @brief
		*    Returns the RendererContext, can be null
		*/
		PLRenderer::RendererContext* GetRendererContext();

		/**
		*  @brief
		*    Enables/Disables updating the input handling of PixelLight via the update timer
		*
		*  @param[in] enabled
		*    indicates if the input handling should be updated via the update timer
		*/
		void EnableInputUpdates(bool enabled)
		{
			m_doInputUpdates = enabled;
		}

		/**
		*  @brief
		*    Returns if the input handling is updated via the update timer
		*
		*  @return
		*    true: input handling is updated via the update timer
		*    false: no updates to the input handling is done
		*/
		bool IsInputUpdateEnabled()
		{
			return m_doInputUpdates;
		}

		/**
		*  @brief
		*    Enables/Disables updating the renderer context of PixelLight via the update timer
		*
		*  @param[in] enabled
		*    indicates if the renderer context should be updated via the update timer
		*/
		void EnableRendererContextUpdates(bool enabled)
		{
			m_doRendererContextUpdates = enabled;
		}

		void SetContextForUpdate(QPLContext *context);

		void DoInpuUpdate();

		/**
		*  @brief
		*    Returns if the renderer context is updated via the update timer
		*
		*  @return
		*    true: renderer context is updated via the update timer
		*    false: no updates to the renderer context is done
		*/
		bool IsRendererContextEnabled()
		{
			return m_doRendererContextUpdates;
		}

		/**
		*  @brief
		*    Sets the update interval in which the Timing and optional the input handling and renderer context components of PixelLight gets Updated
		*
		* @param[in] msec
		*   update interval in milliseconds.
		*   A value of -1 disables the update completely
		*   A value of 0 will create an update timer which will fire every time when no none system events needs to be processed.
		*   Note:
		*           If the interval is set to zero then the CPU usage (one core) of the application will go virtually to nearly 100%. Because this is similar to an endless loop.
		*/
		void SetUpdateInterval(int msec);

		/**
		*  @brief
		*    Returns the current used update interval
		*
		*  @return
		*    Update interval in milliseconds
		*/
		int GetUpdateInterval()
		{
			return m_updateInterval;
		}

		/**
		*  @brief
		*    Returns if the used renderer by the renderer context support shader
		*
		*  @return
		*    true, when shader are supported by the renderer, otherwise false
		*/
		bool AreShaderSupported();


	//[-------------------------------------------------------]
	//[ Protected virtual QObject functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void timerEvent(QTimerEvent *pQTimerEvent) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void Init();

		/**
		*  @brief
		*    Destroys the renderer context
		*/
		void DestroyRenderContext();

		/**
		*  @brief
		*    Creates an renderer context with the given renderer
		*
		*  @param[in] sRendererName
		*    Name of the Renderer to be used
		*/
		void CreateRenderContext(const PLCore::String &sRendererName = "PLRendererOpenGL::Renderer");


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void OnBeginContextChange();
		void OnEndContextChange();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Config				 m_cConfig;		/**< Configuration instance */
		PLRenderer::RendererContext	*m_pRendererContext;
		int							 m_TimerId;
		bool						 m_doInputUpdates;
		bool						 m_doRendererContextUpdates;
		int							 m_updateInterval;
		bool						 m_suspendRendererContextUpdates;
		QPLContext					*m_pContext;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


//This redefines qApp, causing it to return an Application pointer instead of a QApplication one.
//This is useful, for example, to access the logging system. This is done in the same way that
//Qt does it to get a QApplication rather than a QCoreApplication, so it should be legitimate.
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<PLFrontendQt::Application *>(QCoreApplication::instance()))


#endif // __PLFRONTENDQT_APPLICATION_H__
