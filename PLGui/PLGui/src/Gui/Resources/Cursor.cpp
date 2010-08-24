/*********************************************************\
 *  File: Cursor.cpp                                     *
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
#include "PLGui/Gui/Resources/Cursor.h"
#include "PLGui/Gui/Gui.h"
#include "PLGui/Backend/CursorImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGui {


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Cursor::Cursor(Gui &cGui) :
	m_pGui(&cGui),
	m_pCursorImpl(NULL),
	m_nMouseCursor(CursorArrow)
{
	// Load cursor
	Load(CursorArrow);
}

/**
*  @brief
*    Constructor
*/
Cursor::Cursor(Gui &cGui, EMouseCursor nCursor) :
	m_pGui(&cGui),
	m_pCursorImpl(NULL),
	m_nMouseCursor(nCursor)
{
	// Load cursor
	Load(nCursor);
}

/**
*  @brief
*    Constructor
*/
Cursor::Cursor(Gui &cGui, const String &sFilename, const Vector2i &vHotspot) :
	m_pGui(&cGui),
	m_pCursorImpl(NULL),
	m_nMouseCursor(CursorCustom),
	m_sFilename(sFilename)
{
	// Load cursor
	Load(sFilename, vHotspot);
}

/**
*  @brief
*    Copy constructor
*/
Cursor::Cursor(const Cursor &cCursor) :
	m_pGui(cCursor.m_pGui),
	m_pCursorImpl(cCursor.m_pCursorImpl),
	m_sFilename(cCursor.m_sFilename),
	m_nMouseCursor(cCursor.m_nMouseCursor)
{
	// Increase reference count for cursor
	m_pCursorImpl->AddReference();
}

/**
*  @brief
*    Destructor
*/
Cursor::~Cursor()
{
	// Release implementation object
	m_pCursorImpl->Release();
}

/**
*  @brief
*    Assignment operator
*/
Cursor &Cursor::operator =(const Cursor &cCursor)
{
	// Release cursor
	if (m_pCursorImpl) {
		m_pCursorImpl->Release();
		m_pCursorImpl = NULL;
	}

	// Copy cursor
	m_pCursorImpl	= cCursor.m_pCursorImpl;
	m_nMouseCursor	= cCursor.m_nMouseCursor;
	m_sFilename		= cCursor.m_sFilename;
	if (m_pCursorImpl) {
		m_pCursorImpl->AddReference();
	}

	// Return reference to this cursor
	return *this;
}

/**
*  @brief
*    Get owner GUI
*/
Gui *Cursor::GetGui() const
{
	// Return GUI
	return m_pGui;
}

/**
*  @brief
*    Get implementation
*/
CursorImpl *Cursor::GetImpl() const
{
	// Return cursor implementation
	return m_pCursorImpl;
}

/**
*  @brief
*    Load cursor
*/
void Cursor::Load(EMouseCursor nCursor)
{
	// Release cursor
	if (m_pCursorImpl) {
		m_pCursorImpl->Release();
		m_pCursorImpl = NULL;
	}

	// Store cursor data
	m_nMouseCursor	= (nCursor == CursorCustom ? CursorArrow : nCursor);
	m_sFilename		= "";

	// Create cursor
	m_pCursorImpl = m_pGui->CreateCursorImpl(*this);
	m_pCursorImpl->AddReference();

	// Load cursor
	m_pCursorImpl->Load(m_nMouseCursor);
}

/**
*  @brief
*    Load cursor
*/
void Cursor::Load(const PLGeneral::String &sFilename, const Vector2i &vHotspot)
{
	// Release cursor
	if (m_pCursorImpl) {
		m_pCursorImpl->Release();
		m_pCursorImpl = NULL;
	}

	// Store cursor data
	m_nMouseCursor	= CursorCustom;
	m_sFilename		= sFilename;

	// Create cursor
	m_pCursorImpl = m_pGui->CreateCursorImpl(*this);
	m_pCursorImpl->AddReference();

	// Load cursor
	m_pCursorImpl->Load(m_sFilename, vHotspot);
}

/**
*  @brief
*    Get cursor ID
*/
EMouseCursor Cursor::GetCursorID() const
{
	// Return cursor ID
	return m_nMouseCursor;
}

/**
*  @brief
*    Get cursor filename
*/
String Cursor::GetFilename() const
{
	// Return filename
	return m_sFilename;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
