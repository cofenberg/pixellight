/*********************************************************\
 *  File: DockWidget.h                                   *
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_H__
#define __PLFRONTENDQT_DOCKWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
class QWidget;
class QDockWidget;
QT_END_NAMESPACE
namespace PLFrontendQt {
	class InternalQDockWidget;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract PixelLight RTTI class encapsulating a Qt dock widget
*
*  @remarks
*  @verbatim
*    Usage example:
*        "
*        const PLCore::Class *pClass = PLCore::ClassManager::GetInstance()->GetClass("PLFrontendQt::DockWidgetSceneGraph");
*        if (pClass)
*            pClass->Create(PLCore::Params<PLCore::Object*, QWidget*>(pQtMainWindow)));
*        "
*    The destruction of the created RTTI class instance is automatically handled by the Qt main window, see notes below.
*  @endverbatim
*
*    Each RTTI dock widget should have the following properties:
*    - "Title": Human readable title, may be shown e.g. within a menu and is used by default as the encapsulated Qt dock widget title
*
*  @note
*    - When a RTTI dock widget is instanced, it automatically creates the Qt dock widget it's encapsulating, access it by using "GetQDockWidget()"
*    - Derived RTTI dock widgets must implement a decent default behaviour to make it possible to use them out-of-the-box
*    - When a RTTI dock widget instance gets destroyed, it automatically destroys the Qt dock widget it's encapsulating
*    - When the encapsulated Qt dock widget gets destroyed, it automatically destroys the encapsulating RTTI dock widget
*    - This behaviour results in a Qt similar behaviour, when a RTTI dock widget is instanced it's parent takes over the control
*    - By convention, one should only derive new RTTI dock widgets from abstract RTTI dock widgets
*/
class DockWidget : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class InternalQDockWidget;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidget, "PLFrontendQt", PLCore::Object, "Abstract PixelLight RTTI class encapsulating a Qt dock widget")
		// Properties
		pl_properties
			pl_property("Title", "")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the encapsulated Qt dock widget
		*
		*  @return
		*    The encapsulated Qt dock widget, can be a null pointer
		*/
		PLFRONTENDQT_API QDockWidget *GetQDockWidget() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pQWidgetParent
		*    Pointer to parent Qt widget as parameter, can be a null pointer (in this case you're responsible for destroying this instance)
		*/
		PLFRONTENDQT_API DockWidget(QWidget *pQWidgetParent);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidget();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		InternalQDockWidget	*m_pQDockWidget;	/**< Qt dock widget, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_H__
