/*********************************************************\
 *  File: MeshLoaderObj.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Url.h>
#include <PLMath/Vector2.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/Wavefront/MeshLoaderObj.h"


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
pl_implement_class(MeshLoaderObj)


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
namespace Obj {
// Materials
struct Material {
	uint32 nID;			/**< Material ID */
	String sName;		/**< Material name */
	String sTexture;	/**< Material texture */
};

// Vertices
struct Vertex {
	float fX, fY, fZ;
};

// Normals
struct Normal {
	float fX, fY, fZ;
};

// Texture coordinates
struct TexCoord {
	float fS, fT;
};

// Faces
struct Face {
	int nVertex[3];
	int nTexCoord[3];
	int nNormal[3];
	int nMaterial;
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
			return Math::Abs((int)(cVertex.fX*10+cVertex.fY*100+cVertex.fZ*112+
							cVertex.fS*123+cVertex.fT*42))%m_nSlots;
		}


};
} // Obj


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderObj::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderObj::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n()[]=,;\"");
	cTokenizer.SetSingleChars("{}:");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCaseSensitive(true);

	Array<Obj::Material*>			 lstMaterials;
	HashMap<String, Obj::Material*>  mapMaterials;
	Obj::Material					*pMaterial = NULL;	/**< Current face material */
	Array<Array<Obj::Vertex*>*>		 lstVertices;
	Array<Obj::Normal*>				 lstNormals;
	Array<Obj::TexCoord*>			 lstTexCoords;
	Array<Obj::Face*>				 lstFaces;

	String sAbsDirectory = cFile.GetUrl().CutFilename();

	// Read file
	while (cTokenizer.GetNextToken().GetLength()) {
		// vt (Texture coordinates)
		if (cTokenizer.CompareToken("vt")) {
			Obj::TexCoord *pTexCoord = new Obj::TexCoord;

			// Read out coordinates
			pTexCoord->fS =		   cTokenizer.GetNextToken().GetFloat();
			pTexCoord->fT = 1.0f - cTokenizer.GetNextToken().GetFloat();

			// Add texture coordinate to temp list
			lstTexCoords.Add(pTexCoord);

		// vn (Normal)
		} else if (cTokenizer.CompareToken("vn")) {
			Obj::Normal *pNormal = new Obj::Normal;

			// Read out normal
			pNormal->fX = cTokenizer.GetNextToken().GetFloat();
			pNormal->fY = cTokenizer.GetNextToken().GetFloat();
			pNormal->fZ = cTokenizer.GetNextToken().GetFloat();

			// Add normal to temp list
			lstNormals.Add(pNormal);

		// v (Vertex)
		} else if (cTokenizer.CompareToken("v")) {
			Obj::Vertex *pVertex = new Obj::Vertex;

			// Read out coordinates
			pVertex->fX = cTokenizer.GetNextToken().GetFloat();
			pVertex->fY = cTokenizer.GetNextToken().GetFloat();
			pVertex->fZ = cTokenizer.GetNextToken().GetFloat();

			// Add vertex to temp list
			if (!lstVertices.GetNumOfElements()) lstVertices.Add(new Array<Obj::Vertex*>);
			lstVertices[lstVertices.GetNumOfElements()-1]->Add(pVertex);

		// frame
		} else if (cTokenizer.CompareToken("frame")) {
			lstVertices.Add(new Array<Obj::Vertex*>);

		// f (Face)
		} else if (cTokenizer.CompareToken("f")) {
			// Change tokenizer settings (we have to process a whole line...)
			cTokenizer.SetDelimiters(" \t\r()[]=,;");
			cTokenizer.SetSingleChars("{}:\n/");

			// Get the vertices
			int nIndices[2][3];
			int nVertex, nTexCoord, nNormal, nVertices = 0;
			cTokenizer.GetNextToken();
			while (cTokenizer.GetToken().GetLength() && !cTokenizer.CompareToken("\n")) {
				// Get the indices
				nVertex = cTokenizer.GetToken().GetInt()-1; // We start at index 0...
				cTokenizer.GetNextToken();
				if (cTokenizer.CompareToken("/")) {
					nTexCoord = cTokenizer.GetNextToken().GetInt();

					// Check for negative texture coordinate
					if (nTexCoord < 0) {
						// Fix texture coordinate indices
						nTexCoord = lstTexCoords.GetNumOfElements()+nTexCoord;
					} else nTexCoord--; // We start at index 0...

					cTokenizer.GetNextToken();
					if (cTokenizer.CompareToken("/")) {
						nNormal = cTokenizer.GetNextToken().GetInt()-1; // We start at index 0...
						cTokenizer.GetNextToken();
					} else {
						nNormal = -1;
					}
				} else {
					nTexCoord = nNormal = -1;
				}

				// Are this the first two initial vertices?
				if (nVertices < 2) {
					nIndices[nVertices][0] = nVertex;
					nIndices[nVertices][1] = nTexCoord;
					nIndices[nVertices][2] = nNormal;

				// Nope, add a face
				} else {
					// Create the face
					Obj::Face *pFace = new Obj::Face;

					// First vertex
					pFace->nVertex[0]   = nIndices[0][0];
					pFace->nTexCoord[0] = nIndices[0][1];
					pFace->nNormal[0]   = nIndices[0][2];

					// Second vertex
					pFace->nVertex[1]   = nIndices[1][0];
					pFace->nTexCoord[1] = nIndices[1][1];
					pFace->nNormal[1]   = nIndices[1][2];

					// Third vertex (backup the indices for the next triangle, too)
					pFace->nVertex[2]   = nIndices[1][0] = nVertex;
					pFace->nTexCoord[2] = nIndices[1][1] = nTexCoord;
					pFace->nNormal[2]   = nIndices[1][2] = nNormal;

					// Set face material
					if (pMaterial) pFace->nMaterial = pMaterial->nID;
					else		   pFace->nMaterial = -1;

					// Add face to temp list
					lstFaces.Add(pFace);
				}
				nVertices++;
			}

			// Reset tokenizer settings
			cTokenizer.SetDelimiters(" \t\r\n()[]=,;\"");
			cTokenizer.SetSingleChars("{}:");

		// mtllib (Material library)
		} else if (cTokenizer.CompareToken("mtllib")) {
			// Read material lib filename
			String sMaterial = cTokenizer.GetNextToken();

			// Open material file
			String sFilename = sAbsDirectory + sMaterial;
			File cMaterialFile(sFilename);
			if (cMaterialFile.Open(File::FileRead)) {
				Tokenizer cMatTokenizer;
				cMatTokenizer.Start(cMaterialFile);

				// Read out material
				while (cMatTokenizer.GetNextToken().GetLength()) {
					// newmtl
					if (cMatTokenizer.CompareToken("newmtl")) {
						// Add new material
						pMaterial = new Obj::Material();
						pMaterial->nID      = lstMaterials.GetNumOfElements();
						pMaterial->sName    = cMatTokenizer.GetNextToken();
						pMaterial->sTexture = "";
						lstMaterials.Add(pMaterial);
						mapMaterials.Add(pMaterial->sName, pMaterial);

					// map_Kd
					} else if (cMatTokenizer.CompareToken("map_Kd")) {
						// Material texture
						if (pMaterial) pMaterial->sTexture = cMatTokenizer.GetNextToken();
					}
				}
				cMatTokenizer.Stop();
				cMaterialFile.Close();
			}

		// usemtl (Material)
		} else if (cTokenizer.CompareToken("usemtl")) {
			// Get material name
			String sMaterial = cTokenizer.GetNextToken();

			// Get material
			Obj::Material *pFoundMaterial = mapMaterials.Get(sMaterial);
			if (!pFoundMaterial) {
				// Add new material
				pMaterial = new Obj::Material();
				pMaterial->nID      = lstMaterials.GetNumOfElements();
				pMaterial->sName    = sMaterial;
				pMaterial->sTexture = sMaterial;
				lstMaterials.Add(pMaterial);
				mapMaterials.Add(pMaterial->sName, pMaterial);
			} else pMaterial = pFoundMaterial;
		}
	}
	cTokenizer.Stop();

	// Optimize read data
	Array<Obj::VertexTex*> lstVertexTex;
	lstVertexTex.Resize(lstFaces.GetNumOfElements()*3, false, false);
	Obj::VertexHashTable *pVHTable = new Obj::VertexHashTable(lstFaces.GetNumOfElements()*3);
	Obj::VertexTex cVertex, *pVertex;
	int nV, nT, nN;
	for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++) {
		Obj::Face *pFace = lstFaces[i];
		for (uint32 nVertex=0; nVertex<3; nVertex++) {
			// Setup face vertex
			nV = pFace->nVertex[nVertex];
			if (nV < 0 || nV >= (signed)lstVertices[0]->GetNumOfElements()) {
				// ? Error! ?
				pFace->nVertex[nVertex] = 0;
			} else {
				cVertex.nVertex = nV;
				cVertex.fX = lstVertices[0]->Get(nV)->fX;
				cVertex.fY = lstVertices[0]->Get(nV)->fY;
				cVertex.fZ = lstVertices[0]->Get(nV)->fZ;
				if (lstNormals.GetNumOfElements()) {
					nN = pFace->nNormal[nVertex];
					if (nN >= 0 && nN < (signed)lstNormals.GetNumOfElements()) {
						cVertex.fNX = lstNormals[nN]->fX;
						cVertex.fNY = lstNormals[nN]->fY;
						cVertex.fNZ = lstNormals[nN]->fZ;
					} else { // ? Error! ?
						cVertex.fNX = 0.0f;
						cVertex.fNY = 0.0f;
						cVertex.fNZ = 0.0f;
					}
				} else {
					cVertex.fNX = 0.0f;
					cVertex.fNY = 0.0f;
					cVertex.fNZ = 0.0f;
				}
				if (lstTexCoords.GetNumOfElements()) {
					nT = pFace->nTexCoord[nVertex];
					if (nT >= 0 && nT < (signed)lstTexCoords.GetNumOfElements()) {
						cVertex.fS = lstTexCoords[nT]->fS;
						cVertex.fT = lstTexCoords[nT]->fT;
					} else { // ? Error! ?
						cVertex.fS = cVertex.fT = 0.0f;
					}
				} else {
					cVertex.fS = cVertex.fT = 0.0f;
				}

				// Add vertex to list if not already in
				pVertex = pVHTable->Add(cVertex);
				if (pVertex->nIndex >= lstVertexTex.GetNumOfElements())
					lstVertexTex.Add(pVertex);

				// Update face vertex ID
				pFace->nVertex[nVertex] = pVertex->nIndex;
			}
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
		Material *pCurrentMaterial = cMaterialManager.LoadResource(sTexture);
		cMesh.AddMaterial(pCurrentMaterial ? pCurrentMaterial : cMaterialManager.Create(sTexture));
	}

	// Create morph targets
	Array<Obj::Vertex*> *plstFrame0 = lstVertices[0];
	for (uint32 nFrame=0; nFrame<lstVertices.GetNumOfElements(); nFrame++) {
		Array<Obj::Vertex*> *plstFrame = lstVertices[nFrame];
		MeshMorphTarget *pMorphTarget  = cMesh.AddMorphTarget();
		VertexBuffer    *pVertexBuffer = pMorphTarget->GetVertexBuffer();
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);

		// Fill vertex buffer
		float *pfVertex;
		uint32 nID;
		if (nFrame) {
			pVertexBuffer->Allocate(lstVertexTex.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);
			if (pVertexBuffer->Lock(Lock::WriteOnly)) {
				pMorphTarget->SetRelative(true);

				// Fill vertex buffer
				for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++) {
					const Obj::Face *pFace = lstFaces[i];
					// V0
					nID      = lstVertexTex[pFace->nVertex[0]]->nVertex;
					pfVertex = (float*)pVertexBuffer->GetData(pFace->nVertex[0], VertexBuffer::Position);
					pfVertex[Vector3::X] = plstFrame->Get(nID)->fX - plstFrame0->Get(nID)->fX;
					pfVertex[Vector3::Y] = plstFrame->Get(nID)->fY - plstFrame0->Get(nID)->fY;
					pfVertex[Vector3::Z] = plstFrame->Get(nID)->fZ - plstFrame0->Get(nID)->fZ;

					// V1
					nID      = lstVertexTex[pFace->nVertex[1]]->nVertex;
					pfVertex = (float*)pVertexBuffer->GetData(pFace->nVertex[1], VertexBuffer::Position);
					pfVertex[Vector3::X] = plstFrame->Get(nID)->fX - plstFrame0->Get(nID)->fX;
					pfVertex[Vector3::Y] = plstFrame->Get(nID)->fY - plstFrame0->Get(nID)->fY;
					pfVertex[Vector3::Z] = plstFrame->Get(nID)->fZ - plstFrame0->Get(nID)->fZ;

					// V2
					nID      = lstVertexTex[pFace->nVertex[2]]->nVertex;
					pfVertex = (float*)pVertexBuffer->GetData(pFace->nVertex[2], VertexBuffer::Position);
					pfVertex[Vector3::X] = plstFrame->Get(nID)->fX - plstFrame0->Get(nID)->fX;
					pfVertex[Vector3::Y] = plstFrame->Get(nID)->fY - plstFrame0->Get(nID)->fY;
					pfVertex[Vector3::Z] = plstFrame->Get(nID)->fZ - plstFrame0->Get(nID)->fZ;
				}

				// Unlock the vertex buffer
				pVertexBuffer->Unlock();
			}
		} else { // Main frame
			if (lstTexCoords.GetNumOfElements()) pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
			if (lstNormals.GetNumOfElements()) pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal, 0, VertexBuffer::Float3);
			pVertexBuffer->Allocate(lstVertexTex.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);
			if (pVertexBuffer->Lock(Lock::WriteOnly)) {
				// Fill vertex buffer
				for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++) {
					const Obj::Face *pFace = lstFaces[i];
					// V0
					nID      = lstVertexTex[pFace->nVertex[0]]->nVertex;
					pfVertex = (float*)pVertexBuffer->GetData(pFace->nVertex[0], VertexBuffer::Position);
					pfVertex[Vector3::X] = plstFrame->Get(nID)->fX;
					pfVertex[Vector3::Y] = plstFrame->Get(nID)->fY;
					pfVertex[Vector3::Z] = plstFrame->Get(nID)->fZ;
					nID = pFace->nVertex[0];
					if (lstTexCoords.GetNumOfElements()) {
						pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::TexCoord);
						pfVertex[Vector2::X] = lstVertexTex[nID]->fS;
						pfVertex[Vector2::Y] = lstVertexTex[nID]->fT;
					}
					if (lstNormals.GetNumOfElements()) {
						pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Normal);
						pfVertex[Vector3::X] = lstVertexTex[nID]->fNX;
						pfVertex[Vector3::Y] = lstVertexTex[nID]->fNY;
						pfVertex[Vector3::Z] = lstVertexTex[nID]->fNZ;
					}

					// V1
					nID      = lstVertexTex[pFace->nVertex[1]]->nVertex;
					pfVertex = (float*)pVertexBuffer->GetData(pFace->nVertex[1], VertexBuffer::Position);
					pfVertex[Vector3::X] = plstFrame->Get(nID)->fX;
					pfVertex[Vector3::Y] = plstFrame->Get(nID)->fY;
					pfVertex[Vector3::Z] = plstFrame->Get(nID)->fZ;
					nID = pFace->nVertex[1];
					if (lstTexCoords.GetNumOfElements()) {
						pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::TexCoord);
						pfVertex[Vector2::X] = lstVertexTex[nID]->fS;
						pfVertex[Vector2::Y] = lstVertexTex[nID]->fT;
					}
					if (lstNormals.GetNumOfElements()) {
						pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Normal);
						pfVertex[Vector3::X] = lstVertexTex[nID]->fNX;
						pfVertex[Vector3::Y] = lstVertexTex[nID]->fNY;
						pfVertex[Vector3::Z] = lstVertexTex[nID]->fNZ;
					}

					// V2
					nID      = lstVertexTex[pFace->nVertex[2]]->nVertex;
					pfVertex = (float*)pVertexBuffer->GetData(pFace->nVertex[2], VertexBuffer::Position);
					pfVertex[Vector3::X] = plstFrame->Get(nID)->fX;
					pfVertex[Vector3::Y] = plstFrame->Get(nID)->fY;
					pfVertex[Vector3::Z] = plstFrame->Get(nID)->fZ;
					nID = pFace->nVertex[2];
					if (lstTexCoords.GetNumOfElements()) {
						pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::TexCoord);
						pfVertex[Vector2::X] = lstVertexTex[nID]->fS;
						pfVertex[Vector2::Y] = lstVertexTex[nID]->fT;
					}
					if (lstNormals.GetNumOfElements()) {
						pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Normal);
						pfVertex[Vector3::X] = lstVertexTex[nID]->fNX;
						pfVertex[Vector3::Y] = lstVertexTex[nID]->fNY;
						pfVertex[Vector3::Z] = lstVertexTex[nID]->fNZ;
					}
				}

				// Unlock the vertex buffer
				pVertexBuffer->Unlock();
			}
		}
	}

	// Allocate index buffer
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(lstVertexTex.GetNumOfElements()-1);
	pIndexBuffer->Allocate(lstFaces.GetNumOfElements()*3, bStatic ? Usage::Static : Usage::Dynamic);

	// Fill index buffer
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
	if (pIndexBuffer->Lock(Lock::WriteOnly)) {
		uint32 nIndex		= 0;
		uint32 nStartVertex = 0;
		uint32 nVertices    = 0;

		// Go through all object materials
		for (int nMat=-1; nMat<(int)cMesh.GetNumOfMaterials(); nMat++) {
			// Fill index buffer
			for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++) {
				// Get the face
				const Obj::Face *pFace = lstFaces[i];

				// Check material
				if (pFace->nMaterial == nMat) {
					// V0
					pIndexBuffer->SetData(nIndex++, pFace->nVertex[0]);

					// V1
					pIndexBuffer->SetData(nIndex++, pFace->nVertex[1]);

					// V2
					pIndexBuffer->SetData(nIndex++, pFace->nVertex[2]);

					// Next vertices, please
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

		// Unlock the index buffer
		pIndexBuffer->Unlock();
	}

	// Destroy temp data
	for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++)
		delete lstMaterials[i];
	lstMaterials.Clear();
	mapMaterials.Clear();
	for (uint32 nFrame=0; nFrame<lstVertices.GetNumOfElements(); nFrame++) {
		for (uint32 i=0; i<lstVertices[nFrame]->GetNumOfElements(); i++)
			delete lstVertices[nFrame]->Get(i);
		lstVertices[nFrame]->Clear();
		delete lstVertices[nFrame];
	}
	lstVertices.Clear();
	for (uint32 i=0; i<lstTexCoords.GetNumOfElements(); i++)
		delete lstTexCoords[i];
	lstTexCoords.Clear();
	for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++)
		delete lstFaces[i];
	lstFaces.Clear();
	lstVertexTex.Clear();
	delete pVHTable;

	// Done
	return true;
}

bool MeshLoaderObj::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderObj::MeshLoaderObj() :
	MethodLoad(this),
	MethodLoadParams(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderObj::~MeshLoaderObj()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
