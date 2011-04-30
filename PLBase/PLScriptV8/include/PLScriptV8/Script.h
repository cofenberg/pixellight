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


#ifndef __PLSCRIPTV8_SCRIPT_H__
#define __PLSCRIPTV8_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <v8.h>
#include <PLScript/Script.h>
#include "PLScriptV8/PLScriptV8.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptV8 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    V8 (JavaScript engine, http://code.google.com/p/v8/) script implementation
*/
class Script : public PLScript::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTV8_RTTI_EXPORT, Script, "PLScriptV8", PLScript::Script, "V8 (JavaScript engine, http://code.google.com/p/v8/) script implementation")
		pl_properties
			pl_property("Language", "JavaScript")
			pl_property("Formats",  "js,JS")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLSCRIPTV8_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTV8_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLScript::Script functions             ]
	//[-------------------------------------------------------]
	public:
		PLSCRIPTV8_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTV8_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);
		PLSCRIPTV8_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTV8_API virtual void PushArgument(int nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTV8_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTV8_API virtual void PushArgument(float fValue);
		PLSCRIPTV8_API virtual void PushArgument(double fValue);
		PLSCRIPTV8_API virtual bool EndCall();
		PLSCRIPTV8_API virtual void GetReturn(int &nValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::uint8 &nValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::uint16 &nValue);
		PLSCRIPTV8_API virtual void GetReturn(PLGeneral::uint32 &nValue);
		PLSCRIPTV8_API virtual void GetReturn(float &fValue);
		PLSCRIPTV8_API virtual void GetReturn(double &fValue);


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

		/**
		*  @brief
		*    Clears the script
		*/
		void Clear();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String			m_sSourceCode;		/**< Script source code */
		v8::Persistent<v8::Context> m_cV8Context;		/**< V8 context */
		PLGeneral::String			m_sCurrentFunction;	/**< Name of the current function */
		v8::Handle<v8::Value>		m_cV8CurrentResult;	/**< Current V8 function */
		PLGeneral::Array<double>	m_lstArguments;		/**< Current V8 arguments */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptV8


#endif // __PLSCRIPTV8_SCRIPT_H__
