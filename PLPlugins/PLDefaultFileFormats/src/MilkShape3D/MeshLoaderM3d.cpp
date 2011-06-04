/*********************************************************\
 *  File: MeshLoaderM3d.cpp                              *
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
#include <PLGeneral/String/Tokenizer.h>
#include <PLMath/Vector2.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/MilkShape3D/MeshLoaderM3d.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshLoaderM3d)


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
namespace M3d {
/**
*  @brief
*    Material
*/
struct Material {
	String sTexture;	/**< Material texture */
};

/**
*  @brief
*    Vertex
*/
struct Vertex {
	float fX, fY, fZ, fS, fT;
};

/**
*  @brief
*    Normal
*/
struct Normal {
	float fX, fY, fZ;
};

/**
*  @brief
*    Face
*/
struct Face {
	uint32 nMeshID;
	uint32 nVertex[3];
	uint32 nNormal[3];
	uint32 nMaterial;
};


//[-------------------------------------------------------]
//[ Optimization                                          ]
//[-------------------------------------------------------]
/**
*  @brief
*    For vertex optimizing
*/
class VertexTex {
	public:
	uint32 nVertex;			/**< Vertex ID */
	float  fX, fY, fZ;		/**< Coordinate */
	float  fNX, fNY, fNZ;	/**< Normal */
	float  fS, fT;			/**< Texture coordinate */
	uint32 nIndex;			/**< Used inside the vertex hash table */
	VertexTex &operator =(const VertexTex &cSource)
	{
		// We do not need an implementation in here...
		return *this;
	}
	bool operator ==(const VertexTex &cVertex) const
	{
		// We do not need an implementation in here...
		return false;
	}
};

/**
*  @brief
*    For vertex optimizing
*/
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
		VertexHashTable(uint32 nSlots) :
			m_nSlots(nSlots),
			m_nVertices(0),
			m_plstSlots(new List<VertexTex>[nSlots])
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
		*    Adds a vertex to the hash table
		*
		*  @param[in] cVertex
		*    Vertex to add (nIndex is only used internally!)
		*
		*  @return
		*    The vertex from the hash table
		*/
		VertexTex *Add(VertexTex &cVertex)
		{
			// Get key
			uint32 nKey = GetKey(cVertex);
			List<VertexTex> &cSlot = m_plstSlots[nKey];

			// Check if the vertex is already in the hash table
			if (m_plstSlots[nKey].GetNumOfElements()) {
				// Check slot and collisions
				for (uint32 i=0; i<cSlot.GetNumOfElements(); i++) {
					VertexTex &cVer = cSlot[i];
					if (cVer.fX  == cVertex.fX  &&
						cVer.fY  == cVertex.fY  &&
						cVer.fZ  == cVertex.fZ  &&
						cVer.fNX == cVertex.fNX &&
						cVer.fNY == cVertex.fNY &&
						cVer.fNZ == cVertex.fNZ &&
						cVer.fS  == cVertex.fS  &&
						cVer.fT  == cVertex.fT) {
						// The vertex is already in the table!
						return &cVer;
					}
				}
			}

			// Add vertex to table
			VertexTex &cVer = cSlot.Add();
			cVer.nVertex  = cVertex.nVertex;
			cVer.fX       = cVertex.fX;
			cVer.fY       = cVertex.fY;
			cVer.fZ       = cVertex.fZ;
			cVer.fNX      = cVertex.fNX;
			cVer.fNY      = cVertex.fNY;
			cVer.fNZ      = cVertex.fNZ;
			cVer.fS       = cVertex.fS;
			cVer.fT       = cVertex.fT;
			cVer.nIndex   = m_nVertices++;

			// Return the index of the added vertex
			return &cVer;
		}


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32			 m_nSlots;		/**< Number of slots */
		uint32			 m_nVertices;	/**< Total number of vertices in the table */
		List<VertexTex> *m_plstSlots;	/**< Collisions per slot */


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
		uint32 GetKey(VertexTex &cVertex)
		{
			return Math::Abs(static_cast<int>(cVertex.fX*10+cVertex.fY*100+cVertex.fZ*112+
							 cVertex.fS*123+cVertex.fT*42))%m_nSlots;
		}


};
} // M3d


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderM3d::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderM3d::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n()[]=,;\"");
	cTokenizer.SetSingleChars("{}");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCaseSensitive(true);

	bool   bMergeMeshes = false;	/**< Merge the meshes where possible to one mesh? */
	uint32 nNumOfMeshes = 0;		/**< Number of read meshes */

	Array<M3d::Material*> lstMaterials;
	Array<M3d::Vertex*> lstVertices;
	Array<M3d::Normal*> lstNormals;
	Array<M3d::Face*> lstFaces;

	// Read file
	while (cTokenizer.GetNextToken().GetLength()) {
		// Meshes:
		if (cTokenizer.CompareToken("Meshes:")) {
			uint32 nStartVertex = 0, nStartNormal = 0;

			// Get number of meshes
			nNumOfMeshes = cTokenizer.GetNextToken().GetInt();

			// Parse meshes
			for (uint32 nMesh=0; nMesh<nNumOfMeshes; nMesh++) {
				// Get geometry information
				cTokenizer.GetNextToken(); // Ingnore the mesh name
				cTokenizer.GetNextToken(); // Ingnore the next number
				uint32 nMaterial = cTokenizer.GetNextToken().GetInt();

				// Get number of vertices
				uint32 nNumOfVertices = cTokenizer.GetNextToken().GetInt();

				// Read vertices
				for (uint32 nVertex=0; nVertex<nNumOfVertices; nVertex++) {
					M3d::Vertex *pVertex = new M3d::Vertex;

					cTokenizer.GetNextToken(); // Ingnore the next number
					pVertex->fX = cTokenizer.GetNextToken().GetFloat();
					pVertex->fY = cTokenizer.GetNextToken().GetFloat();
					pVertex->fZ = cTokenizer.GetNextToken().GetFloat();
					pVertex->fS = cTokenizer.GetNextToken().GetFloat();
					pVertex->fT = cTokenizer.GetNextToken().GetFloat();
					cTokenizer.GetNextToken(); // Ingnore the next number

					// Add vertex to temp list
					lstVertices.Add(pVertex);
				}

				// Get number of normals
				uint32 nNumOfNormals = cTokenizer.GetNextToken().GetInt();

				// Read normals
				for (uint32 nNormal=0; nNormal<nNumOfNormals; nNormal++) {
					M3d::Normal *pNormal = new M3d::Normal;

					pNormal->fX = cTokenizer.GetNextToken().GetFloat();
					pNormal->fY = cTokenizer.GetNextToken().GetFloat();
					pNormal->fZ = cTokenizer.GetNextToken().GetFloat();

					// Add normal to temp list
					lstNormals.Add(pNormal);
				}

				// Get number of faces
				uint32 nNumOfFaces = cTokenizer.GetNextToken().GetInt();

				// Read faces
				for (uint32 nFace=0; nFace<nNumOfFaces; nFace++) {
					// Get face
					M3d::Face *pFace = new M3d::Face;
					pFace->nMeshID = nMesh;

					cTokenizer.GetNextToken(); // Ingnore the next number
					pFace->nVertex[0] = cTokenizer.GetNextToken().GetInt();
					pFace->nVertex[1] = cTokenizer.GetNextToken().GetInt();
					pFace->nVertex[2] = cTokenizer.GetNextToken().GetInt();
					pFace->nNormal[0] = cTokenizer.GetNextToken().GetInt();
					pFace->nNormal[1] = cTokenizer.GetNextToken().GetInt();
					pFace->nNormal[2] = cTokenizer.GetNextToken().GetInt();
					cTokenizer.GetNextToken(); // Ingnore the next number

					pFace->nMaterial = nMaterial;
					pFace->nVertex[0] += nStartVertex;
					pFace->nVertex[1] += nStartVertex;
					pFace->nVertex[2] += nStartVertex;
					pFace->nNormal[0] += nStartNormal;
					pFace->nNormal[1] += nStartNormal;
					pFace->nNormal[2] += nStartNormal;

					// Add face to temp list
					lstFaces.Add(pFace);
				}

				// Update start indices
				nStartVertex += nNumOfVertices;
				nStartNormal += nNumOfNormals;
			}

		// Materials:
		} else if (cTokenizer.CompareToken("Materials:")) {
			// Get number of materials
			uint32 nNumOfMaterials = cTokenizer.GetNextToken().GetInt();

			// Parse materials
			for (uint32 nMaterial=0; nMaterial<nNumOfMaterials; nMaterial++) {
				// Get material
				M3d::Material *pMaterial = new M3d::Material;

				// Ingnore the name
				cTokenizer.GetNextToken();

				// Ingnore color 1
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();

				// Ingnore color 2
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();

				// Ingnore color 3
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();

				// Ingnore color 4
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();
				cTokenizer.GetNextToken();

				// Ingnore color value 1
				cTokenizer.GetNextToken();

				// Ingnore color value 2
				cTokenizer.GetNextToken();

				// Texture
				pMaterial->sTexture = cTokenizer.GetNextToken();

				// Ingnore the last value
				cTokenizer.GetNextToken();

				// Add material to list
				lstMaterials.Add(pMaterial);
			}
		}
	}
	cTokenizer.Stop();

	// Optimize read data
	Array<M3d::VertexTex*> lstVertexTex;
	lstVertexTex.Resize(lstFaces.GetNumOfElements()*3, false, false);
	M3d::VertexHashTable *pVHTable = new M3d::VertexHashTable(lstFaces.GetNumOfElements()*3);
	for (uint32 nFace=0; nFace<lstFaces.GetNumOfElements(); nFace++) {
		M3d::Face *pFace = lstFaces[nFace];
		for (uint32 nVertex=0; nVertex<3; nVertex++) {
			// Setup face vertex
			uint32 nV = pFace->nVertex[nVertex];
			M3d::VertexTex cVertex;
			cVertex.nVertex = nV;
			cVertex.fX = lstVertices[nV]->fX;
			cVertex.fY = lstVertices[nV]->fY;
			cVertex.fZ = lstVertices[nV]->fZ;
			cVertex.fS = lstVertices[nV]->fS;
			cVertex.fT = lstVertices[nV]->fT;
			uint32 nN = pFace->nNormal[nVertex];
			cVertex.fNX = lstNormals[nN]->fX;
			cVertex.fNY = lstNormals[nN]->fY;
			cVertex.fNZ = lstNormals[nN]->fZ;

			// Add vertex to list if not already in
			M3d::VertexTex *pVertex = pVHTable->Add(cVertex);
			if (pVertex->nIndex >= lstVertexTex.GetNumOfElements())
				lstVertexTex.Add(pVertex);

			// Update face vertex ID
			pFace->nVertex[nVertex] = pVertex->nIndex;
		}
	}

	// Create the mesh and fill it with the read data
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();

	// Get the material manager
	MaterialManager &cMaterialManager = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager();

	// Go through all the materials
	for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++) {
		String sTexture = lstMaterials[i]->sTexture;
		Material *pMaterial = cMaterialManager.LoadResource(sTexture);
		cMesh.AddMaterial(pMaterial ? pMaterial : cMaterialManager.Create(sTexture));
	}

	// Create morph target
	MeshMorphTarget *pMorphTarget = cMesh.AddMorphTarget();
	VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
	pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
	pVertexBuffer->Allocate(lstVertexTex.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);

	// Fill vertex buffer
	if (pVertexBuffer->Lock(Lock::WriteOnly)) {
		// Fill vertex buffer
		for (uint32 nFace=0; nFace<lstFaces.GetNumOfElements(); nFace++) {
			const M3d::Face *pFace = lstFaces[nFace];
			for (uint32 i=0; i<3; i++) {
				uint32 nID = pFace->nVertex[i];
				const M3d::VertexTex &cVertex = *lstVertexTex[nID];
				float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Position));
				pfVertex[Vector3::X] = cVertex.fX;
				pfVertex[Vector3::Y] = cVertex.fY;
				pfVertex[Vector3::Z] = cVertex.fZ;
				pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Normal));
				pfVertex[Vector3::X] = cVertex.fNX;
				pfVertex[Vector3::Y] = cVertex.fNY;
				pfVertex[Vector3::Z] = cVertex.fNZ;
				pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::TexCoord));
				pfVertex[Vector2::X] = cVertex.fS;
				pfVertex[Vector2::Y] = cVertex.fT;
			}
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Allocate index buffer
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(pVertexBuffer->GetNumOfElements()-1);
	pIndexBuffer->Allocate(lstFaces.GetNumOfElements()*3, bStatic ? Usage::Static : Usage::Dynamic);

	// Fill index buffer
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
	if (pIndexBuffer->Lock(Lock::WriteOnly)) {
		uint32 nIndex       = 0;
		uint32 nStartVertex = 0;
		uint32 nVertices    = 0;

		// Loop through all meshes
		if (bMergeMeshes) nNumOfMeshes = 1;
		for (uint32 nMesh=0; nMesh<nNumOfMeshes; nMesh++) {
			// Go through all object materials
			for (int nMat=-1; nMat<static_cast<int>(cMesh.GetNumOfMaterials()); nMat++) {
				// Fill vertex buffer
				for (uint32 nFace=0; nFace<lstFaces.GetNumOfElements(); nFace++) {
					// Get the face
					const M3d::Face *pFace = lstFaces[nFace];

					// Check mesh ID and material
					if ((bMergeMeshes || pFace->nMeshID == nMesh) && pFace->nMaterial == static_cast<uint32>(nMat)) {
						// V0
						pIndexBuffer->SetData(nIndex++, pFace->nVertex[0]);

						// V1
						pIndexBuffer->SetData(nIndex++, pFace->nVertex[1]);

						// V2
						pIndexBuffer->SetData(nIndex++, pFace->nVertex[2]);

						nVertices += 3;
					}
				}

				// Setup geometry
				if (nVertices) {
					Geometry &cGeometry = lstGeometries.Add();
					cGeometry.SetPrimitiveType(Primitive::TriangleList);
					cGeometry.SetStartIndex(nStartVertex);
					cGeometry.SetIndexSize(nVertices);
					cGeometry.SetMaterial(nMat);
				}
				nStartVertex += nVertices;
				nVertices	  = 0;
			}
		}

		// Unlock the index buffer
		pIndexBuffer->Unlock();
	}

	// Destroy temp data
	for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++)
		delete lstMaterials[i];
	lstMaterials.Clear();
	for (uint32 i=0; i<lstVertices.GetNumOfElements(); i++)
		delete lstVertices[i];
	lstVertices.Clear();
	for (uint32 i=0; i<lstNormals.GetNumOfElements(); i++)
		delete lstNormals[i];
	lstNormals.Clear();
	for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++)
		delete lstFaces[i];
	lstFaces.Clear();
	lstVertexTex.Clear();
	delete pVHTable;

	// Done
	return true;
}

bool MeshLoaderM3d::Save(Mesh &cMesh, File &cFile)
{
	// [TODO] Implement me!
	return false; // Error!
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshLoaderM3d::MeshLoaderM3d()
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderM3d::~MeshLoaderM3d()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
