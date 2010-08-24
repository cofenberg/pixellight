/*********************************************************\
 *  File: PLSceneMesh.h                                  *
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


#ifndef __PL_SCENEMESH_H__
#define __PL_SCENEMESH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <IGame/IGame.h>
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include <PLMesh/Loader/MeshFile.h>
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class FaceEx;
class PLScene;
class IGameNode;
class IGameMesh;
class morphChannel;
class IGameMaterial;
class PLSceneMaterial;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported mesh
*/
class PLSceneMesh {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLScene;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const char *SkeletonAnimation;		/**< Global skeleton animation name */
		static const char *MorphTargetAnimation;	/**< Global morph target animation name */
		static const char *PointCacheAnimation;		/**< Global point cache animation name */


	//[-------------------------------------------------------]
	//[ Public classes                                        ]
	//[-------------------------------------------------------]
	public:
		 // [TODO] Under construction
	// Animation
		struct FrameSpeed {
			int   nFrameID;
			float fSpeed;
		};
		struct Animation {
			PLMesh::MeshFile::Animation							sAnimation;		/**< General animation information */
			PLGeneral::Array<FrameSpeed*>						lstFrameSpeed;	/**< Frame speed */
			PLGeneral::Array<PLMesh::MeshFile::AnimationEvent*> lstEvents;		/**< Events */
			int nStartTime;
			int nEndTime;
			int nTicksPerFrame;
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the IGame node this mesh comes from
		*
		*  @return
		*    The IGame node this mesh comes from
		*/
		IGameNode &GetIGameNode() const;

		/**
		*  @brief
		*    Returns the 3ds Max object this mesh comes from
		*
		*  @return
		*    The 3ds Max object node this mesh comes from, NULL on error
		*/
		Object *Get3dsMaxObject() const;

		/**
		*  @brief
		*    Returns the mesh name
		*
		*  @return
		*    The mesh name
		*/
		const std::string &GetName() const;

		/**
		*  @brief
		*    Returns a list of all morph channels
		*
		*  @return
		*    A list of all morph channels
		*/
		const PLGeneral::Array<morphChannel*> &GetMorphChannels() const;

		/**
		*  @brief
		*    Returns the list of animations
		*
		*  @return
		*    The list of animation
		*/
		const PLGeneral::Array<Animation*> &GetAnimations() const;

		/**
		*  @brief
		*    Returns the list of materials
		*
		*  @return
		*    The list of materials
		*/
		const PLGeneral::Array<PLSceneMaterial*> &GetMaterials() const;


	//[-------------------------------------------------------]
	//[ Protected classes                                     ]
	//[-------------------------------------------------------]
	protected:
		class Weight {
			public:
			bool operator ==(const Weight &cWeight) const
			{
				return (nBone == cWeight.nBone && fWeight == cWeight.fWeight);
			}

			int nBone;
			float fWeight;

		};

		class Vertex {
			public:
			Vertex::Vertex() :
				nOrginal3dsMaxID(-1),
				xyz(0.0f, 0.0f, 0.0f),
				vNormal(0.0f, 0.0f, 0.0f),
				vTangent(0.0f, 0.0f, 0.0f),
				vBinormal(0.0f, 0.0f, 0.0f),
				nIndex(-1),
				nNumOfWeights(0)
			{
				for (int i=0; i<PLSceneExportOptions::MaxTexCoords; i++)
					vTexCoord[i].x = vTexCoord[i].y = vTexCoord[i].z = 0.0f;
				// We don't need to initialize 'cWeights'
			}
			void Reset()
			{
				nOrginal3dsMaxID = -1;
				xyz.x = xyz.y = xyz.z = 0.0f;
				vNormal.x = vNormal.y = vNormal.z = 0.0f;
				vTangent.x = vTangent.y = vTangent.z = 0.0f;
				vBinormal.x = vBinormal.y = vBinormal.z = 0.0f;
				for (int i=0; i<PLSceneExportOptions::MaxTexCoords; i++)
					vTexCoord[i].x = vTexCoord[i].y = vTexCoord[i].z = 0.0f;
				nIndex = -1;
				nNumOfWeights = 0;
				// We don't need to reset 'cWeights'
			}
			bool operator ==(const Vertex &cVertex) const
			{
				if (PLTools::Compare(xyz,           cVertex.xyz)       &&
					PLTools::Compare(vNormal,       cVertex.vNormal)   &&
					PLTools::Compare(vTangent,      cVertex.vTangent)  &&
					PLTools::Compare(vBinormal,     cVertex.vBinormal) &&
					nNumOfWeights == cVertex.nNumOfWeights) {
					for (int i=0; i<PLSceneExportOptions::MaxTexCoords; i++) {
						if (vTexCoord[i] != cVertex.vTexCoord[i])
							return false;
					}
					for (int i=0; i<PLSceneExportOptions::MaxVertexWeights; i++) {
						if (!(cWeights[i] == cVertex.cWeights[i]))
							return false;
					}
					return true;
				} else {
					return false;
				}
			}

			int nOrginal3dsMaxID;
			Point3 xyz;
			Point3 vNormal;
			Point3 vTangent;
			Point3 vBinormal;
			Point3 vTexCoord[PLSceneExportOptions::MaxTexCoords];
			int   nIndex;	// Used inside the vertex hash table
			int nNumOfWeights;
			Weight cWeights[PLSceneExportOptions::MaxVertexWeights];

		};

		// For vertex optimizing
		class VertexHashTable {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				/**
				*  @brief
				*    Constructor
				*
				*  @param[in] nSlots
				*    Number of slots
				*/
				VertexHashTable(int nSlots) :
					m_nSlots(nSlots), m_nVertices(0), m_plstSlots(new std::vector<Vertex*>[nSlots])
				{
				}

				/**
				*  @brief
				*    Destructor
				*/
				~VertexHashTable()
				{
					delete [] m_plstSlots;
				}

				/**
				*  @brief
				*    Returns the number of vertices
				*/
				int GetNumOfVertices() const
				{
					return m_nVertices;
				}

				/**
				*  @brief
				*    Clears the table
				*/
				void Clear()
				{
					m_nVertices = 0;
					for (int i=0; i<m_nSlots; i++)
						m_plstSlots[i].clear();
				}

				/**
				*  @brief
				*    Adds a vertex to the hash table
				*
				*  @param[in] cVertex
				*    Vertex to add (nIndex is only used internally!)
				*
				*  @return
				*    The vertex from the hash table, NULL on error
				*/
				Vertex *Add(Vertex &cVertex)
				{
					// Get key
					int nKey = GetKey(cVertex);
					std::vector<Vertex*> *plstSlot = &m_plstSlots[nKey];
					if (plstSlot) {
						// Check slot and collisions
						for (std::vector<Vertex*>::size_type i=0; i<plstSlot->size(); i++) {
							Vertex *pVer = (*plstSlot)[i];
							if (cVertex == *pVer) {
								// The vertex is already in the table!
								return pVer;
							}
						}

						// Add vertex to table
						plstSlot->push_back(&cVertex);
						cVertex.nIndex = m_nVertices++;

						// Return the index of the added vertex
						return &cVertex;
					} else {
						return NULL; // Error!
					}
				}


			//[-------------------------------------------------------]
			//[ Private functions                                     ]
			//[-------------------------------------------------------]
			private:
				/**
				*  @brief
				*    Gets the vertex key
				*
				*  @param[in] cVertex
				*    Vertex to compute the key from
				*
				*  @return
				*    Vertex key
				*/
				int GetKey(const Vertex &cVertex) const
				{
					return abs((int)(cVertex.vTexCoord[0].x*1350+
									 cVertex.vTexCoord[0].y*420)+
									 int(cVertex.xyz.x*303000)+
									 int(cVertex.xyz.y*750000)+
									 int(cVertex.xyz.z*574000)+
									 int(cVertex.vNormal.x*3000)+
									 int(cVertex.vNormal.y*7000)+
									 int(cVertex.vNormal.z*5000))%m_nSlots;
				}


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				int					  m_nSlots;		/**< Number of slots */
				int					  m_nVertices;	/**< Total number of vertices in the table */
				std::vector<Vertex*> *m_plstSlots;	/**< Collisions per slot */


		};

		struct Triangle {
			int v[3];
			int nMatID;
		};

		class Geometry {
			public:
			int nMaterial;
			int nStartIndex;
			int nIndexSize;
			Geometry::Geometry() :
				nMaterial(0), nStartIndex(0), nIndexSize(0)
			{
			}
			Geometry &operator =(const Geometry &cSource)
			{
				nMaterial   = cSource.nMaterial;
				nStartIndex = cSource.nStartIndex;
				nIndexSize  = cSource.nIndexSize;
				return *this;
			}
			bool operator ==(const Geometry &cGeometry) const
			{
				return (nMaterial   == cGeometry.nMaterial   &&
						nStartIndex == cGeometry.nStartIndex &&
						nIndexSize  == cGeometry.nIndexSize);
			}
			bool operator !=(const Geometry &cGeometry) const
			{
				return !(*this == cGeometry);
			}
		};


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cScene
		*    Scene this mesh is in
		*  @param[in] cIGameNode
		*    IGame node this scene node represents
		*  @param[in] sName
		*    Name of this mesh
		*/
		PLSceneMesh(PLScene &cScene, IGameNode &cIGameNode, const std::string &sName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneMesh();

		/**
		*  @brief
		*    Collects the mesh data
		*
		*  @param[in] cIGameObject
		*    IGameObject to use
		*/
		void CollectMeshData(IGameObject &cIGameObject);

		/**
		*  @brief
		*    Returns the correct material index of a face
		*
		*  @param[in] pIGameMaterial
		*    The IGame material, can be NULL
		*  @param[in] nFaceMaterialIndex
		*    Material index of the current face
		*
		*  @return
		*    The material index of the given face, < 0 on error
		*/
		int GetFaceMaterialIndex(IGameMaterial *pIGameMaterial, int nFaceMaterialIndex) const;

		/**
		*  @brief
		*    Returns a IGame material
		*
		*  @param[in] cIGameMesh
		*    IGame mesh to use
		*  @param[in] nFace
		*    Face index to get the IGame material from
		*
		*  @return
		*    The IGame material at the given index, NULL on error
		*/
		IGameMaterial *GetIGameMaterial(IGameMesh &cIGameMesh, int nFace) const;

		/**
		*  @brief
		*    Adds a material to the mesh
		*
		*  @param[in] pParentIGameMaterial
		*    Parent of the IGame material, can be NULL
		*  @param[in] pIGameMaterial
		*    IGame material to add, can be NULL
		*
		*  @return
		*    The index of the material within the mesh material list, < 0 on error
		*/
		int AddMaterial(IGameMaterial *pParentIGameMaterial, IGameMaterial *pIGameMaterial);

		/**
		*  @brief
		*    Get the vertex of a given vertex of a given face of the mesh
		*
		*  @param[in] cIGameMesh
		*    IGame mesh to use
		*  @param[in] pIGameSkin
		*    IGame skinning modifier, can be NULL
		*  @param[in] cFace
		*    Current face
		*  @param[in] nFaceVertexId
		*    Current face vertex
		*  @param[in] nMat
		*    Current material index
		*  @param[in] nFaceId
		*    Current face index
		*
		*  @return
		*    The vertex, NULL on error
		*/
		PLSceneMesh::Vertex *GetVertex(IGameMesh &cIGameMesh, IGameSkin *pIGameSkin, const FaceEx &cFace, int nFaceVertexId, int nMat, int nFaceId);

		/**
		* @brief
		*   Adds animations defined by using node tracks
		*
		*  @param[in] c3dsMaxNode
		*    3ds Max node to check for node tracks with animation information
		*/
		void AddNodeTrackAnimations(INode &c3dsMaxNode);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLScene							   *m_pScene;											/**< PL owner scene (always valid!) */
		IGameNode						   *m_pIGameNode;										/**< IGame node this scene node represents (always valid!) */
		Object							   *m_p3dsMaxObject;									/**< 3ds Max object node this scene node represents */
		std::string							m_sName;											/**< Name of this mesh */
		PLGeneral::Array<PLSceneMaterial*>	m_lstMaterials;										/**< List of materials (pointer to scene materials - do NOT delete!) */
		Box3								m_cLocalBox;										/**< Local bounding box */
		int									m_nNumOfVertices;									/**< Number of vertices */
		int									m_nOriginalNumOfVertices;							/**< Original number of vertices (hold for error checks...) */
		int									m_nNumOfTriangles;									/**< Number of triangles */
		int									m_nNumOfGeometries;									/**< Number of geometries */
		bool								m_bTexCoord[PLSceneExportOptions::MaxTexCoords];	/**< Texture coordinates filled or not? */
		PLGeneral::Array<morphChannel*>		m_lstMorphChannels;									/**< List of all morph channels (pointer to morph channels - do NOT delete!) */
		PLGeneral::Array<PLGeneral::String>	m_lstPointCaches;									/**< List of 'PointCache'-filenames (if there are any) */
		PLGeneral::uint32					m_nTotalNumOfVertexWeights;							/**< Total number of vertex weights */
		// Skeleton
		PLGeneral::Array<IGameNode*> m_lstBones;			/**< List of all bones, contains ONLY valid pointers! (pointer to scene nodes - do NOT delete!) */
		PLGeneral::Array<GMatrix>	 m_lstBonesInitPose;	/**< Initial transform of each bone */
		// Animation
		PLGeneral::Array<Animation*> m_lstAnimations;		/**< Animation list, destruction required */


};


#endif // __PL_SCENEMESH_H__
