/*********************************************************\
 *  File: GraphicsNull.cpp                               *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Backend/Null/GraphicsNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
GraphicsNull::GraphicsNull(Graphics &cGraphics) : GraphicsImpl(cGraphics)
{
}

/**
*  @brief
*    Destructor
*/
GraphicsNull::~GraphicsNull()
{
}


//[-------------------------------------------------------]
//[ Public virtual GraphicsImpl functions                 ]
//[-------------------------------------------------------]
void GraphicsNull::DrawLine(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nWidth)
{
	// Not implemented
}

void GraphicsNull::DrawRect(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nRoundX, uint32 nRoundY, uint32 nWidth)
{
	// Not implemented
}

void GraphicsNull::DrawBox(const Color4 &cColor, const Vector2i &vPos1, const Vector2i &vPos2, uint32 nRoundX, uint32 nRoundY)
{
	// Not implemented
}

void GraphicsNull::DrawGradientBox(const Color4 &cColor1, const Color4 &cColor2, float fAngle, const Vector2i &vPos1, const Vector2i &vPos2)
{
	// Not implemented
}

void GraphicsNull::DrawImage(const Image &cImage, const Vector2i &vPos, const Vector2i &vSize)
{
	// Not implemented
}

void GraphicsNull::DrawText(const Font &cFont, const Color4 &cTextColor, const Color4 &cBkColor, const Vector2i &vPos, const String &sText)
{
	// Not implemented
}

uint32 GraphicsNull::GetTextWidth(const Font &cFont, const String &sText)
{
	// Not implemented
	return 0;
}

uint32 GraphicsNull::GetTextHeight(const Font &cFont, const String &sText)
{
	// Not implemented
	return 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
