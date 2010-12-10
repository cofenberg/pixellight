/*********************************************************\
 *  File: SNMesh.h                                       *
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


#ifndef __PLSCENE_SCENENODE_MESH_H__
#define __PLSCENE_SCENENODE_MESH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    An mesh is a special scene node that has a 3D mesh attached to it by default
*
*  @note
*    - If 'Skin' is not empty and not a skin file, all materials are replaced through the new one
*    - By default, invisible scene nodes internally don't load in their mesh at once and delay this until
*      the scene node becomes visible and/or 'GetMeshHandler()' is called (use 'LoadAtOnce'-flag do force loading at once)
*    - For the debug visualization of normal vectors the config setting 'EngineDebugConfig->NormalScale' is
*      used to scale the length
*/
class SNMesh : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API static const PLGeneral::String IconMesh;	/**< 'Data/Textures/IconMesh.dds' string */

		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoAutomaticBoundingBox = 1<<10,	/**< Do not create the bounding box of the scene node automatically using the bounding box of the used mesh */
			LoadAtOnce			   = 1<<11,	/**< Load the mesh at once even if not used at the moment */
			DynamicMesh			   = 1<<12,	/**< Hint that this is a dynamic mesh, may have an impact on the performance */
			GenerateStrips		   = 1<<13,	/**< Generate triangle strips? (if possible, don't use this flag -> loading times...) */
			CalculateNormals	   = 1<<14,	/**< Calculate normal vectors? (if not already there) (if possible, don't use this flag -> loading times...) */
			CalculateTSVs		   = 1<<15	/**< Calculate tangent space vectors? (if not already there) (if possible, don't use this flag -> loading times...) */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(NoAutomaticBoundingBox,	"Do not create the bounding box of the scene node automatically using the bounding box of the used mesh")
			pl_enum_value(LoadAtOnce,				"Load the mesh at once even if not used at the moment")
			pl_enum_value(DynamicMesh,				"Hint that this is a dynamic mesh, may have an impact on the performance")
			pl_enum_value(GenerateStrips,			"Generate triangle strips? (if possible, don't use this flag -> loading times...)")
			pl_enum_value(CalculateNormals,			"Calculate normal vectors? (if not already there) (if possible, don't use this flag -> loading times...)")
			pl_enum_value(CalculateTSVs,			"Calculate tangent space vectors? (if not already there) (if possible, don't use this flag -> loading times...)")
		pl_enum_end

		/**
		*  @brief
		*    Scene node debug flags (SceneNode debug flags extension)
		*/
		enum EDebugFlags {
			// Mesh
			DebugShowWireframe      = 1<<8,		/**< Draw wireframe */
			DebugShowVertices       = 1<<9,		/**< Draw vertices */
			DebugShowTangents       = 1<<10,	/**< Draw tangents (red = x/u) */
			DebugShowBinormals      = 1<<11,	/**< Draw binormals (green = y/v) */
			DebugShowNormals        = 1<<12,	/**< Draw normals (blue = z/w) */
			DebugShowVertexNumbers  = 1<<13,	/**< Draw vertex numbers */
			// Skeleton (optional) information
			DebugShowJoints         = 1<<14,	/**< Draw joints */
			DebugShowJointNames     = 1<<15,	/**< Draw joint names */
			DebugShowSkeleton       = 1<<16,	/**< Draw skeleton */
			// Misc
			DebugShowAnchorPoints   = 1<<17		/**< Draw anchor points */
		};
		pl_enum(EDebugFlags)
			pl_enum_base(SceneNode::EDebugFlags)
			// Mesh
			pl_enum_value(DebugShowWireframe,		"Draw wireframe")
			pl_enum_value(DebugShowVertices,		"Draw vertices")
			pl_enum_value(DebugShowTangents,		"Draw tangents (red = x/u)")
			pl_enum_value(DebugShowBinormals,		"Draw binormals (green = y/v)")
			pl_enum_value(DebugShowNormals,			"Draw normals (blue = z/w)")
			pl_enum_value(DebugShowVertexNumbers,	"Draw vertex numbers")
			// Skeleton (optional) information
			pl_enum_value(DebugShowJoints,			"Draw joints")
			pl_enum_value(DebugShowJointNames,		"Draw joint names")
			pl_enum_value(DebugShowSkeleton,		"Draw skeleton")
			// Misc
			pl_enum_value(DebugShowAnchorPoints,	"Draw anchor points")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMesh, "PLScene", PLScene::SceneNode, "An mesh is a special scene node that has a 3D mesh attached to it by default")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Mesh,			PLGeneral::String,			"",			ReadWrite,	GetSet,		"Mesh to use",													"Type='Mesh'")
		pl_attribute(Skin,			PLGeneral::String,			"",			ReadWrite,	GetSet,		"Skin file overwriting the default materials of the used mesh",	"Type='Skin'")
		// Overwritten SceneNode variables
		pl_attribute(Icon,			PLGeneral::String,			IconMesh,	ReadWrite,	ModifyAttr,	"Scene node icon",												"Type='Material Effect Image TextureAni'")
		pl_attribute(Flags,			pl_flag_type(EFlags),		0,			ReadWrite,	GetSet,		"Flags",														"")
		pl_attribute(DebugFlags,	pl_flag_type(EDebugFlags),	0,			ReadWrite,	GetSet,		"Debug flags",													"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetMesh() const;
		PLS_API void SetMesh(const PLGeneral::String &sValue);
		PLS_API PLGeneral::String GetSkin() const;
		PLS_API void SetSkin(const PLGeneral::String &sValue);
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);	// From SceneNode


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNMesh();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMesh();

		/**
		*  @brief
		*    Loads a mesh
		*
		*  @param[in] sFilename
		*    Mesh filename to load
		*  @param[in] sParams
		*    Optional load method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the load method to use, can be an empty string
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If this entitiy is initialized the mesh defined in the entiy variable
		*      m_sMesh is loaded automatically
		*/
		PLS_API bool LoadMesh(const PLGeneral::String &sFilename, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");

		/**
		*  @brief
		*    Loads a skin
		*
		*  @param[in] sFilename
		*    Skin filename to load, if empty, the default materials of the given mesh are used
		*  @param[in] sParams
		*    Optional load method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the load method to use, can be an empty string
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLS_API bool LoadSkin(const PLGeneral::String &sFilename, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");

		/**
		*  @brief
		*    Saves the skin
		*
		*  @param[in] sFilename
		*    Skin filename
		*  @param[in] sParams
		*    Optional save method parameters, can be an empty string
		*  @param[in] sMethod
		*    Optional name of the save method to use, can be an empty string
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLS_API bool SaveSkin(const PLGeneral::String &sFilename, const PLGeneral::String &sParams = "", const PLGeneral::String &sMethod = "");

		/**
		*  @brief
		*    Unloads the current mesh
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLS_API bool UnloadMesh();

		/*
		*  @brief
		*    Returns the world position of a skeleton joint
		*
		*  @param[in]  sJointName
		*    Name of the skeleton joint to return the world position from
		*  @param[out] vPosition
		*    On success this will receive the world position of the requested skeleton joint
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (There's no mesh? There's no skeleton? There's no joint with the given name?)
		*/
		PLS_API bool GetSkeletonJointWorldPosition(const PLGeneral::String &sJointName, PLMath::Vector3 &vPosition);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    This function is called after the mesh handler loads a mesh
		*
		*  @note
		*    - Use e.g. to get animation information
		*/
		PLS_API virtual void MeshInitFunction();

		/**
		*  @brief
		*    This function is called after the mesh handler unloads a mesh
		*
		*  @note
		*    - The default implementation is empty
		*
		*  @see
		*    - MeshInitFunction()
		*/
		PLS_API virtual void MeshDeInitFunction();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String	   m_sMesh;				/**< Mesh to use */
		PLGeneral::String	   m_sSkin;				/**< Skin file overwriting the default materials of the used mesh */
		PLMesh::MeshHandler   *m_pMeshHandler;		/**< The mesh handler, can be NULL */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual PLMesh::MeshHandler *GetMeshHandler();
		PLS_API virtual void DrawDebug(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNode functions                 ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void DeInitFunction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_MESH_H__
