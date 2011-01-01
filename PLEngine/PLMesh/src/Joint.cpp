/*********************************************************\
 *  File: Joint.cpp                                      *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Joint::Joint(const String &sName, ElementManager<Joint> *pManager) : Element<Joint>(sName, pManager),
	m_nID(-1),
	m_nParent(-1)
{
}

/**
*  @brief
*    Destructor
*/
Joint::~Joint()
{
}

/**
*  @brief
*    Get the ID of this joint
*/
int Joint::GetID() const
{
	return m_nID;
}

/**
*  @brief
*    Set the ID this joint
*/
void Joint::SetID(int nID)
{
	m_nID = nID;
}

/**
*  @brief
*    Get the parent joint number of this joint
*/
int Joint::GetParent() const
{
	return m_nParent;
}

/**
*  @brief
*    Set the parent joint number of this joint
*/
void Joint::SetParent(int nParent)
{
	m_nParent = nParent;
}

/**
*  @brief
*    Gets an array with the child joints
*/
const Array<uint32> &Joint::GetChildren() const
{
	return m_lstChildren;
}

/**
*  @brief
*    Copy operator
*/
Joint &Joint::operator =(const Joint &cSource)
{
	// Copy data
	m_nID		  = cSource.m_nID;
	m_nParent	  = cSource.m_nParent;
	m_lstChildren = cSource.m_lstChildren;

	// Return this
	return *this;
}

/**
*  @brief
*    Compares two joints
*/
bool Joint::operator ==(const Joint &cJoint) const
{
	return (m_nID		  == cJoint.m_nID	  &&
		    m_nParent	  == cJoint.m_nParent &&
		    m_lstChildren == cJoint.m_lstChildren);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
