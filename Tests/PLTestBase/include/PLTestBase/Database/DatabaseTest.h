/*********************************************************\
 *  File: DatabaseTest.h                                 *
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


#ifndef __PLTESTBASE_DATABASE_DATABASETEST_H__
#define __PLTESTBASE_DATABASE_DATABASETEST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLTest/TestCase.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class String;
}
namespace PLDatabase {
	class Database;
	class DatabaseQueryResult;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract database base class for function tests
*/
class DatabaseTest : public TestCase {


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Tests an database implementation
		*
		*  @param[in] sClass
		*    Database implementation class name
		*  @param[in] sServer
		*    Server name, can be a hostname (for instance 'localhost') or a IP-address
		*  @param[in] sUserName
		*    User name
		*  @param[in] sUserPassword
		*    User password
		*  @param[in] sDatabase
		*    Database
		*/
		void TestImplementation(const PLCore::String &sClass, const PLCore::String &sServer, const PLCore::String &sUserName, const PLCore::String &sUserPassword, const PLCore::String &sDatabase);

		/**
		*  @brief
		*    Prints field names in query result
		*
		*  @param[in] pQResult
		*    Database query result to print
		*/
		void PrintFields(PLDatabase::DatabaseQueryResult *pQResult);

		/**
		*  @brief
		*    Prints rows in query result
		*
		*  @param[in] pQResult
		*    Database query result to print
		*/
		void PrintRows(PLDatabase::DatabaseQueryResult *pQResult);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Tests a database query implementation
		*
		*  @param[in] pDatabase
		*    Database to use, NEVER a null pointer!
		*/
		void TestQuery(PLDatabase::Database *pDatabase);


};


#endif // __PLTESTBASE_DATABASE_DATABASETEST_H__
