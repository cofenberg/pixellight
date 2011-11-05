/*********************************************************\
 *  File: Main.cpp                                       *
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
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Main.h>
#include <PLCore/Main.h>
#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


// [TODO] Just a platform integration test
TEST(TestMe) {
	CHECK(false == true);
}


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
// ... kind of first unit tests: Is our universal program entry point working?
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// [TODO] Some test so we can see across the platforms that we're able to run, remove this when the real unit tests are there
	System::GetInstance()->GetConsole().Print("I'am a life, I'am a life.. oh no, please, no, not the return!! Noo.....");

	// Done
	return 0;
}
