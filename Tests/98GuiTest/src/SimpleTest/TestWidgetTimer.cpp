/*********************************************************\
 *  File: TestWidgetTimer.cpp                            *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Gui/Gui.h>
#include "SimpleTest/TestWidgetTimer.h"


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
pl_implement_class(TestWidgetTimer)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestWidgetTimer::TestWidgetTimer(Widget *pParent) : Widget(pParent),
	SlotOnTimer(this),
	m_cTimer(*GetGui())
{
	// Connect to timer
	m_cTimer.EventFire.Connect(SlotOnTimer);

	// Set default color to gray
	SetBackgroundColor(Color4(0.7f, 0.7f, 0.7f, 1.0f));

	// Start timer
	m_cTimer.Start(1000);
}

/**
*  @brief
*    Destructor
*/
TestWidgetTimer::~TestWidgetTimer()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Timer callback
*/
void TestWidgetTimer::OnTimer()
{
	// Counter
	static int nCount = 0;
	if (nCount == 0) nCount = 1;
	else			 nCount = 0;

	// Set color
	SetBackgroundColor(nCount == 0 ? Color4::Red : Color4::Blue);
	Redraw();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
