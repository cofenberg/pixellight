--/*********************************************************\
-- *  File: ScriptsScene.lua                               *
-- *
-- *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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


-- This script is called by the scene "Scripts.scene"
-- -> The global variable "this" points to the C++ RTTI scene node modifier class instance invoking the script


--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
soldierTimer = 0
boxRotation = 0


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
--@brief
--  Update function called by C++
function OnUpdate()
	UpdateBox()
	UpdateSoldier()
end

--@brief
--  Update the box
function UpdateBox()
	-- Update our box rotation
	boxRotation = boxRotation + PL.Timing.GetTimeDifference()*10

	-- Get the scene node we want to manipulate
	local sceneNode = this:GetSceneNode():GetByName("BigBox")
	if sceneNode ~= nil then
		sceneNode.Rotation = "0 " .. boxRotation .. " 0"
	end
end

--@brief
--  Update the soldier
function UpdateSoldier()
	-- Update our timer
	soldierTimer = soldierTimer + PL.Timing.GetTimeDifference()

	-- Time to do something?
	if soldierTimer > 1 then
		-- Set back the timer
		soldierTimer = soldierTimer - 1

		-- Get the scene node we want to manipulate
		local sceneNode = this:GetSceneNode():GetByName("Soldier")
		if sceneNode ~= nil then
			-- Toggle debug mode
			if sceneNode.DebugFlags == 0 then
				sceneNode.DebugFlags = 1
			else
				sceneNode.DebugFlags = 0
			end
		end
	end
end
