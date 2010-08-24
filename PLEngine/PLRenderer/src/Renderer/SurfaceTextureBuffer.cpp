/*********************************************************\
 *  File: SurfaceTextureBuffer.h                         *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/SurfaceTextureBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SurfaceTextureBuffer::~SurfaceTextureBuffer()
{
}

/**
*  @brief
*    Returns the texture buffer format
*/
TextureBuffer::EPixelFormat SurfaceTextureBuffer::GetFormat() const
{
	const PLRenderer::TextureBuffer *pTextureBuffer = GetTextureBuffer();
	return pTextureBuffer ? pTextureBuffer->GetFormat() : TextureBuffer::Unknown;
}

/**
*  @brief
*    Returns the texture buffer surface flags
*/
uint32 SurfaceTextureBuffer::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Returns the maximum number of color render targets
*/
uint8 SurfaceTextureBuffer::GetMaxColorTargets() const
{
	return m_nMaxColorTargets;
}

/**
*  @brief
*    Sets the maximum number of color render targets
*/
void SurfaceTextureBuffer::SetMaxColorTargets(uint8 nMaxColorTargets)
{
	m_nMaxColorTargets = nMaxColorTargets;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SurfaceTextureBuffer::SurfaceTextureBuffer(Renderer &cRenderer, uint32 nFlags, uint8 nMaxColorTargets) : Surface(cRenderer, TextureBuffer),
	m_nFlags(nFlags),
	m_nMaxColorTargets(nMaxColorTargets)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
SurfaceTextureBuffer::SurfaceTextureBuffer(const SurfaceTextureBuffer &cSource) : Surface(cSource.GetRenderer(), cSource.GetType()),
	m_nFlags(cSource.GetFlags()),
	m_nMaxColorTargets(cSource.GetMaxColorTargets())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
SurfaceTextureBuffer &SurfaceTextureBuffer::operator =(const SurfaceTextureBuffer &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
