--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
g_Factor = 1


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
function scriptFunction(a)
	return a
end

function callCpp(a)
	return FirstNamespace.SecondNamespace.cppFunction(a) + cppMethod(a) + cppScriptFunction(a)
end

function getFactor()
	return g_Factor
end

function setFactor(a)
	g_Factor = a
end

function calculate(a, b)
	return a * b * g_Factor
end

function returnMyString(s)
	return cppStringFunction(s)
end
