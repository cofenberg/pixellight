/*********************************************************\
 *  File: BitmapButton.h                                 *
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


#ifndef __PLGUI_BITMAPBUTTON_H__
#define __PLGUI_BITMAPBUTTON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Widgets/Base/AbstractButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A button that displays images for each state
*/
class BitmapButton : public AbstractButton {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, BitmapButton, "PLGui", PLGui::AbstractButton, "A button that displays images for each state")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// [TODO] Images...
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Pointer to the parent widget
		*/
		PLGUI_API BitmapButton(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~BitmapButton();

		/**
		*  @brief
		*    Get image for enabled-state
		*
		*  @return
		*    Image that is displayed when the button is enabled
		*/
		PLGUI_API const Image &GetImageEnabled() const;

		/**
		*  @brief
		*    Set image for enabled-state
		*
		*  @param[in] cImage
		*    Image that is displayed when the button is enabled
		*/
		PLGUI_API void SetImageEnabled(const Image &cImage);

		/**
		*  @brief
		*    Get image for disabled-state
		*
		*  @return
		*    Image that is displayed when the button is disabled
		*/
		PLGUI_API const Image &GetImageDisabled() const;

		/**
		*  @brief
		*    Set image for disabled-state
		*
		*  @param[in] cImage
		*    Image that is displayed when the button is disabled
		*/
		PLGUI_API void SetImageDisabled(const Image &cImage);

		/**
		*  @brief
		*    Get image for selected-state
		*
		*  @return
		*    Image that is displayed when the button is selected
		*/
		PLGUI_API const Image &GetImageSelected() const;

		/**
		*  @brief
		*    Set image for selected-state
		*
		*  @param[in] cImage
		*    Image that is displayed when the button is selected
		*/
		PLGUI_API void SetImageSelected(const Image &cImage);

		/**
		*  @brief
		*    Get image for pressed-state
		*
		*  @return
		*    Image that is displayed when the button is pressed
		*/
		PLGUI_API const Image &GetImagePressed() const;

		/**
		*  @brief
		*    Set image for pressed-state
		*
		*  @param[in] cImage
		*    Image that is displayed when the button is pressed
		*/
		PLGUI_API void SetImagePressed(const Image &cImage);


	//[-------------------------------------------------------]
	//[ Private virtual Widget functions                      ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual PLMath::Vector2i OnPreferredSize(const PLMath::Vector2i &vRefSize) const override;
		PLGUI_API virtual void OnDraw(Graphics &cGraphics) override;
		PLGUI_API virtual void OnMouseEnter() override;
		PLGUI_API virtual void OnMouseLeave() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Image m_cImageEnabled;	/**< Image that is displayed when the button is enabled */
		Image m_cImageDisabled;	/**< Image that is displayed when the button is disabled */
		Image m_cImageSelected;	/**< Image that is displayed when the button is selected by the mouse */
		Image m_cImagePressed;	/**< Image that is displayed when the button is pressed */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_BITMAPBUTTON_H__
