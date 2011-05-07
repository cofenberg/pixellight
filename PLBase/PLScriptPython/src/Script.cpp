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
	m_pPythonDictionary(nullptr),
	m_pPythonFunction(nullptr),
	m_pPythonTuple(nullptr),
	m_nCurrentArgument(0),
	m_pPythonFunctionResult(nullptr),
	m_pPythonTableOfFunctions(nullptr)
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

	// Remove all dynamic functions
	RemoveAllDynamicFunctions();

	// Release a context reference
	PythonContext::ReleaseContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddDynamicFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Is there a Python module?
	if (m_pPythonModule) {
		// Error!
		return false;
	} else {
		// Add the dynamic function
		DynamicFunction *psDynamicFunction = new DynamicFunction;
		psDynamicFunction->sFunction  = sFunction;
		psDynamicFunction->pDynFunc   = cDynFunc.Clone();
		psDynamicFunction->sNamespace = sNamespace;
		m_lstDynamicFunctions.Add(psDynamicFunction);

		// Done
		return true;
	}
}

bool Script::RemoveAllDynamicFunctions()
{
	// Is there a Python module?
	if (m_pPythonModule) {
		// Error!
		return false;
	} else {
		// Destroy the dynamic functions
		for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
			delete m_lstDynamicFunctions[i]->pDynFunc;
			delete m_lstDynamicFunctions[i];
		}
		m_lstDynamicFunctions.Clear();

		// Done
		return true;
	}
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
			// Get the dictionary of our module (results in borrowed reference, don't use Py_DECREF on it)
			m_pPythonDictionary = PyModule_GetDict(m_pPythonModule);
			if (m_pPythonDictionary) {
				// Are there any dynamic functions?
				if (m_lstDynamicFunctions.GetNumOfElements()) {
					// Allocate the Python table of functions
					m_pPythonTableOfFunctions = new PyMethodDef[m_lstDynamicFunctions.GetNumOfElements()];

					// Add the dynamic functions
					for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
						// Get the dynamic function
						DynamicFunction *psDynamicFunction = m_lstDynamicFunctions[i];

						// Get the current Python method definition
						PyMethodDef *pPythonMethodDefinition = &m_pPythonTableOfFunctions[i];

						// Setup the current Python method definition
						pPythonMethodDefinition->ml_name  = psDynamicFunction->sFunction;	// The name of the built-in function/method
						pPythonMethodDefinition->ml_meth  = PythonFunctionCallback;			// The C function that implements it
						pPythonMethodDefinition->ml_flags = METH_VARARGS;					// Combination of METH_xxx flags, which mostly describe the args expected by the C func
						pPythonMethodDefinition->ml_doc   = nullptr;						// The __doc__ attribute, or NULL

						// Create the new Python function object
						PyObject *pPythonFunction = PyCFunction_New(pPythonMethodDefinition, PyCapsule_New(psDynamicFunction, nullptr, nullptr));

						// Add the new Python function
						if (!AddPythonFunction(m_pPythonDictionary, psDynamicFunction->sFunction, pPythonFunction, psDynamicFunction->sNamespace)) {
							// Error!
							LogOutput(Log::Error, "Failed to add the function '" + psDynamicFunction->sFunction + "\' to the Python module '" + sModuleName + '\'');
						}

						// Remove our reference from the Python function object
						Py_DECREF(pPythonFunction);
					}
				}

				// "Run" the Python script within the dictionary in order to set the source code (results in new reference, use Py_DECREF on the result)
				PyObject *pPythonResult = PyRun_String(sSourceCode, file_input, m_pPythonDictionary, m_pPythonDictionary);
				if (pPythonResult) {
					// Remove our reference from the Python result object
					Py_DECREF(pPythonResult);

					// Done
					return true;
				} else {
					// Error!
					LogOutputWithErrorDescription(Log::Error, "Failed to run the new Python module with the name '" + sModuleName + "\' in order to set the source code", GetPythonErrorDescription());
				}
			} else {
				// Error!
				LogOutput(Log::Error, "Failed to get the dictionary of the new empty Python module with the name '" + sModuleName + '\'');
			}
		} else {
			// Error!
			LogOutput(Log::Error, "Failed to create a new empty Python module with the name '" + sModuleName + '\'');
		}

		// "m_pPythonModule", "m_pPythonDictionary" and "m_pPythonFunction" are borrowed references, don't use Py_DECREF on them
		m_pPythonModule     = nullptr;
		m_pPythonDictionary = nullptr;
		m_pPythonFunction   = nullptr;
	} else {
		// No script at all - done
		return true;
	}

	// Error!
	return false;
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Is there a Python module dictionary?
	if (m_pPythonDictionary) {
		// Request the Python function (results in borrowed reference, don't use Py_DECREF on it)
		m_pPythonFunction = PyDict_GetItemString(m_pPythonDictionary, sFunctionName);
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
	} else {
		// Error!
		LogOutput(Log::Error, "The function '" + sFunctionName + "' was not found because there's no Python module dictionary");
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
		if (!m_pPythonFunctionResult) {
			// Give some log error output
			PyObject *pPythonFunctionName = PyObject_GetAttrString(m_pPythonFunction, "__name__");
			if (pPythonFunctionName)
				LogOutputWithErrorDescription(Log::Error, String("The call of the function '") + PyString_AsString(pPythonFunctionName) + "' failed", GetPythonErrorDescription());
			else
				LogOutputWithErrorDescription(Log::Error, "Function call failed", GetPythonErrorDescription());

			// Error!
			return false;
		}
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
//[ Private static Python callback functions              ]
//[-------------------------------------------------------]
/*
*  @brief
*    Python function callback
*/
PyObject *Script::PythonFunctionCallback(PyObject *pPythonSelf, PyObject *pPythonArguments)
{
	// Get the dynamic function and ensure that the Python arguments are in fact a tuple
	DynamicFunction *psDynamicFunction = reinterpret_cast<DynamicFunction*>(PyCapsule_GetPointer(pPythonSelf, nullptr));
	if (psDynamicFunction && PyTuple_Check(pPythonArguments)) {
		// Get the number of arguments Python gave to us
		String sParams;
		const Py_ssize_t nNumOfArguments = PyTuple_Size(pPythonArguments);
		for (Py_ssize_t i=0; i<nNumOfArguments; i++) {
			// Get the Python argument
			PyObject *pPythonArgument = PyTuple_GetItem(pPythonArguments, i);

			// Get the value
			String sValue;
			if (PyString_Check(pPythonArgument))
				sValue = PyString_AsString(pPythonArgument);
			else if (PyInt_Check(pPythonArgument))
				sValue = PyInt_AsLong(pPythonArgument);
			else if (PyFloat_Check(pPythonArgument))
				sValue = PyFloat_AsDouble(pPythonArgument);

			// Add to functor parameters
			sParams += String("Param") + i + "=\"" + sValue + "\" ";
		}

		// Call the functor
		const String sReturn = psDynamicFunction->pDynFunc->CallWithReturn(sParams);

		// Process the functor return
		switch (psDynamicFunction->pDynFunc->GetReturnTypeID()) {
			case TypeBool:		return PyInt_FromLong	  (sReturn.GetBool());
			case TypeDouble:	return PyFloat_FromDouble (sReturn.GetDouble());
			case TypeFloat:		return PyFloat_FromDouble (sReturn.GetFloat());
			case TypeInt:		return PyInt_FromLong	  (sReturn.GetInt());
			case TypeInt16:		return PyInt_FromLong	  (sReturn.GetInt());
			case TypeInt32:		return PyInt_FromLong	  (sReturn.GetInt());
			case TypeInt64:		return PyInt_FromLong	  (sReturn.GetInt());		// [TODO] TypeInt64 is currently handled just as long
			case TypeInt8:		return PyInt_FromLong	  (sReturn.GetInt());
			case TypeString:	return PyString_FromString(sReturn);
			case TypeUInt16:	return PyInt_FromLong	  (sReturn.GetUInt16());
			case TypeUInt32:	return PyInt_FromLong	  (sReturn.GetUInt32());
			case TypeUInt64:	return PyInt_FromLong	  (sReturn.GetUInt64());	// [TODO] TypeUInt64 is currently handled just as long
			case TypeUInt8:		return PyInt_FromLong	  (sReturn.GetUInt8());
			default:			return Py_None;// TypeVoid, TypeNull, TypeObjectPtr, -1
		}
	}

	// Error!
	return Py_None;
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
	m_pPythonDictionary(nullptr),
	m_pPythonFunction(nullptr),
	m_pPythonTuple(nullptr),
	m_nCurrentArgument(0),
	m_pPythonFunctionResult(nullptr),
	m_pPythonTableOfFunctions(nullptr)
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
*    Returns a string containing the Python error description
*/
String Script::GetPythonErrorDescription() const
{
	String sErrorDescription;

	// Was there an Python error at all?
	if (PyErr_Occurred()) {
		PyObject *pPythonErrorType, *pPythonErrorValue, *pPythonTraceback;
		PyErr_Fetch(&pPythonErrorType, &pPythonErrorValue, &pPythonTraceback);
		if(pPythonErrorValue) {
			// Get a string representation of the Python object (results in new reference, use Py_DECREF on the result)
			PyObject *pPythonString = PyObject_Str(pPythonErrorValue);

			// Get the line number Python object from the trackback Python object
			if (pPythonTraceback) {
				PyObject *pPythonLineNumber = PyObject_GetAttrString(pPythonTraceback, "tb_lineno");
				if (pPythonLineNumber)
					sErrorDescription += String("Line ") + PyInt_AsLong(pPythonLineNumber) + ' ';
			}

			// Get the error description string
			sErrorDescription += String('\"') + PyString_AS_STRING(pPythonString) + '\"';

			// Remove our reference from the Python string object
			Py_DECREF(pPythonString);
		}
		Py_XDECREF(pPythonErrorValue);
		Py_XDECREF(pPythonErrorType);
		Py_XDECREF(pPythonTraceback);
	}

	// Return the error description
	return sErrorDescription;
}

/**
*  @brief
*    Write a string into the log
*/
bool Script::LogOutputWithErrorDescription(uint8 nLogLevel, const String &sText, const String &sErrorDescription)
{
	// Call the base implementation
	return sErrorDescription.GetLength() ? Script::LogOutput(nLogLevel, sText + " (" + sErrorDescription + ')') : Script::LogOutput(nLogLevel, sText);
}

/**
*  @brief
*    Clears the script
*/
void Script::Clear()
{
	// Is there a Python module?
	if (m_pPythonModule) {

		// [TODO] Remove Python module, use "PyObject_Del()" for this purpose?

		// Reset the source code
		m_sSourceCode = "";

		// "m_pPythonModule", "m_pPythonDictionary" and "m_pPythonFunction" are borrowed references, don't use Py_DECREF on them
		m_pPythonModule     = nullptr;
		m_pPythonDictionary = nullptr;
		m_pPythonFunction   = nullptr;

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

		// Destroy the Python table of functions
		if (m_pPythonTableOfFunctions) {
			delete [] m_pPythonTableOfFunctions;
			m_pPythonTableOfFunctions = nullptr;
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

/**
*  @brief
*    Adds a Python function
*/
bool Script::AddPythonFunction(PyObject *pPythonDictionary, const String &sFunction, PyObject *pPythonFunction, const String &sNamespace) const
{
	// Is the given namespace empty?
	if (sNamespace.GetLength()) {
		// Nope, the target namespace is not yet reached...

		// Find the next "." within the given nested Python namespace name
		int nPartEnd = sNamespace.IndexOf(".");
		if (nPartEnd < 0)
			nPartEnd = sNamespace.GetLength();

		// Get the current Python namespace name
		const String sSubsNamespaceName = sNamespace.GetSubstring(0, nPartEnd);

		// Is there already a Python dictionary object with the given name?
		// Request the Python dictionary (results in borrowed reference, don't use Py_DECREF on it)
		PyObject *pNestedPythonDictionary = PyDict_GetItemString(pPythonDictionary, sSubsNamespaceName);
		if (pNestedPythonDictionary) {
			// There's already an Python object with the given name - Must be a Python dictionary object...
			if (PyDict_Check(pNestedPythonDictionary)) {
				// Go down the rabbit hole...
				return AddPythonFunction(pNestedPythonDictionary, sFunction, pPythonFunction, sNamespace.GetSubstring(nPartEnd + 1));
			} else {
				// Error!
				return false;
			}
		} else {
			// Create the Python dictionary object (results in new reference, use Py_DECREF on the result)
			PyObject *pNestedPythonDictionary = PyDict_New();

			// Add the new Python dictionary object to the current one
			if (PyDict_SetItemString(pPythonDictionary, sSubsNamespaceName, pNestedPythonDictionary) == -1) {
				// Remove our reference from the Python dictionary object
				Py_DECREF(pNestedPythonDictionary);

				// Error!
				return false;
			}

			// Go down the rabbit hole...
			const bool bResult = AddPythonFunction(pNestedPythonDictionary, sFunction, pPythonFunction, sNamespace.GetSubstring(nPartEnd + 1));

			// Remove our reference from the Python dictionary object
			Py_DECREF(pNestedPythonDictionary);

			// Done
			return bResult;
		}
	} else {
		// Jap, now add the given Python function object to the current Python dictionary object
		if (PyDict_SetItemString(pPythonDictionary, sFunction, pPythonFunction) == -1) {
			// Error!
			return false;
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptPython
