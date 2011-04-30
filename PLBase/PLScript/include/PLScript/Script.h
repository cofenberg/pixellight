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
*    - "Language": Shader language (for example: "JavaScript")
*    - "Formats":  File format extensions this script can load in (for example: "js")
*
*  @note
*    - [TODO] Script support is currently under construction
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


	//[-------------------------------------------------------]
	//[ Public virtual Script functions                       ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Adds a dynamic function to the script
		*
		*  @param[in] sFunction
		*    Function name used inside the script to call the dynamic function
		*  @param[in] cDynFunc
		*    Dynamic function
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe a script is already set?)
		*
		*  @note
		*    - If there's already a set script ("SetSourceCode()") this method will return an error
		*/
		virtual bool AddDynamicFunction(const PLGeneral::String &sFunction, const PLCore::DynFunc &cDynFunc) = 0;

		/**
		*  @brief
		*    Removes all dynamic functions from the script
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe a script is already set?)
		*
		*  @note
		*    - If there's already a set script ("SetSourceCode()") this method will return an error
		*/
		virtual bool RemoveAllDynamicFunctions() = 0;

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

		// [TODO] Comment those methods when done
		virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature) = 0;
		virtual void PushArgument(int nValue) = 0;
		virtual void PushArgument(PLGeneral::uint8 nValue) = 0;
		virtual void PushArgument(PLGeneral::uint16 nValue) = 0;
		virtual void PushArgument(PLGeneral::uint32 nValue) = 0;
		virtual void PushArgument(float fValue) = 0;
		virtual void PushArgument(double fValue) = 0;
		virtual bool EndCall() = 0;
		virtual void GetReturn(int &nValue) = 0;
		virtual void GetReturn(PLGeneral::uint8 &nValue) = 0;
		virtual void GetReturn(PLGeneral::uint16 &nValue) = 0;
		virtual void GetReturn(PLGeneral::uint32 &nValue) = 0;
		virtual void GetReturn(float &fValue) = 0;
		virtual void GetReturn(double &fValue) = 0;


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
