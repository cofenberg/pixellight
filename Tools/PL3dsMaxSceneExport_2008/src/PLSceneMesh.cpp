/*********************************************************\
 *  File: PLSceneMesh.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLCore/File/File.h>
#include <IGame/IGame.h>
#include <IGame/IGameModifier.h>
#include <iparamb2.h>
#include <notetrck.h>
#include <CS/Phyexp.h>
#include <morpher/wm3.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMaterial.h"
#include "PL3dsMaxSceneExport/PLSceneMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMesh;


//[-------------------------------------------------------]
//[ Public definitions                                    ]
//[-------------------------------------------------------]
const char *PLSceneMesh::SkeletonAnimation    = "Skeleton animation";
const char *PLSceneMesh::MorphTargetAnimation = "Morph target animation";
const char *PLSceneMesh::PointCacheAnimation  = "Point cache animation";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the IGame node this mesh comes from
*/
IGameNode &PLSceneMesh::GetIGameNode() const
{
	return *m_pIGameNode;
}

/**
*  @brief
*    Returns the 3ds Max object this mesh comes from
*/
Object *PLSceneMesh::Get3dsMaxObject() const
{
	return m_p3dsMaxObject;
}

/**
*  @brief
*    Returns the mesh name
*/
const std::string &PLSceneMesh::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Returns a list of all morph channels
*/
const Array<morphChannel*> &PLSceneMesh::GetMorphChannels() const
{
	return m_lstMorphChannels;
}

/**
*  @brief
*    Returns the list of animations
*/
const Array<PLSceneMesh::Animation*> &PLSceneMesh::GetAnimations() const
{
	return m_lstAnimations;
}

/**
*  @brief
*    Returns the list of materials
*/
const Array<PLSceneMaterial*> &PLSceneMesh::GetMaterials() const
{
	return m_lstMaterials;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneMesh::PLSceneMesh(PLScene &cScene, IGameNode &cIGameNode, const std::string &sName) :
	m_pScene(&cScene),
	m_pIGameNode(&cIGameNode),
	m_p3dsMaxObject(nullptr),
	m_sName(sName),
	m_nNumOfVertices(0),
	m_nOriginalNumOfVertices(0),
	m_nNumOfTriangles(0),
	m_nNumOfGeometries(0),
	m_nTotalNumOfVertexWeights(0)
{
	// By default there are no texture coordinates at all
	for (int i=0; i<PLSceneExportOptions::MaxTexCoords; i++)
		m_bTexCoord[i] = false;

	// Get the IGame mesh object of the given IGame node
	IGameObject *pIGameObject = cIGameNode.GetIGameObject();
	if (pIGameObject) {


		// [TEST] LOD export by using MultiRes
		// Loop through all modifiers
/*		for (int nModifier=0; nModifier<pIGameObject->GetNumModifiers(); nModifier++) {
			// Get the modifier
			IGameModifier *pIGameModifier = pIGameObject->GetIGameModifier(nModifier);
			if (pIGameModifier) {
				// Get the 3ds Max modifier and ONLY take it into account if it is enabled
				Modifier *p3dsMaxModifier = pIGameModifier->GetMaxModifier();
				if (p3dsMaxModifier && p3dsMaxModifier->IsEnabled()) {
					TCHAR *pszClassName = pIGameModifier->GetClassName();
					if (!stricmp(pszClassName, "MultiRes")) {
						// Get the property container
						IPropertyContainer *pIPropertyContainer = pIGameModifier->GetIPropertyContainer();
						if (pIPropertyContainer) {
							// Get the 'vertexCount' property
							IGameProperty *pIGameProperty = pIPropertyContainer->QueryProperty("vertexPercent");
							if (pIGameProperty && pIGameProperty->GetType() == IGAME_FLOAT_PROP) {

								float fVertexPercent = 0.0f;
								if (pIGameProperty->GetPropertyValue(fVertexPercent)) {
									fVertexPercent = fVertexPercent;
								}

								if (pIGameProperty->IsPBlock2()) {
									IParamBlock2 *pIParamBlock2 = pIGameProperty->GetMaxParamBlock2();
									if (pIParamBlock2) {
										Interval cInterval;
										int nParamBlockIndex = pIGameProperty->GetParamBlockIndex();

										if (pIParamBlock2->GetValue(nParamBlockIndex, TIME_NegInfinity, fVertexPercent, cInterval))
											int ii = 0;

										fVertexPercent = 20.0f;

										// [TODO] How to force 3ds Max to update the resulting mesh?
	//									if (pIParamBlock2->SetValue(nParamBlockIndex, TIME_NegInfinity, fVertexPercent))
	//										int ii = 0;

	//									if (pIParamBlock2->GetValue(nParamBlockIndex, TIME_NegInfinity, fVertexPercent, cInterval))
	//										int ii = 0;
									}
								}
							}

	/*
		
							// Loop through all properties
							for (int nProperty=0; nProperty<pIPropertyContainer->GetNumberOfProperties(); nProperty++) {
								// Get the property
								IGameProperty *pIGameProperty = pIPropertyContainer->GetProperty(nProperty);
								if (pIGameProperty) {
									TCHAR *pszName = pIGameProperty->GetName();
									pszName = pszName;
								}
							}
	*/						
	/*					}
					}
				}
			}
		}
*/

		// Backup the 3ds Max object pointer
		m_p3dsMaxObject = pIGameObject->GetMaxObject();

		// Check the type of the IGame object
		if (pIGameObject->GetIGameType() == IGameObject::IGAME_MESH) {
			// Export mesh?
			if (g_SEOptions.bExportMeshes)
				CollectMeshData(*pIGameObject);
		} else {
			g_pLog->LogFLine(PLLog::Error, "%s: IGame object is no known mesh object!", cIGameNode.GetName());
		}

		// Release the IGame object
		cIGameNode.ReleaseIGameObject();
	} else {
		g_pLog->LogFLine(PLLog::Error, "%s: IGame node has no IGame object!", cIGameNode.GetName());
	}
}

/**
*  @brief
*    Destructor
*/
PLSceneMesh::~PLSceneMesh()
{
	// Destroy animations
	for (uint32 i=0; i<m_lstAnimations.GetNumOfElements(); i++) {
		Animation *pAnimation = m_lstAnimations[i];
		for (uint32 j=0; j<pAnimation->lstFrameSpeed.GetNumOfElements(); j++)
			delete pAnimation->lstFrameSpeed[j];
		for (uint32 j=0; j<pAnimation->lstEvents.GetNumOfElements(); j++)
			delete pAnimation->lstEvents[j];
		delete pAnimation;
	}
}

/**
*  @brief
*    Collects the mesh data
*/
void PLSceneMesh::CollectMeshData(IGameObject &cIGameObject)
{
	// Cast to mesh object, note that in case of a skinning modifier applied the IGameMesh
	// pointer may be changed into another mesh like the initial pose
	IGameMesh *pIGameMesh = static_cast<IGameMesh*>(&cIGameObject);

	// By default there is no skinning modifier
	IGameSkin *pIGameSkin = nullptr;

	// Loop through all modifiers and collect the active morph targets and process the
	// skinning modifier if there's one
	for (int nModifier=0; nModifier<cIGameObject.GetNumModifiers(); nModifier++) {
		// Get the modifier
		IGameModifier *pIGameModifier = cIGameObject.GetIGameModifier(nModifier);
		if (pIGameModifier) {
			// Get the 3ds Max modifier
			Modifier *p3dsMaxModifier = pIGameModifier->GetMaxModifier();
			if (p3dsMaxModifier) {
				// There are modifiers we and ONLY take it into account if they are enabled
				if (p3dsMaxModifier->IsEnabled()) {
					// Is this modifier a morpher modifier?
					if (pIGameModifier->IsMorpher()) {
						// Because IGameMorpher::GetMorphTarget() always return a null pointer for me I can't
						// use it and have to go the 'old way'. Note that this solution is also only
						// working in release mode... in debug mode we still get a null pointer...
						if (p3dsMaxModifier->ClassID() == MR3_CLASS_ID) {
							// Get the morpher interface
							MorphR3 *pMorphR3 = static_cast<MorphR3*>(p3dsMaxModifier);

							// Gain access to the animation controller of a morph channel
							for (int nChannel=0; nChannel<MR3_NUM_CHANNELS; nChannel++) {
								morphChannel *pChannel = &pMorphR3->chanBank[nChannel];
								if (pChannel && pChannel->mActive)
									m_lstMorphChannels.Add(pChannel);
							}
						}

						// Done
						p3dsMaxModifier = nullptr;

					// Is this modifier a skinning modifier?
					} else if (pIGameModifier->IsSkin()) {
						// Cast to skinning modifier
						pIGameSkin = static_cast<IGameSkin*>(pIGameModifier);

						// Get the initial pose mesh and use it as 'current' mesh so we get
						// the correct initial vertex data
						IGameMesh *pInitialPoseIGameMesh = pIGameSkin->GetInitialPose();
						if (pInitialPoseIGameMesh)
							pIGameMesh = pInitialPoseIGameMesh;

						// Check if the number of skinned vertices matches the number of mesh vertices
						int nNumberOfMeshVerts = pIGameMesh->GetNumberOfVerts();
						int nNumOfSkinnedVerts = pIGameSkin->GetNumOfSkinnedVerts();
						if (nNumberOfMeshVerts != nNumOfSkinnedVerts) {
							g_pLog->LogFLine(PLLog::Warning, "Node: '%s' -> Mesh has '%d' vertices, but there are '%d' skinned vertices -> both numbers should be equal",
								m_pIGameNode->GetName(), nNumberOfMeshVerts, nNumOfSkinnedVerts);
						}

						// Get the position, rotation and scale of the mesh owner node - relative to the parent node
						GMatrix mParentMatrix;
						IGameNode *pIGameNodeParent = m_pIGameNode->GetNodeParent();
						if (pIGameNodeParent)
							mParentMatrix = pIGameNodeParent->GetWorldTM(0);
						const GMatrix mInvNode = (m_pIGameNode->GetWorldTM(0)*mParentMatrix.Inverse()).Inverse();

						// Get a list of ALL other bones
						int nTotalSkinBoneCount = pIGameSkin->GetTotalBoneCount();
						if (nTotalSkinBoneCount > 0) {
							// We now the array size, so set it at once - but without 'added elements'
							m_lstBones.Resize(nTotalSkinBoneCount, false);
							m_lstBonesInitPose.Resize(nTotalSkinBoneCount, false);

							// Add ALL bones
							for (int nBone=0; nBone<nTotalSkinBoneCount; nBone++) {
								// Get the IGameNode of this bone
								IGameNode *pIGameNode = pIGameSkin->GetIGameBone(nBone);

								// Add it to the list if it is valid
								if (pIGameNode) {
									m_lstBones.Add(pIGameNode);

									// Get the bone TM when skin was added - relative to the mesh owner node
									GMatrix mBoneTM;
									pIGameSkin->GetInitBoneTM(pIGameNode, mBoneTM);
									mBoneTM *= mInvNode;
									m_lstBonesInitPose.Add(mBoneTM);
								} else {
									nBone--;
								}
							}
						}

						// Done
						p3dsMaxModifier = nullptr;
					}
				}

				// No morpher and no skin modifier... let's have a second look...
				if (p3dsMaxModifier && !pIGameModifier->IsMorpher() && !pIGameModifier->IsSkin()) {
					// 'PointCache'-modifier, please note there are two point cache types within 3ds Max, we only support "OBJECT-SPACE MODIFIER"
					if (p3dsMaxModifier->ClassID() == Class_ID(655302627, 61950361)) {	// "OBJECT-SPACE MODIFIER - Point Cache"
						// Get the property container
						IPropertyContainer *pIPropertyContainer = pIGameModifier->GetIPropertyContainer();
						if (pIPropertyContainer) {
							// Get the 'filename' property
							IGameProperty *pIGameProperty = pIPropertyContainer->QueryProperty("filename");
							if (pIGameProperty) {
								// Is this a parameter block 2?
								if (pIGameProperty->IsPBlock2()) {
									// Get parameter block 2
									IParamBlock2 *pParamBlock2 = pIGameProperty->GetMaxParamBlock2();
									if (pParamBlock2) {
										// Get the value
										Interval interval;
										MCHAR *pszFilename = nullptr;
									#if MAX_RELEASE >= 12000	// For R12 release
										pParamBlock2->GetValue(0, 0, (const MCHAR*&)pszFilename, interval);
									#else
										pParamBlock2->GetValue(0, 0, pszFilename, interval);
									#endif
										if (pszFilename) {
											String sPointCache = pszFilename;

											// Open the 'PointCache'-file
											// Can we use the given absolute filename?
											File cPointCacheFileAbsolute(sPointCache);
											if (!cPointCacheFileAbsolute.Exists()) {
												// Hm, the point cache file can't be opened... maybe an absolute
												// filename is given, but the file now is within the same directory
												// as the 3ds Max scene file...

												// Get the current path of the loaded 3ds Max scene
												Url cUrl = GetCOREInterface()->GetCurFilePath().data();
												String sCurFilePath = cUrl.CutFilename();
												if (sCurFilePath.GetLength()) {
													// Compose absolute filename by just concatenating the two filenames (for relative filenames)
													String sPointCacheTemp = sCurFilePath + sPointCache;
													File cPointCacheFileRelative(sPointCacheTemp);
													if (cPointCacheFileRelative.Exists()) {
														// Japo, now we have a valid absolute filename! :D
														sPointCache = sPointCacheTemp;
													} else {
														// Get filename relative to the currently loaded 3ds Max scene
														cUrl = sPointCache;
														sPointCacheTemp = sCurFilePath + cUrl.GetFilename();
														File sPointCacheFileLastChange(sPointCacheTemp);
														if (sPointCacheFileLastChange.Exists()) {
															// Japo, now we have a valid absolute filename! :D
															sPointCache = sPointCacheTemp;
														} else {
															// Sorry, we can't find the file!
															sPointCache = "";
														}
													}
												}
											}

											// Add the point cache to the list of point cache filenames
											if (sPointCache.GetLength())
												m_lstPointCaches.Add(sPointCache);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Initialize the IGame mesh
	if (g_SEOptions.bNormals || g_SEOptions.bTangents || g_SEOptions.bBinormals) {
		pIGameMesh->SetUseWeightedNormals();
		pIGameMesh->SetCreateOptimizedNormalList();
	}
	if (pIGameMesh->InitializeData()) {
		// Setup mesh vertex and triangle buffer
		int nNumOfFaces      = pIGameMesh->GetNumberOfFaces();
		int nMaxMeshVertices = nNumOfFaces*3; // Worst case :)
		if (m_pScene->m_nMaxMeshVertices < nMaxMeshVertices) {
			delete [] m_pScene->m_pMeshVertices;
			m_pScene->m_pMeshVertices    = new Vertex[nMaxMeshVertices];
			m_pScene->m_nMaxMeshVertices = nMaxMeshVertices;
		}
		if (m_pScene->m_nMaxMeshTriangles < nNumOfFaces) {
			delete [] m_pScene->m_pMeshTriangles;
			m_pScene->m_pMeshTriangles    = new Triangle[nNumOfFaces];
			m_pScene->m_nMaxMeshTriangles = nNumOfFaces;
		}

		// If your mesh hash map was already used, clear it right now
		if (m_pScene->m_bVHTableUsed)
			m_pScene->m_pVHTable->Clear();

		// Has this mesh a material?
		IGameMaterial *pIGameMaterial = m_pIGameNode->GetNodeMaterial();
		if (!pIGameMaterial)
			g_pLog->LogFLine(PLLog::Hint, "Mesh '%s' has no material! Creating fallback material...", m_sName.c_str());

		// Add vertices
		// Loop through all faces
		for (int nFace=0; nFace<nNumOfFaces; nFace++) {
			const FaceEx *pFace = pIGameMesh->GetFace(nFace);
			if (pFace) {
				// Add triangle
				Triangle &cTriangle = m_pScene->m_pMeshTriangles[m_nNumOfTriangles++];

				// Find and set correct triangle mesh material ID
				cTriangle.nMatID = AddMaterial(pIGameMaterial, GetIGameMaterial(*pIGameMesh, nFace));

				// Loop through all 3 face vertices
				for (int k=0; k<3; k++) {
					Vertex *pVertex = GetVertex(*pIGameMesh, pIGameSkin, *pFace, k, cTriangle.nMatID, nFace);
					cTriangle.v[k] = pVertex ? pVertex->nIndex : -1;
				}
			}
		}

		// 'IGameMesh.GetVertex()' can give us the vertices directly in object space, but then it can happen
		// that the transform is not correctly and I can't figure out how to fix that. (some kind of mysterious
		// object offset...)
		// So, I request the vertices in 'world space' and then I transform them into 'node space' and all
		// is fine...
		GMatrix mTransform = m_pIGameNode->GetWorldTM().Inverse();
		Quat    qRotation  = mTransform.Rotation();

		// Transform the vertex data from 'world space' to 'node space' and calculate the bounding box of
		// the mesh - I do this by hand because I just couldn't find a way to use 3ds Max and/or IGame functions
		// for this that do the job 'always' correctly :/
		m_nNumOfVertices = m_pScene->m_pVHTable->GetNumOfVertices();
		for (int i=0; i<m_nNumOfVertices; i++) {
			Vertex &cVertex = m_pScene->m_pMeshVertices[i];
			cVertex.xyz = cVertex.xyz*mTransform;
			m_cLocalBox += cVertex.xyz;

			// Export tangents? (red = x/u)
			if (g_SEOptions.bTangents) {
				PLTools::Rotate(qRotation, cVertex.vTangent);
				cVertex.vTangent.Unify();
			}

			// Export binormals? (green = y/v)
			if (g_SEOptions.bBinormals) {
				PLTools::Rotate(qRotation, cVertex.vBinormal);
				cVertex.vBinormal.Unify();

				// We need to flip this axis
				cVertex.vBinormal = -cVertex.vBinormal;
			}

			// Export normals? (blue = z/w)
			if (g_SEOptions.bNormals) {
				PLTools::Rotate(qRotation, cVertex.vNormal);
				cVertex.vNormal.Unify();
			}
		}

		// Get the total number of vertex weights
		for (int i=0; i<m_nNumOfVertices; i++)
			m_nTotalNumOfVertexWeights += m_pScene->m_pMeshVertices[i].nNumOfWeights;

		// Setup geometries
		int nGeoIndices = 0;
		m_nNumOfGeometries = m_lstMaterials.GetNumOfElements();
		if (m_pScene->m_nMaxMeshGeometries < m_nNumOfGeometries) {
			delete [] m_pScene->m_pMeshGeometries;
			m_pScene->m_pMeshGeometries    = new Geometry[m_nNumOfGeometries];
			m_pScene->m_nMaxMeshGeometries = m_nNumOfGeometries;
		}
		int nGeo = 0;
		for (uint32 nMat=0; nMat<m_lstMaterials.GetNumOfElements(); nMat++) {
			Geometry &cGeometry = m_pScene->m_pMeshGeometries[nGeo];
			cGeometry.nMaterial   = static_cast<int>(nMat);
			cGeometry.nStartIndex = nGeoIndices;
			cGeometry.nIndexSize  = 0;
			for (int i=0; i<m_nNumOfTriangles; i++) {
				if (m_pScene->m_pMeshTriangles[i].nMatID == nMat)
					cGeometry.nIndexSize += 3;
			}
			nGeoIndices += cGeometry.nIndexSize;
			if (cGeometry.nIndexSize)
				nGeo++;
		}
		m_nNumOfGeometries = nGeo;

		// Mark your mesh hash map as 'wasted'
		m_pScene->m_bVHTableUsed = true;

		// Are there any note track keys defining animations?
		INode *p3dsMaxNode = m_pIGameNode->GetMaxNode();
		if (p3dsMaxNode)
			AddNodeTrackAnimations(*p3dsMaxNode);
	} else {
		g_pLog->LogFLine(PLLog::Error, "%s: Failed to initialize the IGame mesh!", m_pIGameNode->GetName());
	}
}

/**
*  @brief
*    Returns the correct material index of a face
*/
int PLSceneMesh::GetFaceMaterialIndex(IGameMaterial *pIGameMaterial, int nFaceMaterialIndex) const
{
	if (pIGameMaterial) {
		// 3ds Max allows multiple materials to be used on a single mesh via
		// 'submaterials'. When the first submaterial is defined, the main material
		// is copied into submaterial #1, and the new submaterial because submaterial #2.
		// We have to catch the case where there's a material, but no submaterials. For this
		// case, set face always to 0.
		int nNumOfSubMaterials = pIGameMaterial->GetSubMaterialCount();
		if (nNumOfSubMaterials) {
			// SDK recommends mod'ing the material ID by the valid # of materials,
			// as sometimes a material number that's too high is returned
			nFaceMaterialIndex %= nNumOfSubMaterials;
		} else {
			// ALWAYS 0
			nFaceMaterialIndex = 0;
		}

		// Return the material index
		return nFaceMaterialIndex;
	} else {
		return -1; // No material, no material index :)
	}
}

/**
*  @brief
*    Returns a 3ds Max material
*/
IGameMaterial *PLSceneMesh::GetIGameMaterial(IGameMesh &cIGameMesh, int nFace) const
{
	IGameMaterial *pIGameMaterial = m_pIGameNode->GetNodeMaterial();
	if (pIGameMaterial) {
		// Is this a shell material used for 'backed texture'?
		if (pIGameMaterial->GetMaxMaterial() &&
			pIGameMaterial->GetMaxMaterial()->ClassID() == Class_ID(BAKE_SHELL_CLASS_ID, 0)) {
			// Ignore the material index...
			return pIGameMaterial;
		} else {
			// Let IGame do the job of getting the correct material... if we do this "by hand"
			// using 'IGameMaterial::GetSubMaterialCount()' and 'IGameMaterial::GetSubMaterial()'
			// there may occur problems when there's a multi-material with an empty slot 'between'
			// the maps - IGame ignores this slot, but inside the face material ID it's not ignored...
			return cIGameMesh.GetMaterialFromFace(nFace);
		}
	}

	// Error, no material!
	return nullptr;
}

/**
*  @brief
*    Adds a material to the mesh
*/
int PLSceneMesh::AddMaterial(IGameMaterial *pParentIGameMaterial, IGameMaterial *pIGameMaterial)
{
	// Check parameter
	if (pIGameMaterial) {
		// Is this material already within the mesh material list?
		for (uint32 i=0; i<m_lstMaterials.GetNumOfElements(); i++) {
			PLSceneMaterial *pMaterial = m_lstMaterials[i];
			if (pMaterial && pMaterial->GetIGameMaterial() &&
				pMaterial->GetIGameMaterial()->GetMaxMaterial() == pIGameMaterial->GetMaxMaterial())
				return static_cast<int>(i); // Jap, return the index of the material inside the mesh material list
		}

		// Ok, we are still here, must be a new one :)
		PLSceneMaterial *pNewMaterial = m_pScene->AddMaterial(pParentIGameMaterial, *pIGameMaterial);
		if (pNewMaterial) {
			// Is this material already within the mesh material list?
			for (uint32 i=0; i<m_lstMaterials.GetNumOfElements(); i++) {
				PLSceneMaterial *pMaterial = m_lstMaterials[i];
				if (pMaterial == pNewMaterial) {
					// Jap, return the index of the material inside the mesh material list
					m_pScene->m_sMeshStatistics.nNumOfMaterialReferences--;
					pNewMaterial->m_nReferenceCount--;
					return static_cast<int>(i);
				}
			}

			// Add the new material
			m_lstMaterials.Add(pNewMaterial);
			return static_cast<int>(m_lstMaterials.GetNumOfElements())-1;
		}
	} else {
		// We need to add a dummy material, use 'wire color' (= object color) as diffuse color
		Color cColor(0.5f, 0.5f, 0.5f);
		if (m_pIGameNode->GetMaxNode())
			cColor = Color(m_pIGameNode->GetMaxNode()->GetWireColor());

		// Get material name (and pray that there's no 'real material' with the same name!)
		char szTemp[32];
		sprintf(szTemp, "%d", cColor.toRGB());
		std::string sName = std::string("NoMaterial_WireColorFallback_") + std::string(szTemp) + ".mat";

		// Is this material already within the mesh material list?
		for (uint32 i=0; i<m_lstMaterials.GetNumOfElements(); i++) {
			PLSceneMaterial *pMaterial = m_lstMaterials[i];
			if (pMaterial && pMaterial->m_sName == sName)
				return static_cast<int>(i); // Jap, return the index of the material inside the mesh material list
		}

		// Add the new material
		PLSceneMaterial *pNewMaterial = m_pScene->AddMaterial(cColor, sName);
		if (pNewMaterial) {
			m_lstMaterials.Add(pNewMaterial);
			return static_cast<int>(m_lstMaterials.GetNumOfElements())-1;
		}
	}

	// Error!
	return -1;
}

/**
*  @brief
*    Get the vertex of a given vertex of a given face of the mesh
*/
PLSceneMesh::Vertex *PLSceneMesh::GetVertex(IGameMesh &cIGameMesh, IGameSkin *pIGameSkin, const FaceEx &cFace, int nFaceVertexId, int nMat, int nFaceId)
{
	// Check if face vertex id is valid
	if (nFaceVertexId < 0 || nFaceVertexId >= 3) {
		// Invalid face vertex id found

		// Error!
		return nullptr;
	}

	// Get vertex candidate
	Vertex *pVertexCandidate = &m_pScene->m_pMeshVertices[m_pScene->m_pVHTable->GetNumOfVertices()];
	pVertexCandidate->Reset();

	// Get vertex id
	int nVertexId = cFace.vert[nFaceVertexId];
	pVertexCandidate->nOrginal3dsMaxID = nVertexId;

	// Set the vertex position in world space
	cIGameMesh.GetVertex(nVertexId, pVertexCandidate->xyz);
	m_nOriginalNumOfVertices = cIGameMesh.GetNumberOfVerts();

	// Set the vertex normal in world space
	if (g_SEOptions.bNormals) {
		cIGameMesh.GetNormal(nFaceId, nFaceVertexId, pVertexCandidate->vNormal);

		// I don't trust IGame, so I normalize by myself...
		pVertexCandidate->vNormal.Unify();
	}

	// Binormal and tangent vector data
	int nBinormalTangentIndex = nVertexId;
	if (g_SEOptions.bTangents || g_SEOptions.bBinormals)
		nBinormalTangentIndex = cIGameMesh.GetFaceVertexTangentBinormal(nFaceId, nFaceVertexId);

	// Set the vertex tangent in world space
	if (g_SEOptions.bTangents)
		cIGameMesh.GetTangent(nBinormalTangentIndex, pVertexCandidate->vTangent);

	// Set the vertex binormal in world space
	if (g_SEOptions.bBinormals)
		cIGameMesh.GetBinormal(nBinormalTangentIndex, pVertexCandidate->vBinormal);

	// Now to the texture coordinates... first at all, get the IGame material of the face
	PLSceneMaterial *pSceneMaterial = m_lstMaterials[nMat];
	if (pSceneMaterial) {
		IGameMaterial *pIGameMaterial = pSceneMaterial->GetIGameMaterial();
		if (pIGameMaterial) {
			// Get the 3ds Max material
			Mtl *pMaxMat = pIGameMaterial->GetMaxMaterial();
			if (pMaxMat) {
				// See if it's a standard material (we need this information for a possible uv generator)
				StdMat *pMaxStandardMat = (pMaxMat->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) ? static_cast<StdMat*>(pMaxMat) : nullptr;

				// Get the active map channels
				Tab<int> lstMapNumbers = cIGameMesh.GetActiveMapChannelNum();
				for (int nMapNumber=0; nMapNumber<lstMapNumbers.Count(); nMapNumber++) {
					// Get and check the concrete map ID and check whether this texture coordinates should be exported
					int nMapID = lstMapNumbers[nMapNumber];
					if (nMapID >= 1 && nMapID <= PLSceneExportOptions::MaxTexCoords && g_SEOptions.nTexCoordComponents[nMapID-1]) {
						// Get texture coordinate indices of the current map and face
						DWORD nIndices[3];
						cIGameMesh.GetMapFaceIndex(nMapID, nFaceId, nIndices);
						DWORD nIndex = nIndices[nFaceVertexId];
						if (static_cast<int>(nIndex) < cIGameMesh.GetNumberOfMapVerts(nMapID)) {
							// Note that WE start at 0 and not at 1...
							DWORD nTexCoord = nMapID - 1;

							// Get the texture coordinate we are interested in
							if (cIGameMesh.GetMapVertex(nMapID, nIndex, pVertexCandidate->vTexCoord[nTexCoord])) {
								// If this is a standard material, is the map enabled?
								if (!pMaxStandardMat || pMaxStandardMat->MapEnabled(nMapID)) {
									// Get texture map
									Texmap *pTexMap = pMaxMat->GetSubTexmap(nMapID);

									// Check if map is valid
									if (pTexMap) {
										// Apply a possible uv generator
										StdUVGen *pStdUVGen = static_cast<StdUVGen*>(pTexMap->GetTheUVGen());
										if (pStdUVGen) {
											Matrix3 mUVTransform;
											pStdUVGen->GetUVTransform(mUVTransform);
											pVertexCandidate->vTexCoord[nTexCoord] = pVertexCandidate->vTexCoord[nTexCoord]*mUVTransform;
										}
									}
								}

								// We need to 'flip' the y component
								pVertexCandidate->vTexCoord[nTexCoord].y = 1.0f - pVertexCandidate->vTexCoord[nTexCoord].y;

								// We have texture coordinates on that texture channel
								m_bTexCoord[nTexCoord] = true;
							}
						}
					}
				}
			}
		}
	}

	// Set the number of vertex weights by default to 0
	pVertexCandidate->nNumOfWeights = 0;

	// Is there a skinning modifier? If yes, let's finally go to the vertex skinning data...
	if (pIGameSkin) {
		// Get the numbers of bones effecting the vertex
		const int nNumOfBones = pIGameSkin->GetNumberOfBones(nVertexId);

		// Loop through all bones effecting the vertex
		for (int nBone=0; nBone<nNumOfBones; nBone++) {
			// Get the weight for the bone and vertex index passed in
			const float fWeight = pIGameSkin->GetWeight(nVertexId, nBone);
			if (fWeight > 0.0f) {
				// Get the IGameNode equivalent of the bone effecting the vertex
				IGameNode *pIGameBone = pIGameSkin->GetIGameBone(nVertexId, nBone);
				if (pIGameBone) {
					// Loop through ALL bones and find the proper bone ID
					for (uint32 nBoneID=0; nBoneID<m_lstBones.GetNumOfElements(); nBoneID++) {
						// Is this the parent node?
						if (m_lstBones[nBoneID] == pIGameBone) {
							// Jap, get it's index inside our bone list
							if (pVertexCandidate->nNumOfWeights < PLSceneExportOptions::MaxVertexWeights) {
								// Set vertex weight
								Weight &cWeight = pVertexCandidate->cWeights[pVertexCandidate->nNumOfWeights];
								cWeight.fWeight = fWeight;
								cWeight.nBone   = nBoneID;

								// Update the number of vertex weights
								pVertexCandidate->nNumOfWeights++;
							} else {
								// Error, vertex weight limit (of the exporter) reached
								nBoneID = m_lstBones.GetNumOfElements();
								nBone   = nNumOfBones;
							}

							// Get us out of the loop right now!
							nBoneID = m_lstBones.GetNumOfElements();
						}
					}
				}
			}
		}
	}

	// Add vertex to list if not already in. This optimized algorithm is
	// using a hash table to keep the required time as short as possible :)
	return m_pScene->m_pVHTable->Add(*pVertexCandidate);
}

/**
* @brief
*   Adds animations defined by using node tracks
*/
void PLSceneMesh::AddNodeTrackAnimations(INode &c3dsMaxNode)
{
	// Are there any note track keys defining animations?
	if (c3dsMaxNode.HasNoteTracks()) {
		// Jap, use note track keys to get the different animations...
		const int nTicksPerFrame = GetTicksPerFrame();

		// Loop through the individual note tracks
		for (int nNoteTrack=0; nNoteTrack<c3dsMaxNode.NumNoteTracks(); nNoteTrack++) {
			DefNoteTrack *pNoteTrack = static_cast<DefNoteTrack*>(c3dsMaxNode.GetNoteTrack(nNoteTrack));

			// Loop through the keys of the note track
			for (int nKey=0; nKey<pNoteTrack->NumKeys(); nKey++) {
				const NoteKey *pNoteKey = pNoteTrack->keys[nKey];
				const MSTR    &sNote    = pNoteKey->note;

				// start
				if (!_strnicmp(sNote.data(), "start", 5)) {
					// Startup the animation
					Animation *pAnimation = new Animation;
					pAnimation->nStartTime	   = pNoteKey->time;
					pAnimation->nTicksPerFrame = nTicksPerFrame;
					MeshFile::Animation &sAnimation = pAnimation->sAnimation;
					strcpy(sAnimation.szName, &sNote.data()[6]);
					size_t nAnimationNameLength = strlen(sAnimation.szName);
					sAnimation.nStart = pNoteKey->time/nTicksPerFrame;
					sAnimation.fSpeed  = 24.0f;
					sAnimation.nFlags  = 1; // Loop

					// Loop through the keys of the note track and process the current animation
					for (int nCurrentKey=nKey+1; nCurrentKey<pNoteTrack->NumKeys() && pAnimation; nCurrentKey++) {
						const NoteKey *pCurrentNoteKey = pNoteTrack->keys[nCurrentKey];
						const MSTR    &sCurrentNote    = pCurrentNoteKey->note;

						// [TODO] Update this
/*
						// speed
						if (!_strnicmp(sCurrentNote.data(), "speed", 5)) {
							pAnimation->sAnimation.fSpeed = static_cast<float>(atof(&sCurrentNote.data()[6]));

						// flags
						} else if (!_strnicmp(sCurrentNote.data(), "flags", 5)) {
							pAnimation->sAnimation.nFlags = atoi(&sCurrentNote.data()[6]);

						// fspeed
						} else if (!_strnicmp(sCurrentNote.data(), "fspeed", 6)) {
							// Add frame speed definition
							FrameSpeed *pFrameSpeed = new FrameSpeed;
							pAnimation->lstFrameSpeed.Add(pFrameSpeed);
							pFrameSpeed->nFrameID = pNoteKey->time/nTicksPerFrame-pAnimation->sAnimation.nStart;
							pFrameSpeed->fSpeed   = static_cast<float>(atof(&sCurrentNote.data()[7]));

						// event
						} else if (!_strnicmp(sCurrentNote.data(), "event", 5)) {
							// Add event definition
							MeshFile::AnimationEvent *pEvent = new MeshFile::AnimationEvent;
							pAnimation->lstEvents.Add(pEvent);
							pEvent->m_nID	 = atoi(&sCurrentNote.data()[6]);
							pEvent->m_nFrame = pNoteKey->time/nTicksPerFrame-pAnimation->sAnimation.nStart;
*/
						// stop
						if (!_strnicmp(sCurrentNote.data(), "stop", 4)) {
							// Is this 'our' current animation?
							const char *pszName = &sCurrentNote.data()[5];
							if (!_strnicmp(sAnimation.szName, pszName, nAnimationNameLength)) {
								// Finish animation
								pAnimation->nEndTime = pNoteKey->time;
								sAnimation = pAnimation->sAnimation;
								sAnimation.nType   = 0; // [TODO] Vertex/Skeleton
								sAnimation.nEnd    = pNoteKey->time/nTicksPerFrame-sAnimation.nStart;
								sAnimation.nStart  = 0;
								sAnimation.nEvents = pAnimation->lstEvents.GetNumOfElements();

								// Done
								m_lstAnimations.Add(pAnimation);
								pAnimation = nullptr;
							}

						// Unknown note track key
						} else {
							// Ignore unknown stuff
						}
					}

					// If there still an animation in processing, reject it right now
					if (pAnimation)
						delete pAnimation;
				}
			}
		}
	}
}
