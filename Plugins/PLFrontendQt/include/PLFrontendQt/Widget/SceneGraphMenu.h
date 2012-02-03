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
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Performed action
		*/
		enum EAction {
			ActionUnknown,	/**< Performed action is unknown */
			ActionAdded,	/**< Something was added */
			ActionCloned,	/**< Something was cloned */
			ActionDeleted	/**< Something was deleted */
		};


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

		/**
		*  @brief
		*    Returns the created object instance if an create/clone action was done
		*
		*  @return
		*    The created object instance if an create/clone action was done, otherwise a null pointer will be returned
		*
		*  @note
		*    - Use the returnd object pointer at once when this menu returns, do not use this method later one because the pointer may have become invalid
		*/
		PLCore::Object *GetCreatedObject() const;


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
		*    Fills the add menu recursive
		*
		*  @param[in] cQMenu
		*    Current Qt menu to fill
		*  @param[in] sBaseClass
		*    Name of the currently used RTTI base class
		*/
		void FillAddWindowRec(QMenu &cQMenu, const PLCore::String &sBaseClass);


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
		PLCore::Object *m_pCreatedObject;	/**< RTTI class instance which was created via an add/clone action, can be a null pointer */
		QMenu		   *m_pQMenuAdd;		/**< Add Qt menu instance, always valid */
		QActionGroup   *m_pQActionGroupAdd;	/**< Add Qt action group, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_SCENEGRAPHMENU_H__
