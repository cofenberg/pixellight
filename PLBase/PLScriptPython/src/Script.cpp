/*********************************************************\
 *  File: Script.cpp                                     *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Log/Log.h>
#include "PLScriptPython/PythonContext.h"
#include "PLScriptPython/Script.h"
#include <graminit.h>	// Python parse-mode flags (e.g. "file_input")


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptPython {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Script)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Script::Script() :
	m_pPythonModule(nullptr),
	m_pPythonDirectory(nullptr),
	m_pPythonFunction(nullptr),
	m_pPythonTuple(nullptr),
	m_nCurrentArgument(0),
	m_pPythonFunctionResult(nullptr)
{
	// Add a context reference
	PythonContext::AddContextReference();
}

/**
*  @brief
*    Destructor
*/
Script::~Script()
{
	// Clear the script
	Clear();

	// Release a context reference
	PythonContext::ReleaseContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddDynamicFunction(const String &sFunction, const DynFunc &cDynFunc)
{
	// [TODO] Implement me

	// Done
	return true;
}

bool Script::RemoveAllDynamicFunctions()
{
	// [TODO] Implement me

	// Done
	return true;
}

String Script::GetSourceCode() const
{
	return m_sSourceCode;
}

bool Script::SetSourceCode(const String &sSourceCode)
{
	// Clear the previous script
	Clear();

	// Backup the given source code
	m_sSourceCode = sSourceCode;

	// Is there source code?
	if (m_sSourceCode.GetLength()) {
		// Get the name of our new Python module
		const String sModuleName = Name.Get().GetLength() ? Name.Get() : "__main__";

		// Create an empty Python module (results in borrowed reference, don't use Py_DECREF on it)
		m_pPythonModule = PyImport_AddModule(sModuleName);
		if (m_pPythonModule) {
			// Get the directory of our module (results in borrowed reference, don't use Py_DECREF on it)
			m_pPythonDirectory = PyModule_GetDict(m_pPythonModule); 
			if (m_pPythonDirectory) {
				// "Run" the Python script within the directory in order to set the source code (results in new reference, use Py_DECREF on the result)
				PyObject *pPythonResult = PyRun_String(sSourceCode, file_input, m_pPythonDirectory, m_pPythonDirectory);
				if (pPythonResult) {

					// [TODO] Error handling in case there was an error within the given script code

					// Remove our reference from the Python result object
					Py_DECREF(pPythonResult);

					// Done
					return true;
				} else {
					// Error!
					LogOutput(Log::Error, "Failed to run the new Python module with the name '" + sModuleName + "\' in order to set the source code");
				}
			} else {
				// Error!
				LogOutput(Log::Error, "Failed to get the directory of the new empty Python module with the name '" + sModuleName + '\'');
			}
		} else {
			// Error!
			LogOutput(Log::Error, "Failed to create a new empty Python module with the name '" + sModuleName + '\'');
		}

		// "m_pPythonModule", "m_pPythonDirectory" and "m_pPythonFunction" are borrowed references, don't use Py_DECREF on them
		m_pPythonModule    = nullptr;
		m_pPythonDirectory = nullptr;
		m_pPythonFunction  = nullptr;
	} else {
		// No script at all - done
		return true;
	}

	// Error!
	return false;
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Request the Python function (results in borrowed reference, don't use Py_DECREF on it)
	m_pPythonFunction = PyDict_GetItemString(m_pPythonDirectory, sFunctionName);
	if (m_pPythonFunction) {
		// Functions must be callable
		if (PyCallable_Check(m_pPythonFunction)) {
			// Remove our reference of the Python tuple
			if (m_pPythonTuple) {
				Py_DECREF(m_pPythonTuple);
				m_pPythonTuple = nullptr;
			}

			// Current argument is 0
			m_nCurrentArgument = 0;

			// Remove our reference of from Python function result
			if (m_pPythonFunctionResult) {
				Py_DECREF(m_pPythonFunctionResult);
				m_pPythonFunctionResult = nullptr;
			}

			// Done
			return true;
		} else {
			// "m_pPythonFunction" is a borrowed reference, don't use Py_DECREF on it
			m_pPythonFunction = nullptr;

			// Error!
			LogOutput(Log::Error, "The function '" + sFunctionName + "' is no callable");
		}
	} else {
		// Error!
		LogOutput(Log::Error, "The function '" + sFunctionName + "' was not found");
	}

	// Error!
	return false;
}

void Script::PushArgument(int nValue)
{
	// Is there a current Python function?
	if (m_pPythonFunction) {
		// Increases the number of arguments
		IncreaseNumOfArguments();

		// Set the current tuple item
		PyTuple_SetItem(m_pPythonTuple, m_nCurrentArgument - 1, PyInt_FromLong(nValue));
	}
}

void Script::PushArgument(uint8 nValue)
{
	// Is there a current Python function?
	if (m_pPythonFunction) {
		// Increases the number of arguments
		IncreaseNumOfArguments();

		// Set the current tuple item
		PyTuple_SetItem(m_pPythonTuple, m_nCurrentArgument - 1, PyInt_FromLong(nValue));
	}
}

void Script::PushArgument(uint16 nValue)
{
	// Is there a current Python function?
	if (m_pPythonFunction) {
		// Increases the number of arguments
		IncreaseNumOfArguments();

		// Set the current tuple item
		PyTuple_SetItem(m_pPythonTuple, m_nCurrentArgument - 1, PyInt_FromLong(nValue));
	}
}

void Script::PushArgument(uint32 nValue)
{
	// Is there a current Python function?
	if (m_pPythonFunction) {
		// Increases the number of arguments
		IncreaseNumOfArguments();

		// Set the current tuple item
		PyTuple_SetItem(m_pPythonTuple, m_nCurrentArgument - 1, PyInt_FromLong(nValue));
	}
}

void Script::PushArgument(float fValue)
{
	// Is there a current Python function?
	if (m_pPythonFunction) {
		// Increases the number of arguments
		IncreaseNumOfArguments();

		// Set the current tuple item
		PyTuple_SetItem(m_pPythonTuple, m_nCurrentArgument - 1, PyFloat_FromDouble(fValue));
	}
}

void Script::PushArgument(double fValue)
{
	// Is there a current Python function?
	if (m_pPythonFunction) {
		// Increases the number of arguments
		IncreaseNumOfArguments();

		// Set the current tuple item
		PyTuple_SetItem(m_pPythonTuple, m_nCurrentArgument - 1, PyFloat_FromDouble(fValue));
	}
}

bool Script::EndCall()
{
	// Is there a current Python function?
	if (m_pPythonFunction) {
		// Call the Python function (results in new reference, use Py_DECREF on the result)
		m_pPythonFunctionResult = PyObject_CallObject(m_pPythonFunction, m_pPythonTuple);
	}

	// Done
	return true;
}

void Script::GetReturn(int &nValue)
{
	nValue = m_pPythonFunctionResult ? PyInt_AsLong(m_pPythonFunctionResult) : 0;
}

void Script::GetReturn(uint8 &nValue)
{
	nValue = m_pPythonFunctionResult ? static_cast<uint8>(PyInt_AsLong(m_pPythonFunctionResult)) : 0;
}

void Script::GetReturn(uint16 &nValue)
{
	nValue = m_pPythonFunctionResult ? static_cast<uint16>(PyInt_AsLong(m_pPythonFunctionResult)) : 0;
}

void Script::GetReturn(uint32 &nValue)
{
	nValue = m_pPythonFunctionResult ? PyInt_AsLong(m_pPythonFunctionResult) : 0;
}

void Script::GetReturn(float &fValue)
{
	fValue = m_pPythonFunctionResult ? static_cast<float>(PyFloat_AsDouble(m_pPythonFunctionResult)) : 0.0f;
}

void Script::GetReturn(double &fValue)
{
	fValue = m_pPythonFunctionResult ? PyFloat_AsDouble(m_pPythonFunctionResult) : 0.0;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Script::Script(const Script &cSource) :
	m_pPythonModule(nullptr),
	m_pPythonDirectory(nullptr),
	m_pPythonFunction(nullptr),
	m_pPythonTuple(nullptr),
	m_nCurrentArgument(0),
	m_pPythonFunctionResult(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Script &Script::operator =(const Script &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Clears the script
*/
void Script::Clear()
{
	// Is there a Python module?
	if (m_pPythonModule) {
		// Reset the source code
		m_sSourceCode = "";

		// "m_pPythonModule", "m_pPythonDirectory" and "m_pPythonFunction" are borrowed references, don't use Py_DECREF on them
		m_pPythonModule    = nullptr;
		m_pPythonDirectory = nullptr;
		m_pPythonFunction  = nullptr;

		// Reset the current number of arguments
		m_nCurrentArgument = 0;

		// Remove our reference of from Python tuple
		if (m_pPythonTuple) {
			Py_DECREF(m_pPythonTuple);
			m_pPythonTuple = nullptr;
		}

		// Remove our reference of from Python function result
		if (m_pPythonFunctionResult) {
			Py_DECREF(m_pPythonFunctionResult);
			m_pPythonFunctionResult = nullptr;
		}
	}
}

/**
*  @brief
*    Increases the number of arguments
*/
void Script::IncreaseNumOfArguments()
{
	// Increase the number of arguments
	m_nCurrentArgument++;

	// Create/resize the Python tuble (results in new reference, use Py_DECREF on the result)
	if (m_pPythonTuple)
		_PyTuple_Resize(&m_pPythonTuple, m_nCurrentArgument);
	else
		m_pPythonTuple = PyTuple_New(m_nCurrentArgument);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptPython
