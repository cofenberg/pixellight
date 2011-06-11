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
function Update()
	UpdateBox()
	UpdateSoldier()
end

--@brief
--  Update the box
function UpdateBox()
	-- Update our box rotation
	boxRotation = boxRotation + PL.Timing.GetTimeDifference()*10

	-- Get the scene node we want to manipulate
	local sceneNode = PL.GetApplication():GetScene():GetByName("BigBox")
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
		local sceneNode = PL.GetApplication():GetScene():GetByName("Soldier")
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
