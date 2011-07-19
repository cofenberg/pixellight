/*********************************************************\
 *  File: SystemImpl.h                                   *
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


#ifndef __PLCORE_SYSTEM_IMPL_H__
#define __PLCORE_SYSTEM_IMPL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Time.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Thread;
class Console;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for platform specific 'System' implementations
*
*  @note
*    - Implementation of the bridge design pattern, this class is the implementor of the 'System' abstraction
*/
class SystemImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class System;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		SystemImpl();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SystemImpl();


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Returns the name of the platform
		*
		*  @return
		*    Platform string (for instance 'Win32' for Windows 32 bit, 'Linux' for Linux and so on)
		*/
		virtual String GetPlatform() const = 0;

		/**
		*  @brief
		*    Returns the name and version of the operating system
		*
		*  @return
		*    OS information string
		*/
		virtual String GetOS() const = 0;

		/**
		*  @brief
		*    Get the CPU mhz
		*
		*  @return
		*    CPU mhz
		*/
		virtual uint32 GetCPUMhz() const = 0;

		/**
		*  @brief
		*    Returns the name of the computer
		*
		*  @return
		*    Computer name
		*/
		virtual String GetComputerName() const = 0;

		/**
		*  @brief
		*    Returns the current user name
		*
		*  @return
		*    User name
		*/
		virtual String GetUserName() const = 0;

		/**
		*  @brief
		*    Get home directory of the current user
		*
		*  @return
		*    The home directory of the current user
		*/
		virtual String GetUserHomeDir() const = 0;

		/**
		*  @brief
		*    Get data directory of the current user
		*
		*  @return
		*    The data directory of the current user
		*/
		virtual String GetUserDataDir() const = 0;

		/**
		*  @brief
		*    Get name of data directory for given application name
		*
		*  @param[in] sName
		*    Application name
		*
		*  @return
		*    Name of data directory in native style of used OS
		*/
		virtual String GetDataDirName(const String &sName) const = 0;

		/**
		*  @brief
		*    Get absolute path of application executable
		*
		*  @return
		*    Path to executable (e.g. on Windows: 'C:\MyApplication\Test.exe')
		*/
		virtual String GetExecutableFilename() const = 0;

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
		virtual String GetEnvironmentVariable(const String &sName) const = 0;

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
		virtual bool SetEnvironmentVariable(const String &sName, const String &sValue) const = 0;

		/**
		*  @brief
		*    Deletes an environment variable
		*
		*  @param[in] sName
		*    Name of the environment variable to delete
		*/
		virtual void DeleteEnvironmentVariable(const String &sName) const = 0;

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
		virtual bool Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir) const = 0;

		/**
		*  @brief
		*    Returns the current program locale language information
		*
		*  @return
		*    The current program locale language information
		*/
		virtual String GetLocaleLanguage() const = 0;

		/**
		*  @brief
		*    Returns the current directory
		*
		*  @return
		*    Path to the current directory (never ends with "/"!)
		*/
		virtual String GetCurrentDir() const = 0;

		/**
		*  @brief
		*    Sets the current directory
		*
		*  @param[in] sPath
		*    Path to the current directory
		*
		*  @return
		*    'true', if all went fine, else 'false'
		*/
		virtual bool SetCurrentDir(const String &sPath) = 0;

		/**
		*  @brief
		*    Returns a pointer to the current thread
		*
		*  @return
		*    Current thread, a null pointer on main thread or error
		*/
		virtual Thread *GetCurrentThread() const = 0;

		/**
		*  @brief
		*    Exit the application immediatly
		*
		*  @param[in] nReturn
		*    Return value
		*/
		virtual void Exit(int nReturn) = 0;

		/**
		*  @brief
		*    Returns the console instance
		*
		*  @return
		*    The console instance
		*/
		virtual const Console &GetConsole() const = 0;

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
		virtual Time GetTime() const = 0;

		/**
		*  @brief
		*    Returns the number of milliseconds since the system was started
		*
		*  @return
		*    Number of milliseconds elapsed since the system was started
		*/
		virtual uint64 GetMilliseconds() const = 0;

		/**
		*  @brief
		*    Retrieves the number of microseconds since the system was started
		*
		*  @return
		*    Number of microseconds elapsed since the system was started
		*/
		virtual uint64 GetMicroseconds() const = 0;

		/**
		*  @brief
		*    Suspend the current thread for a specified time period
		*
		*  @param[in] nMilliseconds
		*    Number of milliseconds to sleep
		*/
		virtual void Sleep(uint64 nMilliseconds) const = 0;

		/**
		*  @brief
		*    Yields the rest of the current threads time slice
		*/
		virtual void Yield() const = 0;

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
		virtual float GetPercentageOfUsedPhysicalMemory() const = 0;

		/**
		*  @brief
		*    Returns the total physical memory in bytes
		*
		*  @return
		*    The total physical memory in bytes
		*/
		virtual uint64 GetTotalPhysicalMemory() const = 0;

		/**
		*  @brief
		*    Returns the current free physical memory in bytes
		*
		*  @return
		*    The current free physical memory in bytes
		*/
		virtual uint64 GetFreePhysicalMemory() const = 0;

		/**
		*  @brief
		*    Returns the total virtual memory in bytes
		*
		*  @return
		*    The total virtual memory in bytes
		*/
		virtual uint64 GetTotalVirtualMemory() const = 0;

		/**
		*  @brief
		*    Returns the current free virtual memory in bytes
		*
		*  @return
		*    The current free virtual memory in bytes
		*/
		virtual uint64 GetFreeVirtualMemory() const = 0;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_SYSTEM_IMPL_H__
