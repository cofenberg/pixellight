/*********************************************************\
 *  File: Frontend.h                                     *
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


#ifndef FRONTEND_H
#define FRONTEND_H


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendImpl.h>
#include <PLCore/Frontend/FrontendContext.h>
#include <PLCore/Frontend/FrontendPixelLight.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditor {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Editor PixelLight application frontend implementation class
*/
class Frontend : public PLCore::FrontendImpl {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Frontend, "PLFrontendNull", PLCore::FrontendImpl, "Editor PixelLight application frontend implementation class")
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
		Frontend();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Frontend();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::FrontendImpl functions        ]
	//[-------------------------------------------------------]
	private:
		virtual int Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments);
		virtual int Run(int argc, wchar_t **argv);
		virtual PLCore::handle GetNativeWindowHandle() const;
		virtual void Redraw();
		virtual void Ping();
		virtual PLCore::uint32 GetWidth() const;
		virtual PLCore::uint32 GetHeight() const;
		virtual bool GetToggleFullscreenMode() const;
		virtual void SetToggleFullscreenMode(bool bToggleFullscreenMode);
		virtual bool GetFullscreenAltTab() const;
		virtual void SetFullscreenAltTab(bool bAllowed);
		virtual bool IsFullscreen() const;
		virtual void SetFullscreen(bool bFullscreen);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool					   m_bFrontendApplicationInitialized;	/**< Frontend application successfully initialized? */
		PLCore::FrontendContext    m_cFrontendContext;					/**< PixelLight application frontend context instance */
		PLCore::FrontendPixelLight m_cFrontend;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditor


#endif // FRONTEND_H
