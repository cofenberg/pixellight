/*********************************************************\
 *  File: MeshLoaderOgreXML.cpp                          *
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
#include "PLAssimp/AssimpMeshLoader.h"
#include "PLAssimp/MeshLoader/MeshLoaderOgreXML.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMesh;
namespace PLAssimp {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshLoaderOgreXML)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderOgreXML::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderOgreXML::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Just let Assimp do all the hard work for us
	return AssimpMeshLoader().Load(cMesh, cFile, bStatic, "mesh.xml");
}

bool MeshLoaderOgreXML::Save(Mesh &cMesh, File &cFile)
{
	// Error - not implemented!
	return false;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshLoaderOgreXML::MeshLoaderOgreXML()
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderOgreXML::~MeshLoaderOgreXML()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp
