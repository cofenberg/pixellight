/*********************************************************\
 *  File: DockWidgetLog.h                                *
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_LOG_H__
#define __PLFRONTENDQT_DOCKWIDGET_LOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLFrontendQt/DockWidget/DockWidget.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QMainWindow;
	class QPlainTextEdit;
QT_END_NAMESPACE


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    "PLCore::Log" Qt dock widget class
*/
class DockWidgetLog : public DockWidget {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetLog, "PLFrontendQt", PLFrontendQt::DockWidget, "\"PLCore::Log\" Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Log")
		pl_properties_end
		// Constructors
		pl_constructor_2(DefaultConstructor,	QMainWindow*,	DockWidgetManager*,	"Constructor with a pointer to the Qt main window as first parameter, pointer to the dock widget manager this dock widget should be registered to as second parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pQMainWindow
		*    Pointer to Qt main window, can be a null pointer (in this case you're responsible for destroying this instance)
		*  @param[in] pDockWidgetManager
		*    Optional pointer to the dock widget manager this dock widget should be registered to, can be a null pointer
		*/
		PLFRONTENDQT_API DockWidgetLog(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidgetLog();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Called when a new log entry had been added
		*/
		void OnNewEntry();


	//[-------------------------------------------------------]
	//[ Private PixelLight slots                              ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> SlotNewEntry;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QPlainTextEdit *m_pQPlainTextEdit;	/**< Qt plain text edit instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_LOG_H__
