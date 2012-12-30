--/*********************************************************\
-- *  File: 42ScriptFunctors.lua                           *
-- *
-- *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
-- *
-- *  This file is part of PixelLight.
-- *
-- *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
-- *  and associated documentation files (the “Software”), to deal in the Software without
-- *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
-- *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
-- *  Software is furnished to do so, subject to the following conditions:
-- *
-- *  The above copyright notice and this permission notice shall be included in all copies or
-- *  substantial portions of the Software.
-- *
-- *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
-- *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
-- *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
-- *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
-- *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
--\*********************************************************/


--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
g_Factor = 1


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
function ScriptFunction(a)
	return a
end

function CallCpp(a)
	-- "FirstNamespace.SecondNamespace.CppFunction(a)" is an equivalent for "FirstNamespace["SecondNamespace"]["CppFunction"](a)"
	return FirstNamespace.SecondNamespace.CppFunction(a) + CppMethod(a) + CppScriptFunction(a)
end

function GetFactor()
	return g_Factor
end

function SetFactor(a)
	g_Factor = a
end

function Calculate(a, b)
	return a * b * g_Factor
end

function ReturnMyString(s)
	return CppStringFunction(s)
end

-- Global function within a namespace
PublicFunctions = {			-- Create the "PublicFunctions"-namespace
	SayHello = function()	-- Create the function "SayHello" within the "PublicFunctions"-namespace
		return "Hello there, I'am in a namespace!"
	end
}
