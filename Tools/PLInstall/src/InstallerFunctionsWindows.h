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
//		virtual bool IsLoaded() const override;


		virtual PLCore::Event<int>* getProgressUpdateEvent() override;

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:


};


#endif // INSTALLERFUNCTIONS_WINDOWS_H
