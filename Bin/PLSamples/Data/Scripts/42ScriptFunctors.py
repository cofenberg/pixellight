#[-------------------------------------------------------]
#[ Global variables                                      ]
#[-------------------------------------------------------]
g_Factor = 1


#[-------------------------------------------------------]
#[ Global functions                                      ]
#[-------------------------------------------------------]
def ScriptFunction(a):
	return a

def CallCpp(a):
	return FirstNamespace['SecondNamespace']['CppFunction'](a) + CppMethod(a) + CppScriptFunction(a)

def GetFactor():
	return g_Factor

def SetFactor(a):
	global g_Factor	# If this isn't done, g_Factor is used as local variable when assigning a new value to it
	g_Factor = a

def Calculate(a, b):
	return a * b * g_Factor

def ReturnMyString(s):
	return CppStringFunction(s)
