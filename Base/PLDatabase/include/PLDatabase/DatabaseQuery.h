/*********************************************************\
 *  File: DatabaseQuery.h                                *
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


#ifndef __PLDATABASE_DATABASEQUERY_H__
#define __PLDATABASE_DATABASEQUERY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLDatabase/PLDatabase.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class String;
}
namespace PLDatabase {
	class Database;
	class DatabaseQueryResult;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDatabase {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract database query base class
*/
class DatabaseQuery {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether the given SQL statement is a SELECT
		*
		*  @param[in] sSQL
		*    SQL statement to check
		*
		*  @return
		*    'true' if the given SQL statement is a SELECT one, else 'false'
		*/
		PLDATABASE_API static bool IsSelect(const PLCore::String &sSQL);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLDATABASE_API virtual ~DatabaseQuery();

		/**
		*  @brief
		*    Returns the database this query is in
		*
		*  @return
		*    The database this query is in
		*/
		PLDATABASE_API Database &GetDatabase() const;


	//[-------------------------------------------------------]
	//[ Public virtual DatabaseQuery functions                ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Executes a given SQL statement
		*
		*  @param[in] sSQL
		*    SQL statement to execute
		*
		*  @return
		*    A pointer to a newly created query result you have to delete by own or a null pointer
		*    if the SQL statement is not a select (ie: INSERT, UPDATE, etc.)
		*/
		virtual DatabaseQueryResult *Execute(const PLCore::String &sSQL) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cParentDd
		*    Database this query is in
		*/
		PLDATABASE_API DatabaseQuery(Database &cParentDd);


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
		DatabaseQuery(const DatabaseQuery &cSource);

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
		DatabaseQuery &operator =(const DatabaseQuery &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Database *m_pParentDb;	/**< Database this query is in (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabase


#endif // __PLDATABASE_DATABASEQUERY_H__
