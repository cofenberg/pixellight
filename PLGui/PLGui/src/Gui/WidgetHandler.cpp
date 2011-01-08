/*********************************************************\
 *  File: WidgetHandler.cpp                              *
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
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Gui/WidgetHandler.h"


//[-------------------------------------------------------]
//[ Disable warnings                                      ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
WidgetHandler::WidgetHandler() :
	EventHandlerDestroy(&WidgetHandler::OnWidgetDestroy, this),
	m_pWidget(nullptr)
{
}

/**
*  @brief
*    Copy constructor
*/
WidgetHandler::WidgetHandler(const WidgetHandler &cOther) :
	m_pWidget(nullptr)
{
	// Set widget pointer
	SetWidget(cOther.m_pWidget);
}

/**
*  @brief
*    Destructor
*/
WidgetHandler::~WidgetHandler()
{
	// Reset widget pointer
	Clear();
}

/**
*  @brief
*    Get widget pointer
*/
Widget *WidgetHandler::GetWidget() const
{
	// Return widget pointer
	return m_pWidget;
}

/**
*  @brief
*    Set widget pointer
*/
bool WidgetHandler::SetWidget(Widget *pWidget)
{
	// Clear pointer
	Clear();

	// Set widget pointer
	m_pWidget = pWidget;

	// Register at widget
	if (m_pWidget) {
		// Register destroy-event
		m_pWidget->EventDestroy.Connect(&EventHandlerDestroy);
	}

	// Error!
	return false;
}

/**
*  @brief
*    Clear widget pointer
*/
void WidgetHandler::Clear()
{
	// Check status
	if (m_pWidget) {
		// Unregister from widget
		m_pWidget->EventDestroy.Disconnect(&EventHandlerDestroy);

		// Reset widget pointer
		m_pWidget = nullptr;
	}
}

/**
*  @brief
*    Check if the widget pointer is valid
*/
bool WidgetHandler::IsValid() const
{
	// Check if pointer is set
	return (m_pWidget != nullptr);
}

/**
*  @brief
*    Compare operator
*/
bool WidgetHandler::operator ==(const WidgetHandler &cOther) const
{
	// Compare pointers
	return (m_pWidget == cOther.m_pWidget);
}

/**
*  @brief
*    Assignment operator
*/
WidgetHandler &WidgetHandler::operator =(const WidgetHandler &cOther)
{
	// Set widget pointer
	SetWidget(cOther.m_pWidget);

	// Return reference to this object
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
void WidgetHandler::OnWidgetDestroy()
{
	// Widget has been destroyed, reset pointer
	Clear();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
