//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
var g_Factor = 1;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
function ScriptFunction(a)
{
	return a;
}

function CallCpp(a)
{
	return FirstNamespace.SecondNamespace.CppFunction(a) + CppMethod(a) + CppScriptFunction(a);
}

function GetFactor()
{
	return g_Factor;
}

function SetFactor(a)
{
	g_Factor = a;
}

function Calculate(a, b)
{
	return a * b * g_Factor;
}

function ReturnMyString(s)
{
	return CppStringFunction(s);
}
