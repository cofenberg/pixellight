/*********************************************************\
 *  File: JointState.cpp                                 *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMesh/JointState.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointState::JointState()
{
}

/**
*  @brief
*    Destructor
*/
JointState::~JointState()
{
}


//[-------------------------------------------------------]
//[ Data relative to the parent, if the joint has one     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gets the joint translation
*/
const Vector3 &JointState::GetTranslation() const
{
	return m_vTranslation;
}

/**
*  @brief
*    Sets the joint translation
*/
void JointState::SetTranslation(const Vector3 &vTranslation)
{
	m_vTranslation = vTranslation;
}

/**
*  @brief
*    Gets the joint rotation
*/
const Quaternion &JointState::GetRotation() const
{
	return m_qRotation;
}

/**
*  @brief
*    Sets the joint rotation
*/
void JointState::SetRotation(const Quaternion &qRotation)
{
	m_qRotation = qRotation;
}


//[-------------------------------------------------------]
//[ Absolute data                                         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gets the absolute joint translation
*/
const Vector3 &JointState::GetTranslationAbsolute() const
{
	return m_vTranslationAbsolute;
}

/**
*  @brief
*    Sets the absolute joint translation
*/
void JointState::SetTranslationAbsolute(const Vector3 &vTranslation)
{
	m_vTranslationAbsolute = vTranslation;
}

/**
*  @brief
*    Gets the absolute joint rotation
*/
const Quaternion &JointState::GetRotationAbsolute() const
{
	return m_qRotationAbsolute;
}

/**
*  @brief
*    Sets the absolute joint rotation
*/
void JointState::SetRotationAbsolute(const Quaternion &qRotation)
{
	m_qRotationAbsolute = qRotation;
}

/**
*  @brief
*    Gets the absolute joint matrix
*/
const Matrix3x4 &JointState::GetMatrixAbsolute() const
{
	return m_mTransAbsolute;
}

/**
*  @brief
*    Gets the transform joint matrix
*/
const Matrix3x3 &JointState::GetMatrixTransform() const
{
	return m_mTrans;
}


//[-------------------------------------------------------]
//[ Joint space data                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gets the joint space joint translation
*/
const Vector3 &JointState::GetTranslationJointSpace() const
{
	return m_vTranslationJointSpace;
}

/**
*  @brief
*    Sets the joint space joint translation
*/
void JointState::SetTranslationJointSpace(const Vector3 &vTranslation)
{
	m_vTranslationJointSpace = vTranslation;
}

/**
*  @brief
*    Gets the joint space joint rotation
*/
const Quaternion &JointState::GetRotationJointSpace() const
{
	return m_qRotationJointSpace;
}

/**
*  @brief
*    Sets the joint space joint rotation
*/
void JointState::SetRotationJointSpace(const Quaternion &qRotation)
{
	m_qRotationJointSpace = qRotation;
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
JointState &JointState::operator =(const JointState &cSource)
{
	// Copy data
	m_vTranslation			 = cSource.m_vTranslation;
	m_qRotation				 = cSource.m_qRotation;
	m_vTranslationAbsolute   = cSource.m_vTranslationAbsolute;
	m_qRotationAbsolute      = cSource.m_qRotationAbsolute;
	m_mTransAbsolute         = cSource.m_mTransAbsolute;
	m_vTranslationJointSpace = cSource.m_vTranslationJointSpace;
	m_qRotationJointSpace    = cSource.m_qRotationJointSpace;

	// Return this
	return *this;
}

/**
*  @brief
*    Compares two joint states
*/
bool JointState::operator ==(const JointState &cJointState) const
{
	return (m_vTranslation			 == cJointState.m_vTranslation			 &&
		    m_qRotation				 == cJointState.m_qRotation				 &&
		    m_vTranslationAbsolute	 == cJointState.m_vTranslationAbsolute	 &&
		    m_qRotationAbsolute		 == cJointState.m_qRotationAbsolute		 &&
		    m_mTransAbsolute		 == cJointState.m_mTransAbsolute		 &&
		    m_vTranslationJointSpace == cJointState.m_vTranslationJointSpace &&
		    m_qRotationJointSpace	 == cJointState.m_qRotationJointSpace);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Calculates the initial absolute translation and rotation states and the transform joint matrix
*/
bool JointState::CalculateInitialStates(const JointState *pParentJointState)
{
	// Is there a valid parent joint?
	if (pParentJointState) {
		// Transform relative state with the absolute state of the parent
		// Translation
		m_vTranslationAbsolute  = m_vTranslation;
		// [TODO] At the moment, Quaternion*Vector3 and Vector3*=Quaternion will return different results
//		m_vTranslationAbsolute  = pParentJointState->GetRotationAbsolute()*m_vTranslation;
		m_vTranslationAbsolute *= pParentJointState->GetRotationAbsolute();
		m_vTranslationAbsolute += pParentJointState->GetTranslationAbsolute();
		// Rotation
		m_qRotationAbsolute  = m_qRotation;
		m_qRotationAbsolute *= pParentJointState->GetRotationAbsolute();
	} else {
		// If there's no parent the absolute states are equal to the relative states
		m_vTranslationAbsolute = m_vTranslation;
		m_qRotationAbsolute    = m_qRotation;
	}

	// Generate the vertex transform matrix
	m_qRotationJointSpace.ToRotationMatrix(m_mTrans);

	// [TODO] Hm, why we need to transpose here??
	m_mTrans.Transpose();

//	m_mMatrixTransform = m_qRotationJointSpace;

	// Calculate absolute transform matrix
	m_mTransAbsolute.FromQuatTrans(m_qRotationAbsolute, m_vTranslationAbsolute);

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
