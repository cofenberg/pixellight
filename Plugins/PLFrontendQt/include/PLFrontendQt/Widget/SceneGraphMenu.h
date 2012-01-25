/*********************************************************\
 *  File: SceneGraphMenu.h                               *
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


#ifndef __PLFRONTENDQT_SCENEGRAPHMENU_H__
#define __PLFRONTENDQT_SCENEGRAPHMENU_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtGui/qmenu.h>
#include <PLCore/Base/Event/EventHandler.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QAction;
	class QActionGroup;
QT_END_NAMESPACE
namespace PLCore {
	class Object;
}
namespace PLScene {
	class SceneNode;
	class SceneContainer;
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
*    Scene graph Qt menu class
*/
class SceneGraphMenu : public QMenu {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cObject
		*    RTTI class instance we're working on
		*/
		SceneGraphMenu(PLCore::Object &cObject);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SceneGraphMenu();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the object assigned with this menu was destroyed
		*/
		void OnDestroyed();

		/**
		*  @brief
		*    Fills the add menu recursivity
		*
		*  @param[in] cQMenu
		*    Current Qt menu to fill
		*  @param[in] sBaseClass
		*    Name of the currently used RTTI base class
		*/
		void FillAddWindowRec(QMenu &cQMenu, const PLCore::String &sBaseClass);

		/**
		*  @brief
		*    Clones the given scene node
		*
		*  @param[in] cTargetSceneContainer
		*    Scene container were to create the new scene node in
		*  @param[in] cSceneNode
		*    Scene node to clone
		*  @param[in] sNameExtension
		*    Clone name extension
		*/
		void CloneSceneNode(PLScene::SceneContainer &cTargetSceneContainer, const PLScene::SceneNode &cSceneNode, const PLCore::String &sNameExtension);


	//[-------------------------------------------------------]
	//[ Private Qt slots (MOC)                                ]
	//[-------------------------------------------------------]
	private slots:
		void QtSlotAboutToShowAdd();
		void QtSlotSelectedAdd(QAction *);
		void QtSlotTriggeredClone();
		void QtSlotTriggeredDelete();


	//[-------------------------------------------------------]
	//[ Private PixelLight slots                              ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> SlotDestroyed;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Object *m_pObject;			/**< RTTI class instance we're working on, always valid */
		QMenu		   *m_pQMenuAdd;		/**< Add Qt menu instance, always valid */
		QActionGroup   *m_pQActionGroupAdd;	/**< Add Qt action group, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_SCENEGRAPHMENU_H__
