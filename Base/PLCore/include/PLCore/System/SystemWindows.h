/*********************************************************\
 *  File: SystemWindows.h                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_SYSTEM_WINDOWS_H__
#define __PLCORE_SYSTEM_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCoreWindowsIncludes.h"
#include "PLCore/System/ConsoleWindows.h"
#include "PLCore/System/SystemImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


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
		static PLCORE_API String ErrorCodeToString(DWORD nErrorCode);


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
		virtual String GetPlatform() const override;
		virtual String GetOS() const override;
		virtual char GetSeparator() const override;
		virtual String GetSharedLibraryPrefix() const override;
		virtual String GetSharedLibraryExtension() const override;
		virtual uint32 GetCPUMhz() const override;
		virtual String GetComputerName() const override;
		virtual String GetUserName() const override;
		virtual String GetUserHomeDir() const override;
		virtual String GetUserDataDir() const override;
		virtual String GetDataDirName(const String &sName) const override;
		virtual String GetExecutableFilename() const override;
		virtual String GetEnvironmentVariable(const String &sName) const override;
		virtual bool SetEnvironmentVariable(const String &sName, const String &sValue) const override;
		virtual void DeleteEnvironmentVariable(const String &sName) const override;
		virtual bool Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir) const override;
		virtual String GetLocaleLanguage() const override;
		virtual String GetCurrentDir() const override;
		virtual bool SetCurrentDir(const String &sPath) override;
		virtual Thread *GetCurrentThread() const override;
		virtual void Exit(int nReturn) override;
		virtual const Console &GetConsole() const override;
		virtual void UrgentMessage(const String &sMessage) const override;
		virtual Time GetTime() const override;
		virtual uint64 GetMilliseconds() const override;
		virtual uint64 GetMicroseconds() const override;
		virtual void Sleep(uint64 nMilliseconds) const override;
		virtual void Yield() const override;
		virtual float GetPercentageOfUsedPhysicalMemory() const override;
		virtual uint64 GetTotalPhysicalMemory() const override;
		virtual uint64 GetFreePhysicalMemory() const override;
		virtual uint64 GetTotalVirtualMemory() const override;
		virtual uint64 GetFreeVirtualMemory() const override;


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
} // PLCore


#endif // __PLCORE_SYSTEM_WINDOWS_H__
