--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
timer = 0;


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
function Update()
	-- Update our timer
	timer = timer + PL.Timing.GetTimeDifference()

	-- Time to do something?
	if timer > 1 then
		-- Set back the timer
		timer = timer - 1

		-- Get the scene node we want to manipulate
		local sceneNode = PL.Application.Scene.Get("Scene.Soldier")
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
