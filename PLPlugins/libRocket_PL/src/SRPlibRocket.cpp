/*********************************************************\
 *  File: SRPlibRocket.cpp                               *
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
#include <Rocket/Core.h>
#include "libRocket_PL/RenderInterfacePL.h"
#include "libRocket_PL/SRPlibRocket.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLRenderer;
using namespace PLScene;
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPlibRocket)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SRPlibRocket::SRPlibRocket(Rocket::Core::Context &cRocketContext, RenderInterfacePL &cRenderInterfacePL) :
	m_pRocketContext(&cRocketContext),
	m_pRenderInterfacePL(&cRenderInterfacePL)
{
}

/**
*  @brief
*    Destructor
*/
SRPlibRocket::~SRPlibRocket()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPlibRocket::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Update libRocket
	m_pRocketContext->Update();

	// Configures PixelLight's rendering system for rendering Rocket
	if (m_pRenderInterfacePL->ConfigureRenderSystem()) {
		// Render libRocket
		m_pRocketContext->Render();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL
