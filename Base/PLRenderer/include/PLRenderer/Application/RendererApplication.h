/*********************************************************\
 *  File: RendererApplication.h                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDERER_APPLICATION_H__
#define __PLRENDERER_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendApplication.h>
#include "PLRenderer/Renderer/SurfaceWindowHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SurfacePainter;
class RendererContext;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Renderer application class
*
*  @remarks
*    An application class for programs that open a single widget to render into.
*/
class RendererApplication : public PLCore::FrontendApplication, public PLRenderer::SurfaceWindowHandler {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, RendererApplication, "PLRenderer", PLCore::FrontendApplication, "Renderer application class")
		#ifdef PLRENDERER_EXPORTS	// The following is only required when compiling PLRenderer
			// Constructors
			pl_constructor_1(ParameterConstructor,	PLCore::Frontend&,	"Parameter constructor. Frontend this application instance is running in as first parameter.",	"")
			// Methods
			pl_method_0(GetPainter,	pl_ret_type(PLRenderer::SurfacePainter*),									"Get the surface painter of the main window. Returns pointer to surface painter of the main window (can be a null pointer).",				"")
			pl_method_1(SetPainter,	pl_ret_type(void),							PLRenderer::SurfacePainter*,	"Set the surface painter of the main window. Pointer to surface painter of the main window (can be a null pointer) as first parameter.",	"")
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
		*  @param[in] cFrontend
		*    Frontend this application instance is running in
		*  @param[in] sSurfacePainter
		*    Surface painter class to use
		*/
		PLRENDERER_API RendererApplication(PLCore::Frontend &cFrontend, const PLCore::String &sSurfacePainter = "PLRenderer::SPDefault");

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~RendererApplication();

		/**
		*  @brief
		*    Returns the renderer context
		*
		*  @return
		*    The renderer context, a null pointer on error
		*/
		inline PLRenderer::RendererContext *GetRendererContext() const;

		/**
		*  @brief
		*    Get surface painter of the main window
		*
		*  @return
		*    Pointer to surface painter of the main window, can be a null pointer
		*/
		PLRENDERER_API PLRenderer::SurfacePainter *GetPainter() const;

		/**
		*  @brief
		*    Set surface painter of the main window
		*
		*  @param[in] pPainter
		*    Pointer to surface painter of the main window, can be a null pointer
		*/
		PLRENDERER_API void SetPainter(PLRenderer::SurfacePainter *pPainter);


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::AbstractLifecycle functions ]
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
		*    - Everything that PLCore::CoreApplication::OnStart() does
		*    - Call OnCreateRendererContext()
		*    - Call OnCreatePainter()
		*    - Return and go on with OnInit()
		*/
		PLRENDERER_API virtual bool OnStart() override;

		/**
		*  @brief
		*    De-initialization function that is called after OnDeInit()
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Save renderer related configuration
		*    - Destroy renderer context
		*    - Everything that FrontendApplication::OnStop() does
		*/
		PLRENDERER_API virtual void OnStop() override;


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::AbstractFrontend functions  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the fullscreen mode was changed
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that PLCore::FrontendApplication::OnFullscreenMode() does
		*    - Update renderer surface
		*/
		PLRENDERER_API virtual void OnFullscreenMode() override;

		/**
		*  @brief
		*    Called to let the frontend draw into it's window
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that PLCore::FrontendApplication::OnDraw() does
		*    - Draw renderer surface
		*/
		PLRENDERER_API virtual void OnDraw() override;

		/**
		*  @brief
		*    Called to let the frontend update it's states
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Everything that PLCore::FrontendApplication::OnUpdate() does
		*    - Update renderer context
		*/
		PLRENDERER_API virtual void OnUpdate() override;


	//[-------------------------------------------------------]
	//[ Protected virtual RendererApplication functions       ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Function that is called to create the application's renderer context
		*
		*  @note
		*    - Part of the application framework initialization function "OnStart()"
		*    - The default implementation is using the "PLRenderer::Config"-configuration to get the settings to use
		*/
		PLRENDERER_API virtual void OnCreateRendererContext();

		/**
		*  @brief
		*    Function that is called to create the application's surface painter
		*
		*  @remarks
		*    The default implementation does the following tasks:
		*    - Sets the default painter
		*
		*  @note
		*    - Part of the application framework initialization function "OnStart()"
		*/
		PLRENDERER_API virtual void OnCreatePainter();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String				 m_sSurfacePainter;		/**< Surface painter class to use */
		PLRenderer::RendererContext	*m_pRendererContext;	/**< The renderer context, can be a null pointer */
		PLRenderer::DisplayMode		*m_pDisplayMode;		/**< Display mode, always valid! */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Reads the current display mode from the configuration
		*/
		void ReadDisplayModeFromConfig();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLRenderer/Application/RendererApplication.inl"


#endif // __PLRENDERER_APPLICATION_H__
