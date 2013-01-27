/*********************************************************\
 *  File: main.cpp                                       *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Main.h>
#include <PLCore/System/System.h>
#include <PLCore/File/File.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


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
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// [DEBUG]
//	g_bDebug = true;

	// Change into app directory
	System::GetInstance()->SetCurrentDir(Url(sExecutableFilename).CutFilename());

	// Open log
	g_cLog.Assign("PLUpgradeLog.txt");
	g_cLog.Open(File::FileCreate | File::FileWrite);

	// Call upgrade checks
	UpgradePreV0_8();

	// Close log
	g_cLog.Close();
	return 0;
}
