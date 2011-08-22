/*********************************************************\
 *  File: PLScenePLMesh.cpp                              *
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
#include <morpher/wm3.h>
#include <PLCore/File/File.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMaterial.h"
#include "PL3dsMaxSceneExport/PLScenePLMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMesh;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLScenePLMesh::PLScenePLMesh(PLScene &cScene, IGameNode &cIGameNode, const std::string &sName) : PLSceneMesh(cScene, cIGameNode, sName)
{
}

/**
*  @brief
*    Destructor
*/
PLScenePLMesh::~PLScenePLMesh()
{
	for (uint32 i=0; i<m_lstPointCacheAnimations.GetNumOfElements(); i++)
		delete m_lstPointCacheAnimations[i];
}

/**
*  @brief
*    Saves the mesh
*/
bool PLScenePLMesh::Save(const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	// Open file
	std::string sFilename;
	if (g_SEOptions.bPLDirectories) {
		if (g_SEOptions.bSubDirectories)
			sFilename = sApplicationDrive + sApplicationDir + "Data\\Meshes\\" + g_SEOptions.sFilenameOnly + "\\" + m_sName + ".mesh";
		else
			sFilename = sApplicationDrive + sApplicationDir + "Data\\Meshes\\" + m_sName + ".mesh";
	} else {
		sFilename = sApplicationDrive + sApplicationDir + m_sName + ".mesh";
	}
	FILE *pFile = fopen(sFilename.c_str(), "wb");
	if (pFile) { // If all went fine...
		// Save
		ChunkStack cChunkStack;
		bool bResult = WriteMeshFile(*pFile, cChunkStack);

		// Close file
		fclose(pFile);

		// Done
		return bResult;
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteMeshFile(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MESHFILE)) {
		// Write mesh file header
		MeshFile::MeshFileHeader cMeshFileHeader;
		cMeshFileHeader.nMagic   = MeshFile::MAGIC;
		cMeshFileHeader.nVersion = MeshFile::VERSION;
		if (!Write(cFile, &cMeshFileHeader, sizeof(cMeshFileHeader)))
			return false; // Error!

		// Write mesh data
		if (g_SEOptions.bExportMaterials && !WriteMaterials(cFile, cChunkStack))
			return false; // Error!

		if (!WriteMesh(cFile, cChunkStack))
			return false; // Error!

		// Write skeleton + skeleton animation
		if (m_lstBones.GetNumOfElements()) {
			if (!WriteSkeleton(cFile, cChunkStack))
				return false; // Error!
		}

		// Write morph target animation
		if (m_lstMorphChannels.GetNumOfElements()) {
			if (!WriteMorphTargetAnimation(cFile, cChunkStack))
				return false; // Error!
		}

		// Write point cache animation
		if (m_lstPointCacheAnimations.GetNumOfElements()) {
			// Loop through all point cache animations
			Iterator<Animation*> cIterator = m_lstPointCacheAnimations.GetIterator();
			while (cIterator.HasNext()) {
				if (!WritePointCacheAnimation(cFile, cChunkStack, *cIterator.Next()))
					return false; // Error!
			}

			// [TODO]
			m_lstPointCacheAnimations.Clear();

		}

		// Write animations
		if (m_lstAnimations.GetNumOfElements()) {
			if (!WriteAnimations(cFile, cChunkStack))
				return false; // Error!
		}

		// Write mesh bounding box
		if (!WriteMeshBoundingBox(cFile, cChunkStack))
			return false; // Error!

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteMaterials(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MATERIALS)) {
		// Write materials header
		MeshFile::Materials cMaterials;
		cMaterials.nMaterials = m_lstMaterials.GetNumOfElements();
		if (!Write(cFile, &cMaterials, sizeof(cMaterials)))
			return false; // Error!

		// Write materials
		for (uint32 i=0; i<cMaterials.nMaterials; i++) {
			PLSceneMaterial *pMaterial = m_lstMaterials[i];
			if (pMaterial) {
				std::string sMaterialFilaneme = pMaterial->GetName();
				if (sMaterialFilaneme.find(".mat") != std::string::npos)
					sMaterialFilaneme = "Data\\Materials\\" + sMaterialFilaneme;
				uint32 nLength = (uint32)sMaterialFilaneme.length();
				if (nLength > 255)
					nLength = 255;
				char szMatName[256];
				strncpy(szMatName, sMaterialFilaneme.c_str(), nLength);
				szMatName[nLength] = '\0';
				if (!Write(cFile, szMatName, 256))
					return false; // Error!
			}
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteMesh(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MESH)) {
		// Are there any 'PointCaches' for this mesh? (we need to now the number of frames within the point caches)
		int nNumOfPointCacheFrames = 0;
		if (m_lstPointCaches.GetNumOfElements()) {
			// Loop through all point caches
			Iterator<String> cIterator = m_lstPointCaches.GetIterator();
			while (cIterator.HasNext()) {
				String sPointCache = cIterator.Next();

				// Open the 'PointCache'-file
				File cPointCacheFile(sPointCache);
				if (cPointCacheFile.Open(File::FileRead)) {
					// Read the header
					// Signature
					char szSignature[12] = "";
					cPointCacheFile.Read(szSignature, sizeof(szSignature), 1);
					if (!strcmp(szSignature, "POINTCACHE2")) {
						// File version
						int nFileVersion = 0;
						cPointCacheFile.Read(&nFileVersion, sizeof(int), 1);
						if (nFileVersion == 1) {
							// Get the total number of points
							int nNumOfPoints = 0;
							cPointCacheFile.Read(&nNumOfPoints, sizeof(int), 1);

							// Get the start frame
							int nStartFrame = 0;
							cPointCacheFile.Read(&nStartFrame, sizeof(int), 1);

							// Get the sample rate
							int nSampleRate = 0;
							cPointCacheFile.Read(&nSampleRate, sizeof(int), 1);

							// Get the total number of samples (number of frames)
							int nNumOfFrames = 0;
							cPointCacheFile.Read(&nNumOfFrames, sizeof(int), 1);
							nNumOfPointCacheFrames += nNumOfFrames;

							{ // Add point cache animation
								// Get animation
								Animation *pAnimation = new Animation;
								MeshFile::Animation &sAnimation = pAnimation->sAnimation;

								// Animation name = point cache filename without path and extension
								Url cUrl(sPointCache);
								strcpy(sAnimation.szName, cUrl.GetCompleteTitle());

								sAnimation.nType   = 0; // Vertex animation
								sAnimation.nStart  = 0; // Inclusive
								sAnimation.nEnd    = nNumOfFrames-1; // Inclusive
								sAnimation.fSpeed  = 24.0f;
								sAnimation.nFlags  = 1; // Loop
								sAnimation.nEvents = 0;
								// [TEST]
								pAnimation->nStartTime	   = 0;
								pAnimation->nEndTime	   = nNumOfFrames;
//								Interval cInterval	= m_pScene->GetMaxInterface().GetAnimRange();
//								pAnimation->nStartTime	   = cInterval.Start();
//								pAnimation->nEndTime	   = cInterval.End();
								pAnimation->nTicksPerFrame = GetTicksPerFrame();
								m_lstPointCacheAnimations.Add(pAnimation);
							}
						}
					}
				}
			}
		}

		// Write mesh header
		MeshFile::Mesh cMesh;
		cMesh.nLODLevels	 = 1;
		// 'base frame' + 'number of morph channels' + 'point cache frames'
		cMesh.nMorphTargets  = 1 + m_lstMorphChannels.GetNumOfElements() + nNumOfPointCacheFrames;
		cMesh.nWeights		 = m_nTotalNumOfVertexWeights;
		cMesh.nVertexWeights = m_nTotalNumOfVertexWeights ? m_nNumOfVertices : 0;
		if (!Write(cFile, &cMesh, sizeof(cMesh)))
			return false; // Error!

		// Write LOD levels
		for (unsigned int i=0; i<cMesh.nLODLevels; i++) {
			if (!WriteLODLevel(cFile, cChunkStack, i))
				return false; // Error!
		}

		// Write base frame
		if (!WriteMorphTarget(cFile, cChunkStack))
			return false; // Error!

		// Write morph targets from the morph channels
		for (uint32 nChannel=0; nChannel<m_lstMorphChannels.GetNumOfElements(); nChannel++) {
			if (!WriteMorphTarget(cFile, cChunkStack, *m_lstMorphChannels[nChannel]))
				return false; // Error!
		}

		// Are there any 'PointCaches' for this mesh? If so, write morph targets from the point cache.
		if (m_lstPointCaches.GetNumOfElements()) {
			// Loop through all point caches
			Iterator<String> cIterator = m_lstPointCaches.GetIterator();
			while (cIterator.HasNext()) {
				String sPointCache = cIterator.Next();

				// Open the 'PointCache'-file
				File cPointCacheFile(sPointCache);
				if (cPointCacheFile.Open(File::FileRead)) {
					// Write point cache morph targets
					if (!WritePointCacheMorphTargets(cFile, cChunkStack, cPointCacheFile))
						return false; // Error!
				}
			}
		}

		// Write weights
		if (cMesh.nWeights) {
			// Loop through all vertices
			for (int i=0; i<m_nNumOfVertices; i++) {
				// Get the vertex
				const Vertex &cVertex = m_pScene->m_pMeshVertices[i];

				// Has this vertex any weights?
				if (cVertex.nNumOfWeights) {
					// First, ensure that the total weight of all weights is 1
					// [TODO] Do we need this?
/*					float fWeight = 0.0f;
					for (int j=0; j<vertices[i]->num_weights; j++)
						fWeight += vertices[i]->weights[j].weight;
					if (fWeight != 1.0f && fWeight != 0.0f) {
						fWeight = 1/fWeight;
						for (int j=0; j<vertices[i]->num_weights; j++)
							vertices[i]->weights[j].weight *= fWeight;
					}*/

					// Write weights
					for (int nWeight=0; nWeight<cVertex.nNumOfWeights; nWeight++)
						WriteWeight(cFile, cChunkStack, cVertex.cWeights[nWeight]);
				} else {
					// Ok, this vertex is not skinned... 'normally' this should NEVER happen...
				}
			}
		}

		// Write vertex weights
		uint32 nNumOfWeights = 0;
		// Loop through all vertices
		for (uint32 i=0; i<cMesh.nVertexWeights; i++) {
			// Get the vertex
			const Vertex &cVertex = m_pScene->m_pMeshVertices[i];

			// Write
			WriteVertexWeights(cFile, cChunkStack, cVertex, nNumOfWeights);
			nNumOfWeights += cVertex.nNumOfWeights;
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteLODLevel(FILE &cFile, ChunkStack &cChunkStack, int nLODLevel)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_LODLEVEL)) {
		// Write LOD level header
		MeshFile::LODLevel cLODLevel;
		cLODLevel.fDistance			   = 0.0f;
		cLODLevel.nGeometries		   = static_cast<uint32>(m_nNumOfGeometries);
		cLODLevel.nOctreeSubdivide	   = 0;
		cLODLevel.nOctreeMinGeometries = 0;
		if (!Write(cFile, &cLODLevel, sizeof(cLODLevel)))
			return false; // Error!

		// Write index buffer
		if (!WriteIndexBuffer(cFile, cChunkStack))
			return false; // Error!

		// Write geometries
		for (unsigned int i=0; i<cLODLevel.nGeometries; i++) {
			if (!WriteGeometry(cFile, cChunkStack, i))
				return false; // Error!
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteIndexBuffer(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_INDEXBUFFER)) {
		// Get number of indices
		unsigned int nNumOfIndices = 0;
		for (int i=0; i<m_nNumOfGeometries; i++)
			nNumOfIndices += m_pScene->m_pMeshGeometries[i].nIndexSize;

		// Write index buffer header
		MeshFile::IndexBuffer cIndexBuffer;
		if (m_nNumOfVertices < 256) { // IndexBuffer::UByte
			cIndexBuffer.nElementType = 2;
			cIndexBuffer.nElements	  = nNumOfIndices;
			cIndexBuffer.nSize		  = sizeof(uint8)*cIndexBuffer.nElements;
		} else if (m_nNumOfVertices < 65536) { // IndexBuffer::UShort
			cIndexBuffer.nElementType = 1;
			cIndexBuffer.nElements	  = nNumOfIndices;
			cIndexBuffer.nSize		  = sizeof(uint16)*cIndexBuffer.nElements;
		} else { // IndexBuffer::UInt
			cIndexBuffer.nElementType = 0;
			cIndexBuffer.nElements	  = nNumOfIndices;
			cIndexBuffer.nSize		  = sizeof(uint32)*cIndexBuffer.nElements;
		}
		if (!Write(cFile, &cIndexBuffer, sizeof(cIndexBuffer)))
			return false; // Error!

		// Write index buffer
		if (cIndexBuffer.nElementType == 0) { // IndexBuffer::UInt
			for (uint32 nMat=0; nMat<m_lstMaterials.GetNumOfElements(); nMat++) {
				for (int i=0; i<m_nNumOfTriangles; i++) {
					const Triangle &cTriangle = m_pScene->m_pMeshTriangles[i];
					if (cTriangle.nMatID == nMat) {
						for (int j=0; j<3; j++) {
							uint32 nIndex = static_cast<uint32>(cTriangle.v[j]);
							if (!Write(cFile, &nIndex, sizeof(uint32)))
								return false; // Error!
						}
					}
				}
			}
		} else if (cIndexBuffer.nElementType == 1) { // IndexBuffer::UInt
			for (uint32 nMat=0; nMat<m_lstMaterials.GetNumOfElements(); nMat++) {
				for (int i=0; i<m_nNumOfTriangles; i++) {
					const Triangle &cTriangle = m_pScene->m_pMeshTriangles[i];
					if (cTriangle.nMatID == nMat) {
						for (int j=0; j<3; j++) {
							uint16 nIndex = static_cast<uint16>(cTriangle.v[j]);
							if (!Write(cFile, &nIndex, sizeof(uint16)))
								return false; // Error!
						}
					}
				}
			}
		} else { // IndexBuffer::UByte
			for (uint32 nMat=0; nMat<m_lstMaterials.GetNumOfElements(); nMat++) {
				for (int i=0; i<m_nNumOfTriangles; i++) {
					const Triangle &cTriangle = m_pScene->m_pMeshTriangles[i];
					if (cTriangle.nMatID == nMat) {
						for (int j=0; j<3; j++) {
							uint8 nIndex = static_cast<uint8>(cTriangle.v[j]);
							if (!Write(cFile, &nIndex, sizeof(uint8)))
								return false; // Error!
						}
					}
				}
			}
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteGeometry(FILE &cFile, ChunkStack &cChunkStack, int nGeometry)
{
	// Start chunk
	const Geometry &cGeometry = m_pScene->m_pMeshGeometries[nGeometry];
	if (cGeometry.nIndexSize) {
		if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_GEOMETRY)) {
			// Write geometry
			MeshFile::Geometry sGeometry;
			strcpy(sGeometry.szName, "");
			sGeometry.nFlags		 = 0;
			sGeometry.bActive		 = true;
			sGeometry.nPrimitiveType = 3; // PLRenderer::Primitive::TriangleList
			sGeometry.nMaterial		 = cGeometry.nMaterial;
			sGeometry.nStartIndex	 = cGeometry.nStartIndex;
			sGeometry.nIndexSize	 = cGeometry.nIndexSize;
			if (!Write(cFile, &sGeometry, sizeof(sGeometry)))
				return false; // Error!

			// End chunk
			return EndChunk(cFile, cChunkStack);
		} else {
			// Error!
			return false;
		}
	} else {
		// Done
		return true;
	}
}

bool PLScenePLMesh::WriteMorphTarget(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MORPHTARGET)) {
		// Write morph target header
		MeshFile::MorphTarget cMorphTarget;
		strcpy(cMorphTarget.szName, "Base");
		cMorphTarget.bRelative      = false;
		cMorphTarget.nVertexIDs     = 0;
		cMorphTarget.nVertexBuffers = 1;
		if (!Write(cFile, &cMorphTarget, sizeof(cMorphTarget)))
			return false; // Error!

		// Write vertex buffers
		for (unsigned int i=0; i<cMorphTarget.nVertexBuffers; i++) {
			if (!WriteVertexBuffer(cFile, cChunkStack, i))
				return false; // Error!
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteMorphTarget(FILE &cFile, ChunkStack &cChunkStack, morphChannel &cMorphChannel)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MORPHTARGET)) {
		// Get number of vertices ID's
		std::vector<Point3*> lstPointsMorph;
		std::vector<int> lstPointsMorphID;

		// Check whether the number of original vertices matches the number of deltas - if this is not
		// the case write a warning into the log because this may indicate an situation causing
		// errors!
		int nNumOfDeltas = static_cast<int>(cMorphChannel.mDeltas.size());
		if (m_nOriginalNumOfVertices != nNumOfDeltas) {
			g_pLog->LogFLine(PLLog::Warning, "Node: '%s' -> Morph target: '%s' -> Mesh has '%d' vertices, but there are '%d' deltas -> both numbers should be equal",
				m_pIGameNode->GetName(), cMorphChannel.mName, m_nOriginalNumOfVertices, cMorphChannel.mDeltas.size());
		}

		// Loop through all vertices
		for (int i=0; i<m_nNumOfVertices; i++) {
			// Get the vertex
			const Vertex &cVertex = m_pScene->m_pMeshVertices[i];

			// Check vertex ID
			if (cVertex.nOrginal3dsMaxID >= 0 && cVertex.nOrginal3dsMaxID < nNumOfDeltas) {
				// Get and check delta
				const Point3 &vDelta = cMorphChannel.mDeltas[cVertex.nOrginal3dsMaxID];
				if (vDelta.x != 0.0f || vDelta.y != 0.0f || vDelta.z != 0.0f) {
					// We really need to flip the coordinates to OpenGL style and scale it by the factor 100
					Point3 *pvDelta = new Point3(vDelta[0]*100.0f, vDelta[2]*100.0f, -vDelta[1]*100.0f);

					// Store the delta
					lstPointsMorph.push_back(pvDelta);
					lstPointsMorphID.push_back(i);
				}
			}
		}

		// Write morph target header
		MeshFile::MorphTarget cMorphTarget;
		strcpy(cMorphTarget.szName, cMorphChannel.mName);
		cMorphTarget.bRelative      = true;
		cMorphTarget.nVertexIDs     = static_cast<int>(lstPointsMorph.size());
		cMorphTarget.nVertexBuffers = 1;
		if (!Write(cFile, &cMorphTarget, sizeof(cMorphTarget)))
			return false; // Error!

		// Write vertex ID's
		for (int i=0; i<static_cast<int>(lstPointsMorph.size()); i++) {
			int nID = lstPointsMorphID[i];
			if (!Write(cFile, &nID, sizeof(uint32)))
				return false; // Error!
		}

		// Write vertex buffers
		if (!WriteVertexBufferMorph(cFile, cChunkStack, lstPointsMorph))
			return false; // Error!

		// Cleanup
		for (unsigned int i=0; i<lstPointsMorph.size(); i++)
			delete lstPointsMorph[i];
		lstPointsMorph.clear();

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WritePointCacheMorphTargets(FILE &cFile, ChunkStack &cChunkStack, File &cPointCacheFile)
{
	// Read the header
	// Signature
	char szSignature[12] = "";
	cPointCacheFile.Read(szSignature, sizeof(szSignature), 1);
	if (!strcmp(szSignature, "POINTCACHE2")) {
		// File version
		int nFileVersion = 0;
		cPointCacheFile.Read(&nFileVersion, sizeof(int), 1);
		if (nFileVersion == 1) {
			// Get the total number of points
			int nNumOfPoints = 0;
			cPointCacheFile.Read(&nNumOfPoints, sizeof(int), 1);

			// Get the start frame
			int nStartFrame = 0;
			cPointCacheFile.Read(&nStartFrame, sizeof(int), 1);

			// Get the sample rate
			int nSampleRate = 0;
			cPointCacheFile.Read(&nSampleRate, sizeof(int), 1);

			// Get the total number of samples (number of frames)
			int nNumOfSamples = 0;
			cPointCacheFile.Read(&nNumOfSamples, sizeof(int), 1);
			if (nNumOfSamples) {
				// Check whether or not the number of point cache vertices matches the number of original mesh vertices
				if (nNumOfPoints == m_nOriginalNumOfVertices) {
					// Allocate frame points buffer (streaming... we only hold 'one' frame at the same time within the memory)
					Point3 *pPointCachePoints = new Point3[nNumOfPoints];

					// Allocate frame points
					std::vector<Point3*> lstPointsMorph;
					for (int i=0; i<m_nNumOfVertices; i++) 
						lstPointsMorph.push_back(new Point3(0.0f, 0.0f, 0.0f));

					// Morph target name = point cache filename without path and extension
					char szPointCacheTitle[64];
					Url cUrl(cPointCacheFile.GetUrl().GetFilename());
					strcpy(szPointCacheTitle, cUrl.GetCompleteTitle());

					// Write the morph targets
					for (int nSample=0; nSample<nNumOfSamples; nSample++) {
						// Read frame points
						cPointCacheFile.Read(pPointCachePoints, sizeof(Point3), nNumOfPoints);

						// Start chunk
						if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MORPHTARGET)) {
							// Write morph target header with an build in name
							MeshFile::MorphTarget cMorphTarget;
							sprintf(cMorphTarget.szName, "%s_%d", szPointCacheTitle, nSample);
							cMorphTarget.bRelative      = true;
							cMorphTarget.nVertexIDs     = 0;
							cMorphTarget.nVertexBuffers = 1;
							Write(cFile, &cMorphTarget, sizeof(cMorphTarget));

							// Write vertex ID's -> Currently ALL vertices are influenced so we don't need vertex ID's

							// Loop through all vertices and fill 'lstPointsMorph'
							for (int i=0; i<m_nNumOfVertices; i++) {
								// Get the vertex
								const Vertex &cVertex = m_pScene->m_pMeshVertices[i];
								Point3 *pPointMorph = lstPointsMorph[i];

								// Get the point cache point
								const int nOrginal3dsMaxID = cVertex.nOrginal3dsMaxID;
								if (nOrginal3dsMaxID >= 0 && nOrginal3dsMaxID < m_nOriginalNumOfVertices) {
									const Point3 &cPointCachePoint = pPointCachePoints[cVertex.nOrginal3dsMaxID];

									// Set delta (we really need to flip the coordinates to OpenGL style)
									*pPointMorph = PLTools::Convert3dsMaxVectorToOpenGLVector(cPointCachePoint)-cVertex.xyz;
								} else {
									// Error!
									pPointMorph->Set(0.0f, 0.0f, 0.0f);
								}
							}

							// Write vertex buffers
							if (!WriteVertexBufferMorph(cFile, cChunkStack, lstPointsMorph))
								return false; // Error!

							// End chunk
							EndChunk(cFile, cChunkStack);
						}
					}

					// Cleanup the allocated memory
					for (unsigned int i=0; i<lstPointsMorph.size(); i++)
						delete lstPointsMorph[i];
					lstPointsMorph.clear();
					delete [] pPointCachePoints;

					// Done
					return true;
				} else {
					// Error!
					g_pLog->LogFLine(PLLog::Error, "Node: '%s' -> Point cache: Mesh has '%d' vertices, but there are '%d' point cache vertices per frame -> both numbers should be equal",
						m_pIGameNode->GetName(), m_nOriginalNumOfVertices, nNumOfPoints);
				}
			}
		}
	}

	// Error!
	return false;
}

bool PLScenePLMesh::WriteWeight(FILE &cFile, ChunkStack &cChunkStack, const Weight &cWeight)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_WEIGHT)) {
		// Write weight
		MeshFile::Weight cMeshWeight;
		cMeshWeight.nJoint = cWeight.nBone;
		cMeshWeight.fBias  = cWeight.fWeight;
		if (!Write(cFile, &cMeshWeight, sizeof(cMeshWeight)))
			return false; // Error!

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteVertexWeights(FILE &cFile, ChunkStack &cChunkStack, const Vertex &cVertex, int nWeights)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_VERTEXWEIGHTS)) {
		// Write vertex weights
		MeshFile::VertexWeights cVertexWeights;
		cVertexWeights.nWeights = cVertex.nNumOfWeights;
		if (!Write(cFile, &cVertexWeights, sizeof(cVertexWeights)))
			return false; // Error!

		// Write vertex weights
		for (uint32 i=0; i<cVertexWeights.nWeights; i++) {
			uint32 nWeight = nWeights+i;
			if (!Write(cFile, &nWeight, sizeof(uint32)))
				return false; // Error!
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteVertexBuffer(FILE &cFile, ChunkStack &cChunkStack, int nVertexBuffer)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_VERTEXBUFFER)) {
		// Write vertex buffer header
		MeshFile::VertexBuffer cVertexBuffer;
		// Position
		int nVertexSize = sizeof(float)*3;
		int nAttributes = 1;
		// Normals
		if (g_SEOptions.bNormals) {
			nVertexSize += sizeof(float)*3;
			nAttributes++;
		}
		// Tangents
		if (g_SEOptions.bTangents) {
			nVertexSize += sizeof(float)*3;
			nAttributes++;
		}
		// Binormals
		if (g_SEOptions.bBinormals) {
			nVertexSize += sizeof(float)*3;
			nAttributes++;
		}
		// Texture coordinates
		for (int i=0; i<PLSceneExportOptions::MaxTexCoords; i++) {
			// Are there any texture coordinates?
			if (m_bTexCoord[i]) {
				// Within the options the user can define how many components are exported
				nVertexSize += sizeof(float)*g_SEOptions.nTexCoordComponents[i];
				nAttributes++;
			}
		}
		cVertexBuffer.nVertexAttributes = nAttributes;
		cVertexBuffer.nVertices			= m_nNumOfVertices;
		cVertexBuffer.nSize				= cVertexBuffer.nVertices*nVertexSize;
		if (!Write(cFile, &cVertexBuffer, sizeof(cVertexBuffer)))
			return false; // Error!

		// Write vertex attributes
		// Position
		if (!WriteVertexAttribute(cFile, cChunkStack, 0))
			return false; // Error!
		// Normals
		if (g_SEOptions.bNormals && !WriteVertexAttribute(cFile, cChunkStack, 1))
			return false; // Error!
		// Tangents
		if (g_SEOptions.bTangents && !WriteVertexAttribute(cFile, cChunkStack, 2))
			return false; // Error!
		// Binormals
		if (g_SEOptions.bBinormals && !WriteVertexAttribute(cFile, cChunkStack, 3))
			return false; // Error!
		// Texture coordinates
		for (int i=0; i<PLSceneExportOptions::MaxTexCoords; i++) {
			if (!WriteVertexAttribute(cFile, cChunkStack, 4+i))
				return false; // Error!
		}

		// Write vertex buffer
		for (int i=0; i<m_nNumOfVertices; i++) {
			const Vertex &cVertex = m_pScene->m_pMeshVertices[i];

			// Position
			float fT = cVertex.xyz.x;
			if (!Write(cFile, &fT, sizeof(float)))
				return false; // Error!
			fT = cVertex.xyz.y;
			if (!Write(cFile, &fT, sizeof(float)))
				return false; // Error!
			fT = cVertex.xyz.z;
			if (!Write(cFile, &fT, sizeof(float)))
				return false; // Error!

			// Normal
			if (g_SEOptions.bNormals) {
				fT = cVertex.vNormal.x;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
				fT = cVertex.vNormal.y;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
				fT = cVertex.vNormal.z;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
			}

			// Tangent
			if (g_SEOptions.bTangents) {
				fT = cVertex.vTangent.x;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
				fT = cVertex.vTangent.y;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
				fT = cVertex.vTangent.z;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
			}

			// Binormal
			if (g_SEOptions.bBinormals) {
				fT = cVertex.vBinormal.x;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
				fT = cVertex.vBinormal.y;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
				fT = cVertex.vBinormal.z;
				if (!Write(cFile, &fT, sizeof(float)))
					return false; // Error!
			}

			// Texture coordinates
			for (int j=0; j<PLSceneExportOptions::MaxTexCoords; j++) {
				// Are there any texture coordinates?
				if (m_bTexCoord[j]) {
					// Within the options the user can define how many components are exported
					if (g_SEOptions.nTexCoordComponents[j] >= 1) {
						fT = cVertex.vTexCoord[j].x;
						if (!Write(cFile, &fT, sizeof(float)))
							return false; // Error!
					}
					if (g_SEOptions.nTexCoordComponents[j] >= 2) {
						fT = cVertex.vTexCoord[j].y;
						if (!Write(cFile, &fT, sizeof(float)))
							return false; // Error!
					}
					if (g_SEOptions.nTexCoordComponents[j] >= 3) {
						fT = cVertex.vTexCoord[j].z;
						if (!Write(cFile, &fT, sizeof(float)))
							return false; // Error!
					}
				}
			}
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteVertexBufferMorph(FILE &cFile, ChunkStack &cChunkStack, std::vector<Point3*> &lstPoints)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_VERTEXBUFFER)) {
		// Write vertex buffer header
		MeshFile::VertexBuffer cVertexBuffer;
		// Position
		int nVertexSize = sizeof(float)*3;
		int nAttributes = 1;
		cVertexBuffer.nVertexAttributes = nAttributes;
		cVertexBuffer.nVertices		    = static_cast<int>(lstPoints.size());
		cVertexBuffer.nSize			    = cVertexBuffer.nVertices*nVertexSize;
		if (!Write(cFile, &cVertexBuffer, sizeof(cVertexBuffer)))
			return false; // Error!

		// Write vertex attributes
		// Position
		WriteVertexAttribute(cFile, cChunkStack, 0);

		// Write vertex buffer
		for (int i=0; i<static_cast<int>(lstPoints.size()); i++) {
			const Point3 *pPoint = lstPoints[i];

			// Position (delta)
			float fT = pPoint->x;
			Write(cFile, &fT, sizeof(float));
			fT = pPoint->y;
			Write(cFile, &fT, sizeof(float));
			fT = pPoint->z;
			Write(cFile, &fT, sizeof(float));
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteVertexAttribute(FILE &cFile, ChunkStack &cChunkStack, int nVertexAttribute)
{
	// Check if there are texture coordinate components
	if (nVertexAttribute >= 4 && !m_bTexCoord[nVertexAttribute-4])
		return true; // Done, skip because there are no texture coordinates to export

	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_VERTEXATTRIBUTE)) {
		// Write vertex attribute
		MeshFile::VertexAttribute cVertexAttribute;
		switch (nVertexAttribute) {
			case 0:	// Positions
				cVertexAttribute.nSemantic = 0;	// PLRenderer::VertexBuffer::Position
				cVertexAttribute.nChannel  = 0;
				cVertexAttribute.nType	   = 3;	// PLRenderer::VertexBuffer::Float3
				break;

			case 1:	// Normals
				cVertexAttribute.nSemantic = 2;	// PLRenderer::VertexBuffer::Normal
				cVertexAttribute.nChannel  = 0;
				cVertexAttribute.nType	   = 3;	// PLRenderer::VertexBuffer::Float3
				break;

			case 2:	// Tangents
				cVertexAttribute.nSemantic = 8;	// PLRenderer::VertexBuffer::Tangent
				cVertexAttribute.nChannel  = 0;
				cVertexAttribute.nType	   = 3;	// PLRenderer::VertexBuffer::Float3
				break;

			case 3:	// Binormal
				cVertexAttribute.nSemantic = 9;	// PLRenderer::VertexBuffer::Binormal
				cVertexAttribute.nChannel  = 0;
				cVertexAttribute.nType	   = 3;	// PLRenderer::VertexBuffer::Float3
				break;

			default: // Texture coordinates
				cVertexAttribute.nSemantic = 7;	// PLRenderer::VertexBuffer::TexCoord
				cVertexAttribute.nChannel  = nVertexAttribute-4;
				cVertexAttribute.nType	   = g_SEOptions.nTexCoordComponents[nVertexAttribute-4];
				break;
		}
		if (!Write(cFile, &cVertexAttribute, sizeof(cVertexAttribute)))
			return false; // Error!

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteSkeleton(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_SKELETON)) {
		// Get all animation information
		Interval cInterval	= m_pScene->GetMaxInterface().GetAnimRange();
		int nStartTime		= cInterval.Start();
		int nEndTime		= cInterval.End();
		int nTicksPerFrame	= GetTicksPerFrame();
		int nNumOfFrames	= (nEndTime-nStartTime)/nTicksPerFrame;

		// Make a animation containing ALL frames
		Animation *pAnimation = new Animation;
		MeshFile::Animation &sAnimation = pAnimation->sAnimation;
		strcpy(sAnimation.szName, SkeletonAnimation);
		sAnimation.nType   = 1; // Skeleton animation
		sAnimation.nStart  = 0; // Inclusive
		sAnimation.nEnd    = nNumOfFrames-1; // Inclusive
		sAnimation.fSpeed  = 24.0f;
		sAnimation.nFlags  = 1; // Loop
		sAnimation.nEvents = 0;
		pAnimation->nStartTime	   = nStartTime;
		pAnimation->nEndTime	   = nEndTime;
		pAnimation->nTicksPerFrame = nTicksPerFrame;
		m_lstAnimations.Add(pAnimation);

		// [TODO] Precalculate this!
		// Get parent joint IDs
		Array<int> lstJointParents;
		lstJointParents.Resize(m_lstBones.GetNumOfElements());
		for (uint32 nJoint=0; nJoint<m_lstBones.GetNumOfElements(); nJoint++) {
			// Get the IGameNode of this bone
			IGameNode *pIGameNode = m_lstBones[nJoint];

			// Find parent joint ID
			int nParent = -1;
			IGameNode *pIGameNodeParent = pIGameNode->GetNodeParent();
			if (pIGameNodeParent) {
				// Loop through ALL bones
				for (uint32 nParentJointID=0; nParentJointID<m_lstBones.GetNumOfElements(); nParentJointID++) {
					// Is this the parent node?
					if (m_lstBones[nParentJointID] == pIGameNodeParent) {
						// Jap, get it's index inside our bone list and get out of here!
						nParent = nParentJointID;
						break;
					}
				}
			}
			lstJointParents[nJoint] = nParent;
		}

		// Get the number of frames
//		const int nNumOfFrames = pAnimation ? abs(pAnimation->sAnimation.nEnd-pAnimation->sAnimation.nStart)+1 : 0;

		// Tell which attribute the track modify
		enum EAttribute {
			eAX		= 1<<0,
			eAY		= 1<<1,
			eAZ		= 1<<2,
			eAYaw	= 1<<3,
			eAPitch	= 1<<4,
			eARoll	= 1<<5,
			eAW		= 1<<6
		};

		// Get animated bone components
		Array<uint32> lstAnimatedComponentsAll;
		if (pAnimation) {
			// Initialize animated components
			lstAnimatedComponentsAll.Resize(m_lstBones.GetNumOfElements(), true, true);

			// Loop through all frames to get the animated components of each bone
			for (int nTime=pAnimation->nStartTime; nTime<=pAnimation->nEndTime; nTime+=pAnimation->nTicksPerFrame) {
				// Loop through all bones
				for (uint32 nJoint=0; nJoint<m_lstBones.GetNumOfElements(); nJoint++) {
					// Get bone frame data
					IGameNode *pIGameNodeBone = m_lstBones[nJoint];

					// Get relative base transform
					GMatrix cBaseGMatrix = m_lstBonesInitPose[nJoint];
					if (lstJointParents[nJoint] >= 0)
						cBaseGMatrix *= m_lstBonesInitPose[lstJointParents[nJoint]].Inverse();

					// Get relative current transform
					GMatrix cGMatrix = pIGameNodeBone->GetWorldTM(nTime);
					if (lstJointParents[nJoint] >= 0) {
						IGameNode *pIGameNodeParentBone = m_lstBones[lstJointParents[nJoint]];
						if (pIGameNodeParentBone)
							cGMatrix *= pIGameNodeParentBone->GetWorldTM(nTime).Inverse();
					}

					// Please note, the following solution is NOT working correctly although it 'looks within the code correctly'
					// cGMatrix *= cBaseGMatrix.Inverse(); // Get relative transform between current and base transform
					// ... if we get the position & rotation from the animation frame AND the base frame and
					// subtracting them, the result is quite fine (maybe a precision problem?)

					// Get the position, rotation and scale
					Point3 vPos, vScale;
					Quat qRot;
					PLTools::GetPosRotScale(cGMatrix, vPos, qRot, vScale);

					// Get the position, rotation and scale of the base frame
					Point3 vPosBase, vScaleBase;
					Quat qRotBase;
					PLTools::GetPosRotScale(cBaseGMatrix, vPosBase, qRotBase, vScaleBase);

					// Get relative transform between current and base transform
					vPos -= vPosBase;
					qRot *= qRotBase.Inverse();

					// Check which components have been changed and add it
					uint32 nAnimatedComponents = lstAnimatedComponentsAll[nJoint];
					if (vPos.x)
						nAnimatedComponents |= eAX;
					if (vPos.y)
						nAnimatedComponents |= eAY;
					if (vPos.z)
						nAnimatedComponents |= eAZ;
					if (qRot.x)
						nAnimatedComponents |= eAYaw;
					if (qRot.y)
						nAnimatedComponents |= eAPitch;
					if (qRot.z)
						nAnimatedComponents |= eARoll;
					if (qRot.w)
						nAnimatedComponents |= eAW;
					lstAnimatedComponentsAll[nJoint] = nAnimatedComponents;
				}
			}
		} else { // Base frame of no animation optimization
			lstAnimatedComponentsAll.Resize(m_lstBones.GetNumOfElements());

			// Initialize animated components
			const uint32 nAllComponents = eAX | eAY | eAZ | eAYaw | eAPitch | eARoll | eAW;
			for (uint32 nBone=0; nBone<m_lstBones.GetNumOfElements(); nBone++)
				lstAnimatedComponentsAll[nBone] = nAllComponents;
		}

		// Get animated bones
		Array<uint32> lstAnimatedComponents;
		Array<IGameNode*> lstAnimatedBones;
		for (uint32 i=0; i<lstAnimatedComponentsAll.GetNumOfElements(); i++) {
			if (lstAnimatedComponentsAll[i]) {
				lstAnimatedComponents.Add(lstAnimatedComponentsAll[i]);
				lstAnimatedBones.Add(m_lstBones[i]);
			}
		}

		// Write skeleton
		MeshFile::Skeleton cSkeleton;
		// Animation
		if (pAnimation) {
			strcpy(cSkeleton.szName, pAnimation->sAnimation.szName);
			cSkeleton.nFrames = nNumOfFrames;
		} else {
			strcpy(cSkeleton.szName, "BaseFrame");
			cSkeleton.nFrames = 0;
		}
		cSkeleton.nJoints = lstAnimatedBones.GetNumOfElements();
		if (!Write(cFile, &cSkeleton, sizeof(cSkeleton)))
			return false; // Error!

		// Write joints
		for (uint32 nJoint=0; nJoint<cSkeleton.nJoints; nJoint++) {
			MeshFile::Joint cJoint;

			// Get the IGameNode of this bone
			IGameNode *pIGameNode = lstAnimatedBones[nJoint];

			// Set joint name
			const TCHAR *pszName = pIGameNode->GetName();
			if (pszName)
				strcpy(cJoint.szName, pIGameNode->GetName());
			else
				strcpy(cJoint.szName, "");

			// Find parent joint ID
			cJoint.nParent = -1; // By default this joint has no parent
			IGameNode *pIGameNodeParent = pIGameNode->GetNodeParent();
			if (pIGameNodeParent) {
				// Loop through ALL bones
				for (uint32 nParentJointID=0; nParentJointID<m_lstBones.GetNumOfElements(); nParentJointID++) {
					// Is this the parent node?
					if (m_lstBones[nParentJointID] == pIGameNodeParent) {
						// Jap, get it's index inside our bone list and get out of here!
						// [TODO] Invalid bone index if not all bones are animated... !?!
						cJoint.nParent = nParentJointID;
						break;
					}
				}
			}

			// Set the number of animated components
			cJoint.nAnimatedComponents = lstAnimatedComponents[nJoint];

			// Write the joint
			if (!Write(cFile, &cJoint, sizeof(cJoint)))
				return false; // Error!
		}

		// Write base frame
		for (uint32 nJoint=0; nJoint<m_lstBones.GetNumOfElements(); nJoint++) {
			MeshFile::JointState cJointState;


			// Bone
			// Get the relative translation and rotation of the initial bone transform
			GMatrix cGMatrix = m_lstBonesInitPose[nJoint];
			if (lstJointParents[nJoint] >= 0)
				cGMatrix *= m_lstBonesInitPose[lstJointParents[nJoint]].Inverse();

			// Get the position, rotation and scale
			Point3 vPos, vScale;
			Quat qRot;
			PLTools::GetPosRotScale(cGMatrix, vPos, qRot, vScale);

			// Set translation
			cJointState.fTranslation[0] = vPos.x;
			cJointState.fTranslation[1] = vPos.y;
			cJointState.fTranslation[2] = vPos.z;

			// Set rotation
			cJointState.fRotation[0] = qRot.w;
			cJointState.fRotation[1] = qRot.x;
			cJointState.fRotation[2] = qRot.y;
			cJointState.fRotation[3] = qRot.z;


			// Joint space using the the initial bone transform
			cGMatrix = m_lstBonesInitPose[nJoint];
			cGMatrix = cGMatrix.Inverse();

			// Get the position, rotation and scale
			PLTools::GetPosRotScale(cGMatrix, vPos, qRot, vScale);

			// Get joint space translation
			cJointState.fTranslationJointSpace[0] = vPos.x;
			cJointState.fTranslationJointSpace[1] = vPos.y;
			cJointState.fTranslationJointSpace[2] = vPos.z;

			// Get joint space rotation
			cJointState.fRotationJointSpace[0] = qRot.w;
			cJointState.fRotationJointSpace[1] = qRot.x;
			cJointState.fRotationJointSpace[2] = qRot.y;
			cJointState.fRotationJointSpace[3] = qRot.z;


			// Write the base frame of this joint
			if (!Write(cFile, &cJointState, sizeof(cJointState)))
				return false; // Error!
		}

		// Write frame keys
		if (pAnimation) {
			// Loop through all frames
			for (int nTime=pAnimation->nStartTime; nTime<=pAnimation->nEndTime; nTime+=pAnimation->nTicksPerFrame) {
				// Loop through all bones
				for (uint32 nJoint=0; nJoint<lstAnimatedBones.GetNumOfElements(); nJoint++) {
					// Get the IGameNode of this bone
					IGameNode *pIGameNodeBone = m_lstBones[nJoint];

					// Get the animated components
					const uint32 nAnimatedComponents = lstAnimatedComponents[nJoint];

					// Get relative base transform
					GMatrix cBaseGMatrix = m_lstBonesInitPose[nJoint];
					if (lstJointParents[nJoint] >= 0)
						cBaseGMatrix *= m_lstBonesInitPose[lstJointParents[nJoint]].Inverse();

					// Get relative current transform
					GMatrix cGMatrix = pIGameNodeBone->GetWorldTM(nTime);
					if (lstJointParents[nJoint] >= 0) {
						IGameNode *pIGameNodeParentBone = m_lstBones[lstJointParents[nJoint]];
						if (pIGameNodeParentBone)
							cGMatrix *= pIGameNodeParentBone->GetWorldTM(nTime).Inverse();
					}

					// Please note, the following solution is NOT working correctly although it 'looks within the code correctly'
					// cGMatrix *= cBaseGMatrix.Inverse(); // Get relative transform between current and base transform
					// ... if we get the position & rotation from the animation frame AND the base frame and
					// subtracting them, the result is quite fine (maybe a precision problem?)

					// Get the position, rotation and scale
					Point3 vPos, vScale;
					Quat qRot;
					PLTools::GetPosRotScale(cGMatrix, vPos, qRot, vScale);

					// Get the position, rotation and scale of the base frame
					Point3 vPosBase, vScaleBase;
					Quat qRotBase;
					PLTools::GetPosRotScale(cBaseGMatrix, vPosBase, qRotBase, vScaleBase);

					// Get relative transform between current and base transform
					vPos -= vPosBase;
					qRot *= qRotBase.Inverse();

					// Write down
					if (nAnimatedComponents & eAX) {
						if (!Write(cFile, &vPos.x, sizeof(float)))
							return false; // Error!
					}
					if (nAnimatedComponents & eAY) {
						if (!Write(cFile, &vPos.y, sizeof(float)))
							return false; // Error!
					}
					if (nAnimatedComponents & eAZ) {
						if (!Write(cFile, &vPos.z, sizeof(float)))
							return false; // Error!
					}
					if (nAnimatedComponents & eAYaw) {
						if (!Write(cFile, &qRot.x, sizeof(float)))
							return false; // Error!
					}
					if (nAnimatedComponents & eAPitch) {
						if (!Write(cFile, &qRot.y, sizeof(float)))
							return false; // Error!
					}
					if (nAnimatedComponents & eARoll) {
						if (!Write(cFile, &qRot.z, sizeof(float)))
							return false; // Error!
					}
					if (nAnimatedComponents & eAW) {
						if (!Write(cFile, &qRot.w, sizeof(float)))
							return false; // Error!
					}
				}
			}
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteMeshBoundingBox(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MESHBOUNDINGBOX)) {
		// Write mesh bounding box
		MeshFile::BoundingBox cBoundingBox;
		if (PLTools::IsEmpty(m_cLocalBox)) {
			cBoundingBox.fMin[0] = 0.0f;
			cBoundingBox.fMin[1] = 0.0f;
			cBoundingBox.fMin[2] = 0.0f;
			cBoundingBox.fMax[0] = 0.0f;
			cBoundingBox.fMax[1] = 0.0f;
			cBoundingBox.fMax[2] = 0.0f;
		} else {
			cBoundingBox.fMin[0] = m_cLocalBox.pmin.x;
			cBoundingBox.fMin[1] = m_cLocalBox.pmin.y;
			cBoundingBox.fMin[2] = m_cLocalBox.pmin.z;
			cBoundingBox.fMax[0] = m_cLocalBox.pmax.x;
			cBoundingBox.fMax[1] = m_cLocalBox.pmax.y;
			cBoundingBox.fMax[2] = m_cLocalBox.pmax.z;
		}
		if (!Write(cFile, &cBoundingBox, sizeof(cBoundingBox)))
			return false; // Error!

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteMorphTargetAnimation(FILE &cFile, ChunkStack &cChunkStack)
{
	// Get all animation information
	Interval cInterval	= m_pScene->GetMaxInterface().GetAnimRange();
	int nStartTime		= cInterval.Start();
	int nEndTime		= cInterval.End();
	int nTicksPerFrame	= GetTicksPerFrame();
	int nNumOfFrames	= (nEndTime-nStartTime)/nTicksPerFrame;

	// Get morph targets influenced by the animation
	Array<morphChannel*> lstMorphChannels;
	for (uint32 nChannel=0; nChannel<m_lstMorphChannels.GetNumOfElements(); nChannel++) {
		morphChannel *lChannel = m_lstMorphChannels[nChannel];
		Control *pControl = lChannel->cblock->GetController(0);

		// Check if this morph target is influenced by the animation...
		// First get the initial value at the start time...
		float fInitialValue = 0.0f;
		pControl->GetValue(nStartTime, &fInitialValue, cInterval, CTRL_ABSOLUTE);

		// ... and now look whether at some time within the animation this morph target is manipulated
		for (int nTime=nStartTime+nTicksPerFrame; nTime<=nEndTime; nTime+=nTicksPerFrame) {
			float fValue;
			pControl->GetValue(nTime, &fValue, cInterval, CTRL_ABSOLUTE);
			if (fValue != fInitialValue) {
				// Ok, this morph target is influenced by the animation, that's all we currently want to now
				lstMorphChannels.Add(lChannel);
				break;
			}
		}
	}

	// Is any morph target influenced by the animation?
	if (lstMorphChannels.GetNumOfElements()) {
		// Make a animation containing ALL frames
		Animation *pAnimation = new Animation;
		MeshFile::Animation &sAnimation = pAnimation->sAnimation;
		strcpy(sAnimation.szName, MorphTargetAnimation);
		sAnimation.nType   = 0; // Vertex animation
		sAnimation.nStart  = 0; // Inclusive
		sAnimation.nEnd    = nNumOfFrames-1; // Inclusive
		sAnimation.fSpeed  = 24.0f;
		sAnimation.nFlags  = 1; // Loop
		sAnimation.nEvents = 0;
		pAnimation->nStartTime	   = nStartTime;
		pAnimation->nEndTime	   = nEndTime;
		pAnimation->nTicksPerFrame = nTicksPerFrame;
		m_lstAnimations.Add(pAnimation);

		// Start chunk
		if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MORPHTARGETANIMATION)) {
			// Write morph target animation header
			MeshFile::MorphTargetAnimation sMorphTargetAnimation;
			strcpy(sMorphTargetAnimation.szName, pAnimation->sAnimation.szName);
			sMorphTargetAnimation.nMorphTargets = lstMorphChannels.GetNumOfElements();
			sMorphTargetAnimation.nFrames		= nNumOfFrames;
			if (!Write(cFile, &sMorphTargetAnimation, sizeof(sMorphTargetAnimation)))
				return false; // Error!

			// Write morph targets
			for (uint32 i=0; i<sMorphTargetAnimation.nMorphTargets; i++) {
				char szName[64];
				strcpy(szName, lstMorphChannels[i]->mName);
				if (!Write(cFile, szName, sizeof(char)*64))
					return false; // Error!
			}

			// Write frame keys
			Interval vValid(pAnimation->nStartTime, pAnimation->nEndTime);
			int nFrame = 0;
			for (int nTime=pAnimation->nStartTime; nTime<=pAnimation->nEndTime; nTime+=pAnimation->nTicksPerFrame) {
				for (uint32 i=0; i<sMorphTargetAnimation.nMorphTargets; i++) {
					float fValue;
					lstMorphChannels[i]->cblock->GetController(0)->GetValue(nTime, &fValue, vValid, CTRL_ABSOLUTE);
					fValue /= 100.0f;
					if (!Write(cFile, &fValue, sizeof(float)))
						return false; // Error!
				}
				nFrame++;
			}

			// End chunk
			return EndChunk(cFile, cChunkStack);
		} else {
			// Error!
			return false;
		}
	} else {
		// Done, there's no morph target animation
		return true;
	}
}

bool PLScenePLMesh::WritePointCacheAnimation(FILE &cFile, ChunkStack &cChunkStack, Animation &cAnimation)
{
	// Start chunk
	if (BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_MORPHTARGETANIMATION)) {
		int nNumOfFrames = cAnimation.sAnimation.nEnd-cAnimation.sAnimation.nStart;

		// Write morph target animation header
		MeshFile::MorphTargetAnimation sMorphTargetAnimation;
		strcpy(sMorphTargetAnimation.szName, cAnimation.sAnimation.szName);
		sMorphTargetAnimation.nMorphTargets = nNumOfFrames; // One morph target for each frame
		sMorphTargetAnimation.nFrames		= nNumOfFrames;
		if (!Write(cFile, &sMorphTargetAnimation, sizeof(sMorphTargetAnimation)))
			return false; // Error!

		// Write morph targets
		for (uint32 i=0; i<sMorphTargetAnimation.nMorphTargets; i++) {
			char szName[64];
			sprintf(szName, "%s_%d", sMorphTargetAnimation.szName, i); // Build in name
			if (!Write(cFile, szName, sizeof(char)*64))
				return false; // Error!
		}

		// Write frame keys
		for (int nFrame=0; nFrame<static_cast<int>(sMorphTargetAnimation.nFrames); nFrame++) {
			for (uint32 nMorphTarget=0; nMorphTarget<sMorphTargetAnimation.nMorphTargets; nMorphTarget++) {
				float fValue = (nFrame == nMorphTarget) ? 1.0f : 0.0f;
				if (!Write(cFile, &fValue, sizeof(float)))
					return false; // Error!
			}
		}

		// Put the point cache animation into the animation list
		m_lstAnimations.Add(&cAnimation);

		// [TODO]
//		m_pPointCacheAnimation = nullptr;

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::WriteAnimations(FILE &cFile, ChunkStack &cChunkStack)
{
	// Start chunk
	if (m_lstAnimations.GetNumOfElements() && BeginChunk(cFile, cChunkStack, MeshFile::CHUNK_ANIMATIONS)) {
		// Write animations header
		MeshFile::Animations sAnimations;
		sAnimations.nAnimations = m_lstAnimations.GetNumOfElements();
		if (!Write(cFile, &sAnimations, sizeof(sAnimations)))
			return false; // Error!

		// Write down all animations
		for (uint32 nAnimation=0; nAnimation<m_lstAnimations.GetNumOfElements(); nAnimation++) {
			// Get the animation
			Animation *pAnimation = m_lstAnimations[nAnimation];

			// [TODO] Currently not supported
			pAnimation->sAnimation.nEvents = 0;

			// Write animation header
			if (!Write(cFile, &pAnimation->sAnimation, sizeof(pAnimation->sAnimation)))
				return false; // Error!

			// Write frames
			uint32 nNumOfFrames = pAnimation->sAnimation.nEnd-pAnimation->sAnimation.nStart+1;
			for (uint32 nFrame=0; nFrame<nNumOfFrames; nFrame++) {
				float fSpeed = 1.0f;
				if (!Write(cFile, &fSpeed, sizeof(fSpeed)))
					return false; // Error!
			}
		}

		// End chunk
		return EndChunk(cFile, cChunkStack);
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::BeginChunk(FILE &cFile, ChunkStack &cChunkStack, uint32 nType)
{
	// Output log message
	char szTemp[256];
	GetChunkString(nType, szTemp);
	g_pLog->AddSpaces(PLLog::TabSize);

	// Create a new chunk
	MeshFile::Chunk sChunk;
	sChunk.nType = nType;
	sChunk.nSize = ftell(&cFile);

	// Write empty chunk
	MeshFile::Chunk sEmptyChunk = {0, 0};
	if (!Write(cFile, &sEmptyChunk, sizeof(sEmptyChunk)))
		return false; // Error!

	// Push on stack
	cChunkStack.push(sChunk);

	// Done
	return true;
}

bool PLScenePLMesh::EndChunk(FILE &cFile, ChunkStack &cChunkStack)
{
	// Pop chunk from stack
	if (cChunkStack.size() > 0) {
		MeshFile::Chunk &sChunk = cChunkStack.top();

		// Save current file position and calculate chunk size
		uint32 nChunkStart = sChunk.nSize;
		uint32 nChunkEnd   = ftell(&cFile);
		sChunk.nSize	   = nChunkEnd - nChunkStart;

		// Output log message
		char szTemp[256];
		GetChunkString(sChunk.nType, szTemp);
		g_pLog->AddSpaces(-PLLog::TabSize);

		// Write chunk header
		bool bResult = !fseek(&cFile, nChunkStart, SEEK_SET) &&
					    Write(cFile, &sChunk, sizeof(sChunk)) &&
					   !fseek(&cFile, nChunkEnd, SEEK_SET);

		// Remove the chunk from the stack
		cChunkStack.pop();

		// Done
		return bResult;
	} else {
		// Error!
		return false;
	}
}

bool PLScenePLMesh::Write(FILE &cFile, void *pBuffer, ULONG nSize)
{
	return (fwrite(pBuffer, nSize, 1, &cFile) == 1);
}

void PLScenePLMesh::GetChunkString(uint32 nType, char szString[])
{
	switch (nType) {
		case MeshFile::CHUNK_MESHFILE:
			strcpy(szString, "CHUNK_MESHFILE");
			break;

		case MeshFile::CHUNK_MATERIALS:
			strcpy(szString, "CHUNK_MATERIALS");
			break;

		case MeshFile::CHUNK_MESH:
			strcpy(szString, "CHUNK_MESH");
			break;

		case MeshFile::CHUNK_LODLEVEL:
			strcpy(szString, "CHUNK_LODLEVEL");
			break;

		case MeshFile::CHUNK_INDEXBUFFER:
			strcpy(szString, "CHUNK_INDEXBUFFER");
			break;

		case MeshFile::CHUNK_GEOMETRY:
			strcpy(szString, "CHUNK_GEOMETRY");
			break;

		case MeshFile::CHUNK_MORPHTARGET:
			strcpy(szString, "CHUNK_MORPHTARGET");
			break;

		case MeshFile::CHUNK_VERTEXBUFFER:
			strcpy(szString, "CHUNK_VERTEXBUFFER");
			break;

		case MeshFile::CHUNK_VERTEXATTRIBUTE:
			strcpy(szString, "CHUNK_VERTEXATTRIBUTE");
			break;

		case MeshFile::CHUNK_WEIGHT:
			strcpy(szString, "CHUNK_WEIGHT");
			break;

		case MeshFile::CHUNK_VERTEXWEIGHTS:
			strcpy(szString, "CHUNK_VERTEXWEIGHTS");
			break;

		case MeshFile::CHUNK_SKELETON:
			strcpy(szString, "CHUNK_SKELETON");
			break;

		case MeshFile::CHUNK_ANIMATIONS:
			strcpy(szString, "CHUNK_ANIMATIONS");
			break;

		case MeshFile::CHUNK_MORPHTARGETANIMATION:
			strcpy(szString, "CHUNK_MORPHTARGETANIMATION");
			break;

		default:
			strcpy(szString, "");
			break;
	}
}
