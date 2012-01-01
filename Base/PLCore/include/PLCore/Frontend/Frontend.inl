/*********************************************************\
 *  File: Frontend.inl                                   *
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
#include "PLCore/Frontend/FrontendImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get frontend context
*/
inline const FrontendContext &Frontend::GetContext() const
{
	return m_cFrontendContext;
}

/**
*  @brief
*    Get frontend implementation
*/
inline FrontendImpl *Frontend::GetImpl() const
{
	// Return implementation
	return m_pFrontendImpl;
}

/**
*  @brief
*    Get native window handle
*/
inline handle Frontend::GetNativeWindowHandle() const
{
	// Call backend
	return m_pFrontendImpl->GetNativeWindowHandle();
}

/**
*  @brief
*    Redraw frontend
*/
inline void Frontend::Redraw()
{
	// Call backend
	m_pFrontendImpl->Redraw();
}

/**
*  @brief
*    Give the frontend a chance to process OS messages
*/
inline void Frontend::Ping() const
{
	// Call backend
	m_pFrontendImpl->Ping();
}

/**
*  @brief
*    Redraw frontend and give the frontend a chance to process OS messages
*/
inline void Frontend::RedrawAndPing()
{
	// Call backend methods
	m_pFrontendImpl->Redraw();
	m_pFrontendImpl->Ping();
}

/**
*  @brief
*    Get frontend title
*/
inline String Frontend::GetTitle() const
{
	// Call backend
	return m_pFrontendImpl->GetTitle();
}

/**
*  @brief
*    Set frontend title
*/
inline void Frontend::SetTitle(const String &sTitle)
{
	// Call backend
	return m_pFrontendImpl->SetTitle(sTitle);
}

/**
*  @brief
*    Get the x position of the frontend (in screen coordinates)
*/
inline int Frontend::GetX() const
{
	// Call backend
	return m_pFrontendImpl->GetX();
}

/**
*  @brief
*    Get the y position of the frontend (in screen coordinates)
*/
inline int Frontend::GetY() const
{
	// Call backend
	return m_pFrontendImpl->GetY();
}

/**
*  @brief
*    Get frontend width
*/
inline uint32 Frontend::GetWidth() const
{
	// Call backend
	return m_pFrontendImpl->GetWidth();
}

/**
*  @brief
*    Get frontend height
*/
inline uint32 Frontend::GetHeight() const
{
	// Call backend
	return m_pFrontendImpl->GetHeight();
}

/**
*  @brief
*    Set frontend position and size
*/
inline void Frontend::SetPositionSize(int nX, int nY, uint32 nWidth, uint32 nHeight)
{
	// Call backend
	m_pFrontendImpl->SetPositionSize(nX, nY, nWidth, nHeight);
}

/**
*  @brief
*    Gets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
inline bool Frontend::GetToggleFullscreenMode() const
{
	// Call backend
	return m_pFrontendImpl->GetToggleFullscreenMode();
}

/**
*  @brief
*    Sets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
inline void Frontend::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// Call backend
	m_pFrontendImpl->SetToggleFullscreenMode(bToggleFullscreenMode);
}

/**
*  @brief
*    Gets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
inline bool Frontend::GetFullscreenAltTab() const
{
	// Call backend
	return m_pFrontendImpl->GetFullscreenAltTab();
}

/**
*  @brief
*    Sets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
inline void Frontend::SetFullscreenAltTab(bool bAllowed)
{
	// Call backend
	m_pFrontendImpl->SetFullscreenAltTab(bAllowed);
}

/**
*  @brief
*    Returns whether the frontend is in fullscreen mode or not
*/
inline bool Frontend::IsFullscreen() const
{
	// Call backend
	return m_pFrontendImpl->IsFullscreen();
}

/**
*  @brief
*    Sets the frontend's fullscreen mode
*/
inline void Frontend::SetFullscreen(bool bFullscreen)
{
	// Call backend
	m_pFrontendImpl->SetFullscreen(bFullscreen);
}

/**
*  @brief
*    Something related to fullscreen mode has been changed (e.g. the display resolution)
*/
inline void Frontend::RefreshFullscreen()
{
	// Call backend
	m_pFrontendImpl->RefreshFullscreen();
}

/**
*  @brief
*    Check if the mouse is currently over the frontend
*/
inline bool Frontend::IsMouseOver() const
{
	// Call backend
	return m_pFrontendImpl->IsMouseOver();
}

/**
*  @brief
*    Get current mouse cursor X position inside the frontend
*/
inline int Frontend::GetMousePositionX() const
{
	// Call backend
	return m_pFrontendImpl->GetMousePositionX();
}

/**
*  @brief
*    Get current mouse cursor Y position inside the frontend
*/
inline int Frontend::GetMousePositionY() const
{
	// Call backend
	return m_pFrontendImpl->GetMousePositionY();
}

/**
*  @brief
*    Check if the mouse cursor is visible
*/
inline bool Frontend::IsMouseVisible() const
{
	// Call backend
	return m_pFrontendImpl->IsMouseVisible();
}

/**
*  @brief
*    Set mouse cursor visibility
*/
inline void Frontend::SetMouseVisible(bool bVisible)
{
	// Call backend
	m_pFrontendImpl->SetMouseVisible(bVisible);
}

/**
*  @brief
*    Trap mouse inside the frontend
*/
inline void Frontend::SetTrapMouse(bool bTrap)
{
	// Call backend
	m_pFrontendImpl->SetTrapMouse(bTrap);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
