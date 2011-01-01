/*********************************************************\
 *  File: SNEngineInformation.h                          *
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


#ifndef __PLSCENE_SCENENODE_ENGINEINFORMATION_H__
#define __PLSCENE_SCENENODE_ENGINEINFORMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class MaterialHandler;
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
*    Engine information scene node
*
*  @remarks
*    This scene node can draw different engine/debug information.
*    The drawn depends on the config group 'EngineDebugConfig':
*    ShowFPS, ShowCoordinateAxis, ShowXZPlane, ShowXYPlane, ShowYZPlane
*
*  @note
*    - Should only be used within a scene root container
*    - If profiling is active, you can use the page-up/page-down keys to select the
*      next/previous group
*/
class SNEngineInformation : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Information flags
		*/
		enum EInfoFlags {
			FPS            = 1<<0,	/**< Draw FPS */
			CoordinateAxis = 1<<1,	/**< Draw coordinate axis */
			Planes         = 1<<2,	/**< Draw planes */
			Profiling      = 1<<3	/**< Draw profiling */
		};
		pl_enum(EInfoFlags)
			pl_enum_value(FPS,				"Draw FPS")
			pl_enum_value(CoordinateAxis,	"Draw coordinate axis")
			pl_enum_value(Planes,			"Draw planes")
			pl_enum_value(Profiling,		"Draw profiling")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNEngineInformation, "PLScene", PLScene::SceneNode, "Engine information scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(InfoFlags,			pl_flag_type(EInfoFlags),	FPS|CoordinateAxis|Planes|Profiling,	ReadWrite,	DirectValue,	"Information flags",	"")
		pl_attribute(ProfilingMaterial,	PLGeneral::String,			"Data/Effects/PLProfiling.plfx",		ReadWrite,	GetSet,			"Profiling material",	"Type='Material Effect Image TextureAni'")
		// Overwritten SceneNode variables
		pl_attribute(Flags,				pl_flag_type(EFlags),		NoCulling,								ReadWrite,	GetSet,			"Flags",				"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetProfilingMaterial() const;
		PLS_API void SetProfilingMaterial(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLS_API SNEngineInformation();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNEngineInformation();

		/**
		*  @brief
		*    Returns the handler of the profiling material
		*
		*  @return
		*    Handler of the profiling material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetProfilingMaterialHandler();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws the information of the current selected profile group
		*
		*  @param[in] cRenderer
		*    The used renderer
		*/
		void DrawProfiling(PLRenderer::Renderer &cRenderer);

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
		PLGeneral::String			 m_sProfilingMaterial;	/**< Profiling material */
		bool						 m_bProfilingMaterial;	/**< Profiling material loaded? */
		PLRenderer::MaterialHandler *m_pProfilingMaterial;	/**< Profiling material (ALWAYS valid!) */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawPost(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNode functions                 ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_ENGINEINFORMATION_H__
