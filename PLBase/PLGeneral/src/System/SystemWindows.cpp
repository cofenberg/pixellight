/*********************************************************\
 *  File: SystemWindows.cpp                              *
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
#include <Tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <shlobj.h>
#include <locale.h>
#include <windows.h>
#include <Userenv.h>
#include <shellapi.h>
#include "PLGeneral/File/Url.h"
#include "PLGeneral/System/SystemWindows.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
DWORD g_nTlsIndex = TLS_OUT_OF_INDEXES; // 'Thread Local Storage' (TLS), TLS_OUT_OF_INDEXES on error


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Converts a given Windows error code received by 'GetLastError()' into a human readable string
*/
String SystemWindows::ErrorCodeToString(DWORD nErrorCode)
{
	LPTSTR pszError;

	// Try to format the error code
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					  NULL, nErrorCode, 0, (LPTSTR)&pszError, 0, NULL)) {
		// All went fine, now build the PL string
		LPTSTR pszErrorEnd = _tcschr(pszError, _T('\r'));
		if (pszErrorEnd) *pszErrorEnd = _T('\0');
		String sError = pszError;
		LocalFree(pszError);

		// Done
		return sError;
	} else return String::Format("Unknown error code '%d'", nErrorCode);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SystemWindows::SystemWindows()
{
	// Force the main thread to always run on CPU 0.
	// This is done because on some systems QueryPerformanceCounter returns a bit different counter values
	// on the different CPUs (contrary to what it's supposed to do), which can cause negative frame times
	// if the thread is scheduled on the other CPU in the next frame. This can cause very jerky behavior and
	// appear as if frames return out of order.
	SetThreadAffinityMask(GetCurrentThread(), 1);

	// Initialize performance timer
	QueryPerformanceFrequency(&m_nPerformanceFrequency);

	// Initalize the random generator
	srand((unsigned)GetMicroseconds());

	// Allocate a global TLS index
	g_nTlsIndex = TlsAlloc();
}

/**
*  @brief
*    Destructor
*/
SystemWindows::~SystemWindows()
{
	// Free our global TLS index
	if (g_nTlsIndex != TLS_OUT_OF_INDEXES) {
		TlsFree(g_nTlsIndex);
		g_nTlsIndex = TLS_OUT_OF_INDEXES;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual SystemImpl functions                ]
//[-------------------------------------------------------]
String SystemWindows::GetPlatform() const
{
#ifdef WIN64
	static const String sString = "Win64";
#else
	static const String sString = "Win32";
#endif
	return sString;
}

String SystemWindows::GetOS() const
{
	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;

	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	BOOL bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi);
	if (!bOsVersionInfoEx) {
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO*)&osvi))
			return "Windows";
	}

	// Call GetNativeSystemInfo if supported or GetSystemInfo otherwise
	PGNSI pGNSI = (PGNSI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
	if (pGNSI) pGNSI(&si);
	else	   GetSystemInfo(&si);

	// Compose version string
	String sVersion;

	// Get Windows version
	switch (osvi.dwPlatformId) {
		// Test for the Windows NT product family
		case VER_PLATFORM_WIN32_NT:
			// Test for the specific product
			if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1) {
				if (osvi.wProductType == VER_NT_WORKSTATION)
					sVersion += "Windows 7 ";
				else
					sVersion += "Windows Server 2008 R2 ";

			} else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0) {
				if (osvi.wProductType == VER_NT_WORKSTATION)
					sVersion += "Windows Vista ";
				else
					sVersion += "Windows Server \"Longhorn\" ";

			} else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2) {
				#ifndef SM_SERVERR2
					#define SM_SERVERR2 89
				#endif
				if (GetSystemMetrics(SM_SERVERR2))
					sVersion += "Microsoft Windows Server 2003 \"R2\" ";
				else if (osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					sVersion += "Microsoft Windows XP Professional x64 Edition ";
				else
					sVersion += "Microsoft Windows Server 2003, ";

			} else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
				sVersion += "Microsoft Windows XP ";

			else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
				sVersion += "Microsoft Windows 2000 ";

			else if (osvi.dwMajorVersion <= 4)
				sVersion += "Microsoft Windows NT ";

			// Test for specific product on Windows NT 4.0 SP6 and later
			if (bOsVersionInfoEx) {
				// Test for the workstation type
				if (osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64) {
					if (osvi.dwMajorVersion == 4)
						sVersion += "Workstation 4.0 ";
					else if (osvi.wSuiteMask & VER_SUITE_PERSONAL)
						sVersion += "Home Edition ";
					else
						sVersion += "Professional ";
				}

				// Test for the server type
				else if (osvi.wProductType == VER_NT_SERVER || osvi.wProductType == VER_NT_DOMAIN_CONTROLLER) {
					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2) {
						if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
							if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
								sVersion += "Datacenter Edition for Itanium-based Systems";
							else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
								sVersion += "Enterprise Edition for Itanium-based Systems";

						} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
							if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
								sVersion += "Datacenter x64 Edition ";
							else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
								sVersion += "Enterprise x64 Edition ";
							else
								sVersion += "Standard x64 Edition ";

						} else {
							if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
								sVersion += "Datacenter Edition ";
							else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
								sVersion += "Enterprise Edition ";
							else if (osvi.wSuiteMask == VER_SUITE_BLADE)
								sVersion += "Web Edition ";
							else
								sVersion += "Standard Edition ";
						}

					} else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0) {
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							sVersion += "Datacenter Server ";
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							sVersion += "Advanced Server ";
						else
							sVersion += "Server ";

					} else { // Windows NT 4.0
						if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							sVersion += "Server 4.0, Enterprise Edition ";
						else
							sVersion += "Server 4.0 ";
					}
				}

			// Test for specific product on Windows NT 4.0 SP5 and earlier
			} else {
				HKEY hKey;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
										 TEXT("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"),
										 0, KEY_QUERY_VALUE, &hKey);
				if (lRet != ERROR_SUCCESS)
					break;

				TCHAR szProductType[80];
				DWORD dwBufLen = 80*sizeof(TCHAR);
				lRet = RegQueryValueEx(hKey, TEXT("ProductType"), NULL, NULL,
									   (LPBYTE) szProductType, &dwBufLen);
				RegCloseKey(hKey);

				if (lRet != ERROR_SUCCESS || dwBufLen > 80*sizeof(TCHAR))
					break;

				if (!lstrcmpi(TEXT("WINNT"), szProductType))
					sVersion += "Workstation ";
				if (!lstrcmpi(TEXT("LANMANNT"), szProductType))
					sVersion += "Server ";
				if (!lstrcmpi(TEXT("SERVERNT"), szProductType))
					sVersion += "Advanced Server ";
				sVersion += String::Format("%d.%d ", osvi.dwMajorVersion, osvi.dwMinorVersion);
			}

			// Display service pack (if any) and build number
			if (osvi.dwMajorVersion == 4 && !lstrcmpi(osvi.szCSDVersion, TEXT("Service Pack 6"))) {
				// Test for SP6 versus SP6a
				HKEY hKey;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
										 TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009"),
										 0, KEY_QUERY_VALUE, &hKey);
				if (lRet == ERROR_SUCCESS)
					sVersion += String::Format("Service Pack 6a (Build %d)", osvi.dwBuildNumber & 0xFFFF);
				else { // Windows NT 4.0 prior to SP6a
					sVersion += String::Format(TEXT("%s (Build %d)"), osvi.szCSDVersion, osvi.dwBuildNumber & 0xFFFF);
				}

				RegCloseKey(hKey);
			} else { // Not Windows NT 4.0 
				sVersion += String::Format(TEXT("%s (Build %d)"), osvi.szCSDVersion, osvi.dwBuildNumber & 0xFFFF);
			}
		break;

		// Test for the Windows Me/98/95
		case VER_PLATFORM_WIN32_WINDOWS:
			if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0) {
				sVersion += "Microsoft Windows 95 ";
				if (osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B')
					sVersion += "OSR2 ";

			} else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10) {
				sVersion += "Microsoft Windows 98 ";
				if (osvi.szCSDVersion[1] == 'A' || osvi.szCSDVersion[1] == 'B')
					sVersion += "SE ";

			} else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90) {
				sVersion += "Microsoft Windows Millennium Edition";
			}
		break;

		case VER_PLATFORM_WIN32s:
			sVersion += "Microsoft Win32s";
			break;
	}

	// Fallback, if unknown version number combination found
	if (sVersion.GetLength())
		sVersion.Trim();
	else
		sVersion = "Windows";

	// Return the found Windows version
	return sVersion;
}

uint32 SystemWindows::GetCPUMhz() const
{
#if !defined(WIN64) && !defined(NO_INLINE_ASM)
	// 32 Bit assembler method
	unsigned long nStartTicks = 0;
	unsigned long nEndTicks   = 0;
	uint32 nTimeStop;

	uint32 nTimeStart = GetMilliseconds();
	do {
		nTimeStop = GetMilliseconds();
		// Rollover past 1
	} while (nTimeStop - nTimeStart <= 1);
	__asm {
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx
		_emit 0x0f // CPUID
		_emit 0xa2
		_emit 0x0f // RTDSC
		_emit 0x31
		mov [nStartTicks], eax // Tick counter starts here
	}

	nTimeStart = nTimeStop;
	do {
		nTimeStop = GetMilliseconds();
		// One second
	} while (nTimeStop - nTimeStart <= 1000);
	__asm {
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx
		_emit 0x0f
		_emit 0xa2
		_emit 0x0f
		_emit 0x31
		mov [nEndTicks], eax
	}

	// Total tick count
	unsigned long nTotalTicks = nEndTicks - nStartTicks;

	// CPU Speed
	return uint32(nTotalTicks / 1000000);
#elif defined(WIN64) && !defined(NO_INLINE_ASM)
	// 64 Bit assembler method
	// [TODO] Implement 64 bit version
	return 0;
#else
	// C++ method
	// [TODO] Implement C++ version
	return 0;
#endif
}

String SystemWindows::GetComputerName() const
{
	// First of all, get the length of the computer name (including the terminating zero)
	DWORD nTempLength = 0;
	GetComputerNameW(NULL, &nTempLength);
	if (nTempLength) {
		// Get computer name
		wchar_t *pszTemp = new wchar_t[nTempLength];
		if (GetComputerNameW(pszTemp, &nTempLength)) {
			return String(pszTemp, false, nTempLength); // Do not copy, please
		} else {
			// We no longer need the data, so free it
			delete [] pszTemp;
		}
	}

	// Error!
	return "";
}

String SystemWindows::GetUserName() const
{
	// First of all, get the length of the user name (including the terminating zero)
	DWORD nTempLength = 0;
	GetUserNameW(NULL, &nTempLength);
	if (nTempLength) {
		// Get user name
		wchar_t *pszTemp = new wchar_t[nTempLength];
		if (GetUserNameW(pszTemp, &nTempLength)) {
			return String(pszTemp, false, nTempLength-1); // Do not copy, please
		} else {
			// We no longer need the data, so free it
			delete [] pszTemp;
		}
	}

	// Error!
	return "";
}

String SystemWindows::GetUserHomeDir() const
{
	// Open the access token associated with our process
	HANDLE hToken = 0;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken) != 0) {
		// First of all, get the length of the user home directory (including the terminating zero)
		DWORD nTempLength = 0;
		GetUserProfileDirectoryW(hToken, NULL, &nTempLength);
		if (nTempLength) {
			// Get user home directory
			wchar_t *pszTemp = new wchar_t[nTempLength];
			if (GetUserProfileDirectoryW(hToken, pszTemp, &nTempLength)) {
				// Close the access token
				CloseHandle(hToken);

				// Do not copy, please
				return String(pszTemp, false, nTempLength-1);
			} else {
				// We no longer need the data, so free it
				delete [] pszTemp;
			}
		}

		// Close the access token
		CloseHandle(hToken);
	}

	// Error!
	return "";
}

String SystemWindows::GetUserDataDir() const
{
	// Get application data path
	wchar_t szPath[MAX_PATH];
	SHGetSpecialFolderPathW(NULL, szPath, CSIDL_APPDATA, FALSE);

	// Return path (copy string)
	return szPath;
}

String SystemWindows::GetDataDirName(const String &sName) const
{
	// Use name directly
	return sName;
}

String SystemWindows::GetExecutableFilename() const
{
	// Allocate a buffer that is large enough to hold the information
	wchar_t *pszBuffer = new wchar_t[MAX_PATH];

	// Get user name as Unicode
	if (GetModuleFileNameW(NULL, pszBuffer, MAX_PATH)) {
		return String(pszBuffer, false); // Do not copy, please
	} else {
		// We no longer need the data, so free it
		delete [] pszBuffer;

		// Error
		return "";
	}
}

String SystemWindows::GetEnvironmentVariable(const String &sName) const
{
	// Get size of buffer to receive variable value
	// This ASCII/Unicode check may look weird: "It's based on the type of the name-string, used only for the size and then returns a unicode-string anyway.
	// Perhaps skip this completely?" - we could skip it, right... but then 'sName' MUST be converted internally ALWAYS to
	// Unicode even if in the most cases ASCII is given and in the case that no such environment variable was found, this additional work
	// was quite useless. (yeah, not really performance critical - but if there's a chance to skip some work, we should take it)
	DWORD nSize = (sName.GetFormat() == String::ASCII) ? GetEnvironmentVariableA(sName.GetASCII(), NULL, 0) : GetEnvironmentVariableW(sName.GetUnicode(), NULL, 0);
	if (nSize > 0) {
		// Get variable as Unicode
		wchar_t *pszBuffer = new wchar_t[nSize];
		if (GetEnvironmentVariableW(sName.GetUnicode(), pszBuffer, nSize) > 0) {
			return String(pszBuffer, false); // Do not copy, please
		} else {
			// We no longer need the data, so free it
			delete [] pszBuffer;
		}
	}

	// Error!
	return "";
}

bool SystemWindows::SetEnvironmentVariable(const String &sName, const String &sValue) const
{
	if (sName.GetFormat() == String::ASCII)
		return (SetEnvironmentVariableA(sName.GetASCII(),   sValue.GetASCII())   > 0);
	else
		return (SetEnvironmentVariableW(sName.GetUnicode(), sValue.GetUnicode()) > 0);
}

void SystemWindows::DeleteEnvironmentVariable(const String &sName) const
{
	if (sName.GetFormat() == String::ASCII)
		SetEnvironmentVariableA(sName.GetASCII(),   NULL);
	else
		SetEnvironmentVariableW(sName.GetUnicode(), NULL);
}

bool SystemWindows::Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir) const
{
	// Check if a command has been given
	if (!sCommand.GetLength())
		return false; // Error!

	// Execute command
	size_t nResult;
	if (sCommand.GetFormat() == String::ASCII && sParameters.GetFormat() == String::ASCII && sWorkingDir.GetFormat() == String::ASCII) {
		nResult = (size_t)ShellExecuteA(
			NULL,
			"open",
			sCommand.GetASCII(),
			sParameters.GetLength() ? sParameters.GetASCII() : NULL,
			sWorkingDir.GetLength() ? sWorkingDir.GetASCII() : NULL,
			SW_SHOWDEFAULT
		);
	} else {
		nResult = (size_t)ShellExecuteW(
			NULL,
			L"open",
			sCommand.GetUnicode(),
			sParameters.GetLength() ? sParameters.GetUnicode() : NULL,
			sWorkingDir.GetLength() ? sWorkingDir.GetUnicode() : NULL,
			SW_SHOWDEFAULT
		);
	}

	// Has the execution been successful?
	return (nResult > 32);
}

String SystemWindows::GetLocaleLanguage() const
{
	// Get the locale
	const char *pszSaveLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "");
	String sLocal = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, pszSaveLocale);

	// Find the '_'
	int nIndex = sLocal.IndexOf("_");
	return (nIndex >= 0) ? sLocal.GetSubstring(0, nIndex) : "";
}

String SystemWindows::GetCurrentDir() const
{
	// First of all, get the length of the current directory (including the terminating zero)
	uint32 nTempLength = GetCurrentDirectoryW(0, NULL);
	if (nTempLength) {
		// Get current directory
		wchar_t *pszTemp = new wchar_t[nTempLength];
		GetCurrentDirectoryW(nTempLength, pszTemp);
		String sDir = String(pszTemp, false, nTempLength-1); // Do not copy, please

		// Return the URL
		return Url(sDir).GetNativePath();
	} else return ""; // Done
}

bool SystemWindows::SetCurrentDir(const String &sPath)
{
	// Get path in Windows style
	const String sWindowsPath = Url(sPath).GetWindowsPath();

	// Set current directory
	if (sWindowsPath.GetFormat() == String::ASCII)
		return (SetCurrentDirectoryA(sWindowsPath.GetASCII()) != 0);
	else
		return (SetCurrentDirectoryW(sWindowsPath.GetUnicode()) != 0);
}

Thread *SystemWindows::GetCurrentThread() const
{
	// Valid TLS?
	if (g_nTlsIndex != TLS_OUT_OF_INDEXES) {
		// Get the dynamic memory of the current thread, if NULL, this must be the main thread
		return (Thread*)TlsGetValue(g_nTlsIndex);
	} else return NULL; // Error!
}

void SystemWindows::Exit(int nReturn)
{
	// Exit
	exit(nReturn);
}

const Console &SystemWindows::GetConsole() const
{
	return m_cConsole;
}

Time SystemWindows::GetTime() const
{
	SYSTEMTIME sTime;
	GetLocalTime(&sTime);
	return Time(sTime.wYear,
				(Time::EMonth)(sTime.wMonth),
				(uint8)sTime.wDay,
				(Time::EDay)sTime.wDayOfWeek,
				(uint8)sTime.wHour,
				(uint8)sTime.wMinute,
				(uint8)sTime.wSecond,
				sTime.wMilliseconds);
}

uint32 SystemWindows::GetMilliseconds() const
{
	// Get past time
	LARGE_INTEGER nCurTime;
	QueryPerformanceCounter(&nCurTime);
	LONGLONG nNewTicks = nCurTime.QuadPart;

	// Scale by 1000 in order to get millisecond precision
	nNewTicks *= 1000;
	if (m_nPerformanceFrequency.QuadPart)
		nNewTicks /= m_nPerformanceFrequency.QuadPart;

	// Return past time
	return (uint32)nNewTicks;
}

uint32 SystemWindows::GetMicroseconds() const
{
	// Get past time
	LARGE_INTEGER nCurTime;
	QueryPerformanceCounter(&nCurTime);
	double dNewTicks = (double)nCurTime.QuadPart;

	// Scale by 1000000 in order to get microsecond precision
	dNewTicks *= (double)1000000.0/(double)m_nPerformanceFrequency.QuadPart;

	// Return past time
	return (uint32)dNewTicks;
}

void SystemWindows::Sleep(uint32 nMilliseconds) const
{
	SleepEx(nMilliseconds, false);
}

void SystemWindows::Yield() const
{
	// By passing 0 to the sleep Windows function it behaves like desired (this is from Microsoft documented behaviour)
	SleepEx(0, false);
}

float SystemWindows::GetPercentageOfUsedPhysicalMemory() const
{
	MEMORYSTATUSEX sMemoryInfo;
	sMemoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
	return GlobalMemoryStatusEx(&sMemoryInfo) ? (float)sMemoryInfo.dwMemoryLoad : 0;
}

uint64 SystemWindows::GetTotalPhysicalMemory() const
{
	MEMORYSTATUSEX sMemoryInfo;
	sMemoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
	return GlobalMemoryStatusEx(&sMemoryInfo) ? sMemoryInfo.ullTotalPhys : 0;
}

uint64 SystemWindows::GetFreePhysicalMemory() const
{
	MEMORYSTATUSEX sMemoryInfo;
	sMemoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
	return GlobalMemoryStatusEx(&sMemoryInfo) ? sMemoryInfo.ullAvailPhys : 0;
}

uint64 SystemWindows::GetTotalVirtualMemory() const
{
	MEMORYSTATUSEX sMemoryInfo;
	sMemoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
	return GlobalMemoryStatusEx(&sMemoryInfo) ? sMemoryInfo.ullTotalVirtual : 0;
}

uint64 SystemWindows::GetFreeVirtualMemory() const
{
	MEMORYSTATUSEX sMemoryInfo;
	sMemoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
	return GlobalMemoryStatusEx(&sMemoryInfo) ? sMemoryInfo.ullAvailVirtual : 0;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
