/*********************************************************\
 *  File: SQByName.cpp                                   *
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
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneQueries/SQByName.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SQByName)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SQByName::SQByName()
{
}

/**
*  @brief
*    Destructor
*/
SQByName::~SQByName()
{
}

/**
*  @brief
*    Returns the used regular expression
*/
const RegEx &SQByName::GetRegEx() const
{
	return m_cRegEx;
}

/**
*  @brief
*    Sets the used regular expression
*/
void SQByName::SetRegEx(const RegEx &cRegEx)
{
	m_cRegEx = cRegEx;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Recursive part of PerformQuery()
*/
bool SQByName::PerformQueryRec(const SceneContainer &cContainer)
{
	// Loop through all scene nodes
	for (uint32 i=0; i<cContainer.GetNumOfElements(); i++) {
		// Get the scene node
		SceneNode *pSceneNode = cContainer.Get(i);

		// Does the name of this scene node match the given regular expression?
		if (m_cRegEx.Match(pSceneNode->GetName())) {
			// Emit event
			EventSceneNode(*this, *pSceneNode);
			if (m_nFlags & StopQuery)
				return false; // Stop the query right now
		}

		// Is this a container and is recursion allowed?
		if ((m_nFlags & Recursive) && pSceneNode->IsContainer() && !(pSceneNode->GetFlags() & SceneContainer::NoRecursion)) {
			// Container recursion
			if (!PerformQueryRec(static_cast<SceneContainer&>(*pSceneNode)))
				return false; // Stop the query right now
		}
	}

	// Done, continue the query
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual SceneQuery functions                   ]
//[-------------------------------------------------------]
bool SQByName::PerformQuery()
{
	// Perform the query recursive...
	m_nFlags &= ~StopQuery;
	return PerformQueryRec(GetSceneContainer());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
