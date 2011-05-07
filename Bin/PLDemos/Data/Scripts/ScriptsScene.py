#[-------------------------------------------------------]
#[ Global variables                                      ]
#[-------------------------------------------------------]
g_Factor = 1


#[-------------------------------------------------------]
#[ Global functions                                      ]
#[-------------------------------------------------------]
def Update():
	PL['Log']['OutputAlways']("Always")
	PL['Log']['OutputCritical']("Critical")
	PL['Log']['OutputError']("Error")
	PL['Log']['OutputWarning']("Warning")
	PL['Log']['OutputInfo']("Info")
	PL['Log']['OutputDebug']("Debug")
	return

def getFactor():
	return PL['Timing']['GetTimeDifference']() + PL['Timing']['GetFramesPerSecond']()
