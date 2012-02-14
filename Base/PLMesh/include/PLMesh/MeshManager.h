/*********************************************************\
 *  File: MeshManager.h                                  *
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


#ifndef __PLMESH_MESHMANAGER_H__
#define __PLMESH_MESHMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/ResourceManager.h>
#include "PLMesh/MeshHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This is a manager for the mesh resource
*
*  @note
*    - Unloads unused resources automatically by default
*/
class MeshManager : public PLCore::ResourceManager<Mesh> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		PLMESH_API MeshManager(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshManager();

		/**
		*  @brief
		*    Returns the used renderer
		*
		*  @return
		*    Pointer to the renderer the meshes should use, can be a null pointer
		*/
		PLMESH_API PLRenderer::Renderer *GetRenderer() const;

		/**
		*  @brief
		*    Creates the mesh and adds the required LODs
		*
		*  @return
		*   The created mesh, a null pointer on error
		*
		*  @note
		*    - If the mesh is created, the 'Material' is added automatically
		*/
		PLMESH_API Mesh *CreateMesh();

		/**
		*  @brief
		*    Creates a new mesh resource
		*
		*  @param[in] sName
		*    Resource name, if empty an unused name is set automatically
		*  @param[in] bStatic
		*    Static mesh? (better performance!)
		*
		*  @return
		*    Pointer to the created resource, a null pointer if there was an error
		*
		*  @note
		*    - If there's already a resource with this name, this resource is returned
		*/
		PLMESH_API Mesh *CreateMesh(const PLCore::String &sName, bool bStatic = true);

		/**
		*  @brief
		*    Creates a mesh resource using a mesh creator
		*
		*  @param[in] sName
		*    Mesh creator class name (for instance "MeshCreatorSphere")
		*  @param[in] bStatic
		*    Static mesh? (better performance!)
		*  @param[in] sParameters
		*    Mesh creator parameters. (for instance "Radius='4.0' Detail='20'")
		*    This parameters depend on the used mesh creator.
		*
		*  @return
		*    Pointer to the created resource, a null pointer if there was an error
		*    (maybe unknown class or the class is not derived from 'MeshCreator')
		*/
		PLMESH_API Mesh *CreateMesh(const PLCore::String &sName, bool bStatic, const PLCore::String &sParameters);

		/**
		*  @brief
		*    Load mesh
		*
		*  @param[in] sFilename
		*    Mesh filename. It's also possible to create meshes dynamically.
		*    "Create MeshCreatorSphere Name=\"Sphere\" Radius=\"4.0\" Detail=\"20.0\""
		*    For instance will use the mesh creator class 'MeshCreatorSphere'
		*    to create a mesh with the name 'Sphere' and some parameters.
		*  @param[in] sParams
		*    Optional load method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the load method to use, can be an empty string
		*  @param[in] bReloadMesh
		*    Force mesh itself to be reloaded?
		*  @param[in] bStatic
		*    Static mesh? (better performance!)
		*
		*  @return
		*    The loaded mesh, a null pointer on error
		*/
		PLMESH_API Mesh *LoadMesh(const PLCore::String &sFilename, const PLCore::String &sParams = "", const PLCore::String &sMethod = "", bool bReloadMesh = false, bool bStatic = true);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer *m_pRenderer;	/**< Renderer the manager is using (always valid!) */


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual Mesh *CreateResource(const PLCore::String &sName) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHMANAGER_H__
