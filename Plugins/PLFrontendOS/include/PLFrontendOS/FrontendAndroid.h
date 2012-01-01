/*********************************************************\
 *  File: FrontendAndroid.h                              *
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


#ifndef __PLFRONTENDOS_FRONTENDANDROID_H__
#define __PLFRONTENDOS_FRONTENDANDROID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <android_native_app_glue.h>
#include <PLCore/Frontend/FrontendImpl.h>
#include <PLCore/Frontend/FrontendPixelLight.h>
#include "PLFrontendOS/PLFrontendOS.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendOS {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Android frontend implementation class
*
* @note
*   - Several comments are copied from "android_native_app_glue.h" to make it easier to follow the program flow
*/
class FrontendAndroid : public PLCore::FrontendImpl {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDOS_RTTI_EXPORT, FrontendAndroid, "PLFrontendOS", PLCore::FrontendImpl, "Android frontend implementation class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFrontendContext
		*    Frontend context to use (just shared, the given instance must stay valid as long as this frontend lives)
		*  @param[in] cAndroidApp
		*    Given reference to the native Android application instance
		*/
		PLFRONTENDOS_API FrontendAndroid(const PLCore::FrontendContext &cFrontendContext, struct android_app &cAndroidApp);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDOS_API virtual ~FrontendAndroid();


	//[-------------------------------------------------------]
	//[ Private "android_native_app_glue.h" callback functions ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Process the next main command
		*
		*  @param[in] app
		*   Pointer to the native Android application instance, always valid! (do NOT delete this pointer!)
		*  @param[in] cmd
		*    Main app commands (APP_CMD_*) to process
		*/
		static void onAppCmd(struct android_app* app, int32_t cmd);

		/**
		*  @brief
		*    Process the next input event
		*
		*  @param[in] app
		*   Pointer to the native Android application instance, always valid! (do NOT delete this pointer!)
		*  @param[in] event
		*    Input event to process, always valid! (do NOT delete this pointer!)
		*
		*  @return
		*    1 if you have handled the event, 0 for any default dispatching
		*
		*  @note
		*    At this point the event has already been pre-dispatched, and it will be finished upon return
		*/
		static int32_t onInputEvent(struct android_app* app, struct AInputEvent* event);


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::FrontendImpl functions        ]
	//[-------------------------------------------------------]
	private:
		virtual int Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments) override;
		virtual PLCore::handle GetNativeWindowHandle() const override;
		virtual void Redraw() override;
		virtual void Ping() override;
		virtual PLCore::String GetTitle() const override;
		virtual void SetTitle(const PLCore::String &sTitle) override;
		virtual int GetX() const override;
		virtual int GetY() const override;
		virtual PLCore::uint32 GetWidth() const override;
		virtual PLCore::uint32 GetHeight() const override;
		virtual void SetPositionSize(int nX, int nY, PLCore::uint32 nWidth, PLCore::uint32 nHeight) override;
		virtual bool GetToggleFullscreenMode() const override;
		virtual void SetToggleFullscreenMode(bool bToggleFullscreenMode) override;
		virtual bool GetFullscreenAltTab() const override;
		virtual void SetFullscreenAltTab(bool bAllowed) override;
		virtual bool IsFullscreen() const override;
		virtual void SetFullscreen(bool bFullscreen) override;
		virtual void RefreshFullscreen() override;
		virtual bool IsMouseOver() const override;
		virtual int GetMousePositionX() const override;
		virtual int GetMousePositionY() const override;
		virtual bool IsMouseVisible() const override;
		virtual void SetMouseVisible(bool bVisible) override;
		virtual void SetTrapMouse(bool bTrap) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		struct android_app		   *m_pAndroidApp;		/**< Given pointer to the native Android application instance, always valid! (do NOT delete this pointer!) */
		PLCore::FrontendPixelLight	m_cFrontend;
		bool						m_bQuit;
		PLCore::uint64				m_nTimeToWait;		/**< Time to wait */
		bool						m_bAnimating;
		// Mouse emulation
		int							m_nMousePositionX;	/**< Current mouse x position */
		int							m_nMousePositionY;	/**< Current mouse y position */
		bool						m_bMouseVisible;	/**< Is the mouse cursor currently visible? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS


#endif // __PLFRONTENDOS_FRONTENDANDROID_H__
