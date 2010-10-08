/*********************************************************\
 *  File: SNMOrbitingController.h                        *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSCENE_SCENENODEMODIFIER_ORBITINGCONTROLLER_H__
#define __PLSCENE_SCENENODEMODIFIER_ORBITINGCONTROLLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMOrbiting.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class OrbitingController;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node modifier class rotating a scene node towards a target scene node using an input controller
*
*  @remarks
*    When using the unchanged virtual standard controller:
*    Hold the left mouse button to rotate, the right mouse button to zoom and the middle mouse button to pan.
*/
class SNMOrbitingController : public SNMOrbiting {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMOrbitingController, "PLScene", PLScene::SNMOrbiting, "Scene node modifier class rotating a scene node towards a target scene node using an input controller")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLS_API SNMOrbitingController(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMOrbitingController();


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SceneNodeModifier functions   ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual PLInput::Controller *GetInputController() const;


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
		OrbitingController *m_pController;	/**< Orbiting input controller instance, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_ORBITINGCONTROLLER_H__
