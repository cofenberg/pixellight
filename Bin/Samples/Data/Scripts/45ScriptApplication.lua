--/*********************************************************\
-- *  File: 45ScriptApplication.lua                        *
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

		-- Clear the content of the current used render target by using gray (this way, in case on an graphics error we might still see at least something)
		this:GetSceneRendererTool():SetPassAttribute("Begin", "ColorClear", "0.5 0.5 0.5 0")

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

	-- Get the input controller of the application
	local inputController = this:GetInputController()
	if inputController ~= nil then
		-- Use the script function "OnControl" as slot and connect it with the RTTI "SignalOnControl"-signal of our RTTI controller class instance
		inputController.SignalOnControl.Connect(OnControl)
	end
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

--@brief
--  Slot function is called by C++ when a control event has occured
--
--@param[in] control
--  Occured control
function OnControl(control)
	-- Check whether the escape key was pressed
	if control:GetName() == "KeyboardEscape" then
		-- Shut down the application
		this:Exit(0)
	end
end
