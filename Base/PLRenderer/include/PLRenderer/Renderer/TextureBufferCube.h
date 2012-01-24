/*********************************************************\
 *  File: TextureBufferCube.h                            *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDERER_TEXTUREBUFFERCUBE_H__
#define __PLRENDERER_TEXTUREBUFFERCUBE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
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
*    Abstract renderer cube texture buffer resource
*
*  @remarks
*    The order of the cube map faces is: x-positive (0, left), x-negative (1, right),
*    y-positive (2, top), y-negative (3, bottom), z-positive (4, back), z-negative (5, front)
*
*    @code
*    Texture buffer faces:
*            ----------
*            | Top    |
*            | + Y    |
*    -----------------------------------
*    | Left  | Front  | Right  | Back  |
*    | + X   | - Z    | - X    | + Z   |
*    -----------------------------------
*            | Bottom |
*            | - Y    |
*            ----------
*
*    Coordinate system:
*                     +y (top)
*                      |
*                      |  -z (front)
*                      |  /
*                      | /
*    -x (right) _______|/_______ +x (left)
*                     /|
*                    / |
*                   /  |
*           +z (back)  |
*                     -y (bottom)
*    @endcode
*/
class TextureBufferCube : public TextureBuffer {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureBufferCube();

		/**
		*  @brief
		*    Returns the texture buffer size
		*
		*  @param[in] nMipmap
		*    Mipmap level (0 - GetNumOfMipmaps())
		*
		*  @return
		*    Texture buffer size
		*/
		PLRENDERER_API PLCore::uint32 GetSize(PLCore::uint32 nMipmap = 0) const;


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
		PLRENDERER_API TextureBufferCube(Renderer &cRenderer, PLCore::uint32 nFlags);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::uint32 m_nSize;	/**< Texture buffer size */


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
		TextureBufferCube(const TextureBufferCube &cSource);

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
		TextureBufferCube &operator =(const TextureBufferCube &cSource);


	//[-------------------------------------------------------]
	//[ Public virtual TextureBuffer functions                ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool IsPowerOfTwo() const override;
		PLRENDERER_API virtual PLCore::uint32 GetNumOfPixels(PLCore::uint32 nMipmap = 0) const override;
		PLRENDERER_API virtual PLCore::uint32 GetNumOfBytes(PLCore::uint32 nMipmap = 0, EPixelFormat nFormat = Unknown) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TEXTUREBUFFERCUBE_H__
