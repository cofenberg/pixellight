/*********************************************************\
 *  File: TestCase.h                                     *
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


#ifndef __PLTEST_TESTCASE_H__
#define __PLTEST_TESTCASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include "PLTest/PLTest.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract base class for function tests
*/
class TestCase {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLTEST_API TestCase();

		/**
		*  @brief
		*    Destructor
		*/
		PLTEST_API virtual ~TestCase();

		/**
		*  @brief
		*    Perform the test
		*
		*  @return
		*    'true' if the test has succeeded, else 'false'
		*/
		PLTEST_API bool Perform();

		/**
		*  @brief
		*    Returns whether the test has succeeded or not
		*
		*  @return
		*    'true' if the test has succeeded, else 'false'
		*/
		PLTEST_API bool GetTestSuccess() const;

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

		/**
		*  @brief
		*    Prints a text
		*
		*  @param[in] pszText
		*    Text to print
		*
		*  @return
		*    The number of printed characters
		*/
		PLTEST_API PLCore::uint32 Print(const char *pszText, ...) const;


	//[-------------------------------------------------------]
	//[ Public virtual TestCase functions                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the test
		*
		*  @return
		*    Name of the test, a null pointer on error
		*/
		virtual const char *GetName() const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Starts a new task
		*
		*  @param[in] pszName
		*    Name of the new task
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe we are currently already within a task?)
		*/
		PLTEST_API bool StartTask(const char *pszName);

		/**
		*  @brief
		*    Currently within a task?
		*
		*  @return 
		*    'true' if we are currently within a task, else 'false'
		*/
		PLTEST_API bool InTask() const;

		/**
		*  @brief
		*    Ends the task
		*
		*  @param[in] bSuccess
		*    'true' if the task has succeeded, else 'false'
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe we are currently within no task?)
		*/
		PLTEST_API bool EndTask(bool bSuccess);


	//[-------------------------------------------------------]
	//[ Private virtual TestCase functions                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Perform the test
		*/
		virtual void Test() = 0;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint32 m_nSucceeded;	/**< Number of succeeded tasks */
		PLCore::uint32 m_nFailed;		/**< Number of failed tasks */
		bool		   m_bInTask;		/**< Currently within a task? */


};


#endif // __PLTEST_TESTCASE_H__
