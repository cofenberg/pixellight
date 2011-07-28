/*********************************************************\
 *  File: PluginPixelLight.h                             *
\*********************************************************/


#ifndef __PLPLUGIN_PLUGIN_PIXELLIGHT_H__
#define __PLPLUGIN_PLUGIN_PIXELLIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPlugin/Plugin.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLEngine {
	class RenderApplication;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight browser plugin
*
*  @remarks
*    This is the main PixelLight plugin for integration in web browsers such as
*    MS Internet Explorer or Mozilla Firefox. It provides a way to load and display
*    PixelLight scenes within a web page and also supports the PL scripting
*    capabilities to develop whole applications that can be embedded on a website.
*/
class PluginPixelLight : public Plugin {


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
		PLPLUGIN_API PluginPixelLight(PluginImpl &cImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLPLUGIN_API virtual ~PluginPixelLight();


	//[-------------------------------------------------------]
	//[ Private virtual Plugin functions                      ]
	//[-------------------------------------------------------]
	private:
		PLPLUGIN_API virtual void OnInit() override;
		PLPLUGIN_API virtual void OnDeInit() override;
		PLPLUGIN_API virtual void OnDraw() override;
		PLPLUGIN_API virtual void OnSize() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLEngine::RenderApplication *m_pApplication;	/**< Applet application, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin


#endif // __PLPLUGIN_PLUGIN_PIXELLIGHT_H__
