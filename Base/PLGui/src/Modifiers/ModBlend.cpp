/*********************************************************\
 *  File: ModBlend.cpp                                   *
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
#include <PLGraphics/Color/Color4.h>
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/Resources/Timer.h"
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Modifiers/ModBlend.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(ModBlend)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ModBlend::ModBlend() :
	SlotOnTimer(this),
	m_nTimeout(20),
	m_fTrans(1.0f),
	m_fTransDest(1.0f),
	m_pTimer(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ModBlend::~ModBlend()
{
	// Delete timer
	if (m_pTimer) delete m_pTimer;
}

/**
*  @brief
*    Get blend animation time
*/
uint64 ModBlend::GetBlendTime() const
{
	// Return timeout
	return m_nTimeout;
}

/**
*  @brief
*    Set blend animation time
*/
void ModBlend::SetBlendTime(uint64 nBlendTime)
{
	// Set timeout
	if (nBlendTime > 0) {
		m_nTimeout = nBlendTime;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual Modifier functions                  ]
//[-------------------------------------------------------]
void ModBlend::OnAttach(Widget &cWidget)
{
	// Create timer
	m_pTimer = new Timer(*cWidget.GetGui());
	m_pTimer->EventFire.Connect(SlotOnTimer);
}

void ModBlend::OnDetach(Widget &cWidget)
{
}


//[-------------------------------------------------------]
//[ Protected virtual WidgetFunctions functions           ]
//[-------------------------------------------------------]
void ModBlend::OnMouseOver(bool bMouseOver)
{
	// Mouse in over widget or any child-widget
	if (bMouseOver) {
		// Blend to full opacity (1.0)
		m_fTransDest = 1.0f;

		// Start blending
		if (!m_pTimer->IsActive())
			m_pTimer->Start(m_nTimeout);
	}

	// Mouse is not over the widget or any child-widget
	else {
		// Blend to half transparent (0.5)
		m_fTransDest = 0.5f;

		// Start blending
		if (!m_pTimer->IsActive())
			m_pTimer->Start(m_nTimeout);
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the timer has fired
*/
void ModBlend::OnTimer()
{
	// Blend
	if (m_fTransDest > m_fTrans) {
		m_fTrans += 0.04f;
		if (m_fTrans >= m_fTransDest) m_fTrans = m_fTransDest;
	} else if (m_fTransDest < m_fTrans) {
		m_fTrans -= 0.04f;
		if (m_fTrans <= m_fTransDest) m_fTrans = m_fTransDest;
	}

	// Target reached?
	if (m_fTrans == m_fTransDest)
		m_pTimer->Stop();

	// Set transparency
	m_pWidget->SetTransparency(AlphaTransparency, Color4(0.0f, 0.0f, 0.0f, m_fTrans));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP
