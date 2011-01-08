/*********************************************************\
 *  File: MeshCreatorPartialDisk.cpp                     *
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


// [TODO] Calculate texture coordinates for the 'Fill' flag


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "PLMesh/Geometry.h"
#include "PLMesh/MeshManager.h"
#include "PLMesh/MeshLODLevel.h"
#include "PLMesh/MeshMorphTarget.h"
#include "PLMesh/Creator/MeshCreatorPartialDisk.h"


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
pl_implement_class(MeshCreatorPartialDisk)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
MeshCreatorPartialDisk::MeshCreatorPartialDisk() :
	InnerRadius(this),
	OuterRadius(this),
	Slices(this),
	Loops(this),
	StartAngle(this),
	SweepAngle(this),
	Offset(this)
{
}

/**
*  @brief
*    Destructor
*/
MeshCreatorPartialDisk::~MeshCreatorPartialDisk()
{
}


//[-------------------------------------------------------]
//[ Private virtual MeshCreator functions                 ]
//[-------------------------------------------------------]
Mesh *MeshCreatorPartialDisk::Create(Mesh &cMesh, uint32 nLODLevel, bool bStatic) const
{
	// Call base implementation
	MeshCreator::Create(cMesh, nLODLevel, bStatic);

	// Get morph target
	MeshMorphTarget *pMorphTarget = cMesh.GetMorphTarget(0);
	if (pMorphTarget && pMorphTarget->GetVertexBuffer()) {
		// Setup vertex buffer
		VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
		pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
		if (DrawStyle == Fill) {
			if (TexCoords)
				pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
			if (Normals)
				pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
		}

		// Get LOD level
		MeshLODLevel *pLODLevel = cMesh.GetLODLevel(nLODLevel);
		if (pLODLevel && pLODLevel->GetIndexBuffer()) {
			IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();

			// Draw
			switch (DrawStyle) {
				case Fill:
				{
					// Allocate vertex and index buffer
					uint32 nVertices = Loops*(Slices+1)*2;
					pVertexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);
					pIndexBuffer->SetElementTypeByMaximumIndex(nVertices-1);
					pIndexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);

					// Setup vertices & geometry
					if (pVertexBuffer->Lock(Lock::WriteOnly)) {
						if (pIndexBuffer->Lock(Lock::WriteOnly)) {
							float fDeltaRadius = (OuterRadius - InnerRadius)/Loops;
							float fDeltaAngle  = (float)(Math::DegToRad*(SweepAngle/Slices));
							float fRadius      = InnerRadius;

							// Get offset
							const Vector3 &vOffset = Offset.Get();

							// Setup vertex and index buffer
							Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
							uint32 nVertex = 0;
							for (uint32 nLoop=0; nLoop<Loops; nLoop++) {
								float fAngle = (float)(Math::DegToRad*StartAngle);

								// Create and setup the geometry
								Geometry &cGeometry = lstGeometries.Add();
								cGeometry.SetPrimitiveType(Primitive::TriangleStrip);
								cGeometry.SetStartIndex(nVertex);
								cGeometry.SetIndexSize((Slices+1)*2);

								for (uint32 nSlice=0; nSlice<=Slices; nSlice++) {
									if (Order) {
										// Set vertex 0
										float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
										pfVertex[Vector3::X] = vOffset.x + fRadius*Math::Sin(fAngle);
										pfVertex[Vector3::Y] = vOffset.y + fRadius*Math::Cos(fAngle);
										pfVertex[Vector3::Z] = vOffset.z;
										if (Normals) {
											pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
											pfVertex[Vector3::X] =  0.0f;
											pfVertex[Vector3::Y] =  0.0f;
											pfVertex[Vector3::Z] = -1.0f;
										}

										// Set index 0
										pIndexBuffer->SetData(nVertex, nVertex);
										nVertex++;

										// Set vertex 1
										pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
										pfVertex[Vector3::X] = vOffset.x + (fRadius + fDeltaRadius)*Math::Sin(fAngle);
										pfVertex[Vector3::Y] = vOffset.y + (fRadius + fDeltaRadius)*Math::Cos(fAngle);
										pfVertex[Vector3::Z] = vOffset.z;
										if (Normals) {
											pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
											pfVertex[Vector3::X] =  0.0f;
											pfVertex[Vector3::Y] =  0.0f;
											pfVertex[Vector3::Z] = -1.0f;
										}

										// Set index 1
										pIndexBuffer->SetData(nVertex, nVertex);
										nVertex++;
									} else {
										// Set vertex 0
										float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
										pfVertex[Vector3::X] = vOffset.x + (fRadius + fDeltaRadius)*Math::Sin(fAngle);
										pfVertex[Vector3::Y] = vOffset.y + (fRadius + fDeltaRadius)*Math::Cos(fAngle);
										pfVertex[Vector3::Z] = vOffset.z;
										if (Normals) {
											pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
											pfVertex[Vector3::X] = 0.0f;
											pfVertex[Vector3::Y] = 0.0f;
											pfVertex[Vector3::Z] = 1.0f;
										}

										// Set index 0
										pIndexBuffer->SetData(nVertex, nVertex);
										nVertex++;

										// Set vertex 1
										pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
										pfVertex[Vector3::X] = vOffset.x + fRadius*Math::Sin(fAngle);
										pfVertex[Vector3::Y] = vOffset.y + fRadius*Math::Cos(fAngle);
										pfVertex[Vector3::Z] = vOffset.z;
										if (Normals) {
											pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Normal);
											pfVertex[Vector3::X] = 0.0f;
											pfVertex[Vector3::Y] = 0.0f;
											pfVertex[Vector3::Z] = 1.0f;
										}

										// Set index 1
										pIndexBuffer->SetData(nVertex, nVertex);
										nVertex++;
									}

									// Increase fAngle
									fAngle += fDeltaAngle;
								}

								// Increase fRadius
								fRadius += fDeltaRadius;
							}

							// Unlock the index buffer
							pIndexBuffer->Unlock();
						}

						// Unlock the vertex buffer
						pVertexBuffer->Unlock();
					}
					break;
				}

				case Line:
				{
					// Allocate vertex and index buffer
					uint32 nVertices = (Loops+1)*(Slices+1)*2;
					pVertexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);
					pIndexBuffer->SetElementTypeByMaximumIndex(nVertices-1);
					pIndexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);

					// Setup vertices & geometry
					if (pVertexBuffer->Lock(Lock::WriteOnly)) {
						if (pIndexBuffer->Lock(Lock::WriteOnly)) {
							float fDeltaRadius = (OuterRadius - InnerRadius)/float(Loops);
							float fDeltaAngle  = (float)(Math::DegToRad*(SweepAngle/float(Slices)));
							float fRadius      = InnerRadius;

							// Get offset
							const Vector3 &vOffset = Offset.Get();

							// Setup vertex and index buffer
							Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
							uint32 nVertex = 0;

						// Draw rings
							for (uint32 nLoop=0; nLoop<=Loops; nLoop++) {
								float fAngle = (float)(Math::DegToRad*StartAngle);

								// Create and setup the geometry
								Geometry &cGeometry = lstGeometries.Add();
								cGeometry.SetPrimitiveType(Primitive::LineStrip);
								cGeometry.SetStartIndex(nVertex);
								cGeometry.SetIndexSize(Slices+1);

								for (uint32 nSlice=0; nSlice<=Slices; nSlice++) {
									// Set vertex 0
									float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
									pfVertex[Vector3::X] = vOffset.x + fRadius*Math::Sin(fAngle);
									pfVertex[Vector3::Y] = vOffset.y + fRadius*Math::Cos(fAngle);
									pfVertex[Vector3::Z] = vOffset.z;

									// Set index 0
									pIndexBuffer->SetData(nVertex, nVertex);
									nVertex++;

									// Increase fAngle
									fAngle += fDeltaAngle;
								}

								// Increase fRadius
								fRadius += fDeltaRadius;
							}

						// Draw spokes
							float fAngle = (float)(Math::DegToRad*StartAngle);
							for (uint32 nSlice=0; nSlice<=Slices; nSlice++) {
								fRadius = InnerRadius;

								// Create and setup the geometry
								Geometry &cGeometry = lstGeometries.Add();
								cGeometry.SetPrimitiveType(Primitive::LineStrip);
								cGeometry.SetStartIndex(nVertex);
								cGeometry.SetIndexSize(Loops+1);

								for (uint32 nLoop=0; nLoop<=Loops; nLoop++) {
									// Set vertex 0
									float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
									pfVertex[Vector3::X] = vOffset.x + fRadius*Math::Sin(fAngle);
									pfVertex[Vector3::Y] = vOffset.y + fRadius*Math::Cos(fAngle);
									pfVertex[Vector3::Z] = vOffset.z;

									// Set index 0
									pIndexBuffer->SetData(nVertex, nVertex);
									nVertex++;

									// Increase fRadius
									fRadius += fDeltaRadius;
								}

								// Increase fAngle
								fAngle += fDeltaAngle;
							}

							// Unlock the index buffer
							pIndexBuffer->Unlock();
						}

						// Unlock the vertex buffer
						pVertexBuffer->Unlock();
					}
					break;
				}

				case Silhouette:
				{
					// Allocate vertex and index buffer
					uint32 nVertices = Slices+1;
					if (InnerRadius > 0.0f)
						nVertices += Slices+1;
					if (SweepAngle < 360.0f)
						nVertices += 4;
					pVertexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);
					pIndexBuffer->SetElementTypeByMaximumIndex(nVertices-1);
					pIndexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);

					// Setup vertices & geometry
					if (pVertexBuffer->Lock(Lock::WriteOnly)) {
						if (pIndexBuffer->Lock(Lock::WriteOnly)) {
							float fDeltaAngle = (float)(Math::DegToRad*SweepAngle/float(Slices));

							// Get offset
							const Vector3 &vOffset = Offset.Get();

							// Setup vertex and index buffer
							Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
							uint32 nVertex = 0;

						// Draw outer ring
							{ // Create and setup the geometry
								Geometry &cGeometry = lstGeometries.Add();
								cGeometry.SetPrimitiveType(Primitive::LineStrip);
								cGeometry.SetStartIndex(nVertex);
								cGeometry.SetIndexSize(Slices+1);
								// Setup vertex and index buffer
								float fAngle = (float)(Math::DegToRad*StartAngle);
								for (uint32 nSlice=0; nSlice<=Slices; nSlice++) {
									// Set vertex 0
									float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
									pfVertex[Vector3::X] = vOffset.x + OuterRadius*Math::Sin(fAngle);
									pfVertex[Vector3::Y] = vOffset.y + OuterRadius*Math::Cos(fAngle);
									pfVertex[Vector3::Z] = vOffset.z;

									// Set index 0
									pIndexBuffer->SetData(nVertex, nVertex);
									nVertex++;

									// Increase fAngle
									fAngle += fDeltaAngle;
								}
							}

						// Draw inner ring
							if (InnerRadius > 0.0f) {
								// Create and setup the geometry
								Geometry &cGeometry = lstGeometries.Add();
								cGeometry.SetPrimitiveType(Primitive::LineStrip);
								cGeometry.SetStartIndex(nVertex);
								cGeometry.SetIndexSize(Slices+1);

								// Setup vertex and index buffer
								float fAngle = (float)(Math::DegToRad*StartAngle);
								for (uint32 nSlice=0; nSlice<=Slices; nSlice++) {
									// Set vertex 0
									float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
									pfVertex[Vector3::X] = vOffset.x + InnerRadius*Math::Sin(fAngle);
									pfVertex[Vector3::Y] = vOffset.y + InnerRadius*Math::Cos(fAngle);
									pfVertex[Vector3::Z] = vOffset.z;

									// Set index 0
									pIndexBuffer->SetData(nVertex, nVertex);
									nVertex++;

									// Increase fAngle
									fAngle += fDeltaAngle;
								}
							}

						// Draw spokes
							if (SweepAngle < 360.0f) {
								// Sin and Cos for degree angles
								float fStopAngle = StartAngle + SweepAngle;

								// Create and setup the geometry
								Geometry &cGeometry = lstGeometries.Add();
								cGeometry.SetPrimitiveType(Primitive::LineList);
								cGeometry.SetStartIndex(nVertex);
								cGeometry.SetIndexSize(4);

								// Setup vertex and index buffer
								// Set vertex 0
								float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + InnerRadius*Math::Sin(float(StartAngle*Math::DegToRad));
								pfVertex[Vector3::Y] = vOffset.y + InnerRadius*Math::Cos(float(StartAngle*Math::DegToRad));
								pfVertex[Vector3::Z] = vOffset.z;
								// Set index 0
								pIndexBuffer->SetData(nVertex, nVertex);
								nVertex++;
								// Set vertex 1
								pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + OuterRadius*Math::Sin(float(StartAngle*Math::DegToRad));
								pfVertex[Vector3::Y] = vOffset.y + OuterRadius*Math::Cos(float(StartAngle*Math::DegToRad));
								pfVertex[Vector3::Z] = vOffset.z;
								// Set index 1
								pIndexBuffer->SetData(nVertex, nVertex);
								nVertex++;
								// Set vertex 2
								pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + InnerRadius*Math::Sin(float(fStopAngle*Math::DegToRad));
								pfVertex[Vector3::Y] = vOffset.y + InnerRadius*Math::Cos(float(fStopAngle*Math::DegToRad));
								pfVertex[Vector3::Z] = vOffset.z;
								// Set index 2
								pIndexBuffer->SetData(nVertex, nVertex);
								nVertex++;
								// Set vertex 3
								pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
								pfVertex[Vector3::X] = vOffset.x + OuterRadius*Math::Sin(float(fStopAngle*Math::DegToRad));
								pfVertex[Vector3::Y] = vOffset.y + OuterRadius*Math::Cos(float(fStopAngle*Math::DegToRad));
								pfVertex[Vector3::Z] = vOffset.z;
								// Set index 3
								pIndexBuffer->SetData(nVertex, nVertex);
								nVertex++;
							}

							// Unlock the index buffer
							pIndexBuffer->Unlock();
						}

						// Unlock the vertex buffer
						pVertexBuffer->Unlock();
					}
					break;
				}

				case Point:
				{
					// Allocate vertex and index buffer
					uint32 nVertices = (Slices+1)*(Loops+1);
					pVertexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);
					pIndexBuffer->SetElementTypeByMaximumIndex(nVertices-1);
					pIndexBuffer->Allocate(nVertices, bStatic ? Usage::Static : Usage::Dynamic);

					// Setup vertices & geometry
					if (pVertexBuffer->Lock(Lock::WriteOnly)) {
						if (pIndexBuffer->Lock(Lock::WriteOnly)) {
							float fDeltaRadius = (OuterRadius - InnerRadius)/Loops;
							float fDeltaAngle  = float(Math::DegToRad*SweepAngle/Slices);

							// Get offset
							const Vector3 &vOffset = Offset.Get();

							// Create and setup the geometry
							Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
							Geometry &cGeometry = lstGeometries.Add();
							cGeometry.SetPrimitiveType(Primitive::PointList);
							cGeometry.SetStartIndex(0);
							cGeometry.SetIndexSize(nVertices);

							// Setup vertex and index buffer
							uint32 nVertex = 0;
							float fRadius = InnerRadius;
							for (uint32 nLoop=0; nLoop<=Loops; nLoop++) {
								float fAngle = (float)(Math::DegToRad*StartAngle);
								for (uint32 nSlice=0; nSlice<=Slices; nSlice++) {
									// Set vertex
									float *pfVertex = (float*)pVertexBuffer->GetData(nVertex, VertexBuffer::Position);
									pfVertex[Vector3::X] = vOffset.x + fRadius*Math::Sin(fAngle);
									pfVertex[Vector3::Y] = vOffset.y + fRadius*Math::Cos(fAngle);
									pfVertex[Vector3::Z] = vOffset.z;

									// Set index
									pIndexBuffer->SetData(nVertex, nVertex);
									nVertex++;

									// Increase fAngle
									fAngle += fDeltaAngle;
								}
								// Increase fRadius
								fRadius += fDeltaRadius;
							}

							// Unlock the index buffer
							pIndexBuffer->Unlock();
						}

						// Unlock the vertex buffer
						pVertexBuffer->Unlock();
					}
					break;
				}
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
