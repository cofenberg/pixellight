--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
g_Factor = 1
g_Name = "Bob"

-- Global variables within a namespace
PublicVariables = {};		-- Create the "PublicVariables"-namespace
PublicVariables.Health = 42	-- Create the variable "Health" within the "PublicVariables"-namespace
