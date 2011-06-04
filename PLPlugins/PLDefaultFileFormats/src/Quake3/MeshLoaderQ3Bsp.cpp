/*********************************************************\
 *  File: MeshLoaderQ3Bsp.cpp                            *
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


// [TODO] Rework completely ...


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/File.h>
#include <PLCore/Tools/LoadableType.h>
#include <PLCore/Tools/LoadableManager.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImagePart.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Texture/TextureManager.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLRenderer/Effect/EffectPass.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Effect/EffectTechnique.h>
#include <PLRenderer/Effect/EffectPassLayer.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/Quake3/MeshLoaderQ3Bsp.h"


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
pl_implement_class(MeshLoaderQ3Bsp)


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
// Lumps enumeration
enum eLumps {
	kEntities = 0,	// Stores player/object positions, etc...
	kTextures,		// Stores texture information
	kPlanes,		// Stores the splitting planes
	kNodes,			// Stores the BSP nodes
	kLeafs,			// Stores the leafs of the nodes
	kLeafFaces,		// Stores the leaf's indices into the faces
	kLeafBrushes,	// Stores the leaf's indices into the brushes
	kModels,		// Stores the info of world models
	kBrushes,		// Stores the brushes info (for collision)
	kBrushSides,	// Stores the brush surfaces info
	kVertices,		// Stores the level vertices
	kMeshVerts,		// Stores the model vertices offsets
	kShaders,		// Stores the shader files (blending, anims..)
	kFaces,			// Stores the faces for the level
	kLightmaps,		// Stores the lightmaps for the level
	kLightVolumes,	// Stores extra world lighting information
	kVisData,		// Stores PVS and cluster info (visibility)
	kMaxLumps		// A constant to store the number of lumps
};


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
// BSP header structure
struct tBSPHeader {
	char strID[4];	// Should always be 'IBSP'
	int version;	// Should be 0x2e for Quake 3 files
};

// BSP lump structure
struct tBSPLump {
	int offset;	// Offset into the file for the start of this lump
	int length;	// Length in bytes for this lump
};

// BSP vertex structure
struct tBSPVertex {
	float vPosition[3];			// (x, y, z) position
	float vTextureCoord[2];		// (u, v) texture coordinate
	float vLightmapCoord[2];	// (u, v) lightmap coordinate
	float vNormal[3];			// (x, y, z) normal vector
	uint8 color[4];				// RGBA color for the vertex
};

// BSP face structure
struct tBSPFace {
	int textureID;			// The index into the texture array
	int effect;				// The index for the effects (or -1 = n/a)
	int type;				// 1=polygon, 2=patch, 3=mesh, 4=billboard
	int startVertIndex;		// The starting index into this face's first vertex
	int numOfVerts;			// The number of vertices for this face
	int meshVertIndex;		// The index into the first meshvertex
	int numMeshVerts;		// The number of mesh vertices
	int lightmapID;			// The texture index for the lightmap
	int lMapCorner[2];		// The face's lightmap corner in the image
	int lMapSize[2];		// The size of the lightmap section
	float lMapPos[3];		// The 3D origin of lightmap
	float lMapVecs[2][3];	// The 3D space for s and t unit vectors
	float vNormal[3];		// The face normal
	int size[2];			// The bezier patch dimensions
};

// BSP texture structure
struct tBSPTexture {
	char strName[64];	// The name of the texture w/o the extension
	int flags;
	int contents;
};

// BSP lightmap structure which stores the 128x128 RGB values
struct tBSPLightmap {
	uint8 imageBits[128][128][3];	// The RGB data in a 128x128 image
};

namespace Q3Bsp {
struct Material {
	uint32 nIndex;		/**< Material index */
	String sName;		/**< Material name */
	int    nTextureID;	/**< Texture ID */
	int    nLightmapID;	/**< Lightmap ID */
};

struct Face {
	int nTextureID;
	int nLightmapID;
	int nMaterialID;
	Array<uint32> lstVertices;
	Face &operator =(const Face &cSource)
	{
		// We do not need an implementation in here...
		return *this;
	}
	bool operator ==(const Face &cVertex) const
	{
		// We do not need an implementation in here...
		return false;
	}
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
	float  fLS, fLT;		/**< Lightmap texture coordinate */
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
     For vertex optimizing
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

		inline bool IsEqual(float f1, float f2)
		{
			return (Math::Abs(f1-f2) < 0.001f);
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
					if (IsEqual(cVer.fX,  cVertex.fX)  &&
						IsEqual(cVer.fY,  cVertex.fY)  &&
						IsEqual(cVer.fZ,  cVertex.fZ)  &&
						IsEqual(cVer.fNX, cVertex.fNX) &&
						IsEqual(cVer.fNY, cVertex.fNY) &&
						IsEqual(cVer.fNZ, cVertex.fNZ) &&
						IsEqual(cVer.fS,  cVertex.fS)  &&
						IsEqual(cVer.fT,  cVertex.fT)  &&
						IsEqual(cVer.fLS, cVertex.fLS) &&
						IsEqual(cVer.fLT, cVertex.fLT)) {
						// The vertex is already in the table!
						return &cVer;
					}
				}
			}

			// Add vertex to table
			Vertex &cVer = cSlot.Add();
			cVer.nVertex = cVertex.nVertex;
			cVer.fX      = cVertex.fX;
			cVer.fY      = cVertex.fY;
			cVer.fZ      = cVertex.fZ;
			cVer.fNX     = cVertex.fNX;
			cVer.fNY     = cVertex.fNY;
			cVer.fNZ     = cVertex.fNZ;
			cVer.fS      = cVertex.fS;
			cVer.fT      = cVertex.fT;
			cVer.fLS     = cVertex.fLS;
			cVer.fLT     = cVertex.fLT;
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
} // Q3Bsp


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderQ3Bsp::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderQ3Bsp::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Read file
	// Read and check the header
	tBSPHeader sHeader;
	cFile.Read(&sHeader, sizeof(tBSPHeader), 1);
	if (MemoryManager::Compare(sHeader.strID, "IBSP", 4) || sHeader.version != 0x2e)
		return false; // Error!

	// Read lump information
	tBSPLump sLumps[kMaxLumps];
	cFile.Read(sLumps, sizeof(tBSPLump), kMaxLumps);

	// Read vertices
	uint32 nNumOfVertices = sLumps[kVertices].length/sizeof(tBSPVertex);
	tBSPVertex *pVertices = new tBSPVertex[nNumOfVertices];
	cFile.Seek(sLumps[kVertices].offset);
	cFile.Read(pVertices, sizeof(tBSPVertex), nNumOfVertices);

	// Read mesh vertices
	uint32 nNumOfMeshVertices = sLumps[kMeshVerts].length/sizeof(int);
	int *pMeshVertices = new int[nNumOfMeshVertices];
	cFile.Seek(sLumps[kMeshVerts].offset);
	cFile.Read(pMeshVertices, sizeof(int), nNumOfMeshVertices);

	// Read faces
	uint32 nNumOfFaces = sLumps[kFaces].length/sizeof(tBSPFace);
	nNumOfFaces--; // ?? The last face isn't correct ??
	tBSPFace *pFaces = new tBSPFace[nNumOfFaces];
	cFile.Seek(sLumps[kFaces].offset);
	cFile.Read(pFaces, sizeof(tBSPFace), nNumOfFaces);

	// Read textures
	uint32 nNumOfTextures = sLumps[kTextures].length/sizeof(tBSPTexture);
	tBSPTexture *pTextures = new tBSPTexture[nNumOfTextures];
	cFile.Seek(sLumps[kTextures].offset);
	cFile.Read(pTextures, sizeof(tBSPTexture), nNumOfTextures);

	// Read lightmaps
	uint32 nNumOfLightmaps = sLumps[kLightmaps].length/sizeof(tBSPLightmap);
	tBSPLightmap *pLightmaps = new tBSPLightmap[nNumOfLightmaps];
	cFile.Seek(sLumps[kLightmaps].offset);
	cFile.Read(pLightmaps, sizeof(tBSPLightmap), nNumOfLightmaps);

	// Optimize read data
	Array<Q3Bsp::Face> lstFaces(nNumOfFaces);
	Array<Q3Bsp::Vertex*> lstVertexTex;
	lstVertexTex.Resize(nNumOfVertices, false, false);
	Q3Bsp::VertexHashTable *pVHTable = new Q3Bsp::VertexHashTable(nNumOfVertices*2);
	Q3Bsp::Vertex cVertex;
	uint32 nNumOfIndices = 0;
	const float fScale = 0.03f;	// The Quake coordinate system is also scaled so that one meter is about 0.03 units
	tBSPFace *pBSPFace = pFaces;
	for (uint32 i=0; i<nNumOfFaces; i++, pBSPFace++) {
		Q3Bsp::Face &cFace = lstFaces[i];
		cFace.nTextureID  = pBSPFace->textureID;
		cFace.nLightmapID = pBSPFace->lightmapID;
		for (uint32 nVertex=0; nVertex<static_cast<uint32>(pBSPFace->numMeshVerts); nVertex++) {
			uint32 nIndex = pBSPFace->startVertIndex+pMeshVertices[pBSPFace->meshVertIndex+nVertex];
			if (nIndex < nNumOfVertices && nIndex >= 0) {
				tBSPVertex *pBspVertex = &pVertices[nIndex];
				cVertex.nVertex = nIndex;
				cVertex.fX  =  pBspVertex->vPosition[0]*fScale;
				cVertex.fZ  = -pBspVertex->vPosition[1]*fScale;
				cVertex.fY  =  pBspVertex->vPosition[2]*fScale;
				cVertex.fS  =   pBspVertex->vTextureCoord[0];
				cVertex.fT  = 1-pBspVertex->vTextureCoord[1];
				cVertex.fLS =  pBspVertex->vLightmapCoord[0];
				cVertex.fLT =  pBspVertex->vLightmapCoord[1];
				cVertex.fNX =  pBspVertex->vNormal[0];
				cVertex.fNZ = -pBspVertex->vNormal[1];
				cVertex.fNY =  pBspVertex->vNormal[2];

				// Add vertex to list if not already in
				Q3Bsp::Vertex *pVertex = pVHTable->Add(cVertex);
				if (pVertex->nIndex >= lstVertexTex.GetNumOfElements())
					lstVertexTex.Add(pVertex);

				// Update face vertex ID
				cFace.lstVertices.Add(pVertex->nIndex);
				nNumOfIndices++;
			}
		}
	}
	bool bNormals    = true;
	bool bTexCoords  = true;
	bool bLTexCoords = true;


// Part II
	// Create the mesh and fill it with the read data
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();

	// Create morph targets
	MeshMorphTarget *pMorphTarget  = cMesh.AddMorphTarget();
	VertexBuffer    *pVertexBuffer = pMorphTarget->GetVertexBuffer();
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	if (bNormals)
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
	if (bTexCoords)
		pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
	if (bLTexCoords)
		pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 1, VertexBuffer::Float2);
	pVertexBuffer->Allocate(lstVertexTex.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);

	// Add materials
	Array<Q3Bsp::Material*> lstMaterials;
	HashMap<String, Q3Bsp::Material*> mapMaterials;
	for (uint32 i=0; i<nNumOfFaces; i++) {
		Q3Bsp::Face &cFace = lstFaces[i];
		String sMatName = String::Format("%d_%d", cFace.nTextureID, cFace.nLightmapID);
		Q3Bsp::Material *pFoundMaterial = mapMaterials.Get(sMatName);
		if (!pFoundMaterial) {
			Q3Bsp::Material *pMaterial = new Q3Bsp::Material;
			pMaterial->nIndex      = lstMaterials.GetNumOfElements();
			pMaterial->sName       = sMatName;
			pMaterial->nTextureID  = cFace.nTextureID;
			pMaterial->nLightmapID = cFace.nLightmapID;
			lstMaterials.Add(pMaterial);
			mapMaterials.Add(sMatName, pMaterial);
			cFace.nMaterialID = pMaterial->nIndex;
		} else {
			cFace.nMaterialID = pFoundMaterial->nIndex;
		}
	}

	// Get the renderer context
	RendererContext &cRendererContext = cMesh.GetRenderer()->GetRendererContext();

	// Add all the materials
	String sFilenameT;
	for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++) {
		// Create the material
		Q3Bsp::Material *pMaterial = lstMaterials[i];
		Material *pMat = cRendererContext.GetMaterialManager().Get(pMaterial->sName);
		if (pMat) {
			cMesh.AddMaterial(pMat);
			continue;
		}
		pMat = cRendererContext.GetMaterialManager().Create(pMaterial->sName);
		cMesh.AddMaterial(pMat);
		Effect *pFX = cRendererContext.GetEffectManager().Create();
		pMat->SetEffect(pFX);

		// Valid texture?
		if (pMaterial->nTextureID < 0 || pMaterial->nTextureID >= static_cast<int>(nNumOfTextures))
			continue;
		tBSPTexture *pTexture = &pTextures[pMaterial->nTextureID];
		sFilenameT = pTexture->strName;

		// [TODO] It's unclear, what this block really was supposed to do, as no file is currently read and pTextureFile
		//        is not used anymore. Perhaps it's sFilenameT that's set here
		/*
		// Try to load in directly by using the given filename
		File *pTextureFile = (File*)FileSystem::GetInstance()->Open(sFilenameT);
		if (!pTextureFile || !pTextureFile->Open()) {
			if (pTextureFile)
				pTextureFile->Release();
			// Try to load in the texture with an supported image format
			LoadableType *pLoadableType = LoadableManager::GetInstance()->GetType("Image");
			if (pLoadableType) {
				// Loop through all seach paths
				bool bValid = false;
				for (uint32 nPath=0; nPath<=pLoadableType->GetNumOfSearchPaths() && !bValid; nPath++) {
					// Loop through all supported image formats
					for (uint32 nFormat=0; nFormat<pLoadableType->GetNumOfFormats() && !bValid; nFormat++) {
						// Construct filename
						if (nPath)
							sFilenameT = pLoadableType->GetSearchPath(nPath-1) + String::Format("%s.", pTexture->strName) + pLoadableType->GetFormat(nFormat);
						else
							sFilenameT = String::Format("%s.", pTexture->strName) + pLoadableType->GetFormat(nFormat);

						// Try to open this file
						pTextureFile = (File*)FileSystem::GetInstance()->Open(sFilenameT);
						if (pTextureFile) {
							if (pTextureFile->Open())
								bValid = true;
							pTextureFile->Release();
						}
					}
				}
			}
		} else {
			pTextureFile->Release();
		}
		*/

		EffectTechnique *pTechnique = pFX->AddTechnique();
		pFX->SelectTechnique(0);
		EffectPass *pFXPass = pTechnique->AddPass();

		// Decal texture
		EffectPassLayer *pFXPassLayer = pFXPass->AddLayer();
		// [TODO]
//		pFXPassLayer->Load(sFilenameT);

		// Add lightmap texture
		if (pMaterial->nLightmapID < 0 || pMaterial->nLightmapID >= static_cast<int>(nNumOfLightmaps))
			continue;
		tBSPLightmap *pLightmap = &pLightmaps[pMaterial->nLightmapID];

		String sLName = sFilenameT + "_L" + pMaterial->nLightmapID;
		Texture *pTex = cRendererContext.GetTextureManager().Get(sLName);
		if (!pTex) {
			float max, r, g, b;
			uint8 *pImageData = &pLightmap->imageBits[0][0][0];
			for (int nElement=0; nElement<128*128; nElement+=3) {
				max  = 1.0f;
				r    = (static_cast<float>(pImageData[nElement])*3.1f)/255.0f;
				g    = (static_cast<float>(pImageData[nElement+1])*3.1f)/255.0f;
				b    = (static_cast<float>(pImageData[nElement+2])*3.1f)/255.0f;
				if (r > 1.0f)
					if ((1.0f/r) < max)
						max = 1.0f/r;
				if (g > 1.0f)
					if ((1.0f/g) < max)
						max = 1.0f/g;
				if (b > 1.0f)
					if ((1.0f/b) < max)
						max = 1.0f/b;

				max *= 255;
				r   *= max;
				g   *= max;
				b   *= max;
				pImageData[nElement]   = static_cast<uint8>(r);
				pImageData[nElement+1] = static_cast<uint8>(g);
				pImageData[nElement+2] = static_cast<uint8>(b);
			}

			// Create the image and copy over the lightmap data
			Image cImage = Image::CreateImageAndCopyData(DataByte, ColorRGB, Vector3i(128, 128, 1), CompressionNone, &pLightmap->imageBits[0][0][0]);

			// Create the texture
			pTex = cRendererContext.GetTextureManager().Create(sLName);
			pTex->SetTextureBuffer(reinterpret_cast<TextureBuffer*>(pVertexBuffer->GetRenderer().CreateTextureBuffer2D(cImage)));
		}

		pFXPassLayer = pFXPass->AddLayer();
//		pFXPassLayer->SetTexture(pTex);
	}

	// Fill vertex buffer
	if (pVertexBuffer->Lock(Lock::WriteOnly)) {
		{ // Fill vertex buffer
			int i = 0;
			Iterator<Q3Bsp::Vertex*> cIterator = lstVertexTex.GetIterator();
			while (cIterator.HasNext()) {
				const Q3Bsp::Vertex *pVertex = cIterator.Next();

				// Position
				float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::Position));
				pfVertex[Vector3::X] = pVertex->fX;
				pfVertex[Vector3::Y] = pVertex->fY;
				pfVertex[Vector3::Z] = pVertex->fZ;

				// Normal
				if (bNormals) {
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::Normal));
					pfVertex[Vector3::X] = pVertex->fNX;
					pfVertex[Vector3::Y] = pVertex->fNY;
					pfVertex[Vector3::Z] = pVertex->fNZ;
				}

				// Texture coordinate
				if (bTexCoords) {
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::TexCoord));
					pfVertex[Vector2::X] = pVertex->fS;
					pfVertex[Vector2::Y] = pVertex->fT;
				}

				// Lightmap texture coordinate
				if (bLTexCoords) {
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(i, VertexBuffer::TexCoord, 1));
					pfVertex[Vector2::X] = pVertex->fLS;
					pfVertex[Vector2::Y] = pVertex->fLT;
				}

				// Increment index
				i++;
			}
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Allocate index buffer
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	if (pIndexBuffer) {
		pIndexBuffer->SetElementTypeByMaximumIndex(lstVertexTex.GetNumOfElements()-1);
		pIndexBuffer->Allocate(nNumOfIndices, bStatic ? Usage::Static : Usage::Dynamic);

		// Fill index buffer
		Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
		if (pIndexBuffer->Lock(Lock::WriteOnly)) {
			uint32 nIndex = 0;
			int nStartVertex = 0;
			int nVertices    = 0;

			// Check material ID's
			for (uint32 i=0; i<nNumOfFaces; i++) {
				Q3Bsp::Face &cFace = lstFaces[i];
				if (cFace.nTextureID >= static_cast<int>(cMesh.GetNumOfMaterials()))
					cFace.nTextureID = -1;
			}

			// Go through all object materials
			for (int nMat=-1; nMat<static_cast<int>(cMesh.GetNumOfMaterials()); nMat++) {
				// Fill index buffer
				for (uint32 i=0; i<nNumOfFaces; i++) {
					// Get the face
					Q3Bsp::Face &cFace = lstFaces[i];

					// Check material
					if (cFace.nMaterialID == nMat) {
						// Add indices in reversed order
						for (int j=cFace.lstVertices.GetNumOfElements()-1; j>=0; j--) {
							pIndexBuffer->SetData(nIndex++, cFace.lstVertices[j]);
							nVertices++;
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
	}

	// Cleanup
	for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++)
		delete lstMaterials[i];
	lstMaterials.Clear();
	mapMaterials.Clear();
	delete pVHTable;
	delete [] pVertices;
	delete [] pFaces;
	delete [] pTextures;
	delete [] pLightmaps;

	// Done
	return true;
}

bool MeshLoaderQ3Bsp::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderQ3Bsp::MeshLoaderQ3Bsp()
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderQ3Bsp::~MeshLoaderQ3Bsp()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
