/*********************************************************\
 *  File: User.cpp                                       *
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
#include "PLIRC/User.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLIRC {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
User::User(const String &sNick, bool bOp, bool bVoice) :
	m_sNick(sNick), m_bOp(bOp), m_bVoice(bVoice)
{
}

User::~User()
{
}

String User::GetNick() const
{
	return m_sNick;
}

void User::SetNick(const String &sNick)
{
	m_sNick = sNick;
}

bool User::IsOp() const
{
	return m_bOp;
}

void User::SetOp(bool bOp)
{
	m_bOp = bOp;
}

bool User::IsVoice() const
{
	return m_bVoice;
}

void User::SetVoice(bool bVoice)
{
	m_bVoice = bVoice;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC
