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
#include <PLCore/String/String.h>
#include <PLCore/Base/Event/Event.h>
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

		PLCore::String getLastErrorDescription();

		PLCore::String getLastSuccessMessage();
				
	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<int> m_pEventProgressUpdate;

	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		static const int INSTALL_RUNTIME_PROGRESS_STEPS = 8;
		static const int CHECK_RUNTIME_PROGRESS_STEPS = 4;

		PLCore::String m_sLastErrorMessage;
		PLCore::String m_sLastSuccessMessage;
};


#endif // INSTALLERFUNCTIONS_H
