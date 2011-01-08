/*********************************************************\
 *  File: SRPFunctionsPost.h                             *
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


#ifndef __PLCOMPOSITING_FUNCTIONSPOST_H__
#define __PLCOMPOSITING_FUNCTIONSPOST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCompositing/SRPFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass calling all 'post'-draw functions
*
*  @note
*    - Doesn't use directly shaders or fixed functions features, therefore there's usually no need to derive from this class
*/
class SRPFunctionsPost : public SRPFunctions {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPFunctionsPost, "PLCompositing", PLCompositing::SRPFunctions, "Scene renderer pass calling all 'post'-draw functions")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPFunctionsPost();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPFunctionsPost();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Draws recursive
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*/
		void DrawRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery) const;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_FUNCTIONSPOST_H__
