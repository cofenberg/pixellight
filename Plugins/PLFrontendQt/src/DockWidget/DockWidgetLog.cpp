/*********************************************************\
 *  File: DockWidgetLog.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/qdockwidget.h>
#include <QtGui/qmainwindow.h>
#include <QtGui/qplaintextedit.h>
#include <PLCore/Log/Log.h>
#include <PLCore/Base/Class.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DockWidget/DockWidgetLog.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetLog)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetLog::DockWidgetLog(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager) : DockWidget(pQMainWindow, pDockWidgetManager),
	SlotNewEntry(&DockWidgetLog::OnNewEntry, this),
	m_pQPlainTextEdit(nullptr)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Get the log instance
		Log *pLog = Log::GetInstance();

		// Create Qt plain text edit instance
		m_pQPlainTextEdit = new QPlainTextEdit();
		m_pQPlainTextEdit->setReadOnly(true);
		m_pQPlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
		m_pQPlainTextEdit->document()->setMaximumBlockCount(pLog->GetBufferCount());
		pQDockWidget->setWidget(m_pQPlainTextEdit);

		{ // Append the last log messages
			Iterator<String> cIterator = pLog->GetLastMessages().GetIterator();
			while (cIterator.HasNext())
				m_pQPlainTextEdit->appendPlainText(QtStringAdapter::PLToQt(cIterator.Next()));
		}

		// Set window title
		pQDockWidget->setWindowTitle(pQDockWidget->tr(GetClass()->GetProperties().Get("Title")));

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::BottomDockWidgetArea, pQDockWidget);

		// Connect event handler
		pLog->EventNewEntry.Connect(SlotNewEntry);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetLog::~DockWidgetLog()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a new log entry had been added
*/
void DockWidgetLog::OnNewEntry()
{
	// Append the latest log message
	const Queue<String> &qLastMessages = Log::GetInstance()->GetLastMessages();
	if (qLastMessages.GetNumOfElements())
		m_pQPlainTextEdit->appendPlainText(QtStringAdapter::PLToQt(qLastMessages.Top()));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
