/*********************************************************\
 *  File: Topic.cpp                                      *
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
#include "PLIRC/Topic.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLIRC {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
Topic::Topic()
{
}

Topic::Topic(const String &sNick, const String &sTopic, const Time &cDate) :
	m_sNick(sNick), m_sTopic(sTopic), m_cDate(cDate)
{
}

Topic::~Topic()
{
}

String Topic::GetNick() const
{
	return m_sNick;
}

void Topic::SetNick(const String &sNick)
{
	m_sNick = sNick;
}

String Topic::GetTopic() const
{
	return m_sTopic;
}

void Topic::SetTopic(const String &sTopic)
{
	m_sTopic = sTopic;
}

const Time &Topic::GetDate() const
{
	return m_cDate;
}

void Topic::SetDate(const Time &cDate)
{
	m_cDate = cDate;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC
