/*********************************************************\
 *  File: ClipBoardImpl.h                                *
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


#ifndef __PLGUI_CLIPBOARDIMPL_H__
#define __PLGUI_CLIPBOARDIMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Gui/Data/DataObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ClipBoard;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Clipboard implementation base class
*/
class ClipBoardImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ClipBoard;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cClipBoard
		*    Reference to platform independent clipboard
		*/
		PLGUI_API ClipBoardImpl(ClipBoard &cClipBoard);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~ClipBoardImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual ClipBoardImpl functions             ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Get data from clipboard
		*
		*  @return
		*    Data
		*/
		virtual DataObject GetData() = 0;

		/**
		*  @brief
		*    Save data to clipboard
		*
		*  @param[in] cData
		*    Data
		*/
		virtual void SetData(const DataObject &cData) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		ClipBoard *m_pClipBoard;	/**< Pointer to the platform independent clipboard object */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_CLIPBOARDIMPL_H__
