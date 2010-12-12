/*********************************************************\
 *  File: SceneLoaderX.h                                 *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLDEFAULTFILEFORMATS_DIRECTX_SCENELOADER_X_H__
#define __PLDEFAULTFILEFORMATS_DIRECTX_SCENELOADER_X_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneLoader/SceneLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class File;
}
namespace PLRenderer {
	class Material;
}
namespace PLScene {
	class SNMesh;
	class SceneContainer;
}
namespace PLDefaultFileFormats {
	class XNode;
	class XMesh;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene loader implementation for the x-format (DirectX)
*
*  @note
*    - Each single mesh is represented by it's own scene node
*/
class SceneLoaderX : public PLScene::SceneLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SceneLoaderX, "PLDefaultFileFormats", PLScene::SceneLoader, "Scene loader implementation for the x-format (DirectX)")
		pl_properties
			pl_property("Formats",	"x,X")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, PLScene::SceneContainer&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, PLScene::SceneContainer&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLScene::SceneContainer &cContainer, PLGeneral::File &cFile);
		bool Save(PLScene::SceneContainer &cContainer, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal per instance data
		*/
		struct SInstance {
			PLGeneral::Array<PLRenderer::Material*> lstMaterials;	/**< List of all materials */
			// Statistics
			PLGeneral::uint32 nTotalNumOfContainers;	/**< Total number of containers within the scene (without the root container itself) */
			PLGeneral::uint32 nTotalNumOfNodes;			/**< Total number of nodes (without containers) within the scene */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SceneLoaderX();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SceneLoaderX();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Processes a block of DirectX nodes
		*
		*  @param[in]  sInstance
		*    Per instance data
		*  @param[out] cContainer
		*    Scene container to load into
		*  @param[in]  pXNode
		*    Current X node, can be NULL
		*  @param[in]  sResourceName
		*    Desired resource name
		*/
		void ProcessNodes(SInstance &sInstance, PLScene::SceneContainer &cContainer, XNode *pXNode, const PLGeneral::String &sResourceName) const;

		/**
		*  @brief
		*    Processes a DirectX mesh block
		*
		*  @param[in]      sInstance
		*    Per instance data
		*  @param[in]      cXMesh
		*    Current X mesh node
		*  @param[in, out] cSceneNode
		*    Mesh scene node receiving the processed mesh
		*  @param[in]      sResourceName
		*    Desired resource name
		*/
		void ProcessMesh(SInstance &sInstance, XMesh &cXMesh, PLScene::SNMesh &cMeshSceneNode, const PLGeneral::String &sResourceName) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DIRECTX_SCENELOADER_X_H__
