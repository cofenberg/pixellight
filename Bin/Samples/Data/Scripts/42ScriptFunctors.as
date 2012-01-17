/*********************************************************\
 *  File: 42ScriptFunctors.as                            *
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
//[ Global variables                                      ]
//[-------------------------------------------------------]
float g_Factor = 1;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
int ScriptFunction(int a)
{
	return a;
}

int CallCpp(int a)
{
	return FirstNamespace_SecondNamespace_CppFunction(a) + CppMethod(a) + CppScriptFunction(a);
}

float GetFactor()
{
	return g_Factor;
}

void SetFactor(float a)
{
	g_Factor = a;
}

float Calculate(float a, float b)
{
	return a * b * g_Factor;
}

string ReturnMyString(string s)
{
	return CppStringFunction(s);
}

// [TODO] Global function within a namespace
