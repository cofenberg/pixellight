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


#ifndef __PLSAMPLE_44_SCRIPTOOP_H__
#define __PLSAMPLE_44_SCRIPTOOP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Application/ConsoleApplication.h>


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
class MyRTTIClass;


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
		*    Calls the OOP script
		*
		*  @param[in] sScriptFilename
		*    Filename of the script to use
		*/
		void OOP(const PLGeneral::String &sScriptFilename);

		/**
		*  @brief
		*    Called on MySignal signal
		*
		*  @param[in] sParameter
		*    Signal parameter
		*/
		void NotifyMySignal(PLGeneral::String sParameter);

		/**
		*  @brief
		*    Returns the MyRTTIClass instance
		*
		*  @return
		*    MyRTTIClass instance, always valid!
		*/
		// [TODO] "MyRTTIClass*" instead of "PLCore::Object*"
		PLCore::Object *GetMyRTTIClassInstance();
//		MyRTTIClass *GetMyRTTIClassInstance();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ConsoleApplication functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Main();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLGeneral::String> EventHandlerMySignal;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		MyRTTIClass *m_pMyRTTIClass;	/**< MyRTTIClass instance, always valid! */


};


#endif // __PLSAMPLE_44_SCRIPTOOP_H__
