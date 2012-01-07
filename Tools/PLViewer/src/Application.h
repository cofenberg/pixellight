/*********************************************************\
 *  File: Application.h                                  *
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


#ifndef __PLVIEWER_APPLICATION_H__
#define __PLVIEWER_APPLICATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLEngine/Application/ScriptApplication.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLInput {
	class Control;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Application class
*/
class Application : public PLEngine::ScriptApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Application, "", PLEngine::ScriptApplication, "Application class")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLCore::Frontend&,	"Parameter constructor. Frontend this application instance is running in as first parameter.",	"")
		// Slots
		pl_slot_1(OnControl,	PLInput::Control&,	"Called when a control event has occurred, occurred control as first parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLCore::String DefaultFilename;	/**< The used default resource loaded at start, if empty a file dialog will appear */


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
		Application(PLCore::Frontend &cFrontend);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Application();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when a control event has occurred
		*
		*  @param[in] cControl
		*    Occurred control
		*/
		void OnControl(PLInput::Control &cControl);


	//[-------------------------------------------------------]
	//[ Protected virtual Application functions               ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Loads a resource which type has to be evaluated internally
		*
		*  @param[in] sFilename
		*    Filename of the resource to load
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool LoadResource(const PLCore::String &sFilename);

		/**
		*  @brief
		*    Sets the state text
		*
		*  @param[in] sText
		*    State text
		*
		*  @note
		*    - The default implementation is misusing the frontend title to communicate with the user
		*/
		virtual void SetStateText(const PLCore::String &sText);


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::CoreApplication functions   ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnInitLog() override;
		virtual void OnInit() override;


	//[-------------------------------------------------------]
	//[ Protected virtual PLCore::AbstractFrontend functions  ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnDrop(const PLCore::Container<PLCore::String> &lstFiles) override;


	//[-------------------------------------------------------]
	//[ Private virtual PLEngine::EngineApplication functions ]
	//[-------------------------------------------------------]
	private:
		virtual void OnCreateInputController() override;


};


#endif // __PLVIEWER_APPLICATION_H__
