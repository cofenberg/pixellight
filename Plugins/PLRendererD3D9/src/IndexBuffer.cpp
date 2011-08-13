/*********************************************************\
 *  File: IndexBuffer.cpp                                *
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
#include <PLCore/System/System.h>
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/IndexBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererD3D9 {


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


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IndexBuffer::IndexBuffer(PLRenderer::Renderer &cRenderer) : PLRenderer::IndexBuffer(cRenderer),
	m_pIndexBuffer(nullptr),
	m_pData(nullptr),
	m_pLockedData(nullptr),
	m_nUsageAPI(0),
	m_nTypeAPI(D3DFMT_UNKNOWN)
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
	// Check if there's an index buffer and check if there are renderer information
	if ((m_pIndexBuffer || m_pData) && static_cast<Renderer&>(GetRenderer()).GetDevice()) {
		// Make this index buffer to the renderers current one
		if (m_pIndexBuffer)
			return (static_cast<Renderer&>(GetRenderer()).GetDevice()->SetIndices(m_pIndexBuffer) == D3D_OK);
		else
			return true; // Done
	} else {
		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Buffer functions           ]
//[-------------------------------------------------------]
bool IndexBuffer::IsAllocated() const
{
	return (m_pIndexBuffer != nullptr || m_pData != nullptr);
}

bool IndexBuffer::Allocate(uint32 nElements, PLRenderer::Usage::Enum nUsage, bool bManaged, bool bKeepData)
{
	// Get API dependent type
	uint32 nElementSizeAPI;
	if (m_nElementType == UInt) {
		m_nTypeAPI		= D3DFMT_INDEX32;
		nElementSizeAPI = sizeof(uint32);
	} else if (m_nElementType == UShort) {
		m_nTypeAPI		= D3DFMT_INDEX16;
		nElementSizeAPI = sizeof(uint16);
	} else {
		// UByte is not supported by DirectX 9

		// Error!
		return false;
	}

	// Check if we have to reallocate the buffer
	if (m_nSize == nElementSizeAPI*nElements && nUsage == m_nUsage && m_bManaged == bManaged)
		return true; // Done

	// Check if there are renderer information
	if (!static_cast<Renderer&>(GetRenderer()).GetDevice())
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
		else
			delete [] static_cast<uint16*>(m_pData);
		m_pData = nullptr;
	} else if (m_pIndexBuffer) {
		if (bKeepData && !m_pData && !pDataBackup && Lock(PLRenderer::Lock::ReadOnly)) {
			// Backup the current data
			pDataBackup = new uint8[m_nSize];
			MemoryManager::Copy(pDataBackup, GetData(), m_nSize);
			Unlock();
		}

		// Delete index buffer object
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}
	ForceUnlock();
	m_nElements = nElements;
	m_nUsage    = nUsage;
	m_bManaged  = bManaged;
	m_nSize     = nElementSizeAPI*m_nElements;

	// Create the index buffer
	if (nUsage != PLRenderer::Usage::Software) {
		// Create the Direct3D index buffer
		if (static_cast<Renderer&>(GetRenderer()).GetDevice()->CreateIndexBuffer(m_nSize,
																				 m_nUsageAPI,
																				 m_nTypeAPI,
																				 m_bManaged ? D3DPOOL_MANAGED : D3DPOOL_DEFAULT,
																				 &m_pIndexBuffer,
																				 nullptr) != D3D_OK)
			return false; // Error!
	} else {
		// Create software index buffer
		if (!m_pData)
			m_pData = new uint8[m_nSize];
	}

	// Restore old data if required
	if (pDataBackup) {
		// We can just copy the old data in...
		if (Lock(PLRenderer::Lock::WriteOnly)) {
			uint32 nSize = nSizeBackup;
			if (nSize > m_nSize)
				nSize = m_nSize;
			MemoryManager::Copy(GetData(), pDataBackup, nSize);
			Unlock();
		}

		// Cleanup
		if (m_nElementType == UInt)
			delete [] static_cast<uint32*>(m_pData);
		else
			delete [] static_cast<uint16*>(m_pData);
	}

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferMem += m_nSize;

	// Done
	return true;
}

bool IndexBuffer::Clear()
{
	ForceUnlock();
	if (m_pIndexBuffer) {
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	} else if (m_pData) {
		if (m_nElementType == UInt)
			delete [] static_cast<uint32*>(m_pData);
		else
			delete [] static_cast<uint16*>(m_pData);
		m_pData = nullptr;
	} else {
		// Error!
		return false;
	}

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferMem -= m_nSize;

	// Init
	m_nElements	= 0;
	m_nSize		= 0;
	m_nUsage	= PLRenderer::Usage::Unknown;
	m_nTypeAPI	= D3DFMT_UNKNOWN;
	m_nUsageAPI	= 0;

	// Done
	return true;
}

void *IndexBuffer::Lock(uint32 nFlag)
{
	// Check whether there's an index buffer
	if (!m_pIndexBuffer && !m_pData)
		return nullptr; // Error!

	// Check whether the index buffer is already locked
	m_nLockCount++;
	if (m_pLockedData)
		return m_pLockedData;

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

	// Lock the index buffer
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBufferLocks++;
	m_nLockStartTime = System::GetInstance()->GetMicroseconds();
	if (m_pIndexBuffer) {
		if (m_pIndexBuffer->Lock(0, 0, &m_pLockedData, nFlagAPI) != D3D_OK)
			return nullptr; // Error!
	}
	if (m_pData)
		m_pLockedData = m_pData;

	// Lock valid?
	if (!m_pLockedData)
		m_nLockCount--;

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
	m_pLockedData = nullptr;
	if (m_pIndexBuffer) {
		if (m_pIndexBuffer->Unlock() != D3D_OK)
			return false; // Error!
	}
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nIndexBuffersSetupTime += System::GetInstance()->GetMicroseconds()-m_nLockStartTime;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void IndexBuffer::BackupDeviceData(uint8 **ppBackup)
{
	// Backup required?
	if (m_bManaged || GetUsage() >= PLRenderer::Usage::Software) {
		// Nope, D3D will do the dirty work for us if required!
		*ppBackup = nullptr;
	} else {
		// Backup data
		if (Lock(PLRenderer::Lock::ReadOnly)) {
			*ppBackup = new uint8[m_nSize];
			MemoryManager::Copy(*ppBackup, GetData(), m_nSize);
			ForceUnlock();
		} else {
			*ppBackup = nullptr;
		}

		// Release the index buffer
		if (m_pIndexBuffer) {
			m_pIndexBuffer->Release();
			m_pIndexBuffer = nullptr;
		}
	}
}

void IndexBuffer::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore required?
	if (!m_bManaged && GetUsage() < PLRenderer::Usage::Software && *ppBackup) {
		// Restore data
		static_cast<Renderer&>(GetRenderer()).GetDevice()->CreateIndexBuffer(m_nSize,
																			 m_nUsageAPI,
																			 m_nTypeAPI,
																			 m_bManaged ? D3DPOOL_MANAGED : D3DPOOL_DEFAULT,
																			 &m_pIndexBuffer,
																			 nullptr);
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
