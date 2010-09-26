/*********************************************************\
 *  File: ShadowMapManager.h                             *
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


#ifndef __PLSCENE_SHADOWMAPMANAGER_H__
#define __PLSCENE_SHADOWMAPMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Pool.h>
#include <PLGeneral/Base/ElementManager.h>
#include <PLMath/Rectangle.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLScene/Compositing/ShadowMap.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
	class Material;
	class IndexBuffer;
	class VertexBuffer;
	class ProgramUniform;
	class ProgramAttribute;
	class SurfaceTextureBuffer;
}
namespace PLMesh {
	class Mesh;
	class Geometry;
	class MeshHandler;
	class MeshLODLevel;
}
namespace PLScene {
	class SQCull;
	class SNLight;
	class VisNode;
	class SceneQueryHandler;
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
*    This is a manager for shadow map elements
*/
class ShadowMapManager : public PLGeneral::ElementManager<ShadowMap> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used, don't change the shader language on each call (performance!)
		*/
		PLS_API ShadowMapManager(PLRenderer::Renderer &cRenderer, const PLGeneral::String &sShaderLanguage = "");

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~ShadowMapManager();

		/**
		*  @brief
		*    Updates the shadow map
		*
		*  @param[in] cLight
		*    Light scene node to render the shadow map for
		*  @param[in] cCullQuery
		*    Current cull query
		*  @param[in] fSquaredDistanceToCamera
		*    Squared distance to camera, if <=0 means no shadow LOD 
		*
		*  @note
		*    - Changes the current render states!
		*/
		PLS_API void UpdateShadowMap(SNLight &cLight, const SQCull &cCullQuery, float fSquaredDistanceToCamera);

		/**
		*  @brief
		*    Returns the render target for the cube shadow map
		*
		*  @return
		*    The render target for the cube shadow map, NULL on error
		*/
		PLS_API PLRenderer::SurfaceTextureBuffer *GetCubeShadowRenderTarget() const;

		/**
		*  @brief
		*    Returns the render target for the spot shadow map
		*
		*  @return
		*    The render target for the spot shadow map, NULL on error
		*/
		PLS_API PLRenderer::SurfaceTextureBuffer *GetSpotShadowRenderTarget() const;


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Vertex shader flags, flag names become to source code definitions
		*/
		enum EVertexShaderFlags {
			VS_TEXCOORD0 = 1<<0	/**< Use texture coordinate 0 */
		};

		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_ALPHATEST = 1<<0		/**< Use alpha test to discard fragments */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			PLRenderer::ProgramAttribute *pVertexTexCoord0;
			// Vertex shader uniforms
			PLRenderer::ProgramUniform *pWorldVP;
			PLRenderer::ProgramUniform *pWorldV;
			PLRenderer::ProgramUniform *pInvRadius;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pDiffuseMap;
			PLRenderer::ProgramUniform *pAlphaReference;
		};

		/**
		*  @brief
		*    Mesh batch
		*/
		struct MeshBatch {
			const PLRenderer::Material		*pMaterial;			/**< Used material, always valid! */
				  PLRenderer::VertexBuffer	*pVertexBuffer;		/**< Used vertex buffer, always valid! */
				  PLRenderer::IndexBuffer	*pIndexBuffer;		/**< Used index buffer, always valid! */
			const PLMesh::Geometry			*pGeometry;			/**< Used geometry, always valid! */
			const PLScene::SQCull			*pCullQuery;		/**< Used cull query, always valid! */
			const PLScene::VisNode			*pVisNode;			/**< Used visibility node, always valid! */
				  PLMath::Rectangle			 sScissorRectangle;	/**< Scissor rectangle */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Collect mesh batches recursive
		*
		*  @param[in] cCullQuery
		*    Cull query to use
		*/
		void CollectMeshBatchesRec(const PLScene::SQCull &cCullQuery);

		/**
		*  @brief
		*    Makes a material to the currently used one
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cMaterial
		*    Material to use
		*  @param[in] fInvRadius
		*    Set world space inverse light radius
		*
		*  @return
		*    Generated program user data
		*/
		GeneratedProgramUserData *MakeMaterialCurrent(PLRenderer::Renderer &cRenderer, const PLRenderer::Material &cMaterial, float fInvRadius);

		/**
		*  @brief
		*    Draws a mesh batch
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cGeneratedProgramUserData
		*    Generated program user data for the mesh batch material
		*  @param[in] cMeshBatch
		*    Mesh batch to use
		*/
		void DrawMeshBatch(PLRenderer::Renderer &cRenderer, GeneratedProgramUserData &cGeneratedProgramUserData, MeshBatch &cMeshBatch) const;

		/**
		*  @brief
		*    Returns a free mesh batch
		*
		*  @return
		*    Free mesh batch
		*
		*  @note
		*    - Use FreeMeshBatch() if you no longer need this mesh batch
		*/
		MeshBatch &GetFreeMeshBatch();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer	*m_pRenderer;		/**< Used renderer (always valid!) */
		PLGeneral::String		 m_sShaderLanguage;	/**< Shader language to use */
		SceneQueryHandler		*m_pLightCullQuery;	/**< Light cull query (always valid!) */

		// Cube shadow map
		static const PLGeneral::uint32 CubeShadowRenderTargets = 5;
		PLRenderer::SurfaceTextureBuffer *m_pCubeShadowRenderTarget[CubeShadowRenderTargets];	/**< 256, 128, 64, 32, 16, can be NULL */
		PLRenderer::SurfaceTextureBuffer **m_pCurrentCubeShadowRenderTarget;

		// Spot shadow map
		static const PLGeneral::uint32 SpotShadowRenderTargets = 5;
		PLRenderer::SurfaceTextureBuffer *m_pSpotShadowRenderTarget[SpotShadowRenderTargets];	/**< 512, 256, 128, 64, 32, can be NULL */
		PLRenderer::SurfaceTextureBuffer **m_pCurrentSpotShadowRenderTarget;

		// Material & shader
		PLGeneral::Pool<const PLRenderer::Material*>  m_lstMaterials;			/**< List of currently used materials */
		PLGeneral::Pool<MeshBatch*>					  m_lstFreeMeshBatches;		/**< List of currently free mesh batches */
		PLGeneral::Pool<MeshBatch*>					  m_lstMeshBatches;			/**< List of currently used mesh batches */
		PLRenderer::ProgramGenerator				 *m_pProgramGenerator;		/**< Program generator, can be NULL */
		PLRenderer::ProgramGenerator::Flags			  m_cProgramFlags;			/**< Program flags as class member to reduce dynamic memory allocations */


	//[-------------------------------------------------------]
	//[ Private virtual PLGeneral::ElementManager functions   ]
	//[-------------------------------------------------------]
	private:
		virtual ShadowMap *CreateElement(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SHADOWMAPMANAGER_H__
