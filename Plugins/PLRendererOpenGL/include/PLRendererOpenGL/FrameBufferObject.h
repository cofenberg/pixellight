/*********************************************************\
 *  File: FrameBufferObject.h                            *
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


#ifndef __PLRENDEREROPENGL_FRAMEBUFFEROBJECT_H__
#define __PLRENDEREROPENGL_FRAMEBUFFEROBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include <PLRenderer/Renderer/TextureBuffer.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class TextureBufferBuffer;
class Renderer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Frame buffer object
*/
class FrameBufferObject {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Frame buffer flags
		*/
		enum EFlags {
			Color   = 1<<0,	/**< Color buffer */
			Depth16 = 1<<1,	/**< 16 bit depth buffer */
			Depth24 = 1<<2,	/**< 24 bit depth buffer */
			Depth32 = 1<<3,	/**< 32 bit depth buffer */
			Stencil = 1<<4	/**< Stencil buffer */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		FrameBufferObject();

		/**
		*  @brief
		*    Destructor
		*/
		~FrameBufferObject();

		/**
		*  @brief
		*    Initializes the frame buffer object
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] vSize
		*    Frame buffer size
		*  @param[in] nFormat
		*    Frame buffer format
		*  @param[in] bNoMultisampleAntialiasing
		*    Do not use multisample antialiasing
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Initialize(Renderer &cRenderer, const PLMath::Vector2i &vSize, PLCore::uint32 nFormat, PLRenderer::TextureBuffer::EPixelFormat nTextureFormat, bool bNoMultisampleAntialiasing);

		/**
		*  @brief
		*    Switches the texture buffer target
		*
		*  @param[in] cTextureBuffer
		*    Target texture buffer
		*  @param[in] nAttachIndex
		*    Color attachment index
		*  @param[in] nFace
		*    Cube map face to render in
		*/
		void SwitchTarget(PLRenderer::TextureBuffer &cTextureBuffer, PLCore::uint32 nAttachIndex = 0, PLCore::uint8 nFace = 0);

		/**
		*  @brief
		*    Binds the frame buffer
		*/
		void Bind();

		/**
		*  @brief
		*    Finishes the process
		*/
		void Finish();

		/**
		*  @brief
		*    Unbinds the frame buffer
		*/
		void Unbind();

		/**
		*  @brief
		*    Returns the size of the frame buffer
		*
		*  @return
		*    Size of the frame buffer
		*/
		const PLMath::Vector2i &GetSize() const;

		/**
		*  @brief
		*    Takes over the control of the depth buffer of the given FBO
		*
		*  @param[in] cFBO
		*    FBO we take the depth buffer away
		*/
		void TakeDepthBufferFromFBO(FrameBufferObject &cFBO);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Checks the frame buffer
		*
		*  @return
		*    'true' if all is ok, else 'false'
		*/
		bool CheckFrameBufferStatus() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector2i m_vSize;
		GLuint			 m_nFrameBufferIndex;
		GLuint			 m_nMultisampleFrameBufferIndex;
		GLuint			 m_nColorBufferIndex;
		GLuint			 m_nDepthBufferIndex;
		GLuint			 m_nStencilBufferIndex;
		GLuint			 m_nDepthBufferAttachment;	/**< Depth buffer attachment (GL_DEPTH_ATTACHMENT_EXT or GL_DEPTH_STENCIL_ATTACHMENT) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_FRAMEBUFFEROBJECT_H__
