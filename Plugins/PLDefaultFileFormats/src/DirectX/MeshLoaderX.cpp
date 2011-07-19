/*********************************************************\
 *  File: MeshLoaderX.cpp                                *
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
#include <PLCore/Log/Log.h>
#include <PLCore/File/Url.h>
#include <PLCore/File/File.h>
#include <PLCore/String/Tokenizer.h>
#include <PLCore/Core/MemoryManager.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/DirectX/XProcessorText.h"
#include "PLDefaultFileFormats/DirectX/XProcessorBinary.h"
#include "PLDefaultFileFormats/DirectX/MeshLoaderX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshLoaderX)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderX::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderX::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Read the file header and validate it
	XFileHeader sFileHeader;
	if (!cFile.Read(&sFileHeader, 1, sizeof(XFileHeader)))
		return false; // Error!

	// Check the signature (must be "xof")
	if (sFileHeader.nSignature[0] != 'x' || sFileHeader.nSignature[1] != 'o' || sFileHeader.nSignature[2] != 'f') {
		// Error!
		PL_LOG(Error, "Not DirectX x file")
		return false;
	}

/*  // [TODO] Do we really need a version check? (there are multiple versions...)
	// Check minor version (must be "03")
	if (sFileHeader.nMinor[0] != '0' || sFileHeader.nMinor[1] != '3') {
		// Error!
		PL_LOG(Error, "Invalid minor version (must be '03')")
		return false;
	}

	// Check major version (must be "02")
	if (sFileHeader.nMajor[0] != '0' || sFileHeader.nMajor[1] != '2') {
		// Error!
		PL_LOG(Error, "Invalid major version (must be '02')")
		return false;
	}
*/
	// Check accuracy (only "0032" supported)
	if (sFileHeader.nAccuracy[0] != '0' || sFileHeader.nAccuracy[1] != '0' ||
		sFileHeader.nAccuracy[2] != '3' || sFileHeader.nAccuracy[3] != '2') {
		// Error!
		PL_LOG(Error, "Unsupported accuracy (only '0032' supported)")
		return false;
	}

	// Check type and try to process the file
	XRoot *pXRoot;
	if (sFileHeader.nType[0] == 't' && sFileHeader.nType[1] == 'x' && sFileHeader.nType[2] == 't') {
		// Text file
		Tokenizer cTokenizer;
		cTokenizer.SetSingleLineComment("//#");
		cTokenizer.Start(cFile);
		pXRoot = new XRootText(cTokenizer);
		cTokenizer.Stop();

	} else if (sFileHeader.nType[0] == 'b' && sFileHeader.nType[1] == 'i' && sFileHeader.nType[2] == 'n') {
		// Binary file
		pXRoot = new XRootBinary(cFile);

	} else {
		// Error!
		PL_LOG(Error, "Unsupported type (only 'txt' and 'bin' supported)")
		return false;
	}

	// Create the mesh
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();
	MeshMorphTarget *pMorphTarget = cMesh.AddMorphTarget();
	VertexBuffer    *pVertexBuffer =  pMorphTarget->GetVertexBuffer();
	IndexBuffer     *pIndexBuffer  =  pLODLevel->GetIndexBuffer();
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();

	// Get the statistics of the x file
	const XRoot::Statistics &sStatistics = pXRoot->GetStatistics();

	// Create the vertex buffer
	if (pVertexBuffer && pIndexBuffer) {
		// There's always a position
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);

		// Are there texture coordinates?
		if (sStatistics.bTextureCoords)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);

		// Are there vertex normals?
		if (sStatistics.bNormals)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal, 0, VertexBuffer::Float3);

		// Allocate the vertex position
		pVertexBuffer->Allocate(sStatistics.nNumOfMeshVertices, bStatic ? Usage::Static : Usage::Dynamic);

		// Lock the vertex buffer
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// There are always 3 indices per face
			uint32 nNumOfIndices = sStatistics.nNumOfMeshFaces*3;

			// Create the index buffer
			pIndexBuffer->SetElementTypeByMaximumIndex(sStatistics.nNumOfMeshVertices-1);
			pIndexBuffer->Allocate(nNumOfIndices, Usage::Static);

			// Process the x-file information
			uint32 nVertexOffset = 0;
			uint32 nIndexOffset  = 0;
			Array<XMesh*> lstXMeshes;
			ProcessNodes(cMesh, pXRoot->GetFirstChildNode(), Matrix4x4::Identity,
						 nVertexOffset, nIndexOffset, lstXMeshes);

			// Lock the index buffer and fill it sorted by material usage
			if (pIndexBuffer->Lock(Lock::WriteOnly)) {
				uint32 nIndex = 0;

				// Loop through all materials
				for (uint32 nMaterial=0; nMaterial<cMesh.GetNumOfMaterials(); nMaterial++) {
					Material &cMaterial   = *cMesh.GetMaterial(nMaterial);
					uint32    nStartIndex = nIndex;

					// Loop through all meshes
					for (uint32 nMesh=0; nMesh<lstXMeshes.GetNumOfElements(); nMesh++) {
						XMesh             &cXMesh         = *lstXMeshes[nMesh];
						XMeshMaterialList *psMaterialList = cXMesh.psMaterialList;
						if (psMaterialList) {
							// Here's a mysterious thing a few testet meshes used: If the number of faces in the
							// material list is not equal to the number of mesh faces, and there's only one entry
							// in the material ist seems to mean: Use this one material for all faces of the mesh
							if (psMaterialList->nFaceIndexes != cXMesh.nFaces && psMaterialList->nFaceIndexes == 1) {
								// One material for ALL faces...
								uint32 nFaceMaterialIndex        = psMaterialList->pnFaceIndexes[0];
								uint32 nCurrentFaceMaterialIndex = 0;

								// Find the indexed material
								if (psMaterialList->pcFirstMaterial) {
									XNode *pcMaterial = psMaterialList->pcFirstMaterial;
									while (pcMaterial) {
										// Indexed material found?
										if (nCurrentFaceMaterialIndex == nFaceMaterialIndex) {
											// Is this the current processed material?
											if (pcMaterial->GetType() == XNode::Reference) {
												// [TODO] Use a kind of name table because we can't ensure the material name is correct!
												if (cMaterial.GetName() == static_cast<XReference*>(pcMaterial)->pszName) {
													for (uint32 nFaceIndex=0; nFaceIndex<cXMesh.nFaces; nFaceIndex++) {
														// Jap, add the vertex indices
														const XMeshFace &sFace = cXMesh.psFaces[nFaceIndex];

														// Loop through all vertex indices of the face
														for (uint32 nVertexIndex=0; nVertexIndex<sFace.nNumFaceVertexIndices; nVertexIndex++)
															pIndexBuffer->SetData(nIndex++, sFace.pnFaceVertexIndices[nVertexIndex]);
													}
												}
											} else {
												// [TOOD] Do we need to do in here anything?
											}
											break;
										}

										// Next material
										pcMaterial = pcMaterial->GetNextNode();
										nCurrentFaceMaterialIndex++;
									}
								} else {
									// [TOOD] Do we need to do in here anything?
								}

							} else {
								// Each face has it's own material index...
								uint32 nNumOfFaceIndexes = psMaterialList->nFaceIndexes < cXMesh.nFaces ? psMaterialList->nFaceIndexes : cXMesh.nFaces;
								for (uint32 nFaceIndex=0; nFaceIndex<nNumOfFaceIndexes; nFaceIndex++) {
									uint32 nFaceMaterialIndex        = psMaterialList->pnFaceIndexes[nFaceIndex];
									uint32 nCurrentFaceMaterialIndex = 0;

									// Find the indexed material
									if (psMaterialList->pcFirstMaterial) {
										XNode *pcMaterial = psMaterialList->pcFirstMaterial;
										while (pcMaterial) {
											// Indexed material found?
											if (nCurrentFaceMaterialIndex == nFaceMaterialIndex) {
												// Is this the current processed material?
												if (pcMaterial->GetType() == XNode::Reference) {
													// [TODO] Use a kind of name table because we can't ensure the material name is correct!
													if (cMaterial.GetName() == static_cast<XReference*>(pcMaterial)->pszName) {
														// Jap, add the vertex indices
														const XMeshFace &sFace = cXMesh.psFaces[nFaceIndex];

														// Loop through all vertex indices of the face
														for (uint32 nVertexIndex=0; nVertexIndex<sFace.nNumFaceVertexIndices; nVertexIndex++)
															pIndexBuffer->SetData(nIndex++, sFace.pnFaceVertexIndices[nVertexIndex]);
													}
												} else {
													// [TOOD] Do we need to do in here anything?
												}
												break;
											}

											// Next material
											pcMaterial = pcMaterial->GetNextNode();
											nCurrentFaceMaterialIndex++;
										}
									} else {
										// [TOOD] Do we need to do in here anything?
									}
								}
							}
						} else {
							// [TOOD] Do we need to do in here anything?
						}
					}

					// Is there at least one face using this material?
					if (nStartIndex != nIndex) {
						// Add geometry
						Geometry &cGeometry = lstGeometries.Add();
						cGeometry.SetPrimitiveType(Primitive::TriangleList);
						cGeometry.SetStartIndex(nStartIndex);
						cGeometry.SetIndexSize(nIndex-nStartIndex);
						cGeometry.SetMaterial(nMaterial);
					}
				}

				// Check whether all indices were set correctly
				if (pIndexBuffer->GetNumOfElements() != nIndex) {
					// [TOOD] Do we need to do in here anything?
				}

				// Unlock the index buffer
				pIndexBuffer->Unlock();
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}
	}

	// Destroy the parsed token tree
	delete pXRoot;

	// Add dummy material?
	if (!cMesh.GetNumOfMaterials())
		cMesh.AddMaterial(cMesh.GetRenderer()->GetRendererContext().GetMaterialManager().GetStandard());

	// Done
	return true;
}

bool MeshLoaderX::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderX::MeshLoaderX()
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderX::~MeshLoaderX()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Processes a block of DirectX nodes
*/
void MeshLoaderX::ProcessNodes(Mesh &cMesh, XNode *pXNode, const Matrix4x4 &mTransform,
							   uint32 &nVertexOffset, uint32 &nIndexOffset, Array<XMesh*> &lstXMeshes) const
{
	// Process nodes
	while (pXNode) {
		// Check the node type
		switch (pXNode->GetType()) {
			case XNode::Header:
				// We don't care about the header :)
				break;

			case XNode::Material:
			{
				// Create a PixelLight material
				XMaterial *pXMaterial = static_cast<XMaterial*>(pXNode);
				// [TODO] What do do if there's already a material with the given name??
				Material  *pMaterial  = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager().Create(pXMaterial->pszName);
				if (pMaterial) {
					ParameterManager &cParameterManager = pMaterial->GetParameterManager();

					// Set 'DiffuseColor'-parameter, we don't need/support "pXMaterial->sFaceColor.fAlpha"
					cParameterManager.SetParameter3f("DiffuseColor", pXMaterial->sFaceColor.fRed, pXMaterial->sFaceColor.fGreen, pXMaterial->sFaceColor.fBlue);

					// Set 'SpecularColor'-parameter
					cParameterManager.SetParameter3f("SpecularColor", pXMaterial->sSpecularColor.fRed, pXMaterial->sSpecularColor.fGreen, pXMaterial->sSpecularColor.fBlue);

					// Set 'SpecularExponent'-parameter
					cParameterManager.SetParameter1f("SpecularExponent", pXMaterial->fPower);

					// Set 'EmissiveColor'-parameter
					cParameterManager.SetParameter3f("EmissiveColor", pXMaterial->sEmissiveColor.fRed, pXMaterial->sEmissiveColor.fGreen, pXMaterial->sEmissiveColor.fBlue);

					// Add 'DiffuseMap'-parameter
					if (pXMaterial->psTextureFilename) {
						Parameter *pParameter = cParameterManager.CreateParameter(PLRenderer::Parameters::TextureBuffer, Material::DiffuseMap);
						if (pParameter) {
							// We really need a file extension, if there's no one add '.dds'
							String sExtension = Url(pXMaterial->psTextureFilename->pszName).GetExtension();
							pParameter->SetValueTexture("Data/Textures/" + (sExtension.GetLength() ? String(pXMaterial->psTextureFilename->pszName) : String(pXMaterial->psTextureFilename->pszName) + ".dds"));
						}
					}

					// Finally, add the new PixelLight material to the mesh
					cMesh.AddMaterial(pMaterial);
				}
				break;
			}

			case XNode::Mesh:
			{
				uint32 nVertexOffsetAdd = 0;
				XMesh *pXMesh = static_cast<XMesh*>(pXNode);
				lstXMeshes.Add(pXMesh);

				// Fill vertex data
				if (pXMesh->psVertices) {
					MeshMorphTarget *pMorphTarget = cMesh.GetMorphTarget();
					if (pMorphTarget && pMorphTarget->GetVertexBuffer()) {
						VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
						nVertexOffsetAdd = pXMesh->nVertices;

						// Position
						for (uint32 i=0; i<pXMesh->nVertices; i++) {
							float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertexOffset+i, VertexBuffer::Position));
							if (pfVertex) {
								const XVector &sVector = pXMesh->psVertices[i];

								// Calculate absolute vertex position
								Vector3 vVector(sVector.x, sVector.y, sVector.z);
								Vector3 vVectorT = mTransform*vVector;

								// Fill vertex data
								pfVertex[0] = vVectorT.x;
								pfVertex[1] = vVectorT.y;
								pfVertex[2] = vVectorT.z;
							}
						}

						// Texture coordinates
						XMeshTextureCoords *psTextureCoords = pXMesh->psTextureCoords;
						if (psTextureCoords && psTextureCoords->psTextureCoords) {
							uint32 nTextureCoords = psTextureCoords->nTextureCoords < pVertexBuffer->GetNumOfElements() ? psTextureCoords->nTextureCoords : pVertexBuffer->GetNumOfElements();
							for (uint32 i=0; i<nTextureCoords; i++) {
								float           *pfVertex  = static_cast<float*>(pVertexBuffer->GetData(nVertexOffset+i, VertexBuffer::TexCoord));
								const XCoords2d &sCoords2D = psTextureCoords->psTextureCoords[i];
								pfVertex[0] = sCoords2D.u;
								pfVertex[1] = sCoords2D.v;
							}
						}

						// Normals
						XMeshNormals *psNormals = pXMesh->psNormals;
						if (psNormals && psNormals->psNormals) {
							uint32 nNormals = psNormals->nNormals < pVertexBuffer->GetNumOfElements() ? psNormals->nNormals : pVertexBuffer->GetNumOfElements();
							for (uint32 i=0; i<nNormals; i++) {
								float          *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertexOffset+i, VertexBuffer::Normal));
								const  XVector &sVector  = psNormals->psNormals[i];

								// Calculate absolute vertex normal rotation
								Vector3 vVector(sVector.x, sVector.y, sVector.z);
								Vector3 vVectorT = mTransform.RotateVector(vVector);
								vVectorT.Normalize();

								// Fill vertex data
								pfVertex[0] = vVectorT.x;
								pfVertex[1] = vVectorT.y;
								pfVertex[2] = vVectorT.z;
							}
						}
					}
				}

				// Update index data
				if (pXMesh->psFaces) {
					// Loop through all faces and make the relative face vertex indices absolute
					for (uint32 nFace=0; nFace<pXMesh->nFaces; nFace++) {
						const XMeshFace &sFace = pXMesh->psFaces[nFace];
						for (uint32 nIndex=0; nIndex<sFace.nNumFaceVertexIndices; nIndex++)
							sFace.pnFaceVertexIndices[nIndex] += nVertexOffset;
					}
				}

				// Update the vertex offset
				nVertexOffset += nVertexOffsetAdd;
				break;
			}

			case XNode::Frame:
			{
				XFrame *pXFrame = static_cast<XFrame*>(pXNode);
				ProcessNodes(cMesh, pXFrame->GetFirstChildNode(), pXFrame->psTransformMatrix ? mTransform*Matrix4x4(pXFrame->psTransformMatrix->sFrameMatrix.f) : mTransform,
							 nVertexOffset, nIndexOffset, lstXMeshes);
				break;
			}

			default:
				// Invalid node!
				break;
		}

		// Next X node, please
		pXNode = pXNode->GetNextNode();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
