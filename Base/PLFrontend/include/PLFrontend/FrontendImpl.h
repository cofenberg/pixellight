/*********************************************************\
 *  File: FrontendImpl.h                                 *
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


#ifndef __PLFRONTEND_FRONTEND_IMPL_H__
#define __PLFRONTEND_FRONTEND_IMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include <PLCore/Base/Object.h>
#include "PLFrontend/PLFrontend.h"
#include "PLFrontend/AbstractFrontendLifecycle.h"


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
*    Abstract frontend implementation base class
*
*  @remarks
*    This base class provides the backend interface for concrete implementations
*    (e.g. for Internet Explorer or Mozilla Firefox frontends).
*/
class FrontendImpl : public PLCore::Object, protected AbstractFrontendLifecycle {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Frontend;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTEND_RTTI_EXPORT, FrontendImpl, "PLFrontend", PLCore::Object, "Abstract frontend implementation base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLFRONTEND_API FrontendImpl();

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTEND_API virtual ~FrontendImpl();

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


	//[-------------------------------------------------------]
	//[ Public virtual FrontendImpl functions                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get native window handle
		*
		*  @return
		*    Native window handle for the frontend window, can be a null pointer
		*/
		virtual PLCore::handle GetNativeWindowHandle() const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called to let the frontend draw into it's window
		*/
		PLFRONTEND_API void OnDraw();

		/**
		*  @brief
		*    Called when the window size has been changed
		*/
		PLFRONTEND_API void OnSize();


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractFrontendLifecycle functions ]
	//[-------------------------------------------------------]
	protected:
		PLFRONTEND_API virtual void OnCreate() override;
		PLFRONTEND_API virtual void OnRestart() override;
		PLFRONTEND_API virtual void OnStart() override;
		PLFRONTEND_API virtual void OnResume() override;
		PLFRONTEND_API virtual void OnPause() override;
		PLFRONTEND_API virtual void OnStop() override;
		PLFRONTEND_API virtual void OnDestroy() override;


	//[-------------------------------------------------------]
	//[ Protected virtual FrontendImpl functions              ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the frontend should run
		*
		*  @param[in] sApplicationClass
		*    Name of the application RTTI class to use (must be derived from "PLCore::FrontendApplication")
		*  @param[in] sExecutableFilename
		*    Absolute application executable filename
		*  @param[in] lstArguments
		*    List of arguments to the program
		*
		*  @return
		*    Exit code (usually 0 means no error), usually <0 when there was an error
		*    (e.g. an embeded frontend implementation is run and controlled by another application and can't be run by using this method)
		*/
		virtual int Run(const PLCore::String &sApplicationClass, const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments) = 0;

		/**
		*  @brief
		*    Redraw the window
		*/
		virtual void Redraw() = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Frontend *m_pFrontend;	/**< Pointer to frontend, can be a null pointer */
		int		  m_nWidth;		/**< Window width */
		int		  m_nHeight;	/**< Window height */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontend


#endif // __PLFRONTEND_FRONTEND_IMPL_H__
