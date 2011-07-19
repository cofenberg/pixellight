/*********************************************************\
 *  File: SurfaceTextureBuffer.h                         *
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


#ifndef __PLRENDERER_SURFACE_TEXTUREBUFFER_H__
#define __PLRENDERER_SURFACE_TEXTUREBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/TextureBuffer.h"
#include "PLRenderer/Renderer/Surface.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A texture buffer renderer surface where we can render in (RTT -> Render To Texture)
*/
class SurfaceTextureBuffer : public Surface {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Texture buffer surface flags
		*/
		enum EFlags {
			Depth                     = 1<<0,	/**< Depth buffer */
			Stencil                   = 1<<1,	/**< Stencil buffer */
			Mipmaps                   = 1<<2,	/**< Mipmaps (created "on the fly" by the GPU) */
			NoMultisampleAntialiasing = 1<<3	/**< Do not use multisample antialiasing */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~SurfaceTextureBuffer();

		/**
		*  @brief
		*    Returns the texture buffer format
		*
		*  @return
		*    The texture buffer format
		*/
		PLRENDERER_API TextureBuffer::EPixelFormat GetFormat() const;

		/**
		*  @brief
		*    Returns the texture buffer surface flags
		*
		*  @return
		*    The texture buffer surface flags (see EFlags)
		*/
		PLRENDERER_API PLCore::uint32 GetFlags() const;

		/**
		*  @brief
		*    Returns the maximum number of color render targets
		*
		*  @return
		*    The maximum number of color render targets
		*/
		PLRENDERER_API PLCore::uint8 GetMaxColorTargets() const;

		/**
		*  @brief
		*    Sets the maximum number of color render targets
		*
		*  @param[in] nMaxColorTargets
		*    The maximum number of color render targets
		*/
		PLRENDERER_API void SetMaxColorTargets(PLCore::uint8 nMaxColorTargets);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the renderer texture buffer this surface will render in
		*
		*  @return
		*    The renderer texture buffer this surface will render in, can be a null pointer
		*
		*  @note
		*    - If you currently render into the texture buffer it can't be used for texturing!
		*/
		virtual PLRenderer::TextureBuffer *GetTextureBuffer() const = 0;

		/**
		*  @brief
		*    Returns the current renderer texture buffer face this surface will render in
		*
		*  @return
		*    The current renderer texture buffer face this surface will render in
		*
		*  @note
		*    - Only valid if the target texture buffer is a cube map!
		*
		*  @see
		*    - 'TextureBufferCube.h' for more information about cube maps
		*/
		virtual PLCore::uint8 GetTextureBufferFace() const = 0;

		/**
		*  @brief
		*    Takes over the control of the depth buffer of the given surface texture buffer
		*
		*  @param[in] cSurfaceTextureBuffer
		*    Surface texture buffer we take the depth buffer away
		*/
		virtual void TakeDepthBufferFromSurfaceTextureBuffer(SurfaceTextureBuffer &cSurfaceTextureBuffer) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nFlags
		*    Texture buffer surface flags (see EFlags)
		*  @param[in] nMaxColorTargets
		*    Maximum number of color render targets. This must be at least 1 - main renderer
		*    target color.
		*/
		PLRENDERER_API SurfaceTextureBuffer(Renderer &cRenderer, PLCore::uint32 nFlags = Depth | Stencil, PLCore::uint8 nMaxColorTargets = 1);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::uint32 m_nFlags;			/**< Texture buffer surface flags (see EFlags) */
		PLCore::uint8  m_nMaxColorTargets;	/**< Maximum number of color render targets */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		SurfaceTextureBuffer(const SurfaceTextureBuffer &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		SurfaceTextureBuffer &operator =(const SurfaceTextureBuffer &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SURFACE_TEXTUREBUFFER_H__
