/*********************************************************\
 *  File: CursorImpl.h                                   *
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


#ifndef __PLGUI_CURSORIMPL_H__
#define __PLGUI_CURSORIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Core/RefCount.h>
#include <PLCore/String/String.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector2i;
}
namespace PLGui {
	class Cursor;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Cursor implementation base class
*
*  @remarks
*    This class is the base class for platform specific cursor implementations
*
*  @note
*    - Implementation of the bridge design pattern, this class is the implementor of the 'Cursor' abstraction
*/
class CursorImpl : public PLCore::RefCount<CursorImpl> {


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
		PLGUI_API CursorImpl(Cursor &cCursor);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~CursorImpl();

		/**
		*  @brief
		*    Get cursor ID
		*
		*  @return
		*    Cursor ID or CursorCustom, if no default cursor is used
		*/
		PLGUI_API EMouseCursor GetCursorID() const;

		/**
		*  @brief
		*    Get image filename
		*
		*  @return
		*    Image filename
		*/
		PLGUI_API PLCore::String GetFilename() const;


	//[-------------------------------------------------------]
	//[ Public virtual CursorImpl functions                   ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Load cursor
		*
		*  @param[in] nCursor
		*    Default cursor ID
		*/
		virtual void Load(EMouseCursor nCursor) = 0;

		/**
		*  @brief
		*    Load cursor
		*
		*  @param[in] sFilename
		*    Name of image file
		*  @param[in] vHotspot
		*    Hotspot of cursor
		*/
		virtual void Load(const PLCore::String &sFilename, const PLMath::Vector2i &vHotspot) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Cursor		   *m_pCursor;		/**< Pointer to the platform independent cursor object */
		EMouseCursor	m_nMouseCursor;	/**< Default cursor ID (CustomCursor if a custom image has been loaded) */
		PLCore::String  m_sFilename;	/**< Image filename */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_CURSORIMPL_H__
