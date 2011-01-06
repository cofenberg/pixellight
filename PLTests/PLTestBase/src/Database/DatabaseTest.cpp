/*********************************************************\
 *  File: DatabaseTest.cpp                               *
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
#include <PLDatabase/Database.h>
#include <PLDatabase/DatabaseQuery.h>
#include <PLDatabase/DatabaseQueryResult.h>
#include "PLTestBase/Database/DatabaseTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLDatabase;


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tests an database implementation
*/
void DatabaseTest::TestImplementation(const String &sClass, const String &sServer, const String &sUserName, const String &sUserPassword, const String &sDatabase)
{
	Database *pDatabase = nullptr;

	// Create(const String &sClass)
	StartTask("Create(const String &sClass)");
	pDatabase = Database::Create(sClass);
	EndTask(pDatabase != nullptr);
	if (!pDatabase) return; // Error!

	// Print version
	Print(pDatabase->GetVersion());
	Print("\n");

	// Connect(const String &sServer, const String &sUserName, const String &sUserPassword, const String &sDatabase)
	StartTask("Connect(const String &sServer, const String &sUserName, const String &sUserPassword, const String &sDatabase)");
	if (pDatabase->Connect(sServer, sUserName, sUserPassword, sDatabase)) {
		EndTask(true);

		// IsConnected()
		StartTask("IsConnected()");
		EndTask(pDatabase->IsConnected());

		// IsConnectionActive()
		StartTask("IsConnectionActive()");
		EndTask(pDatabase->IsConnectionActive());

		// Test the query implementation
		TestQuery(pDatabase);

		// Disconnect()
		StartTask("Disconnect()");
		pDatabase->Disconnect();
		EndTask(true);
	} else EndTask(false);

	// delete
	StartTask("delete");
	delete pDatabase;
	EndTask(true);
}

/**
*  @brief
*    Prints field names in query result
*/
void DatabaseTest::PrintFields(DatabaseQueryResult *pQResult)
{
	// Check parameter
	if (!pQResult) return; // Error!

	// A new row, please
	Print("\n");

	// Fetch the fild list
	const Array<String> &lstList = pQResult->FetchFieldList();

	// Print the fild names
	for (uint32 i=0; i<lstList.GetNumOfElements(); i++)
		Print(String("Field ") + int(i) + ": " + lstList[i] + '\n');
}

/**
*  @brief
*    Prints rows in query result
*/
void DatabaseTest::PrintRows(DatabaseQueryResult *pQResult)
{
	// Check parameter
	if (!pQResult) return; // Error!

	// A new row, please
	Print("\n");

	// Fetched rows from query result are returned in a map containing
	// field name and field value
	const HashMap<String, String> *pmapRow = pQResult->FetchRow();
	while (pmapRow && pmapRow->GetNumOfElements()) {
		// id
		int id = pmapRow->Get("id").GetInt();

		// name
		String name = pmapRow->Get("name");

		// livel
		int livel = pmapRow->Get("livel").GetInt();

		// Print
		Print(String("Record: ") + "id: " + int(id) + " name: " + name + " livel: " + livel + '\n');

		// Next, please
		pmapRow = pQResult->FetchRow();
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tests a database query implementation
*/
void DatabaseTest::TestQuery(Database *pDatabase)
{
	DatabaseQueryResult *pDbQResult = nullptr;
	DatabaseQuery *pDbQuery = nullptr;
	bool bResult = true;

	// CreateQuery()
	StartTask("CreateQuery()");
		pDbQuery = pDatabase->CreateQuery();
	EndTask(pDbQuery != nullptr);
	if (!pDbQuery) return; // Error!

	// DatabaseQuery::IsSelect(const String &sSQL)
	StartTask("DatabaseQuery::IsSelect(const String &sSQL)");
		if (DatabaseQuery::IsSelect("")) bResult = false;
		if (DatabaseQuery::IsSelect(" Ahoioi")) bResult = false;
		if (!DatabaseQuery::IsSelect("SELECT")) bResult = false;
		if (!DatabaseQuery::IsSelect(" SELECT")) bResult = false;
		if (DatabaseQuery::IsSelect(" S ELECT  ")) bResult = false;
	EndTask(bResult);

	// Query: Execute("")
	StartTask("Query: Execute(\"\")");
		pDbQResult = pDbQuery->Execute("");
	EndTask(pDbQResult == nullptr);

	// Query: Execute("SELECT * from TestTable")
	StartTask("Query: Execute(\"SELECT * from TestTable\")");
		if (pDbQResult=pDbQuery->Execute("SELECT * from TestTable")) {
			PrintFields(pDbQResult);
			PrintRows(pDbQResult);
			delete pDbQResult;
		}
	EndTask(pDbQResult != nullptr);

	// Query: Execute("SELECT * from TestTable WHERE id=1")
	StartTask("Query: Execute(\"SELECT * from TestTable WHERE id=1\")");
		if (pDbQResult=pDbQuery->Execute("SELECT * from TestTable WHERE id=1")) {
			PrintFields(pDbQResult);
			PrintRows(pDbQResult);
			delete pDbQResult;
		}
	EndTask(pDbQResult != nullptr);

	// Cleanup
	delete pDbQuery;
}
