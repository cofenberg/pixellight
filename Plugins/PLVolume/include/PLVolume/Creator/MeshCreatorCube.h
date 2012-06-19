/*********************************************************\
 *  File: MeshCreatorCube.h                              *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


#ifndef __PLVOLUME_MESHCREATOR_CUBE_H__
#define __PLVOLUME_MESHCREATOR_CUBE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLMesh/Creator/MeshCreator.h>
#include "PLVolume/PLVolume.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class VertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Cube mesh creator class
*/
class MeshCreatorCube : public PLMesh::MeshCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUME_RTTI_EXPORT, MeshCreatorCube, "PLVolume", PLMesh::MeshCreator, "Cube mesh creator class")
		// Attributes
		pl_attribute(Dimension,	PLMath::Vector3,	PLMath::Vector3(1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Cube dimension",	"")
		pl_attribute(Offset,	PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Offset to center",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		MeshCreatorCube();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshCreatorCube();


	//[-------------------------------------------------------]
	//[ Private virtual PLMesh::MeshCreator functions         ]
	//[-------------------------------------------------------]
	private:
		virtual PLMesh::Mesh *Create(PLMesh::Mesh &cMesh, PLCore::uint32 nLODLevel = 0, bool bStatic = true) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_MESHCREATOR_CUBE_H__
