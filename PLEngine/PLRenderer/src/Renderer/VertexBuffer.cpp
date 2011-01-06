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
#include <PLMath/Vector3.h>
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/FixedFunctions.h"
#include "PLRenderer/Renderer/IndexBuffer.h"
#include "PLRenderer/Renderer/VertexBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
VertexBuffer::~VertexBuffer()
{
	// Check if this is the renderers current fixed functions vertex buffer
	FixedFunctions *pFixedFunctions = GetRenderer().GetFixedFunctions();
	if (pFixedFunctions && pFixedFunctions->GetVertexBuffer() == this)
		pFixedFunctions->SetVertexBuffer();

	// Delete vertex attributes
	for (uint32 i=0; i<m_lstVertexAttributes.GetNumOfElements(); i++)
		delete m_lstVertexAttributes[i];
	m_lstVertexAttributes.Clear();
}

/**
*  @brief
*    Returns the number of vertex attributes
*/
uint32 VertexBuffer::GetNumOfVertexAttributes() const
{
	return m_lstVertexAttributes.GetNumOfElements();
}

/**
*  @brief
*    Clears the vertex attributes
*/
bool VertexBuffer::ClearVertexAttributes()
{
	// Is the vertex buffer already allocated?
	if (IsAllocated())
		return false; // Error!

	// Delete vertex attributes
	for (uint32 i=0; i<m_lstVertexAttributes.GetNumOfElements(); i++)
		delete m_lstVertexAttributes[i];
	m_lstVertexAttributes.Clear();

	// Done
	return true;
}

/**
*  @brief
*    Adds vertex attribute
*/
bool VertexBuffer::AddVertexAttribute(ESemantic nSemantic, uint32 nChannel, EType nType)
{
	// Check whether this semantic & channel is already used
	for (uint32 i=0; i<m_lstVertexAttributes.GetNumOfElements(); i++) {
		if (m_lstVertexAttributes[i]->nSemantic == nSemantic &&
			m_lstVertexAttributes[i]->nChannel  == nChannel)
			return false; // Error, the vertex attribute is already defined!
	}

	// Check normal, tangent and binormal
	if ((nSemantic == Normal || nSemantic == Tangent || nSemantic == Binormal) && nType != Float3)
		return false; // Error!

	// Check color
	if (nSemantic == Color && nType != RGBA)
		return false; // Error!

	// Check whether the channel is correct
	switch (nSemantic) {
		case Position: case Normal:
			if (nChannel > 1)
				return false; // Error!
			break;

		case Color:
			if (nChannel > 2)
				return false; // Error!
			break;
	}

	// Add vertex attribute
	Attribute *pAttribute = new Attribute;
	m_lstVertexAttributes.Add(pAttribute);
	// Setup values
	pAttribute->nSemantic	   = nSemantic;
	pAttribute->nChannel	   = nChannel;
	pAttribute->nType		   = nType;
	pAttribute->nOffset		   = m_nVertexSize;
	// This values will be setup through the API dependent function
	pAttribute->nSizeAPI	   = 0;
	pAttribute->nTypeAPI	   = 0;
	pAttribute->nComponentsAPI = 0;

	// Call API dependent vertex attribute added function
	VertexAttributeAdded(*pAttribute);

	// Update vertex size
	uint32 nVertexSize = m_nVertexSize;
	m_nVertexSize += pAttribute->nSizeAPI;

	// Is the vertex buffer already allocated?
	if (!IsAllocated())
		return true; // Yeah, that was pretty easy! :)

	// Uff, now we have to update the buffer!
	void *pData = Lock(Lock::ReadOnly);
	if (pData) {
		// Backup old buffer
		uint8 *pOldData = new uint8[GetSize()];
		MemoryManager::Copy(pOldData, pData, GetSize());

		// Allocate new buffer
		uint32      nElements = GetNumOfElements();
		Usage::Enum nUsage    = GetUsage();
		bool        bManaged  = IsManaged();
		Clear();  // Now 'pData' becomes invalid and we don't have to call Unlock() at the end
		Allocate(nElements, nUsage, bManaged);

		// Copy the old data into the new buffer
		if (Lock(Lock::WriteOnly)) {
			for (uint32 nElement=0; nElement<GetNumOfElements(); nElement++) {
				for (uint32 i=0; i<m_lstVertexAttributes.GetNumOfElements()-1; i++) {
					const Attribute *pCurrentAttribute = GetVertexAttribute(i);
					MemoryManager::Copy(GetData(nElement, pCurrentAttribute->nSemantic, pCurrentAttribute->nChannel),
										pOldData+nElement*nVertexSize+pCurrentAttribute->nOffset,
										pCurrentAttribute->nSizeAPI);
				}
			}

			// Unlock this buffer
			Unlock();
		}

		// Finally free the old buffer backup
		delete [] pOldData;
	}

	// Done
	return true;
}

/**
*  @brief
*    Returns a vertex attribute
*/
const VertexBuffer::Attribute *VertexBuffer::GetVertexAttribute(uint32 nIndex) const
{
	return m_lstVertexAttributes[nIndex];
}

/**
*  @brief
*    Returns the first found vertex attribute with the requested semantic
*/
const VertexBuffer::Attribute *VertexBuffer::GetVertexAttribute(ESemantic nSemantic, uint32 nChannel) const
{
	// Loop through all vertex attributes
	for (uint32 i=0; i<m_lstVertexAttributes.GetNumOfElements(); i++) {
		// Get the current vertex attribute
		const Attribute *pAttribute = m_lstVertexAttributes[i];

		// Semantic and channel match?
		if (pAttribute->nSemantic == nSemantic && pAttribute->nChannel == nChannel)
			return pAttribute; // Vertex attribute found!
	}

	// Error, no vertex attribute with the requested semantic found!
	return nullptr;
}

/**
*  @brief
*    Returns the vertex size in bytes
*/
uint32 VertexBuffer::GetVertexSize() const
{
	return m_nVertexSize;
}

/**
*  @brief
*    Copy operator
*/
VertexBuffer &VertexBuffer::operator =(const VertexBuffer &cSource)
{
	// Lock the source buffer
	if (((VertexBuffer&)cSource).Lock(Lock::ReadOnly)) {
		// Clear old vertex buffer
		Clear();
		ClearVertexAttributes();

		// Copy vertex attributes
		for (uint32 i=0; i<cSource.GetNumOfVertexAttributes(); i++) {
			const Attribute *pAttribute = cSource.GetVertexAttribute(i);
			if (pAttribute) AddVertexAttribute(pAttribute->nSemantic, pAttribute->nChannel, pAttribute->nType);
		}

		// Allocate this buffer
		Allocate(cSource.GetNumOfElements(), cSource.GetUsage(), cSource.IsManaged());

		// Lock this (target) buffer
		if (Lock(Lock::WriteOnly)) {
			// Copy the buffer data
			MemoryManager::Copy(GetData(), ((VertexBuffer&)cSource).GetData(), cSource.GetSize());

			// Unlock this (target) buffer
			Unlock();
		}

		// Unlock the source buffer
		((VertexBuffer&)cSource).Unlock();
	}

	// Done
	return *this;
}

/**
*  @brief
*    Returns the vertex buffer bounding box
*/
void VertexBuffer::CalculateBoundingBox(Vector3 &vMinPos, Vector3 &vMaxPos, PLRenderer::IndexBuffer *pIndexBuffer)
{
	// Initialize the parameters
	vMinPos = Vector3::Zero;
	vMaxPos = Vector3::Zero;

	// Index buffer given?
	if (pIndexBuffer) {
		// Lock this vertex buffer
		if (Lock(Lock::ReadOnly)) {
			// Lock the given index buffer
			if (pIndexBuffer->Lock(Lock::ReadOnly)) {
				// We have to take the indices typ into account...
				switch (pIndexBuffer->GetElementType()) {
					case IndexBuffer::UInt:
					{
						const uint32 *pIndices = (const uint32*)pIndexBuffer->GetData();
						if (pIndexBuffer->GetNumOfElements()) {
							const float *pfPos = (const float*)GetData(pIndices[0], Position);
							if (pfPos) {
								vMinPos = vMaxPos = pfPos;

								// Loop through all indices
								for (uint32 i=1; i<pIndexBuffer->GetNumOfElements(); i++) {
									pfPos = (const float*)GetData(pIndices[i], Position);
									// Min
									if (vMinPos.x > pfPos[0])
										vMinPos.x = pfPos[0];
									if (vMinPos.y > pfPos[1])
										vMinPos.y = pfPos[1];
									if (vMinPos.z > pfPos[2])
										vMinPos.z = pfPos[2];
									// Max
									if (vMaxPos.x < pfPos[0])
										vMaxPos.x = pfPos[0];
									if (vMaxPos.y < pfPos[1])
										vMaxPos.y = pfPos[1];
									if (vMaxPos.z < pfPos[2])
										vMaxPos.z = pfPos[2];
								}
							}
						}
						break;
					}

					case IndexBuffer::UShort:
					{
						const uint16 *pIndices = (const uint16*)pIndexBuffer->GetData();
						if (pIndexBuffer->GetNumOfElements()) {
							const float *pfPos = (const float*)GetData(pIndices[0], Position);
							if (pfPos) {
								vMinPos = vMaxPos = pfPos;

								// Loop through all indices
								for (uint32 i=1; i<pIndexBuffer->GetNumOfElements(); i++) {
									pfPos = (const float*)GetData(pIndices[i], Position);
									// Min
									if (vMinPos.x > pfPos[Vector3::X])
										vMinPos.x = pfPos[Vector3::X];
									if (vMinPos.y > pfPos[Vector3::Y])
										vMinPos.y = pfPos[Vector3::Y];
									if (vMinPos.z > pfPos[Vector3::Z])
										vMinPos.z = pfPos[Vector3::Z];
									// Max
									if (vMaxPos.x < pfPos[Vector3::X])
										vMaxPos.x = pfPos[Vector3::X];
									if (vMaxPos.y < pfPos[Vector3::Y])
										vMaxPos.y = pfPos[Vector3::Y];
									if (vMaxPos.z < pfPos[Vector3::Z])
										vMaxPos.z = pfPos[Vector3::Z];
								}
							}
						}
						break;
					}

					case IndexBuffer::UByte:
					{
						const uint8 *pIndices = (const uint8*)pIndexBuffer->GetData();
						if (pIndexBuffer->GetNumOfElements()) {
							const float *pfPos = (const float*)GetData(pIndices[0], Position);
							if (pfPos) {
								vMinPos = vMaxPos = pfPos;

								// Loop through all indices
								for (uint32 i=1; i<pIndexBuffer->GetNumOfElements(); i++) {
									pfPos = (const float*)GetData(pIndices[i], Position);
									// Min
									if (vMinPos.x > pfPos[Vector3::X])
										vMinPos.x = pfPos[Vector3::X];
									if (vMinPos.y > pfPos[Vector3::Y])
										vMinPos.y = pfPos[Vector3::Y];
									if (vMinPos.z > pfPos[Vector3::Z])
										vMinPos.z = pfPos[Vector3::Z];
									// Max
									if (vMaxPos.x < pfPos[Vector3::X])
										vMaxPos.x = pfPos[Vector3::X];
									if (vMaxPos.y < pfPos[Vector3::Y])
										vMaxPos.y = pfPos[Vector3::Y];
									if (vMaxPos.z < pfPos[Vector3::Z])
										vMaxPos.z = pfPos[Vector3::Z];
								}
							}
						}
						break;
					}
				}

				// Unlock the given index buffer
				pIndexBuffer->Unlock();
			}

			// Unlock this vertex buffer
			Unlock();
		}
	} else {
		// Lock this vertex buffer
		if (Lock(Lock::ReadOnly)) {
			const float *pfPos = (const float*)GetData(0, Position);
			if (pfPos) {
				vMinPos = vMaxPos = pfPos;

				// Loop through all indices
				for (uint32 i=1; i<m_nElements; i++) {
					pfPos = (const float*)GetData(i, Position);
					// Min
					if (vMinPos.x > pfPos[Vector3::X])
						vMinPos.x = pfPos[Vector3::X];
					if (vMinPos.y > pfPos[Vector3::Y])
						vMinPos.y = pfPos[Vector3::Y];
					if (vMinPos.z > pfPos[Vector3::Z])
						vMinPos.z = pfPos[Vector3::Z];
					// Max
					if (vMaxPos.x < pfPos[Vector3::X])
						vMaxPos.x = pfPos[Vector3::X];
					if (vMaxPos.y < pfPos[Vector3::Y])
						vMaxPos.y = pfPos[Vector3::Y];
					if (vMaxPos.z < pfPos[Vector3::Z])
						vMaxPos.z = pfPos[Vector3::Z];
				}
			}

			// Unlock this vertex buffer
			Unlock();
		}
	}
}

/**
*  @brief
*    Returns the vertex buffer bounding sphere
*/
void VertexBuffer::CalculateBoundingSphere(Vector3 &vPos, float &fRadius, PLRenderer::IndexBuffer *pIndexBuffer)
{
	// Initialize the parameters
	vPos    = Vector3::Zero;
	fRadius = 0.0f;

	// Index buffer given?
	if (pIndexBuffer) {
		// Lock this vertex buffer
		if (Lock(Lock::ReadOnly)) {
			// Lock the given index buffer
			if (pIndexBuffer->Lock(Lock::ReadOnly)) {
				// We have to take the indices typ into account...
				switch (pIndexBuffer->GetElementType()) {
					case IndexBuffer::UInt:
					{
						const uint32 *pIndices = (const uint32*)pIndexBuffer->GetData();
						if (pIndexBuffer->GetNumOfElements()) {
							const float *pfPos = (const float*)GetData(pIndices[0], Position);
							if (pfPos) {
								// Average points to get approximate center
								for (uint32 i=0; i<pIndexBuffer->GetNumOfElements(); i++) {
									pfPos = (const float*)GetData(pIndices[i], Position);
									vPos.x += pfPos[0];
									vPos.y += pfPos[1];
									vPos.z += pfPos[2];
								}
								vPos /= (float)pIndexBuffer->GetNumOfElements();

								// Find maximum distance from center (sphere radius)
								Vector3 vV;
								for (uint32 i=0; i<pIndexBuffer->GetNumOfElements(); i++) {
									vV      = (float*)GetData(pIndices[i], Position);
									fRadius = Math::Max(fRadius, (vV-vPos).GetSquaredLength());
								}
								fRadius = Math::Sqrt(fRadius);
							}
						}
						break;
					}

					case IndexBuffer::UShort:
					{
						const uint16 *pIndices = (const uint16*)pIndexBuffer->GetData();
						if (pIndexBuffer->GetNumOfElements()) {
							const float *pfPos = (const float*)GetData(pIndices[0], Position);
							if (pfPos) {
								// Average points to get approximate center
								for (uint32 i=0; i<pIndexBuffer->GetNumOfElements(); i++) {
									pfPos = (const float*)GetData(pIndices[i], Position);
									vPos.x += pfPos[0];
									vPos.y += pfPos[1];
									vPos.z += pfPos[2];
								}
								vPos /= (float)pIndexBuffer->GetNumOfElements();

								// Find maximum distance from center (sphere radius)
								Vector3 vV;
								for (uint32 i=0; i<pIndexBuffer->GetNumOfElements(); i++) {
									vV      = (float*)GetData(pIndices[i], Position);
									fRadius = Math::Max(fRadius, (vV-vPos).GetSquaredLength());
								}
								fRadius = Math::Sqrt(fRadius);
							}
						}
						break;
					}

					case IndexBuffer::UByte:
					{
						const uint8 *pIndices = (const uint8*)pIndexBuffer->GetData();
						if (pIndexBuffer->GetNumOfElements()) {
							const float *pfPos = (const float*)GetData(pIndices[0], Position);
							if (pfPos) {
								// Average points to get approximate center
								for (uint32 i=0; i<pIndexBuffer->GetNumOfElements(); i++) {
									pfPos = (const float*)GetData(pIndices[i], Position);
									vPos.x += pfPos[0];
									vPos.y += pfPos[1];
									vPos.z += pfPos[2];
								}
								vPos /= (float)pIndexBuffer->GetNumOfElements();

								// Find maximum distance from center (sphere radius)
								Vector3 vV;
								for (uint32 i=0; i<pIndexBuffer->GetNumOfElements(); i++) {
									vV      = (float*)GetData(pIndices[i], Position);
									fRadius = Math::Max(fRadius, (vV-vPos).GetSquaredLength());
								}
								fRadius = Math::Sqrt(fRadius);
							}
						}
						break;
					}
				}

				// Unlock the given index buffer
				pIndexBuffer->Unlock();
			}

			// Unlock this vertex buffer
			Unlock();
		}
	} else {
		// Lock this vertex buffer
		if (Lock(Lock::ReadOnly)) {
			const float *pfPos = (const float*)GetData(0, Position);
			if (pfPos) {
				// Average points to get approximate center
				for (uint32 i=0; i<GetNumOfElements(); i++) {
					pfPos = (const float*)GetData(i, Position);
					vPos.x += pfPos[0];
					vPos.y += pfPos[1];
					vPos.z += pfPos[2];
				}
				vPos /= (float)GetNumOfElements();

				// Find maximum distance from center (sphere radius)
				Vector3 vV;
				for (uint32 i=0; i<GetNumOfElements(); i++) {
					vV      = (float*)GetData(i, Position);
					fRadius = Math::Max(fRadius, (vV-vPos).GetSquaredLength());
				}
				fRadius = Math::Sqrt(fRadius);
			}

			// Unlock this vertex buffer
			Unlock();
		}
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VertexBuffer::VertexBuffer(Renderer &cRenderer) : Buffer(cRenderer, TypeVertexBuffer),
	m_nVertexSize(0)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
VertexBuffer::VertexBuffer(const VertexBuffer &cSource) : Buffer(cSource.GetRenderer(), TypeVertexBuffer),
	m_nVertexSize(cSource.GetVertexSize())
{
	// No implementation because the copy constructor is never used
}


//[-------------------------------------------------------]
//[ Public virtual Buffer functions                       ]
//[-------------------------------------------------------]
void *VertexBuffer::GetData()
{
	// We need this dummy default implementation because this function is used within this file!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
