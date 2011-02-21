/*********************************************************\
 *  File: SPK_PLRenderer.h                               *
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


#ifndef __SPARK_PL_RENDERER_H__
#define __SPARK_PL_RENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/Types.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <Core/SPK_Renderer.h>
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


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void setBlending(SPK::BlendingMode blendMode);


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

		/**
		*  @brief
		*    Inits the rendering hints of this SPK_PLRenderer
		*/
		SPARK_PL_API void InitRenderingHints() const;


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
#include "SPARK_PL/RenderingAPI/SPK_PLRenderer.inl"


#endif	// __SPARK_PL_RENDERER_H__
