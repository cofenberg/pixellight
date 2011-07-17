/*********************************************************\
 *  File: CursorLinux.h                                  *
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


#ifndef __PLGUI_CURSORLINUX_H__
#define __PLGUI_CURSORLINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneralLinuxIncludes.h>
#include "PLGui/Backend/CursorImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux cursor implementation
*/
class CursorLinux : public CursorImpl {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cCursor
		*    Reference to platform independent cursor
		*/
		PLGUI_API CursorLinux(Cursor &cCursor);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~CursorLinux();

		/**
		*  @brief
		*    Get X cursor
		*
		*  @return
		*    Pointer to cursor, can be a null pointer
		*/
		PLGUI_API ::Cursor GetXCursor() const;


	//[-------------------------------------------------------]
	//[ Public virtual CursorImpl functions                   ]
	//[-------------------------------------------------------]
	public:
		virtual void Load(EMouseCursor nCursor);
		virtual void Load(const PLGeneral::String &sFilename, const PLMath::Vector2i &vHotspot);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		::Display *m_pDisplay;	/**< X Display */
		::Cursor   m_pXCursor;	/**< X cursor */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_CURSORLINUX_H__
