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


#ifndef __PLQT_APPLICATION_H__
#define __PLQT_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/QApplication>
#include <PLCore/Config/Config.h>
#include "PLQt/PLQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class RendererContext;
}
namespace PLQt {
	class QPLContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
* @brief
*   This is the entry point for an Qt application which uses PixelLight for Rendering
*   This class initializes the core part of PixelLight and creates an RendererContext which is used for rendering
*
*   A timer is used to update some components of PixelLight which needs continouse updates to work correctly.
*   At least the Timing component will be updated. Optional the input handling and the renderer context will be updated
*/
class PLQT_API Application : public QApplication {


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
		*    Sets the update inverval in which the Timing and optional the input handling and renderer context components of PixelLight gets Updated
		*
		* @param[in] msec
		*   update interval in miliseconds.
		*   A value of 0 will create an update timer which will fire everytime when no nore system events needs to be processed.
		*   Note:
		*           If the interval is set to zero then the cpu usage (one core) of the application will go virtually to nearly 100%. Because this is similar to an endless loop.
		*/
		void SetUpdateInterval(int msec);

		/**
		*  @brief
		*    Returns the current used update interval
		*
		*  @return
		*    Update interval in miliseconds
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
		*    Initializes the core of PL
		*
		*  @param[in] useRuntimeDir
		*    indicates if the runtime dir should be used (e.g. given by the PL_RUNTIME env var)
		*/
		void InitCore(bool useRuntimeDir);

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

		/**
		*  @brief
		*    Scan an directory for archives which gets added as base paths
		*
		*  @param[in] sDirectory
		*    path of the directory to be scanned
		*  @param[in] sExtension
		*    extension of the archive to be used (default .zip)
		*/
		bool ScanFSArchives(const PLCore::String &sDirectory, const PLCore::String &sExtension = "*.zip");


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
} // PLQt


//This redefines qApp, causing it to return an Application pointer instead of a QApplication one.
//This is useful, for example, to access the logging system. This is done in the same way that
//Qt does it to get a QApplication rather than a QCoreApplication, so it should be legitimate.
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<PLQt::Application *>(QCoreApplication::instance()))


#endif // __PLQT_APPLICATION_H__
