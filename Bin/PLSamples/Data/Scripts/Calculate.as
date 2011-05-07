//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
float g_Factor = 1;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
int scriptFunction(int a)
{
	return a;
}

int callCpp(int a)
{
	return FirstNamespace_SecondNamespace_cppFunction(a) + cppMethod(a) + cppScriptFunction(a);
}

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
