/*********************************************************\
 *  File: User.h                                         *
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


#ifndef __PLIRC_USER_H__
#define __PLIRC_USER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
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
*    IRC User
*/
class User {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		// Construction/Destruction
		PLIRC_API User(const PLCore::String &sNick, bool bOp, bool bVoice);
		PLIRC_API ~User();

		// Get the nick name
		PLIRC_API PLCore::String GetNick() const;

		// Set the nick name
		PLIRC_API void SetNick(const PLCore::String &sNick);

		// Does the user have op mode?
		PLIRC_API bool IsOp() const;

		// Set op mode
		PLIRC_API void SetOp(bool bOp);

		// Does the user have voice mode?
		PLIRC_API bool IsVoice() const;

		// Set voice mode
		PLIRC_API void SetVoice(bool bVoice);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String m_sNick;		/**< Nick name */
		bool		   m_bOp;		/**< Op mode */
		bool		   m_bVoice;	/**< Voice mode */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC


#endif // __PLIRC_USER_H__
