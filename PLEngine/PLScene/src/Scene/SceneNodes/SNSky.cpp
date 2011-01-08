/*********************************************************\
 *  File: SNSky.cpp                                      *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/EulerAngles.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/IndexBuffer.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLRenderer/Material/MaterialManager.h>
#include <PLMesh/Geometry.h>
#include <PLMesh/MeshManager.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodes/Loader/SkyLoader.h"
#include "PLScene/Scene/SceneNodes/SNSky.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SkyLayer)
pl_implement_class(SNSky)


//[-------------------------------------------------------]
//[ SkyLayer functions                                    ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
SkyLayer::EType SkyLayer::GetType() const
{
	return m_nType;
}

void SkyLayer::SetType(EType nValue)
{
	if (m_nType != nValue) {
		m_nType = (EType)nValue;

		// Create the sky mesh
		Mesh *pMesh = nullptr;
		MeshManager &cMeshManager = GetSky()->GetSceneContext()->GetMeshManager();
		switch (m_nType) {
			case Plane:
			{
				// Create the mesh
				pMesh = cMeshManager.Create(GetSky()->GetAbsoluteName() + "_PlaneLayer");
				MeshMorphTarget *pMorphTarget = pMesh->GetMorphTarget(0);
				if (pMorphTarget) {
					VertexBuffer *pVertexBuffer = pMorphTarget->GetVertexBuffer();
					if (pVertexBuffer) {
						pVertexBuffer->AddVertexAttribute(VertexBuffer::Position, 0, VertexBuffer::Float3);
						pVertexBuffer->AddVertexAttribute(VertexBuffer::TexCoord, 0, VertexBuffer::Float2);
						pVertexBuffer->Allocate(4);
						pMesh->AddMaterial(cMeshManager.GetRenderer()->GetRendererContext().GetMaterialManager().Create());
						if (pVertexBuffer->Lock(Lock::WriteOnly)) {
							// Setup vertices
							// 0
							float *pfVertex = (float*)pVertexBuffer->GetData(0, VertexBuffer::Position);
							pfVertex[Vector3::X] = -10000.0f;
							pfVertex[Vector3::Y] =      0.0f;
							pfVertex[Vector3::Z] = -10000.0f;

							// 1
							pfVertex = (float*)pVertexBuffer->GetData(1, VertexBuffer::Position);
							pfVertex[Vector3::X] =  10000.0f;
							pfVertex[Vector3::Y] =      0.0f;
							pfVertex[Vector3::Z] = -10000.0f;

							// 2
							pfVertex = (float*)pVertexBuffer->GetData(2, VertexBuffer::Position);
							pfVertex[Vector3::X] = 10000.0f;
							pfVertex[Vector3::Y] =     0.0f;
							pfVertex[Vector3::Z] = 10000.0f;

							// 3
							pfVertex = (float*)pVertexBuffer->GetData(3, VertexBuffer::Position);
							pfVertex[Vector3::X] = -10000.0f;
							pfVertex[Vector3::Y] =      0.0f;
							pfVertex[Vector3::Z] =  10000.0f;

							// Setup texture coordinates
							// 0
							pfVertex = (float*)pVertexBuffer->GetData(0, VertexBuffer::TexCoord);
							pfVertex[Vector2::X] = 0.0f;
							pfVertex[Vector2::Y] = 0.0f;

							// 1
							pfVertex = (float*)pVertexBuffer->GetData(1, VertexBuffer::TexCoord);
							pfVertex[Vector2::X] = 1000.0f;
							pfVertex[Vector2::Y] = 0.0f;

							// 2
							pfVertex = (float*)pVertexBuffer->GetData(2, VertexBuffer::TexCoord);
							pfVertex[Vector2::X] = 1000.0f;
							pfVertex[Vector2::Y] = 1000.0f;

							// 3
							pfVertex = (float*)pVertexBuffer->GetData(3, VertexBuffer::TexCoord);
							pfVertex[Vector2::X] = 0.0f;
							pfVertex[Vector2::Y] = 1000.0f;

							// Unlock the vertex buffer
							pVertexBuffer->Unlock();
						}
					}
				}

				// Get LOD level
				MeshLODLevel *pMeshLODLevel = pMesh->GetLODLevel(0);
				if (pMeshLODLevel) {
					// Allocate and setup index buffer
					IndexBuffer *pIndexBuffer = pMeshLODLevel->GetIndexBuffer();
					if (pIndexBuffer) {
						pIndexBuffer->Allocate(4);
						if (pIndexBuffer->Lock(Lock::WriteOnly)) {
							pIndexBuffer->SetData(0, 1);
							pIndexBuffer->SetData(1, 0);
							pIndexBuffer->SetData(2, 2);
							pIndexBuffer->SetData(3, 3);

							// Unlock the index buffer
							pIndexBuffer->Unlock();
						}

						// Create the geometry
						Array<Geometry> &lstGeometries = *pMeshLODLevel->GetGeometries();
						Geometry &cGeometry = lstGeometries.Add();
						cGeometry.SetPrimitiveType(Primitive::TriangleStrip);
						cGeometry.SetStartIndex(0);
						cGeometry.SetIndexSize(4);
					}
				}
				break;
			}

			case Cube:
				pMesh = cMeshManager.CreateMesh("PLMesh::MeshCreatorCube", true, "Order=\"1\" Dimension=\"10.0 10.0 10.0\" MultiMaterials=\"1\"");
				if (pMesh)
					pMesh->SetName(GetSky()->GetAbsoluteName() + "_CubeLayer");
				break;

			case Sphere:
				pMesh = cMeshManager.CreateMesh("PLMesh::MeshCreatorSphere", true, "Order=\"1\" Radius=\"10\" Detail=\"40\"");
				if (pMesh)
					pMesh->SetName(GetSky()->GetAbsoluteName() + "_SphereLayer");
				break;

			case Dome:
				pMesh = cMeshManager.CreateMesh("PLMesh::MeshCreatorDome", true, "Order=\"1\" Radius=\"10\"");
				if (pMesh)
					pMesh->SetName(GetSky()->GetAbsoluteName() + "_DomeLayer");
				break;

			case Cylinder:
				pMesh = cMeshManager.CreateMesh("PLMesh::MeshCreatorCylinder", true, "Order=\"1\" TopRadius=\"10.0\" Height=\"10.0\" Slices=\"20\"");
				if (pMesh)
					pMesh->SetName(GetSky()->GetAbsoluteName() + "_CylinderLayer");
				break;
		}

		// Set the new mesh
		m_pMeshHandler->SetMesh(pMesh);
	}
}

const Vector3 &SkyLayer::GetPosition() const
{
	return m_vPos;
}

void SkyLayer::SetPosition(const Vector3 &vValue)
{
	if (m_vPos != vValue) {
		m_vPos = vValue;

		// The current world matrix is now 'dirty'
		m_bRecalculateWorldMatrix = true;
	}
}

const Vector3 &SkyLayer::GetRotation() const
{
	return m_vRot;
}

void SkyLayer::SetRotation(const Vector3 &vValue)
{
	if (m_vRot != vValue) {
		m_vRot = vValue;

		// The current world matrix is now 'dirty'
		m_bRecalculateWorldMatrix = true;
	}
}

const Vector3 &SkyLayer::GetScale() const
{
	return m_vScale;
}

void SkyLayer::SetScale(const Vector3 &vValue)
{
	if (m_vScale != vValue) {
		m_vScale = vValue;

		// The current world matrix is now 'dirty'
		m_bRecalculateWorldMatrix = true;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
SkyLayer::~SkyLayer()
{
	delete m_pMeshHandler;
}

/**
*  @brief
*    Returns the sky this sky layer is in
*/
SNSky *SkyLayer::GetSky() const
{
	return (SNSky*)GetManager();
}

/**
*  @brief
*    Returns the sky layer mesh handler
*/
MeshHandler *SkyLayer::GetMeshHandler() const
{
	return m_pMeshHandler;
}

/**
*  @brief
*    Loads a material
*/
bool SkyLayer::LoadMaterial(const String &sFilename, uint32 nMaterial)
{
	// Check material ID
	if (nMaterial >= m_pMeshHandler->GetNumOfMaterials())
		return false; // Error!

	// Load the material
	return m_pMeshHandler->SetMaterial(nMaterial, GetSky()->GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(sFilename));
}

/**
*  @brief
*    Returns the current final transform matrix
*/
const Matrix3x4 &SkyLayer::GetTransformMatrix()
{
	// Recalculate the world matrix?
	if (m_bRecalculateWorldMatrix) {
		// Set rotation
		Quaternion qRotation;
		EulerAngles::ToQuaternion(float(m_vRot.x*Math::DegToRad), float(m_vRot.y*Math::DegToRad), float(m_vRot.z*Math::DegToRad), qRotation);

		// Set position and rotation
		m_mTrans.FromQuatTrans(qRotation, m_vPos);

		// Apply scale
		Matrix3x4 mScale;
		mScale.SetScaleMatrix(m_vScale);
		m_mTrans *= mScale;

		// Recalculation done
		m_bRecalculateWorldMatrix = false;
	}

	// Return the world matrix
	return m_mTrans;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SkyLayer::SkyLayer(const String &sName, ElementManager<SkyLayer> *pManager) : Element<SkyLayer>(sName, pManager),
	Type(this),
	Position(this),
	Rotation(this),
	Scale(this),
	Name(this),
	m_nType(Unknown),
	m_vScale(1.0f, 1.0f, 1.0f),
	m_pMeshHandler(new MeshHandler()),
	m_bRecalculateWorldMatrix(true)
{
}




//[-------------------------------------------------------]
//[ SNSky functions                                       ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNSky::SetFilename(const String &sValue)
{
	if (m_sFilename != sValue) {
		m_sFilename = sValue;
		if (IsInitialized())
			Load(m_sFilename);
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNSky::SNSky() :
	Flags(this),
	MaxDrawDistance(this),
	AABBMin(this),
	AABBMax(this),
	Filename(this),
	EventHandlerUpdate(&SNSky::NotifyUpdate, this)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoCulling);

	// Overwritten SceneNode variables
	SetAABoundingBox(AABoundingBox(Vector3(-10000.0f, -10000.0f, -10000.0f), Vector3(10000.0f, 10000.0f, 10000.0f)));

	// Set draw function flags
	SetDrawFunctionFlags(uint8(GetDrawFunctionFlags() | UseDrawPre));
}

/**
*  @brief
*    Destructor
*/
SNSky::~SNSky()
{
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNSky::DrawPre(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SceneNode::DrawPre(cRenderer, pVisNode);

	// Fixed functions suppord required
	FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
	if (pFixedFunctions) {
		// Get view matrix
		Matrix4x4 mWorld = pFixedFunctions->GetTransformState(FixedFunctions::Transform::View);
		mWorld.Invert();

		// Get sky world matrix: Set rotation and scale to zero - we only use the translation
		mWorld.xx = 1.0f; mWorld.xy = 0.0f; mWorld.xz = 0.0f;
		mWorld.yx = 0.0f; mWorld.yy = 1.0f; mWorld.yz = 0.0f;
		mWorld.zx = 0.0f; mWorld.zy = 0.0f; mWorld.zz = 1.0f;

		// Draw solid sky layers
		for (uint32 i=0; i<GetNumOfElements(); i++) {
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mWorld*((SkyLayer*)Get(i))->GetTransformMatrix());
			MeshHandler *pMeshHandler = ((SkyLayer*)Get(i))->GetMeshHandler();
			if (pMeshHandler)
				pMeshHandler->Draw();
		}

		// Draw transparent sky layers
		for (uint32 i=0; i<GetNumOfElements(); i++) {
			pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mWorld*((SkyLayer*)Get(i))->GetTransformMatrix());
			MeshHandler *pMeshHandler = ((SkyLayer*)Get(i))->GetMeshHandler();
			if (pMeshHandler)
				pMeshHandler->Draw(true);
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual SceneNode functions                   ]
//[-------------------------------------------------------]
void SNSky::InitFunction()
{
	// Call base implementation
	SceneNode::InitFunction();

	// Init data
	Load(m_sFilename);
}

void SNSky::OnActivate(bool bActivate)
{
	// Call the base implementation
	SceneNode::OnActivate(bActivate);

	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLGeneral::ElementManager functions   ]
//[-------------------------------------------------------]
SkyLayer *SNSky::CreateElement(const String &sName)
{
	return new SkyLayer(sName, this);
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool SNSky::Unload()
{
	// Cleanup the sky
	if (Clear()) {
		// Call base implementation
		return Loadable::Unload();
	} else {
		// Error!
		return false;
	}
}

String SNSky::GetLoadableTypeName() const
{
	static const String sString = "Sky";
	return sString;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::Loadable functions            ]
//[-------------------------------------------------------]
bool SNSky::CallLoadable(File &cFile, Loader &cLoader, const String &sMethod, const String &sParams)
{
	if (sParams.GetLength()) {
		cLoader.CallMethod(sMethod, "Param0=\"" + Type<SNSky&>::ConvertToString(*this) + "\" Param1=\"" + Type<File&>::ConvertToString(cFile) + "\" " + sParams);
		return true;
	} else {
		Params<bool, SNSky&, File&> cParams(*this, cFile);
		cLoader.CallMethod(sMethod, cParams);
		return cParams.Return;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNSky::NotifyUpdate()
{
	// Update sky layers
	const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();
	for (uint32 i=0; i<GetNumOfElements(); i++) {
		MeshHandler *pMeshHandler = ((SkyLayer*)Get(i))->GetMeshHandler();
		if (pMeshHandler)
			pMeshHandler->Update(fTimeDiff);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
