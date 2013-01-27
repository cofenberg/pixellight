/*********************************************************\
 *  File: DockWidgetObject.h                             *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLFRONTENDQT_DOCKWIDGET_OBJECT_H__
#define __PLFRONTENDQT_DOCKWIDGET_OBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidget.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QTreeView;
	class QMainWindow;
QT_END_NAMESPACE
namespace PLFrontendQt {
	namespace DataModels {
		class PLIntrospectionModel;
	}
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
*    "PLCore::Object" Qt dock widget class
*/
class DockWidgetObject : public DockWidget {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetObject, "PLFrontendQt", PLFrontendQt::DockWidget, "\"PLCore::Object\" Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Object")
		pl_properties_end
		#ifdef PLFRONTENDQT_EXPORTS	// The following is only required when compiling PLFrontendQt
			// Methods
			pl_method_0(GetSelectedObject,	pl_ret_type(PLCore::Object*),						"Returns the currently selected object, can be a null pointer.",	"")
			pl_method_1(SelectObject,		pl_ret_type(void),				PLCore::Object*,	"Selects the given object. Object to select as first parameter.",	"")
		#endif
		// Constructors
		pl_constructor_2(DefaultConstructor,	QMainWindow*,	DockWidgetManager*,	"Constructor with a pointer to the Qt main window as first parameter, pointer to the dock widget manager this dock widget should be registered to as second parameter",	"")
		// Slots
		pl_slot_0(OnDestroyed,	"Called when the object assigned with this dock widget was destroyed",	"")
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
		PLFRONTENDQT_API DockWidgetObject(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidgetObject();

		/**
		*  @brief
		*    Returns the currently selected object
		*
		*  @return
		*    The currently selected object, can be a null pointer
		*/
		PLFRONTENDQT_API PLCore::Object *GetSelectedObject() const;

		/**
		*  @brief
		*    Selects the given object
		*
		*  @param[in] pObject
		*    Object to select, can be a null pointer
		*/
		PLFRONTENDQT_API void SelectObject(PLCore::Object *pObject);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the object assigned with this dock widget was destroyed
		*/
		void OnDestroyed();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QTreeView						 *m_pQTreeView;				/**< Qt tree view instance, can be a null pointer */
		DataModels::PLIntrospectionModel *m_pPLIntrospectionModel;	/**< PL introspection model, can be a null pointer */
		PLCore::Object					 *m_pObject;				/**< Object assigned with this dock widget, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_OBJECT_H__
