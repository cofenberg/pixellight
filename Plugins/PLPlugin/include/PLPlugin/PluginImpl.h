/*********************************************************\
 *  File: PluginImpl.h                                   *
\*********************************************************/


#ifndef __PLPLUGIN_PLUGIN_IMPL_H__
#define __PLPLUGIN_PLUGIN_IMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include "PLPlugin/PLPlugin.h"
#ifdef WIN32
	#include "PLPlugin/PLPluginWin32Includes.h"
#elif defined(LINUX)
	#include "PLPlugin/PLPluginLinuxIncludes.h"
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Plugin;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract plugin implementation base class
*
*  @remarks
*    This base class provides the backend interface for concrete implementations
*    (e.g. for Internet Explorer or Mozilla Firefox plugins).
*/
class PluginImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Plugin;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLPLUGIN_API PluginImpl();

		/**
		*  @brief
		*    Destructor
		*/
		PLPLUGIN_API virtual ~PluginImpl();

		/**
		*  @brief
		*    Get window handle
		*
		*  @return
		*    System handle for the plugin window
		*/
		PLPLUGIN_API PLCore::handle GetWindowHandle() const;

		/**
		*  @brief
		*    Get device context handle
		*
		*  @return
		*    System handle for the device context
		*/
		PLPLUGIN_API PLCore::handle GetDeviceContext() const;

		/**
		*  @brief
		*    Get window width
		*
		*  @return
		*    Width
		*/
		PLPLUGIN_API PLCore::uint32 GetWidth() const;

		/**
		*  @brief
		*    Get window height
		*
		*  @return
		*    Height
		*/
		PLPLUGIN_API PLCore::uint32 GetHeight() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called to initialize the plugin
		*/
		PLPLUGIN_API void OnInit();

		/**
		*  @brief
		*    Called to deinitialize the plugin
		*/
		PLPLUGIN_API void OnDeInit();

		/**
		*  @brief
		*    Called to let the plugin draw into it's window
		*/
		PLPLUGIN_API void OnDraw();

		/**
		*  @brief
		*    Called when the window size has been changed
		*/
		PLPLUGIN_API void OnSize();


	//[-------------------------------------------------------]
	//[ Protected virtual PluginImpl functions                ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Redraw the window
		*/
		virtual void Redraw() = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Plugin
		Plugin	   *m_pPlugin;		/**< Pointer to plugin */

		// General
		int			m_nWidth;		/**< Window width */
		int			m_nHeight;		/**< Window height */

		// Windows specific
		#ifdef WIN32
			HWND	m_hPluginWnd;	/**< Window handle of the plugin container */
			HDC		m_hPluginDC;	/**< Device context */
		#endif

		// Linux specific
		#ifdef LINUX
		#endif


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin


#endif // __PLPLUGIN_PLUGIN_IMPL_H__
