/*********************************************************\
 *  File: SRPDeferredHDAO.h                              *
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


#ifndef __PLCOMPOSITING_DEFERRED_HDAO_H__
#define __PLCOMPOSITING_DEFERRED_HDAO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLCompositing/Shaders/Deferred/SRPDeferredSSAO.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class TextureBufferRectangle;
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
*    Scene renderer pass for deferred rendering "High Definition Ambient Occlusion" (HDAO), a "Screen-Space Ambient Occlusion" (SSAO) technique
*
*  @note
*    - Using "High Definition Ambient Occlusion" as described within ATI Radeon SDK
*      (http://developer.amd.com/Downloads/HDAO10.1.zip)
*/
class SRPDeferredHDAO : public SRPDeferredSSAO {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoNormals = 1<<2	/**< Ignore the per fragment normals when calculating the ambient occlusion (less AO details for heavy normal mapped scenes) */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferredSSAO::EFlags)
			pl_enum_value(NoNormals, "Ignore the per fragment normals when calculating the ambient occlusion (less AO details for heavy normal mapped scenes)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredHDAO, "PLCompositing", PLCompositing::SRPDeferredSSAO, "Scene renderer pass for deferred rendering 'High Definition Ambient Occlusion' (HDAO), a 'Screen-Space Ambient Occlusion' (SSAO) technique")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(AORejectRadius,		float,					0.43f,		ReadWrite,	DirectValue,	"If either of a twin pair of sampled camera Z values is further away from the central pixel’s camera Z value than the “Reject Radius”, then the twin pair of samples will not contribute to the occlusion factor. This alleviates a common problem with SSAO, where distant objects can cause a halo of occlusion on the silhouette edges of close by objects.",	"Min='0.0'")
		pl_attribute(AOAcceptRadius,		float,					0.00312f,	ReadWrite,	DirectValue,	"This works in a similar fashion to the “Reject Radius”. Again if either of a twin pair is closer to the central sample than the “Accept Radius”, then the twin pair of samples will not contribute to the occlusion factor. This can be particularly useful for avoiding unwanted occlusion on low density meshes.",												"Min='0.0'")
		pl_attribute(NormalScale,			float,					0.3f,		ReadWrite,	DirectValue,	"Controls the influence of per fragment normal vectors.",																																																																											"Min='0.0'")
		pl_attribute(AcceptAngle,			float,					0.98f,		ReadWrite,	DirectValue,	"Accept angle",																																																																																						"Min='0.0'")
		pl_attribute(NumberOfRingGathers,	PLGeneral::uint32,		20,			ReadWrite,	DirectValue,	"Number of ring gathers",																																																																																			"Min='1' Max='20'")
		pl_attribute(NumberOfRings,			PLGeneral::uint32,		4,			ReadWrite,	DirectValue,	"Number of rings",																																																																																					"Min='1' Max='4'")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,					pl_flag_type(EFlags),	0,			ReadWrite,	GetSet,			"Flags",																																																																																							"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredHDAO();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredHDAO();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_NORMAL = 1<<0	/**< Use per fragment normal vector */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			// Vertex shader uniforms
			PLRenderer::ProgramUniform *pTextureSize;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pAORejectRadius;
			PLRenderer::ProgramUniform *pContrast;
			PLRenderer::ProgramUniform *pAOAcceptRadius;
			PLRenderer::ProgramUniform *pNormalScale;
			PLRenderer::ProgramUniform *pAcceptAngle;
			PLRenderer::ProgramUniform *pNumRingGathers;
			PLRenderer::ProgramUniform *pNumRings;
			PLRenderer::ProgramUniform *pResolution;
			PLRenderer::ProgramUniform *pNormalDepthMap;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;	/**< Program generator, can be a null pointer */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;		/**< Program flags as class member to reduce dynamic memory allocations */


	//[-------------------------------------------------------]
	//[ Protected virtual SRPDeferredSSAO functions           ]
	//[-------------------------------------------------------]
	protected:
		virtual void DrawAO(const PLGeneral::String &sShaderLanguage, PLRenderer::VertexBuffer &cVertexBuffer, PLRenderer::TextureBufferRectangle &cNormalDepthTextureBuffer);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEFERRED_HDAO_H__
