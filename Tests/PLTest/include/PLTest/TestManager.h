/*********************************************************\
 *  File: TestManager.h                                  *
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


#ifndef __PLTEST_TESTMANAGER_H__
#define __PLTEST_TESTMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLTest/PLTest.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class TestCase;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Test manager class for function tests
*/
class TestManager {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pszName
		*    Name of the test manager
		*/
		PLTEST_API TestManager(const char *pszName);

		/**
		*  @brief
		*    Destructor
		*/
		PLTEST_API virtual ~TestManager();

		/**
		*  @brief
		*    Returns the name of the test manager
		*
		*  @return
		*    Name of the test manager, a null pointer on error
		*/
		PLTEST_API const char *GetName() const;

		/**
		*  @brief
		*    Performs a test
		*
		*  @param[in] pTestCase
		*    Test case to perform, the manager will destroy this test automatically 
		*    after it was performed
		*
		*  @return
		*    'true' if the test has succeeded, else 'false'
		*/
		PLTEST_API bool Perform(TestCase *pTestCase);

		/**
		*  @brief
		*    Returns the number of succeeded test cases
		*
		*  @return
		*    The number of succeeded test cases
		*/
		PLTEST_API PLCore::uint32 GetSucceededTestCases() const;

		/**
		*  @brief
		*    Returns the number of failed test cases
		*
		*  @return
		*    The number of failed test cases
		*/
		PLTEST_API PLCore::uint32 GetFailedTestCases() const;

		/**
		*  @brief
		*    Returns the number of test cases
		*
		*  @return
		*    The number of test test cases
		*/
		PLTEST_API PLCore::uint32 GetTestCases() const;

		/**
		*  @brief
		*    Returns the number of succeeded tasks
		*
		*  @return
		*    The number of succeeded tasks
		*/
		PLTEST_API PLCore::uint32 GetSucceededTasks() const;

		/**
		*  @brief
		*    Returns the number of failed tasks
		*
		*  @return
		*    The number of failed tasks
		*/
		PLTEST_API PLCore::uint32 GetFailedTasks() const;

		/**
		*  @brief
		*    Returns the number of tasks
		*
		*  @return
		*    The number of tasks
		*/
		PLTEST_API PLCore::uint32 GetTasks() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		char		   *m_pszName;				/**< Name of the test manager */
		PLCore::uint32  m_nSucceededTestCases;	/**< Number of succeeded test cases */
		PLCore::uint32  m_nFailedTestCases;		/**< Number of failed test cases */
		PLCore::uint32  m_nSucceededTasks;		/**< Number of succeeded tasks */
		PLCore::uint32  m_nFailedTasks;			/**< Number of failed tasks */


};


#endif // __PLTEST_TESTMANAGER_H__
