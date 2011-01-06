/*********************************************************\
 *  File: FixedFunctions.cpp                             *
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
#include <PLGeneral/Tools/Tools.h>
#include <PLMath/Matrix3x4.h>
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/VertexBuffer.h"
#include "PLRendererD3D9/FixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FixedFunctions::FixedFunctions(Renderer &cRendererD3D9) :
	m_pRendererD3D9(&cRendererD3D9),
	m_cColor(Color4::White),
	m_ppnTextureStageState(nullptr),
	m_ppnInternalTextureStageState(nullptr),
	m_ppCurrentVertexBuffer(nullptr),
	m_nVertexBufferOffsets(nullptr),
	m_nVertexOffset(0),
	m_bUpdateVertexDeclaration(false),
	m_pConstructedVertexDeclaration(nullptr),
	m_pConstructedDeclarations(nullptr),
	m_nNumOfVertexStreams(0)
{
	{ // Capabilities
		// Get Direct3D capabilities
		D3DCAPS9 pCaps;
		m_pRendererD3D9->GetInstance()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &pCaps);

		// Maximum number of active lights
		m_sCapabilities.nMaxActiveLights = (uint8)pCaps.MaxActiveLights;

		// Maximum number of clip planes
		m_sCapabilities.nMaxClipPlanes = (uint8)pCaps.MaxUserClipPlanes;

		// Vertex buffer fog coordinates supported?
		m_sCapabilities.bVertexBufferFogCoord = true;

		// Maximum vertex buffer streams
		m_sCapabilities.nMaxVertexBufferStreams = (uint8)pCaps.MaxStreams;
	}

	{ // Wrappers
		// Fog modes
		m_cPLE_FMWrapper.Resize(Fog::Number, false, false);
		m_cPLE_FMWrapper += D3DFOG_EXP;		//  0: Fog::Exp
		m_cPLE_FMWrapper += D3DFOG_EXP2;	//  1: Fog::Exp2
		m_cPLE_FMWrapper += D3DFOG_LINEAR;	//  2: Fog::Linear

		// Shade modes
		m_cPLE_SHADEWrapper.Resize(Shade::Number, false, false);
		m_cPLE_SHADEWrapper += D3DSHADE_FLAT;		//  0: Shade::Flat
		m_cPLE_SHADEWrapper += D3DSHADE_GOURAUD;	//  1: Shade::Smooth
	}

	{ // Renderer states
		// Set default renderer states
		// Fog
		m_nDefaultRenderState[RenderState::FogEnable]  = false;
		m_nDefaultRenderState[RenderState::FogColor]   = 0;
		m_nDefaultRenderState[RenderState::FogDensity] = Tools::FloatToUInt32(1.0f);
		m_nDefaultRenderState[RenderState::FogStart]   = Tools::FloatToUInt32(0.0f);
		m_nDefaultRenderState[RenderState::FogEnd]     = Tools::FloatToUInt32(1.0f);
		m_nDefaultRenderState[RenderState::FogMode]    = Fog::Exp;
		// Alpha test
		m_nDefaultRenderState[RenderState::AlphaTestEnable]    = false;
		m_nDefaultRenderState[RenderState::AlphaTestFunction]  = PLRenderer::Compare::GreaterEqual;
		m_nDefaultRenderState[RenderState::AlphaTestReference] = Tools::FloatToUInt32(0.5f);
		// Misc
		m_nDefaultRenderState[RenderState::Lighting]         = false;
		m_nDefaultRenderState[RenderState::Ambient]          = 0;
		m_nDefaultRenderState[RenderState::NormalizeNormals] = true;
		m_nDefaultRenderState[RenderState::ShadeMode]		 = Shade::Smooth;
	}
	MemoryManager::Set(m_nRenderState, -1, sizeof(uint32)*RenderState::Number);

	{ // Texture stage states
		// Set default texture stage states
		m_nDefaultTextureStageState[TextureStage::ColorTexEnv] = TextureEnvironment::Modulate;
		m_nDefaultTextureStageState[TextureStage::AlphaTexEnv] = TextureEnvironment::Modulate;
		m_nDefaultTextureStageState[TextureStage::TexGen]      = TexCoordGen::None;

		// Allocate texture stage states
		m_ppnTextureStageState = new uint32*[m_pRendererD3D9->GetCapabilities().nMaxTextureUnits];
		for (uint32 i=0; i<m_pRendererD3D9->GetCapabilities().nMaxTextureUnits; i++) {
			m_ppnTextureStageState[i] = new uint32[TextureStage::Number];
			MemoryManager::Set(m_ppnTextureStageState[i], -1, sizeof(uint32)*TextureStage::Number);
		}

		// Allocate internal texture stage states
		m_ppnInternalTextureStageState = new uint32*[m_pRendererD3D9->GetCapabilities().nMaxTextureUnits];
		for (uint32 i=0; i<m_pRendererD3D9->GetCapabilities().nMaxTextureUnits; i++) {
			m_ppnInternalTextureStageState[i] = new uint32[TextureStage::Number];
			MemoryManager::Set(m_ppnInternalTextureStageState[i], -1, sizeof(uint32)*TextureStage::Number);
		}
	}

	{ // Material states
		// Set default material states
		m_nDefaultMaterialState[MaterialState::Ambient]   = Color4::ToUInt32(0.2f, 0.2f, 0.2f, 1.0f);
		m_nDefaultMaterialState[MaterialState::Diffuse]   = Color4::ToUInt32(0.8f, 0.8f, 0.8f, 1.0f);
		m_nDefaultMaterialState[MaterialState::Specular]  = Color4::Black.ToUInt32();
		m_nDefaultMaterialState[MaterialState::Emission]  = Color4::Black.ToUInt32();
		m_nDefaultMaterialState[MaterialState::Shininess] = Tools::FloatToUInt32(0.0f);
	}
	MemoryManager::Set(m_nMaterialState, -1, sizeof(uint32)*MaterialState::Number);

	{ // Vertex buffer states
		// Allocate vertex buffer streams
		m_ppCurrentVertexBuffer = new PLRenderer::VertexBuffer*[m_sCapabilities.nMaxVertexBufferStreams];
		MemoryManager::Set(m_ppCurrentVertexBuffer, 0, sizeof(PLRenderer::VertexBuffer**)*m_sCapabilities.nMaxVertexBufferStreams);
		m_nVertexBufferOffsets = new uint32[m_sCapabilities.nMaxVertexBufferStreams];
		MemoryManager::Set(m_nVertexBufferOffsets, 0, sizeof(uint32)*m_sCapabilities.nMaxVertexBufferStreams);

		// Allocate dynamic vertex declarations
		m_pConstructedDeclarations = new D3DVERTEXELEMENT9[m_sCapabilities.nMaxVertexBufferStreams+1];
	}
}

/**
*  @brief
*    Destructor
*/
FixedFunctions::~FixedFunctions()
{
	{ // Texture stage states
		// Free texture stage states
		if (m_ppnTextureStageState) {
			for (uint32 i=0; i<m_pRendererD3D9->GetCapabilities().nMaxTextureUnits; i++)
				delete [] m_ppnTextureStageState[i];
			delete [] m_ppnTextureStageState;
			m_ppnTextureStageState = nullptr;
		}

		// Free internal texture stage states
		if (m_ppnInternalTextureStageState) {
			for (uint32 i=0; i<m_pRendererD3D9->GetCapabilities().nMaxTextureUnits; i++)
				delete [] m_ppnInternalTextureStageState[i];
			delete [] m_ppnInternalTextureStageState;
			m_ppnInternalTextureStageState = nullptr;
		}
	}

	{ // Vertex buffer states
		// Free vertex buffer streams
		if (m_ppCurrentVertexBuffer) {
			delete [] m_ppCurrentVertexBuffer;
			m_ppCurrentVertexBuffer = nullptr;
		}
		if (m_nVertexBufferOffsets) {
			delete [] m_nVertexBufferOffsets;
			m_nVertexBufferOffsets = nullptr;
		}

		// Destroy dynamic vertex declarations
		if (m_pConstructedDeclarations) {
			delete [] m_pConstructedDeclarations;
			m_pConstructedDeclarations = nullptr;
		}

		// Release the constructed vertex declaration
		if (m_pConstructedVertexDeclaration) {
			m_pConstructedVertexDeclaration->Release();
			m_pConstructedVertexDeclaration = nullptr;
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Updates the current D3D 9 projection matrix
*/
bool FixedFunctions::UpdateCurrentD3D9ProjectionMatrix()
{
	// Set original projection matrix
	m_mProj = m_mOriginalProj;

	// Apply z bias
	m_mProj.zz -= Tools::UInt32ToFloat(m_pRendererD3D9->GetRenderState(PLRenderer::RenderState::ZBias));

	// Flip along the y axis?
	PLRenderer::Surface *pSurface = m_pRendererD3D9->GetRenderTarget();
	if (pSurface && pSurface->IsAPISwapY()) {
		// Flip
		m_mProj.yy = -m_mProj.yy;

		// Update the cull mode render state
		const uint32 nState = m_pRendererD3D9->GetRenderState(PLRenderer::RenderState::CullMode);
		m_pRendererD3D9->SetRenderState(PLRenderer::RenderState::CullMode, nState + 1);
		m_pRendererD3D9->SetRenderState(PLRenderer::RenderState::CullMode, nState);
	}

	// Set D3D 9 matrix
	D3DXMATRIX mD3D;
	MemoryManager::Copy(&mD3D, m_mProj.fM, sizeof(float)*16);
	return (m_pRendererD3D9->GetDevice()->SetTransform(D3DTS_PROJECTION, &mD3D) == D3D_OK);
}

/**
*  @brief
*    Updates the current D3D 9 texture matrix of the given stage
*/
bool FixedFunctions::UpdateCurrentD3D9TextureMatrix(uint32 nStage)
{
	// If automatic texture generation is reflection map, we need to apply the transpose of the
	// view matrix in order to get the reflection looking correct
	if (m_ppnInternalTextureStageState[nStage][TextureStage::TexGen] == TexCoordGen::ReflectionMap) {
		Matrix4x4 mTransposed(m_mView.xx, m_mView.yx, m_mView.zx, 0.0f,
							  m_mView.xy, m_mView.yy, m_mView.zy, 0.0f,
							  m_mView.xz, m_mView.yz, m_mView.zz, 0.0f,
							  0.0f,       0.0f,       0.0f,       1.0f);
		m_mTextureMatrix[nStage] = m_mOriginalTexture[nStage]*m_mOriginalTexture[nStage];
	} else {
		m_mTextureMatrix[nStage] = m_mOriginalTexture[nStage];
	}

	// Set D3D 9 texture transform flags
	uint32 nAPITextureTransformFlags = 0;
	if (m_pRendererD3D9->GetTextureBuffer(nStage)) {
		switch (m_pRendererD3D9->GetTextureBuffer(nStage)->GetType()) {
			case PLRenderer::Resource::TypeTextureBuffer3D:
			case PLRenderer::Resource::TypeTextureBufferCube:
				nAPITextureTransformFlags = D3DTTFF_COUNT3;
				break;

			default:
				nAPITextureTransformFlags = D3DTTFF_COUNT2;
				break;
		}
	} else {
		nAPITextureTransformFlags = D3DTTFF_COUNT2;
	}
	if (m_pRendererD3D9->GetDevice()->SetTextureStageState(nStage, D3DTSS_TEXTURETRANSFORMFLAGS, nAPITextureTransformFlags) != D3D_OK)
		return false; // Error!

	// Set texture matrix
	D3DXMATRIX mD3D;
	MemoryManager::Copy(&mD3D, m_mTextureMatrix[nStage].fM, sizeof(float)*16);
	return (m_pRendererD3D9->GetDevice()->SetTransform(D3DTRANSFORMSTATETYPE(D3DTS_TEXTURE0+nStage), &mD3D) == D3D_OK);
}

/**
*  @brief
*    Set vertex declaration
*/
bool FixedFunctions::SetVertexDeclaration()
{
	// Update required?
	if (!m_bUpdateVertexDeclaration)
		return (m_nNumOfVertexStreams != 0); // Nope

	// Update
	m_bUpdateVertexDeclaration = false;

	// Is there a vertex stream?
	if (m_nNumOfVertexStreams) {
		// Is there only ONE vertex stream? If this is the case, we can use the vertex declaration of
		// the vertex buffer directly...
		if (m_nNumOfVertexStreams == 1) {
			// We can use the vertex declaration of the vertex buffer directly
			if (m_pRendererD3D9->GetDevice()->SetVertexDeclaration(((VertexBuffer*)m_ppCurrentVertexBuffer[0])->GetVertexDeclaration()) != D3D_OK)
				return false; // Error!
		} else {
			// Release the previous constructed vertex declaration
			if (m_pConstructedVertexDeclaration) {
				m_pConstructedVertexDeclaration->Release();
				m_pConstructedVertexDeclaration = nullptr;
			}

			// Construct the vertex declaration dynamically...
			uint32 nDeclaration = 0;
			// Loop through the vertex streams
			uint8 nUsageAPI;
			for (uint32 nStreamNumber=0; nStreamNumber<m_sCapabilities.nMaxVertexBufferStreams; nStreamNumber++) {
				// Get the vertex buffer of this vertex stream
				PLRenderer::VertexBuffer *pVertexBuffer = m_ppCurrentVertexBuffer[nStreamNumber];
				if (pVertexBuffer) {
					// Loop through the vertex attributes of this vertex buffer
					for (uint32 nAttribute=0; nAttribute<pVertexBuffer->GetNumOfVertexAttributes(); nAttribute++) {
						// Get the vertex attribute
						const PLRenderer::VertexBuffer::Attribute *pAttribute = pVertexBuffer->GetVertexAttribute(nAttribute);
						if (pAttribute) {
							// Get the API dependent usage
							switch (pAttribute->nSemantic) {
								case PLRenderer::VertexBuffer::Position:
									nUsageAPI = D3DDECLUSAGE_POSITION;
									break;

								case PLRenderer::VertexBuffer::BlendWeight:
									nUsageAPI = D3DDECLUSAGE_BLENDWEIGHT;
									break;

								case PLRenderer::VertexBuffer::Normal:
									nUsageAPI = D3DDECLUSAGE_NORMAL;
									break;

								case PLRenderer::VertexBuffer::Color:
									nUsageAPI = D3DDECLUSAGE_COLOR;
									break;

								case PLRenderer::VertexBuffer::FogCoord:
									nUsageAPI = D3DDECLUSAGE_FOG;
									break;

								case PLRenderer::VertexBuffer::PSize:
									nUsageAPI = D3DDECLUSAGE_PSIZE;
									break;

								case PLRenderer::VertexBuffer::BlendIndices:
									nUsageAPI = D3DDECLUSAGE_BLENDINDICES;
									break;

								case PLRenderer::VertexBuffer::TexCoord:
									nUsageAPI = D3DDECLUSAGE_TEXCOORD;
									break;

								case PLRenderer::VertexBuffer::Tangent:
									nUsageAPI = D3DDECLUSAGE_TANGENT;
									break;

								case PLRenderer::VertexBuffer::Binormal:
									nUsageAPI = D3DDECLUSAGE_BINORMAL;
									break;

								default:
									return false;	// Error!
							}

							// Set declaration
							D3DVERTEXELEMENT9 *pDecl = &m_pConstructedDeclarations[nDeclaration];
							pDecl->Stream	  = (WORD)nStreamNumber;
							pDecl->Offset	  = (WORD)pAttribute->nOffset;
							pDecl->Type		  = (uint8)pAttribute->nTypeAPI;
							pDecl->Method	  = D3DDECLMETHOD_DEFAULT;
							pDecl->Usage	  = nUsageAPI;
							pDecl->UsageIndex = (BYTE)pAttribute->nChannel;

							// Next declaration, please
							nDeclaration++;
						}
					}
				}
			}

			// End of declaration (see D3DDECL_END())
			D3DVERTEXELEMENT9 *pDecl = &m_pConstructedDeclarations[nDeclaration];
			pDecl->Stream	  = 0xFF;
			pDecl->Offset	  = 0;
			pDecl->Type		  = D3DDECLTYPE_UNUSED;
			pDecl->Method	  = 0;
			pDecl->Usage	  = 0;
			pDecl->UsageIndex = 0;

			// Create the constructed vertex declaration
			if (m_pRendererD3D9->GetDevice()->CreateVertexDeclaration(m_pConstructedDeclarations, &m_pConstructedVertexDeclaration) != D3D_OK)
				return false; // Error!

			// Set this vertex declaration
			if (m_pRendererD3D9->GetDevice()->SetVertexDeclaration(m_pConstructedVertexDeclaration) != D3D_OK)
				return false; // Error!
		}
	} else {
		// There is no vertex stream at all...
		m_pRendererD3D9->GetDevice()->SetVertexDeclaration(nullptr);

		// Error, there are no vertex streams!
		return false;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::FixedFunctions functions   ]
//[-------------------------------------------------------]
const FixedFunctions::Capabilities &FixedFunctions::GetCapabilities() const
{
	return m_sCapabilities;
}

void FixedFunctions::Reset()
{
	ResetRenderStates();
	SetColor();
	ResetTransformStates();
	ResetTextureStageStates();
	ResetMaterialStates();
	ResetLights();
	SetClipPlaneEnabled();
	SetClipPlane();
	SetVertexBuffer();
}

uint32 FixedFunctions::GetDefaultRenderState(RenderState::Enum nState) const
{
	return (nState < RenderState::Number) ? m_nDefaultRenderState[nState] : 0;
}

void FixedFunctions::ResetRenderStates()
{
	// Set renderer states to this default settings
	for (uint32 i=0; i<RenderState::Number; i++)
		SetRenderState((RenderState::Enum)i, m_nDefaultRenderState[i]);
}

int FixedFunctions::GetRenderState(RenderState::Enum nState) const
{
	// Check if the state is a valid render state member
	return (nState < RenderState::Number) ? m_nRenderState[nState] : -1;
}

bool FixedFunctions::SetRenderState(RenderState::Enum nState, uint32 nValue)
{
	// Get the D3D9 device
	LPDIRECT3DDEVICE9 pDevice = m_pRendererD3D9->GetDevice();

	// Check if the state is a valid render state member
	if (!pDevice || nState >= RenderState::Number)
		return false; // Error!

	// Check if this render state is already set to this value
	if (m_nRenderState[nState] != nValue) {
		// Set the render state
		m_nRenderState[nState] = nValue;

		// Set render state
		switch (nState) {
		// Fog
			case RenderState::FogEnable:
				if (nValue != 0 && nValue != 1)
					return false; // Error, invalid value!
				if (pDevice->SetRenderState(D3DRS_FOGENABLE, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::FogColor:
				if (pDevice->SetRenderState(D3DRS_FOGCOLOR, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::FogDensity:
				if (pDevice->SetRenderState(D3DRS_FOGDENSITY, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::FogStart:
				if (pDevice->SetRenderState(D3DRS_FOGSTART, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::FogEnd:
				if (pDevice->SetRenderState(D3DRS_FOGEND, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::FogMode:
			{
				const uint32 &nAPIValue = m_cPLE_FMWrapper[nValue];
				if (&nAPIValue != &Array<uint32>::Null) {
					if (pDevice->SetRenderState(D3DRS_FOGTABLEMODE, nAPIValue) != D3D_OK)
						return false; // Error!
				} else {
					// Error, invalid value!
					return false;
				}
				break;
			}

		// Alpha test
			case RenderState::AlphaTestEnable:
				if (nValue != 0 && nValue != 1)
					return false; // Error, invalid value!
				if (pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::AlphaTestFunction:
			{
				const uint32 &nAPIValue = m_pRendererD3D9->m_cPLE_CMPWrapper[nValue];
				if (&nAPIValue != &Array<uint32>::Null) {
					if (pDevice->SetRenderState(D3DRS_ALPHAFUNC, nAPIValue) != D3D_OK)
						return false; // Error!
				} else {
					// Error, invalid value!
					return false;
				}
				break;
			}

			case RenderState::AlphaTestReference:
				if (pDevice->SetRenderState(D3DRS_ALPHAREF, DWORD(Tools::UInt32ToFloat(nValue)*255)) != D3D_OK)
					return false; // Error!
				break;

		// Misc
			case RenderState::Lighting:
				if (nValue != 0 && nValue != 1)
					return false; // Error, invalid value!
				if (pDevice->SetRenderState(D3DRS_LIGHTING, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::Ambient:
				if (pDevice->SetRenderState(D3DRS_AMBIENT, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::NormalizeNormals:
				if (nValue != 0 && nValue != 1)
					return false; // Error, invalid value!
				if (pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, nValue) != D3D_OK)
					return false; // Error!
				break;

			case RenderState::ShadeMode:
			{
				const uint32 &nAPIValue = m_cPLE_SHADEWrapper[nValue];
				if (&nAPIValue != &Array<uint32>::Null) {
					if (pDevice->SetRenderState(D3DRS_SHADEMODE, nAPIValue) != D3D_OK)
						return false; // Error!
				} else {
					// Error, invalid value!
					return false;
				}
				break;
			}

			default:
				return false; // Error, invalid render state!
		}
	}

	// All went fine
	return true;
}

Color4 FixedFunctions::GetColor() const
{
	return m_cColor;
}

void FixedFunctions::SetColor(const Color4 &cColor)
{
	m_cColor = cColor;
}

void FixedFunctions::ResetTransformStates()
{
	// Create Direct3D identity matrix
	D3DXMATRIX mD3D;
	D3DXMatrixIdentity(&mD3D);

	// Reset projection matrix
	m_mOriginalProj.SetIdentity();
	UpdateCurrentD3D9ProjectionMatrix();

	// Reset view matrix
	m_mView.SetIdentity();
	m_pRendererD3D9->GetDevice()->SetTransform(D3DTS_VIEW, &mD3D);

	// Reset world matrix
	m_mWorld.SetIdentity();
	m_pRendererD3D9->GetDevice()->SetTransform(D3DTS_WORLD, &mD3D);

	// Reset texture matrices
	for (uint32 i=0; i<m_pRendererD3D9->GetCapabilities().nMaxTextureUnits; i++) {
		m_mOriginalTexture[i].SetIdentity();
		UpdateCurrentD3D9TextureMatrix(i);
	}
}

const Matrix4x4 &FixedFunctions::GetTransformState(Transform::Enum nState, bool bOriginal) const
{
	// Check if the state is a valid Transform::Enum member
	if (nState < Transform::Number) {
		// Get transform state
		switch (nState) {
			case Transform::Projection:
				return bOriginal ? m_mOriginalProj : m_mProj;

			case Transform::View:
				return m_mView;

			case Transform::World:
				return m_mWorld;

			default: // Texture transformation matrix
			{
				const uint32 nStage = nState - Transform::Texture0;
				if (nStage < m_pRendererD3D9->GetCapabilities().nMaxTextureUnits)
					return bOriginal ? m_mOriginalTexture[nStage] : m_mTextureMatrix[nStage];
				break;
			}
		}
	}

	// Error!
	return Matrix4x4::Identity;
}

bool FixedFunctions::SetTransformState(Transform::Enum nState, const Matrix3x4 &mTrans)
{
	// Check if the state is a valid Transform::Enum member
	if (m_pRendererD3D9->GetDevice() && nState < Transform::Number) {
		// Direct3D assumes row-major matrices and we're working with OpenGL column-major matrices
		// so we have to transpose the matrices
		D3DXMATRIX mD3D(mTrans.xx, mTrans.yx, mTrans.zx, 0.0f,
						mTrans.xy, mTrans.yy, mTrans.zy, 0.0f,
						mTrans.xz, mTrans.yz, mTrans.zz, 0.0f,
						mTrans.xw, mTrans.yw, mTrans.zw, 1.0f);

		// Set matrix, we check the matrix before setting it which gives a bit more performance
		bool bResult = true; // No error by default
		switch (nState) {
			case Transform::Projection: // Projection transformation matrix
				if (m_mOriginalProj != mTrans) {
					m_mOriginalProj = mTrans;
					bResult = UpdateCurrentD3D9ProjectionMatrix();
				}
				return bResult;

			case Transform::View: // View transformation matrix
				if (m_mView != mTrans) {
					m_mView = mTrans;
					bResult = (m_pRendererD3D9->GetDevice()->SetTransform(D3DTS_VIEW, &mD3D) == D3D_OK);
				}
				return bResult;

			case Transform::World: // World transformation matrix
				if (m_mWorld != mTrans) {
					m_mWorld = mTrans;
					bResult = (m_pRendererD3D9->GetDevice()->SetTransform(D3DTS_WORLD, &mD3D) == D3D_OK);
				}
				return bResult;

			default: // Texture transformation matrix
			{
				const uint32 nStage = nState - Transform::Texture0;
				if (nStage < m_pRendererD3D9->GetCapabilities().nMaxTextureUnits)
					return (m_mOriginalTexture[nStage] != mTrans) ? UpdateCurrentD3D9TextureMatrix(nStage) : bResult;
				break;
			}
		}
	}

	// Error!
	return false;
}

bool FixedFunctions::SetTransformState(Transform::Enum nState, const Matrix4x4 &mTrans)
{
	// Check if the state is a valid Transform::Enum member
	if (m_pRendererD3D9->GetDevice() && nState < Transform::Number) {
		// Direct3D assumes row-major matrices and we're working with OpenGL column-major matrices
		// so we have to transpose the matrices
		D3DXMATRIX mD3D;
		MemoryManager::Copy(&mD3D, mTrans.fM, sizeof(float)*16);

		// Set matrix, we check the matrix before setting it which gives a bit more performance
		switch (nState) {
			case Transform::Projection: // Projection transformation matrix
				if (m_mOriginalProj != mTrans) {
					m_mOriginalProj = mTrans;
					return UpdateCurrentD3D9ProjectionMatrix();
				} else {
					// Done
					return true;
				}

			case Transform::View: // View transformation matrix
				if (m_mView != mTrans) {
					m_mView = mTrans;
					return (m_pRendererD3D9->GetDevice()->SetTransform(D3DTS_VIEW, &mD3D) == D3D_OK);
				} else {
					// Done
					return true;
				}

			case Transform::World: // World transformation matrix
				if (m_mWorld != mTrans) {
					m_mWorld = mTrans;
					return (m_pRendererD3D9->GetDevice()->SetTransform(D3DTS_WORLD, &mD3D) == D3D_OK);
				} else {
					// Done
					return true;
				}

			default: // Texture transformation matrix
			{
				const uint32 nStage = nState - Transform::Texture0;
				if (nStage < m_pRendererD3D9->GetCapabilities().nMaxTextureUnits)
					return (m_mOriginalTexture[nStage] != mTrans) ? UpdateCurrentD3D9TextureMatrix(nStage) : true;
				break;
			}
		}
	}

	// Error!
	return false;
}

uint32 FixedFunctions::GetDefaultTextureStageState(TextureStage::Enum nState) const
{
	return (nState < TextureStage::Number) ? m_nDefaultTextureStageState[nState] : 0;
}

void FixedFunctions::ResetTextureStageStates()
{
	// Set texture stage states to this default settings
	for (uint32 nStage=0; nStage<m_pRendererD3D9->GetCapabilities().nMaxTextureUnits; nStage++) {
		for (uint32 i=0; i<TextureStage::Number; i++)
			SetTextureStageState(nStage, (TextureStage::Enum)i, m_nDefaultTextureStageState[i]);
	}
}

int FixedFunctions::GetTextureStageState(uint32 nStage, TextureStage::Enum nState) const
{
	// Check if the stage is correct and check if the state is a valid texture stage member
	return (nStage < m_pRendererD3D9->GetCapabilities().nMaxTextureUnits && nState < TextureStage::Number) ? m_ppnTextureStageState[nStage][nState] : -1;
}

// Internal helper function
void ConfigureTexEnv(LPDIRECT3DDEVICE9 pDevice, uint32 nStage,
					 FixedFunctions::TextureEnvironment::Enum nTexEnv, bool bIsRGB)
{
	D3DTEXTURESTAGESTATETYPE nCombineMode, nSource0, nSource1, nSource2;

	// Color/alpha check
	if (bIsRGB) {
		nCombineMode = D3DTSS_COLOROP;
		nSource0     = D3DTSS_COLORARG1;
		nSource1     = D3DTSS_COLORARG2;
		nSource2     = D3DTSS_COLORARG0;
	} else {
		nCombineMode = D3DTSS_ALPHAOP;
		nSource0     = D3DTSS_ALPHAARG1;
		nSource1     = D3DTSS_ALPHAARG2;
		nSource2     = D3DTSS_ALPHAARG0;
	}

	// Setup environment mode
	switch (nTexEnv) {
		case FixedFunctions::TextureEnvironment::Add:
			pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_ADD);
			pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_CURRENT);
			pDevice->SetTextureStageState(nStage, nSource1,     D3DTA_TEXTURE);
			break;

		case FixedFunctions::TextureEnvironment::Replace:
			pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_SELECTARG1);
			pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_TEXTURE);
			break;

		case FixedFunctions::TextureEnvironment::Modulate:
			pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_MODULATE);
			pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_CURRENT);
			pDevice->SetTextureStageState(nStage, nSource1,     D3DTA_TEXTURE);
			break;

		case FixedFunctions::TextureEnvironment::PassThru:
			pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_SELECTARG1);
			pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_CURRENT);
			break;

		case FixedFunctions::TextureEnvironment::Dot3:
			// Only valid for color!
			if (bIsRGB) {
				pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_DOTPRODUCT3);
				pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_CURRENT);
				pDevice->SetTextureStageState(nStage, nSource1,     D3DTA_TEXTURE);
			}
			break;

		case FixedFunctions::TextureEnvironment::Interpolate:
			pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_LERP);
			pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_TEXTURE);
			pDevice->SetTextureStageState(nStage, nSource1,     D3DTA_CURRENT);
			pDevice->SetTextureStageState(nStage, nSource2,     D3DTA_DIFFUSE);
			break;

		case FixedFunctions::TextureEnvironment::InterpolatePrimary:
			pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_LERP);
			pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_DIFFUSE);
			pDevice->SetTextureStageState(nStage, nSource1,     D3DTA_CURRENT);
			pDevice->SetTextureStageState(nStage, nSource2,     D3DTA_TEXTURE);
			break;

		case FixedFunctions::TextureEnvironment::InterpolateTexAlpha:
			pDevice->SetTextureStageState(nStage, nCombineMode, D3DTOP_BLENDTEXTUREALPHA);
			pDevice->SetTextureStageState(nStage, nSource0,     D3DTA_CURRENT);
			pDevice->SetTextureStageState(nStage, nSource1,     D3DTA_TEXTURE);
			break;

		default:
			break;
	}
}

bool FixedFunctions::SetTextureStageState(uint32 nStage, TextureStage::Enum nState, uint32 nValue)
{
	// Get the D3D9 device
	LPDIRECT3DDEVICE9 pDevice = m_pRendererD3D9->GetDevice();

	// Check if the stage is correct and check if the state is a valid texture stage member
	if (nStage >= m_pRendererD3D9->GetCapabilities().nMaxTextureUnits || !pDevice || nState >= TextureStage::Number)
		return false; // Error!

	// Set the texture stage state
	m_ppnTextureStageState[nStage][nState] = nValue;

	// Check if this texture stage state is already set to this value
	if (m_ppnInternalTextureStageState[nStage][nState] != nValue) {
		// Is reflection map currently active?
		const bool bReflectionMap = m_ppnInternalTextureStageState[nStage][TextureStage::TexGen] == TexCoordGen::ReflectionMap;

		// Set the texture stage state
		m_ppnInternalTextureStageState[nStage][nState] = nValue;

		// Set texture stage state
		switch (nState) {
			case TextureStage::ColorTexEnv:
				ConfigureTexEnv(pDevice, nStage, (TextureEnvironment::Enum)nValue, true);
				break;

			case TextureStage::AlphaTexEnv:
				ConfigureTexEnv(pDevice, nStage, (TextureEnvironment::Enum)nValue, false);
				break;

			case TextureStage::TexGen:
				switch (nValue) {
					case TexCoordGen::None:
						pDevice->SetTextureStageState(nStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU);
						break;

					case TexCoordGen::ObjectLinear:
						pDevice->SetTextureStageState(nStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACENORMAL);
						break;

					case TexCoordGen::EyeLinear:
						pDevice->SetTextureStageState(nStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
						break;

					case TexCoordGen::ReflectionMap:
						pDevice->SetTextureStageState(nStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR);
						break;

					case TexCoordGen::NormalMap:
						pDevice->SetTextureStageState(nStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR);
						break;

					case TexCoordGen::SphereMap:
						pDevice->SetTextureStageState(nStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_SPHEREMAP);
						break;
				}
				break;

			default:
				return false; // Error, invalid texture stage state!
		}

		// Reflection map state changed?
		if ((bReflectionMap && m_ppnInternalTextureStageState[nStage][TextureStage::TexGen] != TexCoordGen::ReflectionMap) ||
			(!bReflectionMap && m_ppnInternalTextureStageState[nStage][TextureStage::TexGen] == TexCoordGen::ReflectionMap))
			UpdateCurrentD3D9TextureMatrix(nStage);
	}

	// All went fine
	return true;
}

uint32 FixedFunctions::GetDefaultMaterialState(MaterialState::Enum nState) const
{
	return (nState < MaterialState::Number) ? m_nDefaultMaterialState[nState] : 0;
}

void FixedFunctions::ResetMaterialStates()
{
	// Set material states to this default settings
	for (uint32 i=0; i<MaterialState::Number; i++)
		SetMaterialState((MaterialState::Enum)i, m_nDefaultMaterialState[i]);
}

int FixedFunctions::GetMaterialState(MaterialState::Enum nState) const
{
	// Check if the state is a valid material state member
	return (nState < MaterialState::Number) ? m_nMaterialState[nState] : -1;
}

bool FixedFunctions::SetMaterialState(MaterialState::Enum nState, uint32 nValue)
{
	// Check if the state is a valid material state member
	if (nState >= MaterialState::Number)
		return false; // Error!

	// Check if this material state is already set to this value
	if (m_nMaterialState[nState] != nValue) {
		// Set the material state
		m_nMaterialState[nState] = nValue;

		// Setup Direct3D 9 material
		D3DMATERIAL9 sD3DMaterial;

		// Ambient
		nValue				   = GetMaterialState(MaterialState::Ambient);
		sD3DMaterial.Ambient.r = Color4::RedFromUInt32(nValue);
		sD3DMaterial.Ambient.g = Color4::GreenFromUInt32(nValue);
		sD3DMaterial.Ambient.b = Color4::BlueFromUInt32(nValue);
		sD3DMaterial.Ambient.a = Color4::AlphaFromUInt32(nValue);
		// Diffuse
		nValue				   = GetMaterialState(MaterialState::Diffuse);
		sD3DMaterial.Diffuse.r = Color4::RedFromUInt32(nValue);
		sD3DMaterial.Diffuse.g = Color4::GreenFromUInt32(nValue);
		sD3DMaterial.Diffuse.b = Color4::BlueFromUInt32(nValue);
		sD3DMaterial.Diffuse.a = Color4::AlphaFromUInt32(nValue);
		// Specular
		nValue					= GetMaterialState(MaterialState::Specular);
		sD3DMaterial.Specular.r = Color4::RedFromUInt32(nValue);
		sD3DMaterial.Specular.g = Color4::GreenFromUInt32(nValue);
		sD3DMaterial.Specular.b = Color4::BlueFromUInt32(nValue);
		sD3DMaterial.Specular.a = Color4::AlphaFromUInt32(nValue);
		// Emission
		nValue					= GetMaterialState(MaterialState::Emission);
		sD3DMaterial.Emissive.r = Color4::RedFromUInt32(nValue);
		sD3DMaterial.Emissive.g = Color4::GreenFromUInt32(nValue);
		sD3DMaterial.Emissive.b = Color4::BlueFromUInt32(nValue);
		sD3DMaterial.Emissive.a = Color4::AlphaFromUInt32(nValue);
		// Shininess
		sD3DMaterial.Power = Tools::UInt32ToFloat(GetMaterialState(MaterialState::Shininess));

		// Set Direct3D 9 material
		if (m_pRendererD3D9->GetDevice()->SetMaterial(&sD3DMaterial) != D3D_OK)
			return false; // Error!
	}

	// Done
	return true;
}

void FixedFunctions::GetDefaultLightSettings(Light &sLight) const
{
	sLight.nType = LightType::Point;
	sLight.cAmbient.SetRGBA(0.0f, 0.0f, 0.0f, 0.0f);
	sLight.cDiffuse.SetRGBA(0.0f, 0.0f, 0.0f, 0.0f);
	sLight.cSpecular.SetRGBA(0.0f, 0.0f, 0.0f, 0.0f);
	sLight.vPosition.SetXYZ(0.0f, 0.0f, 0.0f);
	sLight.vDirection.SetXYZ(0.0f, 0.0f, 0.0f);
	sLight.fCutOff				 = 0.0f;
	sLight.fConstantAttenuation  = 1.0f;
	sLight.fLinearAttenuation	 = 0.0f;
	sLight.fQuadraticAttenuation = 0.0f;
}

void FixedFunctions::ResetLights()
{
	// Get default light settings
	Light sLight;
	GetDefaultLightSettings(sLight);

	// Reset lights
	for (uint32 i=0; i<m_sCapabilities.nMaxActiveLights; i++) {
		SetLightEnabled(i, false);
		SetLight(i, sLight);
	}
}

bool FixedFunctions::IsLightEnabled(uint32 nLightID) const
{
	// Check if the index is correct
	if (nLightID < m_sCapabilities.nMaxActiveLights) {
		// Get light state
		BOOL bEnable;
		if (m_pRendererD3D9->GetDevice()->GetLightEnable(nLightID, &bEnable) == D3D_OK)
			return bEnable != 0;
	}

	// Error!
	return false;
}

bool FixedFunctions::SetLightEnabled(uint32 nLightID, bool bEnabled)
{
	// Check if the index is correct
	if (nLightID < m_sCapabilities.nMaxActiveLights) {
		// Enable/disable the light
		if (m_pRendererD3D9->GetDevice()->LightEnable(nLightID, bEnabled) == D3D_OK)
			return true; // Done
	}

	// Error!
	return false;
}

bool FixedFunctions::GetLight(uint32 nLightID, Light &sLight) const
{
	// Check if the index is correct
	if (nLightID < m_sCapabilities.nMaxActiveLights) {
		// Setup Direct3D 9 light
		D3DLIGHT9 sD3DLight;
		MemoryManager::Set(&sD3DLight, 0, sizeof(D3DLIGHT9));
		if (m_pRendererD3D9->GetDevice()->GetLight(nLightID, &sD3DLight) == D3D_OK) {
			// Type
			switch (sD3DLight.Type) {
				case D3DLIGHT_POINT:
					sLight.nType = LightType::Point;
					break;

				case D3DLIGHT_SPOT:
					sLight.nType = LightType::Spot;
					break;

				case D3DLIGHT_DIRECTIONAL:
					sLight.nType = LightType::Directional;
					break;

				default:
					return false; // Error!
			}
			// Ambient
			sLight.cAmbient.r = sD3DLight.Ambient.r;
			sLight.cAmbient.g = sD3DLight.Ambient.g;
			sLight.cAmbient.b = sD3DLight.Ambient.b;
			sLight.cAmbient.a = sD3DLight.Ambient.a;
			// Diffuse
			sLight.cDiffuse.r = sD3DLight.Diffuse.r;
			sLight.cDiffuse.g = sD3DLight.Diffuse.g;
			sLight.cDiffuse.b = sD3DLight.Diffuse.b;
			sLight.cDiffuse.a = sD3DLight.Diffuse.a;
			// Specular
			sLight.cSpecular.r = sD3DLight.Specular.r;
			sLight.cSpecular.g = sD3DLight.Specular.g;
			sLight.cSpecular.b = sD3DLight.Specular.b;
			sLight.cSpecular.a = sD3DLight.Specular.a;
			// Position
			sLight.vPosition.x = sD3DLight.Position.x;
			sLight.vPosition.y = sD3DLight.Position.y;
			sLight.vPosition.z = sD3DLight.Position.z;
			// Direction
			sLight.vDirection.x = sD3DLight.Direction.x;
			sLight.vDirection.y = sD3DLight.Direction.y;
			sLight.vDirection.z = sD3DLight.Direction.z;
			// Range
			sLight.fCutOff = sD3DLight.Range;
			// Attenuation0
			sLight.fConstantAttenuation = sD3DLight.Attenuation0;
			// Attenuation1
			sLight.fLinearAttenuation = sD3DLight.Attenuation1;
			// Attenuation2
			sLight.fQuadraticAttenuation = sD3DLight.Attenuation2;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool FixedFunctions::SetLight(uint32 nLightID, const Light &sLight)
{
	// Check if the index is correct
	if (nLightID >= m_sCapabilities.nMaxActiveLights)
		return false; // Error!

	// Setup Direct3D 9 light
	D3DLIGHT9 sD3DLight;
	MemoryManager::Set(&sD3DLight, 0, sizeof(D3DLIGHT9));

	// Type
	switch (sLight.nType) {
		case LightType::Point:
			sD3DLight.Type = D3DLIGHT_POINT;
			break;

		case LightType::Spot:
			sD3DLight.Type = D3DLIGHT_SPOT;
			break;

		case LightType::Directional:
			sD3DLight.Type = D3DLIGHT_DIRECTIONAL;
			break;

		default:
			return false; // Error!
	}

	// Ambient
	sD3DLight.Ambient.r = sLight.cAmbient.r;
	sD3DLight.Ambient.g = sLight.cAmbient.g;
	sD3DLight.Ambient.b = sLight.cAmbient.b;
	sD3DLight.Ambient.a = sLight.cAmbient.a;
	// Diffuse
	sD3DLight.Diffuse.r = sLight.cDiffuse.r;
	sD3DLight.Diffuse.g = sLight.cDiffuse.g;
	sD3DLight.Diffuse.b = sLight.cDiffuse.b;
	sD3DLight.Diffuse.a = sLight.cDiffuse.a;
	// Specular
	sD3DLight.Specular.r = sLight.cSpecular.r;
	sD3DLight.Specular.g = sLight.cSpecular.g;
	sD3DLight.Specular.b = sLight.cSpecular.b;
	sD3DLight.Specular.a = sLight.cSpecular.a;
	// Position
	sD3DLight.Position.x = sLight.vPosition.x;
	sD3DLight.Position.y = sLight.vPosition.y;
	sD3DLight.Position.z = sLight.vPosition.z;
	// Direction
	sD3DLight.Direction.x = sLight.vDirection.x;
	sD3DLight.Direction.y = sLight.vDirection.y;
	sD3DLight.Direction.z = sLight.vDirection.z;
	// Range
	sD3DLight.Range   = Math::Sqrt(FLT_MAX); // Do we need to set any clever value here?
	sD3DLight.Falloff = sLight.fCutOff;
	// Attenuation0
	sD3DLight.Attenuation0 = sLight.fConstantAttenuation;
	// Attenuation1
	sD3DLight.Attenuation1 = sLight.fLinearAttenuation;
	// Attenuation2
	sD3DLight.Attenuation2 = sLight.fQuadraticAttenuation;

	// Set Direct3D 9 light
	return (m_pRendererD3D9->GetDevice()->SetLight(nLightID, &sD3DLight) == D3D_OK);
}

bool FixedFunctions::IsClipPlaneEnabled(uint8 nIndex) const
{
	// Check whether the index and the device is valid
	if (nIndex >= m_sCapabilities.nMaxClipPlanes || !m_pRendererD3D9->GetDevice())
		return false;

	// Get clip plane state
	DWORD nPrev;
	m_pRendererD3D9->GetDevice()->GetRenderState(D3DRS_CLIPPLANEENABLE, &nPrev);

	// Return clip plane state
	return (nPrev & (1 << nIndex)) != 0;
}

bool FixedFunctions::SetClipPlaneEnabled(char nIndex, bool bEnable)
{
	// Set all available clip planes to this setting?
	if (nIndex < 0) {
		for (uint8 i=0; i<m_sCapabilities.nMaxClipPlanes; i++)
			SetClipPlaneEnabled(i, bEnable);
	} else {
		// Check whether the index and the device is valid
		if (nIndex >= (signed)m_sCapabilities.nMaxClipPlanes || !m_pRendererD3D9->GetDevice())
			return false; // Error!

		// Set clip plane state
		DWORD nPrev;
		m_pRendererD3D9->GetDevice()->GetRenderState(D3DRS_CLIPPLANEENABLE, &nPrev);
		if (bEnable)
			m_pRendererD3D9->GetDevice()->SetRenderState(D3DRS_CLIPPLANEENABLE, nPrev |  (1 << nIndex));
		else
			m_pRendererD3D9->GetDevice()->SetRenderState(D3DRS_CLIPPLANEENABLE, nPrev & ~(1 << nIndex));
	}

	// Done
	return true;
}

bool FixedFunctions::GetClipPlane(uint8 nIndex, float &fA, float &fB, float &fC, float &fD) const
{
	// Check whether the index and the device is valid
	if (nIndex >= m_sCapabilities.nMaxClipPlanes || !m_pRendererD3D9->GetDevice())
		return false; // Error!

	// Get the clip plane
	float fPlane[4];
	m_pRendererD3D9->GetDevice()->GetClipPlane(nIndex, fPlane);
	fA = fPlane[0];
	fB = fPlane[1];
	fC = fPlane[2];
	fD = fPlane[3];

	// Done
	return true;
}

bool FixedFunctions::SetClipPlane(char nIndex, float fA, float fB, float fC, float fD)
{
	// Set all available clip planes to this setting?
	if (nIndex < 0) {
		for (uint8 i=0; i<m_sCapabilities.nMaxClipPlanes; i++)
			SetClipPlane(i, fA, fB, fC, fD);
	} else {
		// Check whether the index and the device is valid
		if (nIndex >= (signed)m_sCapabilities.nMaxClipPlanes || !m_pRendererD3D9->GetDevice())
			return false; // Error!

		// Set the clip plane
		const float fPlane[4] = { fA, fB, fC, fD };
		m_pRendererD3D9->GetDevice()->SetClipPlane(nIndex, fPlane);
	}

	// Done
	return true;
}

PLRenderer::VertexBuffer *FixedFunctions::GetVertexBuffer(uint32 nStreamNumber, uint32 *pnOffset) const
{
	if (nStreamNumber >= m_sCapabilities.nMaxVertexBufferStreams || !m_ppCurrentVertexBuffer)
		return nullptr; // Error!
	if (pnOffset && m_nVertexBufferOffsets)
		*pnOffset = m_nVertexBufferOffsets[nStreamNumber];
	return m_ppCurrentVertexBuffer[nStreamNumber];
}

bool FixedFunctions::SetVertexBuffer(PLRenderer::VertexBuffer *pVertexBuffer, uint32 nOffset, uint32 nStreamNumber)
{
	// Valid stream number?
	if (nStreamNumber >= m_sCapabilities.nMaxVertexBufferStreams)
		return false; // Error!

	// Is this vertex buffer already set?
	if (nStreamNumber != 0) {
		if (m_ppCurrentVertexBuffer[nStreamNumber] == pVertexBuffer &&
			m_nVertexBufferOffsets[nStreamNumber] == nOffset)
			return false; // Error!
	}

	// Update the number of vertex streams
	if (m_ppCurrentVertexBuffer[nStreamNumber])
		m_nNumOfVertexStreams--;

	// Make this vertex buffer to the renderers current one
	m_nVertexBufferOffsets[nStreamNumber] = nOffset;
	PLRenderer::VertexBuffer *pT = m_ppCurrentVertexBuffer[nStreamNumber];
	m_ppCurrentVertexBuffer[nStreamNumber] = pVertexBuffer;
	m_nVertexOffset = nOffset;

	// Disable all stream sources
	if (!pVertexBuffer || !nStreamNumber) {
		for (uint32 i=1; i<m_sCapabilities.nMaxVertexBufferStreams; i++) {
			if (m_ppCurrentVertexBuffer[i])	{
				m_nNumOfVertexStreams--;
				m_ppCurrentVertexBuffer[i] = nullptr;
			}
			m_nVertexBufferOffsets[i] = 0;
		}
	}

	// Update the vertex declaration at the next draw call
	m_bUpdateVertexDeclaration = true;

	// Should an vertex buffer be set?
	if (pVertexBuffer) {
		// Yes, make it current
		if (!((VertexBuffer*)pVertexBuffer)->MakeCurrent(nStreamNumber, nOffset)) {
			m_ppCurrentVertexBuffer[nStreamNumber] = pT;

			// Error!
			return false;
		}

		// Update the number of vertex streams
		m_nNumOfVertexStreams++;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9
