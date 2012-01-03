/*********************************************************\
 *  File: ClipBoard.h                                    *
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


#ifndef __PLGUI_CLIPBOARD_H__
#define __PLGUI_CLIPBOARD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include "PLGui/Gui/Data/DataObject.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Gui;
class ClipBoardImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Clipboard
*
*  @note
*    - Implementation of the bridge design pattern, this class is the abstraction
*/
class ClipBoard {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Gui;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGui
		*    Owner GUI
		*/
		PLGUI_API ClipBoard(Gui &cGui);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~ClipBoard();

		/**
		*  @brief
		*    Get owner GUI
		*
		*  @return
		*    Pointer to GUI object (never a null pointer)
		*/
		PLGUI_API Gui *GetGui() const;

		/**
		*  @brief
		*    Get implementation
		*
		*  @return
		*    Pointer to platform specific implementation
		*/
		PLGUI_API ClipBoardImpl *GetImpl() const;

		/**
		*  @brief
		*    Get data from clipboard
		*
		*  @return
		*    Data
		*/
		PLGUI_API DataObject GetData();

		/**
		*  @brief
		*    Save data to clipboard
		*
		*  @param[in] cData
		*    Data
		*/
		PLGUI_API void SetData(const DataObject &cData);

		/**
		*  @brief
		*    Get text from clipboard
		*
		*  @return
		*    String
		*/
		PLGUI_API PLCore::String GetText();

		/**
		*  @brief
		*    Save text to clipboard
		*
		*  @param[in] sText
		*    String
		*/
		PLGUI_API void SetText(const PLCore::String &sText);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initialize clipboard (create backend)
		*/
		PLGUI_API void InitClipBoard();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Gui			  *m_pGui;		/**< Pointer to GUI */
		ClipBoardImpl *m_pImpl;		/**< Clipboard implementation */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_CLIPBOARD_H__
