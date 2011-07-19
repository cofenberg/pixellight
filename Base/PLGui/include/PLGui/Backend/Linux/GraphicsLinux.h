/*********************************************************\
 *  File: GraphicsLinux.h                                *
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


#ifndef __PLGUI_GRAPHICSLINUX_H__
#define __PLGUI_GRAPHICSLINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Backend/GraphicsImpl.h"
#include "PLGui/PLGuiLinuxIncludes.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux graphics implementation
*/
class GraphicsLinux : public GraphicsImpl {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pDisplay
		*    Pointer to X Display
		*  @param[in] nScreen
		*    Index of screen
		*  @param[in] nWindow
		*    System window handle
		*/
		PLGUI_API GraphicsLinux(::Display *pDisplay, int nScreen, ::Window nWindow);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGraphics
		*    Reference to platform independent graphics
		*/
		PLGUI_API GraphicsLinux(Graphics &cGraphics);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~GraphicsLinux();


	//[-------------------------------------------------------]
	//[ Public virtual GraphicsImpl functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual void DrawLine(const PLGraphics::Color4 &cColor, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLCore::uint32 nWidth = 1);
		virtual void DrawRect(const PLGraphics::Color4 &cColor, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLCore::uint32 nRoundX = 0, PLCore::uint32 nRoundY = 0, PLCore::uint32 nWidth = 1);
		virtual void DrawBox(const PLGraphics::Color4 &cColor, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2, PLCore::uint32 nRoundX = 0, PLCore::uint32 nRoundY = 0);
		virtual void DrawGradientBox(const PLGraphics::Color4 &cColor1, const PLGraphics::Color4 &cColor2, float fAngle, const PLMath::Vector2i &vPos1, const PLMath::Vector2i &vPos2);
		virtual void DrawImage(const Image &cImage, const PLMath::Vector2i &vPos, const PLMath::Vector2i &vSize);
		virtual void DrawText(const Font &cFont, const PLGraphics::Color4 &cTextColor, const PLGraphics::Color4 &cBkColor, const PLMath::Vector2i &vPos, const PLCore::String &sText);
		virtual PLCore::uint32 GetTextWidth(const Font &cFont, const PLCore::String &sText);
		virtual PLCore::uint32 GetTextHeight(const Font &cFont, const PLCore::String &sText);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		::Display	*m_pDisplay;	/**< X Display */
		int			 m_nScreen;		/**< X screen */
		::Window	 m_nWindow;		/**< Window that is used */
		int			 m_nColorDepth; /**< Color depth (e.g. 16 or 24) */
		::GC		 m_sGC;			/**< Graphics context */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GRAPHICSLINUX_H__
