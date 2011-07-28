/*********************************************************\
 *  File: Application.h                                  *
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


#ifndef __PLSAMPLE_99_H__
#define __PLSAMPLE_99_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Application/ConsoleApplication.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*/
class Application : public PLCore::ConsoleApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Application, "", PLCore::ConsoleApplication, "Application class")
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
		Application();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Application();

		/**
		*  @brief
		*    Test: Display GUI test
		*/
		void TestGui();

		/**
		*  @brief
		*    Test: Display available screens
		*/
		void TestScreens();

		/**
		*  @brief
		*    Test: List available fonts
		*/
		void TestFonts();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ConsoleApplication functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Main() override;


};


#endif // __PLSAMPLE_99_H__
