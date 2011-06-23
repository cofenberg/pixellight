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
