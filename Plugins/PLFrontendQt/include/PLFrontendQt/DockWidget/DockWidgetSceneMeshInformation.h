/*********************************************************\
 *  File: DockWidgetSceneMeshInformation.h               *
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_SCENEMESHINFORMATION_H__
#define __PLFRONTENDQT_DOCKWIDGET_SCENEMESHINFORMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidgetScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QTableView;
	class QMainWindow;
	class QStandardItemModel;
QT_END_NAMESPACE
namespace PLRenderer {
	class IndexBuffer;
	class VertexBuffer;
}
namespace PLMesh {
	class Mesh;
	class MeshLODLevel;
	class MeshMorphTarget;
}
namespace PLScene {
	class SceneNode;
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
*    Mesh information Qt dock widget class
*/
class DockWidgetSceneMeshInformation : public DockWidgetScene {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetSceneMeshInformation, "PLFrontendQt", PLFrontendQt::DockWidgetScene, "Mesh information Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Mesh Information")
		pl_properties_end
		#ifdef PLFRONTENDQT_EXPORTS	// The following is only required when compiling PLFrontendQt
			// Methods
			pl_method_0(GetSelectedObject,	pl_ret_type(PLCore::Object*),						"Returns the currently selected object, can be a null pointer.",	"")
			pl_method_1(SelectObject,		pl_ret_type(void),				PLCore::Object*,	"Selects the given object. Object to select as first parameter.",	"")
		#endif
		// Constructors
		pl_constructor_2(DefaultConstructor,	QMainWindow*,	PLFrontendQt::DockWidgetManager*,	"Constructor with a pointer to the Qt main window as first parameter, pointer to the dock widget manager this dock widget should be registered to as second parameter",	"")
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
		DockWidgetSceneMeshInformation(QMainWindow *pQMainWindow, PLFrontendQt::DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DockWidgetSceneMeshInformation();

		/**
		*  @brief
		*    Returns the currently selected object
		*
		*  @return
		*    The currently selected object, can be a null pointer
		*/
		PLCore::Object *GetSelectedObject() const;

		/**
		*  @brief
		*    Selects the given object
		*
		*  @param[in] pObject
		*    Object to select, can be a null pointer
		*/
		void SelectObject(PLCore::Object *pObject);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the object assigned with this dock widget was destroyed
		*/
		void OnDestroyed();

		/**
		*  @brief
		*    Updates the mesh information
		*
		*  @param[in] pObject
		*    Selected object can be a null pointer
		*/
		void UpdateObject(PLCore::Object *pObject);

		/**
		*  @brief
		*    Fills the given Qt standard item model
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cSceneNode
		*    Currently selected scene node
		*/
		void FillStandardItemModel(QStandardItemModel &cQStandardItemModel, PLScene::SceneNode &cSceneNode) const;

		/**
		*  @brief
		*    Fills the given Qt standard item model, mesh part
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cMesh
		*    Currently selected mesh
		*/
		void FillStandardItemModelMesh(QStandardItemModel &cQStandardItemModel, PLMesh::Mesh &cMesh) const;

		/**
		*  @brief
		*    Fills the given Qt standard item model, mesh morph target part
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cMeshMorphTarget
		*    Current morph target of the selected mesh
		*/
		void FillStandardItemModelMeshMorphTarget(QStandardItemModel &cQStandardItemModel, PLMesh::MeshMorphTarget &cMeshMorphTarget) const;

		/**
		*  @brief
		*    Fills the given Qt standard item model, vertex buffer part
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cVertexBuffer
		*    Currently used vertex buffer
		*/
		void FillStandardItemModelVertexBuffer(QStandardItemModel &cQStandardItemModel, PLRenderer::VertexBuffer &cVertexBuffer) const;

		/**
		*  @brief
		*    Fills the given Qt standard item model, mesh LOD level part
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cMeshLODLevel
		*    Current mesh LOD level of the selected mesh
		*/
		void FillStandardItemModelMeshLODLevel(QStandardItemModel &cQStandardItemModel, PLMesh::MeshLODLevel &cMeshLODLevel) const;

		/**
		*  @brief
		*    Fills the given Qt standard item model, index buffer part
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cIndexBuffer
		*    Currently used index buffer
		*/
		void FillStandardItemModelIndexBuffer(QStandardItemModel &cQStandardItemModel, PLRenderer::IndexBuffer &cIndexBuffer) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Object *m_pObject;		/**< Object assigned with this dock widget, can be a null pointer */
		QTableView	   *m_pQTableView;	/**< Qt table view instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_SCENEMESHINFORMATION_H__
