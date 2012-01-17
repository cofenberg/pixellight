--/*********************************************************\
-- *  File: 42ScriptFunctors.lua                           *
-- *
-- *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
-- *
-- *  This file is part of PixelLight.
-- *
-- *  PixelLight is free software: you can redistribute it and/or modify
-- *  it under the terms of the GNU Lesser General Public License as published by
-- *  the Free Software Foundation, either version 3 of the License, or
-- *  (at your option) any later version.
-- *
-- *  PixelLight is distributed in the hope that it will be useful,
-- *  but WITHOUT ANY WARRANTY; without even the implied warranty of
-- *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
-- *  GNU Lesser General Public License for more details.
-- *
-- *  You should have received a copy of the GNU Lesser General Public License
-- *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
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
