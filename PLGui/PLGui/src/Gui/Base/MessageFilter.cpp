/*********************************************************\
 *  File: MessageFilter.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Widgets/Widget.h"
#include "PLGui/Gui/Base/GuiMessage.h"
#include "PLGui/Gui/Base/MessageFilter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MessageFilter::MessageFilter()
{
}

/**
*  @brief
*    Destructor
*/
MessageFilter::~MessageFilter()
{
}

/**
*  @brief
*    Add filter rule
*/
void MessageFilter::AddRule(EMessageFilter nFilterType, EMessageType nMessageType)
{
	// Add filter rule
	m_lstRules.Add(MessageFilterRule(nFilterType, nMessageType));
}

/**
*  @brief
*    Add filter rule
*/
void MessageFilter::AddRule(EMessageFilter nFilterType, const String &sWidget)
{
	// Add filter rule
	m_lstRules.Add(MessageFilterRule(nFilterType, sWidget));
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Add GUI message
*/
void MessageFilter::AddMessage(const GuiMessage &cMessage)
{
	// Get message type and widget type
	EMessageType nMessageType =  cMessage.GetType();
	String		 sWidgetName  = (cMessage.GetWidget() ? cMessage.GetWidget()->GetName() : "");

	// Check filter rules
	bool bTypeRules	  = false;
	bool bTypeDefault = false;
	bool bTypeAllow   = false;
	bool bTypeReject  = false;
	bool bNameRules   = false;
	bool bNameDefault = false;
	bool bNameAllow   = false;
	bool bNameReject  = false;
	for (uint32 i=0; i<m_lstRules.GetNumOfElements(); i++) {
		// Get rule
		MessageFilterRule &cRule = m_lstRules[i];

		// Get rule type
		if (cRule.GetMessageType() != MessageOnUnknown) {
			// Set default value for type-based checks
			if (!bTypeRules) {
				if (cRule.GetFilterType() == FilterInclusive) bTypeDefault = false;
				else										  bTypeDefault = true;
				bTypeRules = true;
			}

			// Filter against message type
			if (cRule.GetFilterType() == FilterInclusive && cRule.GetMessageType() == nMessageType) {
				// Message type accepted
				bTypeAllow = true;
			} else if (cRule.GetFilterType() == FilterExclusive && cRule.GetMessageType() == nMessageType) {
				// Message type rejected
				bTypeReject = true;
			}
		} else if (cRule.GetWidgetName() != "") {
			// Set default value for name-based checks
			if (!bNameRules) {
				if (cRule.GetFilterType() == FilterInclusive) bNameDefault = false;
				else										  bNameDefault = true;
				bNameRules = true;
			}

			// Filter against widget name
			if (cRule.GetFilterType() == FilterInclusive && cRule.GetWidgetName() == sWidgetName) {
				// Widget name accepted
				bNameAllow = true;
			} else if (cRule.GetFilterType() == FilterExclusive && cRule.GetWidgetName() == sWidgetName) {
				// Widget name rejected
				bNameReject = true;
			}
		}
	}

	// Check if message type passes or gets filtered out
	bool bTypeResult = (bTypeReject ? false : (bTypeAllow ? true : (bTypeRules ? bTypeDefault : true)));
	bool bNameResult = (bNameReject ? false : (bNameAllow ? true : (bNameRules ? bNameDefault : true)));
	if (bTypeResult && bNameResult) {
		// Message passes
		OnGuiMessage(cMessage);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual MessageFilter functions             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a GUI message has arrived
*/
void MessageFilter::OnGuiMessage(const GuiMessage &cMessage)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
