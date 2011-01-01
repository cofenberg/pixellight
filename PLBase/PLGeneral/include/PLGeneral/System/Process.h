/*********************************************************\
 *  File: Process.h                                      *
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


#ifndef __PLGENERAL_PROCESS_H__
#define __PLGENERAL_PROCESS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/System/Pipe.h"
#include "PLGeneral/File/File.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class for running and controlling an external process
*/
class Process {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API Process();

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~Process();

		/**
		*  @brief
		*    Starts a process
		*
		*  @param[in] sCommand
		*    Command to run
		*  @param[in] sArguments
		*    Arguments for the command
		*/
		PLGENERAL_API void Execute(const String &sCommand, const String &sArguments);

		/**
		*  @brief
		*    Starts a process with redirected input/output
		*
		*  @param[in] sCommand
		*    Command to run
		*  @param[in] sArguments
		*    Arguments for the command
		*
		*  @remarks
		*    This function creates unnamed pipes to redirect input and output. To access
		*    theses pipes, use the appropriate functions like GetInput(), GetOutput() a.s.o.
		*    If you want to specifiy the pipes by yourself, see the other two variations of
		*    ExecuteRedirectIO().
		*/
		PLGENERAL_API void ExecuteRedirectIO(const String &sCommand, const String &sArguments);

		/**
		*  @brief
		*    Starts a process with redirected input/output
		*
		*  @param[in] sCommand
		*    Command to run
		*  @param[in] sArguments
		*    Arguments for the command
		*  @param[in] cPipeIn
		*    Pipe for input
		*  @param[in] cPipeOut
		*    Pipe for output
		*  @param[in] cPipeErr
		*    Pipe for error
		*/
		PLGENERAL_API void ExecuteRedirectIO(const String &sCommand, const String &sArguments,
											 const Pipe &cPipeIn, const Pipe &cPipeOut, const Pipe &cPipeErr);

		/**
		*  @brief
		*    Starts a process with redirected input/output
		*
		*  @param[in] sCommand
		*    Command to run
		*  @param[in] sArguments
		*    Arguments for the command
		*  @param[in] hPipeIn
		*    System handle for the input pipe
		*  @param[in] hPipeOut
		*    System handle for the output pipe
		*  @param[in] hPipeErr
		*    System handle for the error pipe
		*
		*  @note
		*    - On Linux, the handle is a file handle of type int
		*    - On Windows, the handle is a file handle of type HANDLE
		*/
		PLGENERAL_API void ExecuteRedirectIO(const String &sCommand, const String &sArguments,
											 handle hPipeIn, handle hPipeOut, handle hPipeErr);

		/**
		*  @brief
		*    Returns if the process is running
		*
		*  @return
		*    'true' if running, else 'false'
		*/
		PLGENERAL_API bool IsRunning() const;

		/**
		*  @brief
		*    Terminates the process
		*/
		PLGENERAL_API void Terminate();

		/**
		*  @brief
		*    Get input stream
		*
		*  @return
		*    Input file for the process
		*/
		PLGENERAL_API File &GetInput() const;

		/**
		*  @brief
		*    Get output stream
		*
		*  @return
		*    Output file for the process
		*/
		PLGENERAL_API File &GetOutput() const;

		/**
		*  @brief
		*    Get error stream
		*
		*  @return
		*    Error file for the process
		*/
		PLGENERAL_API File &GetError() const;

		/**
		*  @brief
		*    Get input pipe
		*
		*  @return
		*    Input pipe for the process
		*/
		PLGENERAL_API const Pipe &GetPipeInput() const;

		/**
		*  @brief
		*    Get output pipe
		*
		*  @return
		*    Output pipe for the process
		*/
		PLGENERAL_API const Pipe &GetPipeOutput() const;

		/**
		*  @brief
		*    Get error pipe
		*
		*  @return
		*    Error pipe for the process
		*/
		PLGENERAL_API const Pipe &GetPipeError() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Process(const Process &cSource);

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
		Process &operator =(const Process &cSource);

		/**
		*  @brief
		*    Creates a process with redirected IO
		*
		*  @param[in] sCommand
		*    Command to run
		*  @param[in] sArguments
		*    Arguments for the command
		*  @param[in] hPipeInRd
		*    System handle for the input pipe (read-end)
		*  @param[in] hPipeInWr
		*    System handle for the input pipe (write-end)
		*  @param[in] hPipeOutRd
		*    System handle for the output pipe (read-end)
		*  @param[in] hPipeOutWr
		*    System handle for the output pipe (write-end)
		*  @param[in] hPipeErrRd
		*    System handle for the error pipe (read-end)
		*  @param[in] hPipeErrWr
		*    System handle for the error pipe (write-end)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool CreateProcessRedirectIO(const String &sCommand, const String &sArguments,
									 handle hPipeInRd,  handle hPipeInWr,
									 handle hPipeOutRd, handle hPipeOutWr,
									 handle hPipeErrRd, handle hPipeErrWr);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Input/output redirection
		Pipe m_cPipeInput;		/**< Pipe 'Input' */
		Pipe m_cPipeOutput;		/**< Pipe 'Output' */
		Pipe m_cPipeError;		/**< Pipe 'Error' */
		File m_cFileInput;		/**< File 'Input' */
		File m_cFileOutput;		/**< File 'Output' */
		File m_cFileError;		/**< File 'Error' */

		// System dependent process handle
		#if defined(LINUX)
			int m_hProcess;
		#elif defined(WIN32)
			handle m_hProcess;
		#endif


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_PROCESS_H__
