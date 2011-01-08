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
#include "PLDatabaseNull/DatabaseQuery.h"
#include "PLDatabaseNull/Database.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDatabaseNull {


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
	m_bConnected(false)
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


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Database::Database(const Database &cSource)
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
	static const String sString = "1.0";
	return sString;
}

bool Database::Connect(const String &sServer, const String &sUserName, const String &sUserPassword, const String &sDatabase)
{
	// Already connected?
	if (!m_bConnected) {
		// Done, congratulations, we are now 'connected'! *g*
		m_bConnected = true;
		return true;
	}

	// Error!
	return false;
}

bool Database::IsConnected() const
{
	return m_bConnected;
}

bool Database::IsConnectionActive() const
{
	// There's no special 'connection active' check within this implementation...
	return m_bConnected;
}

bool Database::Disconnect()
{
	if (m_bConnected) {
		m_bConnected = false;

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
} // PLDatabaseNull
