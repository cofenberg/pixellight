/*********************************************************\
 *  File: SNMPositionPath.h                              *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_POSITIONPATH_H__
#define __PLSCENE_SCENENODEMODIFIER_POSITIONPATH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMTransform.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class GraphPath;
	class GraphPathHandler;
}
namespace PLRenderer {
	class Renderer;
}
namespace PLScene {
	class VisNode;
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
*    Scene node modifier class moving the position of a scene node along a given path
*
*  @remarks
*    There are two major strategies how to move along a path:
*    - By giving the percentage along the whole path, 0-1. This is the default setting and has the
*      advantage that the movement speed is constant and not depend of the length of each path segment.
*    - By giving the percentage by node index, 0-<number of nodes>. By using this approach the movement
*      speed on the path may vary, this depends on whether or not all path segments have the same length.
*    Beside the major strategy, it's possible to set the interpolation type.
*/
class SNMPositionPath : public SNMTransform {


	//[-------------------------------------------------------]
	//[ Public definition                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Interpolation type
		*/
		enum EInterpolation {
			Linear			= 0,	/**< Linear interpolation */
			CatmullRomCurve = 1		/**< Catmull rom curve interpolation */
		};
		pl_enum(EInterpolation)
			pl_enum_value(Linear,			"Linear interpolation")
			pl_enum_value(CatmullRomCurve,	"Catmull rom curve interpolation")
		pl_enum_end

		/**
		*  @brief
		*    Scene node modifier flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			NodeIndexProgress = 1<<2	/**< 'Progress' defined by 'node index' instead or 'percentage along path' */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMTransform::EFlags)
			pl_enum_value(NodeIndexProgress, "'Progress' defined by 'node index' instead or 'percentage along path'")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMPositionPath, "PLScene", PLScene::SNMTransform, "Scene node modifier class moving the position of a scene node along a given path")
		// Attributes
		pl_attribute(Filename,		PLCore::String,					"",		ReadWrite,	GetSet,			"Filename of the path the node should move on",									"Type='GraphPath'")
		pl_attribute(Progress,		float,							0.0f,	ReadWrite,	DirectValue,	"Path progress (0-1, automatically wrapped into that range -> or node index)",	"")
		pl_attribute(Speed,			float,							1.0f,	ReadWrite,	DirectValue,	"Path movement speed",															"")
		pl_attribute(Interpolation,	pl_enum_type(EInterpolation),	Linear,	ReadWrite,	DirectValue,	"Interpolation type",															"")
			// Overwritten SceneNodeModifier attributes
		pl_attribute(Flags,			pl_flag_type(EFlags),			0,		ReadWrite,	GetSet,			"Flags",																		"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	SceneNode&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLCore::String GetFilename() const;
		PLS_API void SetFilename(const PLCore::String &sValue);


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
		PLS_API SNMPositionPath(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMPositionPath();

		/**
		*  @brief
		*    Returns the used graph path
		*
		*  @return
		*    The used graph path, can be a null pointer
		*/
		PLS_API PLMath::GraphPath *GetGraphPath() const;


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		void OnUpdate();

		/**
		*  @brief
		*    Called on scene node debug draw
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] pVisNode
		*    The current visibility node of this scene node, can be a null pointer
		*/
		void OnDrawDebug(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<>										  EventHandlerUpdate;
		PLCore::EventHandler<PLRenderer::Renderer &, const VisNode *> EventHandlerDrawDebug;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLCore::String m_sFilename;
		float		   m_fProgress;
		float		   m_fSpeed;
		PLCore::uint32 m_nInterpolation;

		// Private data
		PLMath::GraphPathHandler *m_pPathHandler; /**< Our path (ALWAYS valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_POSITIONPATH_H__
