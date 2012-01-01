/*********************************************************\
 *  File: Helper.h                                       *
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

#ifndef __PLPHYSICSBULLET_HELPER_H__
#define __PLPHYSICSBULLET_HELPER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Quaternion.h>
#include <PLMath/Vector3.h>
#include "PLPhysicsBullet/PLPhysicsBullet.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsBullet {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Helper class for PLPhysicsBullet.
*    Holds converter methods between pixellight types and bullet types
*/
class Helper {
	
	
	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		static btQuaternion PLQuaternionTobtQuaternion(const PLMath::Quaternion& qPLQuat);
		static PLMath::Quaternion btQuaternionToPLQuaternion(const btQuaternion& qbtQuat);
		static btVector3 PLVector3TobtVector3(const PLMath::Vector3& vPLVector3);
		static PLMath::Vector3 btVector3ToPLVector3(const btVector3& vbtVector3);
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsBullet


#endif // __PLPHYSICSBULLET_HELPER_H__
