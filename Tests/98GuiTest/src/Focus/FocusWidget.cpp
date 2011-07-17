/*********************************************************\
 *  File: FocusWidget.cpp                                *
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
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Resources/Graphics.h>
#include "Focus/FocusWidget.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(FocusWidget)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FocusWidget::FocusWidget(Widget *pParent) : Widget(pParent)
{
	// Set background color
	SetBackgroundColor(Color4::Gray);

	// Accept focus (by default)
	SetFocusStyle(AcceptFocus);
}

/**
*  @brief
*    Destructor
*/
FocusWidget::~FocusWidget()
{
}


//[-------------------------------------------------------]
//[ Public virtual Widget functions                       ]
//[-------------------------------------------------------]
void FocusWidget::OnDraw(Graphics &cGraphics)
{
	cGraphics.DrawRect(Color4::Black, Vector2i::Zero, GetSize() - Vector2i(1, 1), 0, 0, 1);
}

void FocusWidget::OnGetFocus()
{
	/*
	SetBackgroundColor(Color4::Green);
	Redraw();
	*/
}

void FocusWidget::OnLooseFocus()
{
	/*
	SetBackgroundColor(Color4::Gray);
	Redraw();
	*/
}

void FocusWidget::OnActivate(bool bActivate)
{
	// Check if focus widget is this or a child widget
	if (m_pGui->GetFocusWidget() == this)
		SetBackgroundColor(Color4::Lime);
	else if (bActivate)
		SetBackgroundColor(Color4::Green);
	else
		SetBackgroundColor(Color4::Gray);
	Redraw();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
