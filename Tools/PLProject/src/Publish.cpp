/*********************************************************\
 *  File: Publish.cpp                                    *
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
#include <PLCore/Runtime.h>
#include <PLCore/File/File.h>
#include <PLCore/String/RegEx.h>
#if defined(WIN32)
	#include "PublishWin32.h"
#elif defined(LINUX)
	#include "PublishLinux.h"
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Externals                                             ]
//[-------------------------------------------------------]
extern void Message(int nType, const String &sMessage);
extern void Find(Array<String> &lstNames, const String &sPath, const String &sPattern, bool bRecursive);


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
// Output types
static const int MESSAGE	=  0;	/**< Message */
static const int STATUS		=  1;	/**< Status message */
static const int ERR		=  2;	/**< Error message */
static const int DEBUG		= 10;	/**< Debug message (only if debug mode is on) */


//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy files
*/
bool CopyFiles(const String &sSourceDirectory, const String &sTargetDirectory, const String sFiles[])
{
	// Loop through all files (no infinite loop...)
	for (int i=0; ; i++) {
		// Get the current file (for example "libPLCore.so")
		const String sFile = sFiles[i];
		if (sFile.GetLength()) {
			#ifdef LINUX
				// Is this a shared library? If yes, we may also need to copy some symlinks and not just one file...
				static RegEx cRegExg(".*\\.so", RegEx::MatchCaseSensitive);
				if (cRegExg.Match(sFile)) {
					// Get the real source directory - please note that on Linux systems, the searched shared library may
					// in fact be at another place as the given expected one.
					// 1. Look within "/usr/lib"
					// 2. Look within "/usr/local/lib"
					// 3. Look within the given directory, e.g. "/home/cofenberg/pixellight/Bin-Linux/Runtime"
					// -> Due RPATH issues, we DON'T first look within e.g. "/home/cofenberg/pixellight/Bin-Linux/Runtime"
					//    because it may contain an absolute RPATH, because we're currently publishing something, this is NOT desired!
					String sRealSourceDirectory = sSourceDirectory;
					{
						// 1. Look within "/usr/local/lib/
						if (File("/usr/local/lib/" + sFile).IsFile()) {
							sRealSourceDirectory = "/usr/local/lib";
						} else {
							// 2. Look within "/usr/lib/
							if (File("/usr/lib/" + sFile).IsFile()) {
								sRealSourceDirectory = "/usr/lib";
							} else {
								// 3. Look within the given directory
								if (File(sSourceDirectory + '/' + sFile).IsFile()) {
									sRealSourceDirectory = sSourceDirectory;
								} else {
									// Error!
									Message(ERR, "Failed to find '" + sFile + '\'');

									// Get us out of this loop right now!
									return false;
								}
							}
						}
					}

					// Find all files belonging to this shared library
					Array<String> lstFiles;
					Find(lstFiles, sRealSourceDirectory, sFile + '*', false);

					// Loop through files
					Iterator<String> cIterator = lstFiles.GetIterator();
					while (cIterator.HasNext()) {
						// Parse file
						String sCurrentFile = Url(cIterator.Next()).GetFilename();

						// Get the filenames
						const String sSourceFilename = Url(sRealSourceDirectory + '/' + sCurrentFile).GetUrl();
						const String sTargetFilename = Url(sTargetDirectory 	+ '/' + sCurrentFile).GetUrl();

						// Write a message
						Message(MESSAGE, "Copy '" + sSourceFilename + "' to '" + sTargetFilename + '\'');

						// Copy file
						File cFile(sSourceFilename);
						if (!cFile.Copy(sTargetFilename, true)) {
							// Error!
							Message(ERR, "Failed to copy '" + sSourceFilename + "' to '" + sTargetFilename + '\'');

							// Get us out of this loop right now!
							return false;
						}
					}
				} else
			#endif
			{ // For Microsoft Windows or none shared library files
				// Get the filenames
				const String sSourceFilename = Url(sSourceDirectory + '/' + sFile).GetUrl();
				const String sTargetFilename = Url(sTargetDirectory + '/' + sFile).GetUrl();

				// Write a message
				Message(MESSAGE, "Copy '" + sSourceFilename + "' to '" + sTargetFilename + '\'');

				// Copy file
				File cFile(sSourceFilename);
				if (!cFile.Copy(sTargetFilename, true)) {
					// Error!
					Message(ERR, "Failed to copy '" + sSourceFilename + "' to '" + sTargetFilename + '\'');

					// Get us out of this loop right now!
					return false;
				}
			}
		} else {
			// We're done, get us out of this loop right now!
			return true;
		}
	}

	// Error... because we can never ever end up in here...
}

/**
*  @brief
*    Publish entry point
*/
bool Publish(const String &sTargetDirectory)
{
	// Get the PixelLight system runtime shared libraries directory (using the local runtime isn't really possible
	// because PLProject is using the static version of PLCore and so, the local runtime is invisible to PLProject)
	String sRuntimeSharedLibrariesDirectory = Runtime::GetSystemDirectory();
	if (sRuntimeSharedLibrariesDirectory.GetLength()) {
		// Get the PixelLight system runtime data directory
		String sRuntimeDataDirectory = Runtime::GetSystemDataDirectory();
		if (sRuntimeDataDirectory.GetLength()) {
			// Show some information
			Message(MESSAGE, "Publishing '" + sTargetDirectory + '\'');
			Message(MESSAGE, "PixelLight runtime shared libraries directory '" + sRuntimeSharedLibrariesDirectory + '\'');
			Message(MESSAGE, "PixelLight runtime data directory '" + sRuntimeDataDirectory + '\'');

			// Copy PixelLight runtime shared libraries
			Message(MESSAGE, "Copy PixelLight runtime shared libraries...");
			if (CopyFiles(sRuntimeSharedLibrariesDirectory, sTargetDirectory + "/x86", sRuntimeSharedLibraries)) {
				// Copy PixelLight runtime data files
				Message(MESSAGE, "Copy PixelLight runtime data files...");
				if (CopyFiles(sRuntimeDataDirectory, sTargetDirectory + "/Data", sRuntimeDataFiles)) {
					// Copy PLRenderer plugins
					Message(MESSAGE, "Copy PLRenderer plugins...");
					if (CopyFiles(sRuntimeSharedLibrariesDirectory, sTargetDirectory + "/x86", sPLRendererPlugins)) {
						// Copy PLScene plugins
						Message(MESSAGE, "Copy PLScene plugins...");
						if (CopyFiles(sRuntimeSharedLibrariesDirectory, sTargetDirectory + "/x86", sPLScenePlugins)) {
							// Copy PLPhysics plugins
							Message(MESSAGE, "Copy PLPhysics plugins...");
							if (CopyFiles(sRuntimeSharedLibrariesDirectory, sTargetDirectory + "/x86", sPLPhysicsPlugins)) {
								// Copy PLSound plugins
								Message(MESSAGE, "Copy PLSound plugins...");
								if (CopyFiles(sRuntimeSharedLibrariesDirectory, sTargetDirectory + "/x86", sPLSoundPlugins)) {
									#ifdef WIN32
										// Copy VC2010 redistributable
										Message(MESSAGE, "Copy VC2010 redistributable...");
										if (CopyFiles(sRuntimeSharedLibrariesDirectory + "/../Runtime/x86/VC2010_Redistributable", sTargetDirectory + "/x86", sVC2010Redistributable))
											Message(MESSAGE, "Copy process successfully finished");
									#else
										Message(MESSAGE, "Copy process successfully finished");
									#endif

									// Done
									return true;
								}
							}
						}
					}
				}
			}
		} else {
			// Error!
			Message(ERR, "PixelLight runtime data directory not found");
		}
	} else {
		// Error!
		Message(ERR, "PixelLight runtime shared libraries directory not found");
	}

	// Error!
	return false;
}
