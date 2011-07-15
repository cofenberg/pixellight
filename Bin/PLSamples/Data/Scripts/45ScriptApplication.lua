-- Scripted stand-alone application -> This is a Lua port of the C++ PixelLight SDK sample "60Scene"
-- -> The global variable "this" points to the C++ RTTI application class instance invoking the script (usually the same as "PL.GetApplication()")


--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
lightTimer = 0	-- This global variable is used for the light animation


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
--@brief
--  Called by C++ when the application should initialize itself
function OnInit()
	-- This function is call by the application framework when application should initialize itself.
	-- At this point, the core components of the application are ready to be used.

	-- Set the application base directory relative to the filename of this running Lua script
	this:SetBaseDirectory("../../")

	-- Set the used scene renderer (optional filename of a fallback scene renderer to use in case the desired scene renderer can't be used as second parameter)
	if this:GetSceneRendererTool():SetSceneRenderer(this:GetScene(), "Deferred.sr", "FixedFunctions.sr") == true then
		-- Configure the compositing system by using the comfort scene renderer tool.
		-- We're setting the attribute "Flags" of the scene renderer step named "DeferredSPAAO" to the value "Inactive" -
		-- this has the effect that the fillrate eating HBAO post processing effect is deactivated. Please note, that
		-- internally "just" the generic PixelLight RTTI is used. PixelLight itself doesn't offer such settings as
		-- "low graphics quality" because the framework can't decide automatically for you what is considered "low quality"
		-- within your application. We highly recommend to provide your end-user more abstract graphics settings as
		-- seen in, for example, many video games out there.
		this:GetSceneRendererTool():SetPassAttribute("DeferredSPAAO", "Flags", "Inactive")
	end

	-- Create the scene
	CreateScene()
end

--@brief
--  Called by C++ when the application should update itself
function OnUpdate()
	-- Get the scene container
	local sceneContainer = this:GetScene()
	if sceneContainer ~= nil then
		-- Get the scene node with the name 'Light' (our 'white light')
		local lightSceneNode = sceneContainer:GetByName("Light")
		if lightSceneNode ~= nil then
			-- We set the current light position using the RTTI class interface. This is quite comfortable and universal
			-- because you haven't to care about the concrete class type - just set the variable values.
			lightSceneNode.Position = string.format("%f %f %f", math.sin(lightTimer), math.sin(lightTimer)/2 + 2, -(math.cos(lightTimer) + 5))

			-- Update the light timer by using the time difference between the last and the current frame
			lightTimer = lightTimer + PL.Timing.GetTimeDifference()
		end
	end
end

--@brief
--  Called by C++ when the application should de-initialize itself
function OnDeInit()
	-- Nothing to do in here
end

--@brief
--  Function which creates the scene
function CreateScene()
	-- Clear the scene, after calling this method the scene is empty (Background: The script can be restarted... :)
	this:ClearScene()

	-- Get the scene container
	local sceneContainer = this:GetScene()
	if sceneContainer ~= nil then
		-- Create a camera scene node
		local camera = sceneContainer:Create("PLScene::SNCamera", "FreeCamera", "Position='1 2 -3' Rotation='25 210 0'")

		-- Make this to our main scene camera
		this:SetCamera(camera)

		-- Create a scene node with the soldier mesh which can produce a shadow
		local soldierSceneNode = sceneContainer:Create("PLScene::SNMesh", "Soldier", "Flags='CastShadow|ReceiveShadow' Position='0.0 0.1 -5.0' Scale='0.008 0.008 0.008' Mesh='Data/Meshes/Soldier.mesh'")
		if soldierSceneNode ~= nil then
			-- Add a scene node modifier which will constantly rotate the soldier
			soldierSceneNode:AddModifier("PLScene::SNMRotationLinearAnimation", "Velocity='0 10 0'")

			-- Add a scene node modifier which will playback the animation named "walk_0" letting the soldier walk
			soldierSceneNode:AddModifier("PLScene::SNMMeshAnimation", "Name='walk_0'")

			-- Add a scene node modifier which will animate the morph target named "blink" letting the soldier blink from time to time
			soldierSceneNode:AddModifier("PLScene::SNMMeshMorphBlink", "Name='blink'")
		end

		-- Create a light source scene node to illuminate the scene - this light can cast shadows
		sceneContainer:Create("PLScene::SNPointLight", "Light", "Flags='CastShadow|Flares|Corona' Range='4'")

		-- Create the floor scene node
		sceneContainer:Create("PLScene::SNMesh", "Floor", "Flags='CastShadow|ReceiveShadow' Position='0.0 0.0 -5.0' Rotation='0.0 180.0 0.0' Scale='4.0 0.1 4.0' Mesh='Default'")
	end
end
