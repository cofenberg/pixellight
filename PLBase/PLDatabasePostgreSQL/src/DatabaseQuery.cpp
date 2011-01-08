/*********************************************************\
 *  File: DatabaseQuery.cpp                              *
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
#include <PostgreSQL/libpq-fe.h>
#include <PLGeneral/Log/Log.h>
#include "PLDatabasePostgreSQL/Database.h"
#include "PLDatabasePostgreSQL/DatabaseQueryResult.h"
#include "PLDatabasePostgreSQL/DatabaseQuery.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDatabasePostgreSQL {


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
	PGconn   *pPostgreSQL = ((Database&)GetDatabase()).GetPostgreSQL();
	PGresult *pResult     = PQexec(pPostgreSQL, sSQL);
	if (pResult) {
		const int nStatus = PQresultStatus(pResult);
		if (PQresultStatus(pResult) == PGRES_TUPLES_OK) {
			// Return the result
			return new DatabaseQueryResult(*this, *pResult);
		}

		// Get the error message
		String sMessage;
		if (nStatus == PGRES_FATAL_ERROR || nStatus == PGRES_NONFATAL_ERROR)
			sMessage = PQresultErrorMessage(pResult);

		// Cleapup
		PQclear(pResult);

		// Print the error message
		if (sMessage.GetLength())
			PL_LOG(Error, "PostgreSQL can't execute the given SQL statement! Error: " + sMessage)
		else
			PL_LOG(Error, "PostgreSQL can't execute the given SQL statement!")
	} else {
		PL_LOG(Error, String("PostgreSQL can't execute the given SQL statement! Error: ") + PQerrorMessage(pPostgreSQL))
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabasePostgreSQL
