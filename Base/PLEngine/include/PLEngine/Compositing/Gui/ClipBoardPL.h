/*********************************************************\
 *  File: ClipBoardPL.h                                  *
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


#ifndef __PLENGINE_COMPOSITING_GUI_CLIPBOARD_H__
#define __PLENGINE_COMPOSITING_GUI_CLIPBOARD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Backend/ClipBoardImpl.h>
#include <PLGui/Gui/Data/DataObject.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    ClipBoard implementation for the PixelLight ingame GUI
*/
class ClipBoardPL : public PLGui::ClipBoardImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GuiPL;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cClipBoard
		*    Reference to platform independent clipboard
		*/
		PL_API ClipBoardPL(PLGui::ClipBoard &cClipBoard);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~ClipBoardPL();


	//[-------------------------------------------------------]
	//[ Private virtual PLGui::ClipBoardImpl functions        ]
	//[-------------------------------------------------------]
	private:
		PL_API virtual PLGui::DataObject GetData() override;
		PL_API virtual void SetData(const PLGui::DataObject &cData) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_COMPOSITING_GUI_CLIPBOARD_H__
