//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
float g_Factor = 1;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
int ScriptFunction(int a)
{
	return a;
}

int CallCpp(int a)
{
	return FirstNamespace_SecondNamespace_CppFunction(a) + CppMethod(a) + CppScriptFunction(a);
}

float GetFactor()
{
	return g_Factor;
}

void SetFactor(float a)
{
	g_Factor = a;
}

float Calculate(float a, float b)
{
	return a * b * g_Factor;
}

string ReturnMyString(string s)
{
	return CppStringFunction(s);
}

// [TODO] Global function within a namespace
