/*********************************************************\
 *  File: Database.h                                     *
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


#ifndef __PLDATABASE_DATABASE_H__
#define __PLDATABASE_DATABASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLDatabase/PLDatabase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDatabase {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class DatabaseQuery;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract SQL (Structured Query Language) database base class
*/
class Database : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLDATABASE_RTTI_EXPORT, Database, "PLDatabase", PLCore::Object, "Abstract SQL (Structured Query Language) database base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates a database instance
		*
		*  @param[in] sClass
		*    Class name of the database implementation
		*
		*  @return
		*    The database instance, a null pointer on error
		*/
		PLDATABASE_API static Database *Create(const PLCore::String &sClass);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLDATABASE_API virtual ~Database();

		/**
		*  @brief
		*    Returns the version of the database implementation
		*
		*  @return
		*    The version of the database implementation
		*/
		virtual PLCore::String GetVersion() const = 0;

		/**
		*  @brief
		*    Connect to a database
		*
		*  @param[in] sServer
		*    Server name, can be a hostname (for instance 'localhost') or a IP-address
		*  @param[in] sUserName
		*    User name
		*  @param[in] sUserPassword
		*    User password
		*  @param[in] sDatabase
		*    Database
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Connect(const PLCore::String &sServer, const PLCore::String &sUserName, const PLCore::String &sUserPassword, const PLCore::String &sDatabase) = 0;

		/**
		*  @brief
		*    Returns whether there's an active database connection or not
		*
		*  @return
		*    'true' if there's an active database connection, else 'false'
		*/
		virtual bool IsConnected() const = 0;

		/**
		*  @brief
		*    Returns whether the connection to the database is still active or not
		*
		*  @return
		*    'true' the connection to the database is still active, else 'false'
		*
		*  @remarks
		*    Checks whether the server connection is still active. If the connection has broken, normally
		*    an automatic reconnection is attempted. If you as client idle for a long tíme, you can use this
		*    function to check whether the server has closed the connection and reconnect if necessary.
		*/
		virtual bool IsConnectionActive() const = 0;

		/**
		*  @brief
		*    Disconnect from the database
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's no connection to disconnect?)
		*/
		virtual bool Disconnect() = 0;

		/**
		*  @brief
		*    Creates a database query
		*
		*  @return
		*    The database query, a null pointer on error
		*/
		virtual DatabaseQuery *CreateQuery() = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLDATABASE_API Database();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Database(const Database &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Database &operator =(const Database &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabase


#endif // __PLDATABASE_DATABASE_H__
