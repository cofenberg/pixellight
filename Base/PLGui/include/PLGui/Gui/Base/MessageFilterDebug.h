/*********************************************************\
 *  File: MessageFilterDebug.h                           *
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


#ifndef __PLGUI_MESSAGEFILTERDEBUG_H__
#define __PLGUI_MESSAGEFILTERDEBUG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Gui/Base/MessageFilter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Message filter that dumps all messages to the console
*/
class MessageFilterDebug : public MessageFilter {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nDebugMode
		*    Debug mode
		*/
		PLGUI_API MessageFilterDebug(EDebugMode nDebugMode = DebugModeAll);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~MessageFilterDebug();

		/**
		*  @brief
		*    Get debug mode
		*
		*  @return
		*    Debug mode
		*/
		PLGUI_API EDebugMode GetDebugMode() const;

		/**
		*  @brief
		*    Set debug mode
		*
		*  @param[in] nDebugMode
		*    Debug mode
		*/
		PLGUI_API void SetDebugMode(EDebugMode nDebugMode);


	//[-------------------------------------------------------]
	//[ Protected virtual MessageFilter functions             ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnGuiMessage(const GuiMessage &cMessage) override;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EDebugMode m_nDebugMode;	/**< Debug mode */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MESSAGEFILTERDEBUG_H__
