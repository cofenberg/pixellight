--[-------------------------------------------------------]
--[ Global variables                                      ]
--[-------------------------------------------------------]
g_Factor = 1


--[-------------------------------------------------------]
--[ Global functions                                      ]
--[-------------------------------------------------------]
function Update()
	PL.Log.OutputAlways("Always")
	PL.Log.OutputCritical("Critical")
	PL.Log.OutputError("Error")
	PL.Log.OutputWarning("Warning")
	PL.Log.OutputInfo("Info")
	PL.Log.OutputDebug("Debug")
end

function getFactor()
	return PL.Timing.GetTimeDifference() + PL.Timing.GetFramesPerSecond()
end
