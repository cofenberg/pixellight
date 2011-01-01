/*********************************************************\
 *  File: TestCase.cpp                                   *
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
#include <stdio.h>
#include <stdarg.h>
#ifdef LINUX
	// Under Linux, we need this for '_vscprintf' :(
	#include <PLGeneral/PLGeneralLinuxWrapper.h>
#endif
#include "PLTest/TestCase.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestCase::TestCase() :
	m_nSucceeded(0),
	m_nFailed(0),
	m_bInTask(false)
{
}

/**
*  @brief
*    Destructor
*/
TestCase::~TestCase()
{
}

/**
*  @brief
*    Perform the test
*/
bool TestCase::Perform()
{
	// Start test
	m_nSucceeded = 0;
	m_nFailed    = 0;

	// Log test start
	printf("------------------------------------------------------------\n");
	printf("Starting Test: %s\n", GetName() ? GetName() : "");
	printf("------------------------------------------------------------\n");

	// Perform the test
	Test();

	// Log test end
	printf("------------------------------------------------------------\n");
	printf("%d tests: %d success, %d failed\n", m_nSucceeded + m_nFailed, m_nSucceeded, m_nFailed);
	printf("Test %s\n", !m_nFailed ? "SUCCESS!" : "FAILED.");
	printf("------------------------------------------------------------\n");
	printf("\n");

	// Done
	return !m_nFailed;
}

/**
*  @brief
*    Returns whether the test has succeeded or not
*/
bool TestCase::GetTestSuccess() const
{
	return !m_nFailed;
}

/**
*  @brief
*    Returns the number of succeeded tasks
*/
uint32 TestCase::GetSucceededTasks() const
{
	return m_nSucceeded;
}

/**
*  @brief
*    Returns the number of failed tasks
*/
uint32 TestCase::GetFailedTasks() const
{
	return m_nFailed;
}

/**
*  @brief
*    Returns the number of tasks
*/
uint32 TestCase::GetTasks() const
{
	return m_nSucceeded + m_nFailed;
}

/**
*  @brief
*    Prints a text
*/
uint32 TestCase::Print(const char *pszText, ...) const
{
	// Check parameter
	if (!pszText) return 0;

	// Start parameter list
	va_list vaList;
	va_start(vaList, pszText);

	// Get the required buffer length
	int nLength = _vscprintf(pszText, vaList);
	if (nLength > 0) {
		// Allocate memory
		uint32  nBufferSize = nLength + 1;
		char   *pszBuffer   = new char[nBufferSize];
		if (pszBuffer) {
			// Print the formatted string
			vsprintf(pszBuffer, pszText, vaList);
			puts(pszBuffer);

			// Cleanup
			delete [] pszBuffer;
		}
	}

	// End parameter list
	va_end(vaList);

	// Done
	return nLength;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Starts a new task
*/
bool TestCase::StartTask(const char *pszName)
{
	// Currently within a task?
	if (m_bInTask) return false; // Error!

	// Log task
	printf("- %s: ", pszName);
	m_bInTask = true;

	// Done
	return true;
}

/**
*  @brief
*    Currently within a task?
*/
bool TestCase::InTask() const
{
	return m_bInTask;
}

/**
*  @brief
*    Ends the task
*/
bool TestCase::EndTask(bool bSuccess)
{
	// Currently within a task?
	if (!m_bInTask) return false; // Error!

	// End task
	if (bSuccess) m_nSucceeded++;
	else		  m_nFailed++;

	// Log end of task
	printf("%s\n", bSuccess ? "ok" : "failed");
	m_bInTask = false;

	// Done
	return true;
}
