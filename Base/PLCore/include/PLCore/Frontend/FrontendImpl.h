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


#ifndef __PLCORE_FRONTEND_IMPL_H__
#define __PLCORE_FRONTEND_IMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Object.h"
#include "PLCore/Application/AbstractLifecycle.h"


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
*    Abstract frontend implementation base class
*
*  @remarks
*    This base class provides the backend interface for concrete implementations
*    (e.g. for Internet Explorer or Mozilla Firefox frontends).
*/
class FrontendImpl : public Object, protected AbstractLifecycle {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Frontend;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, FrontendImpl, "PLCore", PLCore::Object, "Abstract frontend implementation base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API FrontendImpl();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~FrontendImpl();

		/**
		*  @brief
		*    Get window width
		*
		*  @return
		*    Width
		*/
		PLCORE_API uint32 GetWidth() const;

		/**
		*  @brief
		*    Get window height
		*
		*  @return
		*    Height
		*/
		PLCORE_API uint32 GetHeight() const;


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
		virtual handle GetNativeWindowHandle() const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called to let the frontend draw into it's window
		*/
		PLCORE_API void OnDraw();

		/**
		*  @brief
		*    Called when the window size has been changed
		*/
		PLCORE_API void OnSize();


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractLifecycle functions         ]
	//[-------------------------------------------------------]
	protected:
		PLCORE_API virtual void OnCreate() override;
		PLCORE_API virtual void OnRestart() override;
		PLCORE_API virtual bool OnStart() override;
		PLCORE_API virtual void OnResume() override;
		PLCORE_API virtual void OnPause() override;
		PLCORE_API virtual void OnStop() override;
		PLCORE_API virtual void OnDestroy() override;


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
		virtual int Run(const String &sApplicationClass, const String &sExecutableFilename, const Array<String> &lstArguments) = 0;

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
} // PLCore


#endif // __PLCORE_FRONTEND_IMPL_H__
