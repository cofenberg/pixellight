/*********************************************************\
 *  File: UniformBuffer.cpp                              *
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
#include "PLRendererOpenGL/Renderer.h"
#include "PLRendererOpenGL/UniformBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
UniformBuffer::~UniformBuffer()
{
	Clear();

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetStatisticsT().nUniformBufferNum--;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
UniformBuffer::UniformBuffer(PLRenderer::Renderer &cRenderer) : PLRenderer::UniformBuffer(cRenderer),
	m_nUniformBuffer(0)
{
	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(cRenderer).GetStatisticsT().nUniformBufferNum++;
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Buffer functions           ]
//[-------------------------------------------------------]
bool UniformBuffer::IsAllocated() const
{
	return (m_nUniformBuffer != 0);
}

bool UniformBuffer::Allocate(uint32 nElements, PLRenderer::Usage::Enum nUsage, bool bManaged, bool bKeepData)
{
	// [TODO]

	// Update renderer statistics
	static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetStatisticsT().nUniformBufferMem += m_nSize;

	// Done
	return true;
}

bool UniformBuffer::Clear()
{
	if (IsAllocated()) {
		ForceUnlock();
		if (m_nUniformBuffer) {
			glDeleteBuffersARB(1, &m_nUniformBuffer);
			m_nUniformBuffer = 0;
		}

		// Update renderer statistics
		static_cast<PLRenderer::RendererBackend&>(GetRenderer()).GetStatisticsT().nUniformBufferMem -= m_nSize;
	}

	// Done
	return true;
}

void *UniformBuffer::Lock(uint32 nFlag)
{
	// [TODO]
	return nullptr;
}

void *UniformBuffer::GetData()
{
	// [TODO]
	return nullptr;
}

bool UniformBuffer::Unlock()
{
	// [TODO]
	return false;
}


//[-------------------------------------------------------]
//[ Protected virtual PLRenderer::Resource functions      ]
//[-------------------------------------------------------]
void UniformBuffer::BackupDeviceData(uint8 **ppBackup)
{
	// [TODO]
}

void UniformBuffer::RestoreDeviceData(uint8 **ppBackup)
{
	// [TODO]
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
