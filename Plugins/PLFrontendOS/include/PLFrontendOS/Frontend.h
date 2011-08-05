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


#ifndef __PLFRONTENDOS_FRONTEND_H__
#define __PLFRONTENDOS_FRONTEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendImpl.h>
#include <PLCore/Frontend/FrontendPixelLight.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendOS {


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
class OSWindow;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OS frontend implementation class
*/
class Frontend : public PLCore::FrontendImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class OSWindowWindows;
	friend class OSWindowLinux;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Frontend, "PLFrontendOS", PLCore::FrontendImpl, "OS frontend implementation class")
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
	//[ Public virtual PLCore::FrontendImpl functions         ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::handle GetNativeWindowHandle() const override;
		virtual void Ping() override;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::FrontendImpl functions        ]
	//[-------------------------------------------------------]
	private:
		virtual int Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments, const PLCore::String &sApplicationClass) override;
		virtual void Redraw() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		OSWindow				   *m_pOSWindow;	/**< The OS specific window implementation, can be a null pointer */
		PLCore::FrontendPixelLight  m_cFrontend;	/**< The frontend instance */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendOS


#endif // __PLFRONTENDOS_FRONTEND_H__
