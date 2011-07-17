/*********************************************************\
 *  File: Transform3.h                                   *
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


#ifndef __PLMATH_TRANSFORM3_H__
#define __PLMATH_TRANSFORM3_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include <PLMath/Matrix3x4.h>
#include <PLMath/Quaternion.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    3D transform class
*
*  @remarks
*    The design goal of this class was not to be as memory compact as possible - for such a use case, one can use
*    for example directly Matrix3x4. The design goal was wo provide a class that is able to convert between different
*    representations of a 3D transform in an efficient way. To achieve this, the "Lazy Evaluation"-scheme is used. This
*    means that, for example, the inverse transform is only recalculated if it's really required. To allow a practical
*    usage of this transform class within more advanced systems, events are provided to inform when transform data has
*    been changed.
*/
class Transform3 {


	//[-------------------------------------------------------]
	//[ Events                                                ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<>	EventPosition;	/**< Position change event */
		PLCore::Event<>	EventRotation;	/**< Rotation change event */
		PLCore::Event<>	EventScale;		/**< Scale change event */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor (set's an identity transform matrix)
		*/
		PLMATH_API Transform3();

		/**
		*  @brief
		*    Copy constructor (event data is not copied)
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLMATH_API Transform3(const Transform3 &cSource);

		/**
		*  @brief
		*    Copy operator (event data is not copied)
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*
		*  @note
		*    - EventPosition, EventRotation and EventScale events are emitted
		*/
		PLMATH_API Transform3 &operator =(const Transform3 &cSource);

		/**
		*  @brief
		*    Gets the position
		*
		*  @return
		*    Position
		*/
		inline const Vector3 &GetPosition() const;

		/**
		*  @brief
		*    Sets the position
		*
		*  @param[in] vPosition
		*    New position
		*/
		PLMATH_API void SetPosition(const Vector3 &vPosition);

		/**
		*  @brief
		*    Gets the rotation
		*
		*  @return
		*    Rotation
		*/
		inline const Quaternion &GetRotation() const;

		/**
		*  @brief
		*    Sets the rotation
		*
		*  @param[in] qRotation
		*    New rotation
		*/
		PLMATH_API void SetRotation(const Quaternion &qRotation);

		/**
		*  @brief
		*    Gets the scale
		*
		*  @return
		*    Scale
		*/
		inline const Vector3 &GetScale() const;

		/**
		*  @brief
		*    Sets the scale
		*
		*  @param[in] vScale
		*    New scale
		*/
		PLMATH_API void SetScale(const Vector3 &vScale);

		/**
		*  @brief
		*    Returns the current final transform matrix
		*
		*  @return
		*    The current final transform matrix
		*
		*  @note
		*    - If position, rotation or scale was changed, the current transform matrix
		*      is recalculated internally before it is returned
		*/
		PLMATH_API const Matrix3x4 &GetMatrix();

		/**
		*  @brief
		*    Sets the current final transform matrix
		*
		*  @param[in] mTrans
		*    The current final transform matrix
		*
		*  @note
		*    - The scale can't be extracted correctly from the given transform matrix if one or
		*      two scale components are negative while another is/are not (we can't figure out
		*      WHICH axis are negative!)
		*/
		PLMATH_API void SetMatrix(const Matrix3x4 &mTrans);

		/**
		*  @brief
		*    Returns the current final inverse transform matrix
		*
		*  @return
		*    The current final inverse transform matrix
		*
		*  @note
		*    - If position, rotation or scale was changed, the current inverse transform matrix
		*      is recalculated internally before it is returned
		*/
		PLMATH_API const Matrix3x4 &GetInverseMatrix();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Flags which hold ínternal information
		*/
		enum EInternalFlags {
			RecalculateTransformMatrix		   = 1<<0,	/**< Recalculation of transform matrix required */
			RecalculateInverseTransformMatrix  = 1<<1	/**< Recalculation of inverse transform matrix required */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint8 m_nInternalFlags;	/**< Internal flags */
		Vector3			 m_vPosition;		/**< Position as vector */
		Quaternion		 m_qRotation;		/**< Rotation as quaternion */
		Vector3			 m_vScale;			/**< Scale as vector */
		Matrix3x4		 m_mTrans;			/**< Current final composed transform matrix */
		Matrix3x4		 m_mInvTrans;		/**< Current final composed inverse transform matrix */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLMath/Transform3.inl"


#endif // __PLMATH_TRANSFORM3_H__
