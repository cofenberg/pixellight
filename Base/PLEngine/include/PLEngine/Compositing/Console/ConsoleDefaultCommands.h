/*********************************************************\
 *  File: ConsoleDefaultCommands.h                       *
 *      Console default execution function headers
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


#ifndef __PLENGINE_COMPOSITING_CONSOLEDEFAULTCOMMANDS_H__
#define __PLENGINE_COMPOSITING_CONSOLEDEFAULTCOMMANDS_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ConsoleCommand;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
// Standard commands
extern void PLConsoleCommandHelp(ConsoleCommand &cCommand);				/**< Show console help text */
extern void PLConsoleCommandList(ConsoleCommand &cCommand);				/**< List all console commands */
extern void PLConsoleCommandBulkyList(ConsoleCommand &cCommand);		/**< Detailed list all console commands */
extern void PLConsoleCommandClear(ConsoleCommand &cCommand);			/**< Clear console history */
extern void PLConsoleCommandAbout(ConsoleCommand &cCommand);			/**< Display some info about the engine */
extern void PLConsoleCommandVersion(ConsoleCommand &cCommand);			/**< Version information */
extern void PLConsoleCommandFPS(ConsoleCommand &cCommand);				/**< Toggle FPS display */
extern void PLConsoleCommandFPSLimit(ConsoleCommand &cCommand);			/**< Sets the FPS limit, 0 if there's no FPS limitation */
extern void PLConsoleCommandProfiling(ConsoleCommand &cCommand);		/**< Activates/deactivates the profiling system */
extern void PLConsoleCommandNextProfile(ConsoleCommand &cCommand);		/**< Selects the next profile group */
extern void PLConsoleCommandPreviousProfile(ConsoleCommand &cCommand);	/**< Selects the previous profile group */
// Debug commands
extern void PLConsoleCommandWireframes(ConsoleCommand &cCommand);		/**< Toggle render wireframe mode */
extern void PLConsoleCommandPoints(ConsoleCommand &cCommand);			/**< Toggle render point mode */
extern void PLConsoleCommandCoordinateAxis(ConsoleCommand &cCommand);	/**< Toggle coordinate axis visualization */
extern void PLConsoleCommandXZPlane(ConsoleCommand &cCommand);			/**< Toggle xz-plane visualization */
extern void PLConsoleCommandXYPlane(ConsoleCommand &cCommand);			/**< Toggle xy-plane visualization */
extern void PLConsoleCommandYZPlane(ConsoleCommand &cCommand);			/**< Toggle yz-plane visualization */
extern void PLConsoleCommandSetLogLevel(ConsoleCommand &cCommand);		/**< Set log level */
extern void PLConsoleCommandPause(ConsoleCommand &cCommand);			/**< Toggle pause modus */
extern void PLConsoleCommandTimeScale(ConsoleCommand &cCommand);		/**< Time scale */


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_COMPOSITING_CONSOLEDEFAULTCOMMANDS_H__
