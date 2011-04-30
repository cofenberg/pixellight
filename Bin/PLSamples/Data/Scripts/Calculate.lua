--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
g_Factor = 1


--[-------------------------------------------------------]
--[ Functions                                             ]
--[-------------------------------------------------------]
function getFactor()
	return g_Factor
end

function setFactor(a)
	g_Factor = a
end

function calculate(a, b)
	return a * b * g_Factor
end
