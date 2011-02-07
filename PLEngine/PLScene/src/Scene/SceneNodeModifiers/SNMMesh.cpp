/*********************************************************\
 *  File: SNMMesh.cpp                                    *
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
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMMesh)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMMesh::SNMMesh(SceneNode &cSceneNode) : SceneNodeModifier(cSceneNode)
{
}

/**
*  @brief
*    Destructor
*/
SNMMesh::~SNMMesh()
{
}

/**
*  @brief
*    Returns a "PLScene::SNMMeshUpdate" instance from the owner scene node
*/
SNMMeshUpdate *SNMMesh::GetSNMMeshUpdate() const
{
	// Is there already an instance of the "PLScene::SNMMeshUpdate" scene node modifier?
	const static String sSNMMeshUpdate = "PLScene::SNMMeshUpdate";
	SNMMeshUpdate *pSNMMeshUpdate = reinterpret_cast<SNMMeshUpdate*>(GetSceneNode().GetModifier(sSNMMeshUpdate));
	if (!pSNMMeshUpdate)
		pSNMMeshUpdate = reinterpret_cast<SNMMeshUpdate*>(GetSceneNode().AddModifier(sSNMMeshUpdate, "Flags=\"Automatic\""));

	// Return the SNMMeshUpdate instance
	return pSNMMeshUpdate;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
