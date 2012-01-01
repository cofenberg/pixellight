/*********************************************************\
 *  File: DockWidget.cpp                                 *
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
#include "PLFrontendQt/DockWidget/DockWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidget)


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Simple helper class to inform the RTTI dock widget when the Qt dock widget gets destroyed
*/
class InternalQDockWidget : public QDockWidget {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cDockWidget
		*    RTTI dock widget we need to inform when we get destroyed
		*  @param[in] pQWidgetParent
		*    Pointer to parent Qt widget as parameter, can be a null pointer
		*/
		InternalQDockWidget(DockWidget &cDockWidget, QWidget *pQWidgetParent) : QDockWidget(pQWidgetParent),
			m_pDockWidget(&cDockWidget)
		{
			// Delete the dock widget instead of hiding it when someone is closing it
			setAttribute(Qt::WA_DeleteOnClose);
		}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~InternalQDockWidget()
		{
			// Inform the RTTI dock widget politely that we're now dead, then shoot at it...
			m_pDockWidget->m_pQDockWidget = nullptr;
			delete m_pDockWidget;
		}


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DockWidget *m_pDockWidget;	/**< RTTI dock widget we need to inform when we get destroyed, always valid */


};


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the encapsulated Qt dock widget
*/
QDockWidget *DockWidget::GetQDockWidget() const
{
	return m_pQDockWidget;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidget::DockWidget(QWidget *pQWidgetParent) :
	m_pQDockWidget(new InternalQDockWidget(*this, pQWidgetParent))
{
}

/**
*  @brief
*    Destructor
*/
DockWidget::~DockWidget()
{
	// Destroy the encapsulated Qt dock widget, if it still exists
	if (m_pQDockWidget)
		delete m_pQDockWidget;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
