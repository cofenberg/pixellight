/*********************************************************\
 *  File: MessageFilterRule.cpp                          *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGui/Gui/Base/MessageFilterRule.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MessageFilterRule::MessageFilterRule() :
	m_nFilterType(FilterInclusive),
	m_nMessageType(MessageOnUnknown),
	m_sWidget("")
{
}

/**
*  @brief
*    Constructor
*/
MessageFilterRule::MessageFilterRule(EMessageFilter nFilterType, EMessageType nMessageType) :
	m_nFilterType(nFilterType),
	m_nMessageType(nMessageType),
	m_sWidget("")
{
}

/**
*  @brief
*    Constructor
*/
MessageFilterRule::MessageFilterRule(EMessageFilter nFilterType, const String &sWidget) :
	m_nFilterType(nFilterType),
	m_nMessageType(MessageOnUnknown),
	m_sWidget(sWidget)
{
}

/**
*  @brief
*    Copy constructor
*/
MessageFilterRule::MessageFilterRule(const MessageFilterRule &cOther) :
	m_nFilterType(cOther.m_nFilterType),
	m_nMessageType(cOther.m_nMessageType),
	m_sWidget(cOther.m_sWidget)
{
}

/**
*  @brief
*    Destructor
*/
MessageFilterRule::~MessageFilterRule()
{
}

/**
*  @brief
*    Comparison operator
*/
bool MessageFilterRule::operator ==(const MessageFilterRule &cOther) const
{
	// Compare filter rule
	return (cOther.m_nFilterType == m_nFilterType && cOther.m_nMessageType == m_nMessageType && cOther.m_sWidget == m_sWidget);
}

/**
*  @brief
*    Assignment operator
*/
MessageFilterRule &MessageFilterRule::operator =(const MessageFilterRule &cOther)
{
	// Copy filter rule
	m_nFilterType	= cOther.m_nFilterType;
	m_nMessageType	= cOther.m_nMessageType;
	m_sWidget		= cOther.m_sWidget;
	return *this;
}

/**
*  @brief
*    Get filter type
*/
EMessageFilter MessageFilterRule::GetFilterType() const
{
	// Return filter type
	return m_nFilterType;
}

/**
*  @brief
*    Get message type
*/
EMessageType MessageFilterRule::GetMessageType() const
{
	// Return message type
	return m_nMessageType;
}

/**
*  @brief
*    Get widget name
*/
String MessageFilterRule::GetWidgetName() const
{
	// Return widget name
	return m_sWidget;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
