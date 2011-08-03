/*********************************************************\
 *  File: FrontendApplication.h                          *
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


#ifndef __PLFRONTEND_APPLICATION_H__
#define __PLFRONTEND_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Application/ConsoleApplication.h>
#include "PLFrontend/PLFrontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontend {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Frontend;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Frontend application class
*/
class FrontendApplication : public PLCore::ConsoleApplication {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FrontendPixelLight;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTEND_RTTI_EXPORT, FrontendApplication, "PLFrontend", PLCore::ConsoleApplication, "Frontend application class")
		#ifdef PLFRONTEND_EXPORTS	// The following is only required when compiling PLFrontend
			// Constructors
			pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
			// Methods
			pl_method_0(GetFrontend,	pl_ret_type(Frontend*),	"Get the frontend. Returns pointer to the frontend of the application, a null pointer on error.",	"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sFrontend
		*    Class name of the frontend implementation to use, can be empty
		*/
		PLFRONTEND_API FrontendApplication(const PLCore::String &sFrontend = "");

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTEND_API virtual ~FrontendApplication();

		/**
		*  @brief
		*    Get frontend
		*
		*  @return
		*    Frontend, can be a null pointer
		*/
		PLFRONTEND_API Frontend *GetFrontend() const;


	//[-------------------------------------------------------]
	//[ Protected virtual FrontendApplication functions       ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called to let the frontend application draw into it's window
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLFRONTEND_API virtual void OnDraw();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Frontend *m_pFrontend;	/**< Frontend of the application (can be a null pointer) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontend


#endif // __PLFRONTEND_APPLICATION_H__
