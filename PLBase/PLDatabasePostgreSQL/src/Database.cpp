/*********************************************************\
 *  File: Database.cpp                                   *
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
#include <PostgreSQL/pg_config.h>
#include <PLGeneral/Log/Log.h>
#include "PLDatabasePostgreSQL/DatabaseQuery.h"
#include "PLDatabasePostgreSQL/Database.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDatabasePostgreSQL {


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
	m_pPostgreSQL(nullptr)
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
*    Returns the PostgreSQL socket object
*/
PGconn *Database::GetPostgreSQL() const
{
	return m_pPostgreSQL;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Database::Database(const Database &cSource) :
	m_pPostgreSQL(nullptr)
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
	static const String sString = PACKAGE_STRING;
	return sString;
}

bool Database::Connect(const String &sServer, const String &sUserName, const String &sUserPassword, const String &sDatabase)
{
	const String sFinal = "host=" + sServer + " user=" + sUserName + " password=" + sUserPassword + " dbname=" + sDatabase;
	m_pPostgreSQL = PQconnectdb(sFinal);
	if (m_pPostgreSQL)
		return true; // Done
	else {
		PL_LOG(Error, String("PostgreSQL could not connect to specified server! Error: ") + PQerrorMessage(m_pPostgreSQL))

		// Error!
		return false;
	}
}

bool Database::IsConnected() const
{
	return (m_pPostgreSQL != nullptr);
}

bool Database::IsConnectionActive() const
{
	return (PQstatus(m_pPostgreSQL) == CONNECTION_OK);
}

bool Database::Disconnect()
{
	if (m_pPostgreSQL) {
		PQfinish(m_pPostgreSQL);
		m_pPostgreSQL = nullptr;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

PLDatabase::DatabaseQuery *Database::CreateQuery() const
{
	return new DatabaseQuery(*(PLDatabase::Database*)this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabasePostgreSQL
