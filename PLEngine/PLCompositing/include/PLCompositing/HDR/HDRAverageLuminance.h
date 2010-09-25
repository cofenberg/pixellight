/*********************************************************\
 *  File: HDRAverageLuminance.h                          *
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


#ifndef __PLCOMPOSITING_HDR_AVERAGELUMINANCE_H__
#define __PLCOMPOSITING_HDR_AVERAGELUMINANCE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color3;
}
namespace PLRenderer {
	class Program;
	class VertexShader;
	class TextureBuffer;
	class ProgramUniform;
	class FragmentShader;
	class TextureBuffer2D;
	class ProgramAttribute;
	class SurfaceTextureBuffer;
	class TextureBufferRectangle;
}
namespace PLScene {
	class FullscreenQuad;
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
*    HDR logarithmic average luminance calculation component
*
*  @note
*    - The technique described in http://developer.download.nvidia.com/SDK/9.5/Samples/DEMOS/Direct3D9/HDR_FP16x2.zip is used
*/
class HDRAverageLuminance {


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
		*/
		PLCOM_API HDRAverageLuminance(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API ~HDRAverageLuminance();

		/**
		*  @brief
		*    Calculates the logarithmic average luminance
		*
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used, don't change the shader language on each call (performance!)
		*  @param[in] cOriginalTexture
		*    Original HDR texture buffer to calculate the logarithmic average luminance from
		*  @param[in] cLuminanceConvert
		*    Luminance convert
		*
		*  @note
		*    - Use GetTextureBuffer() to receive the result of the calculation
		*/
		PLCOM_API void CalculateAverageLuminance(const PLGeneral::String &sShaderLanguage, PLRenderer::TextureBufferRectangle &cOriginalTexture, const PLGraphics::Color3 &cLuminanceConvert);

		/**
		*  @brief
		*    Returns the 1x1 2D texture buffer storing the logarithmic average luminance
		*
		*  @return
		*    The 1x1 2D texture buffer storing the logarithmic average luminance, NULL on error
		*
		*  @note
		*    - The texture buffer is only valid after CalculateAverageLuminance() was called
		*/
		PLCOM_API PLRenderer::TextureBuffer *GetTextureBuffer() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a program became dirty
		*
		*  @param[in] pProgram
		*    Program which became dirty
		*/
		void OnDirty(PLRenderer::Program *pProgram);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLRenderer::Program*> EventHandlerDirty;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer			 *m_pRenderer;										/**< Renderer to use, always valid! */
		PLScene::FullscreenQuad			 *m_pFullscreenQuad;								/**< Fullscreen quad instance, can be NULL */
		PLRenderer::VertexShader		 *m_pVertexShader;									/**< Vertex shader, can be NULL */
		// Downsample 2x2, calculate pixel luminance and log
		PLRenderer::FragmentShader		 *m_pDownsampleLogFragmentShader;					/**< Downsample 2x2 log fragment shader, can be NULL */
		PLRenderer::Program				 *m_pDownsampleLogProgram;							/**< Downsample 2x2 log GPU program, can be NULL */
		PLRenderer::ProgramAttribute	 *m_pDownsampleLogPositionProgramAttribute;			/**< Downsample 2x2 log position program attribute, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleLogTextureSizeProgramUniform;		/**< Downsample 2x2 log texture size program uniform, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleLogTextureProgramUniform;			/**< Downsample 2x2 log texture program uniform, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleLogLuminanceConvertProgramUniform;	/**< Downsample 2x2 log luminance convert program uniform, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleLogEpsilonProgramUniform;			/**< Downsample 2x2 log epsilon program uniform, can be NULL */
		PLRenderer::SurfaceTextureBuffer *m_pDownsampleLogRenderTarget;						/**< Downsample 2x2 log render target, can be NULL */
		// Downsample 4x4
		PLRenderer::VertexShader		 *m_pDownsampleVertexShader;						/**< Downsample vertex shader, can be NULL */
		PLRenderer::FragmentShader		 *m_pDownsampleFragmentShader;						/**< Downsample 4x4 fragment shader, can be NULL */
		PLRenderer::Program				 *m_pDownsampleProgram;								/**< Downsample 4x4 GPU program, can be NULL */
		PLRenderer::ProgramAttribute	 *m_pDownsamplePositionProgramAttribute;			/**< Downsample 4x4 position program attribute, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleTextureSizeProgramUniform;			/**< Downsample 4x4 texture size program uniform, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleSizeProgramUniform;					/**< Downsample 4x4 size program uniform, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleTextureProgramUniform;				/**< Downsample 4x4 texture program uniform, can be NULL */
		PLRenderer::SurfaceTextureBuffer *m_pDownsampleRenderTarget;						/**< Downsample 4x4 render target, can be NULL */
		// Reduce <4>x<4> to <1>x<1> and calculate the exponent
		PLRenderer::FragmentShader		 *m_pDownsampleExpFragmentShader;					/**< Downsample 4x4 exp fragment shader, can be NULL */
		PLRenderer::Program				 *m_pDownsampleExpProgram;							/**< Downsample 4x4 exp GPU program, can be NULL */
		PLRenderer::ProgramAttribute	 *m_pDownsampleExpPositionProgramAttribute;			/**< Downsample 4x4 exp position program attribute, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleExpTextureSizeProgramUniform;		/**< Downsample 4x4 exp texture size program uniform, can be NULL */
		PLRenderer::ProgramUniform		 *m_pDownsampleExpTextureProgramUniform;			/**< Downsample 4x4 exp texture program uniform, can be NULL */
		PLRenderer::SurfaceTextureBuffer *m_pAverageLuminanceTextureBuffer2D;				/**< 1x1 2D texture buffer storing the logarithmic average luminance, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_HDR_AVERAGELUMINANCE_H__
