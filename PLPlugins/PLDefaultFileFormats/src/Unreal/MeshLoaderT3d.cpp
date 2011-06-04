/*********************************************************\
 *  File: MeshLoaderT3d.cpp                              *
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
#include <PLRenderer/Texture/Texture.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/Unreal/MeshLoaderT3d.h"


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
pl_implement_class(MeshLoaderT3d)


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
namespace T3d {
// Materials
struct Material {
	uint32 nID;		/**< Material ID */
	String sName;	/**< Material name */
};

struct Polygon {
	String			sTextureName;
	int				nMaterialID;
	uint32			nFlags;
	Array<Vector3>	lstVertices;
	Array<uint32>	lstIndices;	// Vertex index
	Vector3			vOrigin;
	Vector3			vNormal;
	Vector3			vS;
	Vector3			vT;
};


//[-------------------------------------------------------]
//[ Optimization                                          ]
//[-------------------------------------------------------]
/**
*  @brief
*    For vertex optimizing
*/
class Vertex {
	public:
	uint32 nVertex;			/**< Vertex ID */
	float  fX, fY, fZ;		/**< Coordinate */
	float  fNX, fNY, fNZ;	/**< Normal */
	float  fS, fT;			/**< Texture coordinate */
	uint32 nIndex;			/**< Used inside the vertex hash table */
	Vertex &operator =(const Vertex &cSource)
	{
		// We do not need an implementation in here...
		return *this;
	}
	bool operator ==(const Vertex &cVertex) const
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
			m_plstSlots(new List<Vertex>[nSlots])
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

		inline bool IsEqual(float f1, float f2)
		{
			return Math::Abs(f1-f2) < 0.001f;
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
		Vertex *Add(Vertex &cVertex)
		{
			// Get key
			uint32 nKey = GetKey(cVertex);
			List<Vertex> &cSlot = m_plstSlots[nKey];

			// Check if the vertex is already in the hash table
			if (m_plstSlots[nKey].GetNumOfElements()) {
				// Check slot and collisions
				for (uint32 i=0; i<cSlot.GetNumOfElements(); i++) {
					Vertex &cVer = cSlot[i];
					if (IsEqual(cVer.fX,  cVertex.fX)  &&
						IsEqual(cVer.fY,  cVertex.fY)  &&
						IsEqual(cVer.fZ,  cVertex.fZ)  &&
						IsEqual(cVer.fNX, cVertex.fNX) &&
						IsEqual(cVer.fNY, cVertex.fNY) &&
						IsEqual(cVer.fNZ, cVertex.fNZ) &&
						IsEqual(cVer.fS,  cVertex.fS)  &&
						IsEqual(cVer.fT,  cVertex.fT)) {
						// The vertex is already in the table!
						return &cVer;
					}
				}
			}

			// Add vertex to table
			Vertex &cVer  = cSlot.Add();
			cVer.nVertex = cVertex.nVertex;
			cVer.fX      = cVertex.fX;
			cVer.fY      = cVertex.fY;
			cVer.fZ      = cVertex.fZ;
			cVer.fNX     = cVertex.fNX;
			cVer.fNY     = cVertex.fNY;
			cVer.fNZ     = cVertex.fNZ;
			cVer.fS      = cVertex.fS;
			cVer.fT      = cVertex.fT;
			cVer.nIndex  = m_nVertices++;

			// Return the index of the added vertex
			return &cVer;
		}


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32		  m_nSlots;		/**< Number of slots */
		uint32		  m_nVertices;	/**< Total number of vertices in the table */
		List<Vertex> *m_plstSlots;	/**< Collisions per slot */


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
		uint32 GetKey(Vertex &cVertex)
		{
			return Math::Abs(static_cast<int>(cVertex.fX*10+cVertex.fY*100+cVertex.fZ*112+
							 cVertex.fS*123+cVertex.fT*42))%m_nSlots;
		}


};
} // T3d


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderT3d::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderT3d::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n()[],;\"");
	cTokenizer.SetSingleChars("{}:=");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCaseSensitive(true);

	Array<T3d::Material*>			lstMaterials;
	HashMap<String, T3d::Material*> mapMaterials;
	Array<T3d::Polygon*>			lstPolys;
	lstPolys.SetResizeCount(10000);


// Part I
	bool removePortals = true;
	bool removeInvisible = true;
	bool removeTwoSided = true;
	float texSize = 512;

	uint32 nPolyMask = 0;
	if (removePortals)
		nPolyMask |= 0x4000000;
	if (removeInvisible)
		nPolyMask |= 0x1;
	if (removeTwoSided)
		nPolyMask |= 0x100;

	// Read file
	while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("End")) {
		// Begin
		if (!cTokenizer.CompareToken("Begin"))
			continue;
		if (!cTokenizer.GetNextToken().GetLength() || cTokenizer.CompareToken("End"))
			continue;

		// PolyList
		if (cTokenizer.CompareToken("PolyList")) {
			// Read this section
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("End")) {
				// Begin
				if (!cTokenizer.CompareToken("Begin"))
					continue;
				if (!cTokenizer.GetNextToken().GetLength() || cTokenizer.CompareToken("End"))
					continue;

				// Polygon
				if (cTokenizer.CompareToken("Polygon")) {
					// Create a new polygon
					T3d::Polygon *pPoly = new T3d::Polygon;
					pPoly->nMaterialID = -1;
					pPoly->nFlags      = 0;

					// Read polygon attributes
					while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("End")) {
						// Texture
						if (cTokenizer.CompareToken("Texture")) {
							// Skip '='
							cTokenizer.GetNextToken();
							// Get texture
							pPoly->sTextureName = cTokenizer.GetNextToken();

							// Get material
							T3d::Material *pFoundMaterial = mapMaterials.Get(pPoly->sTextureName);
							if (!pFoundMaterial) {
								// Add new material
								T3d::Material *pMaterial = new T3d::Material();
								pMaterial->nID   = lstMaterials.GetNumOfElements();
								pMaterial->sName = pPoly->sTextureName;
								lstMaterials.Add(pMaterial);
								mapMaterials.Add(pMaterial->sName, pMaterial);
								pPoly->nMaterialID = pMaterial->nID;
							} else {
								pPoly->nMaterialID = pFoundMaterial->nID;
							}

						// Flags
						} else if (cTokenizer.CompareToken("Flags")) {
							// Skip '='
							cTokenizer.GetNextToken();

							// Get flags
							pPoly->nFlags = cTokenizer.GetNextToken().GetInt();

						// Origin
						} else if (cTokenizer.CompareToken("Origin")) {
							pPoly->vOrigin.x =  cTokenizer.GetNextToken().GetFloat();
							pPoly->vOrigin.z = -cTokenizer.GetNextToken().GetFloat();
							pPoly->vOrigin.y =  cTokenizer.GetNextToken().GetFloat();

						// Normal
						} else if (cTokenizer.CompareToken("Normal")) {
							pPoly->vNormal.x =  cTokenizer.GetNextToken().GetFloat();
							pPoly->vNormal.z = -cTokenizer.GetNextToken().GetFloat();
							pPoly->vNormal.y =  cTokenizer.GetNextToken().GetFloat();

						// TextureU
						} else if (cTokenizer.CompareToken("TextureU")) {
							pPoly->vS.x =  cTokenizer.GetNextToken().GetFloat();
							pPoly->vS.z = -cTokenizer.GetNextToken().GetFloat();
							pPoly->vS.y =  cTokenizer.GetNextToken().GetFloat();

						// TextureV
						} else if (cTokenizer.CompareToken("TextureV")) {
							pPoly->vT.x =  cTokenizer.GetNextToken().GetFloat();
							pPoly->vT.z = -cTokenizer.GetNextToken().GetFloat();
							pPoly->vT.y =  cTokenizer.GetNextToken().GetFloat();

						// Vertex
						} else if (cTokenizer.CompareToken("Vertex")) {
							Vector3 &vV = pPoly->lstVertices.Add();
							vV.x =  cTokenizer.GetNextToken().GetFloat();
							vV.z = -cTokenizer.GetNextToken().GetFloat();
							vV.y =  cTokenizer.GetNextToken().GetFloat();
						}
					}

					// Add this polygon to the polygon list?
					if (pPoly->sTextureName.GetLength() && !(pPoly->nFlags & nPolyMask)) {
						// Add this polygon
						lstPolys.Add(pPoly);
					} else {
						// Ignore this polygon
						delete pPoly;
					}

				// Unknown section
				} else {
					SkipSectionRec(cTokenizer);
				}
			}

		// Unknown section
		} else {
			SkipSectionRec(cTokenizer);
		}
	}
	cTokenizer.Stop();

	// Get the total number of vertices and indices
	uint32 nNumOfVertices = 0;
	uint32 nNumOfPolys    = lstPolys.GetNumOfElements();
	for (uint32 i=0; i<nNumOfPolys; i++)
		nNumOfVertices += lstPolys[i]->lstVertices.GetNumOfElements();
	uint32 nNumOfIndices = 3*nNumOfVertices - 6*nNumOfPolys;

	// Get memory for our data
	Vector3 *pvVertices  = new Vector3[nNumOfVertices];
	Vector2 *pvTexCoords = new Vector2[nNumOfVertices];
	Vector3 *pvTangents  = new Vector3[nNumOfPolys];
	Vector3 *pvBinormals = new Vector3[nNumOfPolys];
	Vector3 *pvNormals   = new Vector3[nNumOfPolys];
	uint32 *pnVTXIndices = new uint32[nNumOfIndices];
	uint32 *pnTanIndices = new uint32[nNumOfIndices];
	uint32 *pnBinIndices = new uint32[nNumOfIndices];
	uint32 *pnNrmIndices = new uint32[nNumOfIndices];

	// Process data
	uint32 nIDest = 0;
	uint32 nStartIndex = 0;
	for (uint32 i=0; i<nNumOfPolys; i++) {
		T3d::Polygon *pPoly = lstPolys[i];

		Vector3 *vtxDest = pvVertices  + nStartIndex;
		Vector2 *texDest = pvTexCoords + nStartIndex;
		
		for (int j=0; j<static_cast<int>(3*pPoly->lstVertices.GetNumOfElements())-6; j++) {
			pnTanIndices[nIDest + j] = i;
			pnBinIndices[nIDest + j] = i;
			pnNrmIndices[nIDest + j] = i;
		}

		uint32 nIndex1, nIndex2;
		for (uint32 j=0; j<static_cast<uint32>(pPoly->lstVertices.GetNumOfElements()); j++) {
			vtxDest[j] = pPoly->lstVertices[j];
			texDest[j].x = (pPoly->lstVertices[j] - pPoly->vOrigin).DotProduct(pPoly->vS/texSize);
			texDest[j].y = (pPoly->lstVertices[j] - pPoly->vOrigin).DotProduct(pPoly->vT/texSize);
			if (j > 2) {
				nIndex1 = nStartIndex;
				nIndex2 = nStartIndex + j - 1;
				pPoly->lstIndices.Add(nIndex1);
				pPoly->lstIndices.Add(nIndex2);
				pnVTXIndices[nIDest++] = nIndex1;
				pnVTXIndices[nIDest++] = nIndex2;
			}
			nIndex1 = nStartIndex + j;
			pPoly->lstIndices.Add(nIndex1);
			pnVTXIndices[nIDest++] = nIndex1;
		}

		pvTangents [i] = pPoly->vS.GetNormalized();
		pvBinormals[i] = pPoly->vT.GetNormalized();
		pvNormals  [i] = pPoly->vNormal.GetNormalized();

		nStartIndex += pPoly->lstVertices.GetNumOfElements();
	}

	// Optimize read data
	Array<T3d::Vertex*> lstVertexTex;
	T3d::VertexHashTable *pVHTable = new T3d::VertexHashTable(nNumOfVertices*2);
	lstVertexTex.Resize(nNumOfVertices, false, false);
	T3d::Vertex cVertex;
	for (uint32 i=0; i<nNumOfPolys; i++) {
		T3d::Polygon *pPoly = lstPolys[i];
		for (uint32 j=0; j<static_cast<uint32>(pPoly->lstIndices.GetNumOfElements()); j++) {
			uint32 nV = pPoly->lstIndices[j];
			cVertex.nVertex = nV;
			cVertex.fX  = pvVertices[nV].x;
			cVertex.fY  = pvVertices[nV].y;
			cVertex.fZ  = pvVertices[nV].z;
			cVertex.fS  = pvTexCoords[nV].x;
			cVertex.fT  = pvTexCoords[nV].y;
			cVertex.fNX = pvNormals[pnNrmIndices[nV]].x;
			cVertex.fNY = pvNormals[pnNrmIndices[nV]].y;
			cVertex.fNZ = pvNormals[pnNrmIndices[nV]].z;

			// Add vertex to list if not already in
			T3d::Vertex *pVertex = pVHTable->Add(cVertex);
			if (pVertex->nIndex >= lstVertexTex.GetNumOfElements())
				lstVertexTex.Add(pVertex);

			// Update face vertex ID
			pPoly->lstIndices[j] = pVertex->nIndex;
		}
	}
	bool bNormals   = true;
	bool bTexCoords = true;


// Part II
	// Create the mesh and fill it with the read data
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();

	// Create morph targets
	MeshMorphTarget *pMorphTarget = cMesh.AddMorphTarget();
	VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	if (bNormals)
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
	if (bTexCoords)
		pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
	pVertexBuffer->Allocate(lstVertexTex.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);

	// Get the material manager
	MaterialManager &cMaterialManager = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager();

	// Go through all the materials
	for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++) {
		const String &sMaterial = lstMaterials[i]->sName;
		Material *pMaterial = cMaterialManager.LoadResource(sMaterial);
		cMesh.AddMaterial(pMaterial ? pMaterial : cMaterialManager.Create(sMaterial));
	}

	// Fill vertex buffer
	if (pVertexBuffer->Lock(Lock::WriteOnly)) {
		{ // Fill vertex buffer
			uint32 i = 0;
			Iterator<T3d::Vertex*> cIterator = lstVertexTex.GetIterator();
			while (cIterator.HasNext()) {
				const T3d::Vertex *pVertex = cIterator.Next();

				// Position
				float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::Position));
				pfVertex[Vector3::X] = pVertex->fX;
				pfVertex[Vector3::Y] = pVertex->fY;
				pfVertex[Vector3::Z] = pVertex->fZ;

				// Normal
				if (bNormals) {
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::Normal));
					pfVertex[Vector3::X] = pVertex->fNX;
					pfVertex[Vector3::Y] = pVertex->fNY;
					pfVertex[Vector3::Z] = pVertex->fNZ;
				}

				// Texture coordinate
				if (bTexCoords) {
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::TexCoord));
					pfVertex[Vector2::X] = pVertex->fS;
					pfVertex[Vector2::Y] = pVertex->fT;
				}

				// Increment index
				i++;
			}
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Allocate index buffer
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(lstVertexTex.GetNumOfElements()-1);
	pIndexBuffer->Allocate(nNumOfIndices, bStatic ? Usage::Static : Usage::Dynamic);

	// Fill index buffer
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
	if (pIndexBuffer->Lock(Lock::WriteOnly)) {
		uint32 nIndex = 0;
		uint32 nStartVertex = 0;
		uint32 nVertices    = 0;

		// Go through all object materials
		for (int nMat=-1; nMat<static_cast<int>(cMesh.GetNumOfMaterials()); nMat++) {
			// Fill index buffer
			for (uint32 i=0; i<nNumOfPolys; i++) {
				// Get the polygon
				const T3d::Polygon *pPoly = lstPolys[i];

				// Check material
				if (pPoly->nMaterialID == nMat) {
					// Add indices in reversed order
					for (int j=pPoly->lstIndices.GetNumOfElements()-1; j>=0; j--) {
						pIndexBuffer->SetData(nIndex++, pPoly->lstIndices[j]);
						nVertices++;
					}
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

		// Unlock the index buffer
		pIndexBuffer->Unlock();
	}

	// Cleanup
	delete pVHTable;
	for (uint32 i=0; i<lstPolys.GetNumOfElements(); i++)
		delete lstPolys[i];
	lstPolys.Clear();
	delete [] pvVertices;
	delete [] pvTexCoords;
	delete [] pvTangents;
	delete [] pvBinormals;
	delete [] pvNormals;
	delete [] pnVTXIndices;
	delete [] pnTanIndices;
	delete [] pnBinIndices;
	delete [] pnNrmIndices;

	// Done
	return true;
}

bool MeshLoaderT3d::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderT3d::MeshLoaderT3d()
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderT3d::~MeshLoaderT3d()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Recursive section skip
*/
void MeshLoaderT3d::SkipSectionRec(Tokenizer &cTokenizer) const
{
	// Read this section
	while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("End")) {
		// Begin
		if (cTokenizer.CompareToken("Begin"))
			SkipSectionRec(cTokenizer);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
