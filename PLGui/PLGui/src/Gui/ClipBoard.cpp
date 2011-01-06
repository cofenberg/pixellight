/*********************************************************\
 *  File: ClipBoard.cpp                                  *
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
#include "PLGui/Gui/Gui.h"
#include "PLGui/Gui/ClipBoard.h"
#include "PLGui/Gui/Data/DataObject.h"
#include "PLGui/Backend/ClipBoardImpl.h"


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
ClipBoard::ClipBoard(Gui &cGui) :
	m_pGui(&cGui),
	m_pImpl(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ClipBoard::~ClipBoard()
{
}

/**
*  @brief
*    Get owner GUI
*/
Gui *ClipBoard::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get implementation
*/
ClipBoardImpl *ClipBoard::GetImpl() const
{
	// Return implementation
	return m_pImpl;
}

/**
*  @brief
*    Get data from clipboard
*/
DataObject ClipBoard::GetData()
{
	// Get data
	return m_pImpl->GetData();
}

/**
*  @brief
*    Save data to clipboard
*/
void ClipBoard::SetData(const DataObject &cData)
{
	// Set data
	m_pImpl->SetData(cData);
}

/**
*  @brief
*    Get text from clipboard
*/
String ClipBoard::GetText()
{
	// Get text
	return m_pImpl->GetData().GetString();
}

/**
*  @brief
*    Save text to clipboard
*/
void ClipBoard::SetText(const String &sText)
{
	// Set text
	DataObject cData(sText);
	m_pImpl->SetData(cData);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialize clipboard (create backend)
*/
void ClipBoard::InitClipBoard()
{
	// We must have a valid GUI
	if (m_pGui) {
		// Create clipboard implementation
		m_pImpl = m_pGui->CreateClipBoardImpl(*this);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
