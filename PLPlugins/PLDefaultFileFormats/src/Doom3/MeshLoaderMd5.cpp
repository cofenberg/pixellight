/*********************************************************\
 *  File: MeshLoaderMd5.cpp                              *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Joint.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshManager.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include <PLMesh/SkeletonManager.h>
#include "PLDefaultFileFormats/Doom3/MeshLoaderMd5.h"


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
pl_implement_class(MeshLoaderMd5)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderMd5::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderMd5::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n{}()[]=,;\"");
	cTokenizer.SetSingleChars("");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCaseSensitive(true);

	// Get and check md5 version
	bool bResult = true; // No error by default
	uint32 nVersion = 0;
	if (cTokenizer.ExpectToken("MD5Version"))
		nVersion = cTokenizer.GetNextToken().GetInt();
	switch (nVersion) {
		case 6:  bResult = LoadV6( cMesh, cTokenizer, bStatic); break;
		case 10: bResult = LoadV10(cMesh, cTokenizer, bStatic); break;
	}
	cTokenizer.Stop();
	if (bResult) {
		// Check for error
		if (cMesh.GetSkeletonHandlers()[0]) {
			Skeleton *pSkeleton = cMesh.GetSkeletonHandlers()[0]->GetResource();
			if (pSkeleton) {
				// Make the joints relative
				for (uint32 i=0; i<pSkeleton->GetNumOfElements(); i++) {
					// Get this joint
					Joint &cJoint = *pSkeleton->Get(i);

					// Get parent of this joint
					Joint *pParentJoint = pSkeleton->Get(cJoint.GetParent());
					if (pParentJoint) {
						// Get relative joint state
						Quaternion q = pParentJoint->GetRotationAbsolute();
						q.UnitInvert();
						cJoint.SetTranslation(q*(cJoint.GetTranslationAbsolute()-pParentJoint->GetTranslationAbsolute()));
						cJoint.SetRotation(cJoint.GetRotationAbsolute()*q);
					} else {
						cJoint.SetTranslation(cJoint.GetTranslationAbsolute());
						cJoint.SetRotation(cJoint.GetRotationAbsolute());
					}
				}

				// Setup skeleton
				pSkeleton->UpdateJointInformation();

				// Setup mesh
				cMesh.CalculateNormals();
				cMesh.CalculateTangentSpaceVectors();

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

bool MeshLoaderMd5::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderMd5::MeshLoaderMd5() :
	MethodLoad(this),
	MethodLoadParams(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderMd5::~MeshLoaderMd5()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Md5 version 6 loader
*/
bool MeshLoaderMd5::LoadV6(Mesh &cMesh, Tokenizer &cTokenizer, bool bStatic) const
{
	// Create the mesh and fill it with the read data
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();
	MeshMorphTarget *pMorphTarget  =  cMesh.AddMorphTarget();
	VertexBuffer	*pVertexBuffer =  pMorphTarget->GetVertexBuffer();
	IndexBuffer		*pIndexBuffer  =  pLODLevel->GetIndexBuffer();
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();

	// Create skeleton
	Skeleton *pSkeleton = cMesh.GetMeshManager()->GetSkeletonManager().Create(cMesh.GetName());

	// Add this skeleton to the skeleton list of the mesh
	SkeletonHandler *pSkeletonHandler = new SkeletonHandler();
	pSkeletonHandler->SetResource(pSkeleton);
	cMesh.GetSkeletonHandlers().Add(pSkeletonHandler);

	// First, get total number of vertices, triangles and weights
	uint32 nTotalNumOfVertices  = 0;
	uint32 nTotalNumOfTriangles = 0;
	uint32 nTotalNumOfWeights   = 0;
	cTokenizer.PushState();
	while (cTokenizer.GetNextToken().GetLength()) {
		if (cTokenizer.CompareToken("numverts")) {
			nTotalNumOfVertices += cTokenizer.GetNextToken().GetInt();
		} else if (cTokenizer.CompareToken("numtris")) {
			nTotalNumOfTriangles += cTokenizer.GetNextToken().GetInt();
		} else if (cTokenizer.CompareToken("numweights")) {
			nTotalNumOfWeights += cTokenizer.GetNextToken().GetInt();
		}
	}
	cTokenizer.PopState();

	// Allocate the vertex buffer
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
	pVertexBuffer->Allocate(nTotalNumOfVertices, bStatic ? Usage::Static : Usage::Dynamic);

	// Allocate the index buffer
	if (pIndexBuffer) {
		pIndexBuffer->SetElementTypeByMaximumIndex(nTotalNumOfVertices-1);
		pIndexBuffer->Allocate(nTotalNumOfTriangles*3, bStatic ? Usage::Static : Usage::Dynamic);
	}

	// Lock buffers
	if (!pVertexBuffer || !pIndexBuffer || !pVertexBuffer->Lock(Lock::WriteOnly) || !pIndexBuffer->Lock(Lock::WriteOnly)) {
		// Unlock the buffers
		pVertexBuffer->Unlock();
		if (pIndexBuffer)
			pIndexBuffer->Unlock();

		// Error!
		return false;
	}

	Array<VertexWeights> &lstVW = cMesh.GetVertexWeights();
	lstVW.Resize(nTotalNumOfVertices);
	cMesh.GetWeights().Resize(nTotalNumOfWeights);
	Array<Vector3> lstWeights;
	lstWeights.Resize(nTotalNumOfWeights);

	// Get the material manager
	MaterialManager &cMaterialManager = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager();

	// Start parsing
	uint32 nNumJoints		= 0;
	uint32 nNumMeshes		= 0;
	uint32 nVerticesOffset	= 0;
	uint32 nTrianglesOffset	= 0;
	uint32 nWeightsOffset	= 0;
	Array<Matrix3x3> lstJointMatrixes;
	while (cTokenizer.GetNextToken().GetLength()) {
		// numbones
		if (cTokenizer.CompareToken("numbones")) {
			nNumJoints = cTokenizer.GetNextToken().GetInt();
			lstJointMatrixes.Resize(nNumJoints);

		// numMeshes
		} else if (cTokenizer.CompareToken("numMeshes")) {
			nNumMeshes = cTokenizer.GetNextToken().GetInt();

		// Joints and meshes
		} else if (nNumJoints && nNumMeshes) {
			// bone
			if (cTokenizer.CompareToken("bone")) {
				cTokenizer.SetDelimiters(" \t\r\n()[]=,;\"");
				cTokenizer.SetSingleChars("{}");
				Joint *pJoint = NULL;

				// Read joint ID
				uint32 nID = cTokenizer.GetNextToken().GetInt();
				while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
					// name
					if (cTokenizer.CompareToken("name")) {
						// Create joint
						pJoint = pSkeleton->Create(cTokenizer.GetNextToken());

						// ID
						pJoint->SetID(nID);
					} else if (pJoint) {
						// bindpos
						if (cTokenizer.CompareToken("bindpos")) {
							float fX = cTokenizer.GetNextToken().GetFloat();
							float fY = cTokenizer.GetNextToken().GetFloat();
							float fZ = cTokenizer.GetNextToken().GetFloat();
							pJoint->SetTranslationAbsolute(Vector3(fX, fY, fZ));
						
						// bindmat
						} else if (cTokenizer.CompareToken("bindmat")) {
							Matrix3x3 &mRot = lstJointMatrixes[pJoint->GetID()];
							for (uint32 nComponent=0; nComponent<9; nComponent++)
								mRot.fM[nComponent] = cTokenizer.GetNextToken().GetFloat();

							Quaternion qQ = mRot;
							qQ.UnitInvert();
							pJoint->SetRotationAbsolute(qQ);

						// parent
						} else if (cTokenizer.CompareToken("parent")) {
							// Parent joint
							Joint *pParent = pSkeleton->Get(cTokenizer.GetNextToken());
							if (pParent) pJoint->SetParent(pParent->GetID());
						}
					}
				}

				// Calculate joint space data
				if (pJoint) {
					// Set joint space data
					Quaternion qQ = pJoint->GetRotationAbsolute();
					qQ.UnitInvert();
					pJoint->SetTranslationJointSpace(qQ*(-pJoint->GetTranslationAbsolute()));
					pJoint->SetRotationJointSpace(qQ);
				}

				cTokenizer.SetDelimiters(" \t\r\n{}()[]=,;\"");
				cTokenizer.SetSingleChars("");

			// mesh
			} else if (cTokenizer.CompareToken("mesh")) {
				// Shader
				cTokenizer.GetNextToken(); // Mesh ID
				cTokenizer.GetNextToken(); // Shader
				String sShader = cTokenizer.GetNextToken();
				int nMaterialID = -1;
				for (uint32 i=0; i<cMesh.GetNumOfMaterials(); i++) {
					if (cMesh.GetMaterial(i)->GetName() == sShader) {
						nMaterialID = i;
						break;
					}
				}
				if (nMaterialID < 0) {
					Material *pMaterial = cMaterialManager.Create(sShader);
					pMaterial->Load(pMaterial->GetName());
					cMesh.AddMaterial(pMaterial);
					nMaterialID = cMesh.GetNumOfMaterials()-1;
				}

				cTokenizer.GetNextToken(); // Skip 'numverts'
				uint32 nNumOfVertices = cTokenizer.GetNextToken().GetInt(); // Read number of vertices

				// Read in vertices
				for (uint32 i=0; i<nNumOfVertices; i++) {
					cTokenizer.GetNextToken(); // Skip 'vert'
					cTokenizer.GetNextToken(); // Skip vertex id

					// No position given because defined over weights...
					float *pfVertex = (float*)pVertexBuffer->GetData(i+nVerticesOffset, VertexBuffer::Position);
					pfVertex[0] = 0.0f;
					pfVertex[0] = 0.0f;
					pfVertex[0] = 0.0f;

					// Texture coordinate
					pfVertex = (float*)pVertexBuffer->GetData(i+nVerticesOffset, VertexBuffer::TexCoord);
					pfVertex[0] = cTokenizer.GetNextToken().GetFloat();			// U
					pfVertex[1] = 1.0f-cTokenizer.GetNextToken().GetFloat();	// V

					// Blend index
					uint32 nStartIndex = cTokenizer.GetNextToken().GetInt()+nWeightsOffset;
					uint32 nIndexCount = cTokenizer.GetNextToken().GetInt();
					lstVW[i+nVerticesOffset].GetWeights().Resize(nIndexCount);
					for (uint32 j=0; j<nIndexCount; j++)
						(lstVW[i+nVerticesOffset].GetWeights()[j]) = nStartIndex+j;
				}

				// Read triangles
				cTokenizer.GetNextToken();
				uint32 nNumOfTriangles = cTokenizer.GetNextToken().GetInt(); // Read number of triangles
				uint32 nIndex0, nIndex1, nIndex2;
				// Read in triangles
				uint32 nIndex = nTrianglesOffset*3;
				for (uint32 i=0; i<nNumOfTriangles; i++) {
					cTokenizer.GetNextToken(); // Skip 'tri'
					cTokenizer.GetNextToken(); // Skip triangle id
					nIndex0 = cTokenizer.GetNextToken().GetInt()+nVerticesOffset;
					nIndex1 = cTokenizer.GetNextToken().GetInt()+nVerticesOffset;
					nIndex2 = cTokenizer.GetNextToken().GetInt()+nVerticesOffset;
					pIndexBuffer->SetData(nIndex++, nIndex2);
					pIndexBuffer->SetData(nIndex++, nIndex1);
					pIndexBuffer->SetData(nIndex++, nIndex0);
				}

				// Add geometry
				Geometry &cGeometry = lstGeometries.Add();
				cGeometry.SetPrimitiveType(Primitive::TriangleList);
				cGeometry.SetStartIndex(nTrianglesOffset*3);
				cGeometry.SetIndexSize(nNumOfTriangles*3);
				cGeometry.SetMaterial(nMaterialID);

				// Read weights
				cTokenizer.GetNextToken();
				uint32 nNumOfWeights = cTokenizer.GetNextToken().GetInt(); // Read number of weights
				for (uint32 i=0; i<nNumOfWeights; i++) {
					uint32 nWeight = nWeightsOffset+i;
					Weight &cWeight = cMesh.GetWeights()[nWeight];
					cTokenizer.GetNextToken(); // Skip 'weight'
					cTokenizer.GetNextToken(); // Skip weight id

					// Joint
					cWeight.SetJoint(cTokenizer.GetNextToken().GetInt());

					// Bias
					cWeight.SetBias(cTokenizer.GetNextToken().GetFloat());

					// Weight
					float fX = cTokenizer.GetNextToken().GetFloat();
					float fY = cTokenizer.GetNextToken().GetFloat();
					float fZ = cTokenizer.GetNextToken().GetFloat();
					lstWeights[nWeight].SetXYZ(fX, fY, fZ);
				}

				// Calculate vertex positions
				for (uint32 i=0; i<nNumOfVertices; i++) {
					uint32 nVertex = i+nVerticesOffset;
					VertexWeights &cVertexWeights = cMesh.GetVertexWeights()[nVertex];
					Array<uint32> &lstVWeights    = cVertexWeights.GetWeights();

					uint32 nWeights = cVertexWeights.GetWeights().GetNumOfElements();
					// Loop through all vertex weights
					//	for all weights
					//		// Add weight influence
					//		vW = lstJointMatrixes[cWeight.GetJoint()]->Transform(cWeight.GetWeight());
					//		vPos += vW*cWeight.GetBias();
					Vector3 vPos = Vector3::Zero;
					for (uint32 j=0; j<nWeights; j++) {
						Weight		  &cWeight  = cMesh.GetWeights()[lstVWeights[j]];
						Matrix3x3	  &mRot     = lstJointMatrixes[cWeight.GetJoint()];
						const Vector3 &vBindPos = pSkeleton->Get(cWeight.GetJoint())->GetTranslationAbsolute();
						const Vector3 &vV       = lstWeights[lstVWeights[j]];
						float		  fBias     = cWeight.GetBias();
						vPos.x += (mRot.fM[0]*vV.x + mRot.fM[3]*vV.y + mRot.fM[6]*vV.z + vBindPos.x)*fBias;
						vPos.y += (mRot.fM[1]*vV.x + mRot.fM[4]*vV.y + mRot.fM[7]*vV.z + vBindPos.y)*fBias;
						vPos.z += (mRot.fM[2]*vV.x + mRot.fM[5]*vV.y + mRot.fM[8]*vV.z + vBindPos.z)*fBias;
					}
					float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
					pfVertex[Vector3::X] = vPos.x;
					pfVertex[Vector3::Y] = vPos.y;
					pfVertex[Vector3::Z] = vPos.z;
				}

				// Update offsets
				nVerticesOffset  += nNumOfVertices;
				nTrianglesOffset += nNumOfTriangles;
				nWeightsOffset   += nNumOfWeights;
			}
		}
	}

	// Unlock the buffers
	pVertexBuffer->Unlock();
	pIndexBuffer->Unlock();

	// Done
	return true;
}

/**
*  @brief
*    Md5 version 10 loader
*/
bool MeshLoaderMd5::LoadV10(Mesh &cMesh, Tokenizer &cTokenizer, bool bStatic) const
{
	// Create the mesh and fill it with the read data
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();
	MeshMorphTarget *pMorphTarget  =  cMesh.AddMorphTarget();
	VertexBuffer	*pVertexBuffer =  pMorphTarget->GetVertexBuffer();
	IndexBuffer		*pIndexBuffer  =  pLODLevel->GetIndexBuffer();
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();

	// Create skeleton
	Skeleton *pSkeleton = cMesh.GetMeshManager()->GetSkeletonManager().Create(cMesh.GetName());

	// Add this skeleton to the skeleton list of the mesh
	SkeletonHandler *pSkeletonHandler = new SkeletonHandler();
	pSkeletonHandler->SetResource(pSkeleton);
	cMesh.GetSkeletonHandlers().Add(pSkeletonHandler);

	// First, get total number of vertices, triangles and weights
	uint32 nTotalNumOfVertices  = 0;
	uint32 nTotalNumOfTriangles = 0;
	uint32 nTotalNumOfWeights   = 0;
	cTokenizer.PushState();
	while (cTokenizer.GetNextToken().GetLength()) {
		if (cTokenizer.CompareToken("numverts")) {
			nTotalNumOfVertices += cTokenizer.GetNextToken().GetInt();
		} else if (cTokenizer.CompareToken("numtris")) {
			nTotalNumOfTriangles += cTokenizer.GetNextToken().GetInt();
		} else if (cTokenizer.CompareToken("numweights")) {
			nTotalNumOfWeights += cTokenizer.GetNextToken().GetInt();
		}
	}
	cTokenizer.PopState();

	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
	pVertexBuffer->Allocate(nTotalNumOfVertices, bStatic ? Usage::Static : Usage::Dynamic);
	if (pIndexBuffer)
		pIndexBuffer->Allocate(nTotalNumOfTriangles*3, bStatic ? Usage::Static : Usage::Dynamic);
	Array<VertexWeights> &lstVW = cMesh.GetVertexWeights();
	lstVW.Resize(nTotalNumOfVertices);
	cMesh.GetWeights().Resize(nTotalNumOfWeights);
	Array<Vector3> lstWeights;
	lstWeights.Resize(nTotalNumOfWeights);

	// Lock buffers
	if (!pVertexBuffer || !pIndexBuffer || !pVertexBuffer->Lock(Lock::WriteOnly) || !pIndexBuffer->Lock(Lock::WriteOnly)) {
		// Unlock the buffers
		pVertexBuffer->Unlock();
		if (pIndexBuffer)
			pIndexBuffer->Unlock();

		// Error!
		return false;
	}

	// Get the material manager
	MaterialManager &cMaterialManager = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager();

	// Start parsing
	uint32 nNumJoints		= 0;
	uint32 nNumMeshes		= 0;
	uint32 nVerticesOffset	= 0;
	uint32 nTrianglesOffset	= 0;
	uint32 nWeightsOffset	= 0;
	Array<Matrix3x4> lstJointMatrixes;
	while (cTokenizer.GetNextToken().GetLength()) {
		// numJoints
		if (cTokenizer.CompareToken("numJoints")) {
			nNumJoints = cTokenizer.GetNextToken().GetInt();
			lstJointMatrixes.Resize(nNumJoints);

		// numMeshes
		} else if (cTokenizer.CompareToken("numMeshes")) {
			nNumMeshes = cTokenizer.GetNextToken().GetInt();

		// Joints and meshes
		} else if (nNumJoints && nNumMeshes) {
			// joints
			if (cTokenizer.CompareToken("joints")) {
				for (uint32 i=0; i<nNumJoints; i++) {
					// Create joint
					Joint *pJoint = pSkeleton->Create(cTokenizer.GetNextToken());

					// ID
					pJoint->SetID(i);

					// Parent joint
					pJoint->SetParent(cTokenizer.GetNextToken().GetInt());

					// Base translation
					float fX = cTokenizer.GetNextToken().GetFloat();
					float fY = cTokenizer.GetNextToken().GetFloat();
					float fZ = cTokenizer.GetNextToken().GetFloat();
					pJoint->SetTranslationAbsolute(Vector3(fX, fY, fZ));

					// Base rotation
					fX = cTokenizer.GetNextToken().GetFloat();
					fY = cTokenizer.GetNextToken().GetFloat();
					fZ = cTokenizer.GetNextToken().GetFloat();

					// Compute last component (w) of the quaternion
					float fTerm = 1.0f - (fX*fX) - (fY*fY) - (fZ*fZ);
					float fW    = fTerm < 0.0f ? 0.0f : -Math::Sqrt(fTerm);

					// Set rotation quaternion
					pJoint->SetRotationAbsolute(Quaternion(fW, fX, fY, fZ));

					// Calculate current joint matrixes
					lstJointMatrixes[i].FromQuatTrans(pJoint->GetRotationAbsolute(), pJoint->GetTranslationAbsolute());

					// Set joint space data
					Quaternion qQ = pJoint->GetRotationAbsolute();
					qQ.UnitInvert();
					pJoint->SetTranslationJointSpace(qQ*(-pJoint->GetTranslationAbsolute()));
					pJoint->SetRotationJointSpace(qQ);
				}

			// mesh
			} else if (cTokenizer.CompareToken("mesh")) {
				// Shader
				cTokenizer.GetNextToken(); // Shader
				String sShader = cTokenizer.GetNextToken();
				int nMaterialID = -1;
				for (uint32 i=0; i<cMesh.GetNumOfMaterials(); i++) {
					if (cMesh.GetMaterial(i)->GetName() == sShader) {
						nMaterialID = i;
						break;
					}
				}
				if (nMaterialID < 0) {
					Material *pMaterial = cMaterialManager.LoadResource(sShader);
					cMesh.AddMaterial(pMaterial ? pMaterial : cMaterialManager.Create(sShader));
					nMaterialID = cMesh.GetNumOfMaterials()-1;
				}

				cTokenizer.GetNextToken(); // Skip 'numverts'
				uint32 nNumOfVertices = cTokenizer.GetNextToken().GetInt(); // Read number of vertices

				// Read in vertices
				for (uint32 i=0; i<nNumOfVertices; i++) {
					cTokenizer.GetNextToken(); // Skip 'vert'
					cTokenizer.GetNextToken(); // Skip vertex id

					// No position given because defined over weights...
					float *pfVertex = (float*)pVertexBuffer->GetData(i+nVerticesOffset, VertexBuffer::Position);
					pfVertex[0] = 0.0f;
					pfVertex[0] = 0.0f;
					pfVertex[0] = 0.0f;

					// Texture coordinate
					pfVertex = (float*)pVertexBuffer->GetData(i+nVerticesOffset, VertexBuffer::TexCoord);
					pfVertex[0] = cTokenizer.GetNextToken().GetFloat();	// U
					pfVertex[1] = cTokenizer.GetNextToken().GetFloat();	// V

					// Blend index
					uint32 nStartIndex = cTokenizer.GetNextToken().GetInt()+nWeightsOffset;
					uint32 nIndexCount = cTokenizer.GetNextToken().GetInt();
					lstVW[i+nVerticesOffset].GetWeights().Resize(nIndexCount);
					for (uint32 j=0; j<nIndexCount; j++)
						lstVW[i+nVerticesOffset].GetWeights()[j] = nStartIndex+j;
				}

				// Read triangles
				cTokenizer.GetNextToken();
				uint32 nNumOfTriangles = cTokenizer.GetNextToken().GetInt(); // Read number of triangles
				uint32 nIndex0, nIndex1, nIndex2;
				// Read in triangles
				uint32 nIndex = nTrianglesOffset*3;
				for (uint32 i=0; i<nNumOfTriangles; i++) {
					cTokenizer.GetNextToken(); // Skip 'tri'
					cTokenizer.GetNextToken(); // Skip triangle id
					nIndex0 = cTokenizer.GetNextToken().GetInt()+nVerticesOffset;
					nIndex1 = cTokenizer.GetNextToken().GetInt()+nVerticesOffset;
					nIndex2 = cTokenizer.GetNextToken().GetInt()+nVerticesOffset;
					pIndexBuffer->SetData(nIndex++, nIndex2);
					pIndexBuffer->SetData(nIndex++, nIndex1);
					pIndexBuffer->SetData(nIndex++, nIndex0);
				}

				// Add geometry
				Geometry &cGeometry = lstGeometries.Add();
				cGeometry.SetPrimitiveType(Primitive::TriangleList);
				cGeometry.SetStartIndex(nTrianglesOffset*3);
				cGeometry.SetIndexSize(nNumOfTriangles*3);
				cGeometry.SetMaterial(nMaterialID);

				// Read weights
				cTokenizer.GetNextToken();
				uint32 nNumOfWeights = cTokenizer.GetNextToken().GetInt(); // Read number of weights
				for (uint32 i=0; i<nNumOfWeights; i++) {
					uint32 nWeight = nWeightsOffset+i;
					Weight &cWeight = cMesh.GetWeights()[nWeight];
					cTokenizer.GetNextToken(); // Skip 'weight'
					cTokenizer.GetNextToken(); // Skip weight id

					// Joint
					cWeight.SetJoint(cTokenizer.GetNextToken().GetInt());

					// Bias
					cWeight.SetBias(cTokenizer.GetNextToken().GetFloat());

					// Weight
					float fX = cTokenizer.GetNextToken().GetFloat();
					float fY = cTokenizer.GetNextToken().GetFloat();
					float fZ = cTokenizer.GetNextToken().GetFloat();
					lstWeights[nWeight].SetXYZ(fX, fY, fZ);
				}

				// Calculate vertex positions
				for (uint32 i=0; i<nNumOfVertices; i++) {
					uint32 nVertex = i+nVerticesOffset;
					VertexWeights &cVertexWeights = cMesh.GetVertexWeights()[nVertex];
					Array<uint32> &lstVWeights    = cVertexWeights.GetWeights();

					uint32 nWeights = cVertexWeights.GetWeights().GetNumOfElements();
					// Loop through all vertex weights
					//	for all weights
					//		// Add weight influence
					//		vW = lstJointMatrixes[cWeight.GetJoint()]->Transform(cWeight.GetWeight());
					//		vPos += vW*cWeight.GetBias();
					Vector3 vPos = Vector3::Zero;
					for (uint32 j=0; j<nWeights; j++) {
						Weight		  &cWeight = cMesh.GetWeights()[lstVWeights[j]];
						Matrix3x4	  &mTrans  = lstJointMatrixes[cWeight.GetJoint()];
						const Vector3 &vV      = lstWeights[lstVWeights[j]];
						float		  fBias    = cWeight.GetBias();
						vPos.x += (mTrans.xx*vV.x + mTrans.xy*vV.y + mTrans.xz*vV.z + mTrans.xw)*fBias;
						vPos.y += (mTrans.yx*vV.x + mTrans.yy*vV.y + mTrans.yz*vV.z + mTrans.yw)*fBias;
						vPos.z += (mTrans.zx*vV.x + mTrans.zy*vV.y + mTrans.zz*vV.z + mTrans.zw)*fBias;
					}
					float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
					pfVertex[Vector3::X] = vPos.x;
					pfVertex[Vector3::Y] = vPos.y;
					pfVertex[Vector3::Z] = vPos.z;
				}

				// Update offsets
				nVerticesOffset  += nNumOfVertices;
				nTrianglesOffset += nNumOfTriangles;
				nWeightsOffset   += nNumOfWeights;
			}
		}
	}

	// Unlock the buffers
	pVertexBuffer->Unlock();
	pIndexBuffer->Unlock();

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
