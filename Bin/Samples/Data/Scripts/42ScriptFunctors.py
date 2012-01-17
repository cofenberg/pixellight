#/*********************************************************\
# *  File: 42ScriptFunctors.py                            *
# *
# *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
# *
# *  This file is part of PixelLight.
# *
# *  PixelLight is free software: you can redistribute it and/or modify
# *  it under the terms of the GNU Lesser General Public License as published by
# *  the Free Software Foundation, either version 3 of the License, or
# *  (at your option) any later version.
# *
# *  PixelLight is distributed in the hope that it will be useful,
# *  but WITHOUT ANY WARRANTY; without even the implied warranty of
# *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# *  GNU Lesser General Public License for more details.
# *
# *  You should have received a copy of the GNU Lesser General Public License
# *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
#\*********************************************************/


#[-------------------------------------------------------]
#[ Global variables                                      ]
#[-------------------------------------------------------]
g_Factor = 1


#[-------------------------------------------------------]
#[ Global functions                                      ]
#[-------------------------------------------------------]
def ScriptFunction(a):
	return a

def CallCpp(a):
	return FirstNamespace['SecondNamespace']['CppFunction'](a) + CppMethod(a) + CppScriptFunction(a)

def GetFactor():
	return g_Factor

def SetFactor(a):
	global g_Factor	# If this isn't done, g_Factor is used as local variable when assigning a new value to it
	g_Factor = a

def Calculate(a, b):
	return a * b * g_Factor

def ReturnMyString(s):
	return CppStringFunction(s)

# [TODO] Global function within a namespace
