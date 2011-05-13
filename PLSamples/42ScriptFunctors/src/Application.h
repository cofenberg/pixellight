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


#ifndef __PLSAMPLE_42_SCRIPTFUNCTORS_H__
#define __PLSAMPLE_42_SCRIPTFUNCTORS_H__
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


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Performs a calculation by using a script
		*
		*  @param[in] sScriptFilename
		*    Filename of the script to use
		*  @param[in] fFirst
		*    First number
		*  @param[in] fSecond
		*    Second number
		*
		*  @return
		*    The result
		*/
		float DoCalculation(const PLGeneral::String &sScriptFilename, float fFirst, float fSecond);

		/**
		*  @brief
		*    A method
		*
		*  @param[in] nFirst
		*    First number
		*
		*  @return
		*    The result
		*/
		int Method(int nFirst);


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    A static method
		*
		*  @param[in] nFirst
		*    First number
		*
		*  @return
		*    The result
		*/
		static int StaticMethod(int nFirst);

		/**
		*  @brief
		*    A static string method
		*
		*  @param[in] sFirst
		*    First string
		*
		*  @return
		*    The result
		*/
		static PLGeneral::String StaticStringMethod(PLGeneral::String sFirst);


	//[-------------------------------------------------------]
	//[ Private virtual ConsoleApplication functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void Main();


};


#endif // __PLSAMPLE_42_SCRIPTFUNCTORS_H__
