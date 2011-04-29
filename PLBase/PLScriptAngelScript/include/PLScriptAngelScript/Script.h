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


#ifndef __PLSCRIPTANGELSCRIPT_SCRIPT_H__
#define __PLSCRIPTANGELSCRIPT_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScript/Script.h>
#include "PLScriptAngelScript/PLScriptAngelScript.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class asIScriptModule;
class asIScriptEngine;
class asIScriptContext;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptAngelScript {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    AngelScript (http://www.angelcode.com/angelscript/) script implementation
*/
class Script : public PLScript::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTANGELSCRIPT_RTTI_EXPORT, Script, "PLScriptAngelScript", PLScript::Script, "AngelScript (http://www.angelcode.com/angelscript/) script implementation")
		pl_properties
			pl_property("Language", "AngelScript")
			pl_property("Formats",  "as,AS")
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
		PLSCRIPTANGELSCRIPT_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTANGELSCRIPT_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLScript::Script functions             ]
	//[-------------------------------------------------------]
	public:
		PLSCRIPTANGELSCRIPT_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTANGELSCRIPT_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);
		PLSCRIPTANGELSCRIPT_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(float fValue);
		PLSCRIPTANGELSCRIPT_API virtual void PushArgument(double fValue);
		PLSCRIPTANGELSCRIPT_API virtual bool EndCall();
		PLSCRIPTANGELSCRIPT_API virtual void GetReturn(PLGeneral::uint8 &nValue);
		PLSCRIPTANGELSCRIPT_API virtual void GetReturn(PLGeneral::uint16 &nValue);
		PLSCRIPTANGELSCRIPT_API virtual void GetReturn(PLGeneral::uint32 &nValue);
		PLSCRIPTANGELSCRIPT_API virtual void GetReturn(float &fValue);
		PLSCRIPTANGELSCRIPT_API virtual void GetReturn(double &fValue);


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
		PLGeneral::String  m_sSourceCode;			/**< Script source code */
		asIScriptEngine   *m_pAngelScriptEngine;	/**< AngelScript engine instance, can be a null pointer, managed by AngelScriptContext */
		asIScriptModule   *m_pAngelScriptModule;	/**< AngelScript module instance, can be a null pointer */
		asIScriptContext  *m_pAngelScriptContext;	/**< AngelScript context instance, can be a null pointer */
		PLGeneral::uint32  m_nCurrentArgument;		/**< Current argument, used during function call */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript


#endif // __PLSCRIPTANGELSCRIPT_SCRIPT_H__
