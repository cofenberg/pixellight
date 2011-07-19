/*********************************************************\
 *  File: Skeleton.cpp                                   *
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
#include "PLMesh/Joint.h"
#include "PLMesh/Skeleton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Skeleton::~Skeleton()
{
}


//[-------------------------------------------------------]
//[ Joints                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the skeleton root joint indices
*/
const Array<uint32> &Skeleton::GetRootJoints() const
{
	return m_lstRootJoints;
}

/**
*  @brief
*    Updates the joint information
*/
void Skeleton::UpdateJointInformation()
{
	// Check joints
	if (m_lstElements.GetNumOfElements()) {
		// Loop through all joints to count and reserve children
		uint32 nNumOfRootJoints = 0;
		for (uint32 i=0; i<m_lstElements.GetNumOfElements(); i++) {
			Joint *pJoint = m_lstElements[i];
			if (!m_lstElements[pJoint->GetParent()])
				nNumOfRootJoints++;
			uint32 nNumOfChildren = 0;
			for (uint32 j=0; j<m_lstElements.GetNumOfElements(); j++) {
				if (m_lstElements[j]->GetParent() == static_cast<int>(i))
					nNumOfChildren++;
			}
			pJoint->m_lstChildren.Resize(nNumOfChildren);
		}
		m_lstRootJoints.Resize(nNumOfRootJoints);
		nNumOfRootJoints = 0;

		// Loop through all joints to fill children
		for (uint32 i=0; i<m_lstElements.GetNumOfElements(); i++) {
			const Joint *pJoint = m_lstElements[i];
			if (!m_lstElements[pJoint->GetParent()])
				m_lstRootJoints[nNumOfRootJoints++] = i;
			uint32 nNumOfChildren = 0;
			for (uint32 j=0; j<m_lstElements.GetNumOfElements(); j++) {
				if (m_lstElements[j]->GetParent() == static_cast<int>(i)) {
					pJoint->m_lstChildren[nNumOfChildren] = j;
					nNumOfChildren++;
				}
			}
		}

		// Set initial absolute joint states
		// Loop through all root joints
		for (uint32 i=0; i<m_lstRootJoints.GetNumOfElements(); i++) {
			Joint *pJoint = m_lstElements[m_lstRootJoints[i]];
			if (pJoint)
				RecCalculateStates(*pJoint, nullptr);
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Skeleton::Skeleton(ResourceManager<Skeleton> &cManager, const String &sName) :
	Resource<Skeleton>(sName, &cManager), JointAni()
{
}

/**
*  @brief
*    Recursive joint state calculations
*/
void Skeleton::RecCalculateStates(Joint &cJoint, Joint *pParentJoint) const
{
	// Check and calculate states of this joint
	cJoint.CalculateInitialStates(pParentJoint);

	// Transform children
	for (uint32 i=0; i<cJoint.GetChildren().GetNumOfElements(); i++) {
		Joint *pJoint = m_lstElements[cJoint.GetChildren()[i]];
		if (pJoint)
			RecCalculateStates(*pJoint, &cJoint);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ElementManager functions      ]
//[-------------------------------------------------------]
Joint *Skeleton::CreateElement(const String &sName)
{
	return new Joint(sName, this);
}


//[-------------------------------------------------------]
//[ Public virtual AnimationInfo functions                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy operator
*/
Skeleton &Skeleton::operator =(const Skeleton &cSource)
{
	// Unload the skeleton
	Unload();

	// Call base function
	*static_cast<Resource<Skeleton>*>(this)    = cSource;
	*static_cast<ElementManager<Joint>*>(this) = cSource;

	// Call base functiona
	*static_cast<JointAni*>(this) = *static_cast<const JointAni*>(&cSource);

/* [TODO]
	// Copy data
	m_lstJoints.Resize(cSource.GetNumOfJoints(), false, false);
	for (uint32 i=0; i<cSource.GetNumOfJoints(); i++) {
		Joint *pJoint = new Joint();
		*pJoint = *cSource.GetJoint(i);
		m_lstJoints.Add(pJoint);
	}
	m_lstRootJoints = cSource.m_lstRootJoints;
	m_cAnimation = cSource.m_cAnimation;
*/

	// Return pointer
	return *this;
}

/**
*  @brief
*    Get the animation source name
*/
String Skeleton::GetSourceName() const
{
	// To implement in derived classes
	return GetName();
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool Skeleton::Unload()
{
	// Clear the skeleton
	ElementManager<Joint>::Clear();
	m_lstRootJoints.Clear();

	// Call base implementation
	return Resource<Skeleton>::Unload();
}

String Skeleton::GetLoadableTypeName() const
{
	static const String sString = "Skeleton";
	return sString;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
