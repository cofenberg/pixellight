/*********************************************************\
 *  File: Bitmap.cpp                                     *
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
#include "PLGui/Gui/Resources/Image.h"
#include "PLGui/Gui/Resources/Graphics.h"
#include "PLGui/Widgets/Controls/Bitmap.h"


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
pl_implement_class(Bitmap)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Bitmap::Bitmap(Widget *pParent) : Widget(pParent),
	ImageName(this),
	m_cImage(*GetGui())
{
	// Don't accept keyboard focus
	SetFocusStyle(NoFocus);
}

/**
*  @brief
*    Destructor
*/
Bitmap::~Bitmap()
{
}

/**
*  @brief
*    Get image
*/
const Image &Bitmap::GetImage() const
{
	// Return font
	return m_cImage;
}

/**
*  @brief
*    Set image
*/
void Bitmap::SetImage(const Image &cImage)
{
	// Set image
	m_cImage = cImage;

	// Update widget
	UpdateContent();

	// Redraw
	Redraw();
}

/**
*  @brief
*    Get image filename
*/
String Bitmap::GetImageName() const
{
	// Return image filename
	return m_cImage.GetFilename();
}

/**
*  @brief
*    Set image filename
*/
void Bitmap::SetImageName(const String &sImage)
{
	// Load image
	SetImage(Image(*GetGui(), sImage));
}


//[-------------------------------------------------------]
//[ Private virtual Widget functions                      ]
//[-------------------------------------------------------]
PLMath::Vector2i Bitmap::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Call base function
	Widget::OnPreferredSize(vRefSize);

	// Is a valid image set?
	if (!m_cImage.IsEmpty())
		// Give back image size
		return m_cImage.GetSize();
	else
		// Bitmap is empty
		return Vector2i::Zero;
}

void Bitmap::OnDraw(Graphics &cGraphics)
{
	// Call base implementation
	Widget::OnDraw(cGraphics);

	// Draw image
	// [TODO] PLGui: Was m_cImage.GetSize() ?!
	cGraphics.DrawImage(m_cImage, Vector2i::Zero, GetSize());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
