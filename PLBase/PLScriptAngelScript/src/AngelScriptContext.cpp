/*********************************************************\
 *  File: AngelScriptContext.cpp                         *
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
#include <angelscript.h>
#include <../../src/add_on/scriptstring/scriptstring.h>
#include <../../src/add_on/scriptarray/scriptarray.h>
#include <../../src/add_on/scriptmath/scriptmath.h>
#include <PLGeneral/Log/Log.h>
#include "PLScriptAngelScript/AngelScriptContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScriptAngelScript {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
uint32			 AngelScriptContext::m_nContexCounter     = 0;
asIScriptEngine	*AngelScriptContext::m_pAngelScriptEngine = nullptr;


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a context reference
*/
asIScriptEngine *AngelScriptContext::AddContextReference()
{
	// Check context
	if (!m_nContexCounter) {
		PL_LOG(Info, String("Initialize AngelScript ") + ANGELSCRIPT_VERSION_STRING)

		// Create the script engine
		m_pAngelScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
		if (m_pAngelScriptEngine) {
			// The script compiler will write any compiler messages to the callback
			m_pAngelScriptEngine->SetMessageCallback(asFUNCTION(ASMessageCallback), 0, asCALL_CDECL);

			// Register some standard AngelScript addons
			RegisterScriptString(m_pAngelScriptEngine);
			RegisterScriptArray(m_pAngelScriptEngine, false);
			RegisterScriptMath(m_pAngelScriptEngine);
		} else {
			PL_LOG(Error, "Failed to create script engine")
		}
	}
	m_nContexCounter++;

	// Return the AngelScript engine instance
	return m_pAngelScriptEngine;
}

/**
*  @brief
*    Releases a context reference
*/
void AngelScriptContext::ReleaseContextReference()
{
	// Check context
	m_nContexCounter--;
	if (!m_nContexCounter && m_pAngelScriptEngine) {
		PL_LOG(Info, String("De-initialize AngelScript ") + ANGELSCRIPT_VERSION_STRING)

		// Release the script engine
		m_pAngelScriptEngine->Release();
		m_pAngelScriptEngine = nullptr;
	}
}

/**
*  @brief
*    Returns an unique name that can be used as AngelScript module name
*/
String AngelScriptContext::GetUniqueName()
{
	static uint32 nCounter = 0;
	return nCounter++;
}


//[-------------------------------------------------------]
//[ Private static AngelScript callback functions         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Internal AngelScript message callback function
*/
void AngelScriptContext::ASMessageCallback(const asSMessageInfo *pASMessageInfo, void *pParam)
{
	// Check the message type
	uint8 nLogLevel = Log::Info;
	switch (pASMessageInfo->type) {
		case asMSGTYPE_ERROR:
			nLogLevel = Log::Error;
			break;

		case asMSGTYPE_WARNING:
			nLogLevel = Log::Warning;
			break;

		case asMSGTYPE_INFORMATION:
			nLogLevel = Log::Info;
			break;
	}

	// Write the message into the log
	Log::GetInstance()->Output(nLogLevel, String(pASMessageInfo->section) + " (" + pASMessageInfo->row + ", " + pASMessageInfo->col + ") : " + pASMessageInfo->message);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript
