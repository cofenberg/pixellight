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


#include <windows.h>
#include <PixelLight.h>


void Message(const wchar_t szMessage[])
{
	MessageBox(NULL, szMessage, L"PixelLight Installation", MB_OK);
}

bool CheckWindowsVersion()
{
	OSVERSIONINFOEX ver;

	// Initialize structur
	ZeroMemory(&ver, sizeof(OSVERSIONINFOEX));
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	// Get version info
	if (!GetVersionEx((OSVERSIONINFO*)&ver)) {
		// Error with OSVERSIONINFOEX, try OSVERSIONINFO
		ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO*)&ver))
			return false;
	}

	// Check Windows version
	return ver.dwPlatformId == VER_PLATFORM_WIN32_NT;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pszCmdLine, int nShow)
{
	// Check Windows version
	if (CheckWindowsVersion()) {
		// Get current directory
		wchar_t szDir[_MAX_PATH], szDirUpcase[_MAX_PATH];
		GetModuleFileName(NULL, szDir, _MAX_PATH);
		wchar_t szApplicationDrive[_MAX_PATH], szApplicationDir[_MAX_PATH];
		_wsplitpath(szDir, szApplicationDrive, szApplicationDir, NULL, NULL);
		wcscpy(szDirUpcase, szApplicationDrive);
		wcscat(szDirUpcase, szApplicationDir);
		if (szDirUpcase[wcslen(szDirUpcase)-1] == L'\\')
			szDirUpcase[wcslen(szDirUpcase)-1] = 0;
		wcscpy(szDir, szDirUpcase);
		_wcsupr(szDirUpcase);

		// Add directory to PATH variable
		HKEY hKey;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Environment", 0, KEY_READ | KEY_WRITE, &hKey) == ERROR_SUCCESS) {
			// Query size of PATH variable
			DWORD nPathSize = 0;
			RegQueryValueEx(hKey, L"PATH", 0, NULL, NULL, &nPathSize);
			nPathSize += _MAX_PATH + 8;
			wchar_t *pszPath = new wchar_t[nPathSize];

			// Query value of PATH variable
			DWORD nType;
			DWORD nSize = nPathSize;
			LSTATUS nResult = RegQueryValueEx(hKey, L"PATH", 0, &nType, (BYTE*)pszPath, &nSize);
			if (nResult == ERROR_FILE_NOT_FOUND) {
				// Write to registry
				RegSetValueEx(hKey, L"PATH", 0, REG_SZ, (BYTE*)szDir, (DWORD)sizeof(wchar_t)*wcslen(szDir));
				RegFlushKey(hKey);
			} else if (nResult == ERROR_SUCCESS) {
				// Get upper case version
				wchar_t *pszPathUpcase = new wchar_t[nSize];
				wcscpy(pszPathUpcase, pszPath);
				_wcsupr(pszPathUpcase);

				// Check if path is already set to this directory
				if (!wcsstr(pszPathUpcase, szDirUpcase)) {
					// Add directory to path
					if (wcslen(pszPath) && pszPath[wcslen(pszPath) - 1] != L';')
						wcscat(pszPath, L";");
					wcscat(pszPath, szDir);
					wcscat(pszPath, L";");

					// Write back to registry
					pszPath[wcslen(pszPath) + 1] = L'\0';
					RegSetValueEx(hKey, L"PATH", 0, nType, (BYTE*)pszPath, (DWORD)sizeof(wchar_t)*wcslen(pszPath));
					RegFlushKey(hKey);
				}

				// Release data
				if (pszPathUpcase)
					delete [] pszPathUpcase;
			}

			// Clean up
			if (pszPath)
				delete [] pszPath;
			RegCloseKey(hKey);
		} else {
			Message(L"Konnte \"HKEY_CURRENT_USER\\Environment\" nicht öffnen");
		}

		// Get PixelLight suffix and compose registry key from it
		wchar_t szSuffix[256];
		mbstowcs(szSuffix, PIXELLIGHT_SUFFIX, strlen(PIXELLIGHT_SUFFIX)+1);
		wchar_t szSubkey[256];
		wcscpy(szSubkey, L"SOFTWARE\\PixelLight\\PixelLight-SDK");
		if (wcslen(szSuffix) > 0) {
			wcscat(szSubkey, L"-");
			wcscat(szSubkey, szSuffix);
		}

		// Add directory to registry key "SOFTWARE\\PixelLight\\PixelLight-SDK"
		if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szSubkey, 0, NULL, 0, KEY_READ | KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
			// Set value
			RegSetValueEx(hKey, L"Runtime", 0, REG_SZ, (BYTE*)szDir, (DWORD)sizeof(wchar_t)*wcslen(szDir));
			RegFlushKey(hKey);

			// Clean up
			RegCloseKey(hKey);
		} else {
			Message(L"Konnte \"HKEY_LOCAL_MACHINE\\SOFTWARE\\PixelLight\\PixelLight-SDK\" nicht öffnen oder erstellen");
		}

		// We need to send a broadcast so other processes will be informed about the change. If this is not done,
		// 'dlls' still will not be found although the "PATH" environment variable was updated!
		DWORD nResult;
		SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"Environment", SMTO_NORMAL, 4000, &nResult);

		// Output message
		Message(L"Die PixelLight DLLs wurden installiert. Bitte starten Sie das System neu, damit die Änderungen wirksam werden");
	} else {
		Message(L"Der Installer benötigt Windows 2000/NT/XP");
	}

	// Done
	return 0;
}
