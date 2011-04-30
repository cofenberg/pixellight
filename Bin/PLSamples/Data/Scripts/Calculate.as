//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
float g_Factor = 1;


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
float getFactor()
{
	return g_Factor;
}

void setFactor(float a)
{
	g_Factor = a;
}

float calculate(float a, float b)
{
	return a * b * g_Factor;
}
