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


#ifndef __PLCORE_APPLICATION_H__
#define __PLCORE_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Frontend/Frontend.h"
#include "PLCore/Application/CoreApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


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
*
*  @note
*    - A frontend application is always running within a frontend
*/
class FrontendApplication : public CoreApplication, protected AbstractFrontend {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FrontendPixelLight;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, FrontendApplication, "PLCore", PLCore::CoreApplication, "Frontend application class")
		#ifdef PLCORE_EXPORTS	// The following is only required when compiling PLCore
			// Methods
			pl_method_0(GetFrontend,	pl_ret_type(Frontend&),	"Returns the frontend this application is running in.",	"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the frontend this application is running in
		*
		*  @return
		*    Frontend this application instance is running in
		*/
		PLCORE_API Frontend &GetFrontend() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFrontend
		*    Frontend this application instance is running in
		*/
		PLCORE_API FrontendApplication(Frontend &cFrontend);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~FrontendApplication();


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractFrontend functions          ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the window size has been changed
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLCORE_API virtual void OnSize() override;

		/**
		*  @brief
		*    Called when the display mode was changed
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLCORE_API virtual void OnDisplayMode() override;

		/**
		*  @brief
		*    Called when the fullscreen mode was changed
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLCORE_API virtual void OnFullscreenMode() override;

		/**
		*  @brief
		*    Called to let the frontend draw into it's window
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLCORE_API virtual void OnDraw() override;

		/**
		*  @brief
		*    Called to let the frontend update it's states
		*
		*  @remarks
		*    You can use this method to do work you have to perform on a regular basis. It's
		*    recommended to keep the work done within the implementation as compact as possible.
		*    Don't use this function to perform 'polling'-everything, use events or if required
		*    for example timers or threads instead.
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLCORE_API virtual void OnUpdate() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Frontend *m_pFrontend;	/**< Frontend the application is running in, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_APPLICATION_H__
