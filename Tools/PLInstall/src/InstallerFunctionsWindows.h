/*********************************************************\
 *  File: InstallerFunctionsWindows.h                                *
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


#ifndef INSTALLERFUNCTIONS_WINDOWS_H
#define INSTALLERFUNCTIONS_WINDOWS_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
// TODO: remove this includes when PLCore::Runtime can handle dynamic libs when linked static
#include <PLCore/Runtime.h>
//-----------------
#include "InstallerFunctionsImpl.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows 'DynLib' implementation
*/
class InstallerFunctionsWindows : public InstallerFunctionsImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class InstallerFunctions;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		InstallerFunctionsWindows();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~InstallerFunctionsWindows();

		
	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<int> EventProgressUpdate;

	//[-------------------------------------------------------]
	//[ Private virtual InstallerFunctionsImpl functions      ]
	//[-------------------------------------------------------]
	protected:
		virtual PLCore::Event<int>* getProgressUpdateEvent() override;
		
		virtual bool installRuntime() override;

		virtual int getInstallRuntimeProgressSteps() override;

		virtual bool checkRuntimeInstallation() override;

		virtual int getCheckRuntimeProgressSteps() override;

		virtual PLCore::String getErrorDescription() override;
		
	//[-------------------------------------------------------]
	//[ Private InstallerFunctionsWindows methods			  ]
	//[-------------------------------------------------------]
	private:
		bool CheckWindowsVersion ();
		void broadcastNewPathEnvironment();

		
		// TODO: THIS METHODS SHOULD WORK WITH THE STATIC LINKED PLCORE TOO!!! 
		// this is just a copy from Runtime.h ... should be corrected there and the functions from Runtime should be used!!
		PLCore::String GetSystemDirectory();
		PLCore::String GetDirectoryDynamic(PLCore::Runtime::EType nType);
		PLCore::String GetPLCoreSharedLibraryName();

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		static const int INSTALL_RUNTIME_PROGRESS_STEPS = 7;
		static const int CHECK_RUNTIME_PROGRESS_STEPS = 3;

		PLCore::String lastErrorMessage;

};


#endif // INSTALLERFUNCTIONS_WINDOWS_H
