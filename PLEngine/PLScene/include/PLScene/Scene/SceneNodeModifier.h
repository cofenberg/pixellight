/*********************************************************\
 *  File: SceneNodeModifier.h                            *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_H__
#define __PLSCENE_SCENENODEMODIFIER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLInput {
	class Controller;
}
namespace PLScene {
	class SceneNode;
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
*    Abstract scene node modifier (other name: controller) class
*
*  @remarks
*    A scene node modifier modifies the behaviour of a scene node. For instance it adds
*    a physical behaviour, make a light source flickering etc. The 'SceneNodeClass' property
*    is the information on which class this modifier operates on. For instance, it's not
*    possible to assign a light flickering modifier to a a scene node which is a noise.
*
*  @note
*    - Derived classes should use a 'SNM'-prefix (example: SNMTransform)
*/
class SceneNodeModifier : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SceneNode;


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node modifier flags
		*/
		enum EFlags {
			Inactive  = 1<<0,	/**< This scene node modifier is currently NOT active */
			Automatic = 1<<1	/**< This scene node modifier was created automatically during runtime and should
									 not be saved with the scene. Such scene nodes modifiers are also hidden for
									 instance within the scene editor. */
		};
		pl_enum(EFlags)
			pl_enum_value(Inactive,		"This scene renderer pass is currently NOT active")
			pl_enum_value(Automatic,	"This scene node modifier was created automatically during runtime and should not be saved with the scene. Such scene nodes modifiers are also hidden for instance within the scene editor.")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SceneNodeModifier, "PLScene", PLCore::Object, "Abstract scene node modifier (other name: controller) class")
		pl_attribute(Flags,	pl_flag_type(EFlags),	0,	ReadWrite,	GetSet,	"Flags",	"")
		pl_properties
			pl_property("SceneNodeClass", "PLScene::SceneNode")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual PLGeneral::uint32 GetFlags() const;
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the owner scene node
		*
		*  @return
		*    The owner scene node
		*/
		PLS_API SceneNode &GetSceneNode() const;

		/**
		*  @brief
		*    Returns the scene node class this modifier operates on
		*
		*  @return
		*    The scene node class this modifier operates on
		*/
		PLS_API PLGeneral::String GetSceneNodeClass() const;

		/**
		*  @brief
		*    Is the scene node modifier active?
		*
		*  @return
		*    'true' if the scene node modifier is active, else 'false'
		*/
		PLS_API bool IsActive() const;

		/**
		*  @brief
		*    Sets whether the scene node modifier is active or not
		*
		*  @param[in] bActive
		*    Should the scene node modifier be active?
		*
		*  @note
		*    - Sets/unsets the 'Inactive'-flag
		*/
		PLS_API void SetActive(bool bActive = true);


	//[-------------------------------------------------------]
	//[ Public virtual SceneNodeModifier functions            ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get input controller
		*
		*  @return
		*    Input controller (can be NULL)
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLS_API virtual PLInput::Controller *GetInputController() const;


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Informed on scene node modifier initialization
		*
		*  @note
		*    - The default implementation calls SetFlags(GetFlags())
		*/
		PLS_API virtual void InformedOnInit();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLS_API SceneNodeModifier(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneNodeModifier();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32  m_nFlags;		/**< Flags */
		SceneNode		  *m_pSceneNode;	/**< Owner scene node (ALWAYS valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_H__
