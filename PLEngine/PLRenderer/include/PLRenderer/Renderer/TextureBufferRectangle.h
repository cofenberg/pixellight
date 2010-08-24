/*********************************************************\
 *  File: TextureBufferRectangle.h                       *
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


#ifndef __PLRENDERER_TEXTUREBUFFERRECTANGLE_H__
#define __PLRENDERER_TEXTUREBUFFERRECTANGLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include "PLRenderer/Renderer/TextureBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer rectangle texture buffer resource
*
*  @remarks
*    The hardware texturing is limited to images with power-of-two dimensions and an optional
*    1-texel border. But there’s also an special kind of texture buffers called ’rectangle textures’ without
*    requiring power-of-two dimensions.\n
*    Non-power-of-two dimensioned texture buffers are useful for storing video images that do not
*    have power-of-two dimensions. Re-sampling artifacts are avoided and less texture buffer memory
*    may be required by using non-power-of-two dimensioned texture buffers. Non-power-of-two dimensioned
*    texture buffers are also useful for shadow maps and window-space texturing.\n
*    However, non-power-of-two dimensioned (NPOTD) texture buffers have limitations that do not
*    apply to power-of-two dimensioned (POT) texture buffers. NPOTD texture buffers may not use mipmap
*    filtering; POTD texture buffers support both mipmapped and non-mipmapped filtering. NPOTD
*    texture buffers support only the CLAMP, CLAMP TO EDGE, and CLAMP TO BORDER wrap
*    modes; POTD texture buffers support CLAMP TO EDGE, REPEAT, CLAMP, MIRRORED
*    REPEAT, and CLAMP TO BORDER. NPOTD texture buffers do not support an optional 1-
*    texel border; POTD texture buffers do support an optional 1-texel border.\n
*/
class TextureBufferRectangle : public TextureBuffer {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureBufferRectangle();

		/**
		*  @brief
		*    Returns the texture buffer size
		*
		*  @return
		*    Texture buffer size
		*/
		PLRENDERER_API PLMath::Vector2i GetSize() const;


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
		*    Texture buffer flags (see EFlags)
		*/
		PLRENDERER_API TextureBufferRectangle(Renderer &cRenderer, PLGeneral::uint32 nFlags);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLMath::Vector2i m_vSize;	/**< Texture buffer size */


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
		TextureBufferRectangle(const TextureBufferRectangle &cSource);

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
		TextureBufferRectangle &operator =(const TextureBufferRectangle &cSource);


	//[-------------------------------------------------------]
	//[ Public virtual TextureBuffer functions                ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual PLGeneral::uint32 GetNumOfPixels(PLGeneral::uint32 nMipmap = 0) const;
		PLRENDERER_API virtual PLGeneral::uint32 GetNumOfBytes(PLGeneral::uint32 nMipmap = 0, EPixelFormat nFormat = Unknown) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TEXTUREBUFFERRECTANGLE_H__
