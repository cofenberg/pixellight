/*********************************************************\
 *  File: InstallerFunctionsImpl.h                                   *
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


#ifndef INSTALLERFUNCTIONS_IMPL_H
#define INSTALLERFUNCTIONS_IMPL_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]

//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for platform specific 'InstallerFunctions' implementations
*
*  @note
*    - Implementation of the bridge design pattern, this class is the implementor of the 'InstallerFunctions' abstraction
*/
class InstallerFunctionsImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class InstallerFunctions;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		InstallerFunctionsImpl();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~InstallerFunctionsImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual InstallerFunctionsImpl functions    ]
	//[-------------------------------------------------------]
	protected:
/*		
		virtual bool IsLoaded() const = 0;
*/
};


#endif // INSTALLERFUNCTIONS_IMPL_H
