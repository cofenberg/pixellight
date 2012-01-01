/*********************************************************\
 *  File: VertexBuffer.cpp                               *
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
#include <PLCore/System/System.h>
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/VertexBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
VertexBuffer::~VertexBuffer()
{
	Clear();

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferNum--;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VertexBuffer::VertexBuffer(PLRenderer::Renderer &cRenderer) : PLRenderer::VertexBuffer(cRenderer),
	m_pVertexBuffer(nullptr),
	m_pVertexDeclaration(nullptr),
	m_pData(nullptr),
	m_pLockedData(nullptr),
	m_nUsageAPI(0)
{
	// Init data
	MemoryManager::Set(m_nOffset, -1, sizeof(int)*NumOfSemantics*MaxPipelineChannels);

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(cRenderer).GetWritableStatistics().nVertexBufferNum++;
}

/**
*  @brief
*    Makes this vertex buffer to the renderers current vertex buffer
*/
bool VertexBuffer::MakeCurrent()
{
	return MakeCurrent(0, 0);
}

/**
*  @brief
*    Makes this vertex buffer to the renderers current vertex buffer
*/
bool VertexBuffer::MakeCurrent(uint32 nStreamNumber, uint32 nOffset)
{
	// Check if there's an vertex buffer and declaration and check if there are renderer information
	if ((m_pVertexBuffer || m_pData) && m_pVertexDeclaration) {
		LPDIRECT3DDEVICE9 pDevice = static_cast<Renderer&>(GetRenderer()).GetDevice();
		if (pDevice) {
			if (m_pData)
				return true; // Done

			// Make this vertex buffer to the renderers current one
			uint32 nBytesOffset = GetVertexSize()*nOffset; // Get the vertex offset in bytes
			return (pDevice->SetStreamSource(nStreamNumber, m_pVertexBuffer, nBytesOffset, m_nVertexSize) == D3D_OK);
		}
	}

	// Error!
	return false;
}

/**
*  @brief
*    Returns the vertex declaration
*/
LPDIRECT3DVERTEXDECLARATION9 VertexBuffer::GetVertexDeclaration() const
{
	return m_pVertexDeclaration;
}

/**
*  @brief
*    Returns the API vertex buffer
*/
LPDIRECT3DVERTEXBUFFER9 VertexBuffer::GetAPIVertexBuffer() const
{
	return m_pVertexBuffer;
}

/**
*  @brief
*    Create a vertex declaration so we can describe to Direct3D how we'll
*    be passing our data to it
*/
bool VertexBuffer::CreateVertexDeclaration()
{
	// Check if there are renderer information
	LPDIRECT3DDEVICE9 pDevice = static_cast<Renderer&>(GetRenderer()).GetDevice();
	if (pDevice) {
		D3DVERTEXELEMENT9 *pDeclarations = new D3DVERTEXELEMENT9[m_lstVertexAttributes.GetNumOfElements()+1];

		// Set vertex declarations
		for (uint32 i=0; i<m_lstVertexAttributes.GetNumOfElements(); i++) {
			// Get declaration
			D3DVERTEXELEMENT9 *pDecl = &pDeclarations[i];
			const Attribute &cAttribute = *m_lstVertexAttributes[i];

			// Get the API dependent usage
			uint8 nUsageAPI;
			switch (cAttribute.nSemantic) {
				case Position:
					nUsageAPI = D3DDECLUSAGE_POSITION;
					break;

				case BlendWeight:
					nUsageAPI = D3DDECLUSAGE_BLENDWEIGHT;
					break;

				case Normal:
					nUsageAPI = D3DDECLUSAGE_NORMAL;
					break;

				case Color:
					nUsageAPI = D3DDECLUSAGE_COLOR;
					break;

				case FogCoord:
					nUsageAPI = D3DDECLUSAGE_FOG;
					break;

				case PointSize:
					nUsageAPI = D3DDECLUSAGE_PSIZE;
					break;

				case BlendIndices:
					nUsageAPI = D3DDECLUSAGE_BLENDINDICES;
					break;

				case TexCoord:
					nUsageAPI = D3DDECLUSAGE_TEXCOORD;
					break;

				case Tangent:
					nUsageAPI = D3DDECLUSAGE_TANGENT;
					break;

				case Binormal:
					nUsageAPI = D3DDECLUSAGE_BINORMAL;
					break;

				default:
					delete [] pDecl;
					return false;	// Error!
			}

			// Set declaration
			pDecl->Stream	  = 0;
			pDecl->Offset	  = static_cast<WORD>(cAttribute.nOffset);
			pDecl->Type		  = static_cast<uint8>(cAttribute.nTypeAPI);
			pDecl->Method	  = D3DDECLMETHOD_DEFAULT;
			pDecl->Usage	  = nUsageAPI;
			pDecl->UsageIndex = static_cast<BYTE>(cAttribute.nChannel);
		}

		// End of declaration (see D3DDECL_END())
		D3DVERTEXELEMENT9 *pDecl = &pDeclarations[m_lstVertexAttributes.GetNumOfElements()];
		pDecl->Stream	  = 0xFF;
		pDecl->Offset	  = 0;
		pDecl->Type		  = D3DDECLTYPE_UNUSED;
		pDecl->Method	  = 0;
		pDecl->Usage	  = 0;
		pDecl->UsageIndex = 0;

		// Create Direct3D declaration
		if (pDevice->CreateVertexDeclaration(pDeclarations, &m_pVertexDeclaration) == D3D_OK) {
			delete [] pDeclarations;

			// Done
			return true;
		}
		delete [] pDeclarations;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Destroy the vertex declaration
*/
void VertexBuffer::DestroyVertexDeclaration()
{
	if (m_pVertexDeclaration) {
		m_pVertexDeclaration->Release();
		m_pVertexDeclaration = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::VertexBuffer functions     ]
//[-------------------------------------------------------]
void *VertexBuffer::GetData(uint32 nIndex, uint32 nSemantic, uint32 nChannel)
{
	// Check whether data is locked
	if (m_pLockedData) {
		// Check whether the index is correct
		if (nIndex < m_nElements) {
			// Check whether the channel and semantic is correct
			if (nChannel < MaxPipelineChannels && nSemantic >= Position && nSemantic <= Binormal) {
				// Return the vertex buffer attribute data
				if (m_nOffset[nSemantic][nChannel] >= 0)
					return static_cast<uint8*>(m_pLockedData)+nIndex*m_nVertexSize+m_nOffset[nSemantic][nChannel];
			}
		}
	}

	// Error!
	return nullptr;
}

Color4 VertexBuffer::GetColor(uint32 nIndex, uint32 nChannel)
{
	// Check whether the index is correct
	if (nIndex < m_nElements) {
		// Check whether the channel is correct
		if (nChannel < 2) {
			// Return the color of the vertex
			const uint32 *pnColor = static_cast<const uint32*>(GetData(nIndex, Color, nChannel));
			if (pnColor)
				return Color4(Color4::RedFromUInt32(*pnColor), Color4::GreenFromUInt32(*pnColor), Color4::BlueFromUInt32(*pnColor), Color4::AlphaFromUInt32(*pnColor));
		}
	}

	// Error!
	return Color4::White;
}

bool VertexBuffer::SetColor(uint32 nIndex, const Color4 &cColor, uint32 nChannel)
{
	// Check whether the index is correct
	if (nIndex < m_nElements) {
		// Check whether the channel is correct
		if (nChannel < 2) {
			// Set the color of the vertex
			uint32 *pnColor = static_cast<uint32*>(GetData(nIndex, Color, nChannel));
			if (pnColor) {
				*pnColor = cColor.ToUInt32();

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::VertexBuffer functions    ]
//[-------------------------------------------------------]
void VertexBuffer::VertexAttributeAdded(Attribute &cAttribute)
{
	// Setup API dependent attribute values
	switch (cAttribute.nType) {
		// Color (legacy API dependent storage which is no longer required when using modern shader based API's, do always use GetColor() and SetColor()!)
		case RGBA:
			cAttribute.nSizeAPI       = sizeof(D3DCOLOR);
			cAttribute.nTypeAPI       = D3DDECLTYPE_D3DCOLOR;
			cAttribute.nComponentsAPI = 1;
			break;

		// Float 1 (one component per element, 32 bit floating point per component)
		case Float1:
			cAttribute.nSizeAPI       = sizeof(float);
			cAttribute.nTypeAPI       = D3DDECLTYPE_FLOAT1;
			cAttribute.nComponentsAPI = 1;
			break;

		// Float 2 (two components per element, 32 bit floating point per component)
		case Float2:
			cAttribute.nSizeAPI       = sizeof(float)*2;
			cAttribute.nTypeAPI       = D3DDECLTYPE_FLOAT2;
			cAttribute.nComponentsAPI = 1;
			break;

		// Float 3 (three components per element, 32 bit floating point per component)
		case Float3:
			cAttribute.nSizeAPI       = sizeof(float)*3;
			cAttribute.nTypeAPI       = D3DDECLTYPE_FLOAT3;
			cAttribute.nComponentsAPI = 1;
			break;

		// Float 4 (four components per element, 32 bit floating point per component)
		case Float4:
			cAttribute.nSizeAPI       = sizeof(float)*4;
			cAttribute.nTypeAPI       = D3DDECLTYPE_FLOAT4;
			cAttribute.nComponentsAPI = 1;
			break;

		// Short 2 (two components per element, 16 bit integer per component)
		case Short2:
			cAttribute.nSizeAPI       = sizeof(short)*2;
			cAttribute.nTypeAPI       = D3DDECLTYPE_SHORT2;
			cAttribute.nComponentsAPI = 1;
			break;

		// Short 4 (four components per element, 16 bit integer per component)
		case Short4:
			cAttribute.nSizeAPI       = sizeof(short)*4;
			cAttribute.nTypeAPI       = D3DDECLTYPE_SHORT4;
			cAttribute.nComponentsAPI = 1;
			break;

		// Half 1 (one component per element, 16 bit floating point per component, may not be supported by each API)
		// Half 2 (two components per element, 16 bit floating point per component, may not be supported by each API)
		// Half 3 (three components per element, 16 bit floating point per component, may not be supported by each API)
		// Half 4 (four components per element, 16 bit floating point per component, may not be supported by each API)
		case Half1:
		case Half2:
		case Half3:
		case Half4:
			// Not supported
			cAttribute.nSizeAPI       = 0;
			cAttribute.nTypeAPI       = 0;
			cAttribute.nComponentsAPI = 0;
			break;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Buffer functions           ]
//[-------------------------------------------------------]
bool VertexBuffer::IsAllocated() const
{
	return (m_pVertexBuffer != nullptr || m_pData != nullptr);
}

bool VertexBuffer::Allocate(uint32 nElements, PLRenderer::Usage::Enum nUsage, bool bManaged, bool bKeepData)
{
	// Check if we have to reallocate the buffer
	if (m_nSize != m_nVertexSize*nElements || m_nUsage != nUsage || m_bManaged != bManaged) {
		// Check if there are renderer information
		LPDIRECT3DDEVICE9 pDevice = static_cast<Renderer&>(GetRenderer()).GetDevice();
		if (!pDevice)
			return false; // Error!

		// Check the vertex buffer size
		if (m_nVertexSize*nElements <= 0)
			return false; // Error!

		// Get API dependent usage
		if (nUsage == PLRenderer::Usage::Static)
			m_nUsageAPI = 0;
		else if (nUsage == PLRenderer::Usage::Dynamic) {
			// Jpip, D3DUSAGE_DYNAMIC and D3DPOOL_MANAGED are incompatible in D3D...
			if (bManaged)
				m_nUsageAPI = 0; // Don't try to set D3DUSAGE_DYNAMIC, OR CreateVertexBuffer() will slap you with an invalid call!
			else
				m_nUsageAPI = D3DUSAGE_DYNAMIC;
		} else if (nUsage == PLRenderer::Usage::WriteOnly) {
			m_nUsageAPI = D3DUSAGE_WRITEONLY;
		} else if (nUsage != PLRenderer::Usage::Software) {
			m_nUsageAPI = 0;

			// Error!
			return false;
		} else {
			m_nUsageAPI = 0;
		}

		// If the buffer is already allocated...
		uint8 *pDataBackup = nullptr;
		uint32 nSizeBackup = m_nSize;
		if (m_pData && m_nSize != m_nVertexSize*nElements) {
			// Backup the current data
			pDataBackup = new uint8[m_nSize];
			MemoryManager::Copy(pDataBackup, m_pData, m_nSize);

			// Delete data
			delete [] m_pData;
			m_pData = nullptr;
		} else if (m_pVertexBuffer && Lock(PLRenderer::Lock::ReadOnly)) {
			// Backup the current data
			pDataBackup = new uint8[m_nSize];
			MemoryManager::Copy(pDataBackup, GetData(), m_nSize);
			Unlock();

			// Delete vertex buffer object
			m_pVertexBuffer->Release();
			m_pVertexBuffer = nullptr;
		}
		ForceUnlock();

		// Update renderer statistics
		static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferMem -= m_nSize;

		// Setup data
		m_nElements = nElements;
		m_nSize		= m_nVertexSize*m_nElements;
		m_nUsage	= nUsage;
		m_bManaged  = bManaged;

		// Create the vertex buffer
		if (nUsage != PLRenderer::Usage::Software) {
			// Create the Direct3D vertex buffer
			if (pDevice->CreateVertexBuffer(m_nSize, m_nUsageAPI,
											0, m_bManaged ? D3DPOOL_MANAGED : D3DPOOL_DEFAULT,
											&m_pVertexBuffer, nullptr) != D3D_OK)
				return false; // Error!

			// Create vertex declaration
			if (!CreateVertexDeclaration())
				return false; // Error!
		} else {
			// No VBO
			if (!m_pData)
				m_pData = new uint8[m_nSize];
		}

		// Restore old data if required
		if (pDataBackup) {
			// We can just copy the old data in... vertex size CAN'T change in this situation!
			if (Lock(PLRenderer::Lock::WriteOnly)) {
				uint32 nSize = nSizeBackup;
				if (nSize > m_nSize)
					nSize = m_nSize;
				MemoryManager::Copy(GetData(), pDataBackup, nSize);
				Unlock();
			}

			// Cleanup
			delete [] pDataBackup;
		}

		// Update renderer statistics
		static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferMem += m_nSize;
	}

	// Get data attribute offsets
	MemoryManager::Set(m_nOffset, -1, sizeof(int)*NumOfSemantics*MaxPipelineChannels);
	for (uint32 i=0; i<m_lstVertexAttributes.GetNumOfElements(); i++) {
		const Attribute &cAttribute = *m_lstVertexAttributes[i];
		m_nOffset[cAttribute.nSemantic][cAttribute.nChannel] = cAttribute.nOffset;
	}

	// Done
	return true;
}

bool VertexBuffer::Clear()
{
	ForceUnlock();
	DestroyVertexDeclaration();
	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	} else if (m_pData) {
		delete [] m_pData;
		m_pData = nullptr;
	} else {
		// Error!
		return false;
	}

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferMem -= m_nSize;

	// Init
	m_nElements	= 0;
	m_nSize		= 0;
	m_nUsage	= PLRenderer::Usage::Unknown;
	m_nUsageAPI	= 0;
	MemoryManager::Set(m_nOffset, -1, sizeof(int)*NumOfSemantics*MaxPipelineChannels);

	// Done
	return true;
}

void *VertexBuffer::Lock(uint32 nFlag)
{
	// Check whether there's a vertex buffer
	if (!m_pVertexBuffer && !m_pData)
		return nullptr; // Error!

	// Check whether the vertex buffer is already locked
	m_nLockCount++;
	if (!m_pLockedData) {
		// Get API dependent flag
		uint32 nFlagAPI;
		if (nFlag == PLRenderer::Lock::ReadOnly)
			nFlagAPI = D3DLOCK_READONLY;
		else if (nFlag == PLRenderer::Lock::WriteOnly)
			nFlagAPI = 0;
		else if (nFlag == PLRenderer::Lock::ReadWrite)
			nFlagAPI = 0;
		else
			return nullptr; // Error!

		// Lock the vertex buffer
		static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferLocks++;
		m_nLockStartTime = System::GetInstance()->GetMicroseconds();
		if (m_pVertexBuffer && m_pVertexBuffer->Lock(0, 0, &m_pLockedData, nFlagAPI) != D3D_OK)
			return nullptr; // Error!
		if (m_pData)
			m_pLockedData = m_pData;

		// Lock valid?
		if (!m_pLockedData)
			m_nLockCount--;
	}

	// Return the vertex buffer data
	return m_pLockedData;
}

void *VertexBuffer::GetData()
{
	return m_pLockedData;
}

bool VertexBuffer::Unlock()
{
	// Check whether data is locked
	if (!m_pLockedData)
		return false; // Error!

	// Do we have to unlock the buffer now?
	m_nLockCount--;
	if (!m_nLockCount) {
		// Unlock the vertex buffer
		m_pLockedData = nullptr;
		if (m_pVertexBuffer && m_pVertexBuffer->Unlock() != D3D_OK)
			return false; // Error!
		static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBuffersSetupTime += System::GetInstance()->GetMicroseconds()-m_nLockStartTime;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void VertexBuffer::BackupDeviceData(uint8 **ppBackup)
{
	// Backup required?
	if (m_bManaged || GetUsage() >= PLRenderer::Usage::Software) {
		// Nope, D3D will do the dirty work for us if required!
		*ppBackup = nullptr;
	} else {
		// Backup data
		if (Lock(PLRenderer::Lock::ReadOnly)) {
			*ppBackup = new uint8[m_nSize];
			MemoryManager::Copy(ppBackup, GetData(), m_nSize);
			ForceUnlock();
		} else {
			*ppBackup = nullptr;
		}

		// Release the vertex buffer
		if (m_pVertexBuffer) {
			m_pVertexBuffer->Release();
			m_pVertexBuffer = nullptr;
		}
		DestroyVertexDeclaration();
	}
}

void VertexBuffer::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore required?
	if (!m_bManaged && GetUsage() < PLRenderer::Usage::Software && *ppBackup) {
		// Restore data
		static_cast<Renderer&>(GetRenderer()).GetDevice()->CreateVertexBuffer(m_nSize,
																			  m_nUsageAPI, 0, m_bManaged ? D3DPOOL_MANAGED : D3DPOOL_DEFAULT,
																			  &m_pVertexBuffer, nullptr);
		CreateVertexDeclaration();
		if (Lock(PLRenderer::Lock::WriteOnly)) {
			MemoryManager::Copy(GetData(), *ppBackup, m_nSize);
			Unlock();
		}

		// Destroy memory
		delete [] *ppBackup;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9
