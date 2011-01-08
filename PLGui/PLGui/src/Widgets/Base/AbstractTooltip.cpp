/*********************************************************\
 *  File: AbstractTooltip.cpp                            *
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
#include "PLGui/Widgets/Base/AbstractTooltip.h"


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
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(AbstractTooltip)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
AbstractTooltip::AbstractTooltip(Widget *pParent) : Widget(pParent),
	Text(this),
	Timeout(this),
	SlotOnTimer(this),
	m_nTimeout(5000),
	m_cTimer(*GetGui())
{
	// Connect to timer
	m_cTimer.EventFire.Connect(&SlotOnTimer);
}

/**
*  @brief
*    Destructor
*/
AbstractTooltip::~AbstractTooltip()
{
}

/**
*  @brief
*    Get tooltip text
*/
String AbstractTooltip::GetText() const
{
	// Return tooltip
	return m_sTooltip;
}

/**
*  @brief
*    Set tooltip text
*/
void AbstractTooltip::SetText(const String &sTooltip)
{
	// Set tooltip
	m_sTooltip = sTooltip;
}

/**
*  @brief
*    Get tooltip timeout
*/
uint32 AbstractTooltip::GetTimeout() const
{
	// Return timeout
	return m_nTimeout;
}

/**
*  @brief
*    Set tooltip timeout
*/
void AbstractTooltip::SetTimeout(uint32 nTimeout)
{
	// Set timeout
	m_nTimeout = nTimeout;
}

/**
*  @brief
*    Show tooltip
*/
void AbstractTooltip::ShowTooltip(const Vector2i &vPos)
{
	// Set position
	SetPos(vPos);

	// Call virtual function
	OnShowTooltip();
}

/**
*  @brief
*    Blend out tooltip
*/
void AbstractTooltip::BlendOut()
{
	// Start timeout timer
	if (!m_cTimer.IsActive() && m_nTimeout > 0) {
		m_cTimer.StartOnce(m_nTimeout);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractTooltip functions           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called on display of the tooltip
*/
void AbstractTooltip::OnShowTooltip()
{
}

/**
*  @brief
*    Called on timeout
*/
void AbstractTooltip::OnTimeout()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the timer has fired
*/
void AbstractTooltip::OnTimer()
{
	// Emit event
	EventTimeout.Emit();

	// Call virtual function
	OnTimeout();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
