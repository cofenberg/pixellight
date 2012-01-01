/*********************************************************\
 *  File: Channel.h                                      *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
