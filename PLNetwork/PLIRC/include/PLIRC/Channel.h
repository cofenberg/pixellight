/*********************************************************\
 *  File: Channel.h                                      *
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


#ifndef __PLIRC_CHANNEL_H__
#define __PLIRC_CHANNEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/List.h>
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
		PLIRC_API Channel(const PLGeneral::String &sName);
		PLIRC_API ~Channel();

		// Get the channel name
		PLIRC_API PLGeneral::String GetName() const;

		// Channel topic
		PLIRC_API const Topic &GetTopic() const;
		PLIRC_API Topic &GetTopic();

		// User list
		PLIRC_API PLGeneral::uint32 GetNumOfUsers() const;
		PLIRC_API const User *GetUser(PLGeneral::uint32 nUser) const;
		PLIRC_API User *GetUser(PLGeneral::uint32 nUser);
		PLIRC_API const User *GetUser(const PLGeneral::String &sNick) const;
		PLIRC_API User *GetUser(const PLGeneral::String &sNick);
		PLIRC_API bool AddUser(const PLGeneral::String &sNick, bool bOp = false, bool bVoice = false);
		PLIRC_API void RemoveUser(const PLGeneral::String &sNick);


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
		PLGeneral::String	   m_sName;		/**< Name of channel */
		Topic				   m_cTopic;	/**< Channel topic */
		PLGeneral::List<User*> m_lstUsers;	/**< User list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC


#endif // __PLIRC_CHANNEL_H__
