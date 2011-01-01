/*********************************************************\
 *  File: CompileError.h                                 *
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


#ifndef __PLCORE_TOOLS_COMPILEERROR_H__
#define __PLCORE_TOOLS_COMPILEERROR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Compile time error
*
*  @remarks
*    Implementation for 'true', takes anything as parameter to the constructor and therefore raises no error
*/
template<bool>
struct CompileTimeError
{
	CompileTimeError(...) {}
};

/**
*  @brief
*    Compile time error
*
*  @remarks
*    Implementation for 'false', raising an error as it has no constructor
*/
template<>
struct CompileTimeError<false>
{
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Macros                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Raise error
*
*  @param[in] error
*    Error message (must NOT be a string but a valid C++ identifier, such as My_Error_Message!)
*/
#define PLCORE_ERROR(error) \
{ \
	class ERROR_##error {}; \
	ERROR_##error _error; \
	PLCore::CompileTimeError<false> __error(_error); \
}

//	(void)sizeof( PLCore::CompileTimeError<false>(ERROR_##error()) ); \

/**
*  @brief
*    Raise error if expression is false
*
*  @param[in] expr
*	 Expression to check
*  @param[in] error
*    Error message (must NOT be a string but a valid C++ identifier, such as My_Error_Message!)
*/
#define PLCORE_CHECK(expr, error) \
{ \
	class ERROR_##error {}; \
	ERROR_##error _error; \
	PLCore::CompileTimeError<(expr)> __error(_error); \
}


#endif // __PLCORE_TOOLS_COMPILEERROR_H__
