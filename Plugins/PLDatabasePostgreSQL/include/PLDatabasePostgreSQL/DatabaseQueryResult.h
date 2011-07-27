/*********************************************************\
 *  File: DatabaseQueryResult.h                          *
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


#ifndef __PLDATABASEPOSTGRESQL_DATABASEQUERYRESULT_H__
#define __PLDATABASEPOSTGRESQL_DATABASEQUERYRESULT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLDatabase/DatabaseQueryResult.h>
#include "PLDatabasePostgreSQL/PLDatabasePostgreSQL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDatabasePostgreSQL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Database query result PostgreSQL implementation
*/
class DatabaseQueryResult : public PLDatabase::DatabaseQueryResult {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DatabaseQuery;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLDATABASEPOSTGRESQL_API virtual ~DatabaseQueryResult();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cParentQuery
		*    Database query this database query result is in
		*  @param[in] cPostgreSQLResult
		*    PostgreSQL database query result
		*/
		DatabaseQueryResult(PLDatabase::DatabaseQuery &cParentQuery, PGresult &cPostgreSQLResult);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		DatabaseQueryResult(const DatabaseQueryResult &cSource);

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
		DatabaseQueryResult &operator =(const DatabaseQueryResult &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PGresult	   *m_pPostgreSQLResult;	/**< PostgreSQL database query result (always valid!) */
		PLCore::uint32  m_nCurrentRow;			/**< Current row */


	//[-------------------------------------------------------]
	//[ Public virtual PLDatabase::DatabaseQueryResult functions ]
	//[-------------------------------------------------------]
	public:
		PLDATABASEPOSTGRESQL_API virtual bool IsEmpty() const override;
		PLDATABASEPOSTGRESQL_API virtual void FirstRow() override;
		PLDATABASEPOSTGRESQL_API virtual const PLCore::Array<PLCore::String> &FetchFieldList() override;
		PLDATABASEPOSTGRESQL_API virtual const PLCore::HashMap<PLCore::String, PLCore::String> *FetchRow() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabasePostgreSQL


#endif // __PLDATABASEPOSTGRESQL_DATABASEQUERYRESULT_H__
