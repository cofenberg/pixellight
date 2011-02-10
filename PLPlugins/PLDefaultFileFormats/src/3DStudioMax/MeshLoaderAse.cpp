/*********************************************************\
 *  File: MeshLoaderAse.cpp                              *
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
#include <PLGeneral/Tools/Tools.h>
#include <PLGeneral/String/Tokenizer.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Texture/TextureHandler.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLRenderer/Effect/EffectPass.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Effect/EffectTechnique.h>
#include <PLRenderer/Effect/EffectPassLayer.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/3DStudioMax/MeshLoaderAse.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshLoaderAse)


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
namespace Ase {
struct Face {
	uint32 nV[3];	// Vertex index
};

struct FaceList {
	uint32  nNumOfFaces;
	Face   *pFaces;
	int     nMaterial;
};

struct TexFace {
	uint32 nT[3];	// Texture coordinate index
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
} // Ase


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderAse::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderAse::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n()[]=,;\"");
	cTokenizer.SetSingleChars("{}:");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCaseSensitive(true);

	// We create this hash table dynamically to avoid the risk to overload the runtime-stack :D
	Ase::VertexHashTable *pVHTable = new Ase::VertexHashTable(100000);

	// Get the material and effect manager
	MaterialManager &cMaterialManager = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager();
	EffectManager   &cEffectManager   = cMesh.GetRenderer()->GetRendererContext().GetEffectManager();

	// Read file
	List<Ase::Vertex*> lstVertexTex;
	Array<Ase::FaceList*> lstFaceLists;
	bool bNormals = false, bTexCoords = false;
	while (cTokenizer.GetNextToken().GetLength()) {
		// *MATERIAL_LIST
		if (cTokenizer.CompareToken("*MATERIAL_LIST")) {
			// Read *MATERIAL_LIST
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
				// *MATERIAL_COUNT
				if (cTokenizer.CompareToken("*MATERIAL_COUNT")) {
					// Nothing to do in here

				// *MATERIAL
				} else if (cTokenizer.CompareToken("*MATERIAL")) {
					// Create material
					Material		*pMaterial  = cMaterialManager.Create();
					Effect			*pFX        = cEffectManager.Create();
					EffectTechnique	*pTechnique = pFX->AddTechnique();
					pFX->SelectTechnique(0);
					pMaterial->SetEffect(pFX);
					EffectPass *pFXPass = pTechnique->AddPass();

					// Add the material to the mesh
					cMesh.AddMaterial(pMaterial);

					// Read *MATERIAL
					while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
						// *MATERIAL_NAME
						if (cTokenizer.CompareToken("*MATERIAL_NAME")) {
							String sMaterialName = cTokenizer.GetNextToken();

							// Find an unused name
							String sFinalMaterialName = sMaterialName;
							int nLoop = 0;
							while (cMaterialManager.Get(sFinalMaterialName))
								sFinalMaterialName = sMaterialName + '_' + nLoop;

							// Set the name
							pMaterial->SetName(sFinalMaterialName);

						// *MATERIAL_AMBIENT
						} else if (cTokenizer.CompareToken("*MATERIAL_AMBIENT")) {
							float fR = cTokenizer.GetNextToken().GetFloat();
							float fG = cTokenizer.GetNextToken().GetFloat();
							float fB = cTokenizer.GetNextToken().GetFloat();
							pFXPass->SetMaterialState(FixedFunctions::MaterialState::Ambient, Color4::ToUInt32(fR, fG, fB, 1.0f));

						// *MATERIAL_DIFFUSE
						} else if (cTokenizer.CompareToken("*MATERIAL_DIFFUSE")) {
							float fR = cTokenizer.GetNextToken().GetFloat();
							float fG = cTokenizer.GetNextToken().GetFloat();
							float fB = cTokenizer.GetNextToken().GetFloat();
							pFXPass->SetMaterialState(FixedFunctions::MaterialState::Diffuse, Color4::ToUInt32(fR, fG, fB, 1.0f));

						// *MATERIAL_SPECULAR
						} else if (cTokenizer.CompareToken("*MATERIAL_SPECULAR")) {
							float fR = cTokenizer.GetNextToken().GetFloat();
							float fG = cTokenizer.GetNextToken().GetFloat();
							float fB = cTokenizer.GetNextToken().GetFloat();
							pFXPass->SetMaterialState(FixedFunctions::MaterialState::Specular, Color4::ToUInt32(fR, fG, fB, 1.0f));

						// *MATERIAL_SHINE
						} else if (cTokenizer.CompareToken("*MATERIAL_SHINE")) {
							float fShininess = cTokenizer.GetNextToken().GetFloat();
							pFXPass->SetMaterialState(FixedFunctions::MaterialState::Shininess, Tools::FloatToUInt32(fShininess));

						// *SUBMATERIAL
						} else if (cTokenizer.CompareToken("*SUBMATERIAL")) {
							// Read *SUBMATERIAL
							while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
								// *MAP_DIFFUSE
								if (cTokenizer.CompareToken("*MAP_DIFFUSE")) {
									// Add a layer
									EffectPassLayer *pFXPassLayer = pFXPass->AddLayer();

									// Read *SUBMATERIAL
									while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
										// *BITMAP
										if (cTokenizer.CompareToken("*BITMAP")) {
											// Get the name of the texture
											String sTexture = cTokenizer.GetNextToken();

											// Add new texture parameter to the effect if required
											if (!pFX->GetParameterManager().GetParameter(sTexture))
												pFX->GetParameterManager().CreateParameter(ParameterManager::TextureBuffer, sTexture);

											// Set the texture of the new layer
											pFXPassLayer->SetTexture(sTexture);
										}
									}
								}
							}

						// *MAP_DIFFUSE
						} else if (cTokenizer.CompareToken("*MAP_DIFFUSE")) {
							// Add a layer
							EffectPassLayer *pFXPassLayer = pFXPass->AddLayer();

							// Read until closing '}'
							while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
								// *BITMAP
								if (cTokenizer.CompareToken("*BITMAP")) {
									// Get the name of the texture
									String sTexture = cTokenizer.GetNextToken();

									// Add new texture parameter to the effect if required
									if (!pFX->GetParameterManager().GetParameter(sTexture))
										pFX->GetParameterManager().CreateParameter(ParameterManager::TextureBuffer, sTexture);

									// Set the texture of the new layer
									pFXPassLayer->SetTexture(sTexture);
								}
							}
						}
					}
				}
			}

		// *GEOMOBJECT
		} else if (cTokenizer.CompareToken("*GEOMOBJECT")) {
			// Vertex list
			uint32 nNumOfVertices = 0;
			float *pVertexList    = nullptr; // float[3]
			float *pNormalList    = nullptr; // float[3]
			// Face list
			Ase::FaceList *pFaceList = nullptr;
			Ase::TexFace  *pTexFaces = nullptr;
			// Texture coordinates list
			uint32 nNumOfTexCoords = 0;
			float *pTexCoordList   = nullptr; // float[2]

			// Read *GEOMOBJECT
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
				// *NODE_TM
				if (cTokenizer.CompareToken("*NODE_TM")) {
					// Read *NODE_TM
					while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}"))
						; // Do nothing

				// *MESH
				} else if (cTokenizer.CompareToken("*MESH")) {
					// At the moment we support only one mesh per geometry object (no animations :)
					if (!pVertexList) {
						// Read *MESH
						while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
							// *MESH_NUMVERTEX
							if (cTokenizer.CompareToken("*MESH_NUMVERTEX")) {
								if (!pVertexList) {
									nNumOfVertices = cTokenizer.GetNextToken().GetInt();
									pVertexList    = new float[nNumOfVertices*3];
								}

							// *MESH_NUMFACES
							} else if (cTokenizer.CompareToken("*MESH_NUMFACES")) {
								if (!pFaceList) {
									pFaceList			   = new Ase::FaceList;
									pFaceList->nNumOfFaces = cTokenizer.GetNextToken().GetInt();
									pFaceList->pFaces	   = new Ase::Face[pFaceList->nNumOfFaces];
								}

							// *MESH_VERTEX_LIST
							} else if (cTokenizer.CompareToken("*MESH_VERTEX_LIST")) {
								// Read *MESH_VERTEX_LIST
								while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
									// *MESH_VERTEX
									if (cTokenizer.CompareToken("*MESH_VERTEX")) {
										uint32 nVertex = cTokenizer.GetNextToken().GetInt();
										float  fX	   = cTokenizer.GetNextToken().GetFloat();
										float  fY	   = cTokenizer.GetNextToken().GetFloat();
										float  fZ	   = cTokenizer.GetNextToken().GetFloat();

										// Set vertex position
										if (pVertexList && nVertex >= 0 && nVertex < nNumOfVertices) {
											pVertexList[nVertex*3+0] = fX;
											pVertexList[nVertex*3+1] = fY;
											pVertexList[nVertex*3+2] = fZ;
										}
									}
								}

							// *MESH_FACE_LIST
							} else if (cTokenizer.CompareToken("*MESH_FACE_LIST")) {
								// Read *MESH_FACE_LIST
								while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
									// *MESH_FACE
									if (cTokenizer.CompareToken("*MESH_FACE")) {
										// *MESH_FACE %d: A: %d B: %d C: %d
										uint32 nFace = cTokenizer.GetNextToken().GetInt();
										cTokenizer.GetNextToken(); // Skip :
										cTokenizer.GetNextToken(); // Skip A
										cTokenizer.GetNextToken(); // Skip :
										int nA = cTokenizer.GetNextToken().GetInt();
										cTokenizer.GetNextToken(); // Skip B
										cTokenizer.GetNextToken(); // Skip :
										int nB = cTokenizer.GetNextToken().GetInt();
										cTokenizer.GetNextToken(); // Skip C
										cTokenizer.GetNextToken(); // Skip :
										int nC = cTokenizer.GetNextToken().GetInt();

										// Set face
										if (pFaceList && nFace >= 0 && nFace < pFaceList->nNumOfFaces) {
											Ase::Face *pFace = &pFaceList->pFaces[nFace];
											pFace->nV[0] = nA;
											pFace->nV[1] = nB;
											pFace->nV[2] = nC;
										}
									}
								}

							// *MESH_NUMTVERTEX
							} else if (cTokenizer.CompareToken("*MESH_NUMTVERTEX")) {
								if (!pTexCoordList) {
									nNumOfTexCoords = cTokenizer.GetNextToken().GetInt();
									pTexCoordList   = new float[nNumOfTexCoords*2];
								}

							// *MESH_TVERTLIST
							} else if (cTokenizer.CompareToken("*MESH_TVERTLIST")) {
								// Read *MESH_TVERTLIST
								while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
									// *MESH_TVERT
									if (cTokenizer.CompareToken("*MESH_TVERT")) {
										uint32 nVertex = cTokenizer.GetNextToken().GetInt();
										float  fX	   = cTokenizer.GetNextToken().GetFloat();
										float  fY	   = cTokenizer.GetNextToken().GetFloat();

										// Set texture coordinate
										if (pTexCoordList && nVertex >= 0 && nVertex < nNumOfTexCoords) {
											pTexCoordList[nVertex*2+0] = fX;
											pTexCoordList[nVertex*2+1] = fY;
										}
									}
								}

							// *MESH_TFACELIST
							} else if (cTokenizer.CompareToken("*MESH_TFACELIST")) {
								if (pFaceList && !pTexFaces)
									pTexFaces = new Ase::TexFace[pFaceList->nNumOfFaces];

								// Read *MESH_TFACELIST
								while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
									// *MESH_TFACE
									if (cTokenizer.CompareToken("*MESH_TFACE")) {
										uint32 nFace = cTokenizer.GetNextToken().GetInt();
										int    nA    = cTokenizer.GetNextToken().GetInt();
										int    nB    = cTokenizer.GetNextToken().GetInt();
										int    nC    = cTokenizer.GetNextToken().GetInt();

										// Set face
										if (pFaceList && nFace >= 0 && nFace < pFaceList->nNumOfFaces) {
											Ase::TexFace *pFace = &pTexFaces[nFace];
											pFace->nT[0] = nA;
											pFace->nT[1] = nB;
											pFace->nT[2] = nC;
										}
									}
								}

							// *MESH_NORMALS
							} else if (cTokenizer.CompareToken("*MESH_NORMALS")) {
								pNormalList = new float[nNumOfVertices*3];

								// Read *MESH_NORMALS
								while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
									// Ignore *MESH_FACENORMAL

									// *MESH_VERTEXNORMAL
									if (cTokenizer.CompareToken("*MESH_VERTEXNORMAL")) {
										uint32 nVertex = cTokenizer.GetNextToken().GetInt();
										float  fX	   = cTokenizer.GetNextToken().GetFloat();
										float  fY	   = cTokenizer.GetNextToken().GetFloat();
										float  fZ	   = cTokenizer.GetNextToken().GetFloat();

										// Set vertex position
										if (nVertex >= 0 && nVertex < nNumOfVertices) {
											pNormalList[nVertex*3+0] = fX;
											pNormalList[nVertex*3+1] = fY;
											pNormalList[nVertex*3+2] = fZ;
										}
									}
								}
							}
						}
					}

				// *MATERIAL_REF
				} else if (cTokenizer.CompareToken("*MATERIAL_REF")) {
					if (pFaceList)
						pFaceList->nMaterial = cTokenizer.GetNextToken().GetInt();
				}
			}

			// Optimize read data
			if (pFaceList) {
				Ase::Vertex cVertex;
				for (uint32 i=0; i<pFaceList->nNumOfFaces; i++) {
					Ase::Face    &cFace    = pFaceList->pFaces[i];
					Ase::TexFace *pTexFace = nullptr;
					if (pTexFaces) pTexFace = &pTexFaces[i];
					for (uint32 nVertex=0; nVertex<3; nVertex++) {
						// Setup face vertex
						uint32 nV = cFace.nV[nVertex];
						cVertex.nVertex = nV;

						// Position
						cVertex.fX = pVertexList[nV*3+0];
						cVertex.fY = pVertexList[nV*3+1];
						cVertex.fZ = pVertexList[nV*3+2];

						// Normal
						if (pNormalList) {
							cVertex.fNX = pNormalList[nV*3+0];
							cVertex.fNY = pNormalList[nV*3+1];
							cVertex.fNZ = pNormalList[nV*3+2];
						} else {
							cVertex.fNX = 0.0f;
							cVertex.fNY = 0.0f;
							cVertex.fNZ = 0.0f;
						}

						// Texture coordinate
						if (pTexFace) {
							uint32 nT = pTexFace->nT[nVertex];
							cVertex.fS = pTexCoordList[nT*2+0];
							cVertex.fT = pTexCoordList[nT*2+1];
						} else {
							cVertex.fS = cVertex.fT = 0.0f;
						}

						// Add vertex to list if not already in
						Ase::Vertex *pVertex = pVHTable->Add(cVertex);
						if (pVertex->nIndex >= lstVertexTex.GetNumOfElements())
							lstVertexTex.Add(pVertex);

						// Update face vertex ID
						cFace.nV[nVertex] = pVertex->nIndex;
					}
				}

				// Add face list
				lstFaceLists.Add(pFaceList);
			}

			// Update states
			if (pNormalList)
				bNormals   = true;
			if (pTexCoordList)
				bTexCoords = true;

			// Clean up
			if (pVertexList)
				delete [] pVertexList;
			if (pNormalList)
				delete [] pNormalList;
			if (pTexFaces)
				delete [] pTexFaces;
			if (pTexCoordList)
				delete [] pTexCoordList;
		}
	}
	cTokenizer.Stop();

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

	// Fill vertex buffer
	if (pVertexBuffer->Lock(Lock::WriteOnly)) {
		{ // Fill vertex buffer
			uint32 i = 0;
			Iterator<Ase::Vertex*> cIterator = lstVertexTex.GetIterator();
			while (cIterator.HasNext()) {
				const Ase::Vertex &cVertex = *cIterator.Next();

				// Position
				float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::Position));
				pfVertex[Vector3::X] = cVertex.fX;
				pfVertex[Vector3::Y] = cVertex.fY;
				pfVertex[Vector3::Z] = cVertex.fZ;

				// Normal
				if (bNormals) {
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::Normal));
					pfVertex[Vector3::X] = cVertex.fNX;
					pfVertex[Vector3::Y] = cVertex.fNY;
					pfVertex[Vector3::Z] = cVertex.fNZ;
				}

				// Texture coordinate
				if (bTexCoords) {
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::TexCoord));
					pfVertex[Vector2::X] = cVertex.fS;
					pfVertex[Vector2::Y] = cVertex.fT;
				}

				// Increment index
				i++;
			}
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Get total number of faces
	uint32 nNumOfFaces = 0;
	for (uint32 i=0; i<lstFaceLists.GetNumOfElements(); i++)
		nNumOfFaces += lstFaceLists[i]->nNumOfFaces;

	// Allocate index buffer
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(pVertexBuffer->GetNumOfElements()-1);
	pIndexBuffer->Allocate(nNumOfFaces*3, bStatic ? Usage::Static : Usage::Dynamic);

	// Fill index buffer
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
	if (pIndexBuffer->Lock(Lock::WriteOnly)) {
		uint32 nIndex       = 0;
		uint32 nStartVertex = 0;
		uint32 nVertices    = 0;

		// Check material ID's
		for (uint32 i=0; i<lstFaceLists.GetNumOfElements(); i++) {
			Ase::FaceList *pFaceList = lstFaceLists[i];
			if (pFaceList->nMaterial >= static_cast<int>(cMesh.GetNumOfMaterials()))
				pFaceList->nMaterial = -1;
		}

		// Go through all object materials
		for (int nMat=-1; nMat<static_cast<int>(cMesh.GetNumOfMaterials()); nMat++) {
			// Fill vertex buffer
			for (uint32 i=0; i<lstFaceLists.GetNumOfElements(); i++) {
				const Ase::FaceList *pFaceList = lstFaceLists[i];
				if (pFaceList->nMaterial == nMat) {
					for (uint32 nFace=0; nFace<pFaceList->nNumOfFaces; nFace++) {
						const Ase::Face &cFace = pFaceList->pFaces[nFace];

						// V0
						pIndexBuffer->SetData(nIndex++, cFace.nV[0]);

						// V1
						pIndexBuffer->SetData(nIndex++, cFace.nV[1]);

						// V2
						pIndexBuffer->SetData(nIndex++, cFace.nV[2]);

						// Update the number of vertices
						nVertices += 3;
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

	// Destroy temp data
	for (uint32 i=0; i<lstFaceLists.GetNumOfElements(); i++) {
		Ase::FaceList *pFaceList = lstFaceLists[i];
		delete [] pFaceList->pFaces;
		delete pFaceList;
	}
	lstFaceLists.Clear();
	lstVertexTex.Clear();
	delete pVHTable;

	// Done
	return true;
}

bool MeshLoaderAse::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderAse::MeshLoaderAse() :
	MethodLoad(this),
	MethodLoadParams(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderAse::~MeshLoaderAse()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
