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


#ifndef __PLDATABASENULL_DATABASE_H__
#define __PLDATABASENULL_DATABASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLDatabase/Database.h>
#include "PLDatabaseNull/PLDatabaseNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDatabaseNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null database implementation
*/
class Database : public PLDatabase::Database {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLDATABASENULL_RTTI_EXPORT, Database, "PLDatabaseNull", PLDatabase::Database, "Null database implementation")
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
		PLDATABASENULL_API Database();

		/**
		*  @brief
		*    Destructor
		*/
		PLDATABASENULL_API virtual ~Database();


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
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bConnected;	/**< Are we currently connected to the database? */


	//[-------------------------------------------------------]
	//[ Public virtual PLDatabase::Database functions         ]
	//[-------------------------------------------------------]
	public:
		PLDATABASENULL_API virtual PLGeneral::String GetVersion() const;
		PLDATABASENULL_API virtual bool Connect(const PLGeneral::String &sServer, const PLGeneral::String &sUserName,
												const PLGeneral::String &sUserPassword, const PLGeneral::String &sDatabase);
		PLDATABASENULL_API virtual bool IsConnected() const;
		PLDATABASENULL_API virtual bool IsConnectionActive() const;
		PLDATABASENULL_API virtual bool Disconnect();
		PLDATABASENULL_API virtual PLDatabase::DatabaseQuery *CreateQuery() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabaseNull


#endif // __PLDATABASENULL_DATABASE_H__
