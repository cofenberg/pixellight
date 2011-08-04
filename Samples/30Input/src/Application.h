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


#ifndef __PLSAMPLE_30_H__
#define __PLSAMPLE_30_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLCore/Application/CoreApplication.h>


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
class Application : public PLCore::CoreApplication {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, Application, "", PLCore::CoreApplication, "Application class")
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
		*    Test: List devices
		*/
		void TestDevices();

		/**
		*  @brief
		*    Test: Controller
		*/
		void TestController();

		/**
		*  @brief
		*    Test: Input
		*
		*  @param[in] sDevice
		*    Name of device
		*/
		void TestInput(const PLCore::String &sDevice);

		/**
		*  @brief
		*    Test: GetChar() functionality
		*
		*  @param[in] sDevice
		*    Name of device
		*/
		void TestGetChar(const PLCore::String &sDevice);

		/**
		*  @brief
		*    Test: Connections
		*/
		void TestConnections();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when a control of the input controller has been activated
		*/
		void OnControl(PLInput::Control &cControl);

		/**
		*  @brief
		*    Called when a control of the input controller has been activated
		*/
		void OnControlExit(PLInput::Control &cControl);


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::CoreApplication functions     ]
	//[-------------------------------------------------------]
	private:
		virtual void Main() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Event handlers
		PLCore::EventHandler<PLInput::Control&> EventHandlerOnControl;
		PLCore::EventHandler<PLInput::Control&> EventHandlerOnControlExit;

		// Status
		bool m_bExit;


};


#endif // __PLSAMPLE_30_H__
