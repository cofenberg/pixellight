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
#include "PLCore/System/Thread.h"
#if defined(WIN32)
	#include "PLCore/System/SystemWindows.h"
#elif defined(LINUX)
	#include "PLCore/System/SystemLinux.h"
#endif
#include "PLCore/File/File.h"
#include "PLCore/System/System.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns an information string about the system
*/
String System::GetInfo() const
{
	static const String sString = String("PLCore library") +
								  "\nEndian: "			+ (IsLittleEndian() ? "'Little Endian First'" : "'Big Endian First'") +
								  "\nPlatform: "		+ GetPlatform() +
								  "\nOS: "				+ GetOS() +
								  '\n';
	return sString;
}

/**
*  @brief
*    Detects the current machine's endian ("byte order")
*/
bool System::IsLittleEndian() const
{
	union Probe {
		unsigned int  nNumber;
		unsigned char nBytes[sizeof(unsigned int)];
	};

	// Initialize the first member of p with unsigned 1
	Probe p = { 1u };

	// In a big endian architecture, p.nBytes[0] equals 0
	return (p.nBytes[0] == 1u);
}

/**
*  @brief
*    Returns the name of the platform
*/
String System::GetPlatform() const
{
	// Call system function
	return m_pSystemImpl->GetPlatform();
}

/**
*  @brief
*    Returns the name and version of the operating system
*/
String System::GetOS() const
{
	// Call system function
	return m_pSystemImpl->GetOS();
}

/**
*  @brief
*    Get the CPU mhz
*/
uint32 System::GetCPUMhz() const
{
	// Call system function
	return m_pSystemImpl->GetCPUMhz();
}

/**
*  @brief
*    Returns the name of the computer
*/
String System::GetComputerName() const
{
	// Call system function
	return m_pSystemImpl->GetComputerName();
}

/**
*  @brief
*    Returns the current user name
*/
String System::GetUserName() const
{
	// Call system function
	return m_pSystemImpl->GetUserName();
}

/**
*  @brief
*    Get home directory of the current user
*/
String System::GetUserHomeDir() const
{
	// Call system function
	return m_pSystemImpl->GetUserHomeDir();
}

/**
*  @brief
*    Get data directory of the current user
*/
String System::GetUserDataDir() const
{
	// Call system function
	return m_pSystemImpl->GetUserDataDir();
}

/**
*  @brief
*    Get name of data directory for given application name
*/
String System::GetDataDirName(const String &sName) const
{
	// Call system function
	return m_pSystemImpl->GetDataDirName(sName);
}

/**
*  @brief
*    Get absolute path of application executable
*/
String System::GetExecutableFilename() const
{
	// Call system function
	return m_pSystemImpl->GetExecutableFilename();
}

/**
*  @brief
*    Reads an environment variable
*/
String System::GetEnvironmentVariable(const String &sName) const
{
	// Call system function
	return m_pSystemImpl->GetEnvironmentVariable(sName);
}

/**
*  @brief
*    Writes an environment variable
*/
bool System::SetEnvironmentVariable(const String &sName, const String &sValue) const
{
	// Call system function
	return m_pSystemImpl->SetEnvironmentVariable(sName, sValue);
}

/**
*  @brief
*    Deletes an environment variable
*/
void System::DeleteEnvironmentVariable(const String &sName) const
{
	// Call system function
	return m_pSystemImpl->DeleteEnvironmentVariable(sName);
}

/**
*  @brief
*    Executes a system command (create a new process)
*/
bool System::Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir) const
{
	// Call system function
	return m_pSystemImpl->Execute(sCommand, sParameters, sWorkingDir);
}

/**
*  @brief
*    Returns the current program locale language information
*/
String System::GetLocaleLanguage() const
{
	// Call system function
	return m_pSystemImpl->GetLocaleLanguage();
}

/**
*  @brief
*    Returns the current directory
*/
String System::GetCurrentDir() const
{
	// Call system function
	return m_pSystemImpl->GetCurrentDir();
}

/**
*  @brief
*    Sets the current directory
*/
bool System::SetCurrentDir(const String &sPath)
{
	// Call system function
	return m_pSystemImpl->SetCurrentDir(sPath);
}

/**
*  @brief
*    Returns a pointer to the main thread
*/
Thread *System::GetMainThread() const
{
	// Return main thread
	return m_pMainThread;
}

/**
*  @brief
*    Returns a pointer to the current thread
*/
Thread *System::GetCurrentThread() const
{
	// Call system function
	Thread *pThread = m_pSystemImpl->GetCurrentThread();
	return pThread ? pThread : m_pMainThread;
}

/**
*  @brief
*    Exit the application immediatly
*/
void System::Exit(int nReturn)
{
	// Call system function
	m_pSystemImpl->Exit(nReturn);
}

/**
*  @brief
*    Returns the console instance
*/
const Console &System::GetConsole() const
{
	// Call system function
	return m_pSystemImpl->GetConsole();
}

/**
*  @brief
*    Returns the current date and time
*/
Time System::GetTime() const
{
	// Call system function
	return m_pSystemImpl->GetTime();
}

/**
*  @brief
*    Returns the number of milliseconds since the system was started
*/
uint64 System::GetMilliseconds() const
{
	// Call system function
	return m_pSystemImpl->GetMilliseconds();
}

/**
*  @brief
*    Retrieves the number of microseconds since the system was started
*/
uint64 System::GetMicroseconds() const
{
	// Call system function
	return m_pSystemImpl->GetMicroseconds();
}

/**
*  @brief
*    Suspend the current thread for a specified time period
*/
void System::Sleep(uint64 nMilliseconds) const
{
	// Call system function
	m_pSystemImpl->Sleep(nMilliseconds);
}

/**
*  @brief
*    Yields the rest of the current threads time slice
*/
void System::Yield() const
{
	// Call system implementation
	m_pSystemImpl->Yield();
}

/**
*  @brief
*    Returns an approximation of the percentage of used physical memory (0.0-100.0)
*/
float System::GetPercentageOfUsedPhysicalMemory() const
{
	// Call system function
	return m_pSystemImpl->GetPercentageOfUsedPhysicalMemory();
}

/**
*  @brief
*    Returns the total physical memory in bytes
*/
uint64 System::GetTotalPhysicalMemory() const
{
	// Call system function
	return m_pSystemImpl->GetTotalPhysicalMemory();
}

/**
*  @brief
*    Returns the current free physical memory in bytes
*/
uint64 System::GetFreePhysicalMemory() const
{
	// Call system function
	return m_pSystemImpl->GetFreePhysicalMemory();
}

/**
*  @brief
*    Returns the total virtual memory in bytes
*/
uint64 System::GetTotalVirtualMemory() const
{
	// Call system function
	return m_pSystemImpl->GetTotalVirtualMemory();
}

/**
*  @brief
*    Returns the current free virtual memory in bytes
*/
uint64 System::GetFreeVirtualMemory() const
{
	// Call system function
	return m_pSystemImpl->GetFreeVirtualMemory();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
System::System() :
	m_pSystemImpl(nullptr),
	m_pMainThread(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pSystemImpl = new SystemWindows();
	#elif defined(LINUX)
		// Create Linux implementation
		m_pSystemImpl = new SystemLinux();
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif

	// Create main thread object
	m_pMainThread = new Thread(true);
}

/**
*  @brief
*    Copy constructor
*/
System::System(const System &cSource) :
	m_pSystemImpl(nullptr),
	m_pMainThread(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
System::~System()
{
	// Destroy main thread object
	delete m_pMainThread;

	// Destroy system specific implementation
	if (m_pSystemImpl)
		delete m_pSystemImpl;
}

/**
*  @brief
*    Copy operator
*/
System &System::operator =(const System &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
