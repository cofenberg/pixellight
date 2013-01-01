/*********************************************************\
 *  File: IndexBuffer.cpp                                *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/System/System.h>
#include "PLRendererD3D11/Renderer.h"
#include "PLRendererD3D11/IndexBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererD3D11 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
IndexBuffer::~IndexBuffer()
{
	Clear();

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferNum--;
}

/**
*  @brief
*    Returns the Direct3D buffer
*/
ID3D11Buffer *IndexBuffer::GetD3D11Buffer()
{
	// Do we need to update the IBO?
	if (m_bUpdateIBO && m_pData) {
		// Upload new data
		if (m_pD3D11Buffer) {
			// Get the used D3D11 device context
			ID3D11DeviceContext *pD3D11DeviceContext = static_cast<Renderer&>(GetRenderer()).GetD3D11DeviceContext();
			if (pD3D11DeviceContext) {
				// Upload
				pD3D11DeviceContext->UpdateSubresource(m_pD3D11Buffer, 0, nullptr, m_pData, 0, 0);
			}
		}

		// The data is now up-to-date
		m_bUpdateIBO = false;
	}

	// Return the Direct3D buffer
	return m_pD3D11Buffer;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IndexBuffer::IndexBuffer(PLRenderer::Renderer &cRenderer) : PLRenderer::IndexBuffer(cRenderer),
	m_pData(nullptr),
	m_pLockedData(nullptr),
	m_pD3D11Buffer(nullptr),
	m_nDXGIFormat(DXGI_FORMAT_UNKNOWN),
	m_bLockReadOnly(false),
	m_bUpdateIBO(false)
{
	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(cRenderer).GetWritableStatistics().nIndexBufferNum++;
}

/**
*  @brief
*    Makes this index buffer to the renderers current index buffer
*/
bool IndexBuffer::MakeCurrent()
{
	// Get the up-to-date Direct3D buffer
	ID3D11Buffer *pD3D11Buffer = GetD3D11Buffer();
	if (pD3D11Buffer) {
		// Get the used D3D11 device context
		ID3D11DeviceContext *pD3D11DeviceContext = static_cast<Renderer&>(GetRenderer()).GetD3D11DeviceContext();
		if (pD3D11DeviceContext) {
			// Done
			pD3D11DeviceContext->IASetIndexBuffer(pD3D11Buffer, m_nDXGIFormat, 0);
			return true;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Buffer functions           ]
//[-------------------------------------------------------]
bool IndexBuffer::IsAllocated() const
{
	return (m_pData != nullptr);
}

bool IndexBuffer::Allocate(uint32 nElements, PLRenderer::Usage::Enum nUsage, bool bManaged, bool bKeepData)
{
	// Get API dependent type
	uint32 nElementSizeAPI;
	DXGI_FORMAT nDXGIFormat = DXGI_FORMAT_UNKNOWN;
	if (m_nElementType == UInt) {
		nElementSizeAPI = sizeof(uint32);
		nDXGIFormat     = DXGI_FORMAT_R32_UINT;
	} else if (m_nElementType == UShort) {
		nElementSizeAPI = sizeof(uint16);
		nDXGIFormat     = DXGI_FORMAT_R16_UINT;
	} else if (m_nElementType == UByte) {
		nElementSizeAPI = sizeof(uint8);
		nDXGIFormat     = DXGI_FORMAT_R8_UINT;
	} else {
		return false; // Error!
	}

	// Check if we have to reallocate the buffer
	if (m_nSize == nElementSizeAPI*nElements && nUsage == m_nUsage && m_bManaged == bManaged)
		return true; // Done

	// Get the used D3D11 device instance
	ID3D11Device *pD3D11Device = static_cast<Renderer&>(GetRenderer()).GetD3D11Device();
	if (!pD3D11Device)
		return false; // Error!

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferMem -= m_nSize;

	// Init data
	uint8 *pDataBackup = nullptr;
	uint32 nSizeBackup = m_nSize;
	if (m_pData && m_nSize != nElementSizeAPI*nElements) {
		// Backup the current data
		if (bKeepData) {
			pDataBackup = new uint8[m_nSize];
			MemoryManager::Copy(pDataBackup, m_pData, m_nSize);
		}

		// Delete data
		if (m_nElementType == UInt)
			delete [] static_cast<uint32*>(m_pData);
		else if (m_nElementType == UShort)
			delete [] static_cast<uint16*>(m_pData);
		else
			delete [] static_cast<uint8*>(m_pData);
		m_pData = nullptr;
	}
	ForceUnlock();
	m_nElements = nElements;
	m_nUsage    = nUsage;
	m_bManaged  = bManaged;
	m_nSize     = nElementSizeAPI*m_nElements;

	// Create the index buffer
	if (!m_pData)
		m_pData = new uint8[m_nSize];

	// Restore old data if required
	if (pDataBackup) {
		// We can just copy the old data in...
		uint32 nSize = nSizeBackup;
		if (nSize > m_nSize)
			nSize = m_nSize;
		MemoryManager::Copy(m_pData, pDataBackup, nSize);

		// Cleanup
		if (m_nElementType == UInt)
			delete [] pDataBackup;
		else if (m_nElementType == UShort)
			delete [] pDataBackup;
		else
			delete [] pDataBackup;
	}

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferMem += m_nSize;

	// Fill in a Direct3D buffer description
	D3D11_BUFFER_DESC sD3D11BufferDesc;
	sD3D11BufferDesc.Usage			= D3D11_USAGE_DEFAULT;
	sD3D11BufferDesc.ByteWidth		= m_nSize;
	sD3D11BufferDesc.BindFlags		= D3D11_BIND_INDEX_BUFFER;
	sD3D11BufferDesc.CPUAccessFlags	= 0;
	sD3D11BufferDesc.MiscFlags		= 0;

	// Fill in the Direct3D subresource data
	D3D11_SUBRESOURCE_DATA sD3D11SubResourceData;
	sD3D11SubResourceData.pSysMem			= m_pData;
	sD3D11SubResourceData.SysMemPitch		= 0;
	sD3D11SubResourceData.SysMemSlicePitch	= 0;

	// Create the Direct3D index buffer
	m_bLockReadOnly = m_bUpdateIBO = false;
	if (m_pD3D11Buffer) {
		m_pD3D11Buffer->Release();
		m_pD3D11Buffer = nullptr;
	}
	m_nDXGIFormat = nDXGIFormat;
	return SUCCEEDED(pD3D11Device->CreateBuffer(&sD3D11BufferDesc, &sD3D11SubResourceData, &m_pD3D11Buffer));
}

bool IndexBuffer::Clear()
{
	if (!IsAllocated())
		return false; // Error!
	ForceUnlock();
	if (m_pD3D11Buffer) {
		m_pD3D11Buffer->Release();
		m_pD3D11Buffer = nullptr;
	}
	m_nDXGIFormat = DXGI_FORMAT_UNKNOWN;
	m_bLockReadOnly = m_bUpdateIBO = false;
	if (m_pData) {
		if (m_nElementType == UInt)
			delete [] static_cast<uint32*>(m_pData);
		else if (m_nElementType == UShort)
			delete [] static_cast<uint16*>(m_pData);
		else
			delete [] static_cast<uint8*>(m_pData);
		m_pData = nullptr;
	} else {
		return false; // Error!
	}

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferMem -= m_nSize;

	// Init
	m_nElements = 0;
	m_nSize     = 0;
	m_nUsage    = PLRenderer::Usage::Unknown;

	// Done
	return true;
}

void *IndexBuffer::Lock(uint32 nFlag)
{
	// Check whether there's an index buffer
	if (!m_pData)
		return nullptr; // Error!

	// Check whether the index buffer is already locked
	m_nLockCount++;
	if (m_pLockedData)
		return m_pLockedData; // Return the locked data

	// Read only?
	m_bLockReadOnly = (nFlag == PLRenderer::Lock::ReadOnly);

	// Lock the index buffer
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferLocks++;
	m_nLockStartTime = System::GetInstance()->GetMicroseconds();
	m_pLockedData = m_pData;

	// Return the index buffer data
	return m_pLockedData;
}

void *IndexBuffer::GetData()
{
	return m_pLockedData;
}

bool IndexBuffer::Unlock()
{
	// Check whether data is locked
	if (!m_pLockedData)
		return false; // Error!

	// Do we have to unlock the buffer now?
	m_nLockCount--;
	if (m_nLockCount)
		return true; // Nope, it's still used somewhere else...

	// Unlock the index buffer
	if (m_pData && m_pD3D11Buffer && !m_bLockReadOnly)
		m_bUpdateIBO = true;
	m_pLockedData = nullptr;
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBuffersSetupTime += System::GetInstance()->GetMicroseconds()-m_nLockStartTime;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D11
