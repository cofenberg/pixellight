/*********************************************************\
 *  File: <Filename>                            *
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
#include "PLPhysicsBullet/Helper.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsBullet {


btQuaternion Helper::PLQuaternionTobtQuaternion(const PLMath::Quaternion& qPLQuat)
{
	return btQuaternion(qPLQuat.x, qPLQuat.y, qPLQuat.z, qPLQuat.w);
}

PLMath::Quaternion Helper::btQuaternionToPLQuaternion(const btQuaternion& qbtQuat)
{
	return PLMath::Quaternion(qbtQuat.w(), qbtQuat.x(), qbtQuat.y(), qbtQuat.z());
}

btVector3 Helper::PLVector3TobtVector3(const PLMath::Vector3& vPLVector3)
{
	return btVector3(vPLVector3.x, vPLVector3.y, vPLVector3.z);
}

PLMath::Vector3 Helper::btVector3ToPLVector3(const btVector3& vbtVector3)
{
	return PLMath::Vector3(vbtVector3.x(), vbtVector3.y(), vbtVector3.z());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
