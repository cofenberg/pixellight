/*********************************************************\
 *  File: PLScene.h                                      *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PL_SCENE_H__
#define __PL_SCENE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PL3dsMaxSceneExport/PLScenePLMesh.h"
#include "PL3dsMaxSceneExport/PLSceneContainer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Interface;
class IGameScene;
class IGameMaterial;
class PLSceneObject;
class PLSceneTexture;
class PLSceneMaterial;
namespace PLCore {
	class XmlDocument;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight scene
*/
class PLScene : public PLSceneContainer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLSceneMesh;
	friend class PLSceneLight;
	friend class PLScenePLMesh;
	friend class PLSceneObject;
	friend class PLSceneContainer;
	friend class PLSceneMaterialBakeShell;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cMaxInterface
		*    3ds Max interface
		*  @param[in] cIGame
		*    IGame interface
		*  @param[in] nProgressMin
		*    Minimum progress (start)
		*  @param[in] nProgressMin
		*    Maximum progress (end)
		*  @param[in] szApplicationDrive
		*    Application drive
		*  @param[in] szApplicationDir
		*    Application directory
		*/
		PLScene(Interface &cMaxInterface, IGameScene &cIGame, int nProgressMin, int nProgressMax, const char szApplicationDrive[], const char szApplicationDir[]);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLScene();

		/**
		*  @brief
		*    Returns the 3ds Max interface
		*
		*  @return
		*    The 3ds Max interface
		*/
		Interface &GetMaxInterface() const;

		/**
		*  @brief
		*    Returns the IGame interface
		*
		*  @return
		*    The IGame interface
		*/
		IGameScene &GetIGameInterface() const;

		/**
		*  @brief
		*    Returns the total number of 3ds Max nodes
		*
		*  @return
		*    The total number of 3ds Max nodes
		*/
		int GetTotalNumOfMaxNodes() const;

		/**
		*  @brief
		*    Returns the current number of 3ds Max nodes
		*
		*  @return
		*    The current number of 3ds Max nodes
		*/
		int GetNumOfMaxNodes() const;

		/**
		*  @brief
		*    Returns the a pointer to the PL scene node of a given 3ds Max node
		*
		*  @param[in] cMaxNode
		*    3ds Max node
		*
		*  @return
		*    The PL scene node, a null pointer on error
		*/
		PLSceneNode *GetPLSceneNode(INode &cMaxNode);

		//[-------------------------------------------------------]
		//[ Meshes                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Adds a mesh to the scene
		*
		*  @param[in] cIGameNode
		*    IGame node this scene node represents
		*  @param[in] sMeshName
		*    Mesh name
		*
		*  @return
		*    The added mesh, a null pointer on error
		*
		*  @remarks
		*    If there's already a mesh with the same name within the scene, this mesh
		*    is returned instead creating a new one.
		*/
		PLScenePLMesh *AddMesh(IGameNode &cIGameNode, const PLCore::String &sMeshName);

		//[-------------------------------------------------------]
		//[ Materials                                             ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Copies a texture
		*
		*  @param[in] sFilename
		*    Filename of the texture to copy
		*  @param[in] bNormalMap_xGxR
		*    Is this a 'xGxR' normal map?
		*
		*  @return
		*    Resulting PixelLight texture object, a null pointer on error
		*
		*  @remarks
		*    The given texture will be copied into the target scene directory given be the options. If there's
		*    already such a texture, this old texture is only overwritten if the other is newer. Textures are
		*    only copied if this is activated within the options.
		*/
		PLSceneTexture *CopyTexture(const PLCore::String &sFilename, bool bNormalMap_xGxR = false);

		/**
		*  @brief
		*    Writes the scene into a XML document
		*
		*  @param[in] cDocument
		*    Scene XML document to insert into
		*/
		void WriteToXMLDocument(PLCore::XmlDocument &cDocument);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Gets a PixelLight material
		*
		*  @param[in] cMaxMaterial
		*    3ds Max material to return the PixelLight material from
		*
		*  @return
		*    The PixelLight material, a null pointer on error
		*/
		PLSceneMaterial *GetMaterial(Mtl &cMaxMaterial) const;

		/**
		*  @brief
		*    Adds a material to the scene
		*
		*  @param[in] pParentIGameMaterial
		*    Parent of the IGame, can be a null pointer
		*  @param[in] cIGameMaterial
		*    IGame material to add
		*
		*  @return
		*    The scene material, a null pointer on error
		*/
		PLSceneMaterial *AddMaterial(IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial);

		/**
		*  @brief
		*    Adds a color material to the scene
		*
		*  @param[in] cColor
		*    Color to use
		*  @param[in] sName
		*    Material name
		*
		*  @return
		*    The scene material, a null pointer on error
		*/
		PLSceneMaterial *AddMaterial(const Color &cColor, const PLCore::String &sName);

		/**
		*  @brief
		*    Updates the total mesh statistics
		*
		*  @param[in] cMesh
		*    New mesh
		*/
		void UpdateTotalMeshStatistics(const PLScenePLMesh &cMesh);

		/**
		*  @brief
		*    Reads the value as string of the 'summary' file properties
		*
		*  @param[in] cSceneElement
		*    Scene XML element to insert into
		*  @param[in] nSet
		*    Property set to read from
		*  @param[in] nType
		*    Property type to read from
		*  @param[in] szName
		*    Name of the property written into the file
		*/
		void GetSummaryPropertyValue(PLCore::XmlElement &cSceneElement, int nSet, int nType, const TCHAR szName[]) const;

		/**
		*  @brief
		*    Exports the 'start camera'
		*
		*  @param[in] cSceneElement
		*    Scene XML element to insert into
		*/
		void ExportStartCamera(PLCore::XmlElement &cSceneElement);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Mesh statistics
		*/
		struct SMeshStatistics {
			// Materials
			int nNumOfTextureReferences;	/**< Number of texture references */
			int nNumOfMaterialReferences;	/**< Number of material references */
			// Unique meshes
			int nNumOfMeshes;				/**< Number of unique meshes */
			int nNumOfMeshVertices;			/**< Number of unique mesh vertices */
			int nNumOfMeshIndices;			/**< Number of unique mesh indices */
			int nNumOfMeshTriangles;		/**< Number of unique mesh triangles */
			int nNumOfMeshGeometries;		/**< Number of unique mesh geometries */
			// Total meshes
			int nTotalNumOfMeshes;			/**< Total number of meshes */
			int nTotalNumOfMeshVertices;	/**< Total number of mesh vertices */
			int nTotalNumOfMeshIndices;		/**< Total number of mesh indices */
			int nTotalNumOfMeshTriangles;	/**< Total number of mesh triangles */
			int nTotalNumOfMeshGeometries;	/**< Total number of mesh geometries */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Interface								 *m_pMaxInterface;			/**< 3ds Max interface (always valid!) */
		IGameScene								 *m_pIGame;					/**< IGame interface (always valid!) */
		int										  m_nTotalNumOfMaxNodes;	/**< Total number of 3ds Max nodes */
		int										  m_nNumOfMaxNodes;			/**< Current number of 3ds Max nodes */
		int										  m_nProgressMin;			/**< Minimum progress (start) */
		int										  m_nProgressMax;			/**< Maximum progress (end) */
		int										  m_nProgress;				/**< Current progress */
		PLCore::String							  m_sApplicationDrive;		/**< Application drive */
		PLCore::String							  m_sApplicationDir;		/**< Application directory */
		std::vector<PLScenePLMesh*>				  m_lstMeshes;				/**< List of meshes */
		std::vector<PLSceneTexture*>			  m_lstTextures;			/**< List of textures */
		std::vector<PLSceneMaterial*>			  m_lstMaterials;			/**< List of materials */
		std::map<PLCore::String, PLScenePLMesh*>  m_mapMeshes;				/**< Map with mesh references */
		std::map<PLCore::String, PLSceneNode*>    m_mapMaxToPLNodes;		/**< Map with Max to PL node references */

		// Statistics
		SStatistics	    m_sSceneStatistics;	/**< Scene statistics */
		SMeshStatistics m_sMeshStatistics;	/**< Mesh statistics */
		int				m_nTotalNumOfNodes;	/**< Total number of nodes */

		// For PLSceneMesh
		int							  m_nMaxMeshVertices;
		PLSceneMesh::Vertex			 *m_pMeshVertices;		/**< Always valid! */
		PLSceneMesh::VertexHashTable *m_pVHTable;			/**< Always valid! */
		bool						  m_bVHTableUsed;
		int							  m_nMaxMeshTriangles;
		PLSceneMesh::Triangle		 *m_pMeshTriangles;		/**< Always valid! */
		int							  m_nMaxMeshGeometries;
		PLSceneMesh::Geometry		 *m_pMeshGeometries;	/**< Always valid! */


	//[-------------------------------------------------------]
	//[ Public virtual PLSceneContainer functions             ]
	//[-------------------------------------------------------]
	public:
		virtual bool AddIGameNode(IGameNode &cIGameNode) override;
		virtual void PostProcess() override;
		virtual void OutputStatistics() override;


};


#endif // __PL_SCENE_H__
