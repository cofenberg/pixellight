/*********************************************************\
 *  File: SceneLoaderProc.cpp                            *
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


// [TODO] Add spot light support (falloff)
// [TODO] Add better material support


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/Tools/Stopwatch.h>
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/MeshManager.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include <PLScene/Scene/SCCell.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SNCellPortal.h>
#include <PLScene/Scene/SNPointLight.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodes/SNMesh.h>
#include "PLDefaultFileFormats/Doom3/SceneLoaderProc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneLoaderProc)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SceneLoaderProc::Load(SceneContainer &cContainer, File &cFile)
{
	// Start the stopwatch
	Stopwatch cStopwatch;
	cStopwatch.Start();

	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n{}()[]=,;\"");
	cTokenizer.SetSingleChars("");
	cTokenizer.SetQuotes("");

	// Initialize the statistics
	SInstance sInstance;
	sInstance.nTotalNumOfMeshes    = 0;
	sInstance.nTotalNumOfVertices = 0;
	sInstance.nTotalNumOfIndices  = 0;
	sInstance.nTotalNumOfCells    = 0;
	sInstance.nTotalNumOfPortals  = 0;
	sInstance.nTotalNumOfLights   = 0;

	// Strings (for faster comparison)
	String sInterAreaPortals = "interAreaPortals";
	String sCloseBracket	 = "}";
	String sModel			 = "model";
	String sNodes			 = "nodes";

	// Get the material manager
	MaterialManager &cMaterialManager = cContainer.GetSceneContext()->GetRendererContext().GetMaterialManager();

	// Get the mesh manager
	MeshManager &cMeshManager = cContainer.GetSceneContext()->GetMeshManager();

	// Load
	while (cTokenizer.GetNextToken().GetLength()) {
		// 'model' (cell)
		if (cTokenizer.GetToken() == sModel) {
			// Get the name
			String sModelName = cTokenizer.GetNextToken();

			// Get the number of surfaces
			uint32 nNumOfSurfaces = cTokenizer.GetNextToken().GetInt();

			// ONLY 'areas', please (no trigger, func_static etc.)
			// Keep areas without any surfaces, else the portal area indices will be wrong!
			if (!sModelName.Compare("_area", 0, 5)) {
				// Skip the whole block
				cTokenizer.SetDelimiters(" \t\r\n{()[]=,;\"");
				while (cTokenizer.GetNextToken().GetLength()) {
					if (cTokenizer.GetToken() == sCloseBracket)
						break;
				}
				cTokenizer.SetDelimiters(" \t\r\n{}()[]=,;\"");
				continue;
			}

			// Create the cell
			SCCell *pCell = static_cast<SCCell*>(cContainer.Create("PLScene::SCCell", sModelName));
			sInstance.nTotalNumOfCells++;
			sInstance.lstCells.Add(pCell);

			// Load in all model surfaces (meshes)
			for (uint32 nSurface=0; nSurface<nNumOfSurfaces; nSurface++) {
				// Get the material name
				String sMaterialName = cTokenizer.GetNextToken();

				// Get the number of vertices
				uint32 nNumOfVertices = cTokenizer.GetNextToken().GetInt();

				// Get the number of indices
				uint32 nNumOfIndices = cTokenizer.GetNextToken().GetInt();

				// Get an unused mesh name
				String sName;
				uint32 i = 0;
				do {
					sName = sModelName + '_' + int(nSurface+i);
					i++;
				} while (cMeshManager.Get(sName));

				// Create the mesh
				Mesh *pMesh = cMeshManager.Create(sName);

				// Add the material to the mesh
				// [TEST]
				Material *pMaterial = cMaterialManager.LoadResource("Data/Effects/NoLightingDefault.plfx");
//				Material *pMaterial = cMaterialManager.LoadResource(sMaterialName);
				pMesh->AddMaterial(pMaterial);

				// Add morph target
				Vector3 vCenter = Vector3::Zero;
				MeshMorphTarget *pMorphTarget = pMesh->AddMorphTarget();
				if (pMorphTarget) {
					VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
					pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
					pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
					pVertexBuffer->AddVertexAttribute(VertexBuffer::Normal,   0, VertexBuffer::Float3);
					pVertexBuffer->Allocate(nNumOfVertices, Usage::Static);
					sInstance.nTotalNumOfVertices += nNumOfVertices;

					// Fill vertex buffer
					if (pVertexBuffer->Lock(Lock::WriteOnly)) {
						for (uint32 nVertex=0; nVertex<nNumOfVertices; nVertex++) {
							// Position
							float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::Position));
							vCenter.x += pfVertex[Vector3::X] = cTokenizer.GetNextToken().GetFloat()*Scale;
							if (SwapYZ) {
								vCenter.z += pfVertex[Vector3::Z] = cTokenizer.GetNextToken().GetFloat()*Scale;
								vCenter.y += pfVertex[Vector3::Y] = cTokenizer.GetNextToken().GetFloat()*Scale;
							} else {
								vCenter.y += pfVertex[Vector3::Y] = cTokenizer.GetNextToken().GetFloat()*Scale;
								vCenter.z += pfVertex[Vector3::Z] = cTokenizer.GetNextToken().GetFloat()*Scale;
							}

							// Texture coordinate
							pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::TexCoord));
							pfVertex[Vector2::X] = cTokenizer.GetNextToken().GetFloat();
							pfVertex[Vector2::Y] = cTokenizer.GetNextToken().GetFloat();

							// Normal
							pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::Normal));
							pfVertex[Vector3::X] = cTokenizer.GetNextToken().GetFloat();
							if (SwapYZ) {
								pfVertex[Vector3::Z] = cTokenizer.GetNextToken().GetFloat();
								pfVertex[Vector3::Y] = cTokenizer.GetNextToken().GetFloat();
							} else {
								pfVertex[Vector3::Y] = cTokenizer.GetNextToken().GetFloat();
								pfVertex[Vector3::Z] = cTokenizer.GetNextToken().GetFloat();
							}
						}

						// Calculate the center
						vCenter /= static_cast<float>(nNumOfVertices);

						// Center the mesh
						for (uint32 nVertex=0; nVertex<nNumOfVertices; nVertex++) {
							// Position
							float *pfVertex = static_cast<float*>(pVertexBuffer->GetData(nVertex, VertexBuffer::Position));
							pfVertex[Vector3::X] -= vCenter.x;
							pfVertex[Vector3::Y] -= vCenter.y;
							pfVertex[Vector3::Z] -= vCenter.z;
						}

						// Add LOD level
						MeshLODLevel *pLODLevel = pMesh->AddLODLevel();
						if (pLODLevel) {
							pLODLevel->CreateGeometries();
							pLODLevel->CreateIndexBuffer();

							// Allocate index buffer
							IndexBuffer *pIndexBuffer = pLODLevel->GetIndexBuffer();
							if (pIndexBuffer) {
								pIndexBuffer->SetElementTypeByMaximumIndex(nNumOfVertices-1);
								pIndexBuffer->Allocate(nNumOfIndices, Usage::Static);
								sInstance.nTotalNumOfIndices += nNumOfIndices;

								// Fill index buffer
								Array<Geometry> &lstGeometries = *pLODLevel->GetGeometries();
								if (pIndexBuffer->Lock(Lock::WriteOnly)) {
									// Load indices
									for (uint32 nIndex=0; nIndex<nNumOfIndices; nIndex++)
										pIndexBuffer->SetData(nIndex, cTokenizer.GetNextToken().GetInt());

									// Check index order
									Vector3 vV0, vV1, vV2, vN;
									for (uint32 nIndex=0; nIndex<nNumOfIndices; nIndex+=3) {
										vV0 = static_cast<float*>(pVertexBuffer->GetData(pIndexBuffer->GetData(nIndex+0), VertexBuffer::Position));
										vV1 = static_cast<float*>(pVertexBuffer->GetData(pIndexBuffer->GetData(nIndex+1), VertexBuffer::Position));
										vV2 = static_cast<float*>(pVertexBuffer->GetData(pIndexBuffer->GetData(nIndex+2), VertexBuffer::Position));
										vN  = static_cast<float*>(pVertexBuffer->GetData(pIndexBuffer->GetData(nIndex+0), VertexBuffer::Normal));
										if ((vV1-vV0).CrossProduct(vV2-vV0).DotProduct(vN) < 0.0f) {
											uint32 nTemp = pIndexBuffer->GetData(nIndex+1);
											pIndexBuffer->SetData(nIndex+1, pIndexBuffer->GetData(nIndex+2));
											pIndexBuffer->SetData(nIndex+2, nTemp);
										}
									}

									// Unlock the index buffer
									pIndexBuffer->Unlock();

									// Create the geometry
									Geometry &cGeometry = lstGeometries.Add();
									cGeometry.SetPrimitiveType(Primitive::TriangleList);
									cGeometry.SetStartIndex(0);
									cGeometry.SetIndexSize(nNumOfIndices);
									cGeometry.SetMaterial(0);
								}
							}
						}

						// Unlock the vertex buffer
						pVertexBuffer->Unlock();
					}
				}

				// Create the mesh
				SNMesh *pMeshNode = static_cast<SNMesh*>(pCell->Create("PLScene::SNMesh", sName, String::Format("Position=\"%g %g %g\"", vCenter.x, vCenter.y, vCenter.z)));
				if (pMeshNode) {
					sInstance.nTotalNumOfMeshes++;
					// Set the mesh
					pMeshNode->LoadMesh(sName);
				}
			}

			// Calculate the scene container bounding box
			pCell->CalculateAABoundingBox();

			// Calculate the center of the cell
			AABoundingBox cAABB = pCell->GetAABoundingBox();
			Vector3 vCenter = cAABB.GetCenter();

			// Set cell position
			pCell->GetTransform().SetPosition(vCenter);

			// Set cell bounding box
			cAABB.vMin -= vCenter;
			cAABB.vMax -= vCenter;
			pCell->SetAABoundingBox(cAABB);

			// Center all scene nodes
			for (uint32 nNode=0; nNode<pCell->GetNumOfElements(); nNode++) {
				SceneNode &cSceneNode = *pCell->Get(nNode);
				cSceneNode.GetTransform().SetPosition(cSceneNode.GetTransform().GetPosition()-vCenter);
			}

		// 'interAreaPortals' (Portals)
		} else if (cTokenizer.GetToken() == sInterAreaPortals) {
			// Get the number of cells (unused)
			cTokenizer.GetNextToken().GetInt();

			// Get the number of portals
			uint32 nNumOfPortals = cTokenizer.GetNextToken().GetInt();

			// Load the portals
			for (uint32 nPortal=0; nPortal<nNumOfPortals; nPortal++) {
				uint32 nNumOfPoints = cTokenizer.GetNextToken().GetInt();
				uint32 nPosCell     = cTokenizer.GetNextToken().GetInt();
				uint32 nNegCell     = cTokenizer.GetNextToken().GetInt();

				// Read the points
				Array<Vector3> lstPoints;
				Vector3 vCenter = Vector3::Zero;
				for (uint32 nPoint=0; nPoint<nNumOfPoints; nPoint++) {
					Vector3 &vPoint = lstPoints.Add();
					vCenter.x += vPoint.x = cTokenizer.GetNextToken().GetFloat()*Scale;
					if (SwapYZ) {
						vCenter.z += vPoint.z = cTokenizer.GetNextToken().GetFloat()*Scale;
						vCenter.y += vPoint.y = cTokenizer.GetNextToken().GetFloat()*Scale;
					} else {
						vCenter.y += vPoint.y = cTokenizer.GetNextToken().GetFloat()*Scale;
						vCenter.z += vPoint.z = cTokenizer.GetNextToken().GetFloat()*Scale;
					}
				}

				// Calculate the center
				vCenter /= static_cast<float>(nNumOfPoints);

				// Center the points
				for (uint32 nPoint=0; nPoint<nNumOfPoints; nPoint++)
					lstPoints[nPoint] -= vCenter;

				// Create the two portals
				SCCell *pPosCell = sInstance.lstCells[nPosCell];
				SCCell *pNegCell = sInstance.lstCells[nNegCell];
				if (pPosCell && pNegCell) {
					// Positive portal
					String sName = "PortalTo_" + pNegCell->GetName();
					SNCellPortal *pPortal = static_cast<SNCellPortal*>(pPosCell->Create("PLScene::SNCellPortal", sName, String::Format("Position=\"%g %g %g\" TargetCell=\"Parent.",
						vCenter.x-pPosCell->GetTransform().GetPosition().x, vCenter.y-pPosCell->GetTransform().GetPosition().y, vCenter.z-pPosCell->GetTransform().GetPosition().z) + pNegCell->GetName() + '\"'));
					if (pPortal) {
						sInstance.nTotalNumOfPortals++;
						PLMath::Polygon &cPolygon = pPortal->GetPolygon();
						cPolygon.GetVertexList().Clear();
						for (uint32 nPoint=0; nPoint<nNumOfPoints; nPoint++)
							cPolygon.GetVertexList().Add(lstPoints[nPoint]);
						pPortal->UpdatePolygon();
					}

					// Negative portal
					sName = "PortalTo_" + pPosCell->GetName();
					pPortal = static_cast<SNCellPortal*>(pNegCell->Create("PLScene::SNCellPortal", sName, String::Format("Position=\"%g %g %g\" TargetCell=\"Parent.",
						vCenter.x-pNegCell->GetTransform().GetPosition().x, vCenter.y-pNegCell->GetTransform().GetPosition().y, vCenter.z-pNegCell->GetTransform().GetPosition().z) + pPosCell->GetName() + '\"'));
					if (pPortal) {
						sInstance.nTotalNumOfPortals++;
						PLMath::Polygon &cPolygon = pPortal->GetPolygon();
						cPolygon.GetVertexList().Clear();
						for (uint32 nPoint=0; nPoint<nNumOfPoints; nPoint++)
							cPolygon.GetVertexList().Add(lstPoints[nNumOfPoints-nPoint-1]);
						pPortal->UpdatePolygon();
					}
				}
			}

		// 'nodes'
		} else if (cTokenizer.GetToken() == sNodes) {
			// Get the number of nodes
			uint32 nNumOfNodes = cTokenizer.GetNextToken().GetInt();
			sInstance.lstNodes.Resize(nNumOfNodes);

			// Load the nodes
			String sName;
			Node *pNode = &sInstance.lstNodes[0];
			for (uint32 nNode=0; nNode<nNumOfNodes; nNode++, pNode++) {
				// Set plane
				pNode->cPlane.fN[Vector3::X] = cTokenizer.GetNextToken().GetFloat();
				if (SwapYZ) {
					pNode->cPlane.fN[Vector3::Z] = cTokenizer.GetNextToken().GetFloat();
					pNode->cPlane.fN[Vector3::Y] = cTokenizer.GetNextToken().GetFloat();
				} else {
					pNode->cPlane.fN[Vector3::Y] = cTokenizer.GetNextToken().GetFloat();
					pNode->cPlane.fN[Vector3::Z] = cTokenizer.GetNextToken().GetFloat();
				}
				pNode->cPlane.fD = cTokenizer.GetNextToken().GetFloat();

				// Set children
				pNode->nPosChild = cTokenizer.GetNextToken().GetInt();
				pNode->nNegChild = cTokenizer.GetNextToken().GetInt();

				// Validate cell indices
				if (pNode->nPosChild < 0) {
					sName = String::Format("_area%d", (-1-pNode->nPosChild));
					pNode->nPosChild = -1-GetCellIndexByName(sInstance, sName);
				}
				if (pNode->nNegChild < 0) {
					sName = String::Format("_area%d", (-1-pNode->nNegChild));
					pNode->nNegChild = -1-GetCellIndexByName(sInstance, sName);
				}
			}
		}
	}

	// Cleanup
	cTokenizer.Stop();

	// Load 'map' file?
	if (LoadMap) {
		// Get 'map' filename
		String sMapFilename = Url(cFile.GetUrl()).CutExtension() + ".map";

		// Load the 'map'
		LoadMapFile(sInstance, cContainer, sMapFilename);
	}

	// Stop the stopwatch
	cStopwatch.Stop();

	// Output the statistics
	PL_LOG(Debug, '\n')
	PL_LOG(Debug, "Scene statistics of '" + cFile.GetUrl().GetNativePath() + '\'')
	PL_LOG(Debug, "Loading time: " + String::Format("%g", cStopwatch.GetSeconds()) + " sec");
	PL_LOG(Debug, String::Format("  Total number of scene nodes: %d",  sInstance.nTotalNumOfCells+sInstance.nTotalNumOfMeshes+sInstance.nTotalNumOfPortals+sInstance.nTotalNumOfLights))
	PL_LOG(Debug, String::Format("  Total number of cells: %d",        sInstance.nTotalNumOfCells))
	PL_LOG(Debug, String::Format("  Total number of meshes: %d",       sInstance.nTotalNumOfMeshes))
	PL_LOG(Debug, String::Format("    Total number of vertices: %d",   sInstance.nTotalNumOfVertices))
	PL_LOG(Debug, String::Format("    Total number of indices: %d",    sInstance.nTotalNumOfIndices))
	PL_LOG(Debug, String::Format("    Total number of triangles: %d",  sInstance.nTotalNumOfIndices/3))
	PL_LOG(Debug, String::Format("  Total number of portals: %d",      sInstance.nTotalNumOfPortals))
	PL_LOG(Debug, String::Format("  Total number of lights: %d",       sInstance.nTotalNumOfLights))
	PL_LOG(Debug, '\n')

	// Done
	return true;
}

bool SceneLoaderProc::Save(SceneContainer &cContainer, File &cFile)
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
SceneLoaderProc::SceneLoaderProc() :
	SwapYZ(this),
	Scale(this),
	LoadMap(this),
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
SceneLoaderProc::~SceneLoaderProc()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Load the 'map' file of this 'proc' file
*/
bool SceneLoaderProc::LoadMapFile(SInstance &sInstance, SceneContainer &cContainer, const String &sFilename) const
{
	// Check parameters
	if (!sFilename.GetLength())
		return false; // Error!

	// Open the file
	File cFile(sFilename);
	if (!cFile.Open(File::FileRead)) {
		// Error!
		return false;
	}

	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n()[]=,;\"");
	cTokenizer.SetSingleChars("{}");
	cTokenizer.SetQuotes("");

	// Strings (for faster comparison)
	String sInfoPlayerStart	= "info_player_start";
	String sLightRadius		= "light_radius";
	String sNoSpecular		= "nospecular";
	String sNoDiffuse		= "nodiffuse";
	String sClassName		= "classname";
	String sNoShadows		= "noshadows";
	String sRotation		= "rotation";
	String sFalloff			= "falloff";
	String sCloseBracket	= "}";
	String sColor			= "_color";
	String sOpenBracket		= "{";
	String sOrigin			= "origin";
	String sLight			= "light";
	String sName			= "name";

	// Look for '{'
	SceneNode *pSceneNode;
	SNPointLight *pLight;
	Vector3 vV;
	while (cTokenizer.GetNextToken().GetLength()) {
		// {
		if (cTokenizer.GetToken() == sOpenBracket) {
			pSceneNode = pLight = nullptr;

			// Look for '}'
			while (cTokenizer.GetNextToken().GetLength()) {
				// }
				if (cTokenizer.GetToken() == sCloseBracket)
					break;

				// "classname" MUST come first
				if (cTokenizer.GetToken() == sClassName) {
					if (!pSceneNode) {
						cTokenizer.GetNextToken();

						// "light"
						if (cTokenizer.GetToken() == sLight) {
							pSceneNode = cContainer.Create("PLScene::SNPointLight");
							if (pSceneNode) {
								sInstance.nTotalNumOfLights++;
								if (pSceneNode->IsLight())
									pLight = static_cast<SNPointLight*>(pSceneNode);
							}

						// info_player_start
						} else if (cTokenizer.GetToken() == sInfoPlayerStart) {
							pSceneNode = cContainer.Create("PLScene::SNCamera", "Camera");
							if (pSceneNode) {
								pSceneNode->AddModifier("PLScene::SNMLookController");
								pSceneNode->AddModifier("PLScene::SNMRotationFixRoll");
								pSceneNode->AddModifier("PLScene::SNMMoveController", "Speed=\"0.2\"");
							}
						} else {
							pSceneNode = pLight = nullptr;
						}
					}
					continue;
				}
				if (!pSceneNode)
					continue;

				// "name"
				if (cTokenizer.GetToken() == sName) {
					pSceneNode->SetName(cTokenizer.GetNextToken());

				// "origin"
				} else if (cTokenizer.GetToken() == sOrigin) {
					vV.x = cTokenizer.GetNextToken().GetFloat();
					if (SwapYZ) {
						vV.z = cTokenizer.GetNextToken().GetFloat();
						vV.y = cTokenizer.GetNextToken().GetFloat();
					} else {
						vV.y = cTokenizer.GetNextToken().GetFloat();
						vV.z = cTokenizer.GetNextToken().GetFloat();
					}
					pSceneNode->GetTransform().SetPosition(vV);

				// "rotation"
				} else if (cTokenizer.GetToken() == sRotation) {
				//"" "4.03077e-007 1 0 -1 4.03077e-007 0 0 0 1"
				//	pSceneNode->SetVar("Position", cTokenizer.GetNextToken());

				// Light only
				} else {
					if (pSceneNode && pSceneNode->IsLight()) {
						// "noshadows"
						if (cTokenizer.GetToken() == sNoShadows) {
							if (cTokenizer.GetNextToken().GetBool()) {
								uint32 nFlags = pLight->GetFlags();
								nFlags &= ~SNLight::CastShadow;
								nFlags &= ~SNLight::ReceiveShadow;
								pLight->SetFlags(nFlags);
							} else {
								pLight->SetFlags(pLight->GetFlags() | SNLight::CastShadow | SNLight::ReceiveShadow);
							}

						// "nospecular"
						} else if (cTokenizer.GetToken() == sNoSpecular) {
							if (cTokenizer.GetNextToken().GetBool()) {
								// [TODO] ?
	//								pLight->SetFlags(pLight->GetFlags() & ~SNLight::Specular);
	//							else pLight->SetFlags(pLight->GetFlags() | SNLight::Specular);
							}

						// "nodiffuse"
						} else if (cTokenizer.GetToken() == sNoDiffuse) {
							if (cTokenizer.GetNextToken().GetBool()) {
								// [TODO] ?
	//								pLight->SetFlags(pLight->GetFlags() & ~SNLight::Diffuse);
	//							else pLight->SetFlags(pLight->GetFlags() | SNLight::Diffuse);
							}

						// "falloff"
						} else if (cTokenizer.GetToken() == sFalloff) {
							// [TODO] Directional light

						// "_color"
						} else if (cTokenizer.GetToken() == sColor) {
							vV.x = cTokenizer.GetNextToken().GetFloat();
							vV.y = cTokenizer.GetNextToken().GetFloat();
							vV.z = cTokenizer.GetNextToken().GetFloat();
							pLight->Color.Set(PLGraphics::Color3(vV.x, vV.y, vV.z));

						// "light_radius"
						} else if (cTokenizer.GetToken() == sLightRadius) {
							// [x, y, z] -> We only use x
							pLight->SetRange(cTokenizer.GetNextToken().GetFloat());
							cTokenizer.GetNextToken().GetFloat(); // Skip y
							cTokenizer.GetNextToken().GetFloat(); // Skip z
						}
					}
				}
			}

			// Push light, we apply Scale AFTER the cell was found to avoid notable precission errors
			if (pLight) {
				PushLight(sInstance, *pLight);
				pLight->SetRange(pLight->GetRange()*Scale);
			} else {
				if (pSceneNode) {
					int nCell = GetCell(sInstance, pSceneNode->GetTransform().GetPosition());
					if (nCell) {
						// Rename cell: -1 -> 0, -2 -> 1
						nCell = -1-nCell;
						if (nCell >= 0) {
							SCCell *pCell = sInstance.lstCells[nCell];
							if (pCell) {
								// Transform the scene node into the new container
								pSceneNode->GetTransform().SetPosition(pSceneNode->GetTransform().GetPosition()*Scale-pCell->GetTransform().GetPosition());

								// Set the new container
								pSceneNode->SetContainer(*pCell);
							}
						}

					// Error, everything MUST be within a cell!
					} else {
						SCCell *pCell = sInstance.lstCells[0];
						if (pCell) {
							// Transform the scene node into the new container
							pSceneNode->GetTransform().SetPosition(pSceneNode->GetTransform().GetPosition()*Scale-pCell->GetTransform().GetPosition());

							// Set the new container
							pSceneNode->SetContainer(*pCell);
						}
					}
				}
			}
		}
	}

	// Cleanup
	cTokenizer.Stop();

	// Done
	return true;
}

/**
*  @brief
*    Returns the cell index
*/
int SceneLoaderProc::GetCellIndexByName(SInstance &sInstance, const String &sName) const
{
	for (uint32 i=0; i<sInstance.lstCells.GetNumOfElements(); i++) {
		if (sName == sInstance.lstCells[i]->GetName())
			return i;
	}

	// Error!
	return -1;
}

/**
*  @brief
*    Returns the cell the given position is in
*/
int SceneLoaderProc::GetCell(SInstance &sInstance, const Vector3 &vPos) const
{
	if (sInstance.lstNodes.IsEmpty())
		return 0; // Error!
	Node *pNode = &sInstance.lstNodes[0];
	while (true) {
		if (pNode->cPlane.GetSide(vPos) == Plane::InFront) { // Front
			if (pNode->nPosChild > 0) {
				pNode = &sInstance.lstNodes[pNode->nPosChild];
			} else {
				return pNode->nPosChild;
			}
		} else { // Back
			if (pNode->nNegChild > 0) {
				pNode = &sInstance.lstNodes[pNode->nNegChild];
			} else {
				return pNode->nNegChild;
			}
		}
	}
}

/**
*  @brief
*    Pushs down a light to a cell
*/
void SceneLoaderProc::PushLight(SInstance &sInstance, SNPointLight &cLight, Node *pNode) const
{
	if (sInstance.lstNodes.GetNumOfElements()) {
		if (!pNode)
			pNode = &sInstance.lstNodes[0];

		float fRadius   = cLight.GetRange();
		float fDistance = pNode->cPlane.GetDistance(cLight.GetTransform().GetPosition());

		if (fDistance > -fRadius) { // Front
			if (pNode->nPosChild > 0) {
				PushLight(sInstance, cLight, &sInstance.lstNodes[pNode->nPosChild]);
			} else {
				// Rename cell: -1 -> 0, -2 -> 1
				int nCell = -1-pNode->nPosChild;
				if (nCell >= 0) {
					SCCell *pCell = sInstance.lstCells[nCell];
					if (pCell) {
						// Transform the scene node into the new container
						cLight.GetTransform().SetPosition(cLight.GetTransform().GetPosition()*Scale-pCell->GetTransform().GetPosition());

						// Set the new container
						cLight.SetContainer(*pCell);
					}
				}
			}
		} else { // Back
			if (pNode->nNegChild > 0) {
				PushLight(sInstance, cLight, &sInstance.lstNodes[pNode->nNegChild]);
			} else {
				// Rename cell: -1 -> 0, -2 -> 1
				int nCell = -1-pNode->nNegChild;
				if (nCell >= 0) {
					SCCell *pCell = sInstance.lstCells[nCell];
					if (pCell) {
						// Transform the scene node into the new container
						cLight.GetTransform().SetPosition(cLight.GetTransform().GetPosition()*Scale-pCell->GetTransform().GetPosition());

						// Set the new container
						cLight.SetContainer(*pCell);
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
