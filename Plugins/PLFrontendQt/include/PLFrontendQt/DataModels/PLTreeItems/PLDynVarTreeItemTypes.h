/*********************************************************\
 *  File: PLDynVarTreeItemTypes.h                        *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLFRONTENDQT_PLDYNVARTREEITEMTYPES_H__
#define __PLFRONTENDQT_PLDYNVARTREEITEMTYPES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/qnamespace.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This class is only a container for some enums used for PLTreeItems
*/
// [TODO] convert to c++0x11 enum class when possible
class PLDynVarTreeItemTypes {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		enum DynVarTreeItemTypes {
			Unknown,
			String,
			Enum,
			Flags,
			Bool,
			Int8,
			Int16,
			Int32, // int is Int32
			Int64,
			UInt8,
			UInt16,
			UInt32, // unsigend int is UInt32
			UInt64,
			Float,
			Double,
			Vector3,
			Vector2,
			Vector4,
			Vector3i,
			Vector2i,
			Color
		};
		
		enum ItemRoles {
			DynVarItemTypeRole = Qt::UserRole+1,
			DynVarEnumValues
		};
};



//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_PLDYNVARTREEITEMTYPES_H__
