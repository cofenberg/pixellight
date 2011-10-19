/*********************************************************\
 *  File: InstallerFunctions.h                                       *
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


#ifndef INSTALLERFUNCTIONS_H
#define INSTALLERFUNCTIONS_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>

//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class InstallerFunctionsImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    [TODO] write a description
*
*  @note
*    - Implementation of the bridge design pattern, this class is the abstraction
*/
class InstallerFunctions {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		InstallerFunctions();

		/**
		*  @brief
		*    Destructor
		*/
		~InstallerFunctions();

		
		void connectProgressEventHandler(PLCore::EventHandler<int> *pProgressEventHandler);
		
		bool installRuntime();

		int getInstallRuntimeProgressSteps();

		bool checkRuntimeInstallation();

		int getCheckRuntimeProgressSteps();

	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		InstallerFunctionsImpl *m_pInstallerFunctionsImpl;	/**< Pointer to the system specific implementation (assumed to be never a null pointer!) */

};


#endif // INSTALLERFUNCTIONS_H
