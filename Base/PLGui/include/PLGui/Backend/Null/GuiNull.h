/*********************************************************\
 *  File: GuiNull.h                                      *
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


#ifndef __PLGUI_GUINULL_H__
#define __PLGUI_GUINULL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Backend/GuiImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null GUI implementation
*/
class GuiNull : public GuiImpl {

	
	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pGui
		*    Platform independent GUI
		*/
		PLGUI_API GuiNull(Gui *pGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~GuiNull();


	//[-------------------------------------------------------]
	//[ Public virtual GuiImpl functions                      ]
	//[-------------------------------------------------------]
	public:
		virtual bool HasPendingMessages() override;
		virtual void ProcessMessage() override;
		virtual void PostMessage(const GuiMessage &cMessage) override;
		virtual void EnumerateScreens(PLCore::List<Screen*> &lstScreens) override;
		virtual PLMath::Vector2i GetScreenSize() const override;
		virtual bool HasTaskbar() override;
		virtual void SetMouseVisible(bool bVisible) override;
		virtual void ListFonts(PLCore::List<FontInfo> &lstFonts) const override;
		virtual WidgetImpl *CreateWidgetImpl(Widget &cWidget) const override;
		virtual GraphicsImpl *CreateGraphicsImpl(Graphics &cGraphics) const override;
		virtual ImageImpl *CreateImageImpl(Image &cImage) const override;
		virtual FontImpl *CreateFontImpl(Font &cFont) const override;
		virtual CursorImpl *CreateCursorImpl(Cursor &cCursor) const override;
		virtual TrayIconImpl *CreateTrayIconImpl(TrayIcon &cTrayIcon) const override;
		virtual ClipBoardImpl *CreateClipBoardImpl(ClipBoard &cClipBoard) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GUINULL_H__
