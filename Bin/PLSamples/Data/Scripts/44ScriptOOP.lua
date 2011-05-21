--[-------------------------------------------------------]
--[ Classes                                               ]
--[-------------------------------------------------------]
-- The "MyScriptClass"-class declaration
MyScriptClass = {

	-- The default constructor - In Lua a static method
	new = function()
		PL.System.Console.Print("MyScriptClass::MyScriptClass()\n")
		return MyScriptClass.newParams(0)
	end,

	-- Destructor - Not possible in Lua

	-- Another constructor - In Lua a static method, please note that we can't have two
	-- methods with the same names and just another signature in Lua
	newParams = function(a)
		-- A private class attribute -> Emulates the C++ "this"-pointer by using a Lua table
		-- (most people are using the name "self" for this purpose, I stick with "this" to have as comparable as possible example scripts)
		local this = {}

		-- A public class attribute
		this.a = a

		PL.System.Console.Print("MyScriptClass::MyScriptClass(a) - a=" .. this.a .. "\n")

		-- A public class method
		function this.DoSomething()
			this.a = this.a*2
			PL.System.Console.Print("MyScriptClass:DoSomething() - a=" .. this.a .. "\n")
		end

		-- Return the created class instance
		return this
	end

}

-- A derived class named "MyDerivedScriptClass"
MyDerivedScriptClass = {

	-- The default constructor
	new = function()
		-- Calling the non-default constructor of the base class
		this = MyScriptClass.newParams(10)

		-- A public class attribute
		this.b = 0

		-- A private class attribute
		local privateX = 0

		PL.System.Console.Print("MyDerivedScriptClass::MyDerivedScriptClass() - b=" .. this.b .. "\n")
		PL.System.Console.Print("MyDerivedScriptClass::MyDerivedScriptClass() - privateX=" .. privateX .. "\n")

		-- A private class method - In Lua a static method
		local function PrivateDoSomething()
			-- Increment the private attribute
			privateX = privateX + 1
			PL.System.Console.Print("MyDerivedScriptClass::PrivateDoSomething() - privateX=" .. privateX .. "\n")
		end

		-- Overloading a public virtual method
		local Base_DoSomething = this.DoSomething -- Save the base implementation so that we can still access it later
		function this.DoSomething()
			-- Call the base class implementation
			Base_DoSomething()

			-- Do something more
			this.b = this.a
			PL.System.Console.Print("MyDerivedScriptClass::DoSomething() - b=" .. this.b .. "\n")

			-- Call the private class method
			PrivateDoSomething()
		end

		-- A public class method
		function this.GetPrivateX()
			return privateX
		end

		-- Return the created class instance
		return this
	end

}


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
function OOP()
	-- Create an instance of MyScriptClass
	local firstObject = MyScriptClass.newParams(5)
	firstObject.a = 1
	firstObject:DoSomething()	-- In Lua, this is the short version of "firstObject.DoSomething(firstObject)"

	-- Create an instance of MyDerivedScriptClass
	local secondObject = MyDerivedScriptClass.new()
	secondObject:DoSomething()
	secondObject.a = firstObject.a
	secondObject.b = 2
	PL.System.Console.Print("secondObject.GetPrivateX() = " .. secondObject.GetPrivateX() .. "\n")
end

function UseCppRTTIObject(cppRTTIObject)
	if cppRTTIObject == nil then
		PL.System.Console.Print("UseCppRTTIObject() was called with a null pointer as parameter\n")
	else
		-- Access RTTI object property
		PL.System.Console.Print("Property: cppRTTIObject.MyProperty = " .. cppRTTIObject.MyProperty .. "\n")

		-- Access RTTI object attributes
		PL.System.Console.Print("Attribute: cppRTTIObject.Level = " .. cppRTTIObject.Level .. "\n")
		PL.System.Console.Print("Attribute: cppRTTIObject.Name = " .. cppRTTIObject.Name .. "\n")
		cppRTTIObject.Name = "Timmy!"
		PL.System.Console.Print("Attribute: cppRTTIObject.Level = " .. cppRTTIObject.Level .. "\n")
		PL.System.Console.Print("Attribute: cppRTTIObject.Name = " .. cppRTTIObject.Name .. "\n")

		-- Call RTTI object methods
		cppRTTIObject:SaySomethingWise()
		cppRTTIObject:IgnoreTheParameter(5)

		-- Emit RTTI object signal
		cppRTTIObject:MySignal("Lua")
	end

	-- Get an RTTI object by using a C++ functor
	local object = GetMyRTTIClassInstance(cppRTTIObject)
	if object == nil then
		PL.System.Console.Print("GetMyRTTIClassInstance() returned a null pointer\n")
	else
		object:MySignal("Lua GetMyRTTIClassInstance() worked\n")
		local self = object:GetSelf()
		if self == nil then
			PL.System.Console.Print("Lua object:GetSelf() returned a null pointer\n")
		else
			self:MySignal("Lua object:GetSelf():GetMyRTTIClassInstance() worked\n")
		end
	end
	return object
end
