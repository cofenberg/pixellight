/*********************************************************\
 *  File: Database.cpp                                   *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLTest/TestManager.h>
#include "PLTestBase/Database/DatabaseTestMySQL.h"
#include "PLTestBase/Database/DatabaseTestSQLite.h"
#include "PLTestBase/Database/DatabaseTestPostgreSQL.h"


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
/**
*  @brief
*    Database tests
*/
void DatabaseTests()
{
	// Perform the test cases
	TestManager cTestManager("PLDatabase");
	cTestManager.Perform(new DatabaseTestMySQL);
	cTestManager.Perform(new DatabaseTestSQLite);
	cTestManager.Perform(new DatabaseTestPostgreSQL);
}
