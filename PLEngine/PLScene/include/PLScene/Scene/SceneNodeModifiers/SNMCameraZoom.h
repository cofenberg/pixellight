/*********************************************************\
 *  File: SNMCameraZoom.h                                *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_CAMERAZOOM_H__
#define __PLSCENE_SCENENODEMODIFIER_CAMERAZOOM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifier.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node modifier class implementing camera zoom
*/
class SNMCameraZoom : public SceneNodeModifier {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMCameraZoom, "PLScene", PLScene::SceneNodeModifier, "Scene node modifier class implementing camera zoom")
		pl_properties
			pl_property("SceneNodeClass", "PLScene::SNCamera")
		pl_properties_end
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(ZoomDegree,	float,	30.0f,	ReadWrite,	DirectValue,	"Zoom in degree, added to original camera FOV",												"")
		pl_attribute(ZoomFactor,	float,	0.0f,	ReadWrite,	DirectValue,	"Target zoom factor [0..1]",																"")
		pl_attribute(ZoomSpeed,		float,	4.0f,	ReadWrite,	DirectValue,	"Current zoom factor update speed, if 0, current factor is set to target factor at once",	"")
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
		PLS_API SNMCameraZoom(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMCameraZoom();


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
		float m_fOriginalFOV;		/**< Original camera scene node FOV in degree when this modifier was added */
		float m_fCurrentZoomFactor;	/**< Current zoom factor [0..1] */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_CAMERAZOOM_H__
