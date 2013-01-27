/*********************************************************\
 *  File: AngelScriptContext.cpp                         *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <AngelScript/angelscript.h>
#include <../../../External/Optional/AngelScript/add_on/scriptstring/scriptstring.h>
#include <../../../External/Optional/AngelScript/add_on/scriptarray/scriptarray.h>
#include <../../../External/Optional/AngelScript/add_on/scriptmath/scriptmath.h>
#include <PLCore/Log/Log.h>
#include "PLScriptAngelScript/AngelScriptContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
