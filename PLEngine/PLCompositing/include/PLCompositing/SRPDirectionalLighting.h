/*********************************************************\
 *  File: SRPDirectionalLighting.h                       *
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


#ifndef __PLCOMPOSITING_DIRECTIONALLIGHTING_H__
#define __PLCOMPOSITING_DIRECTIONALLIGHTING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color3.h>
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class VertexBuffer;
}
namespace PLMesh {
	class Mesh;
	class MeshHandler;
	class MeshLODLevel;
}
namespace PLScene {
	class VisNode;
	class SceneNode;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract directional lighting scene renderer pass
*
*  @remarks
*    Implementations of this scene renderer pass should be able to support as many material parameters as possible with the support for a
*    single directional light source. By using this scene renderer pass, a visible and lit (including ambient) scene can be drawn by using
*    just one render pass. This keeps the hardware requirements low and is already enough for certain applications. Other, following lighting
*    scene renderer passes should be able to detect that a certain directional light source has already been rendered, and don't render
*    this light a second time. As a result, this scene renderer pass can be used as stand alone, or as a part of for example a forward
*    rendering pipeline.
*/
class SRPDirectionalLighting : public PLScene::SceneRendererPass {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Texture filtering modes
		*/
		enum ETextureFiltering {
			NoFiltering   = 0,	/**< No filtering */
			Bilinear      = 1,	/**< Bilinear */
			Anisotropic2  = 2,	/**< Anisotropic x2 */
			Anisotropic4  = 4,	/**< Anisotropic x4 */
			Anisotropic8  = 8,	/**< Anisotropic x8 */
			Anisotropic16 = 16	/**< Anisotropic x16 */
		};
		pl_enum(ETextureFiltering)
			pl_enum_value(NoFiltering,		"No filtering")
			pl_enum_value(Bilinear,			"Bilinear")
			pl_enum_value(Anisotropic2,		"Anisotropic x2")
			pl_enum_value(Anisotropic4,		"Anisotropic x4")
			pl_enum_value(Anisotropic8,		"Anisotropic x8")
			pl_enum_value(Anisotropic16,	"Anisotropic x16")
		pl_enum_end

		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			TransparentPass = 1<<1,	/**< This is a transparent render pass */
			NoZWrite        = 1<<2,	/**< Do not write z-values */
			NoDiffuseMap    = 1<<3,	/**< Ignore diffuse map */
			NoLighting      = 1<<4	/**< Do not perform lighting by using the first found directional light source */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneRendererPass::EFlags)
			pl_enum_value(TransparentPass,	"This is a transparent render pass")
			pl_enum_value(NoZWrite,			"Do not write z-values")
			pl_enum_value(NoDiffuseMap,		"Ignore diffuse map")
			pl_enum_value(NoLighting,		"Do not perform lighting by using the first found directional light source")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDirectionalLighting, "PLCompositing", PLScene::SceneRendererPass, "Abstract directional lighting scene renderer pass")
		pl_attribute(AmbientColor,		PLGraphics::Color3,					PLGraphics::Color3(1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Ambient color",				"")
		pl_attribute(LightingIntensity,	float,								1.0f,									ReadWrite,	DirectValue,	"General lighting intensity",	"")
		pl_attribute(TextureFiltering,	pl_enum_type(ETextureFiltering),	Anisotropic8,							ReadWrite,	DirectValue,	"Texture filtering",			"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),				0,										ReadWrite,	GetSet,			"Flags",						"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDirectionalLighting();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDirectionalLighting();

		/**
		*  @brief
		*    Sets correct texture filtering modes
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] nStage
		*    Texture stage
		*/
		PLCOM_API void SetupTextureFiltering(PLRenderer::Renderer &cRenderer, PLGeneral::uint32 nStage) const;

		/**
		*  @brief
		*    Draws recursive
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*/
		PLCOM_API void DrawRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);

		/**
		*  @brief
		*    Searches for the first (= nearest) visible directional light scene node
		*
		*  @param[in] cCullQuery
		*    Cull query to use
		*
		*  @return
		*    Visibility node referencing the first visible directional light scene node, NULL if no such scene node was found
		*/
		PLCOM_API const PLScene::VisNode *GetFirstDirectionalLight(const PLScene::SQCull &cCullQuery) const;


	//[-------------------------------------------------------]
	//[ Protected virtual SRPDirectionalLighting functions    ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Draws a mesh
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*  @param[in] cVisNode
		*    Visibility node to use
		*  @param[in] cSceneNode
		*    Mesh owner scene node
		*  @param[in] cMeshHandler
		*    Mesh handler to use
		*  @param[in] cMesh
		*    Mesh to draw
		*  @param[in] cMeshLODLevel
		*    LOD level of the mesh to draw
		*  @param[in] cVertexBuffer
		*    Vertex buffer to use
		*/
		virtual void DrawMesh(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, PLScene::SceneNode &cSceneNode, const PLMesh::MeshHandler &cMeshHandler, const PLMesh::Mesh &cMesh, const PLMesh::MeshLODLevel &cMeshLODLevel, PLRenderer::VertexBuffer &cVertexBuffer) = 0;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Searches for the first (= nearest) visible directional light scene node, recursive part
		*
		*  @param[in] cCullQuery
		*    Cull query to use
		*
		*  @return
		*    Visibility node referencing the first visible directional light scene node, NULL if no such scene node was found
		*/
		const PLScene::VisNode *GetFirstDirectionalLightRec(const PLScene::SQCull &cCullQuery) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DIRECTIONALLIGHTING_H__
