/*********************************************************\
 *  File: Application55.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/RendererContext.h>
#include "Application55.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Application55)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application55::Application55(Frontend &cFrontend) : RendererApplication(cFrontend)
{
}

/**
*  @brief
*    Destructor
*/
Application55::~Application55()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::RendererApplication functions ]
//[-------------------------------------------------------]
void Application55::OnCreatePainter()
{
	// Get the renderer context instance
	RendererContext *pRendererContext = GetRendererContext();
	if (pRendererContext) {
		// Set the surface painter to use depending on whether or not there's a default shader language within the used renderer
		const bool bShaders = (pRendererContext->GetRenderer().GetDefaultShaderLanguage().GetLength() != 0);

		// Create and set the surface painter - no fixed functions possible in here
		SetPainter(pRendererContext->GetRenderer().CreateSurfacePainter(bShaders ? "SPTessellationShaders" : ""));
	}
}
