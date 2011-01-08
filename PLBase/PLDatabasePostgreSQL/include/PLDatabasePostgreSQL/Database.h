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


#ifndef __PLDATABASEPOSTGRESQL_DATABASE_H__
#define __PLDATABASEPOSTGRESQL_DATABASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLDatabase/Database.h>
#include "PLDatabasePostgreSQL/PLDatabasePostgreSQL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
typedef struct pg_conn PGconn;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDatabasePostgreSQL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PostgreSQL 8.1.4 (http://www.postgresql.org/) database implementation
*
*  @note
*    - The following parameters of the Connect()-function are used: sServer, sUserName, sUserPassword, sDatabase
*/
class Database : public PLDatabase::Database {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLDATABASEPOSTGRESQL_RTTI_EXPORT, Database, "PLDatabasePostgreSQL", PLDatabase::Database, "PostgreSQL 8.1.4 (http://www.postgresql.org/) database implementation")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLDATABASEPOSTGRESQL_API Database();

		/**
		*  @brief
		*    Destructor
		*/
		PLDATABASEPOSTGRESQL_API virtual ~Database();

		/**
		*  @brief
		*    Returns the PostgreSQL socket object
		*
		*  @return
		*    The PostgreSQL socket object, can be a null pointer
		*/
		PLDATABASEPOSTGRESQL_API PGconn *GetPostgreSQL() const;


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


	//[-------------------------------------------------------]
	//[ Public virtual PLDatabase::Database functions         ]
	//[-------------------------------------------------------]
	public:
		PLDATABASEPOSTGRESQL_API virtual PLGeneral::String GetVersion() const;
		PLDATABASEPOSTGRESQL_API virtual bool Connect(const PLGeneral::String &sServer, const PLGeneral::String &sUserName,
													  const PLGeneral::String &sUserPassword, const PLGeneral::String &sDatabase);
		PLDATABASEPOSTGRESQL_API virtual bool IsConnected() const;
		PLDATABASEPOSTGRESQL_API virtual bool IsConnectionActive() const;
		PLDATABASEPOSTGRESQL_API virtual bool Disconnect();
		PLDATABASEPOSTGRESQL_API virtual PLDatabase::DatabaseQuery *CreateQuery() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PGconn *m_pPostgreSQL;	/**< PostgreSQL socket object, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabasePostgreSQL


#endif // __PLDATABASEPOSTGRESQL_DATABASE_H__
