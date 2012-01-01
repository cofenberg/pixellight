/*********************************************************\
 *  File: InstallerFunctions.h                           *
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


#ifndef __PLINSTALL_INSTALLERFUNCTIONS_H__
#define __PLINSTALL_INSTALLERFUNCTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Installer functions
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

		void ConnectProgressEventHandler(PLCore::EventHandler<int> *pProgressEventHandler);
		bool InstallRuntime();
		int GetInstallRuntimeProgressSteps() const;
		bool CheckRuntimeInstallation();
		int GetCheckRuntimeProgressSteps() const;
		PLCore::String GetLastErrorDescription() const;
		PLCore::String GetLastSuccessMessage() const;


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<int> m_cEventProgressUpdate;


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		static const int INSTALL_RUNTIME_PROGRESS_STEPS = 8;
		static const int CHECK_RUNTIME_PROGRESS_STEPS   = 4;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sLastErrorMessage;
		PLCore::String m_sLastSuccessMessage;


};


#endif // __PLINSTALL_INSTALLERFUNCTIONS_H__
