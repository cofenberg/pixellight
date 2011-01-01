/*********************************************************\
 *  File: Process.cpp                                    *
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
#if defined(WIN32)
	#include "PLGeneral/PLGeneralWindowsIncludes.h"
#elif defined(LINUX)
	#include <unistd.h>
	#include <signal.h>
#endif
#include "PLGeneral/String/Tokenizer.h"
#include "PLGeneral/Container/List.h"
#include "PLGeneral/System/Process.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Process::Process()
{
	// Windows implementation
	#ifdef WIN32
		m_hProcess = NULL;
	#endif

	// Linux implementation
	#ifdef LINUX
		m_hProcess = 0;
	#endif
}

/**
*  @brief
*    Destructor
*/
Process::~Process()
{
	// Windows implementation
	#ifdef WIN32
		if (m_hProcess) CloseHandle((HANDLE)m_hProcess);
	#endif

	// Linux implementation
	#ifdef LINUX
	#endif
}

/**
*  @brief
*    Starts a process
*/
void Process::Execute(const String &sCommand, const String &sArguments)
{
	// Windows implementation
	#ifdef WIN32
		// Create process
		PROCESS_INFORMATION piProcInfo;
		ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
		STARTUPINFO siStartInfo;
		ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
		siStartInfo.cb = sizeof(STARTUPINFO);
		String sCmdLine = sCommand + " " + sArguments;
		BOOL bResult = CreateProcess(
							NULL,
							(LPWSTR)sCmdLine.GetUnicode(),	// Command line
							NULL,							// Process security attributes
							NULL,							// Primary thread security attributes
							TRUE,							// Handles are inherited
							0,								// Creation flags
							NULL,							// Use parent's environment
							NULL,							// Use parent's current directory
							&siStartInfo,					// STARTUPINFO pointer
							&piProcInfo						// Receives PROCESS_INFORMATION
						);

		// Check result
		if (bResult) {
			m_hProcess = (handle)piProcInfo.hProcess;
			CloseHandle(piProcInfo.hThread);
		}
	#endif

	// Linux implementation
	#ifdef LINUX
		// Create process
		m_hProcess = fork();
		if (m_hProcess == 0) {	// Child process
			// Get arguments
			List<String> lstArgs;
			lstArgs.Add(sCommand);
			Tokenizer tokenizer;
			tokenizer.SetSingleChars("");
			tokenizer.SetSingleLineComment("");
			tokenizer.Start(sArguments);
			String sToken = tokenizer.GetNextToken();
			while (sToken.GetLength()) {
				lstArgs.Add(sToken);
				sToken = tokenizer.GetNextToken();
			}

			// Make array for arguments
			const int nSize = lstArgs.GetNumOfElements();
			if (nSize > 0) {
				char **ppszParams = new char*[nSize+1];
				if (sCommand.GetFormat() == String::ASCII) {
					for (int i=0; i<nSize; i++)
						ppszParams[i] = (char*)lstArgs[i].GetASCII();
				} else {
					for (int i=0; i<nSize; i++)
						ppszParams[i] = (char*)lstArgs[i].GetUTF8();
				}
				ppszParams[nSize] = NULL;

				// Execute application
				execv((lstArgs[0].GetFormat() == String::ASCII) ? lstArgs[0].GetASCII() : (char*)lstArgs[0].GetUTF8(), ppszParams);
			}
		}
	#endif
}

/**
*  @brief
*    Starts a process with redirected input/output
*/
void Process::ExecuteRedirectIO(const String &sCommand, const String &sArguments)
{
	// Create pipes
	m_cPipeInput .Create();
	m_cPipeOutput.Create();
	m_cPipeError = m_cPipeOutput;

	// Create process with pipes
	CreateProcessRedirectIO(
		sCommand,
		sArguments,
		m_cPipeInput .GetReadHandle(),
		m_cPipeInput .GetWriteHandle(),
		m_cPipeOutput.GetReadHandle(),
		m_cPipeOutput.GetWriteHandle(),
		m_cPipeError .GetReadHandle(),
		m_cPipeError .GetWriteHandle()
	);

	// Close pipe handles that are unly used by the new process now
	m_cPipeInput .CloseRead();
	m_cPipeOutput.CloseWrite();
}

/**
*  @brief
*    Starts a process with redirected input/output
*/
void Process::ExecuteRedirectIO(const String &sCommand, const String &sArguments, const Pipe &cPipeIn, const Pipe &cPipeOut, const Pipe &cPipeErr)
{
	// Copy pipes
	m_cPipeInput  = cPipeIn;
	m_cPipeOutput = cPipeOut;
	m_cPipeError  = cPipeErr;

	// Create process with pipe handles
	CreateProcessRedirectIO(
		sCommand,
		sArguments,
		m_cPipeInput .GetReadHandle(),
		m_cPipeInput .GetWriteHandle(),
		m_cPipeOutput.GetReadHandle(),
		m_cPipeOutput.GetWriteHandle(),
		m_cPipeError .GetReadHandle(),
		m_cPipeError .GetWriteHandle()
	);

	// Close pipe handles that are unly used by the new process now
	m_cPipeInput .CloseRead();
	m_cPipeOutput.CloseWrite();
	if (cPipeErr != cPipeOut)
		m_cPipeError.CloseWrite();
}

/**
*  @brief
*    Starts a process with redirected input/output
*/
void Process::ExecuteRedirectIO(const String &sCommand, const String &sArguments, handle hPipeIn, handle hPipeOut, handle hPipeErr)
{
	// Copy pipes
	m_cPipeInput .Open(hPipeIn, INVALID_HANDLE);
	m_cPipeOutput.Open(INVALID_HANDLE, hPipeOut);
	m_cPipeError .Open(INVALID_HANDLE, hPipeErr);

	// Create process with pipe handles
	CreateProcessRedirectIO(
		sCommand,
		sArguments,
		m_cPipeInput .GetReadHandle(),
		INVALID_HANDLE,
		INVALID_HANDLE,
		m_cPipeOutput.GetWriteHandle(),
		INVALID_HANDLE,
		m_cPipeError .GetWriteHandle()
	);
}

/**
*  @brief
*    Returns if the process is running
*/
bool Process::IsRunning() const
{
	// Windows implementation
	#ifdef WIN32
		// Check process handle
		return (m_hProcess != NULL);
	#endif

	// Linux implementation
	#ifdef LINUX
		return false;
	#endif
}

/**
*  @brief
*    Terminates the process
*/
void Process::Terminate()
{
	// Windows implementation
	#ifdef WIN32
		TerminateProcess((HANDLE)m_hProcess, 0);
		CloseHandle((HANDLE)m_hProcess);
		m_hProcess = NULL;
	#endif

	// Linux implementation
	#ifdef LINUX
		kill(m_hProcess, SIGKILL);
		m_hProcess = 0;
	#endif

	// Reset streams and files
	m_cPipeInput .Open(INVALID_HANDLE, INVALID_HANDLE);
	m_cPipeOutput.Open(INVALID_HANDLE, INVALID_HANDLE);
	m_cPipeError .Open(INVALID_HANDLE, INVALID_HANDLE);
	m_cFileInput .Assign("");
	m_cFileOutput.Assign("");
	m_cFileError .Assign("");
}

/**
*  @brief
*    Get input stream
*/
File &Process::GetInput() const
{
	// Open file if not already done
	if (!m_cFileInput.IsOpen())
		((File&)m_cFileInput).Open(File::FileWrite | File::FileText);

	// Return file
	return (File&)m_cFileInput;
}

/**
*  @brief
*    Get output stream
*/
File &Process::GetOutput() const
{
	// Open file if not already done
	if (!m_cFileOutput.IsOpen())
		((File&)m_cFileOutput).Open(File::FileRead | File::FileText);

	// Return file
	return (File&)m_cFileOutput;
}

/**
*  @brief
*    Get error stream
*/
File &Process::GetError() const
{
	// Open file if not already done
	if (!m_cFileError.IsOpen())
		((File&)m_cFileError).Open(File::FileRead | File::FileText);

	// Return file
	return (File&)m_cFileError;
}

/**
*  @brief
*    Get input pipe
*/
const Pipe &Process::GetPipeInput() const
{
	// Return pipe
	return m_cPipeInput;
}

/**
*  @brief
*    Get output pipe
*/
const Pipe &Process::GetPipeOutput() const
{
	// Return pipe
	return m_cPipeOutput;
}

/**
*  @brief
*    Get error pipe
*/
const Pipe &Process::GetPipeError() const
{
	// Return pipe
	return m_cPipeError;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Process::Process(const Process &cSource)
{
	// Windows implementation
	#ifdef WIN32
		m_hProcess = NULL;
	#endif

	// Linux implementation
	#ifdef LINUX
		m_hProcess = 0;
	#endif
}

/**
*  @brief
*    Copy operator
*/
Process &Process::operator =(const Process &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Creates a process with redirected IO
*/
bool Process::CreateProcessRedirectIO(const String &sCommand, const String &sArguments, handle hPipeInRd, handle hPipeInWr, handle hPipeOutRd, handle hPipeOutWr, handle hPipeErrRd, handle hPipeErrWr)
{
	// Windows implementation
	#ifdef WIN32
		// Create process
		PROCESS_INFORMATION piProcInfo;
		ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
		const String sCmdLine = sCommand + ' ' + sArguments;
		BOOL bResult = FALSE;
		if (sCmdLine.GetFormat() == String::ASCII) {
			STARTUPINFOA siStartInfo;
			ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
			siStartInfo.cb = sizeof(STARTUPINFO);
			siStartInfo.hStdInput  = (HANDLE)hPipeInRd;
			siStartInfo.hStdOutput = (HANDLE)hPipeOutWr;
			siStartInfo.hStdError  = (HANDLE)hPipeErrWr;
			siStartInfo.dwFlags = STARTF_USESTDHANDLES;
			bResult = CreateProcessA(
							NULL,
							(LPSTR)sCmdLine.GetASCII(),	// Command line
							NULL,						// Process security attributes
							NULL,						// Primary thread security attributes
							TRUE,						// Handles are inherited
							0,							// Creation flags
							NULL,						// Use parent's environment
							NULL,						// Use parent's current directory
							&siStartInfo,				// STARTUPINFO pointer
							&piProcInfo					// Receives PROCESS_INFORMATION
						);
		} else {
			STARTUPINFOW siStartInfo;
			ZeroMemory(&siStartInfo, sizeof(STARTUPINFOW));
			siStartInfo.cb = sizeof(STARTUPINFOW);
			siStartInfo.hStdInput  = (HANDLE)hPipeInRd;
			siStartInfo.hStdOutput = (HANDLE)hPipeOutWr;
			siStartInfo.hStdError  = (HANDLE)hPipeErrWr;
			siStartInfo.dwFlags = STARTF_USESTDHANDLES;
			bResult = CreateProcessW(
							NULL,
							(LPWSTR)sCmdLine.GetUnicode(),	// Command line
							NULL,							// Process security attributes
							NULL,							// Primary thread security attributes
							TRUE,							// Handles are inherited
							0,								// Creation flags
							NULL,							// Use parent's environment
							NULL,							// Use parent's current directory
							&siStartInfo,					// STARTUPINFO pointer
							&piProcInfo						// Receives PROCESS_INFORMATION
						);
		}

		// Check result
		if (bResult) {
			m_hProcess = (handle)piProcInfo.hProcess;
			CloseHandle(piProcInfo.hThread);
		}

		// Connect pipes to files
		m_cFileInput .Assign(m_cPipeInput .GetWriteHandle());
		m_cFileOutput.Assign(m_cPipeOutput.GetReadHandle());
		m_cFileError .Assign(m_cPipeError .GetReadHandle());

		// Return result
		return (bResult != 0);
	#endif

	// Linux implementation
	#ifdef LINUX
		// Create process
		m_hProcess = fork();
		if (m_hProcess == 0) {	// Child process
			dup2(hPipeInRd, 0);		// stdin
			dup2(hPipeOutWr, 1);	// stdout
			dup2(hPipeErrWr, 2);	// stderr
			if (hPipeInWr  != INVALID_HANDLE) close(hPipeInWr);
			if (hPipeOutRd != INVALID_HANDLE) close(hPipeOutRd);
			if (hPipeErrRd != INVALID_HANDLE) close(hPipeErrRd);

			// Get arguments
			List<String> lstArgs;
			lstArgs.Add(sCommand);
			Tokenizer tokenizer;
			tokenizer.SetSingleChars("");
			tokenizer.SetSingleLineComment("");
			tokenizer.Start(sArguments);
			String sToken = tokenizer.GetNextToken();
			while (sToken.GetLength()) {
				lstArgs.Add(sToken);
				sToken = tokenizer.GetNextToken();
			}

			// Make array for arguments
			int nSize = lstArgs.GetNumOfElements();
			if (nSize > 0) {
				char **ppszParams = new char*[nSize+1];
				for (int i=0; i<nSize; i++) {
					ppszParams[i] = (char*)lstArgs[i].GetASCII();
				}
				ppszParams[nSize] = NULL;

				// Execute application
				execv(lstArgs[0].GetASCII(), ppszParams);
			}
		} else if (m_hProcess > 0) { //	Parent process
			// Connect pipes to files
			m_cFileInput .Assign(m_cPipeInput .GetWriteHandle());
			m_cFileOutput.Assign(m_cPipeOutput.GetReadHandle());
			m_cFileError .Assign(m_cPipeError .GetReadHandle());
		} else {
			// Error
		}
	#endif
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
