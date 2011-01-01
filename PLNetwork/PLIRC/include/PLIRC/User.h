/*********************************************************\
 *  File: User.h                                         *
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


#ifndef __PLIRC_USER_H__
#define __PLIRC_USER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
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
		PLIRC_API User(const PLGeneral::String &sNick, bool bOp, bool bVoice);
		PLIRC_API ~User();

		// Get the nick name
		PLIRC_API PLGeneral::String GetNick() const;

		// Set the nick name
		PLIRC_API void SetNick(const PLGeneral::String &sNick);

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
		PLGeneral::String m_sNick;	/**< Nick name */
		bool			  m_bOp;	/**< Op mode */
		bool			  m_bVoice;	/**< Voice mode */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLIRC


#endif // __PLIRC_USER_H__
