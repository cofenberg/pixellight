/*********************************************************\
 *  File: AbstractFrontend.h                             *
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


#ifndef __PLCORE_ABSTRACTFRONTEND_H__
#define __PLCORE_ABSTRACTFRONTEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract frontend class
*/
class AbstractFrontend {


	//[-------------------------------------------------------]
	//[ Public virtual AbstractFrontend functions             ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Called to let the frontend draw into it's window
		*/
		virtual void OnDraw() = 0;

		/**
		*  @brief
		*    Called when the window size has been changed
		*/
		virtual void OnSize() = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		AbstractFrontend();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~AbstractFrontend();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_ABSTRACTFRONTEND_H__
