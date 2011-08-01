/*********************************************************\
 *  File: Frontend.h                                     *
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


#ifndef __PLFRONTEND_FRONTEND_H__
#define __PLFRONTEND_FRONTEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include "PLFrontend/PLFrontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontend {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FrontendImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract frontend base class
*
*  @remarks
*    This base class provides an abstract frontend API which is used to develop
*    an actual PixelLight frontend class. Concrete wrappers for certain browsers,
*    such as MS Internet Explorer or Mozilla Firefox are used to map the browser
*    specific frontend API to this general base class.
*/
class Frontend {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FrontendImpl;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cImpl
		*    Implementation object
		*/
		PLFRONTEND_API Frontend(FrontendImpl &cImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTEND_API virtual ~Frontend();

		/**
		*  @brief
		*    Get window width
		*
		*  @return
		*    Width
		*/
		PLFRONTEND_API PLCore::uint32 GetWidth() const;

		/**
		*  @brief
		*    Get window height
		*
		*  @return
		*    Height
		*/
		PLFRONTEND_API PLCore::uint32 GetHeight() const;

		/**
		*  @brief
		*    Redraw frontend window
		*/
		PLFRONTEND_API void Redraw();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Get frontend implementation
		*
		*  @return
		*    Pointer to the implementation backend, can be a null pointer
		*/
		PLFRONTEND_API FrontendImpl *GetImpl() const;


	//[-------------------------------------------------------]
	//[ Protected virtual Frontend functions                  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called to initialize the frontend
		*/
		virtual void OnInit() = 0;

		/**
		*  @brief
		*    Called to deinitialize the frontend
		*/
		virtual void OnDeInit() = 0;

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
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Implementation
		FrontendImpl *m_pImpl;	/**< Pointer to implementation backend, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontend


#endif // __PLFRONTEND_FRONTEND_H__
