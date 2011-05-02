#[-------------------------------------------------------]
#[ Global variables                                      ]
#[-------------------------------------------------------]
g_Factor = 1


#[-------------------------------------------------------]
#[ Global functions                                      ]
#[-------------------------------------------------------]
def scriptFunction(a):
	return a

def callCpp(a):
	return cppFunction(a) + cppMethod(a) + cppScriptFunction(a)

def getFactor():
	return g_Factor

def setFactor(a):
	global g_Factor	# If this isn't done, g_Factor is used as local variable when assigning a new value to it
	g_Factor = a

def calculate(a, b):
	return a * b * g_Factor
