/*********************************************************\
 *  File: CursorManager.cpp                              *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/CursorManager.h"
#include "PLGui/Backend/GuiImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
CursorManager::CursorManager(Gui &cGui) :
	m_pGui(&cGui)
{
	// Create array for standard cursors
	for (int i=0; i<Cursor_Count; i++) {
		m_pCursors[i] = NULL;
	}
}

/**
*  @brief
*    Destructor
*/
CursorManager::~CursorManager()
{
	// Destroy standard cursors
	for (int i=0; i<Cursor_Count; i++) {
		if (m_pCursors[i]) delete m_pCursors[i];
	}
}

/**
*  @brief
*    Get owner GUI
*/
Gui *CursorManager::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get standard cursor
*/
Cursor *CursorManager::GetCursor(EMouseCursor nCursor)
{
	// Get pointer to standard cursor
	int nIndex = (int)nCursor;
	if (!m_pCursors[nIndex]) {
		// Create cursor
		m_pCursors[nIndex] = new Cursor(*m_pGui);
		m_pCursors[nIndex]->Load(nCursor);
	}

	// Return cursor
	return m_pCursors[nIndex];
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
