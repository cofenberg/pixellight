/*********************************************************\
 *  File: AssimpMeshLoader.cpp                           *
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
#include <Assimp/aiScene.h>
#include <Assimp/assimp.hpp>
#include <Assimp/aiPostProcess.h>
#include <PLCore/Log/Log.h>
#include <PLCore/File/File.h>
#include <PLCore/File/Url.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLAssimp/IOSystem.h"
#include "PLAssimp/AssimpMeshLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
AssimpMeshLoader::AssimpMeshLoader() :
	m_pMesh(nullptr),
	m_pAssimpScene(nullptr),
	m_bHasNormals(false),
	m_bbHasTangentsAndBitangents(false),
	m_bHasTexCoords(false)
{
	for (uint32 nChannel=0; nChannel<MaxNumOfTextureCoords; nChannel++)
		m_mNumUVComponents[nChannel] = 0;
}

/**
*  @brief
*    Destructor
*/
AssimpMeshLoader::~AssimpMeshLoader()
{
}

/**
*  @brief
*    Loads the mesh
*/
bool AssimpMeshLoader::Load(Mesh &cMesh, File &cFile, bool bStatic, const String &sHint)
{
	// Reset states
	m_pMesh							= &cMesh;
	m_pAssimpScene					= nullptr;
	m_bHasNormals					= false;
	m_bbHasTangentsAndBitangents	= false;
	m_bHasTexCoords					= false;
	for (uint32 nChannel=0; nChannel<MaxNumOfTextureCoords; nChannel++)
		m_mNumUVComponents[nChannel] = 0;

	// Create an instance of the Assimp importer class
	Assimp::Importer cAssimpImporter;

	// Get the magic filename (concept based on "Assimp::MemoryIOSystem")
	const String sMagicFilename = (IOSystem::MagicDefaultFilename + String('.') + (sHint.GetLength() ? sHint : cFile.GetUrl().GetExtension()));

	// Set IO handler (the importer takes ownership of the object and will destroy it afterwards)
	cAssimpImporter.SetIOHandler(new IOSystem(cFile, sMagicFilename.GetASCII(), sMagicFilename.GetLength()));

	// Let Assimp load in the scene (scene remains in possession of the importer instance)
	m_pAssimpScene = cAssimpImporter.ReadFile(sMagicFilename.GetUTF8(), aiProcessPreset_TargetRealtime_Quality|aiProcess_TransformUVCoords);
	if (m_pAssimpScene) {
		// Get the total number of vertices and indices required for everything as one PixelLight mesh recursively
		uint32 nNumOfVertices = 0;
		uint32 nNumOfIndices  = 0;
		GetNumOfVerticesAndIndicesRec(*m_pAssimpScene->mRootNode, nNumOfVertices, nNumOfIndices);

		// Create the morph target
		MeshMorphTarget *pMorphTarget = m_pMesh->AddMorphTarget();

		// Create the LOD level
		MeshLODLevel *pLODLevel = m_pMesh->AddLODLevel();
		pLODLevel->CreateGeometries();
		pLODLevel->CreateIndexBuffer();

		// Add the materials
		AddMaterials();

		// Create the vertex buffer
		VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		if (m_bHasNormals)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal, 0, VertexBuffer::Float3);
		if (m_bbHasTangentsAndBitangents) {
			pVertexBuffer->AddVertexAttribute(VertexBuffer::Tangent,  0, VertexBuffer::Float3);
			pVertexBuffer->AddVertexAttribute(VertexBuffer::Binormal, 0, VertexBuffer::Float3);
		}
		if (m_bHasTexCoords) {
			// Loop through the supported number of texture coord sets (UV(W) channels)
			for (uint32 nChannel=0; nChannel<MaxNumOfTextureCoords; nChannel++) {
				switch (m_mNumUVComponents[nChannel]) {
					case 1:
						pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, nChannel, VertexBuffer::Float1);
						break;

					case 2:
						pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, nChannel, VertexBuffer::Float2);
						break;

					case 3:
						pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, nChannel, VertexBuffer::Float3);
						break;
				}
			}
		}
		if (pVertexBuffer->Allocate(nNumOfVertices, bStatic ? Usage::Static : Usage::Dynamic)) {
			// Allocate index
			IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
			pIndexBuffer->SetElementTypeByMaximumIndex(nNumOfVertices - 1);
			if (pIndexBuffer->Allocate(nNumOfIndices, bStatic ? Usage::Static : Usage::Dynamic)) {
				// Lock the vertex buffer
				if (pVertexBuffer->Lock(Lock::WriteOnly)) {
					// Lock the index buffer
					if (pIndexBuffer->Lock(Lock::WriteOnly)) {
						// Fills the mesh data recursively
						nNumOfVertices = 0;
						nNumOfIndices  = 0;
						FillMeshRec(*m_pAssimpScene->mRootNode, *pVertexBuffer, *pIndexBuffer, *pLODLevel->GetGeometries(), aiMatrix4x4(), nNumOfVertices, nNumOfIndices);

						// Unlock the index buffer
						pIndexBuffer->Unlock();
					}

					// Unlock the vertex buffer
					pVertexBuffer->Unlock();
				}

				// Done
				return true;
			} else {
				// Error!
				PL_LOG(Error, '\"' + cFile.GetUrl().GetUrl() + "\": Failed to allocate the index buffer")
			}
		} else {
			// Error!
			PL_LOG(Error, '\"' + cFile.GetUrl().GetUrl() + "\": Failed to allocate the vertex buffer")
		}

		// Error!
		return false;
	} else {
		// Write an error message into the log
		PL_LOG(Error, cAssimpImporter.GetErrorString())

		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds the materials
*/
void AssimpMeshLoader::AddMaterials()
{
	// Get the PixelLight material manager
	MaterialManager &cMaterialManager = m_pMesh->GetRenderer()->GetRendererContext().GetMaterialManager();

	// Loop through all Assimp materials
	for (unsigned int nAssimpMaterial=0; nAssimpMaterial<m_pAssimpScene->mNumMaterials; nAssimpMaterial++) {
		// Get the Assimp material
		const aiMaterial &cAssimpMaterial = *m_pAssimpScene->mMaterials[nAssimpMaterial];

		// AI_MATKEY_NAME - Get Assimp material name
		aiString sAssimpMaterialName;
		cAssimpMaterial.Get(AI_MATKEY_NAME, sAssimpMaterialName);

		// Construct an unique material name to avoid material conflicts
		const String sMaterialNameOriginal = m_pMesh->GetName() + '_' + String::FromUTF8(sAssimpMaterialName.data, -1, sAssimpMaterialName.length);
		String sMaterialName = sMaterialNameOriginal;
		uint32 nIndex = 0;
		while (cMaterialManager.GetByName(sMaterialName)) {
			sMaterialName = sMaterialNameOriginal + '_' + nIndex;
			nIndex++;
		}

		// Add the PixelLight material
		Material *pMaterial = cMaterialManager.Create(sMaterialName);
		m_pMesh->AddMaterial(pMaterial);

		// Fill the material
		if (pMaterial) {
			// Get the parameter manager of the material
			ParameterManager &cParameterManager = pMaterial->GetParameterManager();

			{ // AI_MATKEY_TWOSIDED - default: 0
				int nTwoSided = 0;
				aiGetMaterialInteger(&cAssimpMaterial, AI_MATKEY_TWOSIDED, &nTwoSided);
				if (nTwoSided)
					cParameterManager.SetParameter1i("TwoSided", 1);
			}

			// AI_MATKEY_SHADING_MODEL - not supported
			// AI_MATKEY_ENABLE_WIREFRAME - not supported
			// AI_MATKEY_BLEND_FUNC - not supported

			{ // AI_MATKEY_OPACITY - default: 1.0
				float fOpacity = 1.0f;
				aiGetMaterialFloat(&cAssimpMaterial, AI_MATKEY_OPACITY, &fOpacity);
				if (fOpacity < 1.0f)
					cParameterManager.SetParameter1f("Opacity", fOpacity);
			}

			{ // AI_MATKEY_BUMPSCALING - default: 1.0
				float fBumpScaling = 1.0f;
				aiGetMaterialFloat(&cAssimpMaterial, AI_MATKEY_BUMPSCALING, &fBumpScaling);
				if (fBumpScaling != 1.0f)
					cParameterManager.SetParameter1f("NormalMapBumpiness", fBumpScaling);
			}

			{ // AI_MATKEY_SHININESS - default: 45.0
				float fShininess = 45.0f;
				aiGetMaterialFloat(&cAssimpMaterial, AI_MATKEY_SHININESS, &fShininess);
				if (fShininess != 45.0f)
					cParameterManager.SetParameter1f("SpecularExponent", fShininess);
			}

			// AI_MATKEY_REFLECTIVITY - not supported
			// AI_MATKEY_SHININESS_STRENGTH - not supported
			// AI_MATKEY_REFRACTI - not supported

			{ // AI_MATKEY_COLOR_DIFFUSE - default: 1.0 1.0 1.0
				aiColor3D cColor(1.0f, 1.0f, 1.0f);
				if (cAssimpMaterial.Get(AI_MATKEY_COLOR_DIFFUSE, cColor) == AI_SUCCESS)
					cParameterManager.SetParameter3f("DiffuseColor", cColor.r, cColor.g, cColor.b);
			}

			// AI_MATKEY_COLOR_AMBIENT - not supported

			{ // AI_MATKEY_COLOR_SPECULAR - default: 1.0 1.0 1.0
				aiColor3D cColor(1.0f, 1.0f, 1.0f);
				if (cAssimpMaterial.Get(AI_MATKEY_COLOR_SPECULAR, cColor) == AI_SUCCESS)
					cParameterManager.SetParameter3f("SpecularColor", cColor.r, cColor.g, cColor.b);
			}

			{ // AI_MATKEY_COLOR_EMISSIVE - default: 1.0 1.0 1.0
				aiColor3D cColor(1.0f, 1.0f, 1.0f);
				if (cAssimpMaterial.Get(AI_MATKEY_COLOR_EMISSIVE, cColor) == AI_SUCCESS)
					cParameterManager.SetParameter3f("EmissiveMapColor", cColor.r, cColor.g, cColor.b);
			}

			// AI_MATKEY_COLOR_TRANSPARENT - not supported
			// AI_MATKEY_COLOR_REFLECTIVE - not supported
			// AI_MATKEY_GLOBAL_BACKGROUND_IMAGE - not supported

			{ // aiTextureType_DIFFUSE
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_DIFFUSE, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("DiffuseMap", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}

			{ // aiTextureType_SPECULAR
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_SPECULAR, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("SpecularMap", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}

			{ // aiTextureType_SPECULAR
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_SPECULAR, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("SpecularMap", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}

			// aiTextureType_AMBIENT - not supported

			{ // aiTextureType_EMISSIVE
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_EMISSIVE, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("EmissiveMap", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}

			{ // aiTextureType_HEIGHT
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_HEIGHT, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("HeightMap", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}

			{ // aiTextureType_NORMALS
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_NORMALS, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("NormalMap", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}

			//  aiTextureType_SHININESS - not supported
			//  aiTextureType_OPACITY - not supported
			//  aiTextureType_DISPLACEMENT - not supported

			{ // aiTextureType_LIGHTMAP
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_LIGHTMAP, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("LightMap", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}

			{ // aiTextureType_REFLECTION
				aiString sAssimpFilename;
				if (cAssimpMaterial.GetTexture(aiTextureType_REFLECTION, 0, &sAssimpFilename) == AI_SUCCESS)
					cParameterManager.SetParameterTexture("ReflectionColor", String::FromUTF8(sAssimpFilename.data, -1, sAssimpFilename.length));
			}
		}
	}
}

/**
*  @brief
*    Gets the total number of vertices and indices required for everything as one PixelLight mesh recursively
*/
void AssimpMeshLoader::GetNumOfVerticesAndIndicesRec(const aiNode &cAssimpNode, uint32 &nNumOfVertices, uint32 &nNumOfIndices)
{
	// Loop through all meshes this node is using
	for (unsigned int nAssimpMesh=0; nAssimpMesh<cAssimpNode.mNumMeshes; nAssimpMesh++) {
		// Get the used mesh
		const aiMesh &cAssimpMesh = *m_pAssimpScene->mMeshes[cAssimpNode.mMeshes[nAssimpMesh]];

		// Update the number of vertices
		nNumOfVertices += cAssimpMesh.mNumVertices;

		// Loop through all mesh faces and update the number of indices
		for (unsigned int nAssimpFace=0; nAssimpFace<cAssimpMesh.mNumFaces; nAssimpFace++)
			nNumOfIndices += cAssimpMesh.mFaces[nAssimpFace].mNumIndices;

		// Are there normals?
		if (cAssimpMesh.HasNormals())
			m_bHasNormals = true;

		// Are there tangents and bitangents?
		if (cAssimpMesh.HasTangentsAndBitangents())
			m_bbHasTangentsAndBitangents = true;

		// Are there texture coordinates?
		if (cAssimpMesh.GetNumUVChannels()) {
			m_bHasTexCoords = true;

			// Loop through the supported number of texture coord sets (UV(W) channels)
			for (uint32 nChannel=0; nChannel<MaxNumOfTextureCoords; nChannel++) {
				if (m_mNumUVComponents[nChannel] < cAssimpMesh.mNumUVComponents[nChannel])
					m_mNumUVComponents[nChannel] = cAssimpMesh.mNumUVComponents[nChannel];
			}
		}
	}

	// Loop through all child nodes recursively
	for (unsigned int nAssimpChild=0; nAssimpChild<cAssimpNode.mNumChildren; nAssimpChild++)
		GetNumOfVerticesAndIndicesRec(*cAssimpNode.mChildren[nAssimpChild], nNumOfVertices, nNumOfIndices);
}

/**
*  @brief
*    Fills the mesh data recursively
*/
void AssimpMeshLoader::FillMeshRec(const aiNode &cAssimpNode, VertexBuffer &cVertexBuffer, IndexBuffer &cIndexBuffer, Array<Geometry> &lstGeometries, const aiMatrix4x4 &mAssimpTransformation, uint32 &nNumOfVertices, uint32 &nNumOfIndices)
{
	// We're using aiProcessPreset_TargetRealtime_Quality which also sets the flag aiProcess_SortByPType
	// resulting in 'clean' meshes which consist of a single type of primitives. So, one Assimp mesh will
	// result within one PixelLight mesh geometry.

	// Get the absolute transformation matrix of this Assimp node
	const aiMatrix4x4 mCurrentAssimpTransformation = mAssimpTransformation*cAssimpNode.mTransformation;

	// Loop through all meshes this node is using
	for (unsigned int nAssimpMesh=0; nAssimpMesh<cAssimpNode.mNumMeshes; nAssimpMesh++) {
		// Get the used mesh
		const aiMesh &cAssimpMesh = *m_pAssimpScene->mMeshes[cAssimpNode.mMeshes[nAssimpMesh]];

		// Get the start vertex inside the PixelLight mesh vertex buffer
		const uint32 nStarVertex = nNumOfVertices;

		// Loop through the Assimp mesh vertices
		for (unsigned int nAssimpVertex=0; nAssimpVertex<cAssimpMesh.mNumVertices; nAssimpVertex++) {
			// Get the Assimp mesh vertex position
			aiVector3D cAssimpVertex = cAssimpMesh.mVertices[nAssimpVertex];

			// Transform the Assimp mesh vertex position into global space
			cAssimpVertex *= mCurrentAssimpTransformation;

			// Set vertex buffer position
			float *pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::Position));
			pfVertex[0] = cAssimpVertex.x;
			pfVertex[1] = cAssimpVertex.y;
			pfVertex[2] = cAssimpVertex.z;

			// Are there any normals at all?
			if (m_bHasNormals) {
				pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::Normal));

				// Are there normals within the current mesh?
				if (cAssimpMesh.HasNormals()) {
					const aiVector3D &cAssimpVertexNormal = cAssimpMesh.mNormals[nAssimpVertex];
					pfVertex[0] = cAssimpVertexNormal.x;
					pfVertex[1] = cAssimpVertexNormal.y;
					pfVertex[2] = cAssimpVertexNormal.z;
				} else {
					// Fallback
					pfVertex[0] = 1.0f;
					pfVertex[1] = 0.0f;
					pfVertex[2] = 0.0f;
				}
			}

			// Are there any tangents and bitangents at all?
			if (m_bbHasTangentsAndBitangents) {
				// Are there tangents and bitangents within the current mesh?
				if (cAssimpMesh.HasTangentsAndBitangents()) {
					{ // Tangent
						const aiVector3D &cAssimpVertexTangent = cAssimpMesh.mTangents[nAssimpVertex];
						pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::Tangent));
						pfVertex[0] = cAssimpVertexTangent.x;
						pfVertex[1] = cAssimpVertexTangent.y;
						pfVertex[2] = cAssimpVertexTangent.z;
					}
					{ // Binormal
						const aiVector3D &cAssimpVertexBinormal = cAssimpMesh.mBitangents[nAssimpVertex];
						pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::Binormal));
						pfVertex[0] = cAssimpVertexBinormal.x;
						pfVertex[1] = cAssimpVertexBinormal.y;
						pfVertex[2] = cAssimpVertexBinormal.z;
					}
				} else {
					// Fallback
					pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::Tangent));
					pfVertex[0] = 0.0f;
					pfVertex[1] = 1.0f;
					pfVertex[2] = 0.0f;
					pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::Binormal));
					pfVertex[0] = 0.0f;
					pfVertex[1] = 0.0f;
					pfVertex[2] = 1.0f;
				}
			}

			// Are there any texture coordinates at all?
			if (m_bHasTexCoords) {
				// Loop through the supported number of texture coord sets (UV(W) channels)
				for (uint32 nChannel=0; nChannel<MaxNumOfTextureCoords; nChannel++) {
					// Are there any texture coordinates within the current channel at all?
					if (m_mNumUVComponents[nChannel]) {
						// Are there texture coordinates within the current mesh?
						if (cAssimpMesh.HasTextureCoords(nChannel)) {
							const aiVector3D &cAssimpVertexTexCoord = cAssimpMesh.mTextureCoords[nChannel][nAssimpVertex];
							pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::TexCoord, nChannel));
							pfVertex[0] = cAssimpVertexTexCoord.x;
							if (m_mNumUVComponents[nChannel] > 1) {
								if (cAssimpMesh.mNumUVComponents[nChannel] > 1) {
									// [TODO] When do I need to flip and when not? ("Koerper.mesh.xml" no flip, "duck.dae" flip... ?!)
									pfVertex[1] = cAssimpVertexTexCoord.y;
//									pfVertex[1] = 1.0f - cAssimpVertexTexCoord.y;
									if (m_mNumUVComponents[nChannel] > 2) {
										if (cAssimpMesh.mNumUVComponents[nChannel] > 2)
											pfVertex[2] = cAssimpVertexTexCoord.z;
										else
											pfVertex[2] = 0.0f; // Fallback
									}
								} else {
									// Fallback
									pfVertex[1] = 0.0f;
									if (m_mNumUVComponents[nChannel] > 2)
										pfVertex[2] = 0.0f;
								}
							}
						} else {
							// Fallback
							pfVertex = static_cast<float*>(cVertexBuffer.GetData(nNumOfVertices, VertexBuffer::TexCoord, nChannel));
							pfVertex[0] = 0.0f;
							if (m_mNumUVComponents[nChannel] > 1) {
								pfVertex[1] = 0.0f;
								if (m_mNumUVComponents[nChannel] > 2)
									pfVertex[2] = 0.0f;
							}
						}
					}
				}
			}

			// Update the number of processed vertices
			nNumOfVertices++;
		}

		// Get the start index of this geometry
		const uint32 nGeometryStartIndex = nNumOfIndices;

		// Check the index buffer element type
		switch (cIndexBuffer.GetElementType()) {
			case IndexBuffer::UInt:
			{
				// Loop through all Assimp mesh faces
				uint32 *pnIndex = static_cast<uint32*>(cIndexBuffer.GetData()) + nNumOfIndices;
				for (unsigned int nAssimpFace=0; nAssimpFace<cAssimpMesh.mNumFaces; nAssimpFace++) {
					// Get the Assimp face
					const aiFace &cAssimpFace = cAssimpMesh.mFaces[nAssimpFace];

					// Loop through all indices of the Assimp face and set the PixelLight mesh vertex indices
					for (unsigned int nAssimpIndex=0; nAssimpIndex<cAssimpFace.mNumIndices; nAssimpIndex++, pnIndex++) {
						//			   Assimp mesh vertex index         Where the Assimp mesh starts within the PixelLight mesh vertex buffer
						*pnIndex = cAssimpFace.mIndices[nAssimpIndex] + nStarVertex;
					}

					// Update the number if processed indices
					nNumOfIndices += cAssimpFace.mNumIndices;
				}
				break;
			}

			case IndexBuffer::UShort:
			{
				// Loop through all Assimp mesh faces
				uint16 *pnIndex = static_cast<uint16*>(cIndexBuffer.GetData()) + nNumOfIndices;
				for (unsigned int nAssimpFace=0; nAssimpFace<cAssimpMesh.mNumFaces; nAssimpFace++) {
					// Get the Assimp face
					const aiFace &cAssimpFace = cAssimpMesh.mFaces[nAssimpFace];

					// Loop through all indices of the Assimp face and set the PixelLight mesh vertex indices
					for (unsigned int nAssimpIndex=0; nAssimpIndex<cAssimpFace.mNumIndices; nAssimpIndex++, pnIndex++) {
						//			   Assimp mesh vertex index         Where the Assimp mesh starts within the PixelLight mesh vertex buffer
						*pnIndex = static_cast<uint16>(cAssimpFace.mIndices[nAssimpIndex] + nStarVertex);
					}

					// Update the number if processed indices
					nNumOfIndices += cAssimpFace.mNumIndices;
				}
				break;
			}

			case IndexBuffer::UByte:
			{
				// Loop through all Assimp mesh faces
				uint8 *pnIndex = static_cast<uint8*>(cIndexBuffer.GetData()) + nNumOfIndices;
				for (unsigned int nAssimpFace=0; nAssimpFace<cAssimpMesh.mNumFaces; nAssimpFace++) {
					// Get the Assimp face
					const aiFace &cAssimpFace = cAssimpMesh.mFaces[nAssimpFace];

					// Loop through all indices of the Assimp face and set the PixelLight mesh vertex indices
					for (unsigned int nAssimpIndex=0; nAssimpIndex<cAssimpFace.mNumIndices; nAssimpIndex++, pnIndex++) {
						//			   Assimp mesh vertex index         Where the Assimp mesh starts within the PixelLight mesh vertex buffer
						*pnIndex = static_cast<uint8>(cAssimpFace.mIndices[nAssimpIndex] + nStarVertex);
					}

					// Update the number if processed indices
					nNumOfIndices += cAssimpFace.mNumIndices;
				}
				break;
			}
		}

		// Get the primitive type (see also comment at the beginning of this method)
		Primitive::Enum nPrimitiveType = Primitive::Unknown;
		if (cAssimpMesh.mPrimitiveTypes & aiPrimitiveType_TRIANGLE)
			nPrimitiveType = Primitive::TriangleList;
		else if (cAssimpMesh.mPrimitiveTypes & aiPrimitiveType_LINE)
			nPrimitiveType = Primitive::LineList;
		else if (cAssimpMesh.mPrimitiveTypes & aiPrimitiveType_POINT)
			nPrimitiveType = Primitive::PointList;
		if (nPrimitiveType != Primitive::Unknown) {
			// Add the geometry
			Geometry &cGeometry = lstGeometries.Add();
			cGeometry.SetName(String::FromUTF8(cAssimpMesh.mName.data, -1, cAssimpMesh.mName.length));
			cGeometry.SetFlags(0);
			cGeometry.SetActive(true);
			cGeometry.SetPrimitiveType(nPrimitiveType);
			cGeometry.SetMaterial(cAssimpMesh.mMaterialIndex);
			cGeometry.SetStartIndex(nGeometryStartIndex);
			cGeometry.SetIndexSize(nNumOfIndices - nGeometryStartIndex);
		}
	}

	// Loop through all child nodes recursively
	for (unsigned int nAssimpChild=0; nAssimpChild<cAssimpNode.mNumChildren; nAssimpChild++)
		FillMeshRec(*cAssimpNode.mChildren[nAssimpChild], cVertexBuffer, cIndexBuffer, lstGeometries, mCurrentAssimpTransformation, nNumOfVertices, nNumOfIndices);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp
