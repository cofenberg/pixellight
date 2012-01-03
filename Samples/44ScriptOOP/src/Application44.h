/*********************************************************\
 *  File: Application44.h                                *
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


#ifndef __PLSAMPLE_44_APPLICATION_H__
#define __PLSAMPLE_44_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendApplication.h>


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
class Application44 : public PLCore::FrontendApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Application44, "", PLCore::FrontendApplication, "Application class")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLCore::Frontend&,	"Parameter constructor. Frontend this application instance is running in as first parameter.",	"")
		// Slots
		pl_slot_1(OnMySignal,	PLCore::String,	"Called on MySignal signal, a string as first parameter",	"")
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
		*/
		Application44(PLCore::Frontend &cFrontend);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Application44();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Runs a script
		*
		*  @param[in] sScriptFilename
		*    Filename of the script to run
		*/
		void RunScript(const PLCore::String &sScriptFilename);

		/**
		*  @brief
		*    Called on MySignal signal
		*
		*  @param[in] sParameter
		*    Signal parameter
		*/
		void OnMySignal(PLCore::String sParameter);

		/**
		*  @brief
		*    Returns the MyRTTIClass instance
		*
		*  @param[in] pObject
		*    RTTI class instance, can be a null pointer
		*
		*  @return
		*    MyRTTIClass instance, always valid!
		*/
		MyRTTIClass *GetMyRTTIClassInstance(MyRTTIClass *pObject);


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::AbstractLifecycle functions   ]
	//[-------------------------------------------------------]
	private:
		virtual bool OnStart() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		MyRTTIClass *m_pMyRTTIClass;	/**< MyRTTIClass instance, always valid! */


};


#endif // __PLSAMPLE_44_APPLICATION_H__
