/*********************************************************\
 *  File: DatabaseQueryResult.cpp                        *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <sqlite3.h>
#include "PLDatabaseSQLite/DatabaseQueryResult.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
