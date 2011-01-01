/*********************************************************\
 *  File: MessageFilterRule.h                            *
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


#ifndef __PLGUI_MESSAGEFILTERRULE_H__
#define __PLGUI_MESSAGEFILTERRULE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class that represents a filter rule
*/
class MessageFilterRule {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGUI_API MessageFilterRule();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nFilterType
		*    Filter type (inclusive or exclusive)
		*  @param[in] nMessageType
		*    Message type that is filtered
		*
		*  @remarks
		*    Use this constructor to filter against message type
		*/
		PLGUI_API MessageFilterRule(EMessageFilter nFilterType, EMessageType nMessageType);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nFilterType
		*    Filter type (inclusive or exclusive)
		*  @param[in] sWidget
		*    Name of widget that is filtered
		*
		*  @remarks
		*    Use this constructor to filter against widget name
		*/
		PLGUI_API MessageFilterRule(EMessageFilter nFilterType, const PLGeneral::String &sWidget);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    Filter rule
		*/
		PLGUI_API MessageFilterRule(const MessageFilterRule &cOther);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~MessageFilterRule();

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cOther
		*    Filter rule
		*
		*  @return
		*    'true' if equal, else 'false'
		*/
		PLGUI_API bool operator ==(const MessageFilterRule &cOther) const;

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cOther
		*    Filter rule
		*
		*  @return
		*    Reference to this object
		*/
		PLGUI_API MessageFilterRule &operator =(const MessageFilterRule &cOther);

		/**
		*  @brief
		*    Get filter type
		*
		*  @return
		*    Filter type
		*/
		PLGUI_API EMessageFilter GetFilterType() const;

		/**
		*  @brief
		*    Get message type
		*
		*  @return
		*    Message type, MessageOnUnknown if not used
		*
		*  @remarks
		*    A filter rule can filter against message types or widget names.
		*    This will return MessageOnUnknown, if the type is a widget-name filter.
		*/
		PLGUI_API EMessageType GetMessageType() const;

		/**
		*  @brief
		*    Get widget name
		*
		*  @return
		*    Widget name, "" if not used
		*
		*  @remarks
		*    A filter rule can filter against message types or widget names.
		*    This will return "", if the type is a message-type filter.
		*/
		PLGUI_API PLGeneral::String GetWidgetName() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EMessageFilter		m_nFilterType;		/**< Filter type (inclusive or exclusive) */
		EMessageType		m_nMessageType;		/**< Message type that is filtered (MessageOnUnknown if not used) */
		PLGeneral::String	m_sWidget;			/**< Widget name that is filtered  ("" if not used) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MESSAGEFILTERRULE_H__
