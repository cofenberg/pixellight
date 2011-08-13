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


#ifndef __PLFRONTENDQT_FRONTEND_H__
#define __PLFRONTENDQT_FRONTEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendImpl.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QWidget;
	class QCursor;
QT_END_NAMESPACE


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Qt frontend implementation class
*/
class Frontend : public PLCore::FrontendImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class FrontendMainWindow;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Frontend, "PLFrontendQt", PLCore::FrontendImpl, "Qt frontend implementation class")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLFRONTENDQT_API Frontend();

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~Frontend();

		/**
		*  @brief
		*    Get main window
		*
		*  @return
		*    Main window, can be a null pointer
		*/
		PLFRONTENDQT_API QWidget *GetMainWindow() const;

		/**
		*  @brief
		*    Set main window
		*
		*  @param[in] pMainWindow
		*    Pointer to the main window of the application (a null pointer is also valid)
		*/
		PLFRONTENDQT_API void SetMainWindow(QWidget *pMainWindow);


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::FrontendImpl functions      ]
	//[-------------------------------------------------------]
	protected:
		virtual int Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments) override;
		virtual int Run(int argc, char **argv) override;
		virtual PLCore::handle GetNativeWindowHandle() const override;
		virtual void Redraw() override;
		virtual void Ping() override;
		virtual PLCore::uint32 GetWidth() const override;
		virtual PLCore::uint32 GetHeight() const override;
		virtual bool GetToggleFullscreenMode() const override;
		virtual void SetToggleFullscreenMode(bool bToggleFullscreenMode) override;
		virtual bool GetFullscreenAltTab() const override;
		virtual void SetFullscreenAltTab(bool bAllowed) override;
		virtual bool IsFullscreen() const override;
		virtual void SetFullscreen(bool bFullscreen) override;
		virtual bool IsMouseVisible() const override;
		virtual void SetMouseVisible(bool bVisible) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QWidget *m_pMainWindow;				/**< Main window of the application (can be a null pointer) */
		bool	 m_bToggleFullscreenMode;	/**< Is it allowed to toggle the fullscreen mode using hotkeys? */
		bool	 m_bFullscreenAltTab;		/**< Is it allowed to use Alt-Tab within fullscreen mode? */
		bool	 m_bIsFullscreen;			/**< 'true' if the window is in fullscreen mode, else 'false' */
		QCursor *m_pQCursorBlank;			/**< Blank (invisible) mouse cursor, can be a null pointer */ 


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_FRONTEND_H__
