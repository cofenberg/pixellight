/*********************************************************\
 *  File: SystemInterfacePL.cpp                          *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Log/Log.h>
#include <PLGeneral/Tools/Timing.h>
#include "libRocket_PL/SystemInterfacePL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SystemInterfacePL::SystemInterfacePL()
{
}

/**
*  @brief
*    Destructor
*/
SystemInterfacePL::~SystemInterfacePL()
{
}


//[-------------------------------------------------------]
//[ Public virtual Rocket::Core::SystemInterface functions ]
//[-------------------------------------------------------]
float SystemInterfacePL::GetElapsedTime()
{
	// "PLGeneral::Timing::GetPastTime()" returns the past time in milliseconds since the application start
	// - but this method must return the number of seconds elapsed since the start of the application...
	return Timing::GetInstance()->GetPastTime()*0.001f;
}

bool SystemInterfacePL::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message)
{
	// Get the PL log level
	uint8 nPLLogLevel = Log::Info;
	switch (type) {
		case Rocket::Core::Log::LT_ALWAYS:
			nPLLogLevel = Log::Always;
			break;

		case Rocket::Core::Log::LT_ERROR:
			nPLLogLevel = Log::Error;
			break;

		case Rocket::Core::Log::LT_ASSERT:
			nPLLogLevel = Log::Warning;	// There is no assert PL log level
			break;

		case Rocket::Core::Log::LT_WARNING:
			nPLLogLevel = Log::Warning;
			break;

		case Rocket::Core::Log::LT_INFO:
			nPLLogLevel = Log::Info;
			break;

		case Rocket::Core::Log::LT_DEBUG:
			nPLLogLevel = Log::Debug;
			break;

		case Rocket::Core::Log::LT_MAX:
			nPLLogLevel = Log::Critical;
			break;

		default:
			nPLLogLevel = Log::Info;
			break;
	}

	// Print into the PL log
	Log::GetInstance()->Output(nPLLogLevel, String::FromUTF8(message.CString()));

	// Return "false" to break into the debugger
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
SystemInterfacePL::SystemInterfacePL(const SystemInterfacePL &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
SystemInterfacePL &SystemInterfacePL::operator =(const SystemInterfacePL &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL
