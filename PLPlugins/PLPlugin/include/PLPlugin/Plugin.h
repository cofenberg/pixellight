/*********************************************************\
 *  File: Plugin.h                                       *
\*********************************************************/


#ifndef __PLPLUGIN_PLUGIN_H__
#define __PLPLUGIN_PLUGIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
#include "PLPlugin/PLPlugin.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PluginImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract plugin base class
*
*  @remarks
*    This base class provides an abstract plugin API which is used to develop
*    an actual PixelLight plugin class. Concrete wrappers for certain browsers,
*    such as MS Internet Explorer or Mozilla Firefox are used to map the browser
*    specific plugin API to this general base class.
*/
class Plugin {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PluginImpl;


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
		PLPLUGIN_API Plugin(PluginImpl &cImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLPLUGIN_API virtual ~Plugin();

		/**
		*  @brief
		*    Get window width
		*
		*  @return
		*    Width
		*/
		PLPLUGIN_API PLGeneral::uint32 GetWidth() const;

		/**
		*  @brief
		*    Get window height
		*
		*  @return
		*    Height
		*/
		PLPLUGIN_API PLGeneral::uint32 GetHeight() const;

		/**
		*  @brief
		*    Redraw plugin window
		*/
		PLPLUGIN_API void Redraw();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Get plugin implementation
		*
		*  @return
		*    Pointer to the implementation backend
		*/
		PLPLUGIN_API PluginImpl *GetImpl() const;


	//[-------------------------------------------------------]
	//[ Protected virtual Plugin functions                    ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called to initialize the plugin
		*/
		virtual void OnInit() = 0;

		/**
		*  @brief
		*    Called to deinitialize the plugin
		*/
		virtual void OnDeInit() = 0;

		/**
		*  @brief
		*    Called to let the plugin draw into it's window
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
		PluginImpl *m_pImpl;	/**< Pointer to implementation backend */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin


#endif // __PLPLUGIN_PLUGIN_H__
