/*********************************************************\
 *  File: SystemLinux.h                                  *
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


#ifndef __PLGENERAL_SYSTEM_LINUX_H__
#define __PLGENERAL_SYSTEM_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <sys/utsname.h>
#include "PLGeneral/System/ConsoleLinux.h"
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
*    Linux 'System' implementation
*/
class SystemLinux : public SystemImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class System;


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Holds memory information
		*/
		struct MemoryInformation {
			uint64 nTotalPhysicalMemory;	/**< Total physical memory in bytes */
			uint64 nFreePhysicalMemory;		/**< Free physical memory in bytes */
			uint64 nTotalSwapMemory;		/**< Total swap memory in bytes */
			uint64 nFreeSwapMemory;			/**< Free swap memory in bytes */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		SystemLinux();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SystemLinux();

		/**
		*  @brief
		*    Reads memory information from the '/proc/meminfo'-file
		*
		*  @param[out] sMemoryInformation
		*    Receives the memory information
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool GetMemoryInformation(MemoryInformation &sMemoryInformation) const;


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
		ConsoleLinux   m_cConsole;		/**< Console instance */
		bool		   m_bSysInfoInit;	/**< Has 'm_sName' a valid value? */
		struct utsname m_sName;			/**< Basic system information */
		String		   m_sFilename;		/**< Application filename */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_SYSTEM_LINUX_H__
