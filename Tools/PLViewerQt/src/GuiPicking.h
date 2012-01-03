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
*    Picking application component
*/
class GuiPicking : public PLEngine::MousePicking {


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
		QLabel					   *m_pQLabelStatusBar;					/**< Qt label shown in the status bar of the Qt main window, can be a null pointer */


};


#endif // __PLVIEWERQT_PICKING_H__
