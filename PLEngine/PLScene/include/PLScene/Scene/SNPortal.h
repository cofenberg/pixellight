/*********************************************************\
 *  File: SNPortal.h                                     *
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


#ifndef __PLSCENE_PORTAL_H__
#define __PLSCENE_PORTAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Polygon.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract portal scene node
*
*  @note
*    - Please note: A portal may or may not let light and shadows pass through it. This depends on the used scene renderer,
*      so, by default proper portal scene node flags are set so light and shadows may always pass as default.
*/
class SNPortal : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node debug flags (SceneNode debug flags extension)
		*/
		enum EDebugFlags {
			DebugNoPortalPolygon = 1<<8,	/**< Do not draw the (pink) portal polygon */
			DebugPortalVertices  = 1<<9		/**< Draw the (white) portal vertices */
		};
		pl_enum(EDebugFlags)
			pl_enum_base(SceneNode::EDebugFlags)
			pl_enum_value(DebugNoPortalPolygon,	"Do not draw the (pink) portal polygon")
			pl_enum_value(DebugPortalVertices,	"Draw the (white) portal vertices")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNPortal, "PLScene", PLScene::SceneNode, "Abstract portal scene node")
		pl_attribute(Vertices,		PLGeneral::String,			"-1.0 -1.0 0.0 -1.0 1.0 0.0 1.0 1.0 0.0 1.0 -1.0 0.0",	ReadWrite,	GetSet,	"Vertices (xyz, counterclockwise) defining the portal polygon. There should be at least 3 vertices.",	"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,			pl_flag_type(EFlags),		CastShadow|ReceiveShadow,								ReadWrite,	GetSet,	"Flags",																								"")
		pl_attribute(DebugFlags,	pl_flag_type(EDebugFlags),	0,														ReadWrite,	GetSet,	"Debug flags",																							"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetVertices() const;
		PLS_API void SetVertices(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the portal polygon
		*
		*  @return
		*    The portal polygon
		*
		*  @note
		*    - Call UpdatePolygon() after you manipulated the portal polygon
		*/
		PLS_API PLMath::Polygon &GetPolygon();

		/**
		*  @brief
		*    Call this function after you manipulated the portal polygon
		*/
		PLS_API void UpdatePolygon();

		/**
		*  @brief
		*    Returns the portal polygon in container space
		*
		*  @return
		*    The portal polygon in container space
		*
		*  @note
		*    - This container space portal polygon is rebuild automatically if required
		*/
		PLS_API const PLMath::Polygon &GetContainerPolygon();

		/**
		*  @brief
		*    Returns the warp matrix
		*
		*  @return
		*    The warp matrix
		*
		*  @remarks
		*    The warp matrix transforms from this cell space into target cell space.
		*
		*  @note
		*    - Is updated automatically
		*/
		PLS_API const PLMath::Matrix3x4 &GetWarpMatrix();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNPortal();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNPortal();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::uint8 m_nInternalPortalFlags;	/**< Internal portal flags */


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Flags which hold ínternal portal information
		*/
		enum EInternalPortalFlags {
			// Recalculate
			RecalculateContainerPolygon	= 1<<0	/**< Recalculation of the container space polygon required */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node container, position, rotation or scale changed
		*/
		void NotifyContainerPositionRotationScale();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerContainerPositionRotationScale;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String	m_sVertices;			/**< Vertices (xyz, counterclockwise) defining the portal polygon. There should be at least 3 vertices." */
		PLMath::Polygon		m_cPolygon;				/**< Local portal polygon */
		PLMath::Polygon		m_cContainerPolygon;	/**< Container space portal polygon */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawDebug(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_PORTAL_H__
