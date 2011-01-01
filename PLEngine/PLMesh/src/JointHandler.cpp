/*********************************************************\
 *  File: JointHandler.cpp                               *
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
#include "PLMesh/JointHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
JointHandler::JointHandler() :
	m_bUserControlled(false)
{
}

/**
*  @brief
*    Destructor
*/
JointHandler::~JointHandler()
{
}

/**
*  @brief
*    Returns whether or not this joint is user controlled
*/
bool JointHandler::IsUserControlled() const
{
	return m_bUserControlled;
}

/**
*  @brief
*    Sets whether or not this joint is user controlled
*/
void JointHandler::SetUserControlled(bool bUserControlled)
{
	m_bUserControlled = bUserControlled;
}

/**
*  @brief
*    Calculates the current absolute translation and rotation states and the
*    transform joint matrix
*/
bool JointHandler::CalculateStates(const JointHandler *pJointHandler)
{
	// Get joint
	const Joint *pJoint = GetElement();
	if (pJoint) {
		// Is there a valid parent joint?
		if (!m_bUserControlled) {
			const Joint *pParentJoint = pJointHandler ? pJointHandler->GetElement() : NULL;
			if (pParentJoint) {
				// Valid parent?
				if (pParentJoint->GetID() == pJoint->GetParent()) {
					// Transform relative state with the absolute state of the parent
					// Translation
					m_vTranslationAbsolute  = m_vTranslation;
					// [TODO] At the moment, Quaternion*Vector3 and Vector3*=Quaternion will return different results
					m_vTranslationAbsolute *= pJointHandler->GetRotationAbsolute();
		//			m_vTranslationAbsolute = pJointHandler->GetRotationAbsolute()*m_vTranslation;
					m_vTranslationAbsolute += pJointHandler->GetTranslationAbsolute();
					// Rotation
					m_qRotationAbsolute  = m_qRotation;
					m_qRotationAbsolute *= pJointHandler->GetRotationAbsolute();
				}
			} else {
				// If there's no parent the absolute states are equal to the relative states
				m_vTranslationAbsolute = m_vTranslation;
				m_qRotationAbsolute    = m_qRotation;
			}
		}

		// Calculate the joint space transformation
		// Translation
		m_vTranslationJointSpace  = pJoint->GetTranslationJointSpace();
		// [TODO] At the moment, Quaternion*Vector3 and Vector3*=Quaternion will return different results
		m_vTranslationJointSpace *= m_qRotationAbsolute;
	//	m_vTranslationJointSpace  = m_qRotationAbsolute*pJoint->GetTranslationJointSpace();
		m_vTranslationJointSpace += m_vTranslationAbsolute;
		// Rotation
		m_qRotationJointSpace     = pJoint->GetRotationJointSpace();
		m_qRotationJointSpace    *= m_qRotationAbsolute;

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

	// Error!
	return false;
}

/**
*  @brief
*    Copy operator
*/
JointHandler &JointHandler::operator =(const JointHandler &cSource)
{
	// Set element
	SetElement(cSource.GetElement());

	// Copy joint state
	m_bUserControlled    = cSource.m_bUserControlled;
	*((JointState*)this) = *((const JointState*)&cSource);

	// Return this
	return *this;
}

/**
*  @brief
*    Compares two joint handlers
*/
bool JointHandler::operator ==(const JointHandler &cJointHandler) const
{
	// Compare element and joint state
	return (GetElement() == cJointHandler.GetElement()			 &&
		    m_bUserControlled == cJointHandler.m_bUserControlled &&
		    *((const JointState*)this) == *((const JointState*)&cJointHandler));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
