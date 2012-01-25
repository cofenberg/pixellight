/*********************************************************\
 *  File: DockWidgetSceneGraph.h                         *
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_SCENEGRAPH_H__
#define __PLFRONTENDQT_DOCKWIDGET_SCENEGRAPH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidgetScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QMainWindow;
QT_END_NAMESPACE
namespace PLScene {
	class SceneNode;
	class SceneContainer;
}
namespace PLFrontendQt {
	namespace DataModels {
		class SceneGraphTreeModel;
		class TreeSortAndFilterProxyModel;
	}
	class DockWidgetSceneGraphQObject;
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
*    Scene graph Qt dock widget class
*/
class DockWidgetSceneGraph : public DockWidgetScene {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidgetSceneGraphQObject;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetSceneGraph, "PLFrontendQt", PLFrontendQt::DockWidgetScene, "Scene graph Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Scene Graph")
		pl_properties_end
		#ifdef PLFRONTENDQT_EXPORTS	// The following is only required when compiling PLFrontendQt
			// Methods
			pl_method_0(GetSceneContainer,	pl_ret_type(PLScene::SceneContainer*),								"Returns the used scene container, can be a null pointer.",						"")
			pl_method_1(SetSceneContainer,	pl_ret_type(void),						PLScene::SceneContainer*,	"Sets the scene container to use. Scene container to use as first parameter.",	"")
			pl_method_0(GetSelectedObject,	pl_ret_type(PLCore::Object*),										"Returns the currently selected object, can be a null pointer.",				"")
			pl_method_1(SelectObject,		pl_ret_type(void),						PLCore::Object*,			"Selects the given object. Object to select as first parameter.",				"")
		#endif
		// Constructors
		pl_constructor_2(DefaultConstructor,	QMainWindow*,	DockWidgetManager*,	"Constructor with a pointer to the Qt main window as first parameter, pointer to the dock widget manager this dock widget should be registered to as second parameter",	"")
		// Slots
		pl_slot_0(OnDestroy,	"Called when the scene container assigned with this dock widget was destroyed",	"")
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
		PLFRONTENDQT_API DockWidgetSceneGraph(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidgetSceneGraph();

		/**
		*  @brief
		*    Returns the used scene container
		*
		*  @return
		*    The used scene container, can be a null pointer
		*/
		PLFRONTENDQT_API PLScene::SceneContainer *GetSceneContainer() const;

		/**
		*  @brief
		*    Sets the scene container to use
		*
		*  @param[in] pSceneContainer
		*    Scene container to use, can be a null pointer
		*/
		PLFRONTENDQT_API void SetSceneContainer(PLScene::SceneContainer *pSceneContainer);

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
		*    Sets the used scene container and object
		*/
		void SetSceneContainerAndObject();

		/**
		*  @brief
		*    Called when the scene container assigned with this dock widget was destroyed
		*/
		void OnDestroy();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DataModels::SceneGraphTreeModel 		*m_pSceneGraphTreeModel;			/**< Scene graph tree model, can be a null pointer */
		PLScene::SceneContainer					*m_pSceneContainer;					/**< Scene container assigned with this dock widget, can be a null pointer */
		DockWidgetSceneGraphQObject				*m_pDockWidgetSceneGraphQObject;	/**< QObject instance for Qt's signal/slot mechanisms, always valid */
		DataModels::TreeSortAndFilterProxyModel	*m_pSortAndFilterModel;				/**< sort and filter model, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_SCENEGRAPH_H__
