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
#include "PLCore/Frontend/AbstractFrontend.h"
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
class FrontendImpl : public Object, protected AbstractLifecycle, protected AbstractFrontend {


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
		*    Returns the frontend instance
		*
		*  @return
		*    The frontend instance, can be a null pointer
		*/
		PLCORE_API Frontend *GetFrontend() const;


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractLifecycle functions         ]
	//[-------------------------------------------------------]
	protected:
		PLCORE_API virtual void OnCreate() override;	// Automatically called from within "Frontend::Run()"
		PLCORE_API virtual void OnRestart() override;	// Don't forget to call this within derived frontend implementations
		PLCORE_API virtual bool OnStart() override;		// Don't forget to call this within derived frontend implementations
		PLCORE_API virtual void OnResume() override;	// Don't forget to call this within derived frontend implementations
		PLCORE_API virtual void OnPause() override;		// Don't forget to call this within derived frontend implementations
		PLCORE_API virtual void OnStop() override;		// Don't forget to call this within derived frontend implementations
		PLCORE_API virtual void OnDestroy() override;	// Automatically called from within "Frontend::Run()"


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractFrontend functions          ]
	//[-------------------------------------------------------]
	protected:
		PLCORE_API virtual void OnSize() override;
		PLCORE_API virtual void OnDisplayMode() override;
		PLCORE_API virtual void OnFullscreenMode() override;
		PLCORE_API virtual void OnDraw() override;
		PLCORE_API virtual void OnUpdate() override;
		PLCORE_API virtual void OnDrop(const Container<String> &lstFiles) override;


	//[-------------------------------------------------------]
	//[ Protected virtual FrontendImpl functions              ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the frontend is run
		*
		*  @param[in] sExecutableFilename
		*    Absolute application executable filename
		*  @param[in] lstArguments
		*    List of arguments to the program
		*
		*  @remarks
		*    This frontend method is called just before the frontend calls it's run-method in order to
		*    enter it's main-loop. This means that this method is called between "AbstractLifecycle::OnCreate()"
		*    and "AbstractLifecycle::OnStart()". Use this method for instance to pre-process command line arguments.
		*
		*  @note
		*    - Automatically called from within "Frontend::Run()"
		*/
		PLCORE_API virtual void OnRun(const String &sExecutableFilename, const Array<String> &lstArguments);

		/**
		*  @brief
		*    Called when the frontend should run
		*
		*  @param[in] sExecutableFilename
		*    Absolute application executable filename
		*  @param[in] lstArguments
		*    List of arguments to the program
		*
		*  @return
		*    Exit code (usually 0 means no error), usually <0 when there was an error
		*    (e.g. an embeded frontend implementation is run and controlled by another application and can't be run by using this method)
		*
		*  @note
		*    - The default implementation does nothing at all
		*    - Automatically called from within "Frontend::Run()"
		*/
		PLCORE_API virtual int Run(const String &sExecutableFilename, const Array<String> &lstArguments);

		/**
		*  @brief
		*    Run the frontend using traditional C-arguments
		*
		*  @param[in] argc
		*    Number of C-arguments
		*  @param[in] argv
		*    C-arguments, must be valid
		*
		*  @return
		*    Exit code (usually 0 means no error), usually <0 when there was an error
		*    (e.g. an embeded frontend implementation is run and controlled by another application and can't be run by using this method)
		*
		*  @note
		*    - The default implementation calls the version of the "Run()"-method using PixelLight strings
		*    - Automatically called from within "Frontend::Run()"
		*/
		PLCORE_API virtual int Run(int argc, char **argv);
		PLCORE_API virtual int Run(int argc, wchar_t **argv);

		/**
		*  @brief
		*    Get native window handle
		*
		*  @return
		*    Native window handle for the frontend window, can be a null pointer
		*/
		virtual handle GetNativeWindowHandle() const = 0;

		/**
		*  @brief
		*    Redraw frontend window
		*
		*  @remarks
		*    There are situations were an application may do some heavy work without letting
		*    the frontend a chance to redraw. In such situations, it may be wise
		*    to call this method from time to time to give the frontend a chance to do redraw
		*    itself.
		*
		*  @note
		*    - Whenever possible, don't use this method, do heavy work within e.g. threads
		*    - Depending on the frontend implementation, the redraw may not be immediate
		*    - Doesn't include "Ping()"
		*/
		virtual void Redraw() = 0;

		/**
		*  @brief
		*    Give the frontend a chance to process OS messages
		*
		*  @remarks
		*    There are situations were an application may do some heavy work without letting
		*    the frontend a chance to process OS messages. In such situations, it may be wise
		*    to call this method from time to time to give the frontend a chance to do some
		*    message processing.
		*
		*  @note
		*    - Whenever possible, don't use this method, do heavy work within e.g. threads
		*/
		virtual void Ping() = 0;

		/**
		*  @brief
		*    Get window width
		*
		*  @return
		*    Width
		*/
		virtual uint32 GetWidth() const = 0;

		/**
		*  @brief
		*    Get window height
		*
		*  @return
		*    Height
		*/
		virtual uint32 GetHeight() const = 0;

		//[-------------------------------------------------------]
		//[ Fullscreen                                            ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Gets whether it's allowed to toggle the fullscreen mode using hotkeys
		*
		*  @return
		*    'true' if it's possible to toggle the fullscreen mode using hotkeys, else 'false'
		*/
		virtual bool GetToggleFullscreenMode() const = 0;

		/**
		*  @brief
		*    Sets whether it's allowed to toggle the fullscreen mode using hotkeys
		*
		*  @param[in] bToggleFullscreenMode
		*    Is it allowed to toggle the fullscreen mode using hotkeys?
		*
		*  @note
		*    - By default, it's allowed to switch widgets into fullscreen mode using Alt-Return or AltGr-Return
		*/
		virtual void SetToggleFullscreenMode(bool bToggleFullscreenMode) = 0;

		/**
		*  @brief
		*    Gets whether it's allowed to use Alt-Tab if fullscreen mode is used
		*
		*  @return
		*    'true' if it's possible to use Alt-Tab if fullscreen mode is used, else 'false'
		*
		*  @note
		*    - Widgets only
		*/
		virtual bool GetFullscreenAltTab() const = 0;

		/**
		*  @brief
		*    Sets whether it's allowed to use Alt-Tab if fullscreen mode is used
		*
		*  @param[in] bAllowed
		*    Is it allowed to use Alt-Tab within fullscreen mode?
		*
		*  @note
		*    - By default, it's allowed to use Alt-Tab
		*
		*  @see
		*    - GetFullscreenAltTab()
		*/
		virtual void SetFullscreenAltTab(bool bAllowed) = 0;

		/**
		*  @brief
		*    Returns whether the window is in fullscreen mode or not
		*
		*  @return
		*    'true' if the window is in fullscreen mode, else 'false'
		*/
		virtual bool IsFullscreen() const = 0;

		/**
		*  @brief
		*    Sets the window's fullscreen mode
		*
		*  @param[in] bFullscreen
		*    'true' if the window should be in fullscreen mode, else 'false'
		*/
		virtual void SetFullscreen(bool bFullscreen) = 0;

		//[-------------------------------------------------------]
		//[ Mouse                                                 ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Check if the mouse cursor is visible
		*
		*  @return
		*    'true' if the mouse cursor is visible, else 'false'
		*
		*  @note
		*    - If the mouse cursor is visible in general, it's still possible that it's
		*      invisible over some special widgets.
		*    - If the mouse cursor is invisible in general, it will NEVER be visible!
		*/
		virtual bool IsMouseVisible() const = 0;

		/**
		*  @brief
		*    Set mouse cursor visibility
		*
		*  @param[in] bVisible
		*    Shall the mouse cursor be visible?
		*
		*  @see
		*    - IsMouseVisible()
		*/
		virtual void SetMouseVisible(bool bVisible) = 0;

		/**
		*  @brief
		*    Trap mouse inside the frontend window
		*
		*  @param[in] bTrap
		*    'true' if the mouse should be trapped inside the frontend window, else 'false'
		*/
		virtual void SetTrapMouse(bool bTrap) = 0;


	//[-------------------------------------------------------]
	//[ Protected static functions                            ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Creates a frontend instance
		*
		*  @param[in] cFrontendImpl
		*    Frontend implementation instance
		*  @param[in] sFrontend
		*    Name of the frontend RTTI class to use
		*  @param[in] sFrontendConstructor
		*    Name of the frontend RTTI class constructor to use
		*  @param[in] sFrontendConstructorParameters
		*    Parameters for the frontend RTTI class constructor
		*  @param[in] sFrontendParameters
		*    Parameters for the instanced frontend RTTI class
		*
		*  @return
		*    Frontend instance, null pointer on error
		*/
		PLCORE_API static Frontend *CreateFrontend(FrontendImpl &cFrontendImpl,
												   const String &sFrontend,
												   const String &sFrontendConstructor,
												   const String &sFrontendConstructorParameters,
												   const String &sFrontendParameters);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Frontend *m_pFrontend;	/**< Pointer to frontend, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FRONTEND_IMPL_H__
