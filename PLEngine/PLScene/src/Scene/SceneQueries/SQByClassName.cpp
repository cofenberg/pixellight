/*********************************************************\
 *  File: SQByClassName.cpp                              *
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
#include "PLScene/Scene/SceneQueries/SQByClassName.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SQByClassName)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SQByClassName::SQByClassName()
{
}

/**
*  @brief
*    Destructor
*/
SQByClassName::~SQByClassName()
{
}

/**
*  @brief
*    Returns the used regular expression
*/
const RegEx &SQByClassName::GetRegEx() const
{
	return m_cRegEx;
}

/**
*  @brief
*    Sets the used regular expression
*/
void SQByClassName::SetRegEx(const RegEx &cRegEx)
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
bool SQByClassName::PerformQueryRec(const SceneContainer &cContainer)
{
	// Loop through all scene nodes
	for (uint32 i=0; i<cContainer.GetNumOfElements(); i++) {
		// Get the scene node
		SceneNode *pSceneNode = cContainer.Get(i);

		// Does the class name of this scene node match the given regular expression?
		if (m_cRegEx.Match(pSceneNode->GetClass()->GetClassName())) {
			// Emit event
			EventSceneNode.Emit(*this, *pSceneNode);
			if (m_nFlags & StopQuery)
				return false; // Stop the query right now
		} else {
			// Take base classes into account, too?
			if (!(GetFlags() & IgnoreBaseClasses)) {
				// Get the base class
				const Class *pClass = pSceneNode->GetClass()->GetBaseClass();
				while (pClass) {
					// Does the name of this class match the given regular expression?
					if (m_cRegEx.Match(pClass->GetClassName())) {
						// Emit event
						EventSceneNode.Emit(*this, *pSceneNode);
						if (m_nFlags & StopQuery)
							return false; // Stop the query right now

						// We're done
						pClass = NULL;
					} else {
						// Next base class, please
						pClass = pClass->GetBaseClass();
					}
				}
			}
		}

		// Is this a container and is recursion allowed?
		if ((m_nFlags & Recursive) && pSceneNode->IsContainer() && !(pSceneNode->GetFlags() & SceneContainer::NoRecursion)) {
			// Container recursion
			if (!PerformQueryRec((SceneContainer&)*pSceneNode))
				return false; // Stop the query right now
		}
	}

	// Done, continue the query
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual SceneQuery functions                   ]
//[-------------------------------------------------------]
bool SQByClassName::PerformQuery()
{
	// Perform the query recursive...
	m_nFlags &= ~StopQuery;
	return PerformQueryRec(GetSceneContainer());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
