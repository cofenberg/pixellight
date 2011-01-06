/*********************************************************\
 *  File: MeshLoader3ds.cpp                              *
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
#include <lib3ds/io.h>
#include <lib3ds/file.h>
#include <lib3ds/node.h>
#include <lib3ds/mesh.h>
#include <lib3ds/matrix.h>
#include <lib3ds/material.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Url.h>
#include <PLGeneral/Container/Bitset.h>
#include <PLGeneral/Log/Log.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer//Material/MaterialManager.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/3DStudioMax/MeshLoader3ds.h"


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
pl_implement_class(MeshLoader3ds)


//[-------------------------------------------------------]
//[ Custom lib3ds file callbacks                          ]
//[-------------------------------------------------------]
Lib3dsBool Lib3dsError(void *pSelf)
{
	return pSelf == nullptr;
}

long Lib3dsSeek(void *pSelf, long nOffset, Lib3dsIoSeek nOrigin)
{
	if (nOrigin == LIB3DS_SEEK_CUR)
		return !((File*)pSelf)->Seek(nOffset, File::SeekCurrent);
	else if (nOrigin == LIB3DS_SEEK_END)
		return !((File*)pSelf)->Seek(nOffset, File::SeekEnd);
	else if (nOrigin == LIB3DS_SEEK_SET)
		return !((File*)pSelf)->Seek(nOffset, File::SeekSet);
	else return -1;
}

long Lib3dsTell(void *pSelf)
{
	return ((File*)pSelf)->Tell();
}

size_t Lib3dsRead(void *pSelf, void *pBuffer, size_t nSize)
{
	return ((File*)pSelf)->Read(pBuffer, 1, nSize);
}

size_t Lib3dsWrite(void *pSelf, const void *pBuffer, size_t nSize)
{
	return ((File*)pSelf)->Write(pBuffer, 1, nSize);
}

// Internal helper function to add the mesh data to the buffers
void ProcessMesh(Lib3dsFile *pFile, Lib3dsMesh *p3dsMesh, VertexBuffer *pVertexBuffer,
				 IndexBuffer *pIndexBuffer, uint32 &nStartVertex, uint32 &nStartIndex,
				 Array<Geometry> &lstGeometries, Mesh &cMesh, Lib3dsNode *pNode)
{
	if (p3dsMesh) {
		uint32			   nVertices = p3dsMesh->points;
		uint32			   nFaces    = p3dsMesh->faces;
		uint32			   nIndices  = nFaces*3;
		const Lib3dsPoint *pPoints   = p3dsMesh->pointL;
		const Lib3dsTexel *pTexel    = p3dsMesh->texelL;
		Lib3dsVector	  *pfNormal  = new Lib3dsVector[3*nFaces];
		lib3ds_mesh_calculate_normals(p3dsMesh, pfNormal);

		// Setup transform matrix
		Matrix4x4 mTrans;
		if (pNode) {
			const Lib3dsObjectData *d = &pNode->data.object;
			Lib3dsMatrix N, M;
			lib3ds_matrix_copy(N, pNode->matrix);
			lib3ds_matrix_translate_xyz(N, -d->pivot[0], -d->pivot[1], -d->pivot[2]);
			lib3ds_matrix_copy(M, p3dsMesh->matrix);
			lib3ds_matrix_inv(M);
			lib3ds_matrix_mult(N, M);
			mTrans = &N[0][0];
		}

		// Fill buffers
		uint32 nEndVertex = nStartVertex+nVertices;
		Vector3 vV;
		// Are there any textur coordinates?
		if (pVertexBuffer->GetData(0, VertexBuffer::TexCoord)) {
			// Has this mesh texture coordinates?
			if (pTexel) {
				for (uint32 nID=nStartVertex; nID<nEndVertex; nID++) {
					// Position
					float *pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Position);
					vV.x = pPoints->pos[Vector3::X];
					vV.y = pPoints->pos[Vector3::Y];
					vV.z = pPoints->pos[Vector3::Z];
					vV = mTrans*vV;
					pfVertex[Vector3::X] = vV.x;
					pfVertex[Vector3::Y] = vV.z;
					pfVertex[Vector3::Z] = -vV.y;
					pPoints++;

					// Init normal
					pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Normal);
					pfVertex[Vector3::X] = 0.0f;
					pfVertex[Vector3::Y] = 0.0f;
					pfVertex[Vector3::Z] = 0.0f;

					// Texture coordinate
					pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::TexCoord);
					pfVertex[Vector2::X] = (*pTexel)[0];
					pfVertex[Vector2::Y] = 1.0f - (*pTexel)[1];
					pTexel++;
				}
			} else {
				for (uint32 nID=nStartVertex; nID<nEndVertex; nID++) {
					// Position
					float *pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Position);
					vV.x = pPoints->pos[Vector3::X];
					vV.y = pPoints->pos[Vector3::Y];
					vV.z = pPoints->pos[Vector3::Z];
					vV = mTrans*vV;
					pfVertex[Vector3::X] =  vV.x;
					pfVertex[Vector3::Y] =  vV.z;
					pfVertex[Vector3::Z] = -vV.y;
					pPoints++;

					// Init normal
					pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Normal);
					pfVertex[Vector3::X] = 0.0f;
					pfVertex[Vector3::Y] = 0.0f;
					pfVertex[Vector3::Z] = 0.0f;

					// Texture coordinate
					pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::TexCoord);
					pfVertex[Vector2::X] = 0.0f;
					pfVertex[Vector2::Y] = 0.0f;
				}
			}
		} else {
			for (uint32 nID=nStartVertex; nID<nEndVertex; nID++) {
				// Position
				float *pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Position);
				vV.x = pPoints->pos[Vector3::X];
				vV.y = pPoints->pos[Vector3::Y];
				vV.z = pPoints->pos[Vector3::Z];
				vV = mTrans*vV;
				pfVertex[Vector3::X] =  vV.x;
				pfVertex[Vector3::Y] =  vV.z;
				pfVertex[Vector3::Z] = -vV.y;
				pPoints++;

				// Init normal
				pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Normal);
				pfVertex[Vector3::X] = 0.0f;
				pfVertex[Vector3::Y] = 0.0f;
				pfVertex[Vector3::Z] = 0.0f;
			}
		}

		// Loop through the faces
		uint32 nIndex = nStartIndex;
		uint32 nStartIndexT = 0, nIndicesT = 0;
		Bitset cUsedFaces(nFaces, true, true);
		for (uint32 nMat=0; nMat<cMesh.GetNumOfMaterials(); nMat++) {
			for (uint32 p=0; p<nFaces; p++) {
				const Lib3dsFace &cFace = p3dsMesh->faceL[p];

				// Check material
				const Lib3dsMaterial *pMat = 0;
				if (cFace.material[0])
					pMat = lib3ds_file_material_by_name(pFile, cFace.material);
				if (pMat && pMat->user.i == (int)nMat && !cUsedFaces.IsSet(p)) {
					cUsedFaces.Set(p);

					// Loop through the face indices
					const Lib3dsVector *pfNormalT = &pfNormal[p*3];
					for (uint32 i=0; i<3; i++) {
						// Set index
						uint32 nT = cFace.points[i]+nStartVertex;

						// Set normal
						float *pfVertex = (float*)pVertexBuffer->GetData(nT, VertexBuffer::Normal);
						pfVertex[Vector3::X] +=  (*pfNormalT)[Vector3::X];
						pfVertex[Vector3::Y] +=  (*pfNormalT)[Vector3::Z];
						pfVertex[Vector3::Z] += -(*pfNormalT)[Vector3::Y];
						pfNormalT++;

						// Increase index
						pIndexBuffer->SetData(nIndex++, nT);
						nIndicesT++;
					}
				}
			}
			if (nIndicesT) {
				Geometry &cGeometry = lstGeometries.Add();
				cGeometry.SetName(p3dsMesh->name);
				cGeometry.SetFlags(0);
				cGeometry.SetActive(true);
				cGeometry.SetPrimitiveType(Primitive::TriangleList);
				cGeometry.SetMaterial(nMat);
				cGeometry.SetStartIndex(nStartIndex+nStartIndexT);
				cGeometry.SetIndexSize(nIndicesT);
			}
			nStartIndexT += nIndicesT;
			nIndicesT	  = 0;
		}

		// Add faces with no or an invalid material
		for (uint32 p=0; p<nFaces; p++) {
			const Lib3dsFace &cFace = p3dsMesh->faceL[p];
			if (!cUsedFaces.IsSet(p)) {
				// Loop through the face indices
				const Lib3dsVector *pfNormalT = &pfNormal[p*3];
				for (uint32 i=0; i<3; i++) {
					// Set index
					uint32 nT = cFace.points[i]+nStartVertex;

					// Set normal
					float *pfVertex = (float*)pVertexBuffer->GetData(nT, VertexBuffer::Normal);
					pfVertex[Vector3::X] +=  (*pfNormalT)[Vector3::X];
					pfVertex[Vector3::Y] +=  (*pfNormalT)[Vector3::Z];
					pfVertex[Vector3::Z] += -(*pfNormalT)[Vector3::Y];
					pfNormalT++;

					// Increase index
					pIndexBuffer->SetData(nIndex++, nT);
					nIndicesT++;
				}
			}
		}
		if (nIndicesT) {
			Geometry &cGeometry = lstGeometries.Add();
			cGeometry.SetName(p3dsMesh->name);
			cGeometry.SetFlags(0);
			cGeometry.SetActive(true);
			cGeometry.SetPrimitiveType(Primitive::TriangleList);
			cGeometry.SetMaterial(0);
			cGeometry.SetStartIndex(nStartIndex+nStartIndexT);
			cGeometry.SetIndexSize(nIndicesT);
		}

		// Normalize vertex normals
		for (uint32 nID=nStartVertex; nID<nEndVertex; nID++) {
			float *pfVertex = (float*)pVertexBuffer->GetData(nID, VertexBuffer::Normal);
			float  fLength  = Math::Sqrt(pfVertex[Vector3::X]*pfVertex[Vector3::X] + pfVertex[Vector3::Y]*pfVertex[Vector3::Y] + pfVertex[Vector3::Z]*pfVertex[Vector3::Z]);
			pfVertex[Vector3::X] /= fLength;
			pfVertex[Vector3::Y] /= fLength;
			pfVertex[Vector3::Z] /= fLength;
		}

		// Cleanup normals
		delete [] pfNormal;

		// Increase start variables
		nStartVertex += p3dsMesh->points;
		nStartIndex  += nIndices;
	}
}

// Internal helper function to get the total number of vertices and faces of the mesh to create
void GetInformationRec(Lib3dsFile *pFile, const Lib3dsNode *pNode, uint32 &nVertices, uint32 &nFaces,
					   bool &bTexCoords)
{
	// Go down the children
	for (const Lib3dsNode *pNodeT=pNode->childs; pNodeT!=0; pNodeT=pNodeT->next)
		GetInformationRec(pFile, pNodeT, nVertices, nFaces, bTexCoords);

	// Get information
	if (pNode->type == LIB3DS_OBJECT_NODE) {
		const Lib3dsMesh *pMesh = lib3ds_file_mesh_by_name(pFile, pNode->name);
		if (pMesh) {
			nVertices += pMesh->points;
			nFaces    += pMesh->faces;
			if (pMesh->texelL) bTexCoords = true;
		}
	}
}

void GetInformation(Lib3dsFile *pFile, uint32 &nVertices, uint32 &nFaces, bool &bTexCoords)
{
	// Get the information recursive
	nVertices = nFaces = 0;
	bTexCoords = false;
	if (pFile->nodes) {
		// 'Normal' situation
		for (const Lib3dsNode *pNode=pFile->nodes; pNode!=0; pNode=pNode->next)
			GetInformationRec(pFile, pNode, nVertices, nFaces, bTexCoords);
	} else {
		// Sometimes there are only meshes...
		const Lib3dsMesh *pMesh = pFile->meshes;
		while (pMesh) {
			nVertices += pMesh->points;
			nFaces    += pMesh->faces;
			if (pMesh->texelL) bTexCoords = true;
			pMesh = pMesh->next;
		}
	}
}

// Internal helper function for filling the vertex and index buffers
void FillBuffersRec(Lib3dsFile *pFile, Lib3dsNode *pNode, VertexBuffer *pVertexBuffer,
					IndexBuffer *pIndexBuffer, uint32 &nStartVertex, uint32 &nStartIndex,
					Array<Geometry> &lstGeometries, Mesh &cMesh)
{
	// Go down the children
	for (Lib3dsNode *pNodeT=pNode->childs; pNodeT!=0; pNodeT=pNodeT->next)
		FillBuffersRec(pFile, pNodeT, pVertexBuffer, pIndexBuffer, nStartVertex, nStartIndex, lstGeometries, cMesh);

	// Get information
	if (pNode->type == LIB3DS_OBJECT_NODE) {
		Lib3dsMesh *p3dsMesh = lib3ds_file_mesh_by_name(pFile, pNode->name);
		ProcessMesh(pFile, p3dsMesh, pVertexBuffer, pIndexBuffer, nStartVertex, nStartIndex, lstGeometries, cMesh, pNode);
	}
}

void FillBuffers(Lib3dsFile *pFile, VertexBuffer *pVertexBuffer,
				 IndexBuffer *pIndexBuffer, Array<Geometry> &lstGeometries, Mesh &cMesh)
{
	uint32 nStartVertex = 0, nStartIndex = 0;

	if (pFile->nodes) {
		// 'Normal' situation
		for (Lib3dsNode *pNode=pFile->nodes; pNode!=0; pNode=pNode->next)
			FillBuffersRec(pFile, pNode, pVertexBuffer, pIndexBuffer, nStartVertex, nStartIndex, lstGeometries, cMesh);
	} else {
		// Sometimes there are only meshes...
		Lib3dsMesh *p3dsMesh = pFile->meshes;
		while (p3dsMesh) {
			ProcessMesh(pFile, p3dsMesh, pVertexBuffer, pIndexBuffer, nStartVertex, nStartIndex, lstGeometries, cMesh, nullptr);
			p3dsMesh = p3dsMesh->next;
		}
	}
}

Lib3dsFile *lib3ds_file_load_PL(File *pPLFile)
{
	// Open the file
	Lib3dsFile *pFile = lib3ds_file_new();
	if (pFile) {
		Lib3dsIo *pIO = lib3ds_io_new(
			pPLFile,
			Lib3dsError,
			Lib3dsSeek,
			Lib3dsTell,
			Lib3dsRead,
			Lib3dsWrite
		);
		if (pIO) {
			if (lib3ds_file_read(pFile, pIO)) {
				lib3ds_io_free(pIO);
				return pFile;
			}
			lib3ds_io_free(pIO);
		}
		lib3ds_file_free(pFile);
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoader3ds::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoader3ds::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Load 3ds file
	Lib3dsFile *p3dsFile = lib3ds_file_load_PL(&cFile);
	if (!p3dsFile) {
		PL_LOG(Error, "Loading 3DS file failed: " + cFile.GetUrl().GetNativePath())

		// Error!
		return false;
	}
	lib3ds_file_eval(p3dsFile, 0);

	// Get the total number of vertices and faces
	bool bTexCoords;
	uint32 nVertices, nFaces;
	GetInformation(p3dsFile, nVertices, nFaces, bTexCoords);
	uint32 nIndices = nFaces*3;

	// Create the mesh and fill it with the read data
	MeshMorphTarget *pMorphTarget = cMesh.AddMorphTarget();
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();
	VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
	if (bTexCoords) pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
	pVertexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);

	// Allocate index
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(nVertices-1);
	pIndexBuffer->Allocate(nIndices, bStatic ? Usage::Static : Usage::Dynamic);

	// Get the directory of the filename
	String sDirectory = cFile.GetUrl().CutFilename();

	// Get the material manager
	MaterialManager &cMaterialManager = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager();

	// Go through all the materials
	Lib3dsMaterial *pMat = p3dsFile->materials;
	String sTexture;
	while (pMat) {
		// Get texture
		sTexture = Wrapper::GetStringLength(pMat->texture1_map.name) ? pMat->texture1_map.name : pMat->texture2_map.name;

		// [TODO] Cleanup
		// First check if the texture is within the meshes orginal directory
/*		sprintf(szTemp, "%s%s", szDirectory, szTexture);
		if (PL::FileSystem.IsFilenameValid(szTemp)) {
			pMaterial->Load(szTemp);
		} else {*/
			// Try to find the texture elsewhere
			// Add new material
			// [TODO]
//			Material *pMaterial = cMesh.AddMaterial(cMaterialManager.LoadResource(sTexture));

			Material *pMaterial = cMaterialManager.LoadResource(sTexture);
			cMesh.AddMaterial(pMaterial ? pMaterial : cMaterialManager.Create(sTexture));
//		}
		pMat->user.i = Lib3dsIntd(cMesh.GetNumOfMaterials()-1);

/*
		// [TEST] Set material attributes
		EffectPass *pFXPass = pFX->GetPass();
		if (!pFXPass) {
			pFX->AddTechnique();
			pFX->SelectTechnique(0);
			pFXPass = pFX->AddPass();
		}
		pFXPass->SetMaterialState(MaterialState::Ambient,  Color4::ToUInt32(pMat->ambient[R], pMat->ambient[G],
																			pMat->ambient[B], pMat->ambient[A]));
		pFXPass->SetMaterialState(MaterialState::Diffuse,  Color4::ToUInt32(pMat->diffuse[R], pMat->diffuse[G],
																			pMat->diffuse[B], pMat->diffuse[A]));
		pFXPass->SetMaterialState(MaterialState::Specular, Color4::ToUInt32(pMat->specular[R], pMat->specular[G],
																			pMat->specular[B], pMat->specular[A]));
		float fS = Math::Pow(2.0f, 10.0f*pMat->shininess);
		if (fS > 128.0f) fS=128.0f;
		pFXPass->SetMaterialState(MaterialState::Specular, Tools::FloatToUInt32(fS));
		pFXPass->GetRenderStates().Set(RenderState::Lighting, true);
//	pFXPass->SetRenderState(RenderState::CullMode, Cull::None);
		if (pMat->transparency) {
			pFX->SetBlend(true);
			pFXPass->GetRenderStates().Set(RenderState::BlendEnable, true);
			pFXPass->GetColor().SetColor(1.0f, 1.0f, 1.0f, 1.0f-pMat->transparency);
		}
*/

		// Get next material
		pMat = pMat->next;
	}

	// Add standard material if there are no materials
	if (!cMesh.GetNumOfMaterials())
		cMesh.AddMaterial(cMaterialManager.GetStandard());

	// Fill the buffers
	if (pVertexBuffer->Lock(Lock::WriteOnly)) {
		if (pIndexBuffer->Lock(Lock::WriteOnly)) {
			// Fill buffers
			FillBuffers(p3dsFile, pVertexBuffer, pIndexBuffer, *pLODLevel->GetGeometries(), cMesh);

			// Unlock the index buffer
			pIndexBuffer->Unlock();
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Cleanup
	lib3ds_file_free(p3dsFile);

	// Done
	return true;
}

bool MeshLoader3ds::Save(Mesh &cMesh, File &cFile)
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
MeshLoader3ds::MeshLoader3ds() :
	MethodLoad(this),
	MethodLoadParams(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshLoader3ds::~MeshLoader3ds()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
