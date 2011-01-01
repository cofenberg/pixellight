/*********************************************************\
 *  File: DatabaseQueryResult.cpp                        *
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
#include "PLDatabasePostgreSQL/DatabaseQueryResult.h"


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
DatabaseQueryResult::~DatabaseQueryResult()
{
	PQclear(m_pPostgreSQLResult);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DatabaseQueryResult::DatabaseQueryResult(PLDatabase::DatabaseQuery &cParentQuery, PGresult &cPostgreSQLResult) :
	PLDatabase::DatabaseQueryResult(cParentQuery),
	m_pPostgreSQLResult(&cPostgreSQLResult),
	m_nCurrentRow(0)
{
}

/**
*  @brief
*    Copy constructor
*/
DatabaseQueryResult::DatabaseQueryResult(const DatabaseQueryResult &cSource) :
	PLDatabase::DatabaseQueryResult(cSource.GetQuery()),
	m_pPostgreSQLResult(NULL),
	m_nCurrentRow(0)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
DatabaseQueryResult &DatabaseQueryResult::operator =(const DatabaseQueryResult &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual PLDatabase::DatabaseQueryResult functions ]
//[-------------------------------------------------------]
bool DatabaseQueryResult::IsEmpty() const
{
	return !PQntuples(m_pPostgreSQLResult);
}

void DatabaseQueryResult::FirstRow()
{
	m_nCurrentRow = 0;
}

const Array<String> &DatabaseQueryResult::FetchFieldList()
{
	// Are there any fields within the current list?
	if (!m_lstFields.GetNumOfElements()) {
		uint32 nNumOfFields = PQnfields(m_pPostgreSQLResult);
		for (uint32 i=0; i<nNumOfFields; i++)
			m_lstFields.Add(PQfname(m_pPostgreSQLResult, i));
	}

	// Return a reference to the fields list
	return m_lstFields;
}

const HashMap<String, String> *DatabaseQueryResult::FetchRow()
{
	uint32 nRow = PQntuples(m_pPostgreSQLResult);
	if (m_nCurrentRow >= nRow) return NULL; // Error!
	uint32 nColumn = PQnfields(m_pPostgreSQLResult);

	m_mapRow.Clear();
	for (uint32 i=0; i<nColumn; i++)
		m_mapRow.Add(PQfname(m_pPostgreSQLResult, i), PQgetvalue(m_pPostgreSQLResult, m_nCurrentRow, i));
	m_nCurrentRow++;

	// Return a pointer to the row map
	return &m_mapRow;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabasePostgreSQL
