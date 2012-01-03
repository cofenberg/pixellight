/*********************************************************\
 *  File: DockWidgetManager.h                            *
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


#ifndef __PLFRONTENDQT_DOCKWIDGETMANAGER_H__
#define __PLFRONTENDQT_DOCKWIDGETMANAGER_H__
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
class QMainWindow;
QT_END_NAMESPACE
namespace PLFrontendQt {
	class DockWidget;
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
*    PixelLight RTTI dock widget manager
*
*  @note
*    - Loosely couples together RTTI dock widgets, the RTTI dock widgets can still be destroyed individually (e.g. when the Qt dock widget is destroyed)
*/
class DockWidgetManager : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidget;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetManager, "PLFrontendQt", PLCore::Object, "PixelLight RTTI dock widget manager")
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
		*    Pointer to Qt main window, can be a null pointer
		*
		*  @note
		*    - You're responsible for destroying this PixelLight RTTI dock widget manager instance
		*/
		PLFRONTENDQT_API DockWidgetManager(QMainWindow *pQMainWindow);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidgetManager();

		/**
		*  @brief
		*    Shows a dock widget
		*
		*  @param[in] sClassName
		*    Class name of the PixelLight RTTI class encapsulating a Qt dock widget (must be derived from "PLFrontendQt::DockWidget")
		*
		*  @return
		*    The shown dock widget, can be a null pointer (you don't need to care about destroying the dock widget instance)
		*
		*  @note
		*    - If there's already a shown dock widget of the given class name, it will get the focus
		*    - If there's already a dock widget of the given class name, it will be shown
		*    - If there's currently no dock widget of the given class name, it will be instanced and shown
		*/
		PLFRONTENDQT_API DockWidget *ShowDockWidget(const PLCore::String &sClassName);

		/**
		*  @brief
		*    Returns the first dock widget instance which is an instance of the given class
		*
		*  @param[in] sClassName
		*    Class name of the PixelLight RTTI class encapsulating a Qt dock widget (must be derived from "PLFrontendQt::DockWidget")
		*
		*  @return
		*    The first dock widget instance which is an instance of the given class, can be a null pointer
		*/
		PLFRONTENDQT_API DockWidget *GetFirstDockWidget(const PLCore::String &sClassName);

		/**
		*  @brief
		*    Hides all registered dock widgets
		*/
		PLFRONTENDQT_API void HideDockWidgets();

		/**
		*  @brief
		*    Destroys all registered dock widgets
		*/
		PLFRONTENDQT_API void DestroyDockWidgets();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Registers the given dock widget within this dock widget manager
		*
		*  @param[in] cDockWidget
		*    Dock widget to register
		*/
		inline void RegisterDockWidget(DockWidget &cDockWidget);

		/**
		*  @brief
		*    Unregisters the given dock widget within this dock widget manager
		*
		*  @param[in] cDockWidget
		*    Dock widget to unregister
		*/
		inline void UnregisterDockWidget(DockWidget &cDockWidget);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QMainWindow				   *m_pQMainWindow;		/**< Pointer to Qt main window, can be a null pointer */
		PLCore::Array<DockWidget*>  m_lstDockWidgets;	/**< List of registered dock widgets */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidgetManager.inl"


#endif // __PLFRONTENDQT_DOCKWIDGETMANAGER_H__
