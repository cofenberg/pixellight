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
#include "PLDatabaseNull/DatabaseQueryResult.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLDatabaseNull {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
DatabaseQueryResult::~DatabaseQueryResult()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DatabaseQueryResult::DatabaseQueryResult(PLDatabase::DatabaseQuery &cParentQuery) : PLDatabase::DatabaseQueryResult(cParentQuery)
{
}

/**
*  @brief
*    Copy constructor
*/
DatabaseQueryResult::DatabaseQueryResult(const DatabaseQueryResult &cSource) : PLDatabase::DatabaseQueryResult(cSource.GetQuery())
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
}

bool DatabaseQueryResult::IncRow()
{
	return true;
}

bool DatabaseQueryResult::EndOfRow() const
{
	return true;
}

const char *DatabaseQueryResult::GetCurrentValue(uint32 nColumn) const
{
	return nullptr;
}

const char *DatabaseQueryResult::GetFieldName(uint32 nColumn) const
{
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public virtual PLDatabase::DatabaseQueryResult functions ]
//[-------------------------------------------------------]
bool DatabaseQueryResult::IsEmpty() const
{
	return true;
}

void DatabaseQueryResult::FirstRow()
{
	Reset();
}

const Array<String> &DatabaseQueryResult::FetchFieldList()
{
	// Return a reference to the fields list
	return m_lstFields;
}

const HashMap<String, String> *DatabaseQueryResult::FetchRow()
{
	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabaseNull
