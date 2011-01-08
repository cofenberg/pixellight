/*********************************************************\
 *  File: SPEffectPreview.h                              *
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


#ifndef __PLRENDERER_EFFECT_SURFACEPAINTER_H__
#define __PLRENDERER_EFFECT_SURFACEPAINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/SPPreview.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Effect preview surface painter class
*/
class SPEffectPreview : public SPPreview {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, SPEffectPreview, "PLRenderer", PLRenderer::SPPreview, "Effect preview surface painter class")
		pl_constructor_1(ParameterConstructor, Renderer&, "Parameter constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		PLRENDERER_API SPEffectPreview(Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~SPEffectPreview();

		/**
		*  @brief
		*    Returns the name of the used effect
		*
		*  @return
		*    Name of the used effect
		*/
		PLRENDERER_API PLGeneral::String GetEffect() const;

		/**
		*  @brief
		*    Sets the name of the used effect
		*
		*  @param[in] sName
		*    Name of the used effect
		*/
		PLRENDERER_API void SetEffect(const PLGeneral::String &sName);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sEffect;	/**< Name of the used effect */


	//[-------------------------------------------------------]
	//[ Private virtual SurfacePainter functions              ]
	//[-------------------------------------------------------]
	private:
		virtual void OnPaint(Surface &cSurface);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_EFFECT_SURFACEPAINTER_H__
