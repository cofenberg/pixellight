/*********************************************************\
 *  File: SNSpotLight.cpp                                *
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
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include "PLScene/Visibility/VisNode.h"
#include "PLScene/Scene/SNSpotLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNSpotLight)


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
const Quaternion SNSpotLight::RotationOffset(-4.3711388e-008f, 0.0f, 1.0f, 0.0f);


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNSpotLight::SetRange(float fValue)
{
	// Clamp minimum range
	if (fValue < MinRange)
		fValue = MinRange;

	// Same value?
	if (GetRange() != fValue) {
		// Call base implementation
		SNPointLight::SetRange(fValue);

		// We have to recalculate some stuff
		m_nInternalLightFlags |= RecalculateBoxPlaneSet;
		m_nInternalLightFlags |= RecalculateProjectionMatrix;
		m_nInternalLightFlags |= RecalculateFrustum;

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}

float SNSpotLight::GetOuterAngle() const
{
	return m_fOuterAngle;
}

void SNSpotLight::SetOuterAngle(float fValue)
{
	// Same value?
	if (m_fOuterAngle != fValue) {
		// Set new value
		m_fOuterAngle = fValue;

		// We have to recalculate some stuff
		m_nInternalLightFlags |= RecalculateProjectionMatrix;
		m_nInternalLightFlags |= RecalculateFrustum;

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();

		// The inner angle must be smaller than the outer angle
		if (m_fInnerAngle > m_fOuterAngle)
			m_fInnerAngle = m_fOuterAngle;
	}
}

float SNSpotLight::GetInnerAngle() const
{
	return m_fInnerAngle;
}

void SNSpotLight::SetInnerAngle(float fValue)
{
	// The inner angle must be smaller than the outer angle
	m_fInnerAngle = (fValue > m_fOuterAngle) ? m_fOuterAngle : fValue;
}

float SNSpotLight::GetZNear() const
{
	return m_fZNear;
}

void SNSpotLight::SetZNear(float fValue)
{
	// Same value?
	if (m_fZNear != fValue) {
		m_fZNear = fValue;

		// We have to recalculate some stuff
		m_nInternalLightFlags |= RecalculateBoxPlaneSet;
		m_nInternalLightFlags |= RecalculateProjectionMatrix;
		m_nInternalLightFlags |= RecalculateFrustum;
		m_nInternalLightFlags |= RecalculateFrustumVertices;

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}

float SNSpotLight::GetAspect() const
{
	return m_fAspect;
}

void SNSpotLight::SetAspect(float fValue)
{
	// Same value?
	if (m_fAspect != fValue && ((GetFlags() & NoCone) || (!(GetFlags() & NoCone) && m_fAspect != 1.0f))) {
		m_fAspect = fValue;

		// We have to recalculate some stuff
		m_nInternalLightFlags |= RecalculateBoxPlaneSet;
		m_nInternalLightFlags |= RecalculateProjectionMatrix;
		m_nInternalLightFlags |= RecalculateFrustum;
		m_nInternalLightFlags |= RecalculateFrustumVertices;

		// We have to recalculate the current axis align bounding box in 'scene node space'
		DirtyAABoundingBox();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNSpotLight::SNSpotLight() :
	OuterAngle(this),
	InnerAngle(this),
	ZNear(this),
	Aspect(this),
	Flags(this),
	DebugFlags(this),
	EventHandlerPositionRotation(&SNSpotLight::NotifyPositionRotation, this),
	m_fOuterAngle(45.0f),
	m_fInnerAngle(35.0f),
	m_fZNear(0.1f),
	m_fAspect(1.0f)
{
	// We have to recalculate some stuff
	m_nInternalLightFlags |= RecalculateProjectionMatrix;
	m_nInternalLightFlags |= RecalculateViewMatrix;
	m_nInternalLightFlags |= RecalculateFrustum;
	m_nInternalLightFlags |= RecalculateFrustumVertices;

	// Connect event handlers
	GetTransform().EventPosition.Connect(&EventHandlerPositionRotation);
	GetTransform().EventRotation.Connect(&EventHandlerPositionRotation);
}

/**
*  @brief
*    Destructor
*/
SNSpotLight::~SNSpotLight()
{
}

/**
*  @brief
*    Returns the projection matrix
*/
const Matrix4x4 &SNSpotLight::GetProjectionMatrix()
{
	// Calculate projection matrix if required
	if (m_nInternalLightFlags & RecalculateProjectionMatrix) {
		m_mProj.PerspectiveFov(static_cast<float>(m_fOuterAngle*Math::DegToRad),
							   (GetFlags() & NoCone) ? m_fAspect : 1.0f, m_fZNear, GetRange());

		// Recalculation done
		m_nInternalLightFlags &= ~RecalculateProjectionMatrix;
	}

	// Return the projection matrix
	return m_mProj;
}

/**
*  @brief
*    Returns the view matrix
*/
const Matrix3x4 &SNSpotLight::GetViewMatrix()
{
	// Calculate view matrix if required
	if (m_nInternalLightFlags & RecalculateViewMatrix) {
		// Calculate view with a 180 degree y offset (see SNSpotLight class documentation)
		m_mView.View(GetTransform().GetRotation()*RotationOffset, GetTransform().GetPosition());

		// Recalculation done
		m_nInternalLightFlags &= ~RecalculateViewMatrix;
	}

	// Return the view matrix
	return m_mView;
}

/**
*  @brief
*    Returns the spot light frustum plane set
*/
const Frustum &SNSpotLight::GetFrustum()
{
	// Calculate frustum if required
	if (m_nInternalLightFlags & RecalculateFrustum) {
		// Concatenate (multiply) the view matrix and the projection matrix
		Matrix4x4 mViewProjection = GetProjectionMatrix();
		mViewProjection *= GetViewMatrix();

		// Calculate frustum
		m_cFrustum.CreateViewPlanes(mViewProjection, true);

		// Recalculation done
		m_nInternalLightFlags &= ~RecalculateFrustum;
	}

	// Return the frustum
	return m_cFrustum;
}

/**
*  @brief
*    Returns the 8 spot light frustum vertices
*/
const Array<Vector3> &SNSpotLight::GetFrustumVertices()
{
	// Calculate frustum vertices if required
	if (m_nInternalLightFlags & RecalculateFrustumVertices) {
		// Set unit box
		m_cFrustumVertices.Resize(8);
		m_cFrustumVertices[0].SetXYZ(-1.0f, -1.0f, -1.0f);
		m_cFrustumVertices[1].SetXYZ(-1.0f,  1.0f, -1.0f);
		m_cFrustumVertices[2].SetXYZ( 1.0f,  1.0f, -1.0f);
		m_cFrustumVertices[3].SetXYZ( 1.0f, -1.0f, -1.0f);
		m_cFrustumVertices[4].SetXYZ(-1.0f, -1.0f,  1.0f);
		m_cFrustumVertices[5].SetXYZ(-1.0f,  1.0f,  1.0f);
		m_cFrustumVertices[6].SetXYZ( 1.0f,  1.0f,  1.0f);
		m_cFrustumVertices[7].SetXYZ( 1.0f, -1.0f,  1.0f);

		// Get world transform matrix with a 180 degree y offset (see SNSpotLight class documentation) and no scale
		Matrix4x4 mWorld;
		mWorld.FromQuatTrans(GetTransform().GetRotation()*RotationOffset, GetTransform().GetPosition());
		mWorld *= GetProjectionMatrix().GetInverted();

		// Project the vertices
		for (uint8 i=0; i<m_cFrustumVertices.GetNumOfElements(); i++)
			m_cFrustumVertices[i] *= mWorld;

		// Recalculation done
		m_nInternalLightFlags &= ~RecalculateFrustumVertices;
	}

	// Return the frustum vertices
	return m_cFrustumVertices;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node position or rotation changed
*/
void SNSpotLight::NotifyPositionRotation()
{
	// We have to recalculate some stuff
	m_nInternalLightFlags |= RecalculateViewMatrix;
	m_nInternalLightFlags |= RecalculateFrustum;
	m_nInternalLightFlags |= RecalculateFrustumVertices;
}


//[-------------------------------------------------------]
//[ Public virtual SNLight functions                      ]
//[-------------------------------------------------------]
bool SNSpotLight::IsSpotLight() const
{
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNSpotLight::DrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNPointLight::DrawDebug(cRenderer, pVisNode);

	// Draw anything?
	if (pVisNode && (!(GetDebugFlags() & DebugNoFrustum) || (GetDebugFlags() & DebugFrustumVertices))) {
		static const Color4 cColor(0.8f, 1.0f, 0.8f, 1.0f);

		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      GetDebugFlags() & DebugDepthTest);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, GetDebugFlags() & DebugDepthTest);

		// Draw light frustum?
		if (!(GetDebugFlags() & DebugNoFrustum)) {
			// Get the view projection matrix
			const Matrix4x4 &mViewProjection = pVisNode->GetViewProjectionMatrix();

			// Get world transform matrix with a 180 degree y offset (see SNSpotLight class documentation) and no scale
			Matrix4x4 mTransform;
			mTransform.FromQuatTrans(GetTransform().GetRotation()*RotationOffset, GetTransform().GetPosition());

			// Calculate the final render world space transform
			Matrix4x4 mWorld = pVisNode->GetParent()->GetWorldMatrix();	// Start within 'container space', this is our origin
			mWorld *= mTransform;										// Apply the 'scene node space' to 'container space' transform
			mWorld *= GetProjectionMatrix().GetInverted();				// Apply projection, the box comes a truncated cone

			// Draw
			cRenderer.GetDrawHelpers().DrawBox(cColor, Vector3::NegativeOne, Vector3::One, mViewProjection*mWorld, 1.0f);

			// Draw inner cone light frustum?
			if (!(GetFlags() & NoCone)) {
				// Calculate the projection matrix
				Matrix4x4 mProj;
				mProj.PerspectiveFov(static_cast<float>(m_fInnerAngle*Math::DegToRad), 1.0f, m_fZNear, GetRange());
				mProj.Invert();

				// Calculate the world matrix
				mWorld = pVisNode->GetParent()->GetWorldMatrix();	// Start within 'container space', this is our origin
				mWorld *= mTransform;								// Apply the 'scene node space' to 'container space' transform
				mWorld *= mProj;									// Apply projection, the box comes a truncated cone

				// Draw
				cRenderer.GetDrawHelpers().DrawBox(Color4(0.5f, 1.0f, 0.5f, 1.0f), Vector3::NegativeOne, Vector3::One, mViewProjection*mWorld, 1.0f);
			}
		}

		// Draw the frustum vertices? (there are ALWAYS 8 of them!)
		if ((GetDebugFlags() & DebugFrustumVertices) && pVisNode->GetParent()) {
			// Draw them - this points are within the 'container space'
			const Array<Vector3> &lstV = GetFrustumVertices();
			for (uint8 i=0; i<lstV.GetNumOfElements(); i++)
				cRenderer.GetDrawHelpers().DrawPoint(cColor, lstV[i], pVisNode->GetParent()->GetWorldViewProjectionMatrix(), 5.0f);
		}
	}
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNode functions                 ]
//[-------------------------------------------------------]
void SNSpotLight::UpdateAABoundingBox()
{
	const Array<Vector3> &lstVertices = GetFrustumVertices();
	if (lstVertices.GetNumOfElements()) {
		const Matrix4x4 &mInvWorld = GetTransform().GetInverseMatrix();

		// Initialize
		AABoundingBox cBox = mInvWorld*lstVertices[0];

		// Get axis aligned bounding box
		for (uint8 i=1; i<lstVertices.GetNumOfElements(); i++)
			cBox.AppendToCubicHull(mInvWorld*lstVertices[i]);

		// Set the final axis aligned bounding box
		SetAABoundingBox(cBox);
	}
}

void SNSpotLight::GetBoundingSphere(Sphere &cSphere)
{
	// The sphere has always the 'range' as radius
	cSphere.SetRadius(GetRange());

	// The sphere is always within the scene node origin
	cSphere.SetPos(GetTransform().GetPosition());
}

void SNSpotLight::GetContainerBoundingSphere(Sphere &cSphere)
{
	// The sphere has always the 'range' as radius
	cSphere.SetRadius(GetRange());

	// The sphere is always within the scene node origin
	cSphere.SetPos(GetTransform().GetPosition());
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
