/*********************************************************\
 *  File: GuiPicking.h                                   *
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


#ifndef __PLVIEWERQT_PICKING_H__
#define __PLVIEWERQT_PICKING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeHandler.h>
#include <PLEngine/Picking/MousePicking.h>
#include <PLFrontendQt/DockWidget/DockWidget.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QLabel;
QT_END_NAMESPACE
class Gui;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Picking & selection application component
*
*  @note
*    - This class is also derived from "PLFrontendQt::DockWidget" to be able to spy on the dock widget communication
*/
class GuiPicking : public PLFrontendQt::DockWidget, public PLEngine::MousePicking {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, GuiPicking, "", PLFrontendQt::DockWidget, "Picking & selection application component")
		// Methods
		pl_method_0(GetSceneContainer,	pl_ret_type(PLScene::SceneContainer*),						"Returns the used scene container, can be a null pointer.",			"")
		pl_method_0(GetSelectedObject,	pl_ret_type(PLCore::Object*),								"Returns the currently selected object, can be a null pointer.",	"")
		pl_method_1(SelectObject,		pl_ret_type(void),						PLCore::Object*,	"Selects the given object. Object to select as first parameter.",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*/
		GuiPicking(Gui &cGui);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GuiPicking();

		/**
		*  @brief
		*    Performs the informativ picking
		*
		*   @remarks
		*     The purpose of this method is to provide the user with an information what's currently under the mouse
		*     cursor. So, this method should be called continually without the need to "click on the object". This
		*     method is allowed decide whether or not to internal state.
		*
		*  @return
		*    Picked scene node, can be a null pointer
		*
		*  @see
		*    - "PerformPicking()"
		*/
		PLScene::SceneNode *PerformInformativPicking();

		/**
		*  @brief
		*    Performs picking
		*
		*  @return
		*    Picked scene node, can be a null pointer
		*
		*  @note
		*    - Also updates the Qt label shown in the status bar of the Qt main window
		*/
		PLScene::SceneNode *PerformPicking();

		/**
		*  @brief
		*    Returns the used scene container
		*
		*  @return
		*    The used scene container, can be a null pointer
		*/
		PLScene::SceneContainer *GetSceneContainer() const;

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
		*    Set the text of the Qt label shown in the status bar of the Qt main window
		*
		*  @param[in] sText
		*    Text to be set
		*/
		void SetLabelStatusBarText(const PLCore::String &sText);


	//[-------------------------------------------------------]
	//[ Private virtual PLEngine::Picking functions           ]
	//[-------------------------------------------------------]
	private:
		virtual bool OnPickingCandidate(PLScene::SceneNode &cSceneNode) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Gui						   *m_pGui;								/**< Owner GUI, always valid! */
		PLCore::uint64				m_nLastPickingTime;					/**< Last picking time */
		PLScene::SceneNodeHandler	m_cCurrentPickedSceneNodeHandler;	/**< Currently picked scene node */
		PLScene::SceneNodeHandler   m_cCurrentSelectedSceneNodeHandler;	/**< Scene node handler referencing the scene node which is currently the center of the attention */
		QLabel					   *m_pQLabelStatusBar;					/**< Qt label shown in the status bar of the Qt main window, can be a null pointer */


};


#endif // __PLVIEWERQT_PICKING_H__
