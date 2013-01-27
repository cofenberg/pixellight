/*********************************************************\
 *  File: SPK_PLPointRendererShaders.h                   *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __SPARK_PL_POINTRENDERER_SHADERS_H__
#define __SPARK_PL_POINTRENDERER_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLPointRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Program;
	class VertexShader;
	class FragmentShader;
	class ProgramUniform;
	class ProgramAttribute;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A Renderer drawing drawing particles as PixelLight points using shaders
*
*  @note
*    - Basing on "SPK::GL::GLPointRenderer" (this includes most of the comments)
*/
class SPK_PLPointRendererShaders : public SPK_PLPointRenderer {


	//[-------------------------------------------------------]
	//[ SPARK macro                                           ]
	//[-------------------------------------------------------]
	SPK_IMPLEMENT_REGISTERABLE(SPK_PLPointRendererShaders)


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates and registers a new SPK_PLPointRendererShaders
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fSize
		*    The size of the points
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used
		*
		*  @return
		*    A new registered SPK_PLPointRendererShaders
		*/
		SPARK_PL_API static SPK_PLPointRendererShaders *Create(PLRenderer::Renderer &cRenderer, const PLCore::String &sShaderLanguage = "", float fSize = 1.0f);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/** 
		*  @brief
		*    Constructor of SPK_PLPointRendererShaders
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fSize
		*    The size of the points
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used
		*/
		SPK_PLPointRendererShaders(PLRenderer::Renderer &cRenderer, const PLCore::String &sShaderLanguage = "", float fSize = 1.0f);

		/**
		*  @brief
		*    Destructor of SPK_PLPointRendererShaders
		*/
		SPARK_PL_API virtual ~SPK_PLPointRendererShaders();


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void render(const SPK::Group &group) override;


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
		PLCore::EventHandler<PLRenderer::Program*> *m_pEventHandlerDirty;	/**< Dirty event handler, always valid pointer */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String					 m_sShaderLanguage;								/**< Shader language to use (for example "GLSL" or "Cg"), if empty string, the default shader language of the renderer will be used */
		PLRenderer::VertexShader		*m_pVertexShader;								/**< Vertex shader, can be a null pointer */
		PLRenderer::FragmentShader		*m_pFragmentShader;								/**< Fragment shader, can be a null pointer */
		PLRenderer::Program				*m_pProgram;									/**< GPU program, can be a null pointer */
		PLRenderer::ProgramAttribute	*m_pPositionProgramAttribute;					/**< Position program attribute, can be a null pointer */
		PLRenderer::ProgramAttribute	*m_pColorProgramAttribute;						/**< Color program attribute, can be a null pointer */
		PLRenderer::ProgramUniform		*m_pObjectSpaceToClipSpaceMatrixProgramUniform;	/**< Object space to clip space matrix program uniform, can be a null pointer */
		PLRenderer::ProgramUniform		*m_pPointParametersProgramUniform;				/**< Point parameters program uniform, can be a null pointer */
		PLRenderer::ProgramUniform		*m_pTextureMapProgramUniform;					/**< Texture map program uniform, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_POINTRENDERER_SHADERS_H__
