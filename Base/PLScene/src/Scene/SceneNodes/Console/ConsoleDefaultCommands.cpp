/*********************************************************\
 *  File: ConsoleDefaultCommands.cpp                     *
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
#include <PLCore/Core.h>
#include <PLCore/Log/Log.h>
#include <PLCore/Tools/Timing.h>
#include <PLCore/Tools/Profiling.h>
#include <PLCore/Application/ConsoleApplication.h>
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneNodes/Console/ConsoleCommand.h"
#include "PLScene/Scene/SceneNodes/Console/SNConsole.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Show console help text
*/
void PLConsoleCommandHelp(ConsoleCommand &cCommand)
{
	PL_LOG(Info, "'list' for a list of available commands")
	PL_LOG(Info, "'bulkylist' for a detailed list of available commands")
	PL_LOG(Info, "Press tab for automatic command completion")
	PL_LOG(Info, "Press left/right arrow keys to move the cursor")
	PL_LOG(Info, "  + hold shift to select text")
	PL_LOG(Info, "Press shift and delete/insert key to copy'n'past selected text")
	PL_LOG(Info, "Press up/down arrow keys to select previous commands")
	Log::GetInstance()->Flush();
}

/**
*  @brief
*    List all console commands
*/
void PLConsoleCommandList(ConsoleCommand &cCommand)
{
	if (cCommand.GetConsole())
		cCommand.GetConsole()->List(false);
}

/**
*  @brief
*    Detailed list all console commands
*/
void PLConsoleCommandBulkyList(ConsoleCommand &cCommand)
{
	if (cCommand.GetConsole())
		cCommand.GetConsole()->List(true);
}

/**
*  @brief
*    Clear console history
*/
void PLConsoleCommandClear(ConsoleCommand &cCommand)
{
	if (cCommand.GetConsole())
		cCommand.GetConsole()->ClearCommandHistory();
}

/**
*  @brief
*    Display some info about the engine
*/
void PLConsoleCommandAbout(ConsoleCommand &cCommand)
{
	PL_LOG(Info, "")
	PL_LOG(Info, Core::GetVersion().ToString())
	PL_LOG(Info, "Copyright (C) 2002-2011 by The PixelLight Team")
	PL_LOG(Info, "")
	Log::GetInstance()->Flush();
}

/**
*  @brief
*    Version information
*/
void PLConsoleCommandVersion(ConsoleCommand &cCommand)
{
	PL_LOG(Info, "")
	PL_LOG(Info, Core::GetVersion().ToString() + String::Format(" compiled at %s / %s", __DATE__, __TIME__))
	if (cCommand.GetConsole())
		PL_LOG(Info, cCommand.GetConsole()->GetDescription())
	PL_LOG(Info, "")
	Log::GetInstance()->Flush();
}

/**
*  @brief
*    Toggle FPS display
*/
void PLConsoleCommandFPS(ConsoleCommand &cCommand)
{
	ConsoleApplication *pApplication = ConsoleApplication::GetApplication();
	if (pApplication) {
		const bool bValue = pApplication->GetConfig().GetVar("PLScene::EngineDebugConfig", "ShowFPS").GetBool();
		pApplication->GetConfig().SetVar("PLScene::EngineDebugConfig", "ShowFPS", String::Format("%d", !bValue));
	}
}

/**
*  @brief
*    Sets the FPS limit, 0 if there's no FPS limitation
*/
void PLConsoleCommandFPSLimit(ConsoleCommand &cCommand)
{
	Timing::GetInstance()->SetFPSLimit(cCommand.GetVar(0).f);
}

/**
*  @brief
*    Activates/deactivates the profiling system
*/
void PLConsoleCommandProfiling(ConsoleCommand &cCommand)
{
	Profiling::GetInstance()->SetActive(!Profiling::GetInstance()->IsActive());
}

/**
*  @brief
*    Selects the next profile group
*/
void PLConsoleCommandNextProfile(ConsoleCommand &cCommand)
{
	Profiling::GetInstance()->SelectNextGroup();
}

/**
*  @brief
*    Selects the previous profile group
*/
void PLConsoleCommandPreviousProfile(ConsoleCommand &cCommand)
{
	Profiling::GetInstance()->SelectPreviousGroup();
}

/**
*  @brief
*    Toggle coordinate axis visualisation
*/
void PLConsoleCommandCoordinateAxis(ConsoleCommand &cCommand)
{
	ConsoleApplication *pApplication = ConsoleApplication::GetApplication();
	if (pApplication) {
		const bool bValue = pApplication->GetConfig().GetVar("PLScene::EngineDebugConfig", "ShowCoordinateAxis").GetBool();
		pApplication->GetConfig().SetVar("PLScene::EngineDebugConfig", "ShowCoordinateAxis", String::Format("%d", !bValue));
	}
}

/**
*  @brief
*    Toggle xz-plane visualisation
*/
void PLConsoleCommandXZPlane(ConsoleCommand &cCommand)
{
	ConsoleApplication *pApplication = ConsoleApplication::GetApplication();
	if (pApplication) {
		const bool bValue = pApplication->GetConfig().GetVar("PLScene::EngineDebugConfig", "ShowXZPlane").GetBool();
		pApplication->GetConfig().SetVar("PLScene::EngineDebugConfig", "ShowXZPlane", String::Format("%d", !bValue));
	}
}

/**
*  @brief
*    Toggle xy-plane visualisation
*/
void PLConsoleCommandXYPlane(ConsoleCommand &cCommand)
{
	ConsoleApplication *pApplication = ConsoleApplication::GetApplication();
	if (pApplication) {
		const bool bValue = pApplication->GetConfig().GetVar("PLScene::EngineDebugConfig", "ShowXYPlane").GetBool();
		pApplication->GetConfig().SetVar("PLScene::EngineDebugConfig", "ShowXYPlane", String::Format("%d", !bValue));
	}
}

/**
*  @brief
*    Toggle yz-plane visualisation
*/
void PLConsoleCommandYZPlane(ConsoleCommand &cCommand)
{
	ConsoleApplication *pApplication = ConsoleApplication::GetApplication();
	if (pApplication) {
		const bool bValue = pApplication->GetConfig().GetVar("PLScene::EngineDebugConfig", "ShowYZPlane").GetBool();
		pApplication->GetConfig().SetVar("PLScene::EngineDebugConfig", "ShowYZPlane", String::Format("%d", !bValue));
	}
}

/**
*  @brief
*    Set log level
*/
void PLConsoleCommandSetLogLevel(ConsoleCommand &cCommand)
{
	String sString = cCommand.GetVar(0).s;
	if (sString == "Quiet")
		Log::GetInstance()->SetLogLevel(Log::Quiet);
	else if (sString == "Always")
		Log::GetInstance()->SetLogLevel(Log::Always);
	else if (sString == "Critical")
		Log::GetInstance()->SetLogLevel(Log::Critical);
	else if (sString == "Error")
		Log::GetInstance()->SetLogLevel(Log::Error);
	else if (sString == "Warning")
		Log::GetInstance()->SetLogLevel(Log::Warning);
	else if (sString == "Info")
		Log::GetInstance()->SetLogLevel(Log::Info);
	else if (sString == "Debug")
		Log::GetInstance()->SetLogLevel(Log::Debug);
	else
		PL_LOG(Error, "Unknown log level '" + sString + "'. Must be Quiet, Always, Critical, Error, Warning, Info or Debug!")
}

/**
*  @brief
*    Toggle pause modus
*/
void PLConsoleCommandPause(ConsoleCommand &cCommand)
{
	Timing::GetInstance()->Pause(!Timing::GetInstance()->IsPaused());
}

/**
*  @brief
*    Time scale
*/
void PLConsoleCommandTimeScale(ConsoleCommand &cCommand)
{
	float fFactor = cCommand.GetVar(0).f;
	if (!Timing::GetInstance()->SetTimeScaleFactor(fFactor))
		PL_LOG(Error, String("Failed to set '") + fFactor + "' as time scale factor (note, a factor of <= 0 is NOT allowed)")
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
