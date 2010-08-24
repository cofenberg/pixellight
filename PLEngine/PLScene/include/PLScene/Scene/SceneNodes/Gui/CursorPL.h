/*********************************************************\
 *  File: CursorPL.h                                     *
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


#ifndef __PLSCENE_SCENENODE_GUI_CURSOR_H__
#define __PLSCENE_SCENENODE_GUI_CURSOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/PLGuiDefinitions.h>
#include <PLGui/Backend/CursorImpl.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight ingame GUI cursor implementation
*/
class CursorPL : public PLGui::CursorImpl {


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
		PLS_API CursorPL(PLGui::Cursor &cCursor);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~CursorPL();


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::CursorImpl functions            ]
	//[-------------------------------------------------------]
	public:
		virtual void Load(PLGui::EMouseCursor nCursor);
		virtual void Load(const PLGeneral::String &sFilename, const PLMath::Vector2i &vHotspot);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GUI_CURSOR_H__
