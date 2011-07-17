/*********************************************************\
 *  File: ScriptBindingSample.cpp                        *
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
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include "ScriptBindingSample.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ScriptBindingSample)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
int ScriptBindingSample::Return42()
{
	return 42;
}

void ScriptBindingSample::IgnoreTheParameter(float fValue)
{
	System::GetInstance()->GetConsole().Print(String("Ignoring \"") + fValue + "\" ... D'OH!\n");
}

void ScriptBindingSample::SaySomethingWise()
{
	System::GetInstance()->GetConsole().Print(String(Return42()) + " - wise enough?\n");
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ScriptBindingSample::ScriptBindingSample()
{
}

/**
*  @brief
*    Destructor
*/
ScriptBindingSample::~ScriptBindingSample()
{
}
