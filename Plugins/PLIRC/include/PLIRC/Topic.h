/*********************************************************\
 *  File: Topic.h                                        *
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


#ifndef __PLIRC_TOPIC_H__
#define __PLIRC_TOPIC_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Time.h>
#include "PLIRC/PLIRC.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLIRC {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    IRC Topic
*/
class Topic {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		// Construction/Destruction
		PLIRC_API Topic();
		PLIRC_API Topic(const PLCore::String &sNick, const PLCore::String &sTopic, const PLCore::Time &cDate);
		PLIRC_API ~Topic();

		// Get nick name
		PLIRC_API PLCore::String GetNick() const;

		// Set nick name
		PLIRC_API void SetNick(const PLCore::String &sNick);

		// Get topic
		PLIRC_API PLCore::String GetTopic() const;

		// Set topic
		PLIRC_API void SetTopic(const PLCore::String &sTopic);

		// Get date
		PLIRC_API const PLCore::Time &GetDate() const;

		// Set date
		PLIRC_API void SetDate(const PLCore::Time &cDate);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sNick;		/**< Nick name of the user that sets the topic */
		PLCore::String m_sTopic;	/**< Topic */
		PLCore::Time   m_cDate;		/**< Date the topic was set */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC


#endif // __PLIRC_TOPIC_H__
