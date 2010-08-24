/*********************************************************\
 *  File: MeshCreatorSphere.cpp                          *
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
#include <PLMath/Vector2.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "PLMesh/Geometry.h"
#include "PLMesh/MeshManager.h"
#include "PLMesh/MeshLODLevel.h"
#include "PLMesh/MeshMorphTarget.h"
#include "PLMesh/Creator/MeshCreatorSphere.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
namespace PLMesh {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(MeshCreatorSphere)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshCreatorSphere::MeshCreatorSphere() :
	Radius(this),
	Detail(this),
	Offset(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshCreatorSphere::~MeshCreatorSphere()
{
}


//[-------------------------------------------------------]
//[ Private virtual MeshCreator functions                 ]
//[-------------------------------------------------------]
Mesh *MeshCreatorSphere::Create(Mesh &cMesh, uint32 nLODLevel, bool bStatic) const
{
	// Call base implementation
	MeshCreator::Create(cMesh, nLODLevel, bStatic);

	// Check parameter
	float  fRadius = Radius;
	uint32 nDetail = Detail;
	if (fRadius < 0)
		fRadius = -fRadius;
	if (nDetail < 4 || fRadius <= 0)
		return &cMesh; // Error!

	// Get morph target
	MeshMorphTarget *pMorphTarget = cMesh.GetMorphTarget(0);
	if (pMorphTarget && pMorphTarget->GetVertexBuffer()) {
		// If this is not done, the sphere may be 'opened'
		if (Math::Floor(nDetail/2.0f) != Math::Ceil(nDetail/2.0f))
			nDetail++;

		// Allocate vertex buffer
		VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		if (TexCoords)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
		if (Normals)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
		pVertexBuffer->Allocate(nDetail*(nDetail+1), bStatic ? Usage::Static : Usage::Dynamic);

		// Get LOD level
		MeshLODLevel *pLODLevel = cMesh.GetLODLevel(nLODLevel);
		if (pLODLevel && pLODLevel->GetIndexBuffer()) {
			// Allocate index buffer
			IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
			pIndexBuffer->SetElementTypeByMaximumIndex(pVertexBuffer->GetNumOfElements()-1);
			pIndexBuffer->Allocate(pVertexBuffer->GetNumOfElements(), bStatic ? Usage::Static : Usage::Dynamic);

			// Setup vertices & geometry
			if (pVertexBuffer->Lock(Lock::WriteOnly)) {
				if (pIndexBuffer->Lock(Lock::WriteOnly)) {
					// Get offset
					const Vector3 &vOffset = Offset.Get();

					Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
					uint32 nIndex  = 0;
					uint32 nVertex = 0;
					Vector3 e, p;
					for (uint32 j=0; j<nDetail/2; j++) {
						// Create new geometry
						Geometry &cGeometry = lstGeometries.Add();

						// Setup the new geometry
						cGeometry.SetPrimitiveType(Primitive::TriangleStrip);
						cGeometry.SetStartIndex(nVertex);
						cGeometry.SetIndexSize((nDetail+1)*2);

						double dTheta1 = j*Math::Pi2/nDetail - Math::PiHalf;
						double dTheta2 = (j+1)*Math::Pi2/nDetail - Math::PiHalf;
						for (uint32 i=0; i<=nDetail; i++) {
							double dTheta3 = i*Math::Pi2/nDetail;

							float *pfVertex;
							if (Order) {
								e.x = float(Math::Cos(dTheta2)*Math::Cos(dTheta3));
								e.y = (float)Math::Sin(dTheta2);
								e.z = float(Math::Cos(dTheta2)*Math::Sin(dTheta3));
								p.x = fRadius*e.x;
								p.y = fRadius*e.y;
								p.z = fRadius*e.z;
								if (TexCoords) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord);
									pfVertex[Vector2::X] = (float)i/nDetail;
									pfVertex[Vector2::Y] = (float)2*(j+1)/nDetail;
								}
								if (Normals) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
									pfVertex[Vector3::X] = e.x;
									pfVertex[Vector3::Y] = e.y;
									pfVertex[Vector3::Z] = e.z;
								}
								pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + p.x;
								pfVertex[Vector3::Y] = vOffset.y + p.y;
								pfVertex[Vector3::Z] = vOffset.z + p.z;
								pIndexBuffer->SetData(nIndex++, nVertex);
								nVertex++;

								e.x = float(Math::Cos(dTheta1)*Math::Cos(dTheta3));
								e.y = (float)Math::Sin(dTheta1);
								e.z = float(Math::Cos(dTheta1)*Math::Sin(dTheta3));
								p.x = fRadius*e.x;
								p.y = fRadius*e.y;
								p.z = fRadius*e.z;
								if (TexCoords) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord);
									pfVertex[Vector2::X] = (float)i/nDetail;
									pfVertex[Vector2::Y] = (float)2*j/nDetail;
								}
								if (Normals) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
									pfVertex[Vector3::X] = e.x;
									pfVertex[Vector3::Y] = e.y;
									pfVertex[Vector3::Z] = e.z;
								}
								pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + p.x;
								pfVertex[Vector3::Y] = vOffset.y + p.y;
								pfVertex[Vector3::Z] = vOffset.z + p.z;
								pIndexBuffer->SetData(nIndex++, nVertex);
								nVertex++;
							} else {
								e.x = float(Math::Cos(dTheta1)*Math::Cos(dTheta3));
								e.y = (float)Math::Sin(dTheta1);
								e.z = float(Math::Cos(dTheta1)*Math::Sin(dTheta3));
								p.x = fRadius*e.x;
								p.y = fRadius*e.y;
								p.z = fRadius*e.z;
								if (TexCoords) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord);
									pfVertex[Vector2::X] = (float)i/nDetail;
									pfVertex[Vector2::Y] = (float)2*j/nDetail;
								}
								if (Normals) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
									pfVertex[Vector3::X] = e.x;
									pfVertex[Vector3::Y] = e.y;
									pfVertex[Vector3::Z] = e.z;
								}
								pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + p.x;
								pfVertex[Vector3::Y] = vOffset.y + p.y;
								pfVertex[Vector3::Z] = vOffset.z + p.z;
								pIndexBuffer->SetData(nIndex++, nVertex);
								nVertex++;

								e.x = float(Math::Cos(dTheta2)*Math::Cos(dTheta3));
								e.y = (float)Math::Sin(dTheta2);
								e.z = float(Math::Cos(dTheta2)*Math::Sin(dTheta3));
								p.x = fRadius*e.x;
								p.y = fRadius*e.y;
								p.z = fRadius*e.z;
								if (TexCoords) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord);
									pfVertex[Vector2::X] = (float)i/nDetail;
									pfVertex[Vector2::Y] = (float)2*(j+1)/nDetail;
								}
								if (Normals) {
									pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
									pfVertex[Vector3::X] = e.x;
									pfVertex[Vector3::Y] = e.y;
									pfVertex[Vector3::Z] = e.z;
								}
								pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + p.x;
								pfVertex[Vector3::Y] = vOffset.y + p.y;
								pfVertex[Vector3::Z] = vOffset.z + p.z;
								pIndexBuffer->SetData(nIndex++, nVertex);
								nVertex++;
							}
						}
					}

					// Unlock the index buffer
					pIndexBuffer->Unlock();
				}

				// Unlock the vertex buffer
				pVertexBuffer->Unlock();
			}
		}
	}

	// Return the created mesh
	return &cMesh;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
