/*********************************************************\
 *  File: main.cpp                                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/Main.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/FileSearch.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
// Output types
static const int MESSAGE	=  0;	/**< Message */
static const int STATUS		=  1;	/**< Status message */
static const int ERR		=  2;	/**< Error message */
static const int DEBUG		= 10;	/**< Debug message (only if debug mode is on) */


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
File g_cLog;
bool g_bDebug = false;


//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Output message
*/
void Message(int nType, const String &sMessage)
{
	// Print beginning of line
	if (nType == DEBUG && !g_bDebug) return;
	if (nType == STATUS) g_cLog.Print("-- ");
	if (nType == DEBUG)  g_cLog.Print("** ");
	if (nType == ERR)    g_cLog.Print("!! ");

	// Print message
	g_cLog.PrintLn(sMessage);
	g_cLog.Flush();
}


//[-------------------------------------------------------]
//[ Update checks for PixelLight < 0.8                    ]
//[-------------------------------------------------------]
void UpgradePreV0_8()
{
/* Currently nothing to do...
	// Start
	Message(MESSAGE, "Starting checks for Version Pre 0.8");

	// Done
	Message(STATUS, "Done");
*/
}


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
int PLMain(const String &sFilename, const Array<String> &lstArguments)
{
	// [DEBUG]
//	g_bDebug = true;

	// Change into app directory
	System::GetInstance()->SetCurrentDir(Url(sFilename).CutFilename());

	// Open log
	g_cLog.Assign("PLUpgradeLog.txt");
	g_cLog.Open(File::FileCreate | File::FileWrite);

	// Call upgrade checks
	UpgradePreV0_8();

	// Close log
	g_cLog.Close();
	return 0;
}
