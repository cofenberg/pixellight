/*********************************************************\
 *  File: SQEnumerate.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLScene/Scene/SceneQueries/SQEnumerate.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SQEnumerate)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SQEnumerate::SQEnumerate()
{
}

/**
*  @brief
*    Destructor
*/
SQEnumerate::~SQEnumerate()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Recursive part of PerformQuery()
*/
bool SQEnumerate::PerformQueryRec(const SceneContainer &cContainer)
{
	// Loop through all scene nodes
	for (uint32 i=0; i<cContainer.GetNumOfElements(); i++) {
		// Get the scene node
		SceneNode *pSceneNode = cContainer.GetByIndex(i);

		// Emit signal
		SignalSceneNode(*this, *pSceneNode);
		if (m_nFlags & StopQuery)
			return false; // Stop the query right now

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
bool SQEnumerate::PerformQuery()
{
	// Perform the query recursive...
	m_nFlags &= ~StopQuery;
	return PerformQueryRec(GetSceneContainer());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
