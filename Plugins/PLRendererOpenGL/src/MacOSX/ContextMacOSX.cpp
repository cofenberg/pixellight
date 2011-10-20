/*********************************************************\
 *  File: ContextMacOSX.h                                *
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
#include "PLRendererOpenGL/MacOSX/ContextMacOSX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ContextMacOSX::ContextMacOSX(Renderer &cRenderer) :
	m_pRenderer(&cRenderer)
{
	// [TODO] Implement me
}

/**
*  @brief
*    Destructor
*/
ContextMacOSX::~ContextMacOSX()
{
	// [TODO] Implement me
}


//[-------------------------------------------------------]
//[ Public virtual Context methods                        ]
//[-------------------------------------------------------]
bool ContextMacOSX::IsValid() const
{
	// [TODO] Implement me
	return false;
}

void ContextMacOSX::MakeDummyCurrent() const
{
	// [TODO] Implement me
}

bool ContextMacOSX::QueryDisplayModes(Array<const PLRenderer::DisplayMode*> &lstDisplayModeList)
{
	// [TODO] Implement me
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
