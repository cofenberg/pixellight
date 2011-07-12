/*********************************************************\
 *  File: Application.h                                  *
\*********************************************************/


#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
[!if CORE_APPLICATION]
#include <PLCore/Application/Application.h>
[!endif]
[!if GUI_APPLICATION]
#include <PLGui/Application/GuiApplication.h>
[!endif]
[!if RENDER_APPLICATION]
#include <PLRenderer/Application/RenderApplication.h>
[!endif]
[!if SCENE_APPLICATION]
#include <PLEngine/Application/SceneApplication.h>
[!endif]
[!if BASIC_SCENE_APPLICATION]
#include <PLEngine/Application/BasicSceneApplication.h>
[!endif]
[!if SAMPLE_SCENE_APPLICATION]
#include <PLEngine/Application/SampleSceneApplication.h>
[!endif]


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*/
[!if CORE_APPLICATION]
class Application : public PLCore::Application {
[!endif]
[!if GUI_APPLICATION]
class Application : public PLGui::GuiApplication {
[!endif]
[!if RENDER_APPLICATION]
class Application : public PLRenderer::RenderApplication {
[!endif]
[!if SCENE_APPLICATION]
class Application : public PLEngine::SceneApplication {
[!endif]
[!if BASIC_SCENE_APPLICATION]
class Application : public PLEngine::BasicSceneApplication {
[!endif]
[!if SAMPLE_SCENE_APPLICATION]
class Application : public PLEngine::SampleSceneApplication {
[!endif]


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Application();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Application();


};


#endif // __APPLICATION_H__
