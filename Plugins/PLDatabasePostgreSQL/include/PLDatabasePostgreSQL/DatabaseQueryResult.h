/*********************************************************\
 *  File: DatabaseQueryResult.h                          *
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
