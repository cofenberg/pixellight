/*********************************************************\
 *  File: MeshCreatorCylinder.cpp                        *
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
#include "PLMesh/Creator/MeshCreatorCylinder.h"


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
pl_implement_class(MeshCreatorCylinder)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshCreatorCylinder::MeshCreatorCylinder() :
	BaseRadius(this),
	TopRadius(this),
	Height(this),
	Slices(this),
	Offset(this),
	Closed(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshCreatorCylinder::~MeshCreatorCylinder()
{
}


//[-------------------------------------------------------]
//[ Private virtual MeshCreator functions                 ]
//[-------------------------------------------------------]
Mesh *MeshCreatorCylinder::Create(Mesh &cMesh, uint32 nLODLevel, bool bStatic) const
{
	// Call base implementation
	MeshCreator::Create(cMesh, nLODLevel, bStatic);

	// Get morph target
	MeshMorphTarget *pMorphTarget = cMesh.GetMorphTarget(0);
	if (pMorphTarget && pMorphTarget->GetVertexBuffer()) {
		// Calculate sizes
		uint32 nNumVertices		= Slices*2 + 2;							// Two points for each slice and the two center-points for the caps
		uint32 nNumIndicesCone	= Slices*2 + 2;							// Every point once and the two start points again to close the cone
		uint32 nNumIndicesCap	= Slices   + 2;							// Center point, every point on the cap once and the start point again
		uint32 nNumIndices		= nNumIndicesCone + 2*nNumIndicesCap;	// Overall size of index buffer

		// Allocate vertex buffer
		VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		if (TexCoords)
			pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
		pVertexBuffer->Allocate(nNumVertices, bStatic ? Usage::Static : Usage::Dynamic);

		// Get LOD level
		MeshLODLevel *pLODLevel = cMesh.GetLODLevel(nLODLevel);
		if (pLODLevel && pLODLevel->GetIndexBuffer()) {
			// Allocate index buffer
			IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
			pIndexBuffer->SetElementTypeByMaximumIndex(nNumIndices-1);
			pIndexBuffer->Allocate(nNumIndices, bStatic ? Usage::Static : Usage::Dynamic);

			// Create and setup geometry for the cone
			Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
			Geometry &cGeometry = lstGeometries.Add();
			cGeometry.SetPrimitiveType(Primitive::TriangleStrip);
			cGeometry.SetStartIndex(0);
			cGeometry.SetIndexSize(nNumIndicesCone);

			// Create and setup geometry for cap #1
			if (Closed && BaseRadius > 0.0f) {
				Geometry &cGeometry2 = lstGeometries.Add();
				cGeometry2.SetPrimitiveType(Primitive::TriangleFan);
				cGeometry2.SetStartIndex(nNumIndicesCone);
				cGeometry2.SetIndexSize(nNumIndicesCap);
			}

			// Create and setup geometry for cap #2
			if (Closed && TopRadius > 0.0f) {
				Geometry &cGeometry3 = lstGeometries.Add();
				cGeometry3.SetPrimitiveType(Primitive::TriangleFan);
				cGeometry3.SetStartIndex(nNumIndicesCone + nNumIndicesCap);
				cGeometry3.SetIndexSize(nNumIndicesCap);
			}

			// Setup vertices, indices & geometry
			if (pVertexBuffer->Lock(Lock::WriteOnly)) {
				if (pIndexBuffer->Lock(Lock::WriteOnly)) {
					// Get offset
					const Vector3 &vOffset = Offset.Get();

					// Add center point of cap #1
					float *pfVertex = (float*)pVertexBuffer->GetData(nNumVertices-2, VertexBuffer::Position);
					pfVertex[Vector3::X] = vOffset.x + 0.0f;
					pfVertex[Vector3::Y] = vOffset.y - Height/2;
					pfVertex[Vector3::Z] = vOffset.z + 0.0f;

					// Add center point of cap #2
					pfVertex = (float*)pVertexBuffer->GetData(nNumVertices-1, VertexBuffer::Position);
					pfVertex[Vector3::X] = vOffset.x + 0.0f;
					pfVertex[Vector3::Y] = vOffset.y + Height/2;
					pfVertex[Vector3::Z] = vOffset.z + 0.0f;

					// Create cone
					uint32 nIndex = 0;
					uint32 nVertex = 0;
					bool   bParity = false;
					float  fTheta  = 0.0f;
					float  fAngle = (float)6.28f/Slices;
					for (uint32 i=0, j=0; i<Slices; i++, j+=2, fTheta+=fAngle) {
						// V0
						float fX = BaseRadius*Math::Sin(fTheta);
						float fY = BaseRadius*Math::Cos(fTheta);
						if (TexCoords) {
							pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord);
							if (bParity) {
								pfVertex[Vector2::X] = 0.0f;
								pfVertex[Vector2::Y] = 1.0f;
							} else {
								pfVertex[Vector2::X] = 1.0f;
								pfVertex[Vector2::Y] = 1.0f;
							}
						}
						pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
						pfVertex[Vector3::X] = vOffset.x + fX;
						pfVertex[Vector3::Y] = vOffset.y - Height/2;
						pfVertex[Vector3::Z] = vOffset.z + fY;
						pIndexBuffer->SetData(Order ? nIndex : nIndex+1, j);
						nVertex++;

						// V1
						fX = TopRadius*Math::Sin(fTheta);
						fY = TopRadius*Math::Cos(fTheta);
						if (TexCoords) {
							pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord);
							if (bParity) {
								pfVertex[Vector2::X] = 0.0f;
								pfVertex[Vector2::Y] = 0.0f;
							} else {
								pfVertex[Vector2::X] = 1.0f;
								pfVertex[Vector2::Y] = 0.0f;
							}
						}
						pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
						pfVertex[Vector3::X] = vOffset.x + fX;
						pfVertex[Vector3::Y] = vOffset.y + Height/2;
						pfVertex[Vector3::Z] = vOffset.z + fY;
						pIndexBuffer->SetData(Order ? nIndex+1 : nIndex, j+1);
						nIndex += 2;
						nVertex++;

						// Add index for cap #1
						pIndexBuffer->SetData(nNumIndicesCone + 1 + i, nNumVertices-4 - i*2);

						// Add index for cap #2
						pIndexBuffer->SetData(nNumIndicesCone + nNumIndicesCap + 1 + i, i*2 + 1);

						// Toggle parity
						bParity = !bParity;
					}

					// Add first and last index for cap #1
					pIndexBuffer->SetData(nNumIndicesCone, nNumVertices-2);
					pIndexBuffer->SetData(nNumIndicesCone + nNumIndicesCap - 1, nNumVertices - 4);

					// Add first and last index for cap #2
					pIndexBuffer->SetData(nNumIndicesCone + nNumIndicesCap, nNumVertices-1);
					pIndexBuffer->SetData(nNumIndicesCone + nNumIndicesCap + nNumIndicesCap - 1, 1);

					// Add last two triangles that close the cycle
					pIndexBuffer->SetData(Order ? nIndex : nIndex+1, 0);
					pIndexBuffer->SetData(Order ? nIndex+1 : nIndex, 1);

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
