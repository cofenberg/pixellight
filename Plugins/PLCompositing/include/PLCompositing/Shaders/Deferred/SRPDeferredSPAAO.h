/*********************************************************\
 *  File: SRPDeferredSPAAO.h                             *
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


#ifndef __PLCOMPOSITING_DEFERRED_SPAAO_H__
#define __PLCOMPOSITING_DEFERRED_SPAAO_H__
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
	class TextureBuffer2D;
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
*    Scene renderer pass for deferred rendering "A Simple and Practical Approach to SSAO" (SPAAO), a "Screen-Space Ambient Occlusion" (SSAO) technique
*
*  @note
*    - Using "A Simple and Practical Approach to SSAO" as described at http://www.gamedev.net/page/reference/index.html/_/reference/programming/140/lighting-and-shading/a-simple-and-practical-approach-to-ssao-r2753
*/
class SRPDeferredSPAAO : public SRPDeferredSSAO {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredSPAAO, "PLCompositing", PLCompositing::SRPDeferredSSAO, "Scene renderer pass for deferred rendering 'A Simple and Practical Approach to SSAO' (SPAAO), a 'Screen-Space Ambient Occlusion' (SSAO) technique")
		// Attributes
		pl_attribute(NumberOfDirections,	PLCore::uint32,			8,		ReadWrite,	DirectValue,	"The number of randomly-rotated 2D directions in image space distributed around the current pixel. The higher this parameter, the lower is the noise in the ambient occlusion.",	"Min='1'")
		pl_attribute(SampleRadius,			float,					0.1f,	ReadWrite,	DirectValue,	"The sampling radius",																																								"Min='0.0'")
		pl_attribute(Intensity,				float,					4.0f,	ReadWrite,	DirectValue,	"The ambient occlusion intensity",																																					"Min='0.0'")
		pl_attribute(Scale,					float,					10.0f,	ReadWrite,	DirectValue,	"Scales distance between occluders and occludee",																																	"Min='0.0'")
		pl_attribute(Bias,					float,					0.2f,	ReadWrite,	DirectValue,	"Controls the width of the occlusion cone considered by the occludee",																												"Min='0.0'")
			// Overwritten PLScene::SceneRendererPass attributes
		pl_attribute(Flags,					pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",																																											"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API PLCore::uint32 GetNumberOfDirections() const;
		PLCOM_API void SetNumberOfDirections(PLCore::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredSPAAO();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredSPAAO();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pSampleRadius;
			PLRenderer::ProgramUniform *pIntensity;
			PLRenderer::ProgramUniform *pScale;
			PLRenderer::ProgramUniform *pBias;
			PLRenderer::ProgramUniform *pInvFocalLen;
			PLRenderer::ProgramUniform *pRandomSize;
			PLRenderer::ProgramUniform *pRandomNormalsMap;
			PLRenderer::ProgramUniform *pResolution;
			PLRenderer::ProgramUniform *pNormalDepthMap;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint32						 m_nNumberOfDirections;		/**< The number of randomly-rotated 2D directions in image space distributed around the current pixel. The higher this parameter, the lower is the noise in the ambient occlusion. */
		PLRenderer::TextureBuffer2D			*m_pRandomNormalsTexture;	/**< Texture with random normal vectors, can be a null pointer */
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;		/**< Program generator, can be a null pointer */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;			/**< Program flags as class member to reduce dynamic memory allocations */


	//[-------------------------------------------------------]
	//[ Protected virtual SRPDeferredSSAO functions           ]
	//[-------------------------------------------------------]
	protected:
		virtual void DrawAO(const PLCore::String &sShaderLanguage, PLRenderer::VertexBuffer &cVertexBuffer, PLRenderer::TextureBufferRectangle &cNormalDepthTextureBuffer) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEFERRED_SPAAO_H__
