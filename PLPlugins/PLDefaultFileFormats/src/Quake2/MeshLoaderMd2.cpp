/*********************************************************\
 *  File: MeshLoaderMd2.cpp                              *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Tools/Wrapper.h>
#include <PLMath/Vector2.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MorphTargetAni.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLDefaultFileFormats/Quake2/MeshLoaderMd2.h"


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
pl_implement_class(MeshLoaderMd2)


//[-------------------------------------------------------]
//[ Md2 format stuff                                      ]
//[-------------------------------------------------------]
struct MD2Header {
	int magic;				/**< 'magic' number (always 844121161) */
	int version;			/**< Version number of the file (always 8) */
	int skinWidth;			/**< Width of the model's skin */
	int skinHeight;			/**< Height of the model's skin */
	int frameSize;			/**< Size of each frame (in BYTEs) */
	int numSkins;			/**< Model's number of skins */
	int numVertices;		/**< Model's number of vertices */
	int numTexcoords;		/**< Model's number of texture coordinates (most likely, its not the same number as the vertices) */
	int numTriangles;		/**< Number of triangles that make up the model */
	int numGLCommands;		/**< Number of DWORDs (4 bytes) in the GLcommand list (which decide to render the model with tri strips, or fans) */
	int numFrames;			/**< Number of frames (of animation) that the model has */
	int offsetSkins;		/**< Offset in the file of the model, to where the skin information is */
	int offsetTexcoords;	/**< Offset in the file of the model, to where the texture coordinate information is */
	int offsetTriangles;	/**< Offset in the file of the model, to where the traingle information is */
	int offsetFrames;		/**< Offset in the file of the model, to where the first frame information is given */
	int offsetGLCommands;	/**< Offset in the file of the model, to where the GLcommand information is */
	int offsetEnd;			/**< Offset in the file of the model, to where the end of it is */
};

struct MD2Vertex {
	unsigned char vertex[3];		/**< Scaled version of the model's 'real' vertex coordinate */
	unsigned char lightNormalIndex;	/**< An index into the table of normals, kept by Quake 2 */
};

struct MD2TexCoord {
	short s;
	short t;
};

struct MD2Frame {
	float	   scale[3];		/**< The scale used by the model's 'fake' vertex structure */
	float	   translate[3];	/**< The translation used by the model's 'fake' vertex structure */
	char	   name[16];		/**< The name for the frame */
	MD2Vertex  vertices[1];		/**< An array of MD2_VERTEX structures */
};

struct MD2Triangle {
	short vertices[3];	/**< Indices into the vertex table */
	short texCoords[3];	/**< Indices into the texCoords table */
};


//[-------------------------------------------------------]
//[ Optimization                                          ]
//[-------------------------------------------------------]
namespace Md2 {
/**
*  @brief
*    For vertex optimizing
*/
class Vertex {
	public:
	float  fS, fT;	/**< Texture coordinate */
	uint32 nVertex;	/**< Vertex */
	uint32 nIndex;	/**< Used inside the vertex hash table */

	Vertex &operator =(const Vertex &cSource)
	{
		fS		= cSource.fS;
		fT		= cSource.fT;
		nVertex = cSource.nVertex;
		nIndex  = cSource.nIndex;
		return *this;
	}

	bool operator ==(const Vertex &cVertex) const
	{
		return fS == cVertex.fS && fT == cVertex.fT && nVertex == cVertex.nVertex && nIndex == cVertex.nIndex;
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
					if (cVer.fS      == cVertex.fS &&
						cVer.fT      == cVertex.fT &&
						cVer.nVertex == cVertex.nVertex) {
						// The vertex is already in the table!
						return &cVer;
					}
				}
			}

			// Add vertex to table
			Vertex &cVer = cSlot.Add();
			cVer.fS      = cVertex.fS;
			cVer.fT      = cVertex.fT;
			cVer.nVertex = cVertex.nVertex;
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
			return Math::Abs(static_cast<int>(cVertex.fS*30+cVertex.fT*20*m_nSlots+cVertex.nVertex*4))%m_nSlots;
		}


};
} // Md2


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderMd2::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderMd2::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Read file header
	MD2Header sHeader;
	cFile.Read(&sHeader, 1, sizeof(sHeader));
	if (sHeader.magic != 844121161)
		return false; // Error, wrong ID
	if (sHeader.version != 8)
		return false; // Error, wrong version

	// Load frames
	uint8 *pFrames = new uint8[sHeader.frameSize*sHeader.numFrames];
	cFile.Seek(sHeader.offsetFrames);
	cFile.Read(pFrames, 1, sHeader.frameSize*sHeader.numFrames);

	// Load GL commands
	uint8 *pGLCommands = new uint8[sHeader.numGLCommands*sizeof(long)];
	cFile.Seek(sHeader.offsetGLCommands);
	cFile.Read(pGLCommands, 1, sHeader.numGLCommands*sizeof(long));


// Setup mesh and fill it with the read data
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();


// Add material
	String sTexture = "Data/Textures/" + cFile.GetUrl().GetTitle() + ".dds";
	Material *pMaterial = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager().LoadResource(sTexture);
	cMesh.AddMaterial(pMaterial ? pMaterial : cMesh.GetRenderer()->GetRendererContext().GetMaterialManager().Create(sTexture));

// First, get total number of indices
	uint32 nNumOfIndices = 0;
	long *pCommand = reinterpret_cast<long*>(pGLCommands);
	while (*pCommand != 0) {
		uint32 nVertices = Math::Abs(static_cast<int>(*pCommand));
		nNumOfIndices += nVertices;
		pCommand += nVertices*3+1;
	}


// Create the index buffer and geometries
	// Allocate index buffer
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(sHeader.numVertices-1);
	pIndexBuffer->Allocate(nNumOfIndices, bStatic ? Usage::Static : Usage::Dynamic);

	// Fill index buffer
	Md2::VertexHashTable *pVHTable = new Md2::VertexHashTable(sHeader.numVertices*2);
	Array<Md2::Vertex*> lstVertex;
	lstVertex.Resize(sHeader.numVertices*2, false, false);
	Md2::Vertex sVertex;
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
	if (pIndexBuffer->Lock(Lock::WriteOnly)) {
		uint32 nIndex = 0;
		uint32 nStartVertex = 0;

		pCommand = reinterpret_cast<long*>(pGLCommands);
		while (*pCommand != 0) {
			uint32 nVertices = Math::Abs(static_cast<int>(*pCommand));
			Geometry &cGeometry = lstGeometries.Add();
			cGeometry.SetStartIndex(nStartVertex);
			cGeometry.SetIndexSize(nVertices);
			cGeometry.SetMaterial(0);
			if (nVertices == 3)
				cGeometry.SetPrimitiveType(Primitive::TriangleList);
			else
				cGeometry.SetPrimitiveType(*pCommand > 0 ? Primitive::TriangleStrip : Primitive::TriangleFan);
			pCommand++;

			// Get vertices
			for (uint32 i=0; i<nVertices; i++) {
				// Get texture coordinate 1
				float fS = *reinterpret_cast<float*>(pCommand);
				pCommand++;

				// Get texture coordinate 2
				float fT = *reinterpret_cast<float*>(pCommand);
				pCommand++;

				// Add vertex to list if not already in
				sVertex.fS      = fS;
				sVertex.fT      = fT;
				sVertex.nVertex = *pCommand;
				Md2::Vertex *pVertex = pVHTable->Add(sVertex);
				if (pVertex->nIndex >= lstVertex.GetNumOfElements())
					lstVertex.Add(pVertex);
				pIndexBuffer->SetData(nIndex++, pVertex->nIndex);
				pCommand++;
				nStartVertex++;
			}
		}

		// Unlock the index buffer
		pIndexBuffer->Unlock();
	}

// Create morph targets
	MD2Frame *pBaseMD2Frame = reinterpret_cast<MD2Frame*>(pFrames);
	for (uint32 nFrame=0; nFrame<static_cast<uint32>(sHeader.numFrames); nFrame++) {
		// Get frame pointer
		MD2Frame *pMD2Frame = reinterpret_cast<MD2Frame*>(pFrames + nFrame*sHeader.frameSize);

		// Add morph target
		MeshMorphTarget *pMorphTarget = cMesh.AddMorphTarget();
		pMorphTarget->SetName(pMD2Frame->name);
		VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
		pVertexBuffer->Allocate(lstVertex.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);

		// Add vertices
		if (pVertexBuffer->Lock(Lock::WriteOnly)) {
			// Make the data relative to the base frame?
			if (nFrame) {
				pMorphTarget->SetRelative(true);
				for (uint32 nVertex=0; nVertex<lstVertex.GetNumOfElements(); nVertex++) {
					const Md2::Vertex *pVertex   = lstVertex[nVertex];
					uint32             nVertexID = pVertex->nVertex;

					// Position
					float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::Position));
					pfVertex[Vector3::X] = (pMD2Frame->vertices[nVertexID].vertex[0]*pMD2Frame->scale[0] + pMD2Frame->translate[0]) -
										   (pBaseMD2Frame->vertices[nVertexID].vertex[0]*pBaseMD2Frame->scale[0] + pBaseMD2Frame->translate[0]);
					pfVertex[Vector3::Y] = (pMD2Frame->vertices[nVertexID].vertex[2]*pMD2Frame->scale[2] + pMD2Frame->translate[2]) -
										   (pBaseMD2Frame->vertices[nVertexID].vertex[2]*pBaseMD2Frame->scale[2] + pBaseMD2Frame->translate[2]);
					pfVertex[Vector3::Z] = (pMD2Frame->vertices[nVertexID].vertex[1]*pMD2Frame->scale[1] + pMD2Frame->translate[1]) -
										   (pBaseMD2Frame->vertices[nVertexID].vertex[1]*pBaseMD2Frame->scale[1] + pBaseMD2Frame->translate[1]);

					// Texture coordinate
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord));
					pfVertex[Vector2::X] = pVertex->fS;
					pfVertex[Vector2::Y] = pVertex->fT;
				}
			} else {
				for (uint32 nVertex=0; nVertex<lstVertex.GetNumOfElements(); nVertex++) {
					const Md2::Vertex *pVertex   = lstVertex[nVertex];
					uint32             nVertexID = pVertex->nVertex;

					// Position
					float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::Position));
					pfVertex[Vector3::X] = pMD2Frame->vertices[nVertexID].vertex[0]*pMD2Frame->scale[0] + pMD2Frame->translate[0];
					pfVertex[Vector3::Y] = pMD2Frame->vertices[nVertexID].vertex[2]*pMD2Frame->scale[2] + pMD2Frame->translate[2];
					pfVertex[Vector3::Z] = pMD2Frame->vertices[nVertexID].vertex[1]*pMD2Frame->scale[1] + pMD2Frame->translate[1];

					// Texture coordinate
					pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord));
					pfVertex[Vector2::X] = pVertex->fS;
					pfVertex[Vector2::Y] = pVertex->fT;
				}
			}

			// Unlock the vertex buffer
			pVertexBuffer->Unlock();
		}
	}

// Write animations (we use classic c-strings in here, but that's no problem and there can't be a buffer overflow)
	String sName, sLastName;
	uint32 nStart = 0, nEnd = 0;
	for (uint32 nFrame=0; nFrame<static_cast<uint32>(sHeader.numFrames); nFrame++) {
		// Get frame pointer
		MD2Frame *pMD2Frame = reinterpret_cast<MD2Frame*>(pFrames + nFrame*sHeader.frameSize);

		// Get frame name
		int j = static_cast<int>(Wrapper::GetStringLength(pMD2Frame->name) - 1);
		if (j > 15)
			j = 15; // No buffer overflow, please!
		while ((j >= 0 &&
				pMD2Frame->name[j] >= '0' &&
				pMD2Frame->name[j] <= '9') ||
				pMD2Frame->name[j] == '_') {
			j--;
		}
		j++;
		sName.Copy(pMD2Frame->name, j);
		if (!nFrame)
			sLastName = sName;

		// Compare frame names
		if (sName == sLastName && static_cast<int>(nFrame) < sHeader.numFrames-1) {
			// Add frame to animation
			nEnd = nFrame;
		} else { // Save last finished animation and start a new one
			if (static_cast<int>(nFrame) >= sHeader.numFrames-1)
				nEnd = nFrame;

			// Add morph target animation
			MorphTargetAni *pAni = new MorphTargetAni(sLastName, &cMesh.GetMorphTargetAnimationManager());

			// Set morph targets names influenced by this animation
			uint32 nFrames = nEnd-nStart;
			pAni->GetMorphTargets().Resize(nFrames);
			for (uint32 i=0; i<nFrames; i++)
				pAni->GetMorphTargets()[i].sName = cMesh.GetMorphTarget(nStart+i)->GetName();

			// Set frame keys
			Array<MorphTargetAni::FrameKeys> &lstFrameKeys = pAni->GetFrameKeys();
			lstFrameKeys.Resize(nFrames);
			for (uint32 i=0; i<lstFrameKeys.GetNumOfElements(); i++) {
				Array<float> &lstFrameKeysT = lstFrameKeys[i].lstFrameKeys;
				lstFrameKeysT.Resize(nFrames);
				for (uint32 i2=0; i2<lstFrameKeysT.GetNumOfElements(); i2++) {
					if (i == i2)
						lstFrameKeysT[i2] = 1.0f;
					else
						lstFrameKeysT[i2] = 0.0f;
				}
			}
			pAni->SetEndFrame(nFrames);
			pAni->SetFlags(AnimationInfo::Loop);
			pAni->SetSpeed(5.0f);
			pAni->SetType(1);

			// Start new animation
			nStart = nEnd = nFrame;
			sLastName = sName;
		}
	}


// Destroy temp data
	delete [] pFrames;
	delete [] pGLCommands;
	delete pVHTable;

	// Done
	return true;
}

bool MeshLoaderMd2::Save(Mesh &cMesh, File &cFile)
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
MeshLoaderMd2::MeshLoaderMd2()
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderMd2::~MeshLoaderMd2()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
