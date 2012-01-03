/*********************************************************\
 *  File: UnitTests.cpp                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/Array.h>
#include <PLCore/String/String.h>
#include "UnitTest++AddIns/MyTestReporter.h"
#include "UnitTest++AddIns/MyMobileTestReporter.h"
#include "UnitTest++AddIns/RunAllTests.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Unit tests program entry point                        ]
//[-------------------------------------------------------]
int UnitTests(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	MyMobileTestReporter rep;
	//MyTestReporter rep;

	return UnitTest::RunAllTests(rep);
}

