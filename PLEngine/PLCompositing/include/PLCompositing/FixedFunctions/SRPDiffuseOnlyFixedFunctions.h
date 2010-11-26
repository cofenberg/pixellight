/*********************************************************\
 *  File: SRPDiffuseOnlyFixedFunctions.h                 *
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


#ifndef __PLCOMPOSITING_FIXEDFUNCTIONS_DIFFUSEONLY_H__
#define __PLCOMPOSITING_FIXEDFUNCTIONS_DIFFUSEONLY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCompositing/SRPDiffuseOnly.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Material;
	class RenderStates;
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
*    Fixed functions based diffuse only scene renderer pass implementation, can also be used as depth only renderer pass
*
*  @remarks
*    This scene renderer pass can deal with the following material parameters:
*    - Opacity:          Transparency, 0.0 is full transparent, 1.0 is solid, default: 1.0
*    - OpacityOcclusion: Only used if the 'ZWriteOnly' flag is set, for transparency zbuffer writes, 0.0 for not writing into the zbuffer, 1.0 for writing into the zbuffer, default: 0.0
*                        The purpose of this parameter is to allow transparent materials to write into the zbuffer in a seperate z write only render pass before drawing all transparent
*                        objects - this way, a transparent material can block everything other transparent behind it to avoid for example "transparent color summation".
*    - SrcBlendFunc:     If 'Opacity' is less '1', source blend function, default: 'SrcAlpha' (see 'PLRenderer::BlendFunc::Enum')
*    - DstBlendFunc:     If 'Opacity' is less '1', destination blend function, default: 'InvSrcAlpha' (see 'PLRenderer::BlendFunc::Enum')
*    - TwoSided:         Backface culling active? If 1, both sides of polygons are visible, default: 0
*    - DiffuseColor:     Use this 3 floating point values to set the diffuse color, default: 1.0 1.0 1.0
*    - DiffuseMap:       Diffuse map (2D, RGB, other usual name: 'decal map')
*      - AlphaReference: Alpha reference 0.0-1.0, only used if the diffuse map has an alpha channel, if 0 no alpha test is performed at all
*
*    Example:
*  @verbatim
*    <?xml version="1.0"?>
*    <Material Version="1">
*        <Float Name="Opacity">1.0</Float>
*        <Float Name="OpacityOcclusion">0.0</Float>
*        <String Name="SrcBlendFunc">SrcAlpha</String>
*        <String Name="DstBlendFunc">InvSrcAlpha</String>
*        <Float Name="TwoSided">0.0</Float>
*        <Float3 Name="DiffuseColor">1.0 1.0 1.0</Float3>
*        <Texture Name="DiffuseMap">Data/Textures/My_DiffuseMap.dds</Texture>
*        <Float Name="AlphaReference">0.5</Float>
*    </Material>
*  @endverbatim
*/
class SRPDiffuseOnlyFixedFunctions : public SRPDiffuseOnly {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDiffuseOnlyFixedFunctions, "PLCompositing", PLCompositing::SRPDiffuseOnly, "Fixed functions based diffuse only scene renderer pass implementation, can also be used as depth only renderer pass")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDiffuseOnlyFixedFunctions();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDiffuseOnlyFixedFunctions();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::RenderStates   *m_pRenderStates;	/**< Used to 'translate' render state strings, always valid! */
		PLGeneral::uint32			m_nMaterialChanges;	/**< Number of material changes */
		const PLRenderer::Material *m_pCurrentMaterial;	/**< Current used material, can be NULL */


	//[-------------------------------------------------------]
	//[ Private SRPDiffuseOnly functions                      ]
	//[-------------------------------------------------------]
	private:
		void DrawMesh(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, PLScene::SceneNode &cSceneNode, const PLMesh::MeshHandler &cMeshHandler, const PLMesh::Mesh &cMesh, const PLMesh::MeshLODLevel &cMeshLODLevel, PLRenderer::VertexBuffer &cVertexBuffer);


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_FIXEDFUNCTIONS_DIFFUSEONLY_H__
