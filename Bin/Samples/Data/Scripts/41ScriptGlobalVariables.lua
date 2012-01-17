--/*********************************************************\
-- *  File: 41ScriptGlobalVariables.lua                    *
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
g_Name = "Bob"

-- Global variables within a namespace
PublicVariables = {	-- Create the "PublicVariables"-namespace
	Health	= 42,	-- Create the variable "Health" within the "PublicVariables"-namespace
	Gold	= 21,	-- Create the variable "Gold" within the "PublicVariables"-namespace
}
