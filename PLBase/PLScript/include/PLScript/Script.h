/*********************************************************\
 *  File: Script.h                                       *
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


#ifndef __PLSCRIPT_SCRIPT_H__
#define __PLSCRIPT_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLScript/PLScript.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScript {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract script base class
*
*  @remarks
*    Each script should have the followig properties:
*    - "Language": Script language (for example: "JavaScript" or "Lua")
*    - "Formats":  File format extensions this script can load in (for example: "js" or "lua")
*
*    Supported script features:
*    - Global variables
*    - Global functions
*      - C++ calls script
*      - Script calls C++ (with namespace support)
*    - RTTI objects
*      - Properties
*      - Attributes
*      - Methods
*      - Signals
*
*    Supported primitive data types: bool, float, double, int8, int16, int32, int64, uint8, uint16, uint32, uint64, PLCore::Object*
*    Please note that not each script language/API may make such a detailed data type distinction.
*    Because strings are fundamental within scripts, PLGeneral::String is supported as well.
*/
class Script : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPT_RTTI_EXPORT, Script, "PLScript", PLCore::Object, "Abstract script base class")
		pl_properties
			pl_property("Language", "Unknown")
			pl_property("Formats",  "Unknown")
		pl_properties_end
		pl_attribute(Name,	PLGeneral::String,	"",	ReadWrite,	DirectValue,	"Name of this script, optional but recommended for better debugging",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPT_API virtual ~Script();

		/**
		*  @brief
		*    Returns the name of the script language the script is using
		*
		*  @return
		*    The name of the script language the script is using (for example "Lua" or "JavaScript")
		*/
		PLSCRIPT_API PLGeneral::String GetScriptLanguage() const;

		/**
		*  @brief
		*    Returns a list of file formats this script supports
		*
		*  @param[out] lstFormats
		*    List of file formats this script supports (the given list is not cleared before new entries are added)
		*/
		PLSCRIPT_API void GetFormats(PLGeneral::Array<PLGeneral::String> &lstFormats) const;

		/**
		*  @brief
		*    Adds a script binding to connect the given RTTI class instance with this script
		*
		*  @param[in] cObject
		*    RTTI class instance, must stay valid as long as this script lives
		*  @param[in] sNamespace
		*    Optional namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on)
		*
		*  @note
		*    - The added RTTI class instance methods will be available to the script as simple global functions
		*/
		PLSCRIPT_API void AddBinding(PLCore::Object &cObject, const PLGeneral::String &sNamespace = "");

		/**
		*  @brief
		*    Add all script bindings to this script
		*
		*  @remarks
		*    Iterates over all available script binding instances and adds them to this script.
		*
		*  @note
		*    - The added RTTI class instance methods will be available to the script as simple global functions
		*/
		PLSCRIPT_API void AddBindings();


	//[-------------------------------------------------------]
	//[ Public virtual Script functions                       ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Adds a global function to the script
		*
		*  @param[in] sFunction
		*    Function name used inside the script to call the global function
		*  @param[in] cDynFunc
		*    Dynamic function
		*  @param[in] sNamespace
		*    Optional namespace (e.g. "MyNamespace", "MyNamespace.MyOtherNamespace" and so on)
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe a script is already set?)
		*
		*  @note
		*    - If there's already a set script ("SetSourceCode()") this method will return an error
		*/
		virtual bool AddGlobalFunction(const PLGeneral::String &sFunction, const PLCore::DynFunc &cDynFunc, const PLGeneral::String &sNamespace = "") = 0;

		/**
		*  @brief
		*    Removes all global functions from the script
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe a script is already set?)
		*
		*  @note
		*    - If there's already a set script ("SetSourceCode()") this method will return an error
		*/
		virtual bool RemoveAllGlobalFunctions() = 0;

		//[-------------------------------------------------------]
		//[ Script source code                                    ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the script source code
		*
		*  @return
		*    The script source code
		*/
		virtual PLGeneral::String GetSourceCode() const = 0;

		/**
		*  @brief
		*    Sets the script source code
		*
		*  @param[in] sSourceCode
		*    Script source code, usually blank ASCII code, empty string to set to script at all
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool SetSourceCode(const PLGeneral::String &sSourceCode) = 0;

		//[-------------------------------------------------------]
		//[ Global variables                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns a list of all global variable names
		*
		*  @return
		*    A list of all global variable names
		*/
		virtual const PLGeneral::Array<PLGeneral::String> &GetGlobalVariables() = 0;

		/**
		*  @brief
		*    Returns whether or not the given name belongs to a global variable
		*
		*  @param[in] sName
		*    Name of the global variable
		*
		*  @return
		*    'true' if the given name belongs to a global variable, else 'false'
		*/
		virtual bool IsGlobalVariable(const PLGeneral::String &sName) = 0;

		/**
		*  @brief
		*    Returns the type ID a gobal variable
		*
		*  @param[in] sName
		*    Name of the global variable
		*
		*  @return
		*    The type ID of the global variable (e.g. "PLCore::TypeFloat" for "float") or "PLCore::TypeInvalid" on error
		*/
		virtual PLCore::ETypeID GetGlobalVariableTypeID(const PLGeneral::String &sName) = 0;

		/**
		*  @brief
		*    Returns the current value of a gobal variable
		*
		*  @param[in] sName
		*    Name of the global variable
		*
		*  @return
		*    The current value of the global variable
		*/
		virtual PLGeneral::String GetGlobalVariable(const PLGeneral::String &sName) = 0;

		/**
		*  @brief
		*    Sets the current value of a gobal variable
		*
		*  @param[in] sName
		*    Name of the global variable
		*  @param[in] cValue
		*    New value of the global variable
		*
		*  @note
		*    - If there's no global variable with the given name, a new global variable is added to the script
		*/
		virtual void SetGlobalVariable(const PLGeneral::String &sName, const PLCore::DynVar &cValue) = 0;

		//[-------------------------------------------------------]
		//[ Global function call, used by "FuncScriptPtr"         ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Starts a function call
		*
		*  @param[in] sFunctionName
		*    Name of the function to call
		*  @param[in] sFunctionSignature
		*    Signature of the function to call (e.g. "void(int,float)")
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - It's not recommended to use this method directly, use "FuncScriptPtr" instead
		*/
		virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature) = 0;

		/**
		*  @brief
		*    Pushes an argument required for the current function call
		*
		*  @param[in] nValue
		*    Argument value
		*
		*  @note
		*    - It's not recommended to use this method directly, use "FuncScriptPtr" instead
		*/
		virtual void PushArgument(bool bValue) = 0;
		virtual void PushArgument(float fValue) = 0;
		virtual void PushArgument(double fValue) = 0;
		virtual void PushArgument(PLGeneral::int8 nValue) = 0;
		virtual void PushArgument(PLGeneral::int16 nValue) = 0;
		virtual void PushArgument(PLGeneral::int32 nValue) = 0;
		virtual void PushArgument(PLGeneral::int64 nValue) = 0;
		virtual void PushArgument(PLGeneral::uint8 nValue) = 0;
		virtual void PushArgument(PLGeneral::uint16 nValue) = 0;
		virtual void PushArgument(PLGeneral::uint32 nValue) = 0;
		virtual void PushArgument(PLGeneral::uint64 nValue) = 0;
		virtual void PushArgument(const PLGeneral::String &sString) = 0;
		virtual void PushArgument(PLCore::Object *pObject) = 0;

		/**
		*  @brief
		*    Ends a function call
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - It's not recommended to use this method directly, use "FuncScriptPtr" instead
		*    - This actually performs the prepared function call
		*/
		virtual bool EndCall() = 0;

		/**
		*  @brief
		*    Returns the result of a function call
		*
		*  @param[out] pnValue
		*    Receives the result of a function call, the given pointer must be valid! (there's no security check!)
		*
		*  @note
		*    - It's not recommended to use this method directly, use "FuncScriptPtr" instead
		*/
		virtual void GetReturn(bool *pbValue) = 0;
		virtual void GetReturn(float *pfValue) = 0;
		virtual void GetReturn(double *pfValue) = 0;
		virtual void GetReturn(PLGeneral::int8 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::int16 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::int32 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::int64 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::uint8 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::uint16 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::uint32 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::uint64 *pnValue) = 0;
		virtual void GetReturn(PLGeneral::String *psValue) = 0;
		virtual void GetReturn(PLCore::Object **ppObject) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLSCRIPT_API Script();

		/**
		*  @brief
		*    Write a string into the log
		*
		*  @param[in] nLogLevel
		*    Log level
		*  @param[in] sText
		*    Text which should be written into the log
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    The text is written to the log only if the current
		*    log level is greater or equal to the specified value.
		*    This method is an extension of "PLGeneral::Log::Output()"
		*    which also adds the name of the script to the given
		*    text.
		*/
		PLSCRIPT_API bool LogOutput(PLGeneral::uint8 nLogLevel, const PLGeneral::String &sText);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Script(const Script &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Script &operator =(const Script &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScript


#endif // __PLSCRIPT_SCRIPT_H__
