/*********************************************************\
 *  File: GraphicsPL.h                                   *
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


#ifndef __PLSCENE_SCENENODE_GUI_GRAPHICS_H__
#define __PLSCENE_SCENENODE_GUI_GRAPHICS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include <PLGui/Backend/GraphicsImpl.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight ingame GUI graphics implementation
*/
class GraphicsPL : public PLGui::GraphicsImpl {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] vAbsPos
		*    Absolute widget position
		*  @param[in] vScreenSize
		*    Screen size
		*  @param[in] nTransparency
		*    Transparency mode (see ETransparency)
		*  @param[in] cTransparencyColor
		*    If nMode is ColorKey, all pixels of the specified color will be transparent.
		*    If nMode is Alpha, only the alpha channel of the color will be used (1.0 = opaque, 0.0 = transparent)
		*/
		PLS_API GraphicsPL(PLRenderer::Renderer &cRenderer, const PLMath::Vector2i &vAbsPos, const PLMath::Vector2i &vScreenSize, PLGui::ETransparency nTransparency, const PLGraphics::Color4 &cTransparencyColor);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGraphics
		*    Reference to platform independent graphics
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] vAbsPos
		*    Absolute widget position
		*  @param[in] nTransparency
		*    Transparency mode (see ETransparency)
		*  @param[in] cTransparencyColor
		*    If nMode is ColorKey, all pixels of the specified color will be transparent.
		*    If nMode is Alpha, only the alpha channel of the color will be used (1.0 = opaque, 0.0 = transparent)
		*/
		PLS_API GraphicsPL(PLGui::Graphics &cGraphics, PLRenderer::Renderer &cRenderer, const PLMath::Vector2i &vAbsPos, PLGui::ETransparency nTransparency, const PLGraphics::Color4 &cTransparencyColor);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~GraphicsPL();


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::GraphicsImpl functions          ]
	//[-------------------------------------------------------]
	public:
		virtual void DrawLine(const PLGraphics::Color4 &cColor, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLGeneral::uint32 nWidth = 1);
		virtual void DrawRect(const PLGraphics::Color4 &cColor, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLGeneral::uint32 nRoundX = 0, PLGeneral::uint32 nRoundY = 0, PLGeneral::uint32 nWidth = 1);
		virtual void DrawBox(const PLGraphics::Color4 &cColor, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLGeneral::uint32 nRoundX = 0, PLGeneral::uint32 nRoundY = 0);
		virtual void DrawGradientBox(const PLGraphics::Color4 &cColor1, const PLGraphics::Color4 &cColor2, float fAngle, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2);
		virtual void DrawImage(const PLGui::Image &cImage, const PLMath::Vector2i &vPos, const PLMath::Vector2i &vSize);
		virtual void DrawText(const PLGui::Font &cFont, const PLGraphics::Color4 &cTextColor, const PLGraphics::Color4 &cBkColor, const PLMath::Vector2i &vPos, const PLGeneral::String &sText);
		virtual PLGeneral::uint32 GetTextWidth(const PLGui::Font &cFont, const PLGeneral::String &sText);
		virtual PLGeneral::uint32 GetTextHeight(const PLGui::Font &cFont, const PLGeneral::String &sText);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer *m_pRenderer;			/**< The used renderer, always valid! */
		PLMath::Vector2i	  m_vAbsPos;			/**< Absolute widget position */
		PLMath::Vector2i	  m_vScreenSize;		/**< Screen size */
		PLGui::ETransparency  m_nTransparency;		/**< Widget transparency type */
		PLGraphics::Color4	  m_cTransparencyColor;	/**< Widget color */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GUI_GRAPHICS_H__
