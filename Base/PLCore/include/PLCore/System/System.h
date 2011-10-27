/*********************************************************\
 *  File: System.h                                       *
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


#ifndef __PLCORE_SYSTEM_H__
#define __PLCORE_SYSTEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Time.h"
#include "PLCore/Core/Singleton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Thread;
class Console;
class SystemImpl;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Provides access to system and platform functions
*
*  @note
*    - Implementation of the bridge design pattern, this class is the abstraction
*/
class System : public Singleton<System> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Singleton<System>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns relevant system information in one string
		*
		*  @return
		*    Information string
		*
		*  @remarks
		*    The returned information are
		*    - PLCore version information
		*    - PLCore build information
		*    - Endian
		*    - Platform
		*    - Operating system version
		*/
		PLCORE_API String GetInfo() const;

		/**
		*  @brief
		*    Detects the current machine's endian ("byte order")
		*
		*  @return
		*    'true' if the current machine is using 'Little Endian First', (LSB (least significant byte), also known as 'Intel-Format')
		*    'false' if the current machine is using 'Big Endian First', (MSB (most significant byte), also known as 'Motorola-Format')
		*
		*  @note
		*   - PixelLight is using 'Little Endian First' for it's binary file formats and so on
		*/
		PLCORE_API bool IsLittleEndian() const;

		/**
		*  @brief
		*    Returns the name of the platform
		*
		*  @return
		*    Platform string (for instance 'Win32' for Windows 32 bit, 'Linux' for Linux and so on)
		*/
		PLCORE_API String GetPlatform() const;

		/**
		*  @brief
		*    Returns the name and version of the operating system
		*
		*  @return
		*    OS information string
		*/
		PLCORE_API String GetOS() const;

		/**
		*  @brief
		*    Returns the directory separator used by the operation system
		*
		*  @return
		*    The directory separator used by the operation system (e.g. '/' on Linux, '\' on Windows)
		*/
		PLCORE_API char GetSeparator() const;

		/**
		*  @brief
		*    Returns the shared library filename prefix used by the operation system
		*
		*  @return
		*    The shared library filename prefix used by the operation system (e.g. 'lib' as in 'libPLCore.so' on Linux, no prefix as in 'PLCore.dll' on Windows)
		*/
		PLCORE_API String GetSharedLibraryPrefix() const;

		/**
		*  @brief
		*    Returns the shared library file extension used by the operation system
		*
		*  @return
		*    The shared library file extension used by the operation system (e.g. 'so' on Linux, 'dll' on Windows)
		*/
		PLCORE_API String GetSharedLibraryExtension() const;

		/**
		*  @brief
		*    Get the CPU MHz
		*
		*  @return
		*    CPU MHz
		*/
		PLCORE_API uint32 GetCPUMhz() const;

		/**
		*  @brief
		*    Returns the name of the computer
		*
		*  @return
		*    Computer name
		*/
		PLCORE_API String GetComputerName() const;

		/**
		*  @brief
		*    Returns the current user name
		*
		*  @return
		*    User name
		*/
		PLCORE_API String GetUserName() const;

		/**
		*  @brief
		*    Get home directory of the current user
		*
		*  @return
		*    The home directory of the current user
		*
		*  @remarks
		*    Examples on different systems:
		*    - Linux:      /home/<username>
		*    - Windows XP: C:\Documents and Settings\<Username>
		*    - Windows 7:  C:\Users\<UserName>
		*/
		PLCORE_API String GetUserHomeDir() const;

		/**
		*  @brief
		*    Get data directory of the current user
		*
		*  @return
		*    The data directory of the current user
		*
		*  @remarks
		*    Examples on different systems:
		*    - Linux:      /home/<username>
		*    - Windows XP: C:\Documents and Settings\<Username>\Application Data
		*    - Windows 7:  C:\Users\<UserName>\AppData\Roaming
		*/
		PLCORE_API String GetUserDataDir() const;

		/**
		*  @brief
		*    Get name of data directory for given application name
		*
		*  @param[in] sName
		*    Application name
		*
		*  @return
		*    Name of data directory in native style of used OS
		*
		*  @remarks
		*    Examples on different systems:
		*    - Linux:   GetDataDirName("PixelLight") -> ".pixellight"
		*    - Windows: GetDataDirName("PixelLight") -> "PixelLight"
		*/
		PLCORE_API String GetDataDirName(const String &sName) const;

		/**
		*  @brief
		*    Get absolute path of application executable
		*
		*  @return
		*    Path to executable (e.g. on Windows: 'C:\MyApplication\Test.exe')
		*
		*  @note
		*    - Application executable = currently running process
		*/
		PLCORE_API String GetExecutableFilename() const;

		/**
		*  @brief
		*    Reads an environment variable
		*
		*  @param[in] sName
		*    Name of the environment variable to read
		*
		*  @return
		*    Content of the variable
		*/
		PLCORE_API String GetEnvironmentVariable(const String &sName) const;

		/**
		*  @brief
		*    Writes an environment variable
		*
		*  @param[in] sName
		*    Name of the environment variable to write
		*  @param[in] sValue
		*    Value to write into the variable
		*
		*  @return
		*    'true' if the variable has been set successfully, else 'false'
		*/
		PLCORE_API bool SetEnvironmentVariable(const String &sName, const String &sValue) const;

		/**
		*  @brief
		*    Deletes an environment variable
		*
		*  @param[in] sName
		*    Name of the environment variable to delete
		*/
		PLCORE_API void DeleteEnvironmentVariable(const String &sName) const;

		/**
		*  @brief
		*    Executes a system command (create a new process)
		*
		*  @param[in] sCommand
		*    Command to execute
		*  @param[in] sParameters
		*    Parameters to pass to the command
		*  @param[in] sWorkingDir
		*    Working directory in which to execute the command
		*
		*  @return
		*    'true' if the command has been executed successfully, else 'false'
		*/
		PLCORE_API bool Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir = "") const;

		/**
		*  @brief
		*    Returns the current program locale language information
		*
		*  @remarks
		*    Internally 'setlocale' is used to collect the current program locale information - but
		*    only the 'language' information is returned as string. For instance, if the current locale
		*    is 'English_USA.1252', 'English' is returned, if the locale is 'French_France.1252', just
		*    'French' is returned and so on.
		*    This information can for instance be used to set a correct default language within the
		*    localization system of PixelLight.
		*
		*  @return
		*    The current program locale language information
		*/
		PLCORE_API String GetLocaleLanguage() const;

		/**
		*  @brief
		*    Returns the current directory
		*
		*  @return
		*    Path to the current directory as native path (never ends with "/"!)
		*/
		PLCORE_API String GetCurrentDir() const;

		/**
		*  @brief
		*    Sets the current directory
		*
		*  @param[in] sPath
		*    Path to the current directory
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*
		*  @note
		*    - Whenever possible, do not manipulate the current directory, this may backfire when you don't expect it
		*/
		PLCORE_API bool SetCurrentDir(const String &sPath);

		/**
		*  @brief
		*    Returns a pointer to the main thread
		*
		*  @return
		*    Main thread (assumed to be never a null pointer!)
		*/
		PLCORE_API Thread *GetMainThread() const;

		/**
		*  @brief
		*    Returns a pointer to the current thread
		*
		*  @return
		*    Current thread (assumed to be never a null pointer!)
		*/
		PLCORE_API Thread *GetCurrentThread() const;

		/**
		*  @brief
		*    Exit the application immediately
		*
		*  @param[in] nReturn
		*    Return value
		*/
		PLCORE_API void Exit(int nReturn);

		/**
		*  @brief
		*    Returns the console instance
		*
		*  @return
		*    The console instance
		*/
		PLCORE_API const Console &GetConsole() const;

		/**
		*  @brief
		*    Primitive way (e.g. by using a message box) to be able to tell the user that something went terrible wrong
		*
		*  @param[in] sMessage
		*    Message to show
		*
		*  @remarks
		*    Do not misuse this method in order to communicate with the user on a regular basis. This method does only
		*    exist to be able to tell the user that something went terrible wrong. There are situations were one can't
		*    use a log file, command line or something like this. Even when using e.g. a log file to write out error
		*    information - an application may e.g. just close directly after it's start without any further information
		*    and the user may even think that the application didn't start in the first place for an unknown reason.
		*    In such a situation, it's polite to inform the user that something went terrible wrong and providing
		*    a short hint how the issue may be solved. This method wasn't named "MessageBox()" by intend - because
		*    such a feature may not be available on the used platform or is handled in another way as a normal MS Windows
		*    message box.
		*/
		PLCORE_API void UrgentMessage(const String &sMessage) const;

		//[-------------------------------------------------------]
		//[ Time functions                                        ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the current date and time
		*
		*  @return
		*    Date and time string
		*/
		PLCORE_API Time GetTime() const;

		/**
		*  @brief
		*    Returns the number of milliseconds since the system was started
		*
		*  @return
		*    Number of milliseconds elapsed since the system was started
		*/
		PLCORE_API uint64 GetMilliseconds() const;

		/**
		*  @brief
		*    Retrieves the number of microseconds since the system was started
		*
		*  @return
		*    Number of microseconds elapsed since the system was started
		*/
		PLCORE_API uint64 GetMicroseconds() const;

		/**
		*  @brief
		*    Suspend the current thread for a specified time period
		*
		*  @param[in] nMilliseconds
		*    Number of milliseconds to sleep, should not be 0 because the behavior is implementation dependent (use 'Yield()' instead)
		*/
		PLCORE_API void Sleep(uint64 nMilliseconds) const;

		/**
		*  @brief
		*    Yields the rest of the current threads time slice
		*
		*  @remarks
		*    Yields the rest of the threads time slice so another active thread of equal or higher priority
		*    waiting for processor time can run. Note that this function may return immediately and the behavior
		*    is in general not exactly predictable. So, use this function to give the processor just a hint
		*    that you are willed to give processor time away.
		*/
		PLCORE_API void Yield() const;

		//[-------------------------------------------------------]
		//[ Memory functions                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns an approximation of the percentage of used physical memory (0.0-100.0)
		*
		*  @return
		*    An approximation of the percentage of used physical memory
		*/
		PLCORE_API float GetPercentageOfUsedPhysicalMemory() const;

		/**
		*  @brief
		*    Returns the total physical memory in bytes
		*
		*  @return
		*    The total physical memory in bytes
		*/
		PLCORE_API uint64 GetTotalPhysicalMemory() const;

		/**
		*  @brief
		*    Returns the current free physical memory in bytes
		*
		*  @return
		*    The current free physical memory in bytes
		*/
		PLCORE_API uint64 GetFreePhysicalMemory() const;

		/**
		*  @brief
		*    Returns the total virtual memory in bytes
		*
		*  @return
		*    The total virtual memory in bytes
		*/
		PLCORE_API uint64 GetTotalVirtualMemory() const;

		/**
		*  @brief
		*    Returns the current free virtual memory in bytes
		*
		*  @return
		*    The current free virtual memory in bytes
		*/
		PLCORE_API uint64 GetFreeVirtualMemory() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		System();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		System(const System &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~System();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		System &operator =(const System &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SystemImpl	*m_pSystemImpl;	/**< Pointer to the system specific implementation (assumed to be never a null pointer!) */
		Thread		*m_pMainThread;	/**< Pointer to the main thread (assumed to be never a null pointer!) */


};


//[-------------------------------------------------------]
//[ Template extern instance                              ]
//[-------------------------------------------------------]
#ifndef PLCORE_SYSTEM_CPP
	PLCORE_EXTERN_TEMPLATE Singleton<System>;
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_SYSTEM_H__
