/*********************************************************\
 *  File: Box.cpp                                        *
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
#include "PLGui/Widgets/Layout/Box.h"
#include "PLGui/Layout/LayoutBox.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(Box)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Box::Box(Widget *pParent, EOrientation nOrientation) : Widget(pParent),
	Orientation(this),
	m_pBoxLayout(NULL)
{
	// Create layout
	m_pBoxLayout = new LayoutBox();
	m_pBoxLayout->SetOrientation(nOrientation);

	// Set layout
	SetLayout(m_pBoxLayout);

	// Give focus to child windows
	SetFocusStyle(ChildFocus);
}

/**
*  @brief
*    Destructor
*/
Box::~Box()
{
}

/**
*  @brief
*    Get orientation of box
*/
EOrientation Box::GetOrientation() const
{
	// Return orientation
	return m_pBoxLayout->GetOrientation();
}

/**
*  @brief
*    Set orientation of box
*/
void Box::SetOrientation(EOrientation nOrientation)
{
	// Set orientation
	m_pBoxLayout->SetOrientation(nOrientation);
}


//[-------------------------------------------------------]
//[ Private virtual Widget functions                      ]
//[-------------------------------------------------------]
PLMath::Vector2i Box::OnPreferredSize(const Vector2i &vRefSize) const
{
	// Call base function
	Widget::OnPreferredSize(vRefSize);

	// [TODO] Calculate inner size of layout
	return Vector2i(-1, -1);
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
