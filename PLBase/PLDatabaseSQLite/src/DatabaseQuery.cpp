/*********************************************************\
 *  File: DatabaseQuery.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <SQLite/sqlite3.h>
#include <PLGeneral/Log/Log.h>
#include "PLDatabaseSQLite/Database.h"
#include "PLDatabaseSQLite/DatabaseQueryResult.h"
#include "PLDatabaseSQLite/DatabaseQuery.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDatabaseSQLite {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
DatabaseQuery::~DatabaseQuery()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DatabaseQuery::DatabaseQuery(PLDatabase::Database &cParentDd) : PLDatabase::DatabaseQuery(cParentDd)
{
}

/**
*  @brief
*    Copy constructor
*/
DatabaseQuery::DatabaseQuery(const DatabaseQuery &cSource) : PLDatabase::DatabaseQuery(cSource.GetDatabase())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
DatabaseQuery &DatabaseQuery::operator =(const DatabaseQuery &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual PLDatabase::DatabaseQuery functions    ]
//[-------------------------------------------------------]
PLDatabase::DatabaseQueryResult *DatabaseQuery::Execute(const String &sSQL)
{
	sqlite3 *pSQLite = ((Database&)GetDatabase()).GetSQLite();
	DatabaseQueryResult *pQueryResult = new DatabaseQueryResult(*this);
	int nError = sqlite3_get_table(pSQLite,
								   sSQL,
								   &pQueryResult->m_ppszResult,
								   &pQueryResult->m_nRow,
								   &pQueryResult->m_nColumn,
								   NULL);
	if (nError == SQLITE_OK && pQueryResult->m_ppszResult) {
		// 'SELECT'-SQL?
		if (IsSelect(sSQL)) return pQueryResult; // Return the query result
	} else PL_LOG(Error, String("SQLite can't execute the given SQL statement! Error: ") + sqlite3_errmsg(pSQLite))

	// Destroy the query result
	delete pQueryResult;

	// Error!
	return NULL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabaseSQLite
