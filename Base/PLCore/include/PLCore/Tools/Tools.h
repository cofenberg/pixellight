/*********************************************************\
 *  File: Tools.h                                        *
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


#ifndef __PLCORE_TOOLS_H__
#define __PLCORE_TOOLS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static class with some useful tool functions
*/
class Tools {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		//[-------------------------------------------------------]
		//[ Convertion tools                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    float to uint32
		*
		*  @param[in] f
		*    Float value to convert
		*
		*  @return
		*    The converted float value
		*/
		inline static uint32 FloatToUInt32(float f);

		/**
		*  @brief
		*    uint32 to float
		*
		*  @param[in] n
		*    uint32 value to convert
		*
		*  @return
		*    The converted uint32 value
		*/
		inline static float UInt32ToFloat(uint32 n);

		//[-------------------------------------------------------]
		//[ String tools                                          ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Base64 encoder
		*
		*  @param[in] sString
		*    Unencoded string
		*
		*  @return
		*    Base64 encoded string
		*/
		inline static String GetBase64(const String &sString);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Tools.inl"


#endif // __PLCORE_TOOLS_H__
