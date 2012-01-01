/*********************************************************\
 *  File: Process.inl                                    *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline Process::Process() :
	m_hProcess(NULL_HANDLE)
{
}

/**
*  @brief
*    Get input stream
*/
inline File &Process::GetInput()
{
	// Open file if not already done
	if (!m_cFileInput.IsOpen())
		m_cFileInput.Open(File::FileWrite | File::FileText);

	// Return file
	return m_cFileInput;
}

/**
*  @brief
*    Get output stream
*/
inline File &Process::GetOutput()
{
	// Open file if not already done
	if (!m_cFileOutput.IsOpen())
		m_cFileOutput.Open(File::FileRead | File::FileText);

	// Return file
	return m_cFileOutput;
}

/**
*  @brief
*    Get error stream
*/
inline File &Process::GetError()
{
	// Open file if not already done
	if (!m_cFileError.IsOpen())
		m_cFileError.Open(File::FileRead | File::FileText);

	// Return file
	return m_cFileError;
}

/**
*  @brief
*    Get input pipe
*/
inline const Pipe &Process::GetPipeInput() const
{
	// Return pipe
	return m_cPipeInput;
}

/**
*  @brief
*    Get output pipe
*/
inline const Pipe &Process::GetPipeOutput() const
{
	// Return pipe
	return m_cPipeOutput;
}

/**
*  @brief
*    Get error pipe
*/
inline const Pipe &Process::GetPipeError() const
{
	// Return pipe
	return m_cPipeError;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
