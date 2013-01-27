/*********************************************************\
 *  File: TestWidgetImage.cpp                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/Gui.h>
#include <PLGui/Gui/Resources/Graphics.h>
#include <PLGui/Gui/Resources/Font.h>
#include "SimpleTest/TestWidgetImage.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLGui;


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(TestWidgetImage)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestWidgetImage::TestWidgetImage(Widget *pParent) : Widget(pParent),
	m_cImage(*GetGui(), "PLGui/test.png")
{
	// Set default color to gray
	SetBackgroundColor(Color4(0.7f, 0.7f, 0.7f, 1.0f));
}

/**
*  @brief
*    Destructor
*/
TestWidgetImage::~TestWidgetImage()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLGui::Widget functions                ]
//[-------------------------------------------------------]
void TestWidgetImage::OnDraw(Graphics &cGraphics)
{
	// Draw image
	cGraphics.DrawImage(m_cImage, Vector2i(0, 0), Vector2i::Zero);

	// Draw text
	Font cFont(*GetGui());
	cGraphics.DrawText(cFont, Color4::Black, Color4::Transparent, Vector2i(20, 4), "Hello World!");
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
