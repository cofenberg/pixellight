/*********************************************************\
 *  File: SNGui.h                                        *
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


#ifndef __PLSCENE_SCENENODE_GUI_H__
#define __PLSCENE_SCENENODE_GUI_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Gui;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GUI scene node
*
*  @note
*    - Should be used within a scene root container only
*/
class SNGui : public SceneNode {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNGui, "PLScene", PLScene::SceneNode, "GUI scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNGui();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNGui();

		/**
		*  @brief
		*    Returns the GUI
		*
		*  @return
		*    GUI, a null pointer on error
		*/
		PLS_API PLGui::Gui *GetGui() const;

		/**
		*  @brief
		*    Returns whether this GUI has the focus or not
		*
		*  @return
		*    'true' if this GUI has the focus, else 'false'
		*/
		PLS_API bool HasFocus() const;

		/**
		*  @brief
		*    Sets whether this GUI has the focus or not
		*
		*  @param[in] bFocus
		*    'true' if this GUI has the focus, else 'false'
		*/
		PLS_API void SetFocus(bool bFocus = true);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Gui *m_pGui;
		bool		m_bFocus;


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawPost(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


	//[-------------------------------------------------------]
	//[ Private virtual SceneNode functions                   ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GUI_H__
