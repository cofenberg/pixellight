/*********************************************************\
 *  File: Database.cpp                                   *
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
#include "PLDatabaseSQLite/DatabaseQuery.h"
#include "PLDatabaseSQLite/Database.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDatabaseSQLite {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Database)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Database::Database() :
	m_pSQLite(NULL)
{
}

/**
*  @brief
*    Destructor
*/
Database::~Database()
{
	Disconnect();
}

/**
*  @brief
*    Returns the SQLite socket object
*/
sqlite3 *Database::GetSQLite() const
{
	return m_pSQLite;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Database::Database(const Database &cSource) :
	m_pSQLite(NULL)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Database &Database::operator =(const Database &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Public virtual PLDatabase::Database functions         ]
//[-------------------------------------------------------]
String Database::GetVersion() const
{
	static const String sString = SQLITE_VERSION;
	return sString;
}

bool Database::Connect(const String &sServer, const String &sUserName,
					   const String &sUserPassword, const String &sDatabase)
{
	// Already connected?
	if (!m_pSQLite) {
		// Try to connect to our SQLite server
		if (sqlite3_open(sDatabase, &m_pSQLite) == SQLITE_OK)
			return true; // Done
		else PL_LOG(Error, String("SQLite could not connect to specified server! Error: ") + sqlite3_errmsg(m_pSQLite))
	}

	// Error!
	return false;
}

bool Database::IsConnected() const
{
	return (m_pSQLite != NULL);
}

bool Database::IsConnectionActive() const
{
	// There's no special 'connection active' check within SQLite...
	return (m_pSQLite != NULL);
}

bool Database::Disconnect()
{
	if (m_pSQLite) {
		sqlite3_close(m_pSQLite);
		m_pSQLite = NULL;

		// Done
		return true;
	} else return false; // Error!
}

PLDatabase::DatabaseQuery *Database::CreateQuery() const
{
	return new DatabaseQuery(*(PLDatabase::Database*)this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabaseSQLite
