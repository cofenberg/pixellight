/*********************************************************\
 *  File: AngelScriptContext.h                           *
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


#ifndef __PLSCRIPTANGELSCRIPT_ANGELSCRIPTCONTEXT_H__
#define __PLSCRIPTANGELSCRIPT_ANGELSCRIPTCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>


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
		static PLGeneral::String GetUniqueName();


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
		static PLGeneral::uint32  m_nContexCounter;		/**< AngelScript context counter */
		static asIScriptEngine	 *m_pAngelScriptEngine;	/**< AngelScript engine instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptAngelScript


#endif // __PLSCRIPTANGELSCRIPT_ANGELSCRIPTCONTEXT_H__
