/*********************************************************\
 *  File: SNMTransformGizmo.h                            *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_TRANSFORMGIZMO_H__
#define __PLSCENE_SCENENODEMODIFIER_TRANSFORMGIZMO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodeModifiers/SNMTransform.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Ray;
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
*    Abstract transform gizmo scene node modifier base class
*/
class SNMTransformGizmo : public SNMTransform {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Selected axis flags
		*/
		enum ESelected {
			XAxis = 1,	/**< X axis is selected */
			YAxis = 2,	/**< Y axis is selected */
			ZAxis = 4	/**< Z axis is selected */
		};


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMTransformGizmo, "PLScene", PLScene::SNMTransform, "Abstract transform gizmo scene node modifier base class")
		// Slots
		pl_slot_2(OnDrawTransparent,	PLRenderer::Renderer&,	const VisNode*,	"Called on scene node transparent draw, the used renderer as first parameter, the current visibility node of this scene node, can be a null pointer as second parameter",	"")
		pl_slot_0(OnUpdate,														"Called when the scene node modifier needs to be updated",																													"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the current selected axis (see ESelected flags)
		*
		*  @return
		*    Current selected axis
		*/
		PLS_API PLCore::uint32 GetSelected() const;

		/**
		*  @brief
		*    Sets the current selected axis (see ESelected flags)
		*
		*  @param[in] nSelected
		*    Current selected axis, 0 if nothing is currently selected
		*/
		PLS_API void SetSelected(PLCore::uint32 nSelected);

		/**
		*  @brief
		*    Returns whether the transform gizmo is currently in transform mode or not
		*
		*  @return
		*    'true' if the transform gizmo is currently in transform mode, else 'false'
		*/
		PLS_API bool IsTransformMode() const;

		/**
		*  @brief
		*    Sets whether the transform gizmo is currently in transform mode or not
		*
		*  @param[in] bTransformMode
		*    'true' if the transform gizmo is currently in transform mode, else 'false'
		*/
		PLS_API void SetTransformMode(bool bTransformMode);


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
		PLS_API SNMTransformGizmo(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMTransformGizmo();

		/**
		*  @brief
		*    Sets a scaled world matrix
		*
		*  @param[in]      cRenderer
		*    Renderer to use
		*  @param[in, out] mWorld
		*    World matrix to use/manipulate
		*
		*  @return
		*    Scale factor
		*/
		PLS_API float SetScaledWorldMatrix(PLRenderer::Renderer &cRenderer, PLMath::Matrix4x4 &mWorld);


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Protected virtual SNMTransformGizmo functions         ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Determines the current selected axis by using a picking ray
		*
		*  @param[in] cRay
		*    Ray to use for the intersection tests, must be in the correct coordinate system used for the gizmo picking
		*
		*  @return
		*    Chosen axis (see ESelected flags)
		*/
		virtual PLCore::uint32 DetermineSelected(const PLMath::Ray &cRay) const = 0;

		/**
		*  @brief
		*    Updates the transform gizmo selection
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cVisNode
		*    The current visibility node of this scene node
		*/
		virtual void UpdateSelection(PLRenderer::Renderer &cRenderer, const VisNode &cVisNode) = 0;

		/**
		*  @brief
		*    Performs the transform
		*/
		virtual void PerformTransform() = 0;

		/**
		*  @brief
		*    Draws the transform gizmo
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] pVisNode
		*    The current visibility node of this scene node, can be a null pointer
		*/
		virtual void DrawGizmo(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::uint32 m_nSelected;		/**< The current selection */
		bool		   m_bTransform;	/**< Is currently a transform performed? */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called on scene node transparent draw
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] pVisNode
		*    The current visibility node of this scene node, can be a null pointer
		*/
		void OnDrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode);

		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		void OnUpdate();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_TRANSFORMGIZMO_H__
