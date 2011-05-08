//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
float g_Factor = 1;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
void Update()
{
	PL_Log_OutputAlways("Always");
	PL_Log_OutputCritical("Critical");
	PL_Log_OutputError("Error");
	PL_Log_OutputWarning("Warning");
	PL_Log_OutputInfo("Info");
	PL_Log_OutputDebug("Debug");
}

float getFactor()
{
	return PL_Timing_GetTimeDifference() + PL_Timing_GetFramesPerSecond();
}
