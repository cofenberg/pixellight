/*********************************************************\
 *  File: Channel.cpp                                    *
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
#include "PLIRC/Channel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLIRC {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
Channel::Channel(const String &sName) :
	m_sName(sName)
{
}

Channel::~Channel()
{
	// Delete all users
	Iterator<User*> cIterator = m_lstUsers.GetIterator();
	while (cIterator.HasNext())
		delete cIterator.Next();
}

String Channel::GetName() const
{
	// Return name
	return m_sName;
}

const Topic &Channel::GetTopic() const
{
	// Return topic
	return m_cTopic;
}

Topic &Channel::GetTopic()
{
	// Return topic
	return m_cTopic;
}

uint32 Channel::GetNumOfUsers() const
{
	// Return list size
	return m_lstUsers.GetNumOfElements();
}

const User *Channel::GetUser(uint32 nUser) const
{
	// Get user
	return m_lstUsers[nUser];
}

User *Channel::GetUser(uint32 nUser)
{
	return m_lstUsers[nUser];
}

const User *Channel::GetUser(const String &sNick) const
{
	// Search for user
	Iterator<User*> cIterator = m_lstUsers.GetIterator();
	while (cIterator.HasNext()) {
		User *pUser = cIterator.Next();
		if (pUser->GetNick() == sNick) {
			// User found
			return pUser;
		}
	}

	// No user found
	return nullptr;
}

User *Channel::GetUser(const String &sNick)
{
	// Search for user
	Iterator<User*> cIterator = m_lstUsers.GetIterator();
	while (cIterator.HasNext()) {
		User *pUser = cIterator.Next();
		if (pUser->GetNick() == sNick) {
			// User found
			return pUser;
		}
	}

	// No user found
	return nullptr;
}

bool Channel::AddUser(const String &sNick, bool bOp, bool bVoice)
{
	// Check user
	if (GetUser(sNick)) return false; // Error!

	// Create new user
	m_lstUsers.Add(new User(sNick, bOp, bVoice));

	// Done
	return true;
}

void Channel::RemoveUser(const String &sNick)
{
	// Find user
	Iterator<User*> cIterator = m_lstUsers.GetIterator();
	while (cIterator.HasNext()) {
		User *pUser = cIterator.Next();
		if (pUser->GetNick() == sNick) {
			// User found
			m_lstUsers.Remove(pUser);
			delete pUser;
			return;
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Channel::Channel(const Channel &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Channel &Channel::operator =(const Channel &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC
