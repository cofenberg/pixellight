/*********************************************************\
 *  File: RenderApplication.h                           *
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


#ifndef __PLENGINE_RENDER_APPLICATION_H__
#define __PLENGINE_RENDER_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendApplication.h>
#include <PLRenderer/Renderer/SurfaceWindowHandler.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class SurfacePainter;
	class RendererContext;
}
namespace PLInput {
	class VirtualController;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Render application class
*
*  @remarks
*    An application class for programs that open a single widget to render into.
*/
class RenderApplication : public PLCore::FrontendApplication, public PLRenderer::SurfaceWindowHandler {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, RenderApplication, "PLEngine", PLCore::FrontendApplication, "Render application class")
		#ifdef PLENGINE_EXPORTS	// The following is only required when compiling PLEngine
			// Constructors
			pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
			// Methods
			pl_method_0(GetPainter,			pl_ret_type(PLRenderer::SurfacePainter*),									"Get the surface painter of the main window. Returns pointer to surface painter of the main window (can be a null pointer).",																																																																																															"")
			pl_method_1(SetPainter,			pl_ret_type(void),							PLRenderer::SurfacePainter*,	"Set the surface painter of the main window. Pointer to surface painter of the main window (can be a null pointer) as first parameter.",																																																																																												"")
			pl_method_0(GetInputController,	pl_ret_type(PLInput::VirtualController*),									"Get the virtual input controller (can be a null pointer).",																																																																																																															"")
			pl_method_1(SetInputController,	pl_ret_type(void),							PLInput::VirtualController*,	"Set the virtual input controller. Virtual input controller (can be a null pointer) as first parameter.",																																																																																																				"")
			pl_method_0(IsFullscreen,		pl_ret_type(bool),															"Returns whether or not the main window is currently fullscreen or not. Returns 'true' if the main window is currently fullscreen, else 'false'.",																																																																																										"")
			pl_method_1(SetFullscreen,		pl_ret_type(void),							bool,							"Sets whether or not the main window is currently fullscreen or not. 'true' as first parameter if the main window is currently fullscreen, else 'false'.",																																																																																								"")
			pl_method_1(Update,				pl_ret_type(bool),							bool,							"Update the application. Force update at once? as first parameter (do this only if you really need it!). Returns 'true' when the update was performed, else 'false' (maybe there's a frame rate limitation and the update wasn't forced). This method is called continously from the main loop of the application. It is called either by the OnRun() method of an Application, or from the outside, if the application is embedded in another application's main loop (which is the case for e.g. browser plugins).",	"")
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
		*  @param[in] sSurfacePainter
		*    Surface painter class to use
		*/
		PL_API RenderApplication(const PLCore::String &sSurfacePainter = "PLRenderer::SPDefault");

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~RenderApplication();

		/**
		*  @brief
		*    Returns the renderer context
		*
		*  @return
		*    The renderer context, a null pointer on error
		*/
		PL_API PLRenderer::RendererContext *GetRendererContext() const;

		/**
		*  @brief
		*    Get surface painter of the main window
		*
		*  @return
		*    Pointer to surface painter of the main window, can be a null pointer
		*/
		PL_API PLRenderer::SurfacePainter *GetPainter() const;

		/**
		*  @brief
		*    Set surface painter of the main window
		*
		*  @param[in] pPainter
		*    Pointer to surface painter of the main window, can be a null pointer
		*/
		PL_API void SetPainter(PLRenderer::SurfacePainter *pPainter);

		/**
		*  @brief
		*    Get virtual input controller
		*
		*  @return
		*    Virtual input controller (can be a null pointer)
		*/
		PL_API PLInput::VirtualController *GetInputController() const;

		/**
		*  @brief
		*    Set virtual input controller
		*
		*  @param[in] pInputController
		*    Virtual input controller (can be a null pointer)
		*/
		PL_API void SetInputController(PLInput::VirtualController *pInputController);

		/**
		*  @brief
		*    Returns whether or not the main window is currently fullscreen or not
		*
		*  @return
		*    'true' if the main window is currently fullscreen, else 'false'
		*/
		PL_API bool IsFullscreen() const;

		/**
		*  @brief
		*    Sets whether or not the main window is currently fullscreen or not
		*
		*  @param[in] bFullscreen
		*    'true' if the main window is currently fullscreen, else 'false'
		*/
		PL_API void SetFullscreen(bool bFullscreen);

		/**
		*  @brief
		*    Update application
		*
		*  @param[in] bForceUpdate
		*    Force update at once? (do this ONLY if you REALLY need it!)
		*
		*  @return
		*    'true' when the update was performed, else 'false'
		*    (maybe there's a frame rate limitation and the update wasn't forced)
		*
		*  @remarks
		*    This method is called continously from the main loop of the application.
		*    It is called either by the OnRun() method of an Application, or from the outside,
		*    if the application is embedded in another application's main loop (which is the
		*    case for e.g. browser plugins).
		*/
		PL_API bool Update(bool bForceUpdate = false);


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::ConsoleApplication functions ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initialization function that is called prior to OnInit()
		*
		*  @return
		*    'true' if all went fine, else 'false' which will stop the application
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that ConsoleApplication::Init() does
		*    - Call OnCreateRendererContext()
		*    - Set default font according to config
		*    - Call OnCreatePainter()
		*    - Initialize input system
		*    - Call OnCreateInputController()
		*    - Return and go on with OnInit()
		*/
		PL_API virtual bool Init() override;

		/**
		*  @brief
		*    De-initialization function that is called after OnDeInit()
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Destroy main window
		*    - Destroy renderer context
		*    - Everything that GuiApplication::DeInit() does
		*/
		PL_API virtual void DeInit() override;


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::FrontendApplication functions ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void OnDraw() override;


	//[-------------------------------------------------------]
	//[ Protected virtual RenderApplication functions         ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Function that is called to create the application's renderer context
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*    - Currently a 'RendererOpenGL' renderer context is created within the default implementation
		*/
		PL_API virtual void OnCreateRendererContext();

		/**
		*  @brief
		*    Function that is called to create the application's surface painter
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*/
		PL_API virtual void OnCreatePainter();

		/**
		*  @brief
		*    Function that is called to initialize the application's virtual input controller
		*
		*  @note
		*    - Part of the application framework initialization function "Init()"
		*    - In the default implementation, an instance of VirtualStandardController is created
		*/
		PL_API virtual void OnCreateInputController();

		/**
		*  @brief
		*    Function that is called once per update loop
		*
		*  @return
		*    'true' when the update was performed, else 'false'
		*    (an implementation has blocked the update due some own criterion)
		*
		*  @remarks
		*    You can use this function to do work you have to to within each frame. It's
		*    recommended to keep the work done within the implementation as compact as possible.
		*    Don't use this function to perform 'polling'-everything, use events or if required
		*    for example timers instead.
		*
		*  @note
		*    - The default implementation updates for example the renderer context, so don't
		*      forget to call this function when overwriting it!
		*    - Don't call this function directly, use 'Update()' instead
		*/
		PL_API virtual bool OnUpdate();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String				 m_sSurfacePainter;		/**< Surface painter class to use */
		PLRenderer::RendererContext	*m_pRendererContext;	/**< The renderer context, can be a null pointer */
		PLInput::VirtualController	*m_pInputController;	/**< Virtual input controller, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_RENDER_APPLICATION_H__
