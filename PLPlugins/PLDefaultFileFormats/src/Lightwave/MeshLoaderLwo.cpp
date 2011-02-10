/*********************************************************\
 *  File: MeshLoaderLwo.cpp                              *
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


// [TODO] Add support for multi surfaces/materials (PTAG chunk)


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/Wrapper.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include <PLMath/Vector2.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/Lightwave/MeshLoaderLwo.h"


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
pl_implement_class(MeshLoaderLwo)


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
static const int StringLength = 1024;
// fourcc defines
#define FOURCC(a,b,c,d)   (a+(b<<8)+(c<<16)+(d<<24))
#define FOURCCPRINTF(tag) (tag&0xff), (tag&0xff00)>>8, (tag&0xff0000)>>16, (tag&0xff000000)>>24

// Endians
inline void *ReverseBytes(void *p, uint32 length)
{
	uint8 *&q = reinterpret_cast<uint8*&>(p);
	for (uint32 i=0; i<length/2; i++) {
		// Swap p[i] and p[length-i]
		q[i]		  ^= q[length-i-1];
		q[length-i-1] ^= q[i];
		q[i]		  ^= q[length-i-1];
	}

	return p;
}

template<typename tAnyType> inline tAnyType Reverse(tAnyType &t) { return *reinterpret_cast<tAnyType*>(ReverseBytes(reinterpret_cast<void*>(&t), sizeof(tAnyType))); }
#if defined (WIN32) && ! defined (LITTLE_ENDIAN)
	#define LITTLE_ENDIAN
#endif
#ifdef LITTLE_ENDIAN
	#define big(v)    Reverse(v)
	#define little(v) v
#else
	#define big(v)    v
	#define little(v) Reverse(v)
#endif

enum Bits {
	Bit0 = 1<<0, Bit1 = 1<<1, Bit2  = 1<<2 , Bit3  = 1<<3 , Bit4  = 1<<4 , Bit5  = 1<<5 , Bit6  = 1<<6 , Bit7  = 1<<7,
	Bit8 = 1<<8, Bit9 = 1<<9, Bit10 = 1<<10, Bit11 = 1<<11, Bit12 = 1<<12, Bit13 = 1<<13, Bit14 = 1<<14, Bit15 = 1<<15,

	Mask8  = (1<<8)-1,  // bits 0..7
	Mask16 = (1<<16)-1, // bits 0..15
};

namespace Lwo {
class Vertex {
	public:
	Vector3 vPos;
	bool bTexCoordUsed[4];
	Vector2 vTexCoord[4];

	Vertex() {
		bTexCoordUsed[0] = bTexCoordUsed[1] = bTexCoordUsed[2] = bTexCoordUsed[3] = false;
	}
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

struct Triangle {
	uint32 nIndex[3];
};
} // Lwo


//[-------------------------------------------------------]
//[ Internal helper functions                             ]
//[-------------------------------------------------------]
uint32 GetVX(File &cFile)
{
	// Read vertex index
	uint8 fidx;
	cFile.Read(&fidx, sizeof(uint8), 1);
	if (fidx == 0xff) {
		uint8 a, b, c;
		cFile.Read(&a, sizeof(uint8), 1);
		cFile.Read(&b, sizeof(uint8), 1);
		cFile.Read(&c, sizeof(uint8), 1);
		return (a<<16) | (b<<8) | c;
	} else {
		uint8 b;
		cFile.Read(&b, sizeof(uint8), 1);
		return (fidx<<8) | b;
	}
}

void ReadString(File &cFile, char *pszString)
{
	int nCount = 0; // To avoid a buffer overflow...
	uint8 nChar;

	cFile.Read(&nChar, sizeof(uint8), 1);
	while (nChar != '\0' && nCount<StringLength-1) {
		*pszString = nChar;
		pszString++;
		nCount++;
		cFile.Read(&nChar, sizeof(uint8), 1);
	}
	*pszString = '\0';

	// Read and ignore the rest of the string (if there's one)
	while (nChar != '\0')
		cFile.Read(&nChar, sizeof(uint8), 1);
}


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderLwo::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderLwo::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Formid magic fourcc
	uint32 nFormTag;
	cFile.Read(&nFormTag, sizeof(uint32), 1);
	if (nFormTag != FOURCC('F','O','R','M')) {
		PL_LOG(Error, "Invalid file tag, FORM expected")

		// Error!
		return false;
	}

	// Get file size
	uint32 nFileSize = cFile.GetSize();

	// Chunk size of global chunk (file size)
	uint32 nChunkSize;
	cFile.Read(&nChunkSize, sizeof(uint32), 1);
	nChunkSize = big(nChunkSize);
	if (nChunkSize != nFileSize-8) {
		PL_LOG(Error, String::Format("Invalid file size, %i sized chunk (-8), %i sized file!\n", nFileSize, nChunkSize))

		// Error!
		return false;
	}

	// Check version
	uint32 nLWO2Tag;
	cFile.Read(&nLWO2Tag, sizeof(uint32), 1);
	if (nLWO2Tag != FOURCC('L','W','O','2')) {
		PL_LOG(Error, "Invalid file version, LWO2 (Lightwave 6+) expected!")

		// Error!
		return false;
	}

	// Current layer information. Not using layers here, but some information is needed (like pivot to offset vertices)
	Vector3 vPivot;
	bool bFirstLayer = true;			// Use only the first layer...
	bool bCreateMesh = false;			// Don't read any more, start creating the mesh
	uint32 nOrginalNumOfVertices = 0;	// Orginal number of vertices
	Array<Lwo::Vertex> lstVertices;
	Array<Lwo::Triangle*> lstTriangles;
	uint32 nMaxNumOfTexCoords = 0;
	char szTemp[StringLength];
	while (cFile.Tell() < static_cast<int32>(nFileSize) && !bCreateMesh) {
		// Read chunk tag
		uint32 nTag;
		cFile.Read(&nTag,       4, 1);
		cFile.Read(&nChunkSize, 4, 1);
		nChunkSize = big(nChunkSize);
		int32 nOldPos = cFile.Tell();

		// Process chunk
		switch (nTag) {
			// SURF - Surface information
			case FOURCC('S','U','R','F'):
			{
				// Name
				ReadString(cFile, szTemp);
				if ((Wrapper::GetStringLength(szTemp)+1)&1)
					cFile.Seek(1, File::SeekCurrent);

				// Source
				ReadString(cFile, szTemp);
				if ((Wrapper::GetStringLength(szTemp)+1)&1)
					cFile.Seek(1, File::SeekCurrent);

				// Parse surface parameters
				while (cFile.Tell() < int32(nOldPos+nChunkSize)) {
					uint32 nSubTag;
					cFile.Read(&nSubTag, sizeof(uint32), 1);
					uint32 nSubSize;
					cFile.Read(&nSubSize, sizeof(uint32), 1);
					nSubSize = big(nSubSize);

					switch (nSubTag) {
						case FOURCC('D','I','F','F'): // Diffuse level
						case FOURCC('S','P','E','C'): // Specular level
						case FOURCC('S','M','A','N'): // Max. smoothing angle
							cFile.Seek(nSubSize, File::SeekCurrent);
							break;

						case FOURCC('C','O','L','R'):
						{
							float fR;
							cFile.Read(&fR, sizeof(float), 1);
							fR = big(fR);
							float fG;
							cFile.Read(&fG, sizeof(float), 1);
							fG = big(fG);
							float fB;
							cFile.Read(&fB, sizeof(float), 1);
							fB = big(fB);
//							uint32 nEnv = GetVX(cFile);
//							cFile.Seek(nSubSize, File::SeekCurrent)
							break;
						}

						default:
							PL_LOG(Debug, String::Format("Unknown subtag %c%c%c%c in SURF encountered", FOURCCPRINTF(nSubTag)))
							break;
					}
				}
				break;
			}

			// LAYR - Layer information
			case FOURCC('L','A','Y','R'):
			{
				// At the moment this loader can only handle one layer...
				if (bFirstLayer) {
					bFirstLayer = false;
					uint16 nLayerNum;
					cFile.Read(&nLayerNum, sizeof(uint16), 1);
					nLayerNum = big(nLayerNum);
					uint16 nLayerFlags;
					cFile.Read(&nLayerFlags, sizeof(uint16), 1);
					nLayerFlags = big(nLayerFlags);

					cFile.Read(&vPivot.x, sizeof(float), 1);
					vPivot.x = big(vPivot.x);
					cFile.Read(&vPivot.y, sizeof(float), 1);
					vPivot.y = big(vPivot.y);
					cFile.Read(&vPivot.z, sizeof(float), 1);
					vPivot.z = big(vPivot.z);

					ReadString(cFile, szTemp);
					if ((Wrapper::GetStringLength(szTemp)+1)&1)
						cFile.Seek(1, File::SeekCurrent);

					PL_LOG(Debug, String::Format("New layer %i: \'%s\' at %g %g %g with flags %i\n",
						nLayerNum, szTemp, vPivot.x, vPivot.y, vPivot.z, nLayerFlags))
				} else {
					// Stop reading at this point
					bCreateMesh = true;
				}
				break;
			}

			// PNTS - 3D points / vertices
			case FOURCC('P','N','T','S'):
			{
				Vector3 vV;
				nOrginalNumOfVertices = nChunkSize/12;
				lstVertices.Resize(nOrginalNumOfVertices, true, false);
				for (uint32 i=0; i<nOrginalNumOfVertices; i++) {
					Lwo::Vertex &cVertex = lstVertices[i];
					cFile.Read(&vV.x, sizeof(float), 1);
					vV.x = big(vV.x);
					cFile.Read(&vV.y, sizeof(float), 1);
					vV.y = big(vV.y);
					cFile.Read(&vV.z, sizeof(float), 1);
					vV.z = big(vV.z);
					cVertex.vPos = vV+vPivot;
				}
				break;
			}

			// POLS - polygons
			case FOURCC('P','O','L','S'):
			{
				uint32 nType;
				cFile.Read(&nType, sizeof(uint32), 1);
				if (nType != FOURCC('F','A','C','E')) {
					PL_LOG(Warning, String::Format("Unsupported polygon type %c%c%c%c found!", FOURCCPRINTF(nType)))

					// Skip
					cFile.Seek(nChunkSize-4, File::SeekCurrent);
					break;
				}

				while (cFile.Tell() < int32(nOldPos+nChunkSize)) {
					uint16 nf;
					cFile.Read(&nf, sizeof(uint16), 1);
					nf = big(nf);
					uint16 nNumVert = nf&~(Bit15 | Bit14 | Bit13 | Bit12 | Bit11 | Bit10);

					if (nNumVert != 3) {
						PL_LOG(Warning, String::Format("Unsupported primitive type with %i vertices!", nNumVert))
						for (uint32 j=0; j<nNumVert; j++)
							GetVX(cFile);

						// Insert bogus tri to keep proper order
						Lwo::Triangle *pTriangle = new Lwo::Triangle;
						pTriangle->nIndex[0] = 0;
						pTriangle->nIndex[1] = 0;
						pTriangle->nIndex[2] = 0;
						lstTriangles.Add(pTriangle);
					} else {
						uint32 nIndex1 = GetVX(cFile);
						uint32 nIndex2 = GetVX(cFile);
						uint32 nIndex3 = GetVX(cFile);

						Lwo::Triangle *pTriangle = new Lwo::Triangle;
						pTriangle->nIndex[0] = nIndex1;
						pTriangle->nIndex[1] = nIndex2;
						pTriangle->nIndex[2] = nIndex3;
						lstTriangles.Add(pTriangle);
					}
				}
				break;
			}

			// PTAG
			case FOURCC('P','T','A','G'):
			{
				uint32 nType;
				cFile.Read(&nType, sizeof(uint32), 1);
				if (nType != FOURCC('S','U','R','F')) {
					// Not surf, so simply skip
					break;
				}

				// Currently not supported...
				break;
			}

			// VMAD: --MUST-- be before PTAG, otherwise undefined behaviour
			case FOURCC('V','M','A','D'):
			{
				uint32 nType;
				cFile.Read(&nType, sizeof(uint32), 1);
				uint16 nDim;
				cFile.Read(&nDim, sizeof(uint16), 1);
				nDim = big(nDim);

				ReadString(cFile, szTemp);
				if ((Wrapper::GetStringLength(szTemp)+1)&1)
					cFile.Seek(1, File::SeekCurrent);
				
				switch (nType) {
					case FOURCC('T','X','U','V'):
					{
						if (nDim != 2) {
							PL_LOG(Warning, String::Format("uvmap with invalid dimension of %i found!", nDim))
							break;
						}

						// Read while not at end of buffer
						while (cFile.Tell() < int32(nOldPos+nChunkSize)) {
							uint32 nVert = GetVX(cFile);
							uint32 nFace = GetVX(cFile);

							// Read uv coords
							Vector2 vV;
							cFile.Read(&vV.x, sizeof(float), 1);
							vV.x = big(vV.x);
							cFile.Read(&vV.y, sizeof(float), 1);
							vV.y = big(vV.y);

							if (nFace < static_cast<uint32>(lstTriangles.GetNumOfElements())) {
								Lwo::Triangle *pTriangle = lstTriangles[nFace];
								Lwo::Vertex   &cVertex   = lstVertices[nVert];
								uint32 i;
								for (i=0; i<3; i++) {
									if (pTriangle->nIndex[i] != nVert)
										continue;

									// Check whether this vertex has already a texture coordinate
									if (cVertex.bTexCoordUsed[0]) {
										// Same texture coordinate?
										if (cVertex.vTexCoord[0] != vV) {
											// New vertex already there?
											// [TODO] Use a kind of hash table to make this more efficent?
											for (uint32 n=nOrginalNumOfVertices; n<lstVertices.GetNumOfElements(); n++) {
												Lwo::Vertex &cNewVertex = lstVertices[n];
												if (cNewVertex.vPos == cVertex.vPos &&
													cNewVertex.vTexCoord[0] == vV) {
													pTriangle->nIndex[i] = n;
													break;
												}
											}

											// Damn! Now we have to duplicate the vertex...
											if (pTriangle->nIndex[i] == nVert) {
												Lwo::Vertex &cNewVertex = lstVertices.Add();
												cNewVertex.vPos = cVertex.vPos;
												cNewVertex.vTexCoord[0] = vV;
												cNewVertex.bTexCoordUsed[0] = true;
												pTriangle->nIndex[i] = lstVertices.GetNumOfElements()-1;
											}
										}
									} else {
										cVertex.vTexCoord[0] = vV;
										cVertex.bTexCoordUsed[0] = true;
										if (nMaxNumOfTexCoords < 1)
											nMaxNumOfTexCoords = 1;
									}
									break;
								}
								if (i >= 3) {
									PL_LOG(Warning, String::Format("Invalid vertex index in VMAD/TXUV, vertex %i not in face %i (%i,%i,%i)",
										nVert, nFace, pTriangle->nIndex[0], pTriangle->nIndex[1], pTriangle->nIndex[2]))
								}
							}
						}
						break;
					}
				}
				break;
			}

			// VMAP
			case FOURCC('V','M','A','P'):
			{
				uint32 nType;
				cFile.Read(&nType, sizeof(uint32), 1);
				uint16 nDim;
				cFile.Read(&nDim, sizeof(uint16), 1);
				nDim = big(nDim);

				ReadString(cFile, szTemp);
				if ((Wrapper::GetStringLength(szTemp)+1)&1)
					cFile.Seek(1, File::SeekCurrent);

				switch (nType) {
					case FOURCC('T','X','U','V'):
					{
						if (nDim != 2) {
							PL_LOG(Warning, String::Format("uvmap with invalid dimension of %i found!", nDim))
							break;
						}

						// Read while not at end of buffer
						while (cFile.Tell() < int32(nOldPos+nChunkSize)) {
							uint32 nIndex = GetVX(cFile);

							// Read uv coords
							Vector2 vV;
							cFile.Read(&vV.x, sizeof(float), 1);
							vV.x = big(vV.x);
							cFile.Read(&vV.y, sizeof(float), 1);
							vV.y = big(vV.y);

							// Add uv coord to vertex
							if (nIndex < static_cast<uint32>(lstVertices.GetNumOfElements())) {
								uint32 nUsed = 0;
								for (uint32 i=0; i<4; i++) {
									Lwo::Vertex &cVertex = lstVertices[nIndex];
									if (cVertex.bTexCoordUsed[i]) {
										nUsed++;
									} else {
										cVertex.bTexCoordUsed[i] = true;
										cVertex.vTexCoord[i] = vV;
										break;
									}
								}
								if (nUsed >= 4)
									PL_LOG(Warning, String::Format("Found more than 4 uv maps for vertex %i, not supported", nIndex))
								else {
									if (nMaxNumOfTexCoords < nUsed+1)
										nMaxNumOfTexCoords = nUsed+1;
								}
							}
						}
						break;
					}
				}
				break;
			}

			// Skip unknown chunks
			default:
				cFile.Seek(nChunkSize, File::SeekCurrent);
				break;
		}

		// Pad to 16 bit and skip
		if (!bCreateMesh) {
			if (int32(nOldPos+nChunkSize) != cFile.Tell()) {
				// Tag not completely read, still some bytes left!
				cFile.Seek(nOldPos+nChunkSize);
			}
			if (nChunkSize & 1)
				cFile.Seek(1, File::SeekCurrent);
		}
	}

	// Create the mesh and fill it with the read data
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();

	// Add dummy material
	cMesh.AddMaterial(cMesh.GetRenderer()->GetRendererContext().GetMaterialManager().GetStandard());

	// Create morph target
	MeshMorphTarget *pMorphTarget = cMesh.AddMorphTarget();
	VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	for (uint32 i=0; i<nMaxNumOfTexCoords; i++)
		pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, i, VertexBuffer::Float2);
	pVertexBuffer->Allocate(lstVertices.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);

	// Fill vertex buffer
	if (pVertexBuffer->Lock(Lock::WriteOnly)) {
		// Fill vertex buffer
		for (uint32 i=0; i<lstVertices.GetNumOfElements(); i++) {
			const Lwo::Vertex &cVertex = lstVertices[i];

			// Position
			float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::Position));
			pfVertex[Vector3::X] = cVertex.vPos.x;
			pfVertex[Vector3::Y] = cVertex.vPos.y;
			pfVertex[Vector3::Z] = cVertex.vPos.z;

			// Texture coordinates
			for (uint32 nCoord=0; nCoord<nMaxNumOfTexCoords; nCoord++) {
				pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::TexCoord, nCoord));
				pfVertex[Vector2::X] = cVertex.vTexCoord[nCoord].x;
				pfVertex[Vector2::Y] = cVertex.vTexCoord[nCoord].y;
			}
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Allocate index buffer
	uint32 nNumOfIndices = lstTriangles.GetNumOfElements()*3;
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(lstVertices.GetNumOfElements()-1);
	pIndexBuffer->Allocate(nNumOfIndices, bStatic ? Usage::Static : Usage::Dynamic);

	// Fill index buffer
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
	if (pIndexBuffer->Lock(Lock::WriteOnly)) {
		const Lwo::Triangle *pTriangle = lstTriangles[0];
		if (pTriangle) {
			for (uint32 i=0, nIndex=0; i<lstTriangles.GetNumOfElements(); i++) {
				pIndexBuffer->SetData(nIndex++, pTriangle->nIndex[0]);
				pIndexBuffer->SetData(nIndex++, pTriangle->nIndex[1]);
				pIndexBuffer->SetData(nIndex++, pTriangle->nIndex[2]);
				pTriangle++;
			}
		}

		// Setup geometry
		Geometry &cGeometry = lstGeometries.Add();
		cGeometry.SetPrimitiveType(Primitive::TriangleList);
		cGeometry.SetStartIndex(0);
		cGeometry.SetIndexSize(nNumOfIndices);
		cGeometry.SetMaterial(0);

		// Unlock the index buffer
		pIndexBuffer->Unlock();
	}

	// Cleanup
	for (uint32 i=0; i<lstTriangles.GetNumOfElements(); i++)
		delete lstTriangles[i];

	// Done
	return true;
}

bool MeshLoaderLwo::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderLwo::MeshLoaderLwo() :
	MethodLoad(this),
	MethodLoadParams(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderLwo::~MeshLoaderLwo()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
