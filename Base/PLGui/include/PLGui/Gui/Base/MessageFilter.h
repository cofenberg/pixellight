/*********************************************************\
 *  File: MessageFilter.h                                *
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


#ifndef __PLGUI_MESSAGEFILTER_H__
#define __PLGUI_MESSAGEFILTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Array.h>
#include "PLGui/Gui/Base/MessageFilterRule.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class String;
}
namespace PLGui {
	class Gui;
	class GuiMessage;
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
*    Class to retrieve and filter GUI messages
*/
class MessageFilter {


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
		*/
		PLGUI_API MessageFilter();

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~MessageFilter();

		/**
		*  @brief
		*    Add filter rule
		*
		*  @param[in] nFilterType
		*    Filter type (inclusive or exclusive)
		*  @param[in] nMessageType
		*    Message type that is filtered
		*
		*  @remarks
		*    Use this constructor to filter against a message type
		*/
		PLGUI_API void AddRule(EMessageFilter nFilterType, EMessageType nMessageType);

		/**
		*  @brief
		*    Add filter rule
		*
		*  @param[in] nFilterType
		*    Filter type (inclusive or exclusive)
		*  @param[in] sWidget
		*    Name of widget that is filtered
		*
		*  @remarks
		*    Use this constructor to filter against a widget name
		*/
		PLGUI_API void AddRule(EMessageFilter nFilterType, const PLCore::String &sWidget);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Add GUI message
		*
		*  @param[in] cMessage
		*    GUI message
		*/
		PLGUI_API void AddMessage(const GuiMessage &cMessage);


	//[-------------------------------------------------------]
	//[ Protected virtual MessageFilter functions             ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when a GUI message has arrived
		*
		*  @param[in] cMessage
		*    GUI message
		*/
		PLGUI_API virtual void OnGuiMessage(const GuiMessage &cMessage);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::Array<MessageFilterRule> m_lstRules;	/**< Filter rule list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MESSAGEFILTER_H__
