/*********************************************************\
 *  File: BitmapToggleButton.cpp                         *
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
#include "PLGui/Gui/Resources/Graphics.h"
#include "PLGui/Widgets/Controls/BitmapToggleButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(BitmapToggleButton)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BitmapToggleButton::BitmapToggleButton(Widget *pParent) : AbstractToggleButton(pParent),
	m_cImageDisabled(*GetGui()),
	m_cImageNotChecked(*GetGui()),
	m_cImageChecked(*GetGui()),
	m_cImagePartiallyChecked(*GetGui()),
	m_cImageSelectedNotChecked(*GetGui()),
	m_cImageSelectedChecked(*GetGui()),
	m_cImageSelectedPartiallyChecked(*GetGui())
{
	// No background
	SetBackgroundColor(Color4::Transparent);

	// Accept focus
	SetFocusStyle(AcceptFocus);
}

/**
*  @brief
*    Destructor
*/
BitmapToggleButton::~BitmapToggleButton()
{
}

/**
*  @brief
*    Get image for disabled-state
*/
const Image &BitmapToggleButton::GetImageDisabled() const
{
	// Return image
	return m_cImageDisabled;
}

/**
*  @brief
*    Set image for disabled-state
*/
void BitmapToggleButton::SetImageDisabled(const Image &cImage)
{
	// Set image
	m_cImageDisabled = cImage;
}

/**
*  @brief
*    Get image for unselected state
*/
const Image &BitmapToggleButton::GetImageUnselected(ECheckState nChecked) const
{
	// Return image
		 if (nChecked == NotChecked) return m_cImageNotChecked;
	else if (nChecked == Checked)	 return m_cImageChecked;
	else							 return m_cImagePartiallyChecked;
}

/**
*  @brief
*    Set image for unselected state
*/
void BitmapToggleButton::SetImageUnselected(ECheckState nChecked, const Image &cImage)
{
	// Set image
		 if (nChecked == NotChecked) m_cImageNotChecked = cImage;
	else if (nChecked == Checked)	 m_cImageChecked = cImage;
	else							 m_cImagePartiallyChecked = cImage;
}

/**
*  @brief
*    Get image for selected state
*/
const Image &BitmapToggleButton::GetImageSelected(ECheckState nChecked) const
{
	// Return image
		 if (nChecked == NotChecked) return m_cImageSelectedNotChecked;
	else if (nChecked == Checked)	 return m_cImageSelectedChecked;
	else							 return m_cImageSelectedPartiallyChecked;
}

/**
*  @brief
*    Set image for selected state
*/
void BitmapToggleButton::SetImageSelected(ECheckState nChecked, const Image &cImage)
{
	// Set image
		 if (nChecked == NotChecked) m_cImageSelectedNotChecked = cImage;
	else if (nChecked == Checked)	 m_cImageSelectedChecked = cImage;
	else							 m_cImageSelectedPartiallyChecked = cImage;
}


//[-------------------------------------------------------]
//[ Public virtual Widget functions                       ]
//[-------------------------------------------------------]
Vector2i BitmapToggleButton::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Call base function
	AbstractButton::OnPreferredSize(vRefSize);

	// Return image size
	return m_cImage.GetSize();
}

void BitmapToggleButton::OnDraw(Graphics &cGraphics)
{
	// Call base implementation
	AbstractToggleButton::OnDraw(cGraphics);

	// Draw button
	Image *pImage = nullptr;
	if (!IsEnabled()) {
		pImage = &m_cImageDisabled;
	} else if (m_bMouseIn) {
			 if (m_nState == NotChecked)		pImage = &m_cImageSelectedNotChecked;
		else if (m_nState == Checked)			pImage = &m_cImageSelectedChecked;
		else if (m_nState == PartiallyChecked)	pImage = &m_cImageSelectedPartiallyChecked;
	} else {
			 if (m_nState == NotChecked)		pImage = &m_cImageNotChecked;
		else if (m_nState == Checked)			pImage = &m_cImageChecked;
		else if (m_nState == PartiallyChecked)	pImage = &m_cImagePartiallyChecked;
	}
	cGraphics.DrawImage(*pImage, Vector2i::Zero, pImage->GetSize() - Vector2i(1, 1));
}

void BitmapToggleButton::OnMouseEnter()
{
	// Call base function
	AbstractToggleButton::OnMouseEnter();

	// Redraw button
	Redraw();
}

void BitmapToggleButton::OnMouseLeave()
{
	// Call base function
	AbstractToggleButton::OnMouseLeave();

	// Redraw button
	Redraw();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
