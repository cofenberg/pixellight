/*********************************************************\
 *  File: Topic.cpp                                      *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLIRC/Topic.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
