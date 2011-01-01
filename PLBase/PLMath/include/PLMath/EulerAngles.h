/*********************************************************\
 *  File: EulerAngles.h                                  *
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


#ifndef __PLMATH_EULERANGLES_H__
#define __PLMATH_EULERANGLES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/PLMath.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Matrix3x3;
class Matrix3x4;
class Matrix4x4;
class Quaternion;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static Euler angles conversion tool class
*
*  @remarks
*    The implementation of this class is basing on the 'Euler Angle Conversion' gem from Ken Shoemake (1993)
*    published in the 'Graphics Gems IV' book. The original code is avaliable here:
*    http://www.graphicsgems.org/gemsiv/euler_angle/
*
*  @note
*    - Within PixelLight, only 'XYZs' Euler angles are used
*    - When dealing with Euler angles keep care of 'gimbal lock', at http://www.sjbaker.org/steve/omniv/eulers_are_evil.html
*      you will find some good information about this topic
*/
class EulerAngles {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Euler angles order
		*/
		enum EOrder {
			// Static axes (takes axes from initial static frame)
			XYZs = 0,	/**< XYZ static axis */
			XYXs = 2,	/**< XYX static axis */
			XZYs = 4,	/**< XZY static axis */
			XZXs = 6,	/**< XZX static axis */
			YZXs = 8,	/**< YZX static axis */
			YZYs = 10,	/**< YZY static axis */
			YXZs = 12,	/**< YXZ static axis */
			YXYs = 14,	/**< YXY static axis */
			ZXYs = 16,	/**< ZXY static axis */
			ZXZs = 18,	/**< ZXZ static axis */
			ZYXs = 20,	/**< ZYX static axis */
			ZYZs = 22,	/**< ZYZ static axis */
			// Rotating axes
			ZYXr = 1,	/**< ZYX rotating axis */
			XYXr = 3,	/**< XYX rotating axis */
			YZXr = 5,	/**< YZX rotating axis */
			XZXr = 7,	/**< XZX rotating axis */
			XZYr = 9,	/**< XZY rotating axis */
			YZYr = 11,	/**< YZY rotating axis */
			ZXYr = 13,	/**< ZXY rotating axis */
			YXYr = 15,	/**< YXY rotating axis */
			YXZr = 17,	/**< YXZ rotating axis */
			ZXZr = 19,	/**< ZXZ rotating axis */
			XYZr = 21,	/**< XYZ rotating axis */
			ZYZr = 23	/**< ZYZ rotating axis */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets a rotation quaternion by using three given Euler angles
		*
		*  @param[in]  fAngleX
		*    Rotation angle around the x axis (in radian)
		*    where fAngleX > 0 indicates a counterclockwise rotation in the yz-plane (if you look along -x)
		*  @param[in]  fAngleY
		*    Rotation angle around the y axis (in radian)
		*    where fAngleY > 0 indicates a counterclockwise rotation in the zx-plane (if you look along -y)
		*  @param[in]  fAngleZ
		*    Rotation angle around the z axis (in radian)
		*    where fAngleZ > 0 indicates a counterclockwise rotation in the xy-plane (if you look along -z)
		*  @param[out] qRotation
		*    Resulting rotation quaternion
		*  @param[out] nOrder
		*    Order of the Euler angles
		*/
		PLMATH_API static void ToQuaternion(float fAngleX, float fAngleY, float fAngleZ, Quaternion &qRotation, EOrder nOrder = XYZs);

		/**
		*  @brief
		*    Returns the Euler angles from a rotation quaternion
		*
		*  @param[in]  qRotation
		*    Rotation quaternion
		*  @param[out] fAngleX
		*    Will receive the rotation angle around the x axis (in radian)
		*  @param[out] fAngleY
		*    Will receive the rotation angle around the y axis (in radian)
		*  @param[out] fAngleZ
		*    Will receive the rotation angle around the z axis (in radian)
		*  @param[out] nOrder
		*    Order of the Euler angles
		*/
		PLMATH_API static void FromQuaternion(const Quaternion &qRotation, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder = XYZs);

		/**
		*  @brief
		*    Sets a rotation matrix by using three given Euler angles
		*
		*  @param[in] fAngleX
		*    Rotation angle around the x axis (in radian)
		*    where fAngleX > 0 indicates a counterclockwise rotation in the yz-plane (if you look along -x)
		*  @param[in] fAngleY
		*    Rotation angle around the y axis (in radian)
		*    where fAngleY > 0 indicates a counterclockwise rotation in the zx-plane (if you look along -y)
		*  @param[in] fAngleZ
		*    Rotation angle around the z axis (in radian)
		*    where fAngleZ > 0 indicates a counterclockwise rotation in the xy-plane (if you look along -z)
		*  @param[out] mRot
		*    Resulting rotation matrix
		*  @param[out] nOrder
		*    Order of the Euler angles
		*/
		PLMATH_API static void ToMatrix(float fAngleX, float fAngleY, float fAngleZ, Matrix3x3 &mRot, EOrder nOrder = XYZs);
		PLMATH_API static void ToMatrix(float fAngleX, float fAngleY, float fAngleZ, Matrix3x4 &mRot, EOrder nOrder = XYZs);
		PLMATH_API static void ToMatrix(float fAngleX, float fAngleY, float fAngleZ, Matrix4x4 &mRot, EOrder nOrder = XYZs);

		/**
		*  @brief
		*    Returns the Euler angles from a rotation matrix
		*
		*  @param[in]  mRot
		*    Rotation matrix
		*  @param[out] fAngleX
		*    Will receive the rotation angle around the x axis (in radian)
		*  @param[out] fAngleY
		*    Will receive the rotation angle around the y axis (in radian)
		*  @param[out] fAngleZ
		*    Will receive the rotation angle around the z axis (in radian)
		*  @param[out] nOrder
		*    Order of the Euler angles
		*/
		PLMATH_API static void FromMatrix(const Matrix3x3 &mRot, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder = XYZs);
		PLMATH_API static void FromMatrix(const Matrix3x4 &mRot, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder = XYZs);
		PLMATH_API static void FromMatrix(const Matrix4x4 &mRot, float &fAngleX, float &fAngleY, float &fAngleZ, EOrder nOrder = XYZs);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_EULERANGLES_H__
