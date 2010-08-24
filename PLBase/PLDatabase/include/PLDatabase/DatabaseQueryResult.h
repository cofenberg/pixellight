/*********************************************************\
 *  File: DatabaseQueryResult.h                          *
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


#ifndef __PLDATABASE_DATABASEQUERYRESULT_H__
#define __PLDATABASE_DATABASEQUERYRESULT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/Container/HashMap.h>
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
*    Abstract database query result base class
*/
class DatabaseQueryResult {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLDATABASE_API virtual ~DatabaseQueryResult();

		/**
		*  @brief
		*    Returns the database query this data base query result is in
		*
		*  @return
		*    The database query this data base query result is in
		*/
		PLDATABASE_API DatabaseQuery &GetQuery() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether all query results are processed or not
		*
		*  @return
		*    'true' if all query results are processed, else 'false'
		*/
		virtual bool IsEmpty() const = 0;

		/**
		*  @brief
		*    Resets the query result to the first row
		*/
		virtual void FirstRow() = 0;

		/**
		*  @brief
		*    Fetches the field list
		*
		*  @return
		*    Reference to the current field list
		*/
		virtual const PLGeneral::Array<PLGeneral::String> &FetchFieldList() = 0;

		/**
		*  @brief
		*    Fetches current row from cursor and moves forward
		*
		*  @return
		*    Pointer to the current row map, NULL on error (do NOT delete this!)
		*/
		virtual const PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> *FetchRow() = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cParentQuery
		*    Database query this database query result is in
		*/
		PLDATABASE_API DatabaseQueryResult(DatabaseQuery &cParentQuery);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::Array<PLGeneral::String>						 m_lstFields;	/**< List of fields */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapRow;		/**< Row map */


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
		DatabaseQuery *m_pParentQuery;	/**< Database query this database query result is in (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabase


#endif // __PLDATABASE_DATABASEQUERYRESULT_H__
