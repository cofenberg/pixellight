/*********************************************************\
 *  File: Topic.h                                        *
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
