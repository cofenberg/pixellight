/*********************************************************\
 *  File: XProcessorBinary.cpp                           *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Core/MemoryManager.h>
#include "PLDefaultFileFormats/DirectX/XBinaryParser.h"
#include "PLDefaultFileFormats/DirectX/XProcessorBinary.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
static const String g_sHeader				= "Header";
static const String g_sMaterial				= "Material";
static const String g_sFrame				= "Frame";
static const String m_sFrameTransformMatrix	= "FrameTransformMatrix";
static const String g_sMesh					= "Mesh";
static const String g_sMeshFaceWraps		= "MeshFaceWraps";
static const String g_sMeshTextureCoords	= "MeshTextureCoords";
static const String g_sMeshNormals			= "MeshNormals";
static const String g_sMeshVertexColors		= "MeshVertexColors";
static const String g_sMeshMaterialList		= "MeshMaterialList";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XRootBinary::XRootBinary(File &cFile)
{
	// Create the binary token parse tree on the runtime-stack
	XTokenRoot cRoot(cFile);

	// Transform the binary token parse tree into a X node tree
	XNode  **ppcNextFreeNode = &m_pcFirstNode;
	XToken  *pToken			 = cRoot.GetFirstChildToken();
	while (pToken) {
		XNode *pcNewNode = NULL;

		// Check token type
		switch (pToken->GetType()) {
			case XToken::TOKEN_NAME:
			{
				XTokenName *pTokenName = (XTokenName*)pToken;

				// Header
				if (g_sHeader == pTokenName->GetName()) {
					pcNewNode = ProcessHeader(*pTokenName);

				// Material
				} else if (g_sMaterial == pTokenName->GetName()) {
					// Process the material
					pcNewNode = ProcessMaterial(&pToken);

				// Mesh
				} else if (g_sMesh == pTokenName->GetName()) {
					// Process the mesh
					pcNewNode = ProcessMesh(&pToken);

				// Frame
				} else if (g_sFrame == pTokenName->GetName()) {
					// Process the frame
					pcNewNode = ProcessFrame(&pToken);

				// Unknown token name
				} else {
					// Error!
				}
				break;
			}

			default:
				// Invalid token!
				break;
		}

		// Link the new node (if there's one :)
		if (pcNewNode) {
			*ppcNextFreeNode = pcNewNode;
			ppcNextFreeNode = &pcNewNode->m_pcNextNode;
		}

		// Next token, please
		if (pToken) pToken = pToken->GetNextToken();
	}
}

/**
*  @brief
*    Destructor
*/
XRootBinary::~XRootBinary()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Processes a header block
*/
XHeader *XRootBinary::ProcessHeader(XTokenName &cTokenName)
{
	XToken *pToken = cTokenName.GetFirstChildToken();
	if (pToken) {
		if (pToken->GetType() == XToken::TOKEN_INTEGER_LIST) {
			XTokenIntList *pIntListToken = (XTokenIntList*)pToken;
			if (pIntListToken->m_nLength == 3) {
				XHeader *pcHeader = new XHeader();
				pcHeader->nMajor = (uint16)pIntListToken->m_list[0];
				pcHeader->nMinor = (uint16)pIntListToken->m_list[1];
				pcHeader->nFlags = pIntListToken->m_list[2];

				// Return the processed header
				return pcHeader;
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Error!
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Processes a material block
*/
XMaterial *XRootBinary::ProcessMaterial(XToken **ppToken)
{
	XTokenName *pTokenName = NULL;

	// Is there an (optional) material name token?
	if ((*ppToken)->GetFirstChildToken()) {
		// There's no material name
	} else {
		// Get material name token
		*ppToken = (*ppToken)->GetNextToken();
		if (*ppToken && (*ppToken)->GetType() == XToken::TOKEN_NAME) {
			pTokenName = (XTokenName*)*ppToken;
		} else {
			// Error!
		}
	}

	// Process the material
	XToken *pToken = (*ppToken)->GetFirstChildToken();
	if (pToken) {
		if (pToken->GetType() == XToken::TOKEN_FLOAT_LIST) {
			XTokenFloatList *pFloatListToken = (XTokenFloatList*)pToken;
			if (pFloatListToken->m_nLength == 11) {
				// Create the material
				XMaterial *pcMaterial = new XMaterial();

				// If there's a material name, take it
				if (pTokenName) {
					pcMaterial->pszName = pTokenName->GetName();
					pTokenName->ControlTaken();
				}

				// Face color
				pcMaterial->sFaceColor.fRed   = pFloatListToken->m_list[0];
				pcMaterial->sFaceColor.fGreen = pFloatListToken->m_list[1];
				pcMaterial->sFaceColor.fBlue  = pFloatListToken->m_list[2];
				pcMaterial->sFaceColor.fAlpha = pFloatListToken->m_list[3];

				// Power
				pcMaterial->fPower = pFloatListToken->m_list[4];

				// Specular color
				pcMaterial->sSpecularColor.fRed   = pFloatListToken->m_list[5];
				pcMaterial->sSpecularColor.fGreen = pFloatListToken->m_list[6];
				pcMaterial->sSpecularColor.fBlue  = pFloatListToken->m_list[7];

				// Emissive color
				pcMaterial->sEmissiveColor.fRed   = pFloatListToken->m_list[8];
				pcMaterial->sEmissiveColor.fGreen = pFloatListToken->m_list[9];
				pcMaterial->sEmissiveColor.fBlue  = pFloatListToken->m_list[10];

				// Next token (TextureFilename)
				pToken = pToken->GetNextToken();
				if (pToken) {
					if (pToken->GetType() == XToken::TOKEN_NAME) {
						XToken *pTextureFilenameToken = pToken->GetFirstChildToken();
						if (pTextureFilenameToken && pTextureFilenameToken->GetType() == XToken::TOKEN_STRING) {
							XTokenString *pStringToken = (XTokenString*)pTextureFilenameToken;
							pcMaterial->psTextureFilename = new XTextureFilename;
							pcMaterial->psTextureFilename->pszName = pStringToken->GetString();
							pStringToken->ControlTaken();
						} else {
							// Error!
						}
					} else {
						// Error!
					}
				}

				// Return the processed material
				return pcMaterial;
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Error!
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Processes a frame block
*/
XFrame *XRootBinary::ProcessFrame(XToken **ppToken)
{
	// Create the frame
	XFrame *pcFrame = new XFrame();

	{ // Is there an (optional) frame name token?
		XTokenName *pTokenName = NULL;
		if ((*ppToken)->GetFirstChildToken()) {
			// There's no frame name
		} else {
			// Get frame name token
			*ppToken = (*ppToken)->GetNextToken();
			if (*ppToken && (*ppToken)->GetType() == XToken::TOKEN_NAME) {
				pTokenName = (XTokenName*)*ppToken;
			} else {
				// Error!
			}
		}

		// If there's a frame name, take it
		if (pTokenName) {
			pcFrame->pszName = pTokenName->GetName();
			pTokenName->ControlTaken();
		}
	}

	// Process frame children
	XNode  **ppcNextFreeNode  = &pcFrame->m_pcFirstNode;
	XToken  *pFrameChildToken = (*ppToken)->GetFirstChildToken();
	while (pFrameChildToken) {
		if (pFrameChildToken->GetType() == XToken::TOKEN_NAME) {
			XTokenName *pTokenName = (XTokenName*)pFrameChildToken;
			XNode      *pcNewNode  = NULL;

			// FrameTransformMatrix
			if (m_sFrameTransformMatrix == pTokenName->GetName()) {
				// A frame can only have ONE transform matrix...
				if (!pcFrame->psTransformMatrix) {
					pcFrame->psTransformMatrix = ProcessFrameTransformMatrix(*pTokenName);
				} else {
					// Error!
				}

			// Mesh
			} else if (g_sMesh == pTokenName->GetName()) {
				// Process the mesh
				pcNewNode = ProcessMesh(&pFrameChildToken);

			// Frame
			} else if (g_sFrame == pTokenName->GetName()) {
				// Process the frame
				pcNewNode = ProcessFrame(&pFrameChildToken);

			// Unknown token name
			} else {
				// Error!
			}

			// Link the new node (if there's one :)
			if (pcNewNode) {
				*ppcNextFreeNode = pcNewNode;
				ppcNextFreeNode = &pcNewNode->m_pcNextNode;
			}
		} else {
			// Error!
		}

		// Next token, please
		if (pFrameChildToken) pFrameChildToken = pFrameChildToken->GetNextToken();
	}

	// Return the processed frame
	return pcFrame;
}

/**
*  @brief
*    Processes a frame transform matrix block
*/
XFrameTransformMatrix *XRootBinary::ProcessFrameTransformMatrix(XTokenName &cTokenName)
{
	XToken *pToken = cTokenName.GetFirstChildToken();
	if (pToken) {
		if (pToken->GetType() == XToken::TOKEN_FLOAT_LIST) {
			XTokenFloatList *pFloatListToken = (XTokenFloatList*)pToken;
			if (pFloatListToken->m_nLength == 16) {
				XFrameTransformMatrix *psTransformMatrix = new XFrameTransformMatrix();

				// [TODO] Checkme
//				MemoryManager::Copy(psTransformMatrix->sFrameMatrix.f, pFloatListToken->m_list, sizeof(float)*16);

				float *fDestination = psTransformMatrix->sFrameMatrix.f;
				float *fSource      = pFloatListToken->m_list;
				fDestination[0] = fSource[ 0]; fDestination[4] = fSource[ 1]; fDestination[ 8] = fSource[ 2]; fDestination[12] = fSource[ 3];
				fDestination[1] = fSource[ 4]; fDestination[5] = fSource[ 5]; fDestination[ 9] = fSource[ 6]; fDestination[13] = fSource[ 7];
				fDestination[2] = fSource[ 8]; fDestination[6] = fSource[ 9]; fDestination[10] = fSource[10]; fDestination[14] = fSource[11];
				fDestination[3] = fSource[12]; fDestination[7] = fSource[13]; fDestination[11] = fSource[14]; fDestination[15] = fSource[15];

				MemoryManager::Copy(psTransformMatrix->sFrameMatrix.f, pFloatListToken->m_list, sizeof(float)*16);

				// Return the created frame transform matrix
				return psTransformMatrix;
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Error!
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Processes a mesh block
*/
XMesh *XRootBinary::ProcessMesh(XToken **ppToken)
{
	// Create the mesh
	XMesh *pcMesh = new XMesh();

	{ // Is there an (optional) mesh name token?
		XTokenName *pTokenName = NULL;
		if ((*ppToken)->GetFirstChildToken()) {
			// There's no mesh name
		} else {
			// Get mesh name token
			*ppToken = (*ppToken)->GetNextToken();
			if (*ppToken && (*ppToken)->GetType() == XToken::TOKEN_NAME) {
				pTokenName = (XTokenName*)*ppToken;
			} else {
				// Error!
			}
		}

		// If there's a mesh name, take it
		if (pTokenName) {
			pcMesh->pszName = pTokenName->GetName();
			pTokenName->ControlTaken();
		}
	}

	// Process the mesh
	XToken *pToken = (*ppToken)->GetFirstChildToken();
	if (pToken) {
		// Next must be the number of vertices
		if (pToken->GetType() == XToken::TOKEN_INTEGER_LIST) {
			XTokenIntList *pNumOfVerticesToken = (XTokenIntList*)pToken;
			if (pNumOfVerticesToken->m_nLength == 1) {
				// Set number of vertices
				pcMesh->nVertices = pNumOfVerticesToken->m_list[0];

				// Next must be the vertices list
				pToken = pToken->GetNextToken();
				if (pToken->GetType() == XToken::TOKEN_FLOAT_LIST) {
					XTokenFloatList *pVerticesToken = (XTokenFloatList*)pToken;
					if (pVerticesToken->m_nLength == pcMesh->nVertices*3) {
						// 'Steal' the vertex data
						pcMesh->psVertices = (XVector*)pVerticesToken->m_list;
						pVerticesToken->m_nLength = 0;
						pVerticesToken->m_list    = NULL;

						// Next must be the face list
						pToken = pToken->GetNextToken();
						if (pToken->GetType() == XToken::TOKEN_INTEGER_LIST) {
							XTokenIntList *pFacesToken = (XTokenIntList*)pToken;

							// Set number of faces
							uint32 nNumOfFaces = pFacesToken->m_list[0];
							pcMesh->nFaces = nNumOfFaces;

							// Create faces
							pcMesh->psFaces = new XMeshFace[nNumOfFaces];
							uint32 *pnIndex = &pFacesToken->m_list[1];
							for (uint32 i=0; i<pcMesh->nFaces; i++) {
								XMeshFace &sFace = pcMesh->psFaces[i];
								sFace.nNumFaceVertexIndices  = *(pnIndex++);
								sFace.pnFaceVertexIndices    = new uint32[sFace.nNumFaceVertexIndices];
								sFace.pnFaceVertexIndices[0] = *(pnIndex++);
								sFace.pnFaceVertexIndices[1] = *(pnIndex++);
								sFace.pnFaceVertexIndices[2] = *(pnIndex++);
							}

							// Now to the optional data elements (if there are any *g*)
							pToken = pToken->GetNextToken();
							while (pToken) {
								if (pToken->GetType() == XToken::TOKEN_NAME) {
									XTokenName *pTokenName = (XTokenName*)pToken;

									// MeshFaceWraps
									if (g_sMeshFaceWraps == pTokenName->GetName()) {
										// A mesh can only have ONE face wraps block...
										if (!pcMesh->psFaceWraps) {
											pcMesh->psFaceWraps = ProcessMeshFaceWraps(*pTokenName);
										} else {
											// Error!
										}

									// MeshTextureCoords
									} else if (g_sMeshTextureCoords == pTokenName->GetName()) {
										// A mesh can only have ONE texture coordinates block...
										if (!pcMesh->psTextureCoords) {
											pcMesh->psTextureCoords = ProcessMeshTextureCoords(*pTokenName);
										} else {
											// Error!
										}

									// MeshNormals
									} else if (g_sMeshNormals == pTokenName->GetName()) {
										// A mesh can only have ONE normals block...
										if (!pcMesh->psNormals) {
											pcMesh->psNormals = ProcessMeshNormals(*pTokenName);
										} else {
											// Error!
										}

									// MeshVertexColors
									} else if (g_sMeshVertexColors == pTokenName->GetName()) {
										// A mesh can only have ONE vertex colors block...
										if (!pcMesh->psVertexColors) {
											pcMesh->psVertexColors = ProcessMeshVertexColors(*pTokenName);
										} else {
											// Error!
										}

									// MeshMaterialList
									} else if (g_sMeshMaterialList == pTokenName->GetName()) {
										// A mesh can only have ONE material list block...
										if (!pcMesh->psMaterialList) {
											pcMesh->psMaterialList = ProcessMeshMaterialList(*pTokenName);

											// [TODO] The 'nFaceIndexes' member should be equal to the number of faces in the parent XMesh node
//											if (pcMesh->psMaterialList && pcMesh->psMaterialList->nFaceIndexes != pcMesh->nFaces) {
//											} else {
//											}

										} else {
											// Error!
										}
									}
								} else {
									// Error!
								}

								// Next token, please
								pToken = pToken->GetNextToken();
							}
						} else {
							// Error!
						}
					} else {
						// Error!
					}
				}
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Error!
	}

	// Update statistics
	m_sStatistics.nNumOfMeshes++;
	m_sStatistics.nNumOfMeshVertices += pcMesh->nVertices;
	m_sStatistics.nNumOfMeshFaces    += pcMesh->nFaces;
	if (pcMesh->psTextureCoords) m_sStatistics.bTextureCoords = true;
	if (pcMesh->psNormals)		 m_sStatistics.bNormals       = true;

	// Return the processed mesh
	return pcMesh;
}

/**
*  @brief
*    Processes a mesh face wraps block
*/
XMeshFaceWraps *XRootBinary::ProcessMeshFaceWraps(XTokenName &cTokenName)
{
	// [TODO]
	return NULL;
}

/**
*  @brief
*    Processes a mesh texture coordinates block
*/
XMeshTextureCoords *XRootBinary::ProcessMeshTextureCoords(XTokenName &cTokenName)
{
	// Process the texture coordinates
	XToken *pToken = cTokenName.GetFirstChildToken();
	if (pToken) {
		// Next must be the number of texture coordinates
		if (pToken->GetType() == XToken::TOKEN_INTEGER_LIST) {
			XTokenIntList *pNumOfTextureCoordsToken = (XTokenIntList*)pToken;
			if (pNumOfTextureCoordsToken->m_nLength == 1) {
				XMeshTextureCoords *pTextureCoords = new XMeshTextureCoords;

				// Set number of texture coordinates
				pTextureCoords->nTextureCoords = pNumOfTextureCoordsToken->m_list[0];

				// Next must be the texture coordinates list
				pToken = pToken->GetNextToken();
				if (pToken->GetType() == XToken::TOKEN_FLOAT_LIST) {
					XTokenFloatList *pTextureCoordsToken = (XTokenFloatList*)pToken;
					if (pTextureCoordsToken->m_nLength == pTextureCoords->nTextureCoords*2) {
						// 'Steal' the texture coordinate data
						pTextureCoords->psTextureCoords = (XCoords2d*)pTextureCoordsToken->m_list;
						pTextureCoordsToken->m_nLength = 0;
						pTextureCoordsToken->m_list    = NULL;

						// Return the processed the texture coordinates
						return pTextureCoords;
					} else {
						// Error!
					}
				} else {
					// Error!
				}

				// Cleanup
				delete pTextureCoords;
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Error!
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Processes a mesh normals block
*/
XMeshNormals *XRootBinary::ProcessMeshNormals(XTokenName &cTokenName)
{
	// Process the normals
	XToken *pToken = cTokenName.GetFirstChildToken();
	if (pToken) {
		// Next must be the number of normals
		if (pToken->GetType() == XToken::TOKEN_INTEGER_LIST) {
			XTokenIntList *pNumOfNormalsToken = (XTokenIntList*)pToken;
			if (pNumOfNormalsToken->m_nLength == 1) {
				XMeshNormals *pNormals = new XMeshNormals;

				// Set number of normals
				pNormals->nNormals = pNumOfNormalsToken->m_list[0];

				// Next must be the normals list
				pToken = pToken->GetNextToken();
				if (pToken->GetType() == XToken::TOKEN_FLOAT_LIST) {
					XTokenFloatList *pNormalsToken = (XTokenFloatList*)pToken;
					if (pNormalsToken->m_nLength == pNormals->nNormals*3) {
						// 'Steal' the normal data
						pNormals->psNormals = (XVector*)pNormalsToken->m_list;
						pNormalsToken->m_nLength = 0;
						pNormalsToken->m_list    = NULL;

						// Next must be the face indices
						if (pToken->GetType() == XToken::TOKEN_INTEGER_LIST) {
							// [TODO]
							// XTokenIntList *pFaceIndicesToken = (XTokenIntList*)pToken;
						}

						// Return the processed the normals
						return pNormals;
					} else {
						// Error!
					}
				} else {
					// Error!
				}

				// Cleanup
				delete pNormals;
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Error!
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Processes a mesh vertex colors block
*/
XMeshVertexColors *XRootBinary::ProcessMeshVertexColors(XTokenName &cTokenName)
{
	// [TODO]
	return NULL;
}

/**
*  @brief
*    Processes a mesh material list block
*/
XMeshMaterialList *XRootBinary::ProcessMeshMaterialList(XTokenName &cTokenName)
{
	// Process the material list
	XToken *pToken = cTokenName.GetFirstChildToken();
	if (pToken) {
		// Next must be an integer list with at least 3 entries
		if (pToken->GetType() == XToken::TOKEN_INTEGER_LIST) {
			XTokenIntList *pIntList = (XTokenIntList*)pToken;
			if (pIntList->m_nLength > 2) {
				// Create the material list
				XMeshMaterialList *psMaterialList = new XMeshMaterialList;

				// Number of available materials
				psMaterialList->nMaterials = pIntList->m_list[0];

				// Number of face indices
				psMaterialList->nFaceIndexes = pIntList->m_list[1];

				// Face material indices
				if (psMaterialList->nFaceIndexes) {
					psMaterialList->pnFaceIndexes = new uint32[psMaterialList->nFaceIndexes];
					MemoryManager::Copy(psMaterialList->pnFaceIndexes, &pIntList->m_list[2], sizeof(uint32)*psMaterialList->nFaceIndexes);
				} else psMaterialList->pnFaceIndexes = NULL;

				// Used materials
				psMaterialList->pcFirstMaterial = NULL;
				pToken = pToken->GetFirstChildToken();
				if (pToken) {
					XNode **ppcNextFreeNode = &psMaterialList->pcFirstMaterial;
					while (pToken) {
						// Check token type
						if (pToken->GetType() == XToken::TOKEN_NAME) {
							XTokenName *pTokenName = (XTokenName*)pToken;

							// Create a new reference
							XReference *pcReference = new XReference();

							// 'Steal' the name
							pcReference->pszName = pTokenName->GetName();
							pTokenName->ControlTaken();

							// Link the new node
							*ppcNextFreeNode = pcReference;
							ppcNextFreeNode = &pcReference->m_pcNextNode;
						} else {
							// Error!
						}

						// Next token, please
						pToken = pToken->GetNextToken();
					}
				}

				// Return the processed the material list
				return psMaterialList;
			} else {
				// Error!
			}
		} else {
			// Error!
		}
	} else {
		// Error!
	}

	// Error!
	return NULL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
