/*********************************************************\
 *  File: SPK_PLRenderer.h                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __SPARK_PL_RENDERER_H__
#define __SPARK_PL_RENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/Renderer/Types.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include "Core/SPK_Renderer.h"
PL_WARNING_POP
#include "SPARK_PL/SPARK_PL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
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
*    An abstract Renderer for the PixelLight renderers
*
*  @note
*    - Basing on "SPK::GL::GLRenderer" (this includes most of the comments)
*/
class SPK_PLRenderer : public SPK::Renderer {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor of SPK_PLRenderer
		*/
		SPARK_PL_API virtual ~SPK_PLRenderer();

		/**
		*  @brief
		*    Returns the used PixelLight renderer
		*
		*  @return
		*    The used PixelLight renderer
		*/
		inline PLRenderer::Renderer &GetPLRenderer() const;

		/**
		*  @brief
		*    Tells whether blending is enabled for this SPK_PLRenderer
		*
		*  @return
		*    'true' if blending is enabled, 'false' if it is disabled
		*/
		inline bool IsBlendingEnabled() const;

		/**
		*  @brief
		*    Enables or disables the blending of this SPK_PLRenderer
		*
		*  @param[in] bBlendingEnabled
		*    'true' to enable the blending, 'false' to disable it
		*/
		inline void EnableBlending(bool bBlendingEnabled);

		/**
		*  @brief
		*    Gets the source blending function of this SPK_PLRenderer
		*
		*  @return
		*    The source blending function of this SPK_PLRenderer
		*/
		inline PLRenderer::BlendFunc::Enum GetSrcBlendingFunction() const;

		/**
		*  @brief
		*    Gets the destination blending function of this SPK_PLRenderer
		*
		*  @return
		*    The source destination function of this SPK_PLRenderer
		*/
		inline PLRenderer::BlendFunc::Enum GetDestBlendingFunction() const;

		/**
		*  @brief
		*    Sets the blending functions of this SPK_PLRenderer
		*
		*  @param[in] nSrcBlending
		*    The source blending function of this SPK_PLRenderer
		*  @param[in] nDestBlending
		*    The destination blending function of this SPK_PLRenderer
		*
		*  @remarks
		*    The blending functions are one of the PixelLight blending functions.
		*/
		inline void SetBlendingFunctions(PLRenderer::BlendFunc::Enum nSrcBlending, PLRenderer::BlendFunc::Enum nDestBlending);

		/**
		*  @brief
		*    Sets the world view projection matrix used for rendering
		*
		*  @param[in] mWorldViewProjection
		*    The world view projection matrix used for rendering
		*/
		inline void SetWorldViewProjectionMatrix(const PLMath::Matrix4x4 &mWorldViewProjection);

		/**
		*  @brief
		*    Sets the inverse world view matrix used for rendering
		*
		*  @param[in] mWorldViewInverse
		*    The inverse world view matrix used for rendering
		*/
		inline void SetWorldViewInverse(const PLMath::Matrix4x4 &mWorldViewInverse);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void setBlending(SPK::BlendingMode blendMode) override;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor of SPK_PLRenderer
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*/
		SPARK_PL_API SPK_PLRenderer(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Inits the blending of this SPK_PLRenderer
		*/
		SPARK_PL_API void InitBlending() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Matrix4x4 m_mWorldViewProjection;	/**< The world view projection matrix used for rendering */
		PLMath::Matrix4x4 m_mWorldViewInverse;		/**< The inverse world view matrix used for rendering */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer		 *m_pRenderer;			/**< The used PixelLight renderer */
		bool						  m_bBlendingEnabled;	/**< 'true' if blending is enabled, 'false' if it is disabled */
		PLRenderer::BlendFunc::Enum   m_nSrcBlending;		/**< The source blending function of this SPK_PLRenderer */
		PLRenderer::BlendFunc::Enum   m_nDestBlending;		/**< The destination blending function of this SPK_PLRenderer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLRenderer.inl"


#endif	// __SPARK_PL_RENDERER_H__
