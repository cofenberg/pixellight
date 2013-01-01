/*********************************************************\
 *  File: Channel.cpp                                    *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLIRC/User.h"
#include "PLIRC/Channel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
