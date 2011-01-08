/*********************************************************\
 *  File: SystemWindows.h                                *
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


#ifndef __PLGENERAL_SYSTEM_WINDOWS_H__
#define __PLGENERAL_SYSTEM_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneralWindowsIncludes.h"
#include "PLGeneral/System/ConsoleWindows.h"
#include "PLGeneral/System/SystemImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows 'System' implementation
*/
class SystemWindows : public SystemImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class System;


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Converts a given Windows error code received by 'GetLastError()' into a human readable string
		*
		*  @param[in] nErrorCode
		*    Windows error code to convert into a string
		*
		*  @return
		*    The resulting string
		*/
		PLGENERAL_API static String ErrorCodeToString(DWORD nErrorCode);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		SystemWindows();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SystemWindows();


	//[-------------------------------------------------------]
	//[ Private virtual SystemImpl functions                  ]
	//[-------------------------------------------------------]
	private:
		virtual String GetPlatform() const;
		virtual String GetOS() const;
		virtual uint32 GetCPUMhz() const;
		virtual String GetComputerName() const;
		virtual String GetUserName() const;
		virtual String GetUserHomeDir() const;
		virtual String GetUserDataDir() const;
		virtual String GetDataDirName(const String &sName) const;
		virtual String GetExecutableFilename() const;
		virtual String GetEnvironmentVariable(const String &sName) const;
		virtual bool SetEnvironmentVariable(const String &sName, const String &sValue) const;
		virtual void DeleteEnvironmentVariable(const String &sName) const;
		virtual bool Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir) const;
		virtual String GetLocaleLanguage() const;
		virtual String GetCurrentDir() const;
		virtual bool SetCurrentDir(const String &sPath);
		virtual Thread *GetCurrentThread() const;
		virtual void Exit(int nReturn);
		virtual const Console &GetConsole() const;
		virtual Time GetTime() const;
		virtual uint32 GetMilliseconds() const;
		virtual uint32 GetMicroseconds() const;
		virtual void Sleep(uint32 nMilliseconds) const;
		virtual void Yield() const;
		virtual float GetPercentageOfUsedPhysicalMemory() const;
		virtual uint64 GetTotalPhysicalMemory() const;
		virtual uint64 GetFreePhysicalMemory() const;
		virtual uint64 GetTotalVirtualMemory() const;
		virtual uint64 GetFreeVirtualMemory() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ConsoleWindows m_cConsole;				/**< Console instance */
		LARGE_INTEGER  m_nPerformanceFrequency;	/**< Frequency of the performance counter */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_SYSTEM_WINDOWS_H__
