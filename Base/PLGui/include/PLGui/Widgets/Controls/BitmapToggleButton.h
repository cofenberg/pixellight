/*********************************************************\
 *  File: BitmapToggleButton.h                           *
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


#ifndef __PLGUI_BITMAPTOGGLEBUTTON_H__
#define __PLGUI_BITMAPTOGGLEBUTTON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Widgets/Base/AbstractToggleButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A toggle button that displays images for each state
*/
class BitmapToggleButton : public AbstractToggleButton {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, BitmapToggleButton, "PLGui", PLGui::AbstractToggleButton, "A toggle button that displays images for each state")
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
		PLGUI_API BitmapToggleButton(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~BitmapToggleButton();

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
		*    Get image for unselected state
		*
		*  @param[in] nChecked
		*    Check-state for which to set the image
		*
		*  @return
		*    Image that is displayed when the button is not selected
		*/
		PLGUI_API const Image &GetImageUnselected(ECheckState nChecked) const;

		/**
		*  @brief
		*    Set image for unselected state
		*
		*  @param[in] nChecked
		*    Check-state for which to set the image
		*  @param[in] cImage
		*    Image that is displayed when the button is not selected
		*/
		PLGUI_API void SetImageUnselected(ECheckState nChecked, const Image &cImage);

		/**
		*  @brief
		*    Get image for selected state
		*
		*  @param[in] nChecked
		*    Check-state for which to set the image
		*
		*  @return
		*    Image that is displayed when the button is selected
		*/
		PLGUI_API const Image &GetImageSelected(ECheckState nChecked) const;

		/**
		*  @brief
		*    Set image for selected state
		*
		*  @param[in] nChecked
		*    Check-state for which to set the image
		*  @param[in] cImage
		*    Image that is displayed when the button is selected
		*/
		PLGUI_API void SetImageSelected(ECheckState nChecked, const Image &cImage);


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
		Image m_cImageDisabled;					/**< Image that is displayed when the butten is disabled */
		Image m_cImageNotChecked;				/**< Image that is displayed when the butten is not checked */
		Image m_cImageChecked;					/**< Image that is displayed when the butten is checked */
		Image m_cImagePartiallyChecked;			/**< Image that is displayed when the butten is partially checked */
		Image m_cImageSelectedNotChecked;		/**< Image that is displayed when the butten is selected and not checked */
		Image m_cImageSelectedChecked;			/**< Image that is displayed when the butten is selected and checked */
		Image m_cImageSelectedPartiallyChecked;	/**< Image that is displayed when the butten is selected and partially checked */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_BITMAPTOGGLEBUTTON_H__
