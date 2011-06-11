/*********************************************************\
 *  File: SRPlibRocket.h                                 *
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


#ifndef __LIBROCKET_PL_SCENERENDERERPASS_H__
#define __LIBROCKET_PL_SCENERENDERERPASS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Compositing/SceneRendererPass.h>
#include "libRocket_PL/libRocket_PL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace Rocket {
	namespace Core {
		class Context;
	}
}
namespace libRocket_PL {
	class RenderInterfacePL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    libRocket scene renderer pass
*/
class SRPlibRocket : public PLScene::SceneRendererPass {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(LIBROCKET_PL_RTTI_EXPORT, SRPlibRocket, "libRocket_PL", PLScene::SceneRendererPass, "libRocket scene renderer pass")
		// Constructors
		pl_constructor_2(ParameterConstructor,	Rocket::Core::Context&,	RenderInterfacePL&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRocketContext
		*    libRocket context to use, just shared, must stay valid as long as this scene renderer pass lives
		*  @param[in] cRenderInterfacePL
		*    Render interface for Rocket into PixelLight, just shared, must stay valid as long as this scene renderer pass lives
		*/
		LIBROCKET_PL_API SRPlibRocket(Rocket::Core::Context &cRocketContext, RenderInterfacePL &cRenderInterfacePL);

		/**
		*  @brief
		*    Destructur
		*/
		LIBROCKET_PL_API virtual ~SRPlibRocket();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Rocket::Core::Context *m_pRocketContext;		/**< libRocket context, always valid! */
		RenderInterfacePL	  *m_pRenderInterfacePL;	/**< Render interface for Rocket into PixelLight, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL


#endif // __LIBROCKET_PL_SCENERENDERERPASS_H__
