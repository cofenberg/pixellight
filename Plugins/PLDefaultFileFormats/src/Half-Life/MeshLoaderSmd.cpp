/*********************************************************\
 *  File: MeshLoaderSmd.cpp                              *
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
#include <PLCore/String/Tokenizer.h>
#include <PLMath/EulerAngles.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshManager.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include <PLMesh/SkeletonManager.h>
#include "PLDefaultFileFormats/Half-Life/MeshLoaderSmd.h"


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
pl_implement_class(MeshLoaderSmd)


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
namespace Smd {
/**
*  @brief
*    Face
*/
struct Face {
	int    nMaterial;	/**< Material ID, -1 if there's no material set */
	uint32 nVertex[3];	/**< Vertex indices */
};

/**
*  @brief
*    Node
*/
struct Node {
	String sName;	/**< Node name */
	int   nParent;	/**< Node parent node ID, -1 if there's no parent */
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
	uint32 nBone;			/**< Bone ID */
	float  fX, fY, fZ;		/**< Coordinate */
	float  fNX, fNY, fNZ;	/**< Normal */
	float  fS, fT;			/**< Texture coordinate */
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
					if (cVer.nBone == cVertex.nBone &&
						cVer.fX	   == cVertex.fX    &&
						cVer.fY	   == cVertex.fY    &&
						cVer.fZ	   == cVertex.fZ    &&
						cVer.fNX   == cVertex.fNX   &&
						cVer.fNY   == cVertex.fNY   &&
						cVer.fNZ   == cVertex.fNZ   &&
						cVer.fS	   == cVertex.fS    &&
						cVer.fT	   == cVertex.fT) {
						// The vertex is already in the table!
						return &cVer;
					}
				}
			}

			// Add vertex to table
			Vertex &cVer = cSlot.Add();
			cVer.nBone  = cVertex.nBone;
			cVer.fX     = cVertex.fX;
			cVer.fY     = cVertex.fY;
			cVer.fZ     = cVertex.fZ;
			cVer.fNX    = cVertex.fNX;
			cVer.fNY    = cVertex.fNY;
			cVer.fNZ    = cVertex.fNZ;
			cVer.fS     = cVertex.fS;
			cVer.fT     = cVertex.fT;
			cVer.nIndex = m_nVertices++;

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
								cVertex.fS*123+cVertex.fT*42+cVertex.nBone))%m_nSlots;
		}


};
} // Smd


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool MeshLoaderSmd::Load(Mesh &cMesh, File &cFile)
{
	return LoadParams(cMesh, cFile, true);
}

bool MeshLoaderSmd::LoadParams(Mesh &cMesh, File &cFile, bool bStatic)
{
	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n()[]=,;{}\"");
	cTokenizer.SetSingleChars(':');
	cTokenizer.SetCaseSensitive(true);

	// First at all, check the version number
	if (cTokenizer.GetNextToken() != "version" || cTokenizer.GetNextToken().GetInt() != 1) {
		PL_LOG(Error, "Invalid version number!")
		cTokenizer.Stop();

		// Error!
		return false;
	}

	Array<Smd::Node*> lstNodes;
	Array<Smd::Face*> lstFaces;
	Array<Smd::Vertex*> lstVertices;
	Array<String> lstMaterials;

	// Get the skeleton manager
	SkeletonManager &cSkeletonManager = cMesh.GetMeshManager()->GetSkeletonManager();

	// Read file
	while (cTokenizer.GetNextToken().GetLength()) {
		// nodes
		if (cTokenizer.CompareToken("nodes")) {
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end")) {
				Smd::Node *pNode = new Smd::Node;

				// Ignore the node index

				// Get name
				if (cTokenizer.GetNextToken() == '\"') {
					pNode->sName = cTokenizer.GetNextToken();
					cTokenizer.GetNextToken();
				} else {
					pNode->sName = cTokenizer.GetToken();
				}

				// Get parent
				pNode->nParent = cTokenizer.GetNextToken().GetInt();

				// Add the node to the node list
				lstNodes.Add(pNode);
			}

		// skeleton
		} else if (cTokenizer.CompareToken("skeleton")) {
			// Change name if this is the base skeleton
			// [TODO] Try to avoid skeleton name conflicts...
			String sName;
		//	if (!m_pMesh->GetSkeleton()) {
		//		sName = cMesh.GetName() + "_" + sSkeleton.sName;
		//	} else 
			if (cSkeletonManager.GetByName(cMesh.GetName())) {
				uint32 i = 0;
				do {
					sName = cMesh.GetName() + '_' + static_cast<int>(i);
					i++;
				} while (cSkeletonManager.GetByName(sName));
			} else {
				sName = cMesh.GetName();
			}

			// Create skeleton
			Skeleton *pSkeleton = cSkeletonManager.Create(sName);

			// Add this skeleton to the skeleton list of the mesh
			SkeletonHandler *pSkeletonHandler = new SkeletonHandler();
			pSkeletonHandler->SetResource(pSkeleton);
			cMesh.GetSkeletonHandlers().Add(pSkeletonHandler);

			// Create nodes
			for (uint32 i=0; i<lstNodes.GetNumOfElements(); i++) {
				Smd::Node *pNode = lstNodes[i];
				Joint *pJoint = pSkeleton->Create(pNode->sName);
				pJoint->SetID(i);
				pJoint->SetParent(pNode->nParent);
			}

			// Ignore the time of the base frame
			cTokenizer.GetNextToken(); // time
			cTokenizer.GetNextToken(); // time index

			// Parse joint base translation/rotation (we only read the base frame at time 0!)
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end") && !cTokenizer.CompareToken("time")) {
				uint32 nNode = cTokenizer.GetToken().GetInt();
				Vector3 vTranslation(cTokenizer.GetNextToken().GetFloat(),
									 cTokenizer.GetNextToken().GetFloat(),
									 cTokenizer.GetNextToken().GetFloat());
				float roll  = cTokenizer.GetNextToken().GetFloat();
				float pitch = cTokenizer.GetNextToken().GetFloat();
				float yaw   = cTokenizer.GetNextToken().GetFloat();

				Joint *pJoint = pSkeleton->GetByIndex(nNode);
				if (pJoint) {
					pJoint->SetTranslation(vTranslation);
					// [TODO] The result is wrong...
					Quaternion qRotation;
					EulerAngles::ToQuaternion(static_cast<float>(roll*Math::RadToDeg), static_cast<float>(pitch*Math::RadToDeg), static_cast<float>(yaw*Math::RadToDeg), qRotation);
					qRotation.Invert();
					pJoint->SetRotation(qRotation);
				}
			}

			// Update skeleton
			pSkeleton->UpdateJointInformation();

			// Loop through all root joints
			for (uint32 i=0; i<pSkeleton->GetRootJoints().GetNumOfElements(); i++) {
				Joint *pJoint = pSkeleton->GetByIndex(pSkeleton->GetRootJoints()[i]);
				RecCalculateStates(*pSkeleton, *pJoint, nullptr);
			}

		// triangles
		} else if (cTokenizer.CompareToken("triangles")) {
			// Read all faces
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end")) {
				Smd::Face *pFace = new Smd::Face;

				// Material
				pFace->nMaterial = -1;
				String sMaterial = cTokenizer.GetToken();
				for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++) {
					if (sMaterial == lstMaterials[i]) {
						pFace->nMaterial = i;
						break;
					}
				}
				if (pFace->nMaterial < 0) {
					pFace->nMaterial = lstMaterials.GetNumOfElements();
					lstMaterials.Add(sMaterial);
				}

				// Read the face vertices
				for (uint32 nVertex=0; nVertex<3; nVertex++) {
					Smd::Vertex *pVertex = new Smd::Vertex;

					pVertex->nBone = cTokenizer.GetNextToken().GetInt();
					pVertex->fX    = cTokenizer.GetNextToken().GetFloat();
					pVertex->fY    = cTokenizer.GetNextToken().GetFloat();
					pVertex->fZ    = cTokenizer.GetNextToken().GetFloat();
					pVertex->fNX   = cTokenizer.GetNextToken().GetFloat();
					pVertex->fNY   = cTokenizer.GetNextToken().GetFloat();
					pVertex->fNZ   = cTokenizer.GetNextToken().GetFloat();
					pVertex->fS    = cTokenizer.GetNextToken().GetFloat();
					pVertex->fT    = 1.0f - cTokenizer.GetNextToken().GetFloat();

					// Add vertex to temp list
					pFace->nVertex[nVertex] = lstVertices.GetNumOfElements();
					lstVertices.Add(pVertex);
				}

				// Add face to temp list
				lstFaces.Add(pFace);
			}
		}
	}
	cTokenizer.Stop();

	// Optimize read data
	Array<Smd::Vertex*> lstVertex;
	lstVertex.Resize(lstFaces.GetNumOfElements()*3, false, false);
	Smd::VertexHashTable *pVHTable = new Smd::VertexHashTable(lstFaces.GetNumOfElements()*3);
	Smd::Vertex cVertex;
	for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++) {
		Smd::Face &cFace = *lstFaces[i];
		for (uint32 nVertex=0; nVertex<3; nVertex++) {
			{ // Setup face vertex
				const Smd::Vertex &cFaceVertex = *lstVertices[cFace.nVertex[nVertex]];
				cVertex.nBone = cFaceVertex.nBone;
				cVertex.fX    = cFaceVertex.fX;
				cVertex.fY    = cFaceVertex.fY;
				cVertex.fZ    = cFaceVertex.fZ;
				cVertex.fNX   = cFaceVertex.fNX;
				cVertex.fNY   = cFaceVertex.fNY;
				cVertex.fNZ   = cFaceVertex.fNZ;
				cVertex.fS    = cFaceVertex.fS;
				cVertex.fT    = cFaceVertex.fT;
			}

			// Add vertex to list if not already in
			Smd::Vertex *pVertex = pVHTable->Add(cVertex);
			if (pVertex->nIndex >= lstVertex.GetNumOfElements())
				lstVertex.Add(pVertex);

			// Update face vertex ID
			cFace.nVertex[nVertex] = pVertex->nIndex;
		}
	}

	// Create the mesh and fill it with the read data
	MeshMorphTarget *pMorphTarget = cMesh.AddMorphTarget();
	MeshLODLevel *pLODLevel = cMesh.AddLODLevel();
	pLODLevel->CreateGeometries();
	pLODLevel->CreateIndexBuffer();
	VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
	pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
	pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
	pVertexBuffer->Allocate(lstVertex.GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);

	// Get the material manager
	MaterialManager &cMaterialManager = cMesh.GetRenderer()->GetRendererContext().GetMaterialManager();

	// Go through all the materials
	for (uint32 i=0; i<lstMaterials.GetNumOfElements(); i++) {
		const String &sMaterial = lstMaterials[i];
		Material *pMaterial = cMaterialManager.LoadResource(sMaterial);
		cMesh.AddMaterial(pMaterial ? pMaterial : cMaterialManager.Create(sMaterial));
	}

	// Allocate index buffer
	IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
	pIndexBuffer->SetElementTypeByMaximumIndex(pVertexBuffer->GetNumOfElements()-1);
	pIndexBuffer->Allocate(lstFaces.GetNumOfElements()*3, bStatic ? Usage::Static : Usage::Dynamic);

	// Fill the buffers
	Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
	if (pVertexBuffer->Lock(Lock::WriteOnly)) {
		if (pIndexBuffer->Lock(Lock::WriteOnly)) {
			// Fill vertex buffer
			uint32 nStartVertex = 0;
			uint32 nVertices    = 0;
			uint32 nIndex       = 0;

			// Go through all the materials
			for (uint32 nMat=0; nMat<lstMaterials.GetNumOfElements(); nMat++) {
				// Go through all the faces
				for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++) {
					// Get the face
					const Smd::Face &cFace = *lstFaces[i];

					// Check material
					if (cFace.nMaterial == static_cast<int>(nMat)) {
						// V0
						uint32 nID = cFace.nVertex[2];
						const Smd::Vertex *pVertex = lstVertex[nID];
						float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Position));
						pfVertex[Vector3::X] = pVertex->fX;
						pfVertex[Vector3::Y] = pVertex->fY;
						pfVertex[Vector3::Z] = pVertex->fZ;
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Normal));
						pfVertex[Vector3::X] = pVertex->fNX;
						pfVertex[Vector3::Y] = pVertex->fNY;
						pfVertex[Vector3::Z] = pVertex->fNZ;
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::TexCoord));
						pfVertex[Vector2::X] = pVertex->fS;
						pfVertex[Vector2::Y] = pVertex->fT;
						pIndexBuffer->SetData(nIndex++,  nID);

						// V1
						nID = cFace.nVertex[1];
						pVertex = lstVertex[nID];
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Position));
						pfVertex[Vector3::X] = pVertex->fX;
						pfVertex[Vector3::Y] = pVertex->fY;
						pfVertex[Vector3::Z] = pVertex->fZ;
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Normal));
						pfVertex[Vector3::X] = pVertex->fNX;
						pfVertex[Vector3::Y] = pVertex->fNY;
						pfVertex[Vector3::Z] = pVertex->fNZ;
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::TexCoord));
						pfVertex[Vector2::X] = pVertex->fS;
						pfVertex[Vector2::Y] = pVertex->fT;
						pIndexBuffer->SetData(nIndex++,  nID);

						// V2
						nID = cFace.nVertex[0];
						pVertex = lstVertex[nID];
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Position));
						pfVertex[Vector3::X] = pVertex->fX;
						pfVertex[Vector3::Y] = pVertex->fY;
						pfVertex[Vector3::Z] = pVertex->fZ;
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::Normal));
						pfVertex[Vector3::X] = pVertex->fNX;
						pfVertex[Vector3::Y] = pVertex->fNY;
						pfVertex[Vector3::Z] = pVertex->fNZ;
						pfVertex = static_cast<float*>(pVertexBuffer->GetData(nID, VertexBuffer::TexCoord));
						pfVertex[Vector2::X] = pVertex->fS;
						pfVertex[Vector2::Y] = pVertex->fT;
						pIndexBuffer->SetData(nIndex++,  nID);
						nVertices += 3;
					}

					// Setup the geometry
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
			}

			// Unlock the index buffer
			pIndexBuffer->Unlock();
		}

		// Unlock the vertex buffer
		pVertexBuffer->Unlock();
	}

	// Add weights
	if (cMesh.GetSkeletonHandlers().GetNumOfElements()) {
		Skeleton *pSkeleton = cMesh.GetSkeletonHandlers()[0]->GetResource();
		if (pSkeleton) {
			Array<JointState> lstJointStates;
			uint32 nVertices = lstVertex.GetNumOfElements();
			cMesh.GetWeights().Resize(nVertices);
			Array<VertexWeights> &lstVW = cMesh.GetVertexWeights();
			lstVW.Resize(nVertices);
			for (uint32 i=0; i<nVertices; i++) {
				Smd::Vertex *pV = lstVertex[i];

				// Setup weight
				Weight &cWeight = cMesh.GetWeights()[i];
				cWeight.SetJoint(pV->nBone);
				cWeight.SetBias(1.0f);

				// Setup vertex weight
				lstVW[i].GetWeights().Resize(1);
				lstVW[i].GetWeights()[0] = i;
			}
		}
	}

	// Destroy temp data
	for (uint32 i=0; i<lstVertices.GetNumOfElements(); i++)
		delete lstVertices[i];
	lstVertices.Clear();
	lstMaterials.Clear();
	for (uint32 i=0; i<lstFaces.GetNumOfElements(); i++)
		delete lstFaces[i];
	lstFaces.Clear();
	lstVertex.Clear();
	delete pVHTable;
	for (uint32 i=0; i<lstNodes.GetNumOfElements(); i++)
		delete lstNodes[i];
	lstNodes.Clear();

	// Done
	return true;
}

bool MeshLoaderSmd::Save(Mesh &cMesh, File &cFile)
{
	// [TODO] Implement me!
	return false; // Error!
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
MeshLoaderSmd::MeshLoaderSmd()
{
}

/**
*  @brief
*    Destructor
*/
MeshLoaderSmd::~MeshLoaderSmd()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Recursive joint state calculations
*/
void MeshLoaderSmd::RecCalculateStates(const Skeleton &cSkeleton, Joint &cJoint, Joint *pParentJoint) const
{
	// Check and calculate states of this joint
	if (pParentJoint) {
		// Transform relative state with the absolute state of the parent
		cJoint.SetTranslationAbsolute(pParentJoint->GetRotationAbsolute()*cJoint.GetTranslation()+
									  pParentJoint->GetTranslationAbsolute());
		cJoint.SetRotationAbsolute(cJoint.GetRotation()*pParentJoint->GetRotationAbsolute());
	} else {
		// If there's no parent the absolute states are equal to the relative states
		cJoint.SetTranslationAbsolute(cJoint.GetTranslation());
		cJoint.SetRotationAbsolute(cJoint.GetRotation());
	}

	// Set joint space data
	Quaternion qQ = cJoint.GetRotationAbsolute();
	qQ.Invert();
	cJoint.SetTranslationJointSpace(qQ*(-cJoint.GetTranslationAbsolute()));
	cJoint.SetRotationJointSpace(qQ);

	// Transform children
	for (uint32 i=0; i<cJoint.GetChildren().GetNumOfElements(); i++)
		RecCalculateStates(cSkeleton, *cSkeleton.GetByIndex(cJoint.GetChildren()[i]), &cJoint);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
