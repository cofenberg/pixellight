/*********************************************************\
 *  File: SceneLoaderX.cpp                               *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/Tools/Stopwatch.h>
#include <PLGeneral/File/Url.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLMesh/MeshManager.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodes/SNMesh.h>
#include "PLDefaultFileFormats/DirectX/XProcessorText.h"
#include "PLDefaultFileFormats/DirectX/XProcessorBinary.h"
#include "PLDefaultFileFormats/DirectX/SceneLoaderX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneLoaderX)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SceneLoaderX::Load(SceneContainer &cContainer, File &cFile)
{
	// Start the stopwatch
	Stopwatch cStopwatch;
	cStopwatch.Start();

	// Deactivate the container during loading
	bool bActive = cContainer.IsActive();
	cContainer.SetActive(false);

	// Read the file header and validate it
	XFileHeader sFileHeader;
	if (!cFile.Read(&sFileHeader, 1, sizeof(XFileHeader))) return false; // Error!

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

	// Initializes the statistics
	SInstance sInstance;
	sInstance.nTotalNumOfContainers = 0;
	sInstance.nTotalNumOfNodes      = 0;

	// Process the x-file information
	ProcessNodes(sInstance, cContainer, pXRoot->GetFirstChildNode(), cContainer.GetName());

	// Calculate the axis aligned bounding box of the container
	cContainer.CalculateAABoundingBox();

	// Destroy the parsed token tree
	delete pXRoot;

	// Reset container active state
	cContainer.SetActive(bActive);

	// Stop the stopwatch
	cStopwatch.Stop();

	// Show statistics within the log
	PL_LOG(Debug, "\n")
	PL_LOG(Debug, "Scene statistics of '" + cFile.GetUrl().GetNativePath() + '\'')
	PL_LOG(Debug, "Loading time: " + String::Format("%g", cStopwatch.GetSeconds()) + " sec");
	PL_LOG(Debug, String("Total number of containers within the scene: (without the root container itself) ") + int(sInstance.nTotalNumOfContainers))
	PL_LOG(Debug, String("Total number of nodes (without containers) within the scene: ") + int(sInstance.nTotalNumOfNodes))
	PL_LOG(Debug, String("Total number of materials within the scene: ") + int(sInstance.lstMaterials.GetNumOfElements()))
	PL_LOG(Debug, "\n")

	// Done
	return true;
}

bool SceneLoaderX::Save(SceneContainer &cContainer, File &cFile)
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
SceneLoaderX::SceneLoaderX() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
SceneLoaderX::~SceneLoaderX()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Processes a block of DirectX nodes
*/
void SceneLoaderX::ProcessNodes(SInstance &sInstance, SceneContainer &cContainer, XNode *pXNode, const String &sResourceName) const
{
	while (pXNode) {
		// Check the node type
		switch (pXNode->GetType()) {
			case XNode::Header:
				// We don't care about the header :)
				break;

			case XNode::Material:
			{
				// Create a PixelLight material
				XMaterial *pXMaterial = (XMaterial*)pXNode;
				// [TODO] What do do if there's already a material with the given name??
				Material  *pMaterial  = cContainer.GetSceneContext()->GetRendererContext().GetMaterialManager().Create(pXMaterial->pszName);
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

					// Finally, add the new PixelLight material to our list
					sInstance.lstMaterials.Add(pMaterial);
				}
				break;
			}

			case XNode::Mesh:
			{
				XMesh *pXMesh = (XMesh*)pXNode;

				// Create a new mesh scene node
				SNMesh *pMeshSceneNode = (SNMesh*)cContainer.Create("PLScene::SNMesh", pXMesh->pszName, "Flags=\"Automatic\"");
				if (pMeshSceneNode) {
					// Update the statistics
					sInstance.nTotalNumOfNodes++;

					// Process the mesh
					ProcessMesh(sInstance, *pXMesh, *pMeshSceneNode, sResourceName + '_' + pXMesh->pszName);
				}
				break;
			}

			case XNode::Frame:
			{
				XFrame *pXFrame     = (XFrame*)pXNode;
				XNode  *pXChildNode = pXFrame->GetFirstChildNode();
				if (pXChildNode) {
					// Before we just create a new scene container, check wether a simple
					// scene node will also do the job
					if (pXChildNode->GetType() == XNode::Mesh && !pXChildNode->GetNextNode()) {
						// Create a new mesh scene node
						String  sName          = String(pXFrame->pszName) + '_' + ((XMesh*)pXChildNode)->pszName;
						SNMesh *pMeshSceneNode = (SNMesh*)cContainer.Create("PLScene::SNMesh", sName, "Flags=\"Automatic\"");
						if (pMeshSceneNode) {
							// Update the statistics
							sInstance.nTotalNumOfNodes++;

							// Set the transform matrix (if there's one)
							if (pXFrame->psTransformMatrix)
								pMeshSceneNode->GetTransform().SetMatrix(Matrix4x4(pXFrame->psTransformMatrix->sFrameMatrix.f));

							// Process the mesh
							ProcessMesh(sInstance, *((XMesh*)pXChildNode), *pMeshSceneNode, sResourceName + '_' + sName);
						}
					} else {
						// Create a new scene container
						SceneContainer *pContainer = (SceneContainer*)cContainer.Create("PLScene::SceneContainer", pXFrame->pszName, "Flags=\"Automatic\"");
						if (pContainer) {
							// Update the statistics
							sInstance.nTotalNumOfContainers++;

							// Set the transform matrix (if there's one)
							if (pXFrame->psTransformMatrix)
								pContainer->GetTransform().SetMatrix(Matrix4x4(pXFrame->psTransformMatrix->sFrameMatrix.f));

							// Process the frame
							ProcessNodes(sInstance, *pContainer, pXFrame->GetFirstChildNode(), sResourceName + '_' + pXFrame->pszName);

							// Calculate the axis aligned bounding box of the container
							pContainer->CalculateAABoundingBox();
						}
					}
				}
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

/**
*  @brief
*    Processes a DirectX mesh block
*/
void SceneLoaderX::ProcessMesh(SInstance &sInstance, XMesh &cXMesh, SNMesh &cMeshSceneNode, const String &sResourceName) const
{
	// Get the mesh manager
	MeshManager &cMeshManager = cMeshSceneNode.GetSceneContext()->GetMeshManager();

	// Get an unused mesh name
	String sMeshName = sResourceName;
	if (cMeshManager.Get(sMeshName)) {
		int i = 0;
		do {
			sMeshName = sResourceName + '_' + i;
			i++;
		} while (cMeshManager.Get(sMeshName));
	}

	// Create the mesh
	Mesh *pMesh = cMeshManager.Create(sMeshName);

	// Add morph target
	MeshMorphTarget *pMorphTarget = pMesh->AddMorphTarget();
	if (pMorphTarget) {
		// Create the vertex buffer
		VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		if (cXMesh.psTextureCoords)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
		if (cXMesh.psNormals)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal, 0, VertexBuffer::Float3);
		pVertexBuffer->Allocate(cXMesh.nVertices, Usage::Static);

		// Lock the vertex buffer
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Position
			for (uint32 i=0; i<cXMesh.nVertices; i++) {
				float *pfVertex = (float*)pVertexBuffer->GetData(i, VertexBuffer::Position);
				if (pfVertex) {
					const XVector &sVector = cXMesh.psVertices[i];

					// Fill vertex data
					pfVertex[0] = sVector.x;
					pfVertex[1] = sVector.y;
					pfVertex[2] = sVector.z;
				}
			}

			// Texture coordinates
			XMeshTextureCoords *psTextureCoords = cXMesh.psTextureCoords;
			if (psTextureCoords && psTextureCoords->psTextureCoords) {
				uint32 nTextureCoords = psTextureCoords->nTextureCoords < pVertexBuffer->GetNumOfElements() ? psTextureCoords->nTextureCoords : pVertexBuffer->GetNumOfElements();
				for (uint32 i=0; i<nTextureCoords; i++) {
					float          *pfVertex   = (float*)pVertexBuffer->GetData(i, VertexBuffer::TexCoord);
					const XCoords2d &sCoords2D = psTextureCoords->psTextureCoords[i];
					pfVertex[0] = sCoords2D.u;
					pfVertex[1] = sCoords2D.v;
				}
			}

			// Normals
			XMeshNormals *psNormals = cXMesh.psNormals;
			if (psNormals && psNormals->psNormals) {
				uint32 nNormals = psNormals->nNormals < pVertexBuffer->GetNumOfElements() ? psNormals->nNormals : pVertexBuffer->GetNumOfElements();
				for (uint32 i=0; i<nNormals; i++) {
					float         *pfVertex = (float*)pVertexBuffer->GetData(i, VertexBuffer::Normal);
					const XVector &sVector  = psNormals->psNormals[i];

					// Fill vertex data
					pfVertex[0] = sVector.x;
					pfVertex[1] = sVector.y;
					pfVertex[2] = sVector.z;
				}
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}
	}

	// Add LOD level
	MeshLODLevel *pLODLevel = pMesh->AddLODLevel();
	if (pLODLevel) {
		pLODLevel->CreateGeometries();
		pLODLevel->CreateIndexBuffer();

		// Setup index buffer
		IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
		if (pIndexBuffer) {
			// There are always 3 indices per face
			uint32 nNumOfIndices = cXMesh.nFaces*3;

			// Create the index buffer
			pIndexBuffer->SetElementTypeByMaximumIndex(cXMesh.nVertices-1);
			pIndexBuffer->Allocate(nNumOfIndices, Usage::Static);

			// Lock the index buffer and fill it sorted by material usage
			if (pIndexBuffer->Lock(Lock::WriteOnly)) {
				Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
				uint32			 nIndex		   = 0;

				// Loop through all materials
				for (uint32 nMaterial=0; nMaterial<sInstance.lstMaterials.GetNumOfElements(); nMaterial++) {
					Material &cMaterial   = *sInstance.lstMaterials[nMaterial];
					uint32    nStartIndex = nIndex;

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
											if (cMaterial.GetName() == ((XReference*)pcMaterial)->pszName) {
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
												if (cMaterial.GetName() == ((XReference*)pcMaterial)->pszName) {
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

					// Is there at least one face using this material?
					if (nStartIndex != nIndex) {
						// Add geometry
						Geometry &cGeometry = lstGeometries.Add();
						cGeometry.SetPrimitiveType(Primitive::TriangleList);
						cGeometry.SetStartIndex(nStartIndex);
						cGeometry.SetIndexSize(nIndex-nStartIndex);
						cGeometry.SetMaterial(pMesh->GetNumOfMaterials());
						pMesh->AddMaterial(&cMaterial);
					}
				}

				// Check whether all indices were set correctly
				if (pIndexBuffer->GetNumOfElements() != nIndex) {
					// [TOOD] Do we need to do in here anything?
				}

				// Unlock the index buffer
				pIndexBuffer->Unlock();
			}
		}
	}

	// Add dummy material?
	if (!pMesh->GetNumOfMaterials())
		pMesh->AddMaterial(cMeshSceneNode.GetSceneContext()->GetRendererContext().GetMaterialManager().GetStandard());

	// Finally, give the mesh scene node this new mesh
	cMeshSceneNode.LoadMesh(sMeshName);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
