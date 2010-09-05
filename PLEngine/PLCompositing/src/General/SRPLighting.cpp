/*********************************************************\
 *  File: SRPLighting.cpp                                *
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
#include <float.h>
#include <PLMath/Matrix3x3.h>
#include <PLMath/Intersect.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLRenderer/Renderer/RenderStates.h>
#include <PLRenderer/Renderer/TextureBuffer2D.h>
#include <PLRenderer/Renderer/TextureBufferCube.h>
#include <PLRenderer/Renderer/Program.h>
#include <PLRenderer/Renderer/ProgramUniform.h>
#include <PLRenderer/Renderer/ProgramAttribute.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Material/Material.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Texture/TextureManager.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Scene/SNProjectiveSpotLight.h>
#include <PLScene/Scene/SNProjectivePointLight.h>
#include <PLScene/Scene/SNCellPortal.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include <PLScene/Visibility/SQCull.h>
#include <PLScene/Visibility/VisPortal.h>
#include <PLScene/Visibility/VisContainer.h>
#include <PLScene/Compositing/ShadowMapManager.h>
#include "PLCompositing/General/SRPDirectionalLighting.h"
#include "PLCompositing/General/SRPLighting.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPLighting)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPLighting::SRPLighting() :
	TextureFiltering(this),
	ShaderLanguage(this),
	LightingIntensity(this),
	Flags(this),
	m_pProgramGenerator(NULL),
	m_pIgnoredLight(NULL)
{
}

/**
*  @brief
*    Destructor
*/
SRPLighting::~SRPLighting()
{
	// Destroy the program generator
	if (m_pProgramGenerator)
		delete m_pProgramGenerator;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets the initial render states
*/
void SRPLighting::SetInitialRenderStates(Renderer &cRenderer)
{
	// Setup render states
	cRenderer.GetRendererContext().GetEffectManager().Use();
	cRenderer.SetRenderState(RenderState::ZWriteEnable,		 false);
	cRenderer.SetRenderState(RenderState::BlendEnable,		 true);
	cRenderer.SetRenderState(RenderState::SrcBlendFunc,		 BlendFunc::One);
	cRenderer.SetRenderState(RenderState::DstBlendFunc,		 BlendFunc::One);
	cRenderer.SetRenderState(RenderState::ScissorTestEnable, true);
}

/**
*  @brief
*    Sets correct texture filtering modes
*/
void SRPLighting::SetupTextureFiltering(Renderer &cRenderer, uint32 nStage) const
{
	// Anisotropic filtering
	if (TextureFiltering > 1) {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter,     TextureFiltering::Anisotropic);
		cRenderer.SetSamplerState(nStage, Sampler::MaxAnisotropy, TextureFiltering);

	// Bilinear filtering
	} else if (TextureFiltering > 0) {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::Linear);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::Linear);

	// No filtering
	} else {
		cRenderer.SetSamplerState(nStage, Sampler::MagFilter, TextureFiltering::None);
		cRenderer.SetSamplerState(nStage, Sampler::MinFilter, TextureFiltering::None);
		cRenderer.SetSamplerState(nStage, Sampler::MipFilter, TextureFiltering::None);
	}
}

/**
*  @brief
*    Draws recursive
*/
void SRPLighting::DrawRec(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

	// Render all visible scene nodes of this scene container
	Iterator<VisNode*> cIterator = cVisContainer.GetVisNodes().GetIterator();
	while (cIterator.HasNext()) {
		// Get visibility node and scene node
		const VisNode   *pVisNode   = cIterator.Next();
			  SceneNode *pSceneNode = pVisNode->GetSceneNode();
		if (pSceneNode) {
			// Is this scene node a portal?
			if (pVisNode->IsPortal()) {
				// Get the target cell visibility container
				const VisContainer *pVisCell = ((const VisPortal*)pVisNode)->GetTargetVisContainer();
				if (pVisCell && pVisCell->GetCullQuery()) {
					// Draw the target cell
					DrawRec(cRenderer, *pVisCell->GetCullQuery());

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Draw this container without special processing
				if (((const VisContainer*)pVisNode)->GetCullQuery()) {
					DrawRec(cRenderer, *((const VisContainer*)pVisNode)->GetCullQuery());

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

			// Is this a light?
			} else if (pSceneNode->IsLight()) {
				// Use this light?
				if (pSceneNode != m_pIgnoredLight && ((SNLight*)pSceneNode)->IsRenderLight()) {
					SNLight &cLight = *((SNLight*)pSceneNode);

					// Skip black lights, they have no visible incluence!
					if (cLight.Color.Get() != Color3::Black)
						RenderLight(cRenderer, cCullQuery, cLight, *pVisNode);
				}

			// This must just be a quite boring scene node, ignore it
			} else {
			}
		}
	}
}

/**
*  @brief
*    Renders a light
*/
void SRPLighting::RenderLight(Renderer &cRenderer, const SQCull &cCullQuery, SNLight &cLight, const VisNode &cLightVisNode)
{
	// Get the shadow map manager
	ShadowMapManager *pShadowMapManager = NULL;
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext)
		pShadowMapManager = &pSceneContext->GetShadowMapManager();

	// Updates shadow maps
	if (!(GetFlags() & NoShadow) && (cLight.GetFlags() & SNLight::CastShadow) && pShadowMapManager) {
		pShadowMapManager->UpdateShadowMap(cLight, cCullQuery, cLightVisNode.GetSquaredDistanceToCamera());

		// Sets the initial render states
		SetInitialRenderStates(cRenderer);
	}

	// Is lighting allowed for this scene container?
	if (!(cCullQuery.GetSceneContainer().GetFlags() & SceneNode::NoLighting))
		RenderLightRec(cRenderer, cCullQuery, cLight, cLightVisNode, pShadowMapManager);
}

/**
*  @brief
*    Renders a light recursive
*/
void SRPLighting::RenderLightRec(Renderer &cRenderer, const SQCull &cCullQuery, SNLight &cLight, const VisNode &cLightVisNode, ShadowMapManager *pShadowMapManager)
{
	// Set cull mode
	cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);

	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Set the new scissor rectangle
	cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);

	// Render all visible scene nodes of this scene container
	Iterator<VisNode*> cIterator = cVisContainer.GetVisNodes().GetIterator();
	while (cIterator.HasNext()) {
		// Get visibility node and scene node
		const VisNode   *pVisNode   = cIterator.Next();
			  SceneNode *pSceneNode = pVisNode->GetSceneNode();

		// Is lighting allowed for this scene node?
		if (pSceneNode && !(pSceneNode->GetFlags() & SceneNode::NoLighting)) {
			// Is this scene node a portal?
			if (pVisNode->IsPortal()) {
				// Get the target cell visibility container
				const VisPortal    *pVisPortal = (const VisPortal*)pVisNode;
				const VisContainer *pVisCell   = pVisPortal->GetTargetVisContainer();
				if (pVisCell && pVisCell->GetCullQuery() && pVisPortal->GetSceneNode()) {
					// [TODO] Find a better solution without changing temporarily the light variables
					// The next thing is a little bit tricky: We need to change light variables
					// temporarily...

					// Backup the old position, rotation and scale
					Vector3    vOldPosition = cLight.GetTransform().GetPosition();
					Quaternion qOldRotation = cLight.GetTransform().GetRotation();
					Vector3    vOldScale    = cLight.GetTransform().GetScale();

					// Update position, scale and rotation using the given warp matrix of the portal
					const Matrix3x4 &mWarp = ((SNCellPortal*)pVisPortal->GetSceneNode())->GetWarpMatrix();
					// New position
					Vector3 vPosition = mWarp*vOldPosition;
					cLight.GetTransform().SetPosition(vPosition);
					// New rotation
					Quaternion qRotation = qOldRotation*mWarp;
					cLight.GetTransform().SetRotation(qRotation);
					// New scale
					Vector3 vScale = vOldScale;
					mWarp.RotateVector(vScale);
					cLight.GetTransform().SetScale(vScale);

					// Draw the target cell
					RenderLightRec(cRenderer, *pVisCell->GetCullQuery(), cLight, cLightVisNode, pShadowMapManager);

					// [TODO] Use new PLMath::Transform3 features!
					// Restore the old position, rotation and scale
					cLight.GetTransform().SetPosition(vOldPosition);
					cLight.GetTransform().SetRotation(qOldRotation);
					cLight.GetTransform().SetScale(vOldScale);

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

			// Is this scene node a container? We do not need to check for cells because we will
			// NEVER receive cells from SQCull directly, they are ONLY visible through portals! (see above)
			} else if (pVisNode->IsContainer()) {
				// Draw this container without special processing
				if (((const VisContainer*)pVisNode)->GetCullQuery()) {
					RenderLightRec(cRenderer, *((const VisContainer*)pVisNode)->GetCullQuery(), cLight, cLightVisNode, pShadowMapManager);

					// Set the previous scissor rectangle
					cRenderer.SetScissorRect(&cVisContainer.GetProjection().cRectangle);
				}

			// Is this a light, if so, ignore it
			} else if (pSceneNode->IsLight()) {

			// This must just be a quite boring scene node :)
			} else {
				// First at all, check sphere/axis aligned bounding box intersection of the used light and the scene node
				if (Intersect::SphereSphere(cLight.GetContainerBoundingSphere(), pSceneNode->GetContainerBoundingSphere()) &&
					Intersect::SphereAABox(cLight.GetContainerBoundingSphere(), pSceneNode->GetContainerAABoundingBox())) {
					// If this is a spot light, we can do another intersection test
					if (!cLight.IsSpotLight() ||
						Intersect::PlaneSetAABox(((SNSpotLight&)cLight).GetFrustum(), pSceneNode->GetContainerAABoundingBox().vMin, pSceneNode->GetContainerAABoundingBox().vMax)) {

						// Here we draw the stuff by hand in order to minimize state changes and other overhead
						const MeshHandler *pMeshHandler = pSceneNode->GetMeshHandler();
						if (pMeshHandler && pMeshHandler->GetVertexBuffer() && pMeshHandler->GetNumOfMaterials()) {
							// Get the used mesh
							const Mesh *pMesh = pMeshHandler->GetResource();
							if (pMesh) {
								// Get the mesh LOD level to use
								const MeshLODLevel *pLODLevel = pMesh->GetLODLevel(0);
								if (pLODLevel && pLODLevel->GetIndexBuffer()) {
									// Get the vertex buffer which needs at least a position attribute
									VertexBuffer *pVertexBuffer = pMeshHandler->GetVertexBuffer();
									if (pVertexBuffer && pVertexBuffer->GetVertexAttribute(VertexBuffer::Position)) {
										// Draw the mesh
										DrawMesh(cRenderer, cCullQuery, *pVisNode, *pSceneNode, *pMeshHandler, *pMesh, *pLODLevel, *pVertexBuffer, cLight, cLightVisNode, pShadowMapManager);

										// Mark this scene node as drawn
										pSceneNode->SetDrawn();
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

/**
*  @brief
*    Draws a mesh
*/
void SRPLighting::DrawMesh(Renderer &cRenderer, const SQCull &cCullQuery, const VisNode &cVisNode, SceneNode &cSceneNode, const MeshHandler &cMeshHandler, const Mesh &cMesh, const MeshLODLevel &cMeshLODLevel,
						   VertexBuffer &cVertexBuffer, SNLight &cLight, const VisNode &cLightVisNode, ShadowMapManager *pShadowMapManager)
{
	// Figure out the type of the given light
	const bool bPoint			= cLight.IsPointLight();
	const bool bProjectivePoint	= (GetFlags() & NoProjectivePointLights) ? false : (cLight.IsProjectivePointLight() && !(cLight.GetFlags() & SNProjectivePointLight::NoProjection));
	const bool bSpot			= cLight.IsSpotLight();
	const bool bProjectiveSpot	= (GetFlags() & NoProjectiveSpotLights) ? false : (cLight.IsProjectiveSpotLight() && !(cLight.GetFlags() & SNProjectiveSpotLight::NoProjection));
	const bool bDirectional		= cLight.IsDirectionalLight();

	// Get the light range
	const float fRange = bPoint ? ((SNPointLight&)cLight).GetRange() : 0.0f;

	// Skip none directional lights with a radius of <= 0, they have no visible incluence!
	if (!bDirectional && fRange <= 0.0f)
		return;	// Get us out of here right now

	// Use spot cone or even smooth spot cone for spot lights?
	bool bSpotCone       = false;
	bool bSpotSmoothCone = false;
	if (bSpot && !(cLight.GetFlags() & SNSpotLight::NoCone)) {
		// A spot cone is used
		bSpotCone = true;

		// The inner angle MUST be smaller than the outer one, else we do not use a smooth cone
		bSpotSmoothCone = ((SNSpotLight&)cLight).GetOuterAngle() > ((SNSpotLight&)cLight).GetInnerAngle();
	}

	// Get the light color
	const Color3 cLightColor = cLight.Color.Get()*LightingIntensity;

	// Shadow mapping?
	const bool bShadow = (!(GetFlags() & NoShadow) && (cLight.GetFlags() & SNLight::CastShadow) && pShadowMapManager && (pShadowMapManager->GetCubeShadowRenderTarget() || pShadowMapManager->GetSpotShadowRenderTarget()));

	// Get scene container
	const VisContainer &cVisContainer = cCullQuery.GetVisContainer();

	// Get buffers
		  IndexBuffer     *pIndexBuffer  = cMeshLODLevel.GetIndexBuffer();
	const Array<Geometry> &lstGeometries = *cMeshLODLevel.GetGeometries();

	// Bind buffers
	cRenderer.SetIndexBuffer(pIndexBuffer);

	// Get available vertex buffer attributes
	// Binormal and tangent make only sense in this usage when there's also a normal, we need all three vectors!
	const bool bHasVertexTexCoord0 = (cVertexBuffer.GetVertexAttribute(VertexBuffer::TexCoord, 0) != NULL);	// e.g. for diffuse maps
	const bool bHasVertexNormal    = (cVertexBuffer.GetVertexAttribute(VertexBuffer::Normal) != NULL);
		  bool bHasVertexTangent   = bHasVertexNormal && (cVertexBuffer.GetVertexAttribute(VertexBuffer::Tangent) != NULL);
	const bool bHasVertexBinormal  = bHasVertexTangent && (cVertexBuffer.GetVertexAttribute(VertexBuffer::Binormal) != NULL);
	if (!bHasVertexBinormal)
		bHasVertexTangent = false;

	// For better readability, define whether or not normal mapping is possible with the given vertex data
	const bool bNormalMappingPossible = bHasVertexBinormal;	// We don't need to check for all three vectors in here :D

	// Draw mesh
	for (uint32 nMat=0; nMat<cMeshHandler.GetNumOfMaterials(); nMat++) {
		// Get mesh material
		const Material *pMaterial = cMeshHandler.GetMaterial(nMat);
		if (pMaterial) {
			// Draw geometries
			bool bTwoSided = false;
			for (uint32 nGeo=0; nGeo<lstGeometries.GetNumOfElements(); nGeo++) {
				// Is this geometry active and is it using the current used mesh material?
				const Geometry &cGeometry = lstGeometries[nGeo];
				if (cGeometry.IsActive() && nMat == cGeometry.GetMaterial()) {
					// Transparent material? - Only none transparent objects can be lit by using this scene renderer pass...
					static const String sOpacity = "Opacity";
					const Parameter *pParameter = pMaterial->GetParameter(sOpacity);
					if (!pParameter || pParameter->GetValue1f() >= 1.0f) {
						// Reset the program flags
						m_cProgramFlags.Reset();

						// Set fragment shader light properties
						if (bDirectional) {
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_DIRECTIONAL)
						} else {
							if (bProjectivePoint) {
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_PROJECTIVE_POINT)
							} else {
								if (bSpot) {
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPOT)
									if (bProjectiveSpot)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPOT_PROJECTIVE)
									if (bSpotCone) {
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPOT_CONE)
										if (bSpotSmoothCone)
											PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPOT_SMOOTHCONE)
									}
								}
							}
						}

						// Shadow mapping
						TextureBuffer *pShadowMap = NULL;
						if (bShadow) {
							// Get the shadow map
							if (bSpot) {
								if (pShadowMapManager->GetSpotShadowRenderTarget())
									pShadowMap = pShadowMapManager->GetSpotShadowRenderTarget()->GetTextureBuffer();
							} else {
								if (pShadowMapManager->GetCubeShadowRenderTarget())
									pShadowMap = pShadowMapManager->GetCubeShadowRenderTarget()->GetTextureBuffer();
							}
							if (pShadowMap) {
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_SHADOWMAPPING)
								if (!(GetFlags() & NoSoftShadow))
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_SOFTSHADOWMAPPING)
							}
						}

						// Discard
						if (!(GetFlags() & NoDiscard))
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_DISCARD)

						// Normal
						if (bHasVertexNormal) {
							PL_ADD_VS_FLAG(m_cProgramFlags, VS_NORMAL)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMAL)
						}

						{ // Two sided
							static const String sTwoSided = "TwoSided";
							pParameter = pMaterial->GetParameter(sTwoSided);
							bTwoSided = (pParameter && pParameter->GetValue1f() == 1.0f);
							if (bTwoSided) {
								// We need to take care of two sided lighting
								if (bHasVertexNormal) {
									// Perform backface culling: For proper two sided lighting, we draw the
									// geometry twice, the second time with flipped vertex normals
									PL_ADD_VS_FLAG(m_cProgramFlags, VS_TWOSIDEDLIGHTING)
									cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);
								} else {
									// No lighting means that we can go the easy way: Just don't perform backface culling
									cRenderer.SetRenderState(RenderState::CullMode, Cull::None);
								}
							} else {
								// Usual backface culling
								cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);
							}
						}

						// Use gamma correction?
						if (!(GetFlags() & NoGammaCorrection))
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_GAMMACORRECTION)

						// Diffuse map and alpha reference
						float fAlphaReference = 0.0f;
						TextureBuffer *pDiffuseMap = (!bHasVertexTexCoord0 || (GetFlags() & NoDiffuseMap)) ? NULL : pMaterial->GetParameterTextureBuffer(Material::DiffuseMap);
						if (pDiffuseMap) {
							PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD0)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_DIFFUSEMAP)

							// Get alpha reference
							if (pDiffuseMap->GetComponentsPerPixel() == 4) {
								static const String sAlphaReference = "AlphaReference";
								pParameter = pMaterial->GetParameter(sAlphaReference);
								fAlphaReference = pParameter ? pParameter->GetValue1f() : 0.5f;
								if (fAlphaReference != 0.0f)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_ALPHATEST)
							}
						}

						// Diffuse ramp map
						static const String sDiffuseRampMap = "DiffuseRampMap";
						TextureBuffer *pDiffuseRampMap = (GetFlags() & NoDiffuseRampMap) ? NULL : pMaterial->GetParameterTextureBuffer(sDiffuseRampMap);
						if (pDiffuseRampMap)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_DIFFUSERAMPMAP)

						// Get index of refraction and fresnel reflection power
						float fIndexOfRefraction      = 0.0f;
						float fFresnelReflectionPower = 5.0f;
						if (!(GetFlags() & NoFresnelReflection)) {
							// IndexOfRefraction
							static const String sIndexOfRefraction = "IndexOfRefraction";
							pParameter = pMaterial->GetParameter(sIndexOfRefraction);
							if (pParameter)
								fIndexOfRefraction = pParameter->GetValue1f();
							if (fIndexOfRefraction > 0.0f) {
								// FresnelReflectionPower
								static const String sFresnelReflectionPower = "FresnelReflectionPower";
								pParameter = pMaterial->GetParameter(sFresnelReflectionPower);
								if (pParameter) {
									fFresnelReflectionPower = pParameter->GetValue1f();

									// Ensure that the value is always >0 to avoid NAN production
									if (fFresnelReflectionPower < FLT_MIN)
										fFresnelReflectionPower = FLT_MIN;
								}
							}
						}

						// Get (2D/cube) reflection map
						TextureBuffer *pReflectionMap = (GetFlags() & NoReflectionMap) ? NULL : pMaterial->GetParameterTextureBuffer(Material::ReflectionMap);
						bool b2DReflectionMap = true;
						if (pReflectionMap) {
							if (pReflectionMap->GetType() == TextureBuffer::TypeTextureBuffer2D) {
								b2DReflectionMap = true;
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_2DREFLECTIONMAP)
							} else if (pReflectionMap->GetType() == TextureBuffer::TypeTextureBufferCube) {
								b2DReflectionMap = false;
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_CUBEREFLECTIONMAP)
							} else
								pReflectionMap   = NULL; // NOT supported!
						}

						// Figure out whether or not there's reflection on this material
						const bool bReflection = (fIndexOfRefraction > 0.0f) || pReflectionMap;

						// Get reflection parameters
						TextureBuffer *pReflectivityMap = NULL;
						float fReflectivity = 1.0f;
						Color3 cReflectionColor = Color3::White;
						static const String sReflectionColor = "ReflectionColor";
						static const String sReflectivity = "Reflectivity";
						if (bReflection) {
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_REFLECTION)
							if (fIndexOfRefraction > 0.0f)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_FRESNELREFLECTION)

							// ReflectionColor
							pParameter = pMaterial->GetParameter(sReflectionColor);
							if (pParameter)
								cReflectionColor = pParameter->GetValue3fv();

							// Get reflectivity map
							if (!(GetFlags() & NoReflectivityMap)) {
								pReflectivityMap = pMaterial->GetParameterTextureBuffer(Material::ReflectivityMap);
								if (pReflectivityMap)
									PL_ADD_FS_FLAG(m_cProgramFlags, FS_REFLECTIVITYMAP)
							}

							// Get reflectivity 
							pParameter = pMaterial->GetParameter(sReflectivity);
							if (pParameter)
								fReflectivity = pParameter->GetValue1f();
						}

						// Get normal map
						TextureBuffer *pNormalMap = (!bNormalMappingPossible || (GetFlags() & NoNormalMap)) ? NULL : pMaterial->GetParameterTextureBuffer(Material::NormalMap);
						float fNormalMapBumpiness = 1.0f;
						static const String sNormalMapBumpiness = "NormalMapBumpiness";
						if (pNormalMap) {
							// Get normal map bumpiness
							const Parameter *pNormalMapParameter = pMaterial->GetParameter(sNormalMapBumpiness);
							if (pNormalMapParameter)
								fNormalMapBumpiness = pNormalMapParameter->GetValue1f();
							if (fNormalMapBumpiness != 0.0f) {
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_TEXCOORD0)
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_TANGENT_BINORMAL)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_TANGENT_BINORMAL)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP)

								// DXT5 xGxR normal map?
								pNormalMapParameter = pMaterial->GetParameter(Material::NormalMap);
								if (pNormalMapParameter) {
									const Texture *pNormalMapTexture = pNormalMapParameter->GetValueTexture();
									if (pNormalMapTexture && pNormalMapTexture->GetCompressionHint() == Texture::DXT5_xGxR)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_NORMALMAP_DXT5_XGXR)
								}
							} else {
								// The normal map has no longer an influence!
								pNormalMap = NULL;
							}
						}

						// Get detail normal map
						static const String sDetailNormalMap = "DetailNormalMap";
						TextureBuffer *pDetailNormalMap = (!pNormalMap || (GetFlags() & NoDetailNormalMap)) ? NULL : pMaterial->GetParameterTextureBuffer(sDetailNormalMap);
						float fDetailNormalMapBumpiness = 1.0f;
						Vector2 vDetailNormalMapUVScale(4.0f, 4.0f);
						static const String sDetailNormalMapBumpiness = "DetailNormalMapBumpiness";
						static const String sDetailNormalMapUVScale   = "DetailNormalMapUVScale";
						if (pDetailNormalMap) {
							// Get detail normal map bumpiness
							const Parameter *pDetailNormalMapParameter = pMaterial->GetParameter(sDetailNormalMapBumpiness);
							if (pDetailNormalMapParameter)
								fDetailNormalMapBumpiness = pDetailNormalMapParameter->GetValue1f();
							if (fDetailNormalMapBumpiness != 0.0f) {
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP)

								// Get detail normal map uv scale
								pDetailNormalMapParameter = pMaterial->GetParameter(sDetailNormalMapUVScale);
								if (pDetailNormalMapParameter)
									vDetailNormalMapUVScale = pDetailNormalMapParameter->GetValue2fv();

								// DXT5 xGxR detail normal map?
								pDetailNormalMapParameter = pMaterial->GetParameter(sDetailNormalMap);
								if (pDetailNormalMapParameter) {
									const Texture *pDetailNormalMapTexture = pDetailNormalMapParameter->GetValueTexture();
									if (pDetailNormalMapTexture && pDetailNormalMapTexture->GetCompressionHint() == Texture::DXT5_xGxR)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_DETAILNORMALMAP_DXT5_XGXR)
								}
							} else {
								// The detail normal map has no longer an influence!
								pDetailNormalMap = NULL;
							}
						}

						// Get parallax mapping settings
						float fParallax = 0.04f;
						TextureBuffer *pHeightMap = NULL;
						if (pNormalMap && !(GetFlags() & NoParallaxMapping)) {
							// Get parallax
							static const String sParallax = "Parallax";
							pParameter = pMaterial->GetParameter(sParallax);
							if (pParameter)
								pParameter->GetValue1f(fParallax);

							// Get height map
							if (fParallax != 0.0f)
								pHeightMap = pMaterial->GetParameterTextureBuffer(Material::HeightMap);

							// No height map = no parallax mapping possible
							if (pHeightMap) {
								PL_ADD_VS_FLAG(m_cProgramFlags, VS_PARALLAXMAPPING)
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_PARALLAXMAPPING)
							}
						}

						// Specular
						static const String sSpecularColor    = "SpecularColor";
						static const String sSpecularExponent = "SpecularExponent";
						Color3 cSpecularColor = Color3::White;
						TextureBuffer *pSpecularMap = NULL;
						float fSpecularExponent = 45.0f;
						if (!(GetFlags() & NoSpecular)) {
							// First, get specular color - if it's 0, we don't have any specular at all
							pParameter = pMaterial->GetParameter(sSpecularColor);
							if (pParameter)
								cSpecularColor = pParameter->GetValue3fv();
							if (cSpecularColor != 0.0f) {
								PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULAR)

								// Get specular exponent
								pParameter = pMaterial->GetParameter(sSpecularExponent);
								if (pParameter)
									pParameter->GetValue1f(fSpecularExponent);

								// Get the specular map
								if (!(GetFlags() & NoSpecularMap)) {
									pSpecularMap = pMaterial->GetParameterTextureBuffer(Material::SpecularMap);
									if (pSpecularMap)
										PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULARMAP)
								}
							}
						}

						// Specular ramp map
						static const String sSpecularRampMap = "SpecularRampMap";
						TextureBuffer *pSpecularRampMap = (!(m_cProgramFlags.GetFragmentShaderFlags() & FS_SPECULAR) || (GetFlags() & NoSpecularRampMap)) ? NULL : pMaterial->GetParameterTextureBuffer(sSpecularRampMap);
						if (pSpecularRampMap)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_SPECULARRAMPMAP)

						// Edge ramp map
						static const String sEdgeRampMap = "EdgeRampMap";
						TextureBuffer *pEdgeRampMap = (GetFlags() & NoEdgeRampMap) ? NULL : pMaterial->GetParameterTextureBuffer(sEdgeRampMap);
						if (pEdgeRampMap)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_EDGERAMPMAP)

						// Fragment shader needs texture coordinate flags, too
						if (m_cProgramFlags.GetVertexShaderFlags() & VS_TEXCOORD0)
							PL_ADD_FS_FLAG(m_cProgramFlags, FS_TEXCOORD0)

						// Get a program instance from the program generator using the given program flags
						ProgramGenerator::GeneratedProgram *pGeneratedProgram = m_pProgramGenerator->GetProgram(m_cProgramFlags);

						// Make our program to the current one
						if (pGeneratedProgram && cRenderer.SetProgram(pGeneratedProgram->pProgram)) {
							// Set pointers to uniforms & attributes of a generated program if they are not set yet
							static const String sDiffuseColor = "DiffuseColor";
							GeneratedProgramUserData *pGeneratedProgramUserData = (GeneratedProgramUserData*)pGeneratedProgram->pUserData;
							if (!pGeneratedProgramUserData) {
								pGeneratedProgram->pUserData = pGeneratedProgramUserData = new GeneratedProgramUserData;
								Program *pProgram = pGeneratedProgram->pProgram;
								// Vertex shader attributes
								static const String sVertexPosition = "VertexPosition";
								pGeneratedProgramUserData->pVertexPosition					= pProgram->GetAttribute(sVertexPosition);
								static const String sVertexTexCoord0 = "VertexTexCoord0";
								pGeneratedProgramUserData->pVertexTexCoord0					= pProgram->GetAttribute(sVertexTexCoord0);
								static const String sVertexNormal = "VertexNormal";
								pGeneratedProgramUserData->pVertexNormal					= pProgram->GetAttribute(sVertexNormal);
								static const String sVertexTangent = "VertexTangent";
								pGeneratedProgramUserData->pVertexTangent					= pProgram->GetAttribute(sVertexTangent);
								static const String sVertexBinormal = "VertexBinormal";
								pGeneratedProgramUserData->pVertexBinormal					= pProgram->GetAttribute(sVertexBinormal);
								// Vertex shader uniforms
								static const String sNormalScale = "NormalScale";
								pGeneratedProgramUserData->pNormalScale						= pProgram->GetUniform(sNormalScale);
								static const String sObjectSpaceToViewSpaceMatrix = "ObjectSpaceToViewSpaceMatrix";
								pGeneratedProgramUserData->pObjectSpaceToViewSpaceMatrix	= pProgram->GetUniform(sObjectSpaceToViewSpaceMatrix);
								static const String sObjectSpaceToClipSpaceMatrix = "ObjectSpaceToClipSpaceMatrix";
								pGeneratedProgramUserData->pObjectSpaceToClipSpaceMatrix	= pProgram->GetUniform(sObjectSpaceToClipSpaceMatrix);
								static const String sEyePos = "EyePos";
								pGeneratedProgramUserData->pEyePos							= pProgram->GetUniform(sEyePos);
								// Fragment shader uniforms
								pGeneratedProgramUserData->pDiffuseColor					= pProgram->GetUniform(sDiffuseColor);
								pGeneratedProgramUserData->pDiffuseMap						= pProgram->GetUniform(Material::DiffuseMap);
								static const String sAlphaReference = "AlphaReference";
								pGeneratedProgramUserData->pAlphaReference					= pProgram->GetUniform(sAlphaReference);
								pGeneratedProgramUserData->pDiffuseRampMap					= pProgram->GetUniform(sDiffuseRampMap);
								pGeneratedProgramUserData->pReflectionColor					= pProgram->GetUniform(sReflectionColor);
								pGeneratedProgramUserData->pReflectivity					= pProgram->GetUniform(sReflectivity);
								pGeneratedProgramUserData->pReflectivityMap					= pProgram->GetUniform(Material::ReflectivityMap);
								static const String sFresnelConstants = "FresnelConstants";
								pGeneratedProgramUserData->pFresnelConstants				= pProgram->GetUniform(sFresnelConstants);
								pGeneratedProgramUserData->pReflectionMap					= pProgram->GetUniform(Material::ReflectionMap);
								static const String sViewSpaceToWorldSpace = "ViewSpaceToWorldSpace";
								pGeneratedProgramUserData->pViewSpaceToWorldSpace			= pProgram->GetUniform(sViewSpaceToWorldSpace);
								pGeneratedProgramUserData->pNormalMap						= pProgram->GetUniform(Material::NormalMap);
								pGeneratedProgramUserData->pNormalMapBumpiness				= pProgram->GetUniform(sNormalMapBumpiness);
								pGeneratedProgramUserData->pDetailNormalMap					= pProgram->GetUniform(sDetailNormalMap);
								pGeneratedProgramUserData->pDetailNormalMapBumpiness		= pProgram->GetUniform(sDetailNormalMapBumpiness);
								pGeneratedProgramUserData->pDetailNormalMapUVScale			= pProgram->GetUniform(sDetailNormalMapUVScale);
								pGeneratedProgramUserData->pHeightMap						= pProgram->GetUniform(Material::HeightMap);
								static const String sParallaxScaleBias = "ParallaxScaleBias";
								pGeneratedProgramUserData->pParallaxScaleBias				= pProgram->GetUniform(sParallaxScaleBias);
								static const String sLightDirection = "LightDirection";
								pGeneratedProgramUserData->pLightDirection					= pProgram->GetUniform(sLightDirection);
								static const String sLightPosition = "LightPosition";
								pGeneratedProgramUserData->pLightPosition					= pProgram->GetUniform(sLightPosition);
								static const String sLightRadius = "LightRadius";
								pGeneratedProgramUserData->pLightRadius						= pProgram->GetUniform(sLightRadius);
								static const String sProjectivePointCubeMap = "ProjectivePointCubeMap";
								pGeneratedProgramUserData->pProjectivePointCubeMap			= pProgram->GetUniform(sProjectivePointCubeMap);
								static const String sViewSpaceToCubeMapSpace = "ViewSpaceToCubeMapSpace";
								pGeneratedProgramUserData->pViewSpaceToCubeMapSpace			= pProgram->GetUniform(sViewSpaceToCubeMapSpace);
								static const String sProjectiveSpotMap = "ProjectiveSpotMap";
								pGeneratedProgramUserData->pProjectiveSpotMap				= pProgram->GetUniform(sProjectiveSpotMap);
								static const String sViewSpaceToSpotMapSpace = "ViewSpaceToSpotMapSpace";
								pGeneratedProgramUserData->pViewSpaceToSpotMapSpace			= pProgram->GetUniform(sViewSpaceToSpotMapSpace);
								static const String sSpotConeCos = "SpotConeCos";
								pGeneratedProgramUserData->pSpotConeCos						= pProgram->GetUniform(sSpotConeCos);
								static const String sShadowMap = "ShadowMap";
								pGeneratedProgramUserData->pShadowMap						= pProgram->GetUniform(sShadowMap);
								static const String sViewSpaceToShadowMapSpace = "ViewSpaceToShadowMapSpace";
								pGeneratedProgramUserData->pViewSpaceToShadowMapSpace		= pProgram->GetUniform(sViewSpaceToShadowMapSpace);
								static const String sViewSpaceToShadowCubeMapSpace = "ViewSpaceToShadowCubeMapSpace";
								pGeneratedProgramUserData->pViewSpaceToShadowCubeMapSpace	= pProgram->GetUniform(sViewSpaceToShadowCubeMapSpace);
								static const String sInvLightRadius = "InvLightRadius";
								pGeneratedProgramUserData->pInvLightRadius					= pProgram->GetUniform(sInvLightRadius);
								static const String sTexelSize = "TexelSize";
								pGeneratedProgramUserData->pTexelSize						= pProgram->GetUniform(sTexelSize);
								static const String sLightColor = "LightColor";
								pGeneratedProgramUserData->pLightColor						= pProgram->GetUniform(sLightColor);
								pGeneratedProgramUserData->pSpecularColor					= pProgram->GetUniform(sSpecularColor);
								pGeneratedProgramUserData->pSpecularExponent				= pProgram->GetUniform(sSpecularExponent);
								pGeneratedProgramUserData->pSpecularMap						= pProgram->GetUniform(Material::SpecularMap);
								pGeneratedProgramUserData->pSpecularRampMap					= pProgram->GetUniform(sSpecularRampMap);
								pGeneratedProgramUserData->pEdgeRampMap						= pProgram->GetUniform(sEdgeRampMap);
							}

							// Set object space to clip space matrix uniform
							if (pGeneratedProgramUserData->pObjectSpaceToClipSpaceMatrix)
								pGeneratedProgramUserData->pObjectSpaceToClipSpaceMatrix->Set(cVisNode.GetWorldViewProjectionMatrix());

							// Set object space to view space matrix uniform
							if (pGeneratedProgramUserData->pObjectSpaceToViewSpaceMatrix)
								pGeneratedProgramUserData->pObjectSpaceToViewSpaceMatrix->Set(cVisNode.GetWorldViewMatrix());

							// Diffuse color
							if (pGeneratedProgramUserData->pDiffuseColor) {
								pParameter = pMaterial->GetParameter(sDiffuseColor);
								if (pParameter) {
									float fDiffuseColor[3] = { 1.0f, 1.0f, 1.0f };
									pParameter->GetValue3f(fDiffuseColor[0], fDiffuseColor[1], fDiffuseColor[2]);
									pGeneratedProgramUserData->pDiffuseColor->Set(fDiffuseColor[0]*LightingIntensity, fDiffuseColor[1]*LightingIntensity, fDiffuseColor[2]*LightingIntensity);
								} else {
									pGeneratedProgramUserData->pDiffuseColor->Set(LightingIntensity, LightingIntensity, LightingIntensity);
								}
							}

							// Diffuse map
							if (pGeneratedProgramUserData->pDiffuseMap) {
								const int nTextureUnit = pGeneratedProgramUserData->pDiffuseMap->Set(pDiffuseMap);
								if (nTextureUnit >= 0) {
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
									SetupTextureFiltering(cRenderer, nTextureUnit);

									// Set the "AlphaReference" fragment shader parameter
									if (pGeneratedProgramUserData->pAlphaReference)
										pGeneratedProgramUserData->pAlphaReference->Set(fAlphaReference);
								}
							}

							// Diffuse ramp map
							if (pGeneratedProgramUserData->pDiffuseRampMap) {
								const int nTextureUnit = pGeneratedProgramUserData->pDiffuseRampMap->Set(pDiffuseRampMap);
								if (nTextureUnit >= 0) {
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
									// No filtering, please
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
								}
							}

							// Set reflection parameters
							if (bReflection) {
								// Set the "ReflectionColor" fragment shader parameter
								if (pGeneratedProgramUserData->pReflectionColor)
									pGeneratedProgramUserData->pReflectionColor->Set(cReflectionColor);

								// Set the "Reflectivity" fragment shader parameter
								if (pGeneratedProgramUserData->pReflectivity)
									pGeneratedProgramUserData->pReflectivity->Set(fReflectivity);

								// Set the "ReflectivityMap" fragment shader parameter
								if (pGeneratedProgramUserData->pReflectivityMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pReflectivityMap->Set(pReflectivityMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										SetupTextureFiltering(cRenderer, nTextureUnit);
									}
								}

								// Use Fresnel reflection?
								if (pGeneratedProgramUserData->pFresnelConstants) {
									// Calculate the eta value
									// [TODO] Make the "from material" also setable per material or global?
									static const float AirIndexOfRefaction = 1.0f;
									const float fEtaValue = AirIndexOfRefaction / fIndexOfRefraction; // "from material" -> "to material"

									// Set the "FresnelConstants" fragment shader parameter
									const float fR0 = Math::Saturate(Math::Pow(1.0f - fEtaValue, 2.0f) / Math::Pow(1.0f + fEtaValue, 2.0f));

									// Set uniform
									pGeneratedProgramUserData->pFresnelConstants->Set(fR0, fFresnelReflectionPower);
								}

								// Set the "ReflectionMap" fragment shader parameter
								if (pGeneratedProgramUserData->pReflectionMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pReflectionMap->Set(pReflectionMap);
									if (nTextureUnit >= 0) {
										// Setup sampler states
										if (b2DReflectionMap) {
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										} else {
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);
										}
										SetupTextureFiltering(cRenderer, nTextureUnit);
									}
								}

								// Set the "ViewSpaceToWorldSpace" fragment shader parameter
								if (pGeneratedProgramUserData->pViewSpaceToWorldSpace && SNCamera::GetCamera()) {
									// [TODO] Add *SNCamera::GetInvViewMatrix()?
									Matrix3x3 mRot = SNCamera::GetCamera()->GetViewMatrix().GetInverted();
									pGeneratedProgramUserData->pViewSpaceToWorldSpace->Set(mRot);
								}
							}

							// Normal map
							if (pNormalMap) {
								// Set normal map
								if (pGeneratedProgramUserData->pNormalMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pNormalMap->Set(pNormalMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										SetupTextureFiltering(cRenderer, nTextureUnit);

										// Set normal map bumpiness
										if (pGeneratedProgramUserData->pNormalMapBumpiness)
											pGeneratedProgramUserData->pNormalMapBumpiness->Set(fNormalMapBumpiness);
									}
								}

								// Set detail normal map
								if (pGeneratedProgramUserData->pDetailNormalMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pDetailNormalMap->Set(pDetailNormalMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										SetupTextureFiltering(cRenderer, nTextureUnit);

										// Set detail normal map bumpiness and uv scale
										if (pGeneratedProgramUserData->pDetailNormalMapBumpiness)
											pGeneratedProgramUserData->pDetailNormalMapBumpiness->Set(fDetailNormalMapBumpiness);
										if (pGeneratedProgramUserData->pDetailNormalMapUVScale)
											pGeneratedProgramUserData->pDetailNormalMapUVScale->Set(vDetailNormalMapUVScale);
									}
								}
							}

							// Parallax mapping
							if (m_cProgramFlags.GetVertexShaderFlags() & VS_PARALLAXMAPPING) {
								// Set object space eye position
								if (pGeneratedProgramUserData->pEyePos)
									pGeneratedProgramUserData->pEyePos->Set(cVisNode.GetInverseWorldMatrix()*(cVisContainer.GetWorldMatrix()*cCullQuery.GetCameraPosition()));

								// Height map (for parallax mapping)
								if (pGeneratedProgramUserData->pHeightMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pHeightMap->Set(pHeightMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										SetupTextureFiltering(cRenderer, nTextureUnit);

										// Set parallax scale bias
										if (pGeneratedProgramUserData->pParallaxScaleBias)
											pGeneratedProgramUserData->pParallaxScaleBias->Set(fParallax, -0.02f);
									}
								}
							}

							// Directional light?
							if (bDirectional) {
								// Set normalized view space light direction vector
								if (pGeneratedProgramUserData->pLightDirection) {
									Vector3 vLightDirection = cLightVisNode.GetWorldViewMatrix().GetZAxis();
									vLightDirection.Invert();
									vLightDirection.Normalize();
									pGeneratedProgramUserData->pLightDirection->Set(vLightDirection);
								}
							} else {
								// Set the "LightPosition" fragment shader parameter
								if (pGeneratedProgramUserData->pLightPosition)
									pGeneratedProgramUserData->pLightPosition->Set(cLightVisNode.GetWorldViewMatrix().GetTranslation());

								// Set the "LightRadius" fragment shader parameter
								if (pGeneratedProgramUserData->pLightRadius)
									pGeneratedProgramUserData->pLightRadius->Set(fRange);

								// Set cube map
								if (bProjectivePoint) {
									if (pGeneratedProgramUserData->pProjectivePointCubeMap) {
										// The texture buffer we're going to project
										TextureBuffer *pCubeMap = NULL;

										// Get the projective material to use
										const Material *pProjectiveMaterial = ((SNProjectivePointLight&)cLight).GetProjectedMaterialHandler().GetResource();
										if (pProjectiveMaterial) {
											// Get the DiffuseMap-parameter of the projective material
											const Parameter *pParameter = pProjectiveMaterial->GetParameter(Material::DiffuseMap);
											if (pParameter) {
												// Get the texture we're going to project
												const Texture *pTexture = pParameter->GetValueTexture();
												if (pTexture)
													pCubeMap = pTexture->GetTextureBuffer();
											}
										}

										// Use the default cube map?
										if (!pCubeMap) {
											if (!m_cCubeMapHandler.GetResource())
												m_cCubeMapHandler.Load(cRenderer.GetRendererContext().GetTextureManager(), "Data/Textures/DefaultCubeMap.dds");
											if (m_cCubeMapHandler.GetResource())
												pCubeMap = m_cCubeMapHandler.GetResource()->GetTextureBuffer();
										}

										// Set the "ProjectivePointCubeMap" fragment shader parameter
										const int nTextureUnit = pGeneratedProgramUserData->pProjectivePointCubeMap->Set(pCubeMap);
										if (nTextureUnit >= 0) {
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
											cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressW, TextureAddressing::Wrap);
											SetupTextureFiltering(cRenderer, nTextureUnit);
										}

										// Set the "ViewSpaceToCubeMapSpace" fragment shader parameter
										if (pGeneratedProgramUserData->pViewSpaceToCubeMapSpace) {
											Matrix3x3 mRot = cLightVisNode.GetWorldViewMatrix();
											mRot.Invert();
											pGeneratedProgramUserData->pViewSpaceToCubeMapSpace->Set(mRot);
										}
									}
								} else {
									// Set spot light parameters
									if (bSpot) {
										// Set light direction in view space
										if (pGeneratedProgramUserData->pLightDirection) {
											Vector3 vLightDirection = cLightVisNode.GetWorldViewMatrix().GetZAxis();
											vLightDirection.Normalize();
											pGeneratedProgramUserData->pLightDirection->Set(vLightDirection);
										}

										// Projective spot light
										if (pGeneratedProgramUserData->pProjectiveSpotMap) {
											// The texture buffer we're going to project
											TextureBuffer *pSpotMap = NULL;

											// Get the projective material to use
											const Material *pProjectiveMaterial = ((SNProjectiveSpotLight&)cLight).GetProjectedMaterialHandler().GetResource();
											if (pProjectiveMaterial) {
												// Get the DiffuseMap-parameter of the projective material
												const Parameter *pParameter = pProjectiveMaterial->GetParameter(Material::DiffuseMap);
												if (pParameter) {
													// Get the texture we're going to project
													const Texture *pTexture = pParameter->GetValueTexture();
													if (pTexture)
														pSpotMap = pTexture->GetTextureBuffer();
												}
											}

											// Use the default spot map?
											if (!pSpotMap) {
												if (!m_cSpotMapHandler.GetResource())
													m_cSpotMapHandler.Load(cRenderer.GetRendererContext().GetTextureManager(), "Data/Textures/PLLogo.dds");
												if (m_cSpotMapHandler.GetResource())
													pSpotMap = m_cSpotMapHandler.GetResource()->GetTextureBuffer();
											}

											// Set the "ProjectiveSpotMap" fragment shader parameter
											const int nTextureUnit = pGeneratedProgramUserData->pProjectiveSpotMap->Set(pSpotMap);
											if (nTextureUnit >= 0) {
												// Do NOT use wrapping for projective textures! :)
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Border);
												cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Border);
												SetupTextureFiltering(cRenderer, nTextureUnit);
											}

											// Set the "ProjectiveSpotMap" fragment shader parameter
											if (pGeneratedProgramUserData->pViewSpaceToSpotMapSpace) {
												// This matrix brings us from clip space [-1...1] to texture space [0...1] (scale & bias)
												static const Matrix4x4 mClipSpaceToTextureSpace(0.5f, 0.0f, 0.0f, 0.5f,
																								0.0f, 0.5f, 0.0f, 0.5f,
																								0.0f, 0.0f, 0.5f, 0.5f,
																								0.0f, 0.0f, 0.0f, 1.0f);

												// Clip space [-1...1] to texture space [0...1]
												Matrix4x4 mTransform = mClipSpaceToTextureSpace;

												// View space to clip space [-1...1]
												mTransform *= ((SNProjectiveSpotLight&)cLight).GetProjectionMatrix();

												// Set the fragment shader parameter
												pGeneratedProgramUserData->pViewSpaceToSpotMapSpace->Set(mTransform*cLightVisNode.GetWorldViewMatrix().GetInverted());
											}
										}

										// Set spot light cone parameters
										if (pGeneratedProgramUserData->pSpotConeCos) {
											if (bSpotSmoothCone) {
												// Set spot light cone outer and inner angle in view space
												pGeneratedProgramUserData->pSpotConeCos->Set(float(Math::Cos(((SNSpotLight&)cLight).GetOuterAngle()*Math::DegToRad*0.5f)),
																							 float(Math::Cos(((SNSpotLight&)cLight).GetInnerAngle()*Math::DegToRad*0.5f)));

											} else {
												// Set spot light cone outer angle in view space
												pGeneratedProgramUserData->pSpotConeCos->Set(float(Math::Cos(((SNSpotLight&)cLight).GetOuterAngle()*Math::DegToRad*0.5f)));
											}
										}
									}
								}

								// Shadow map
								if (pGeneratedProgramUserData->pShadowMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pShadowMap->Set(pShadowMap);
									if (nTextureUnit >= 0) {
										// Clamp, if this is not done, we may see some artefacts
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressW,  TextureAddressing::Clamp);

										// No mipmapping, please
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Linear);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Linear);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);

										// Set the "ViewSpaceToShadowMapSpace" fragment shader parameter
										if (bSpot) {
											if (pGeneratedProgramUserData->pViewSpaceToShadowMapSpace) {
												// This matrix brings us from clip space [-1...1] to texture space [0...1] (scale & bias)
												const Matrix4x4 mClipSpaceToTextureSpace(0.5f, 0.0f, 0.0f, 0.5f,
																						 0.0f, 0.5f, 0.0f, 0.5f,
																						 0.0f, 0.0f, 0.5f, 0.5f,
																						 0.0f, 0.0f, 0.0f, 1.0f);

												// Clip space [-1...1] to texture space [0...1]
												Matrix4x4 mTransform = mClipSpaceToTextureSpace;

												// View space to clip space [-1...1]
												mTransform *= ((SNSpotLight&)cLight).GetProjectionMatrix();

												// Scene node space to view space
												mTransform *= ((SNSpotLight&)cLight).GetViewMatrix();

												// Set the fragment shader parameter
												pGeneratedProgramUserData->pViewSpaceToShadowMapSpace->Set(mTransform*cLight.GetTransform().GetMatrix()*cLightVisNode.GetWorldViewMatrix().GetInverted());
											}
										} else {
											// Set the "ViewSpaceToShadowCubeMapSpace" fragment shader parameter
											if (pGeneratedProgramUserData->pViewSpaceToShadowCubeMapSpace) {
												const Matrix3x3 mRot = cLight.GetTransform().GetMatrix()*cLightVisNode.GetWorldViewMatrix().GetInverted();
												pGeneratedProgramUserData->pViewSpaceToShadowCubeMapSpace->Set(mRot);
											}

											// Set the "InvLightRadius" fragment shader parameter
											if (pGeneratedProgramUserData->pInvLightRadius)
												pGeneratedProgramUserData->pInvLightRadius->Set(1.0f/fRange);
										}

										// Set texel size
										if (pGeneratedProgramUserData->pTexelSize) {
											float fSize = 0.0f;
											if (pShadowMap->GetType() == TextureBuffer::TypeTextureBuffer2D)
												fSize = (float)((TextureBuffer2D*)pShadowMap)->GetSize().x;
											else if (pShadowMap->GetType() == TextureBuffer::TypeTextureBufferCube)
												fSize = (float)((TextureBufferCube*)pShadowMap)->GetSize();
											pGeneratedProgramUserData->pTexelSize->Set(0.5f/fSize);
										}
									}
								}
							}

							// Set the "LightColor" fragment shader parameter
							if (pGeneratedProgramUserData->pLightColor)
								pGeneratedProgramUserData->pLightColor->Set(cLightColor);

							// Specular
							if (m_cProgramFlags.GetFragmentShaderFlags() & FS_SPECULAR) {
								// Set specular exponent and specular color
								if (pGeneratedProgramUserData->pSpecularColor)
									pGeneratedProgramUserData->pSpecularColor->Set(cSpecularColor);
								if (pGeneratedProgramUserData->pSpecularExponent)
									pGeneratedProgramUserData->pSpecularExponent->Set(fSpecularExponent);

								// Set the "SpecularMap" fragment shader parameter
								if (pGeneratedProgramUserData->pSpecularMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pSpecularMap->Set(pSpecularMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);
										SetupTextureFiltering(cRenderer, nTextureUnit);
									}
								}

								// Specular ramp map
								if (pGeneratedProgramUserData->pSpecularRampMap) {
									const int nTextureUnit = pGeneratedProgramUserData->pSpecularRampMap->Set(pSpecularRampMap);
									if (nTextureUnit >= 0) {
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
										// No filtering, please
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
										cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
									}
								}
							}

							// Set edge ramp map
							if (pGeneratedProgramUserData->pEdgeRampMap) {
								const int nTextureUnit = pGeneratedProgramUserData->pEdgeRampMap->Set(pEdgeRampMap);
								if (nTextureUnit >= 0) {
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU,  TextureAddressing::Clamp);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV,  TextureAddressing::Clamp);
									// No filtering, please
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::None);
									cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
								}
							}

							// Set program vertex attributes, this creates a connection between "Vertex Buffer Attribute" and "Vertex Shader Attribute"
							if (pGeneratedProgramUserData->pVertexPosition)
								pGeneratedProgramUserData->pVertexPosition->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Position);
							if (pGeneratedProgramUserData->pVertexTexCoord0)
								pGeneratedProgramUserData->pVertexTexCoord0->Set(&cVertexBuffer, PLRenderer::VertexBuffer::TexCoord, 0);
							if (pGeneratedProgramUserData->pVertexNormal) {
								pGeneratedProgramUserData->pVertexNormal->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Normal);
								if (m_cProgramFlags.GetFragmentShaderFlags() & FS_NORMALMAP) {
									if (pGeneratedProgramUserData->pVertexTangent)
										pGeneratedProgramUserData->pVertexTangent->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Tangent);
									if (pGeneratedProgramUserData->pVertexBinormal)
										pGeneratedProgramUserData->pVertexBinormal->Set(&cVertexBuffer, PLRenderer::VertexBuffer::Binormal);
								}
							}

							// Two sided lighting?
							if (pGeneratedProgramUserData->pNormalScale)
								pGeneratedProgramUserData->pNormalScale->Set(1.0f);

							// Draw the geometry
							cRenderer.DrawIndexedPrimitives(
								cGeometry.GetPrimitiveType(),
								0,
								cVertexBuffer.GetNumOfElements()-1,
								cGeometry.GetStartIndex(),
								cGeometry.GetIndexSize()
							);

							// If this is a two sided material, draw the primitives again - but with
							// flipped culling mode and vertex normals
							if (pGeneratedProgramUserData->pNormalScale) {
								// Flip normals
								pGeneratedProgramUserData->pNormalScale->Set(-1.0f);

								// Flip the backface culling
								cRenderer.SetRenderState(RenderState::CullMode, Cull::CW);

								// Draw geometry - again
								cRenderer.DrawIndexedPrimitives(
									cGeometry.GetPrimitiveType(),
									0,
									cVertexBuffer.GetNumOfElements()-1,
									cGeometry.GetStartIndex(),
									cGeometry.GetIndexSize()
								);
							}
						}
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPLighting::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Get the shader language to use
	String sShaderLanguage = ShaderLanguage;
	if (!sShaderLanguage.GetLength())
		sShaderLanguage = cRenderer.GetDefaultShaderLanguage();

	// Create the program generator if there's currently no instance of it
	if (!m_pProgramGenerator || m_pProgramGenerator->GetShaderLanguage() != sShaderLanguage) {
		// If there's an previous instance of the program generator, destroy it first
		if (m_pProgramGenerator) {
			delete m_pProgramGenerator;
			m_pProgramGenerator = NULL;
		}

		// Choose the shader source codes depending on the requested shader language
		String sDiffuseOnly_VS;
		String sDiffuseOnly_FS;
		if (sShaderLanguage == "GLSL") {
			#include "SRPLighting_GLSL.h"
			sDiffuseOnly_VS = sDiffuseOnly_GLSL_VS;
			sDiffuseOnly_FS = sDiffuseOnly_GLSL_FS;
		} else if (sShaderLanguage == "Cg") {
			#include "SRPLighting_Cg.h"
			sDiffuseOnly_VS = sDiffuseOnly_Cg_VS;
			sDiffuseOnly_FS = sDiffuseOnly_Cg_FS;
		}

		// Create the program generator
		if (sDiffuseOnly_VS.GetLength() && sDiffuseOnly_FS.GetLength())
			m_pProgramGenerator = new ProgramGenerator(cRenderer, sShaderLanguage, sDiffuseOnly_VS, "arbvp1", sDiffuseOnly_FS, "arbfp1", true);
	}

	// If there's no program generator, we don't need to continue
	if (m_pProgramGenerator) {
		{ // Get the instance of the "PLCompositing::SRPDirectionalLighting" scene renderer pass to ask whether or not there's a light that
		  // has already been rendered *the primary directional light source* -> we don't need to render this light again!
			static const String sClassName = "PLCompositing::SRPDirectionalLighting";
			SRPDirectionalLighting *pSRPDirectionalLighting = (SRPDirectionalLighting*)GetFirstInstanceOfSceneRendererPassClass(sClassName);
			if (pSRPDirectionalLighting)
				m_pIgnoredLight = (SNLight*)pSRPDirectionalLighting->GetUsedLight();
		}

		// Sets the initial render states
		SetInitialRenderStates(cRenderer);

		// Backup the color mask
		bool bRed, bGreen, bBlue, bAlpha;
		cRenderer.GetColorMask(bRed, bGreen, bBlue, bAlpha);

		// Don't touch the alpha channel - there may be special information for
		// e.g. post processing effects light glow or DOF, and we don't want to overwrite it!
		cRenderer.SetColorMask(true, true, true, false);

		// Draw recursive from front to back
		DrawRec(cRenderer, cCullQuery);

		// Restore the color mask
		cRenderer.SetColorMask(bRed, bGreen, bBlue, bAlpha);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
