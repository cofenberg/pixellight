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
#include <SQLite/sqlite3.h>
#include "PLDatabaseSQLite/DatabaseQueryResult.h"


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
DatabaseQueryResult::~DatabaseQueryResult()
{
	sqlite3_free_table(m_ppszResult);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DatabaseQueryResult::DatabaseQueryResult(PLDatabase::DatabaseQuery &cParentQuery) : PLDatabase::DatabaseQueryResult(cParentQuery),
	m_nRow(0),
	m_nColumn(0),
	m_ppszResult(nullptr),
	m_nCurrentRow(1)
{
}

/**
*  @brief
*    Copy constructor
*/
DatabaseQueryResult::DatabaseQueryResult(const DatabaseQueryResult &cSource) : PLDatabase::DatabaseQueryResult(cSource.GetQuery()),
	m_nRow(0),
	m_nColumn(0),
	m_ppszResult(nullptr),
	m_nCurrentRow(1)
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

void DatabaseQueryResult::Reset()
{
	m_nCurrentRow = 1;
}

bool DatabaseQueryResult::IncRow()
{
	m_nCurrentRow++;
	return EndOfRow();
}

bool DatabaseQueryResult::EndOfRow() const
{
	return (m_nCurrentRow > m_nRow);
}

const char *DatabaseQueryResult::GetCurrentValue(uint32 nColumn) const
{
	return *(m_ppszResult + m_nCurrentRow*m_nColumn + nColumn);
}

const char *DatabaseQueryResult::GetFieldName(uint32 nColumn) const
{
	return *(m_ppszResult + nColumn);
}


//[-------------------------------------------------------]
//[ Public virtual PLDatabase::DatabaseQueryResult functions ]
//[-------------------------------------------------------]
bool DatabaseQueryResult::IsEmpty() const
{
	return !m_nRow;
}

void DatabaseQueryResult::FirstRow()
{
	Reset();
}

const Array<String> &DatabaseQueryResult::FetchFieldList()
{
	// Are there any fields within the current list?
	if (!m_lstFields.GetNumOfElements()) {
		for (int i=0; i<m_nColumn; i++)
			m_lstFields.Add(*(m_ppszResult + i));
	}

	// Return a reference to the fields list
	return m_lstFields;
}

const HashMap<String, String> *DatabaseQueryResult::FetchRow()
{
	if (EndOfRow())
		return nullptr; // Error!

	m_mapRow.Clear();
	for (int i=0; i<m_nColumn; i++)
		m_mapRow.Add(GetFieldName(i), !GetCurrentValue(i) ? "" : GetCurrentValue(i));
	IncRow();

	// Return a pointer to the row map
	return &m_mapRow;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabaseSQLite
