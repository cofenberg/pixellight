//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
var g_Factor = 1;


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
function scriptFunction(a)
{
	return a;
}

function getFactor()
{
	return g_Factor;
}

function setFactor(a)
{
	g_Factor = a;
}

function calculate(a, b)
{
	return a * b * g_Factor;
}
