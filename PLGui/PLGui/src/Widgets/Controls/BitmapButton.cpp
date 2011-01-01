/*********************************************************\
 *  File: BitmapButton.cpp                               *
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
#include "PLGui/Widgets/Controls/BitmapButton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLGraphics;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(BitmapButton)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BitmapButton::BitmapButton(Widget *pParent) : AbstractButton(pParent),
	m_cImageEnabled(*GetGui()),
	m_cImageDisabled(*GetGui()),
	m_cImageSelected(*GetGui()),
	m_cImagePressed(*GetGui())
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
BitmapButton::~BitmapButton()
{
}

/**
*  @brief
*    Get image for enabled-state
*/
const Image &BitmapButton::GetImageEnabled() const
{
	// Return image
	return m_cImageEnabled;
}

/**
*  @brief
*    Set image for enabled-state
*/
void BitmapButton::SetImageEnabled(const Image &cImage)
{
	// Set image
	m_cImageEnabled = cImage;
}

/**
*  @brief
*    Get image for disabled-state
*/
const Image &BitmapButton::GetImageDisabled() const
{
	// Return image
	return m_cImageDisabled;
}

/**
*  @brief
*    Set image for disabled-state
*/
void BitmapButton::SetImageDisabled(const Image &cImage)
{
	// Set image
	m_cImageDisabled = cImage;
}


/**
*  @brief
*    Get image for selected-state
*/
const Image &BitmapButton::GetImageSelected() const
{
	// Return image
	return m_cImageSelected;
}

/**
*  @brief
*    Set image for selected-state
*/
void BitmapButton::SetImageSelected(const Image &cImage)
{
	// Set image
	m_cImageSelected = cImage;
}


/**
*  @brief
*    Get image for pressed-state
*/
const Image &BitmapButton::GetImagePressed() const
{
	// Return image
	return m_cImagePressed;
}

/**
*  @brief
*    Set image for pressed-state
*/
void BitmapButton::SetImagePressed(const Image &cImage)
{
	// Set image
	m_cImagePressed = cImage;
}



//[-------------------------------------------------------]
//[ Public virtual Widget functions                       ]
//[-------------------------------------------------------]
Vector2i BitmapButton::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Call base function
	AbstractButton::OnPreferredSize(vRefSize);

	// Return image size
	return m_cImage.GetSize();
}

void BitmapButton::OnDraw(Graphics &cGraphics)
{
	// Call base implementation
	AbstractButton::OnDraw(cGraphics);

	// Draw button
	Image *pImage = NULL;
		 if (!IsEnabled())	pImage = &m_cImageDisabled;
	else if (m_bPressed)	pImage = &m_cImagePressed;
	else if (m_bMouseIn)	pImage = &m_cImageSelected;
	else					pImage = &m_cImageEnabled;
	cGraphics.DrawImage(*pImage, Vector2i::Zero, pImage->GetSize() - Vector2i(1, 1));
}

void BitmapButton::OnMouseEnter()
{
	// Call base function
	AbstractButton::OnMouseEnter();

	// Redraw button
	Redraw();
}

void BitmapButton::OnMouseLeave()
{
	// Call base function
	AbstractButton::OnMouseLeave();

	// Redraw button
	Redraw();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
