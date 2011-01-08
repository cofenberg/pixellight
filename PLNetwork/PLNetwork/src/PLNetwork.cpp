/*********************************************************\
 *  File: PLNetwork.cpp                                  *
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
#ifdef WIN32
	#include "PLNetwork/PLNetworkWindowsIncludes.h"
#endif
#include <PLCore/ModuleMain.h>


//[-------------------------------------------------------]
//[ Module implementation                                 ]
//[-------------------------------------------------------]
pl_module("PLNetwork")
	pl_module_vendor("Copyright (C) 2002-2011 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PLNetwork library")
pl_module_end


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialization/de-initialization guard
*/
class Guard {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Guard()
		{
		#ifdef WIN32
			// Init winsock
			WSAData wsaData;
			WSAStartup(MAKEWORD(2, 2), &wsaData);
		#endif
		}

		/**
		*  @brief
		*    Destructor
		*/
		~Guard()
		{
		#ifdef WIN32
			// Deinit winsock
			WSACleanup();
		#endif
		}


};


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
Guard g_cGuard;	/**< Guard */
