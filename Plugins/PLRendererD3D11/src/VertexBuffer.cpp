/*********************************************************\
 *  File: VertexBuffer.cpp                               *
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
#include <PLRenderer/Renderer/Backend/RendererBackend.h>
#include "PLRendererD3D11/VertexBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
namespace PLRendererD3D11 {


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
	m_pData(nullptr),
	m_pLockedData(nullptr),
	m_nVertexOffset(0)
{
	// Init data
	MemoryManager::Set(m_nOffset, -1, sizeof(uint32)*NumOfSemantics*MaxPipelineChannels);

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(cRenderer).GetWritableStatistics().nVertexBufferNum++;
}

/**
*  @brief
*    Makes this vertex buffer to the renderers current vertex buffer
*/
bool VertexBuffer::MakeCurrent()
{
	return MakeCurrent(0);
}

/**
*  @brief
*    Makes this vertex buffer to the renderers current vertex buffer
*/
bool VertexBuffer::MakeCurrent(uint32 nOffset)
{
	// Check if there's an vertex buffer and declaration
	return (m_pData != nullptr);
}

/**
*  @brief
*    Returns the vertex offset
*/
uint32 VertexBuffer::GetVertexOffset() const
{
	return m_nVertexOffset;
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
			const float *pfColor = static_cast<const float*>(GetData(nIndex, Color, nChannel));
			if (pfColor)
				return Color4(pfColor[0], pfColor[1], pfColor[2], pfColor[3]);
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
			float *pfColor = static_cast<float*>(GetData(nIndex, Color, nChannel));
			if (pfColor) {
				pfColor[0] = cColor.r;
				pfColor[1] = cColor.g;
				pfColor[2] = cColor.b;
				pfColor[3] = cColor.a;

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
		case RGBA:
			cAttribute.nSizeAPI		  = sizeof(float)*4;
			cAttribute.nTypeAPI		  = 0;
			cAttribute.nComponentsAPI = 4;
			break;

		case Float1:
			cAttribute.nSizeAPI		  = sizeof(float);
			cAttribute.nTypeAPI		  = 0;
			cAttribute.nComponentsAPI = 1;
			break;

		case Float2:
			cAttribute.nSizeAPI		  = sizeof(float)*2;
			cAttribute.nTypeAPI		  = 0;
			cAttribute.nComponentsAPI = 2;
			break;

		case Float3:
			cAttribute.nSizeAPI		  = sizeof(float)*3;
			cAttribute.nTypeAPI		  = 0;
			cAttribute.nComponentsAPI = 3;
			break;

		case Float4:
			cAttribute.nSizeAPI		  = sizeof(float)*4;
			cAttribute.nTypeAPI		  = 0;
			cAttribute.nComponentsAPI = 4;
			break;

		case Short2:
			cAttribute.nSizeAPI		  = sizeof(short)*2;
			cAttribute.nTypeAPI		  = 0;
			cAttribute.nComponentsAPI = 2;
			break;

		case Short4:
			cAttribute.nSizeAPI		  = sizeof(short)*4;
			cAttribute.nTypeAPI		  = 0;
			cAttribute.nComponentsAPI = 4;
			break;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Buffer functions           ]
//[-------------------------------------------------------]
bool VertexBuffer::IsAllocated() const
{
	return (m_pData != nullptr);
}

bool VertexBuffer::Allocate(uint32 nElements, PLRenderer::Usage::Enum nUsage, bool bManaged, bool bKeepData)
{
	// Check if we have to reallocate the buffer
	if (m_nSize != m_nVertexSize*nElements || m_nUsage != nUsage || m_bManaged != bManaged) {
		// Check the vertex buffer size
		if (m_nVertexSize*nElements <= 0)
			return false; // Error!

		// If the buffer is already allocated...
		uint8 *pDataBackup = nullptr;
		uint32 nSizeBackup = m_nSize;
		if (m_pData && m_nSize != m_nVertexSize*nElements) {
			// Backup the current data
			if (bKeepData) {
				pDataBackup = new uint8[m_nSize];
				MemoryManager::Copy(pDataBackup, m_pData, m_nSize);
			}

			// Delete data
			delete [] m_pData;
			m_pData = nullptr;
		}
		ForceUnlock();

		// Update renderer statistics
		static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferMem -= m_nSize;

		// Setup data
		m_nElements  = nElements;
		m_nSize		 = m_nVertexSize*m_nElements;
		m_nUsage	 = nUsage;
		m_bManaged   = bManaged;

		// Create the vertex buffer
		if (!m_pData)
			m_pData = new uint8[m_nSize];

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
	if (m_pData) {
		delete [] m_pData;
		m_pData = nullptr;
	} else {
		// Error!
		return false;
	}

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferMem -= m_nSize;

	// Init
	m_nElements = 0;
	m_nSize     = 0;
	m_nUsage    = PLRenderer::Usage::Unknown;
	MemoryManager::Set(m_nOffset, -1, sizeof(int)*NumOfSemantics*MaxPipelineChannels);

	// Done
	return true;
}

void *VertexBuffer::Lock(uint32 nFlag)
{
	// Check whether there's a vertex buffer
	if (!m_pData)
		return nullptr; // Error!

	// Check whether the vertex buffer is already locked
	m_nLockCount++;
	if (m_pLockedData)
		return m_pLockedData; // Return the locked data

	// Check if there's an vertex buffer or the data is already locked
	if (m_pLockedData || !m_pData)
		return nullptr; // Error!

	// Lock the vertex buffer
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBufferLocks++;
	m_nLockStartTime = System::GetInstance()->GetMicroseconds();
	m_pLockedData = m_pData;

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
	if (m_nLockCount)
		return true; // Nope, it's still used somewhere else...

	// Unlock the vertex buffer
	m_pLockedData = nullptr;
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetWritableStatistics().nVertexBuffersSetupTime += System::GetInstance()->GetMicroseconds()-m_nLockStartTime;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D11
