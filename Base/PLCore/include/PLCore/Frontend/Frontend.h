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


#ifndef __PLCORE_FRONTEND_H__
#define __PLCORE_FRONTEND_H__
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
class String;
class FrontendImpl;
template <class ValueType> class Array;


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
class Frontend : public Object, protected AbstractLifecycle, protected AbstractFrontend {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FrontendImpl;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, Frontend, "PLCore", PLCore::Object, "Abstract frontend base class")
		#ifdef PLCORE_EXPORTS	// The following is only required when compiling PLCore
			// Methods
			pl_method_0(Redraw,						pl_ret_type(void),				"Redraw frontend window.",																																		"")
			pl_method_0(Ping,						pl_ret_type(void),				"Give the frontend a chance to process OS messages.",																											"")
			pl_method_0(RedrawAndPing,				pl_ret_type(void),				"Redraw frontend window and give the frontend a chance to process OS messages.",																				"")
			pl_method_0(GetWidth,					pl_ret_type(uint32),			"Returns the window width.",																																	"")
			pl_method_0(GetHeight,					pl_ret_type(uint32),			"Returns the window height.",																																	"")
			pl_method_0(GetToggleFullscreenMode,	pl_ret_type(bool),				"Returns whether it's allowed to toggle the fullscreen mode using hotkeys. 'true' if it's possible to toggle the fullscreen mode using hotkeys, else 'false'.",	"")
			pl_method_1(SetToggleFullscreenMode,	pl_ret_type(void),		bool,	"Sets whether it's allowed to toggle the fullscreen mode using hotkeys. 'true' as first parameter to allow it, else 'false'.",									"")
			pl_method_0(GetFullscreenAltTab,		pl_ret_type(bool),				"Returns whether it's allowed to use Alt-Tab if fullscreen mode is used. 'true' if it's possible to use Alt-Tab if fullscreen mode is used, else 'false'.",		"")
			pl_method_1(SetFullscreenAltTab,		pl_ret_type(void),		bool,	"Sets whether it's allowed to use Alt-Tab if fullscreen mode is used. 'true' as first parameter to allow it, else 'false'.",									"")
			pl_method_0(IsFullscreen,				pl_ret_type(bool),				"Returns whether or not the window is currently fullscreen or not. Returns 'true' if the window is currently fullscreen, else 'false'.",						"")
			pl_method_1(SetFullscreen,				pl_ret_type(void),		bool,	"Sets whether or not the window is currently fullscreen or not. 'true' as first parameter if the window is currently fullscreen, else 'false'.",				"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Run the frontend
		*
		*  @param[in] sExecutableFilename
		*    Absolute application executable filename
		*  @param[in] lstArguments
		*    List of arguments to the program
		*  @param[in] sFrontend
		*    Name of the frontend RTTI class to use
		*  @param[in] sFrontendConstructor
		*    Name of the frontend RTTI class constructor to use
		*  @param[in] sFrontendConstructorParameters
		*    Parameters for the frontend RTTI class constructor
		*  @param[in] sFrontendParameters
		*    Parameters for the instanced frontend RTTI class
		*  @param[in] sFrontendImplementation
		*    Name of the frontend implementation RTTI class to use
		*  @param[in] sFrontendImplementationConstructor
		*    Name of the frontend implementation RTTI class constructor to use
		*  @param[in] sFrontendImplementationConstructorParameters
		*    Parameters for the frontend implementation RTTI class constructor
		*  @param[in] sFrontendImplementationParameters
		*    Parameters for the instanced frontend implementation RTTI class
		*
		*  @return
		*    Exit code (usually 0 means no error), usually <0 when there was an error
		*    (e.g. an embeded frontend implementation is run and controlled by another application and can't be run by using this method)
		*/
		PLCORE_API static int Run(const String &sExecutableFilename,
								  const Array<String> &lstArguments,
								  const String &sFrontend										= "PLCore::FrontendPixelLight",
								  const String &sFrontendConstructor							= "",
								  const String &sFrontendConstructorParameters					= "",
								  const String &sFrontendParameters								= "",
								  const String &sFrontendImplementation							= "PLFrontendOS::Frontend",
								  const String &sFrontendImplementationConstructor				= "",
								  const String &sFrontendImplementationConstructorParameters	= "",
								  const String &sFrontendImplementationParameters				= "");

		/**
		*  @brief
		*    Run the frontend using traditional C-arguments
		*
		*  @param[in] argc
		*    Number of C-arguments
		*  @param[in] argv
		*    C-arguments, must be valid
		*  @param[in] sFrontend
		*    Name of the frontend RTTI class to use
		*  @param[in] sFrontendConstructor
		*    Name of the frontend RTTI class constructor to use
		*  @param[in] sFrontendConstructorParameters
		*    Parameters for the frontend RTTI class constructor
		*  @param[in] sFrontendParameters
		*    Parameters for the instanced frontend RTTI class
		*  @param[in] sFrontendImplementation
		*    Name of the frontend implementation RTTI class to use
		*  @param[in] sFrontendImplementationConstructor
		*    Name of the frontend implementation RTTI class constructor to use
		*  @param[in] sFrontendImplementationConstructorParameters
		*    Parameters for the frontend implementation RTTI class constructor
		*  @param[in] sFrontendImplementationParameters
		*    Parameters for the instanced frontend implementation RTTI class
		*
		*  @return
		*    Exit code (usually 0 means no error), usually <0 when there was an error
		*    (e.g. an embeded frontend implementation is run and controlled by another application and can't be run by using this method)
		*/
		PLCORE_API static int Run(int argc,
								  char **argv,
								  const String &sFrontend										= "PLCore::FrontendPixelLight",
								  const String &sFrontendConstructor							= "",
								  const String &sFrontendConstructorParameters					= "",
								  const String &sFrontendParameters								= "",
								  const String &sFrontendImplementation							= "PLFrontendOS::Frontend",
								  const String &sFrontendImplementationConstructor				= "",
								  const String &sFrontendImplementationConstructorParameters	= "",
								  const String &sFrontendImplementationParameters				= "");
		PLCORE_API static int Run(int argc,
								  wchar_t **argv,
								  const String &sFrontend										= "PLCore::FrontendPixelLight",
								  const String &sFrontendConstructor							= "",
								  const String &sFrontendConstructorParameters					= "",
								  const String &sFrontendParameters								= "",
								  const String &sFrontendImplementation							= "PLFrontendOS::Frontend",
								  const String &sFrontendImplementationConstructor				= "",
								  const String &sFrontendImplementationConstructorParameters	= "",
								  const String &sFrontendImplementationParameters				= "");


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFrontendImpl
		*    Frontend implementation instance
		*/
		PLCORE_API Frontend(FrontendImpl &cFrontendImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Frontend();

		/**
		*  @brief
		*    Get native window handle
		*
		*  @return
		*    Native window handle for the frontend window, can be a null pointer
		*/
		PLCORE_API handle GetNativeWindowHandle() const;

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
		PLCORE_API void Redraw();

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
		*    - Doesn't include "Redraw()"
		*/
		PLCORE_API void Ping() const;

		/**
		*  @brief
		*    Redraw frontend window and give the frontend a chance to process OS messages
		*
		*  @remarks
		*    Calls "Redraw()", then "Ping()".
		*
		*  @note
		*    - Whenever possible, don't use this method, do heavy work within e.g. threads
		*/
		PLCORE_API void RedrawAndPing();

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
		//[ Fullscreen                                            ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Gets whether it's allowed to toggle the fullscreen mode using hotkeys
		*
		*  @return
		*    'true' if it's possible to toggle the fullscreen mode using hotkeys, else 'false'
		*/
		PLCORE_API bool GetToggleFullscreenMode() const;

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
		PLCORE_API void SetToggleFullscreenMode(bool bToggleFullscreenMode);

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
		PLCORE_API bool GetFullscreenAltTab() const;

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
		PLCORE_API void SetFullscreenAltTab(bool bAllowed);

		/**
		*  @brief
		*    Returns whether the window is in fullscreen mode or not
		*
		*  @return
		*    'true' if the window is in fullscreen mode, else 'false'
		*/
		PLCORE_API bool IsFullscreen() const;

		/**
		*  @brief
		*    Sets the window's fullscreen mode
		*
		*  @param[in] bFullscreen
		*    'true' if the window should be in fullscreen mode, else 'false'
		*/
		PLCORE_API void SetFullscreen(bool bFullscreen);


	//[-------------------------------------------------------]
	//[ Public virtual Frontend functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether or not the frontend is currently running
		*
		*  @return
		*    'true' if the frontend is currently running, else 'false'
		*/
		virtual bool IsRunning() const = 0;


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
		PLCORE_API FrontendImpl *GetImpl() const;


	//[-------------------------------------------------------]
	//[ Protected virtual Frontend functions                  ]
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
		*    The default implementation does the following tasks:
		*    - none (implement in derived classes)
		*/
		PLCORE_API virtual void OnRun(const String &sExecutableFilename, const Array<String> &lstArguments);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		FrontendImpl *m_pFrontendImpl;	/**< Pointer to implementation backend, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Creates a frontend implementation instance
		*
		*  @param[in] sFrontendImplementation
		*    Name of the frontend implementation RTTI class to use
		*  @param[in] sFrontendImplementationConstructor
		*    Name of the frontend implementation RTTI class constructor to use
		*  @param[in] sFrontendImplementationConstructorParameters
		*    Parameters for the frontend implementation RTTI class constructor
		*  @param[in] sFrontendImplementationParameters
		*    Parameters for the instanced frontend implementation RTTI class
		*
		*  @return
		*    Frontend implementation instance, null pointer on error
		*/
		static FrontendImpl *CreateFrontendImplementation(const String &sFrontendImplementation,
														  const String &sFrontendImplementationConstructor,
														  const String &sFrontendImplementationConstructorParameters,
														  const String &sFrontendImplementationParameters);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FRONTEND_H__
