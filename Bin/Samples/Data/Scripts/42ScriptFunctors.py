#/*********************************************************\
# *  File: 42ScriptFunctors.py                            *
# *
# *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
# *
# *  This file is part of PixelLight.
# *
# *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
# *  and associated documentation files (the “Software”), to deal in the Software without
# *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
# *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
# *  Software is furnished to do so, subject to the following conditions:
# *
# *  The above copyright notice and this permission notice shall be included in all copies or
# *  substantial portions of the Software.
# *
# *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
# *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
