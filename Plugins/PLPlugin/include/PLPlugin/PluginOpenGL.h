/*********************************************************\
 *  File: PluginOpenGL.h                                 *
\*********************************************************/


#ifndef __PLPLUGIN_PLUGIN_OPENGL_H__
#define __PLPLUGIN_PLUGIN_OPENGL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPlugin/Plugin.h"
#ifdef WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Simple test plugin that uses OpenGL
*
*  @remarks
*    This is a test plugin which uses OpenGL to display a spinning colored
*    rectangle. It can be used easily to test the PLPlugin integration when
*    developing a new backend.
*/
class PluginOpenGL : public Plugin {


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
		PLPLUGIN_API PluginOpenGL(PluginImpl &cImpl);

		/**
		*  @brief
		*    Destructor
		*/
		virtual PLPLUGIN_API ~PluginOpenGL();


	//[-------------------------------------------------------]
	//[ Private virtual Plugin functions                      ]
	//[-------------------------------------------------------]
	private:
		PLPLUGIN_API virtual void OnInit();
		PLPLUGIN_API virtual void OnDeInit();
		PLPLUGIN_API virtual void OnDraw();
		PLPLUGIN_API virtual void OnSize();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initialize OpenGL
		*/
		void InitGL();

		/**
		*  @brief
		*    Resize GL scene to fit the current window size
		*/
		void ResizeGL();

		/**
		*  @brief
		*    Draw scene
		*/
		void DrawGL();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HGLRC	m_hRC;		/**< OpenGL rendering context */
		float	m_fAngle;	/**< Current rotation angle of the rectangle */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin


#endif // __PLPLUGIN_PLUGIN_H__
