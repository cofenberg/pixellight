/*********************************************************\
 *  File: System.cpp                                     *
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
#include "PLCore/System/SystemImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the name of the platform
*/
inline String System::GetPlatform() const
{
	// Call system function
	return m_pSystemImpl->GetPlatform();
}

/**
*  @brief
*    Returns the platform architecture
*/
inline String System::GetPlatformArchitecture() const
{
	#ifdef ARCHITECTURE_STRING
		// The exact architecture PLCore has been compiled for is provided as preprocessor definition
		static const String sString = ARCHITECTURE_STRING;
	#else
		// Use a fallback in case ARCHITECTURE_STRING is not given
		#if defined(WIN64) || defined(X64_ARCHITECTURE)
			static const String sString = "x64";
		#else
			static const String sString = "x86";
		#endif
	#endif
	return sString;
}

/**
*  @brief
*    Returns the platform bit architecture
*/
inline uint32 System::GetPlatformBitArchitecture() const
{
	#if defined(WIN64) || defined(X64_ARCHITECTURE)
		return 64;
	#else
		return 32;
	#endif
}

/**
*  @brief
*    Returns the name and version of the operating system
*/
inline String System::GetOS() const
{
	// Call system function
	return m_pSystemImpl->GetOS();
}

/**
*  @brief
*    Returns the directory separator used by the operation system
*/
inline char System::GetSeparator() const
{
	// Call system function
	return m_pSystemImpl->GetSeparator();
}

/**
*  @brief
*    Returns the shared library filename prefix used by the operation system
*/
inline String System::GetSharedLibraryPrefix() const
{
	// Call system function
	return m_pSystemImpl->GetSharedLibraryPrefix();
}

/**
*  @brief
*    Returns the shared library file extension used by the operation system
*/
inline String System::GetSharedLibraryExtension() const
{
	// Call system function
	return m_pSystemImpl->GetSharedLibraryExtension();
}

/**
*  @brief
*    Get the CPU MHz
*/
inline uint32 System::GetCPUMhz() const
{
	// Call system function
	return m_pSystemImpl->GetCPUMhz();
}

/**
*  @brief
*    Returns the name of the computer
*/
inline String System::GetComputerName() const
{
	// Call system function
	return m_pSystemImpl->GetComputerName();
}

/**
*  @brief
*    Returns the current user name
*/
inline String System::GetUserName() const
{
	// Call system function
	return m_pSystemImpl->GetUserName();
}

/**
*  @brief
*    Get home directory of the current user
*/
inline String System::GetUserHomeDir() const
{
	// Call system function
	return m_pSystemImpl->GetUserHomeDir();
}

/**
*  @brief
*    Get data directory of the current user
*/
inline String System::GetUserDataDir() const
{
	// Call system function
	return m_pSystemImpl->GetUserDataDir();
}

/**
*  @brief
*    Get name of data directory for given application name
*/
inline String System::GetDataDirName(const String &sName) const
{
	// Call system function
	return m_pSystemImpl->GetDataDirName(sName);
}

/**
*  @brief
*    Get absolute path of application executable
*/
inline String System::GetExecutableFilename() const
{
	// Call system function
	return m_pSystemImpl->GetExecutableFilename();
}

/**
*  @brief
*    Reads an environment variable
*/
inline String System::GetEnvironmentVariable(const String &sName) const
{
	// Call system function
	return m_pSystemImpl->GetEnvironmentVariable(sName);
}

/**
*  @brief
*    Writes an environment variable
*/
inline bool System::SetEnvironmentVariable(const String &sName, const String &sValue) const
{
	// Call system function
	return m_pSystemImpl->SetEnvironmentVariable(sName, sValue);
}

/**
*  @brief
*    Deletes an environment variable
*/
inline void System::DeleteEnvironmentVariable(const String &sName) const
{
	// Call system function
	return m_pSystemImpl->DeleteEnvironmentVariable(sName);
}

/**
*  @brief
*    Executes a system command (create a new process)
*/
inline bool System::Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir) const
{
	// Call system function
	return m_pSystemImpl->Execute(sCommand, sParameters, sWorkingDir);
}

/**
*  @brief
*    Returns the current program locale language information
*/
inline String System::GetLocaleLanguage() const
{
	// Call system function
	return m_pSystemImpl->GetLocaleLanguage();
}

/**
*  @brief
*    Returns the current directory
*/
inline String System::GetCurrentDir() const
{
	// Call system function
	String sCurrentDir = m_pSystemImpl->GetCurrentDir();

	// No empty string, please (it should always be possible to add e.g. '/Data' without problems)
	if (!sCurrentDir.GetLength())
		sCurrentDir = '.';

	// Done
	return sCurrentDir;
}

/**
*  @brief
*    Sets the current directory
*/
inline bool System::SetCurrentDir(const String &sPath)
{
	// Call system function
	return m_pSystemImpl->SetCurrentDir(sPath);
}

/**
*  @brief
*    Returns a pointer to the main thread
*/
inline Thread *System::GetMainThread() const
{
	// Return main thread
	return m_pMainThread;
}

/**
*  @brief
*    Returns a pointer to the current thread
*/
inline Thread *System::GetCurrentThread() const
{
	// Call system function
	Thread *pThread = m_pSystemImpl->GetCurrentThread();
	return pThread ? pThread : m_pMainThread;
}

/**
*  @brief
*    Exit the application immediately
*/
inline void System::Exit(int nReturn)
{
	// Call system function
	m_pSystemImpl->Exit(nReturn);
}

/**
*  @brief
*    Returns the console instance
*/
inline const Console &System::GetConsole() const
{
	// Call system function
	return m_pSystemImpl->GetConsole();
}

/**
*  @brief
*    Primitive way (e.g. by using a message box) to be able to tell the user that something went terrible wrong
*/
inline void System::UrgentMessage(const String &sMessage) const
{
	// Call system function
	m_pSystemImpl->UrgentMessage(sMessage);
}

/**
*  @brief
*    Returns the current date and time
*/
inline Time System::GetTime() const
{
	// Call system function
	return m_pSystemImpl->GetTime();
}

/**
*  @brief
*    Returns the number of milliseconds since the system was started
*/
inline uint64 System::GetMilliseconds() const
{
	// Call system function
	return m_pSystemImpl->GetMilliseconds();
}

/**
*  @brief
*    Retrieves the number of microseconds since the system was started
*/
inline uint64 System::GetMicroseconds() const
{
	// Call system function
	return m_pSystemImpl->GetMicroseconds();
}

/**
*  @brief
*    Suspend the current thread for a specified time period
*/
inline void System::Sleep(uint64 nMilliseconds) const
{
	// Call system function
	m_pSystemImpl->Sleep(nMilliseconds);
}

/**
*  @brief
*    Yields the rest of the current threads time slice
*/
inline void System::Yield() const
{
	// Call system implementation
	m_pSystemImpl->Yield();
}

/**
*  @brief
*    Returns an approximation of the percentage of used physical memory (0.0-100.0)
*/
inline float System::GetPercentageOfUsedPhysicalMemory() const
{
	// Call system function
	return m_pSystemImpl->GetPercentageOfUsedPhysicalMemory();
}

/**
*  @brief
*    Returns the total physical memory in bytes
*/
inline uint64 System::GetTotalPhysicalMemory() const
{
	// Call system function
	return m_pSystemImpl->GetTotalPhysicalMemory();
}

/**
*  @brief
*    Returns the current free physical memory in bytes
*/
inline uint64 System::GetFreePhysicalMemory() const
{
	// Call system function
	return m_pSystemImpl->GetFreePhysicalMemory();
}

/**
*  @brief
*    Returns the total virtual memory in bytes
*/
inline uint64 System::GetTotalVirtualMemory() const
{
	// Call system function
	return m_pSystemImpl->GetTotalVirtualMemory();
}

/**
*  @brief
*    Returns the current free virtual memory in bytes
*/
inline uint64 System::GetFreeVirtualMemory() const
{
	// Call system function
	return m_pSystemImpl->GetFreeVirtualMemory();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
