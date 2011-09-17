/*********************************************************\
 *  File: ClipBoardNull.h                                *
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


#ifndef __PLGUI_CLIPBOARDNULL_H__
#define __PLGUI_CLIPBOARDNULL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Backend/ClipBoardImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    ClipBoard implementation for Null
*/
class ClipBoardNull : public ClipBoardImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GuiNull;


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
		PLGUI_API ClipBoardNull(ClipBoard &cClipBoard);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ClipBoardNull();


	//[-------------------------------------------------------]
	//[ Private virtual ClipBoardImpl functions               ]
	//[-------------------------------------------------------]
	private:
		PLGUI_API virtual DataObject GetData() override;
		PLGUI_API virtual void SetData(const DataObject &cData) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_CLIPBOARDNULL_H__
