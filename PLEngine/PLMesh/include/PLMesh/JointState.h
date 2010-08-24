/*********************************************************\
 *  File: JointState.h                                   *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLMESH_JOINTSTATE_H__
#define __PLMESH_JOINTSTATE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix3x3.h>
#include <PLMath/Matrix3x4.h>
#include <PLMath/Quaternion.h>
#include "PLMesh/PLMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Joint state class
*/
class JointState {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Skeleton;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMESH_API JointState();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~JointState();

		//[-------------------------------------------------------]
		//[ Data relative to the parent, if the joint has one     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Gets the joint translation
		*
		*  @return
		*    Joint translation
		*/
		PLMESH_API const PLMath::Vector3 &GetTranslation() const;

		/**
		*  @brief
		*    Sets the joint translation
		*
		*  @param[in] vTranslation
		*    Joint translation
		*/
		PLMESH_API void SetTranslation(const PLMath::Vector3 &vTranslation);

		/**
		*  @brief
		*    Gets the joint rotation
		*
		*  @return
		*    Joint rotation
		*/
		PLMESH_API const PLMath::Quaternion &GetRotation() const;

		/**
		*  @brief
		*    Sets the joint rotation
		*
		*  @param[in] qRotation
		*    Joint rotation
		*/
		PLMESH_API void SetRotation(const PLMath::Quaternion &qRotation);

		//[-------------------------------------------------------]
		//[ Absolute data                                         ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Gets the absolute joint translation
		*
		*  @return
		*    Absolute joint translation
		*/
		PLMESH_API const PLMath::Vector3 &GetTranslationAbsolute() const;

		/**
		*  @brief
		*    Sets the absolute joint translation
		*
		*  @param[in] vTranslation
		*    Absolute joint translation
		*/
		PLMESH_API void SetTranslationAbsolute(const PLMath::Vector3 &vTranslation);

		/**
		*  @brief
		*    Gets the absolute joint rotation
		*
		*  @return
		*    Absolute joint rotation
		*/
		PLMESH_API const PLMath::Quaternion &GetRotationAbsolute() const;

		/**
		*  @brief
		*    Sets the absolute joint rotation
		*
		*  @param[in] qRotation
		*    Absolute joint rotation
		*/
		PLMESH_API void SetRotationAbsolute(const PLMath::Quaternion &qRotation);

		/**
		*  @brief
		*    Gets the absolute joint matrix
		*
		*  @return
		*    Absolute joint matrix
		*
		*  @note
		*    - This absolute transform matrix is created using the absolute joint
		*      translation and rotation.
		*/
		PLMESH_API const PLMath::Matrix3x4 &GetMatrixAbsolute() const;

		/**
		*  @brief
		*    Gets the transform joint matrix
		*
		*  @return
		*    Transform joint matrix
		*/
		PLMESH_API const PLMath::Matrix3x3 &GetMatrixTransform() const;

		//[-------------------------------------------------------]
		//[ Joint space data                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Gets the joint space joint translation
		*
		*  @return
		*    Joint space joint translation
		*/
		PLMESH_API const PLMath::Vector3 &GetTranslationJointSpace() const;

		/**
		*  @brief
		*    Sets the joint space joint translation
		*
		*  @param[in] vTranslation
		*    Joint space joint translation
		*/
		PLMESH_API void SetTranslationJointSpace(const PLMath::Vector3 &vTranslation);

		/**
		*  @brief
		*    Gets the joint space joint rotation
		*
		*  @return
		*    Joint space joint rotation
		*/
		PLMESH_API const PLMath::Quaternion &GetRotationJointSpace() const;

		/**
		*  @brief
		*    Sets the joint space joint rotation
		*
		*  @param[in] qRotation
		*    Joint space joint rotation
		*/
		PLMESH_API void SetRotationJointSpace(const PLMath::Quaternion &qRotation);

		//[-------------------------------------------------------]
		//[ Misc                                                  ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This joint state
		*/
		PLMESH_API JointState &operator =(const JointState &cSource);

		/**
		*  @brief
		*    Compares two joint states
		*
		*  @param[in] cJointState
		*    Joint state to compare with
		*
		*  @return
		*    'true' if both joint states are equal, else 'false'
		*/
		PLMESH_API bool operator ==(const JointState &cJointState) const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Data relative to the parent, if the joint has one
		PLMath::Vector3    m_vTranslation;				/**< Translation */
		PLMath::Quaternion m_qRotation;					/**< Rotation */
		// Absolute data
		PLMath::Vector3    m_vTranslationAbsolute;		/**< Absolute translation */
		PLMath::Quaternion m_qRotationAbsolute;			/**< Absolute rotation */
		PLMath::Matrix3x4  m_mTransAbsolute;			/**< Absolute transformation matrix */
		PLMath::Matrix3x3  m_mTrans;					/**< 3x3 orthonormal rotation matrix */
		// Joint space data
		PLMath::Vector3    m_vTranslationJointSpace;	/**< Joint space 3D translation vector */
		PLMath::Quaternion m_qRotationJointSpace;		/**< Joint space rotation */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Calculates the initial absolute translation and rotation states and the transform joint matrix
		*
		*  @param[in] pParentJointState
		*    Parent joint state, NULL if there's no one
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool CalculateInitialStates(const JointState *pParentJointState = NULL);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_JOINTSTATE_H__
