--/*********************************************************\
-- *  File: ScriptsScene.lua                               *
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
