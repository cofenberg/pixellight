/*********************************************************\
 *  File: TestManager.cpp                                *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdio.h>
#include <string.h>
#include "PLTest/TestCase.h"
#include "PLTest/TestManager.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TestManager::TestManager(const char *pszName) :
	m_nSucceededTestCases(0),
	m_nFailedTestCases(0),
	m_nSucceededTasks(0),
	m_nFailedTasks(0)
{
	// Set the name of the test manager
	if (pszName) {
		m_pszName = new char[strlen(pszName) + 1];
		strcpy(m_pszName, pszName);
	} else m_pszName = nullptr;

	// Log test start
	printf("************************************************************\n");
	printf("Starting test manager: %s\n", GetName() ? GetName() : "");
	printf("************************************************************\n");
	printf("\n");
}

/**
*  @brief
*    Destructor
*/
TestManager::~TestManager()
{
	// Log test end
	printf("\n");
	printf("************************************************************\n");
	printf("%u test cases: %u success, %u failed\n", m_nSucceededTestCases + m_nFailedTestCases, m_nSucceededTestCases, m_nFailedTestCases);
	printf("%u tasks: %u success, %u failed\n", m_nSucceededTasks + m_nFailedTasks, m_nSucceededTasks, m_nFailedTasks);
	printf("Test manager %s\n", !m_nFailedTestCases ? "SUCCESS!" : "FAILED.");
	printf("************************************************************\n");
	printf("\n");

	// Destroy the name of the test manager
	if (m_pszName) delete [] m_pszName;
}

/**
*  @brief
*    Returns the name of the test manager
*/
const char *TestManager::GetName() const
{
	return m_pszName;
}

/**
*  @brief
*    Performs a test
*/
bool TestManager::Perform(TestCase *pTestCase)
{
	// Check the test case
	if (!pTestCase) {
		m_nFailedTestCases++;

		// Error!
		return false;
	}

	// Perform the test case
	bool bResult = pTestCase->Perform();
	if (bResult) m_nSucceededTestCases++;
	else		 m_nFailedTestCases++;
	m_nSucceededTasks += pTestCase->GetSucceededTasks();
	m_nFailedTasks    += pTestCase->GetFailedTasks();

	// Destroy the the test case now
	delete pTestCase;

	// Done
	return bResult;
}

/**
*  @brief
*    Returns the number of succeeded test cases
*/
uint32 TestManager::GetSucceededTestCases() const
{
	return m_nSucceededTestCases;
}

/**
*  @brief
*    Returns the number of failed test cases
*/
uint32 TestManager::GetFailedTestCases() const
{
	return m_nFailedTestCases;
}

/**
*  @brief
*    Returns the number of test cases
*/
uint32 TestManager::GetTestCases() const
{
	return m_nSucceededTestCases + m_nFailedTestCases;
}

/**
*  @brief
*    Returns the number of succeeded tasks
*/
uint32 TestManager::GetSucceededTasks() const
{
	return m_nSucceededTasks;
}

/**
*  @brief
*    Returns the number of failed tasks
*/
uint32 TestManager::GetFailedTasks() const
{
	return m_nFailedTasks;
}

/**
*  @brief
*    Returns the number of tasks
*/
uint32 TestManager::GetTasks() const
{
	return m_nSucceededTasks + m_nFailedTasks;
}
