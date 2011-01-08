/*********************************************************\
 *  File: MeshAnimationManagerHardware.cpp               *
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


// [TODO] Not implemented yet


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Animation/Animation.h>
#include "PLMesh/MeshAnimationManagerHardware.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshAnimationManagerHardware)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshAnimationManagerHardware::MeshAnimationManagerHardware()
{
}

/**
*  @brief
*    Destructor
*/
MeshAnimationManagerHardware::~MeshAnimationManagerHardware()
{
}


//[-------------------------------------------------------]
//[ Public virtual MeshAnimationManager functions         ]
//[-------------------------------------------------------]
bool MeshAnimationManagerHardware::Apply(MeshHandler &cMeshHandler) const
{
	// Call base implementation which calculates the current skeleton handler joint states
	if (!MeshAnimationManager::Apply(cMeshHandler))
		return false; // Error!

	// [TODO] Set shader parameters

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
