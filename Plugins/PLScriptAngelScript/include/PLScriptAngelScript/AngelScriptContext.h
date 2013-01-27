/*********************************************************\
 *  File: AngelScriptContext.h                           *
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


#ifndef __PLSCRIPTANGELSCRIPT_ANGELSCRIPTCONTEXT_H__
#define __PLSCRIPTANGELSCRIPT_ANGELSCRIPTCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class asIScriptEngine;
struct asSMessageInfo;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptAngelScript {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static AngelScript context
*/
class AngelScriptContext {


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Adds a context reference
		*
		*  @return
		*    AngelScript engine instance, null pointer on error
		*
		*  @note
		*    - If this is the first reference, the internal AngelScript context is created automatically
		*/
		static asIScriptEngine *AddContextReference();

		/**
		*  @brief
		*    Releases a context reference
		*
		*  @note
		*    - If this is the last reference, the internal AngelScript context is destroyed automatically
		*/
		static void ReleaseContextReference();

		/**
		*  @brief
		*    Returns an unique name that can be used as AngelScript module name
		*
		*  @return
		*    Unique name
		*/
		static PLCore::String GetUniqueName();


	//[-------------------------------------------------------]
	//[ Private static AngelScript callback functions         ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal AngelScript message callback function
		*
		*  @param[in] pASMessageInfo
		*    Message information
		*  @param[in] pParam
		*    Message parameter
		*/
		static void ASMessageCallback(const asSMessageInfo *pASMessageInfo, void *pParam);


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static PLCore::uint32   m_nContexCounter;		/**< AngelScript context counter */
		static asIScriptEngine *m_pAngelScriptEngine;	/**< AngelScript engine instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript


#endif // __PLSCRIPTANGELSCRIPT_ANGELSCRIPTCONTEXT_H__
