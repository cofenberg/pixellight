/*********************************************************\
 *  File: IndexBuffer.cpp                                *
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
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Renderer/IndexBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
IndexBuffer::~IndexBuffer()
{
	// Check if this is the renderers current index buffer
	if (GetRenderer().GetIndexBuffer() == this)
		GetRenderer().SetIndexBuffer();
}

/**
*  @brief
*    Returns the type of the buffer elements
*/
IndexBuffer::EType IndexBuffer::GetElementType() const
{
	return m_nElementType;
}

/**
*  @brief
*    Sets the type of the buffer elements
*/
bool IndexBuffer::SetElementType(EType nType)
{
	// Is the index buffer already allocated?
	if (IsAllocated())
		return false; // Error!

	// Set element type
	m_nElementType = nType;

	// Done
	return true;
}

/**
*  @brief
*    Sets the type of the buffer elements automatically by using a given maximum vertex index
*/
bool IndexBuffer::SetElementTypeByMaximumIndex(PLGeneral::uint32 nMaximumIndex)
{
	// Is the index buffer already allocated?
	if (IsAllocated())
		return false; // Error!

	// Set element type
	if (nMaximumIndex <= MaxVertexIndexUByte)
		m_nElementType = UByte;
	else
		m_nElementType = (nMaximumIndex <= MaxVertexIndexUShort) ? UShort : UInt;

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
IndexBuffer &IndexBuffer::operator =(const IndexBuffer &cSource)
{
	// Lock the source buffer
	if (((IndexBuffer&)cSource).Lock(Lock::ReadOnly)) {
		// Clear old index buffer
		Clear();

		// Copy
		SetElementType(cSource.GetElementType());
		Allocate(cSource.GetNumOfElements(), cSource.GetUsage(), cSource.IsManaged());
		if (Lock(Lock::WriteOnly)) {
			MemoryManager::Copy(GetData(), ((IndexBuffer&)cSource).GetData(), cSource.GetSize());
			Unlock();
		}

		// Unlock the source buffer
		((IndexBuffer&)cSource).Unlock();
	}

	// Done
	return *this;
}

/**
*  @brief
*    Returns the data of the index buffer
*/
uint32 IndexBuffer::GetData(uint32 nIndex)
{
	// Check index
	if (nIndex < GetNumOfElements()) {
		// Get index data
		switch (m_nElementType) {
			case UInt:
			{
				const uint32 *pData = (const uint32*)GetData();
				if (pData)
					return pData[nIndex];
				break;
			}

			case UShort:
			{
				const uint16 *pData = (const uint16*)GetData();
				if (pData)
					return (uint32)pData[nIndex];
				break;
			}

			case UByte:
			{
				const uint8 *pData = (const uint8*)GetData();
				if (pData)
					return (uint8)pData[nIndex];
				break;
			}
		}
	}

	// Error!
	return 0;
}

/**
*  @brief
*    Sets the data of the index buffer
*/
bool IndexBuffer::SetData(uint32 nIndex, uint32 nData)
{
	// Check index
	if (nIndex < GetNumOfElements()) {
		// Get index data
		switch (m_nElementType) {
			case UInt:
			{
				uint32 *pData = (uint32*)GetData();
				if (pData) {
					pData[nIndex] = nData;

					// Done
					return true;
				}
				break;
			}

			case UShort:
			{
				uint16 *pData = (uint16*)GetData();
				if (pData) {
					pData[nIndex] = (uint16)nData;

					// Done
					return true;
				}
				break;
			}

			case UByte:
			{
				uint8 *pData = (uint8*)GetData();
				if (pData) {
					pData[nIndex] = (uint8)nData;

					// Done
					return true;
				}
				break;
			}
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IndexBuffer::IndexBuffer(Renderer &cRenderer) : Buffer(cRenderer, TypeIndexBuffer),
	m_nElementType(UShort)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
IndexBuffer::IndexBuffer(const IndexBuffer &cSource) : Buffer(cSource.GetRenderer(), TypeIndexBuffer),
	m_nElementType(cSource.GetElementType())
{
	// No implementation because the copy constructor is never used
}


//[-------------------------------------------------------]
//[ Public virtual Buffer functions                       ]
//[-------------------------------------------------------]
void *IndexBuffer::GetData()
{
	// We need this dummy default implementation because this function is used within this file!
	return NULL;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
