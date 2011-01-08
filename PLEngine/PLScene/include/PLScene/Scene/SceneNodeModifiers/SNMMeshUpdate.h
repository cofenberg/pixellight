/*********************************************************\
 *  File: SNMMeshUpdate.h                                *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_MESHUPDATE_H__
#define __PLSCENE_SCENENODEMODIFIER_MESHUPDATE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/AABoundingBox.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class VisNode;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh scene node modifier which performs frequent mesh updates
*
*  @note
*    - Usually, there should be only once instance of this scene node modifier per scene node to avoid multiple mesh updates per frame (performance!)
*/
class SNMMeshUpdate : public SNMMesh {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			UpdateUnseen = 1<<2	/**< Do also perform an update if the owner scene node is currently not seen */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNodeModifier::EFlags)
			pl_enum_value(UpdateUnseen, "Do also perform an update if the owner scene node is currently not seen")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMMeshUpdate, "PLScene", PLScene::SNMMesh, "Mesh scene node modifier which performs frequent mesh updates")
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		// Overwritten SceneNodeModifier variables
		pl_attribute(Flags,	pl_flag_type(EFlags),	0,	ReadWrite,	GetSet,	"Flags",	"")
	pl_class_end


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
		PLS_API SNMMeshUpdate(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMMeshUpdate();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the owner scene node was added to a visibility tree
		*
		*  @param[in] cVisNode
		*    Visibility node which is representing the owner scene node within the visibility tree
		*/
		void NotifyAddedToVisibilityTree(VisNode &cVisNode);

		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<VisNode &> EventHandlerAddedToVisibilityTree;
		PLCore::EventHandler<>			EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool				   m_bUpdate;						/**< Perform an update the next time? */
		bool				   m_bFirstUpdate;					/**< First update performed? */
		PLMath::AABoundingBox  m_cDefaultMeshAABoundingBox;		/**< Default mesh axis align bounding box */
		PLMath::AABoundingBox  m_cDefaultJointAABoundingBox;	/**< Default joint axis align bounding box */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_MESHUPDATE_H__
