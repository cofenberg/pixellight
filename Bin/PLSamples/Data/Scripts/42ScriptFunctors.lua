--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
g_Factor = 1


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
function ScriptFunction(a)
	return a
end

function CallCpp(a)
	-- "FirstNamespace.SecondNamespace.CppFunction(a)" is an equivalent for "FirstNamespace["SecondNamespace"]["CppFunction"](a)"
	return FirstNamespace.SecondNamespace.CppFunction(a) + CppMethod(a) + CppScriptFunction(a)
end

function GetFactor()
	return g_Factor
end

function SetFactor(a)
	g_Factor = a
end

function Calculate(a, b)
	return a * b * g_Factor
end

function ReturnMyString(s)
	return CppStringFunction(s)
end
