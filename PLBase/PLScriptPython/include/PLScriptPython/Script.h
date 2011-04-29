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


#ifndef __PLSCRIPTPYTHON_SCRIPT_H__
#define __PLSCRIPTPYTHON_SCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScript/Script.h>
#include "PLScriptPython/PLScriptPython.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptPython {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Python (http://www.python.org/) script implementation
*/
class Script : public PLScript::Script {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSCRIPTPYTHON_RTTI_EXPORT, Script, "PLScriptPython", PLScript::Script, "Python (http://www.python.org/) script implementation")
		pl_properties
			pl_property("Language", "Python")
			pl_property("Formats",  "py,PY")
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
		PLSCRIPTPYTHON_API Script();

		/**
		*  @brief
		*    Destructor
		*/
		PLSCRIPTPYTHON_API virtual ~Script();


	//[-------------------------------------------------------]
	//[ Public virtual PLScript::Script functions             ]
	//[-------------------------------------------------------]
	public:
		PLSCRIPTPYTHON_API virtual PLGeneral::String GetSourceCode() const;
		PLSCRIPTPYTHON_API virtual bool SetSourceCode(const PLGeneral::String &sSourceCode);
		PLSCRIPTPYTHON_API virtual bool BeginCall(const PLGeneral::String &sFunctionName, const PLGeneral::String &sFunctionSignature);
		PLSCRIPTPYTHON_API virtual void PushArgument(PLGeneral::uint8 nValue);
		PLSCRIPTPYTHON_API virtual void PushArgument(PLGeneral::uint16 nValue);
		PLSCRIPTPYTHON_API virtual void PushArgument(PLGeneral::uint32 nValue);
		PLSCRIPTPYTHON_API virtual void PushArgument(float fValue);
		PLSCRIPTPYTHON_API virtual void PushArgument(double fValue);
		PLSCRIPTPYTHON_API virtual bool EndCall();
		PLSCRIPTPYTHON_API virtual void GetReturn(PLGeneral::uint8 &nValue);
		PLSCRIPTPYTHON_API virtual void GetReturn(PLGeneral::uint16 &nValue);
		PLSCRIPTPYTHON_API virtual void GetReturn(PLGeneral::uint32 &nValue);
		PLSCRIPTPYTHON_API virtual void GetReturn(float &fValue);
		PLSCRIPTPYTHON_API virtual void GetReturn(double &fValue);


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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sSourceCode;	/**< Script source code */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptPython


#endif // __PLSCRIPTPYTHON_SCRIPT_H__
