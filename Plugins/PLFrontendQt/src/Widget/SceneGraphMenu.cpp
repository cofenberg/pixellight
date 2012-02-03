/*********************************************************\
 *  File: SceneGraphMenu.cpp                             *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Class.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraph.h"
#include "PLFrontendQt/Widget/SceneGraphMenu.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SceneGraphMenu::SceneGraphMenu(Object &cObject) :
	SlotDestroyed(&SceneGraphMenu::OnDestroyed, this),
	m_pObject(&cObject),
	m_pCreatedObject(nullptr),
	m_pQMenuAdd(nullptr),
	m_pQActionGroupAdd(nullptr)
{
	bool bProtected = false;

	// Connect event handler
	cObject.SignalDestroyed.Connect(SlotDestroyed);

	// Setup the add menu
	if (m_pObject->IsInstanceOf("PLScene::SceneNode")) {
		m_pQMenuAdd = addMenu(tr("Add"));
		connect(m_pQMenuAdd, SIGNAL(aboutToShow()), this, SLOT(QtSlotAboutToShowAdd()));

		// Menu is filled when it's about to show

		// Get the protection state of the scene node
		bProtected = static_cast<SceneNode*>(m_pObject)->IsProtected();
	}

	// Do not allow cloning or deleting protected stuff
	if (!bProtected) {
		{ // Setup the clone action
			QAction *pQAction = addAction(tr("Clone"));
			pQAction->setData(ActionCloned);
			connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredClone()));
		}

		{ // Setup the delete action
			QAction *pQAction = addAction(tr("Delete"));
			pQAction->setData(ActionDeleted);
			connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredDelete()));
		}
	}
}

/**
*  @brief
*    Destructor
*/
SceneGraphMenu::~SceneGraphMenu()
{
}

/**
*  @brief
*    Returns the created object instance if an create/clone action was done
*/
Object *SceneGraphMenu::GetCreatedObject() const
{
	return m_pCreatedObject;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the object assigned with this menu was destroyed
*/
void SceneGraphMenu::OnDestroyed()
{
	// Argh! Mayday! We lost our object!
	// -> Close this menu at once
	close();
}

/**
*  @brief
*    Fills the add menu recursive
*/
void SceneGraphMenu::FillAddWindowRec(QMenu &cQMenu, const String &sBaseClass)
{
	// Get a list of RTTI classes derived from the current base class
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, sBaseClass, NonRecursive, NoBase, IncludeAbstract);
	ConstIterator<const Class*> cIterator = lstClasses.GetConstIterator();
	while (cIterator.HasNext()) {
		// Get the current RTTI class
		const Class *pClass = cIterator.Next();

		// Abstract class?
		if (pClass->HasConstructor()) {
			// Class can be instanced

			// It's possible to derive from non-abstract classes as well, we have to take this into account
			List<const Class*> lstDerivedClasses;
			ClassManager::GetInstance()->GetClasses(lstDerivedClasses, pClass->GetClassName(), Recursive, NoBase, NoAbstract);
			if (lstDerivedClasses.GetNumOfElements()) {
				// Add sub-menu
				QMenu *pQMenuSub = cQMenu.addMenu(tr(pClass->GetClassName()));

				// Add action
				QAction *pQAction = pQMenuSub->addAction(tr(pClass->GetClassName()));
				pQAction->setData(ActionAdded);
				m_pQActionGroupAdd->addAction(pQAction);

				// Automatically fill the Qt window menu by using RTTI information
				FillAddWindowRec(*pQMenuSub, pClass->GetClassName());
			} else {
				// The simple case, there are no classes deriving from the current class

				// Add action
				QAction *pQAction = cQMenu.addAction(tr(pClass->GetClassName()));
				pQAction->setData(ActionAdded);
				m_pQActionGroupAdd->addAction(pQAction);
			}
		} else {
			// Abstract class will result in a sub-menu, but only if at least one none abstract class is derived from it
			List<const Class*> lstDerivedClasses;
			ClassManager::GetInstance()->GetClasses(lstDerivedClasses, pClass->GetClassName(), Recursive, NoBase, NoAbstract);
			if (lstDerivedClasses.GetNumOfElements()) {
				// Add sub-menu
				QMenu *pQMenuSub = cQMenu.addMenu(tr(pClass->GetClassName()));

				// Automatically fill the Qt window menu by using RTTI information
				FillAddWindowRec(*pQMenuSub, pClass->GetClassName());
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void SceneGraphMenu::QtSlotAboutToShowAdd()
{
	// Clear the previous content - this is not performance critical so there's no reason to implement a
	// more complex solution like e.g. updating the menu entries as soon as there's a change within the RTTI system
	m_pQMenuAdd->clear();
	if (m_pQMenuAdd)
		delete m_pQActionGroupAdd;
	m_pQActionGroupAdd = new QActionGroup(m_pQMenuAdd);
	connect(m_pQActionGroupAdd, SIGNAL(selected(QAction*)), this, SLOT(QtSlotSelectedAdd(QAction*)));

	// Automatically fill the Qt menu by using the RTTI system information

	// In case we're currently working on scene container it's possible to add a scene node or a scene node modifier
	if (m_pObject->IsInstanceOf("PLScene::SceneContainer")) {
		// It's possible to add a scene node or a scene node modifier
		FillAddWindowRec(*m_pQMenuAdd->addMenu(tr("Node")), "PLScene::SceneNode");
		FillAddWindowRec(*m_pQMenuAdd->addMenu(tr("Modifier")), "PLScene::SceneNodeModifier");
	} else {
		// It's only possible to add a scene node modifier
		FillAddWindowRec(*m_pQMenuAdd, "PLScene::SceneNodeModifier");
	}
}

void SceneGraphMenu::QtSlotSelectedAdd(QAction *pQAction)
{
	// Get the RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass(QtStringAdapter::QtToPL(pQAction->text()));
	if (pClass) {
		// Scene node
		if (pClass->IsDerivedFrom("PLScene::SceneNode")) {
			// Create scene node instance
			if (m_pObject->IsInstanceOf("PLScene::SceneContainer"))
				m_pCreatedObject = static_cast<SceneContainer*>(m_pObject)->Create(pClass->GetClassName());

		// Scene node modifier
		} else if (pClass->IsDerivedFrom("PLScene::SceneNodeModifier")) {
			// Create scene node modifier instance
			if (m_pObject->IsInstanceOf("PLScene::SceneNode"))
				m_pCreatedObject = static_cast<SceneNode*>(m_pObject)->AddModifier(pClass->GetClassName());
		}
	}
}

void SceneGraphMenu::QtSlotTriggeredClone()
{
	// Scene node
	if (m_pObject->IsInstanceOf("PLScene::SceneNode")) {
		// Get scene node
		SceneNode &cSceneNode = static_cast<SceneNode&>(*m_pObject);

		// Do not clone automatic scene nodes
		if (!(cSceneNode.GetFlags() & SceneNode::Automatic)) {
			// Clone the scene node and add it after the scene node from which the clone will be created
			m_pCreatedObject = cSceneNode.CloneAtIndex(cSceneNode.GetContainerIndex() + 1);
		}

	// Scene node modifier
	} else if (m_pObject->IsInstanceOf("PLScene::SceneNodeModifier")) {
		// Get scene node modifier
		SceneNodeModifier &cSceneNodeModifier = static_cast<SceneNodeModifier&>(*m_pObject);

		// Do not clone automatic scene node modifiers
		if (!(cSceneNodeModifier.GetFlags() & SceneNodeModifier::Automatic)) {
			// Clone the scene node modifier and add it after the scene node modifier from which the clone will be created
			m_pCreatedObject = cSceneNodeModifier.CloneAtIndex(cSceneNodeModifier.GetSceneNodeIndex() + 1);
		}
	}
}

void SceneGraphMenu::QtSlotTriggeredDelete()
{
	// Scene node
	if (m_pObject->IsInstanceOf("PLScene::SceneNode")) {
		// Delete this scene node
		static_cast<SceneNode*>(m_pObject)->Delete();

	// Scene node modifier
	} else if (m_pObject->IsInstanceOf("PLScene::SceneNodeModifier")) {
		// Get scene node modifier
		SceneNodeModifier &cSceneNodeModifier = static_cast<SceneNodeModifier&>(*m_pObject);

		// Delete this scene node modifier
		cSceneNodeModifier.GetSceneNode().RemoveModifierByReference(cSceneNodeModifier);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
