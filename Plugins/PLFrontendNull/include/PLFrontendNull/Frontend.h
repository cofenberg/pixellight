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


#ifndef __PLFRONTENDNULL_FRONTEND_H__
#define __PLFRONTENDNULL_FRONTEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendImpl.h>
#include <PLCore/Frontend/FrontendPixelLight.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null frontend implementation class
*/
class Frontend : public PLCore::FrontendImpl {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Frontend, "PLFrontendNull", PLCore::FrontendImpl, "Null frontend implementation class")
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
		virtual int Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments, const PLCore::String &sApplicationClass) override;
		virtual PLCore::handle GetNativeWindowHandle() const override;
		virtual void Redraw() override;
		virtual void Ping() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::FrontendPixelLight m_cFrontend;		/**< The frontend instance */
		PLCore::uint64			   m_nTimeToWait;	/**< Time to wait */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendNull


#endif // __PLFRONTENDNULL_FRONTEND_H__
