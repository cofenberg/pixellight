/*********************************************************\
 *  File: Channel.h                                      *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLIRC_CHANNEL_H__
#define __PLIRC_CHANNEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/List.h>
#include "PLIRC/Topic.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLIRC {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class User;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    IRC Channel
*/
class Channel {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		// Construction/Destruction
		PLIRC_API Channel(const PLCore::String &sName);
		PLIRC_API ~Channel();

		// Get the channel name
		PLIRC_API PLCore::String GetName() const;

		// Channel topic
		PLIRC_API const Topic &GetTopic() const;
		PLIRC_API Topic &GetTopic();

		// User list
		PLIRC_API PLCore::uint32 GetNumOfUsers() const;
		PLIRC_API const User *GetUser(PLCore::uint32 nUser) const;
		PLIRC_API User *GetUser(PLCore::uint32 nUser);
		PLIRC_API const User *GetUser(const PLCore::String &sNick) const;
		PLIRC_API User *GetUser(const PLCore::String &sNick);
		PLIRC_API bool AddUser(const PLCore::String &sNick, bool bOp = false, bool bVoice = false);
		PLIRC_API void RemoveUser(const PLCore::String &sNick);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Channel(const Channel &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Channel &operator =(const Channel &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String	    m_sName;	/**< Name of channel */
		Topic			    m_cTopic;	/**< Channel topic */
		PLCore::List<User*> m_lstUsers;	/**< User list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC


#endif // __PLIRC_CHANNEL_H__
